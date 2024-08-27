#include "CoreModules/fs_access.hh"
#include "fs_access_impl.hh"
#include <array>
#include <cstdarg>
#include <cstring>
#include <filesystem>
#include <string_view>

namespace MetaModule
{

static constexpr bool print_fs_calls = true;
static constexpr bool write_access = false;

static inline void fs_trace(const char *str) {
	if constexpr (print_fs_calls)
		printf("%s", str);
}

static inline void fs_trace(auto... args) {
	if constexpr (print_fs_calls)
		printf(args...);
}

FS::FS(std::string_view root)
	: impl{new Impl(root)} {
}

FS::~FS() = default;

// Valid Root

// FIXME: needs to match command-line args
std::array<std::string_view, 2> valid_roots{
	"./patches/",
	"../patches/",
};

bool FS::find_valid_root(std::string_view path) {
	auto t_root = impl->root;
	auto t_cwd = impl->cwd;

	for (auto root : valid_roots) {
		impl->root = root;
		impl->cwd = "";

		bool is_valid_root = false;
		if (path == "") {
			// f_stat cannot open root dir, so we use f_opendir;
			Dir dir;

			auto res = f_opendir(&dir, path.data());
			is_valid_root = (res == FR_OK);
			f_closedir(&dir);
		} else {
			Fileinfo info;
			auto res = f_stat(path.data(), &info);
			is_valid_root = (res == FR_OK);
		}

		if (is_valid_root) {
			impl->cwd = path;
			printf("Found valid root %s\n", impl->full_path("").c_str());
			return true;
		}
	}

	// no valid root found. restore previous values
	impl->root = t_root;
	impl->cwd = t_cwd;
	printf("No valid root found\n");

	return false;
}

// READING

FRESULT FS::f_open(File *fp, const char *path, uint8_t mode) {
	auto fullpath = impl->full_path(path);

	if (!write_access)
		mode &= ~(FA_WRITE | FA_CREATE_NEW | FA_CREATE_ALWAYS | FA_OPEN_APPEND);

	fs_trace("f_open(%p, \"%s\", %d)\n", fp, fullpath.c_str(), mode);

	std::string posixmode = mode == (FA_READ)								? "r" :
							mode == (FA_READ | FA_WRITE)					? "r+" :
							mode == (FA_CREATE_ALWAYS | FA_WRITE)			? "w" :
							mode == (FA_CREATE_ALWAYS | FA_WRITE | FA_READ) ? "w+" :
							mode == (FA_OPEN_APPEND | FA_WRITE)				? "a" :
							mode == (FA_OPEN_APPEND | FA_WRITE | FA_READ)	? "a+" :
							mode == (FA_CREATE_NEW | FA_WRITE)				? "wx" :
							mode == (FA_CREATE_NEW | FA_WRITE | FA_READ)	? "w+x" :
																			  "";

	fp->fil = std::fopen(path, posixmode.c_str());

	if (fp->fil == nullptr)
		return FR_NO_FILE;
	else
		return FR_OK;
}

FRESULT FS::f_close(File *fil) {
	fs_trace("f_close(%p)\n", fil);

	auto res = std::fclose(fil->fil);
	if (res == 0)
		return FR_OK;
	else
		return FR_DISK_ERR;
}

FRESULT FS::f_lseek(File *fil, uint64_t offset) {
	fs_trace("f_lseek(%p, %lld)\n", fil, offset);

	if (!fil)
		return FR_INVALID_PARAMETER;

	auto res = std::fseek(fil->fil, offset, SEEK_SET);

	return res == 0 ? FR_OK : FR_NO_FILE;
}

FRESULT FS::f_read(File *fil, void *buff, unsigned bytes_to_read, unsigned *br) {
	fs_trace("f_read(%p, %p, %u, ...)\n", fil, buff, bytes_to_read);

	auto res = std::fread(buff, 1, bytes_to_read, fil->fil);

	if (!fil || !buff)
		return FR_INVALID_PARAMETER;

	if (res == 0) {
		// TODO: determine error
		return FR_NO_FILE;
	} else {
		*br = res;
		return FR_OK;
	}
}

char *FS::f_gets(char *buffer, int len, File *fil) {
	fs_trace("f_gets(%p, %d, %p)\n", buffer, len, fil);

	if (!fil)
		return nullptr;

	return std::fgets(buffer, len, fil->fil);
}

FRESULT FS::f_stat(const char *path, Fileinfo *info) {
	if (info == nullptr)
		return FR_INVALID_PARAMETER;

	auto fullpath = impl->full_path(path);

	fs_trace("f_stat(%s, %p)\n", fullpath.c_str(), info);

	if (std::filesystem::is_regular_file(fullpath)) {
		info->dir_entry = true;
		info->name = path;
		return FR_OK;

	} else if (std::filesystem::is_directory(fullpath)) {
		info->dir_entry = false;
		info->name = path;
		return FR_OK;
	}

	info->name = "";
	return FR_NO_FILE;
}

// DIRS (READ-ONLY)

FRESULT FS::f_opendir(Dir *dir, const char *path) {
	auto fullpath = impl->full_path(path);

	fs_trace("f_opendir(%p, %s)\n", dir, fullpath.c_str());

	if (!dir)
		return FR_INVALID_PARAMETER;

	try {
		if (std::filesystem::is_directory(path)) {
			dir->path = path;
			dir->reset();
			return FR_OK;
		}
	} catch (std::exception &e) {
		//not an error
	}

	return FR_NO_PATH;
}

FRESULT FS::f_closedir(Dir *dir) {
	fs_trace("f_closedir(%p)\n", dir);

	if (dir)
		dir->reset();

	return FR_TIMEOUT;
}

FRESULT FS::f_readdir(Dir *dir, Fileinfo *info) {
	fs_trace("f_readdir(%p, %p)\n", dir, info);

	if (!info || !dir)
		return FR_INVALID_PARAMETER;

	try {
		// All entries read:
		if (dir->dir == std::filesystem::directory_iterator{}) {
			info->name = '\0';
			return FR_NO_FILE;
		}

		info->name = dir->dir->path();
		info->dir_entry = dir->dir->is_directory();

		dir->dir++;

		return FR_OK;
	} catch (std::exception &e) {
		return FR_NO_PATH;
	}
}

FRESULT FS::f_findfirst(Dir *dir, Fileinfo *info, const char *path, const char *pattern) {
	auto fullpath = impl->full_path(path);

	fs_trace("f_findfirst(%p, %p, %s, %s)\n", dir, info, fullpath.c_str(), pattern);

	// auto msg = IntercoreModuleFS::FindFirst{
	// 	.dir = *dir,
	// 	.info = *info,
	// 	.path = fullpath.c_str(),
	// 	.pattern = pattern,
	// };

	// if (auto response = impl->get_response_or_timeout<IntercoreModuleFS::FindFirst>(msg, 3000)) {
	// 	*dir = response->dir;
	// 	*info = response->info;
	// 	return response->res;
	// }

	return FR_TIMEOUT;
}

FRESULT FS::f_findnext(Dir *dir, Fileinfo *info) {
	fs_trace("f_findnext %p\n", dir);

	// auto msg = IntercoreModuleFS::FindNext{
	// 	.dir = *dir,
	// 	.info = *info,
	// };

	// if (auto response = impl->get_response_or_timeout<IntercoreModuleFS::FindNext>(msg, 3000)) {
	// 	*dir = response->dir;
	// 	*info = response->info;
	// 	return response->res;
	// }

	return FR_TIMEOUT;
}

// CREATE Dir

FRESULT FS::f_mkdir(const char *path) {
	auto fullpath = impl->full_path(path);

	fs_trace("f_mkdir(%s)\n", fullpath.c_str());

	// if (write_access) {
	// 	auto msg = IntercoreModuleFS::MkDir{
	// 		.path = fullpath.c_str(),
	// 	};

	// 	if (auto response = impl->get_response_or_timeout<IntercoreModuleFS::MkDir>(msg, 3000)) {
	// 		return response->res;
	// 	}
	// }

	return FR_TIMEOUT;
}

// WRITING

FRESULT FS::f_write(File *fp, const void *buff, unsigned btw, unsigned *bw) {
	if (write_access) {
		fs_trace("f_write(%p, ...)\n", fp);
	}
	return FR_INT_ERR;
}

FRESULT FS::f_sync(File *fp) {
	fs_trace("f_sync(%p)\n", fp);
	if (write_access) {
	}
	return FR_INT_ERR;
}

FRESULT FS::f_truncate(File *fp) {
	fs_trace("f_truncate(%p)\n", fp);
	if (write_access) {
	}
	return FR_INT_ERR;
}

int FS::f_putc(char c, File *fp) {
	char s[2]{c, 0};
	return f_puts(s, fp);
}

int FS::f_puts(const char *str, File *fp) {
	if (write_access) {
		fs_trace("f_puts(\"%s\", %p)\n", str, fp);
	}
	return FR_INT_ERR;
}

int FS::f_printf(File *fp, const char *fmt, ...) {
	constexpr int MaxStringSize = 1024;

	va_list args;
	va_start(args, fmt);
	char buf[1 + MaxStringSize];
	auto sz = vsnprintf(buf, sizeof buf, fmt, args);
	if (sz > MaxStringSize)
		fs_trace("Tructuting f_printf to %zu chars\n", MaxStringSize);
	va_end(args);

	return f_puts(buf, fp);
}

FRESULT FS::f_expand(File *fp, FSIZE_t fsz, uint8_t opt) {
	fs_trace("f_expand(%p...)\n", fp);
	if (write_access) {
	}
	return FR_INT_ERR;
}

// OTHER (write-access)

FRESULT FS::f_unlink(const char *path) {
	auto fullpath = impl->full_path(path);

	fs_trace("f_unlink(%s)\n", fullpath.c_str());

	if (write_access) {
	}
	return FR_INT_ERR;
}

FRESULT FS::f_rename(const char *path_old, const char *path_new) {
	auto fullpath_old = impl->full_path(path_old);
	auto fullpath_new = impl->full_path(path_new);

	fs_trace("f_rename(%s, %s)\n", path_old, path_new);
	if (write_access) {
	}
	return FR_INT_ERR;
}

FRESULT FS::f_utime(const char *path, const Fileinfo *fno) {
	auto fullpath = impl->full_path(path);

	fs_trace("f_utime(%s)\n", fullpath.c_str());

	if (write_access) {
	}
	return FR_INT_ERR;
}

// Working Dir:

FRESULT FS::f_chdir(const char *path) {
	fs_trace("f_chdir(%s)\n", path);

	//TODO: ensure ends in a slash
	impl->cwd = path;

	return FR_OK;
}

FRESULT FS::f_getcwd(char *buff, unsigned len) {
	fs_trace("f_getcwd()\n");

	if (buff == nullptr)
		return FR_INVALID_PARAMETER;

	auto &cwd = impl->cwd;
	auto sz = std::min<size_t>(len, cwd.size());
	std::copy(cwd.begin(), std::next(cwd.begin(), sz), buff);

	return FR_OK;
}

void FS::reset_dir(Dir *dp) {
	// dp->obj.fs = nullptr;
}

void FS::reset_file(File *fp) {
	// fp->obj.fs = nullptr;
	// fp->cltbl = nullptr;
}

bool FS::is_file_reset(File *fp) {
	// return fp->obj.fs == nullptr;
	return true;
}

bool FS::f_eof(File *fp) {
	// return fp->fptr == fp->obj.objsize;
	return true;
}

uint8_t FS::f_error(File *fp) {
	// return fp->err;
	return 0xFF;
}

FSIZE_t FS::f_tell(File *fp) {
	// return fp->fptr;
	return 0;
}

FSIZE_t FS::f_size(File *fp) {
	// return fp->obj.objsize;
	return 0;
}

FRESULT FS::f_rewind(File *fp) {
	// return this->f_lseek(fp, 0);
	return FR_INT_ERR;
}

FRESULT FS::f_rewinddir(Dir *dp) {
	// return this->f_readdir(dp, nullptr);
	return FR_INT_ERR;
}

FRESULT FS::f_rmdir(const char *path) {
	// return this->f_unlink(path);
	return FR_INT_ERR;
}

//FRESULT FS::f_chdrive(const char *path);
// FRESULT FS::f_getfree(const char *path, DWORD *nclst, FATFS **fatfs); /* Get number of free clusters on the drive */
// FRESULT FS::f_getlabel(const char *path, char *label, DWORD *vsn);   /* Get volume label */
// FRESULT FS::f_setlabel(const char *label);							   /* Set volume label */
// FRESULT FS::f_mount(FATFS *fs, const char *path, uint8_t opt); /* Mount/Unmount a logical drive */
// FRESULT FS::f_mkfs (const char* path, const MKFS_PARM* opt, void* work, unsigned len);	/* Create a FAT volume */
// FRESULT FS::f_fdisk(uint8_t pdrv, const LBA_t ptbl[], void *work); /* Divide a physical drive into some partitions */
// FRESULT FS::f_setcp(WORD cp);					  /* Set current code page */
// FRESULT FS::f_forward(FIL *fp, unsigned (*func)(const uint8_t *, unsigned), unsigned btf, unsigned *bf); /* Forward data to the stream */

} // namespace MetaModule
