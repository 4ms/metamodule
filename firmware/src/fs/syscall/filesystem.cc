#include "filesystem.hh"
#include "console/uart_log.hh"
#include "dirent.h"
#include "fat_file_io.hh"
#include "ff.h"
#include "filedesc_manager.hh"
#include "fs/helpers.hh"
#include "fs_syscall_proxy.hh"
#include "time_convert.hh"
#include <sys/fcntl.h>
#include <sys/stat.h>
#include <unistd.h>

// MetaModule::Filesystem is a wrapper for filesystem syscalls (fopen, fread, etc)
// to access the various FatFS volume on the MetaModule (RamDisk, SD, USB)
//
// Example call chain:
//
// User code calls fopen():
// -> newlib/libc function fopen() is defined in libc.a
//    -> _open() (defined in fs/syscall/syscalls.cc)
//       -> MetaModule::Filesystem::open (defined in this file)
//
//   Ramdisk -> RamDisk::open()
//              -> FatFileIO::open()
//                 -> f_open() (defined in fatfs/source/ff.c)
//
//   USB/SD  -> FSProxy::open()
//              -> FSProxyImpl::get_response_or_timeout()
//                 -> Core M4 handler calls f_open() (defined in fatfs/source/ff.c)

// TODO: make FsSyscallProxy and FatFileIO derive from DiskDevice (see TODO in fileio_t.hh)
// then for each function, we can get the device like:
// static DiskDevice *get_device(Volume volume) {
// 		if (volume == Volume::RamDisk)
// 			return mRamdisk;
// 		else if (volume === Volume::SDCard || volume == USB)
// 			return &fs_proxy;
// }
namespace MetaModule::Filesystem
{

namespace
{

// Private:
FatFileIO *mRamdisk{nullptr};
FsSyscallProxy fs_proxy;

} // namespace

void init(FatFileIO &ramdisk) {
	mRamdisk = &ramdisk;
	FileDescManager::init();
}

int open(const char *filename, int flags, int mode) {
	if (auto fd = FileDescManager::alloc_file()) {

		auto file = FileDescManager::filedesc(*fd);

		auto [path, volume] = split_volume(filename);

		if (volume == Volume::RamDisk || volume == Volume::SDCard || volume == Volume::USB) {
			uint8_t fatfs_modes = 0;

			if ((flags & O_ACCMODE) == O_RDWR)
				fatfs_modes = FA_READ | FA_WRITE;
			else if ((flags & O_ACCMODE) == O_RDONLY)
				fatfs_modes = FA_READ;
			else
				fatfs_modes = FA_WRITE;

			if (flags & O_CREAT) {
				if (flags & O_TRUNC)
					fatfs_modes |= FA_CREATE_ALWAYS;
				else
					fatfs_modes |= FA_OPEN_ALWAYS;
			}

			if (volume == Volume::RamDisk) {
				if (mRamdisk && mRamdisk->open(path, file->fatfil, fatfs_modes)) {
					file->vol = volume;
					return *fd;
				}
			} else {
				// SDCard or USB:
				if (fs_proxy.open(filename, file->fatfil, fatfs_modes)) {
					file->vol = volume;
					return *fd;
				}
			}
		}

		else if (volume == Volume::NorFlash)
		{
			pr_err("Filesystem access to internal NorFlash drive not permitted\n");
		}

		pr_err("Opening file '%s' on vol %d with flags %d mode %d failed\n", filename, (int)volume, flags, mode);
		FileDescManager::dealloc_file(*fd);
		return -1;

	} else {
		pr_err("cannot open any more files\n");
		return -1;
	}
}

int lseek(int fd, int offset, int whence) {
	if (auto file = FileDescManager::filedesc(fd)) {

		if (file->vol == Volume::RamDisk && mRamdisk) {
			return mRamdisk->seek(file->fatfil, offset, whence);
		}

		else if (file->vol == Volume::SDCard || file->vol == Volume::USB)
		{
			return fs_proxy.seek(file->fatfil, offset, whence);
		}
	}
	return -1;
}

int read(int fd, char *ptr, int len) {
	if (auto file = FileDescManager::filedesc(fd)) {

		auto buff = std::span{ptr, (size_t)len};

		if (file->vol == Volume::RamDisk && mRamdisk) {
			const auto bytes_read = mRamdisk->read(file->fatfil, buff);
			return bytes_read.value_or(-1);
		}

		else if (file->vol == Volume::SDCard || file->vol == Volume::USB)
		{
			auto bytes_read = fs_proxy.read(file->fatfil, buff);
			return bytes_read.value_or(-1);
		}
	}

	return -1;
}

int close(int fd) {
	if (auto file = FileDescManager::filedesc(fd)) {

		if (file->vol == Volume::RamDisk && mRamdisk) {
			mRamdisk->close(file->fatfil);
		}

		else if (file->vol == Volume::USB || file->vol == Volume::SDCard)
		{
			fs_proxy.close(file->fatfil);
		}

		FileDescManager::dealloc_file(fd);

		return 0;
	}
	return -1;
}

int isatty(int fd) {
	return FileDescManager::isatty(fd);
}

int fstat(int fd, struct stat *st) {
	if (FileDescManager::isatty(fd)) {
		st->st_mode = S_IFCHR;
		return 0;

	} else if (FileDescManager::filedesc(fd)) {
		st->st_mode = S_IFREG;
		pr_trace("Warning: fstat not fully supported: only the return value is valid, and st_mode field is valid\n");
		return 0;

	} else {
		return -1;
	}
}

int stat(const char *filename, struct stat *st) {
	auto [path, volume] = split_volume(filename);

	if (volume == Volume::RamDisk || volume == Volume::SDCard || volume == Volume::USB) {
		FILINFO filinfo;

		bool ok = false;
		if (volume == Volume::RamDisk && mRamdisk)
			ok = mRamdisk->get_fat_filinfo(path, filinfo);
		else
			ok = fs_proxy.stat(path, &filinfo);

		if (ok) {
			FatTime fattime{.date = filinfo.fdate, .time = filinfo.ftime};
			auto tm = fattime_to_tm(fattime);
			time_t secs = mktime(&tm);
			st->st_mtim.tv_sec = secs; //since poweron
			st->st_mtim.tv_nsec = secs * 1000;

			/// we don't know created time, use last modification
			st->st_ctim.tv_sec = secs;
			st->st_ctim.tv_nsec = secs * 1000;

			/// we don't know accessed time, use last modification
			st->st_atim.tv_sec = secs;
			st->st_atim.tv_nsec = secs * 1000;

			st->st_size = filinfo.fsize;

			st->st_mode = S_IFREG;
			return 0;
		}
	}

	pr_err("stat() on file %s on vol %d failed\n", filename, (int)volume);
	return -1;
}

DIR *opendir(std::string_view fullpath) {
	if (auto dirdesc = FileDescManager::alloc_dir()) {

		auto [path, volume] = split_volume(fullpath);

		if (volume == Volume::RamDisk && mRamdisk) {
			if (mRamdisk->opendir(path, dirdesc->dir)) {
				dirdesc->vol = volume;
				return dirdesc->dir;
			}
		}

		if (volume == Volume::SDCard || volume == Volume::USB) {
			if (fs_proxy.opendir(path, dirdesc->dir)) {
				dirdesc->vol = volume;
				return dirdesc->dir;
			}
		}

		pr_err("Opening dir %s on vol %d failed\n", fullpath.data(), (int)volume);
		FileDescManager::dealloc_dir(dirdesc);
		return nullptr;

	} else {
		pr_err("Cannot open any more dirs\n");
		return nullptr;
	}
}

dirent *readdir(DIR *dir) {
	if (!dir)
		return nullptr;

	auto dirdesc = FileDescManager::dirdesc(dir);
	if (!dirdesc)
		return nullptr;

	if (dirdesc->vol == Volume::RamDisk) {
		//TODO
	}

	else if (dirdesc->vol == Volume::SDCard || dirdesc->vol == Volume::USB)
	{
		FILINFO info;
		if (fs_proxy.readdir(dirdesc->dir, &info)) {
			strncpy(dirdesc->cur_entry.d_name, info.fname, 256);
			return &dirdesc->cur_entry;
		}
	}
	return nullptr;
}

void rewinddir(DIR *dir) {
	if (!dir)
		return;

	auto dirdesc = FileDescManager::dirdesc(dir);
	if (!dirdesc)
		return;

	if (dirdesc->vol == Volume::RamDisk) {
		//TODO
	}

	else if (dirdesc->vol == Volume::SDCard || dirdesc->vol == Volume::USB)
	{
		fs_proxy.readdir(dirdesc->dir, nullptr);
	}
}

int closedir(DIR *dir) {
	if (!dir)
		return -1;

	return FileDescManager::dealloc_dir(dir) ? 0 : -1;
}

int write(int fd, const char *ptr, int len) {
	if (fd == STDOUT_FILENO || fd == STDERR_FILENO) {
		UartLog::write_stdout(ptr, len);
		return len;

	} else if (auto file = FileDescManager::filedesc(fd)) {

		auto buff = std::span{ptr, (size_t)len};

		if (file->vol == Volume::RamDisk && mRamdisk) {
			// const auto bytes_read = mRamdisk->write_file(file->fatfil, buff);
			// return bytes_read.value_or(-1);
			return -1;
		}

		else if (file->vol == Volume::SDCard || file->vol == Volume::USB)
		{
			auto bytes_written = fs_proxy.write(file->fatfil, buff);
			return bytes_written.value_or(-1);
		}
	}

	return -1;
}

} // namespace MetaModule::Filesystem
