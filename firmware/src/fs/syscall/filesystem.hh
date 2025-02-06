#pragma once
#include "fat_file_io.hh"
#include "ff.h"
#include "filedesc_manager.hh"
#include "fs_syscall_proxy.hh"
#include <sys/stat.h>
#include <unistd.h>

// MetaModule::Filesystem is a wrapper for filesystem syscalls (fopen, fread, etc)
// to access the various FatFS volume on the MetaModule (RamDisk, SD, USB)
//
// Example call chain:
// fopen():
// -> newlib/libc functions (defined in libc.a)
// -> _open() (defined in fs/syscall/syscalls.cc)
// -> MetaModule::Filesystem::open (defined in this file)
// If the volume is:
//   Ramdisk -> RamDisk::open()
//           -> FatFileIO::open()
//           -> f_open() (defined in fatfs/source/ff.c)
//
//   USB/SD  -> FSProxy::open
//           -> FSProxyImpl::
//           -> Core M4 handler

namespace MetaModule
{

class Filesystem {
	static inline FatFileIO *mRamdisk{nullptr};
	static inline FsSyscallProxy fs_proxy;

public:
	static void init(FatFileIO &ramdisk) {
		mRamdisk = &ramdisk;
		FileDescManager::init();
	}

	static int open(const char *filename, int flags, int mode) {
		if (auto fd = FileDescManager::alloc_file()) {

			auto file = FileDescManager::filedesc(*fd);

			auto [path, volume] = split_volume(filename);

			if (volume == Volume::RamDisk) {
				if (mRamdisk) {
					if (mRamdisk->open(path, file->fatfil)) {
						file->vol = volume;
						return *fd;
					}
				}
			}

			if (volume == Volume::SDCard || volume == Volume::USB) {
				if (fs_proxy.open(path, file->fatfil, FA_READ)) {
					file->vol = volume;
					return *fd;
				}
			}

			pr_err("Opening file %s on vol %d failed\n", filename, (int)volume);
			FileDescManager::dealloc_file(*fd);
			return -1;

		} else {
			pr_err("cannot open any more files\n");
			return -1;
		}
	}

	static int lseek(int fd, int offset, int whence) {
		if (auto file = FileDescManager::filedesc(fd)) {

			if (file->vol == Volume::RamDisk) {
				if (mRamdisk) {
					return mRamdisk->seek(file->fatfil, offset, whence);
				}
			}

			if (file->vol == Volume::SDCard || file->vol == Volume::USB) {
				return fs_proxy.seek(file->fatfil, offset, whence);
			}
		}
		return -1;
	}

	static int read(int fd, char *ptr, int len) {
		if (auto file = FileDescManager::filedesc(fd)) {

			auto buff = std::span{ptr, (size_t)len};

			if (file->vol == Volume::RamDisk) {
				if (mRamdisk) {
					const auto bytes_read = mRamdisk->read(file->fatfil, buff);
					return bytes_read.value_or(-1);
				}
			}

			if (file->vol == Volume::SDCard || file->vol == Volume::USB) {
				auto bytes_read = fs_proxy.read(file->fatfil, buff);
				return bytes_read.value_or(-1);
			}
		}

		return -1;
	}

	static int close(int fd) {
		if (auto file = FileDescManager::filedesc(fd)) {

			if (file->vol == Volume::RamDisk) {
				if (mRamdisk) {
					mRamdisk->close(file->fatfil);
				}
			}

			if (file->vol == Volume::USB || file->vol == Volume::SDCard) {
				fs_proxy.close(file->fatfil);
			}

			FileDescManager::dealloc_file(fd);

			return 0;
		}
		return -1;
	}

	static int isatty(int fd) {
		return FileDescManager::isatty(fd);
	}

	static int fstat(int fd, struct stat *st) {
		if (FileDescManager::isatty(fd)) {
			st->st_mode = S_IFCHR;
			return 0;

		} else if (FileDescManager::filedesc(fd)) {
			st->st_mode = S_IFREG;
			return 0;

		} else {
			return -1;
		}
	}

private:
	static std::pair<std::string_view, Volume> split_volume(const char *filename) {
		auto sv = std::string_view{filename};

		if (sv.starts_with("ram:"))
			return {sv, Volume::RamDisk};

		if (sv.starts_with("usb:"))
			return {sv, Volume::USB};

		if (sv.starts_with("sdc:"))
			return {sv, Volume::SDCard};

		if (sv.starts_with("nor:"))
			return {sv, Volume::NorFlash};

		// Default (no volume given) is RamDisk
		return {sv, Volume::RamDisk};
	}
};
} // namespace MetaModule
