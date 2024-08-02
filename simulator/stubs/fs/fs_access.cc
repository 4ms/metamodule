#include "CoreModules/fs_access.hh"
#include "fs/fs_access_impl.hh"
#include <array>
#include <cstdarg>
#include <cstring>
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
		impl->cwd = "./";

		File file;
		auto res = f_open(&file, path.data(), FA_READ);
		auto res2 = f_close(&file);
		if (res == FR_OK && res2 == FR_OK) {
			printf("Found valid root %s\n", root.data());
			//keep the root, restore cwd
			impl->cwd = t_cwd;
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

	// auto msg = IntercoreModuleFS::Seek{
	// 	.fil = *fil,
	// 	.file_offset = offset,
	// };

	// if (auto response = impl->get_response_or_timeout<IntercoreModuleFS::Seek>(msg, 3000)) {
	// 	*fil = response->fil; //copy File back
	// 	return response->res;
	// }

	return FR_TIMEOUT;
}

FRESULT FS::f_read(File *fil, void *buff, unsigned bytes_to_read, unsigned *br) {
	fs_trace("f_read(%p, %p, %u, ...)\n", fil, buff, bytes_to_read);

	// if (bytes_to_read > impl->file_buffer.size()) {
	// 	pr_err("Cannot f_read %d bytes\n", bytes_to_read);
	// 	return FR_NOT_ENOUGH_CORE;
	// }

	// auto msg = IntercoreModuleFS::Read{
	// 	.fil = *fil,
	// 	.buffer = impl->file_buffer.subspan(0, bytes_to_read),
	// };

	// if (auto response = impl->get_response_or_timeout<IntercoreModuleFS::Read>(msg, 3000)) {
	// 	*fil = response->fil;
	// 	*br = response->bytes_read;
	// 	std::copy(response->buffer.begin(), std::next(response->buffer.begin(), response->bytes_read), (char *)buff);

	// 	return FR_OK;
	// }
	return FR_TIMEOUT;
}

char *FS::f_gets(char *buffer, int len, File *fil) {
	fs_trace("f_gets(%p, %d, %p)\n", buffer, len, fil);

	// if ((size_t)len > impl->file_buffer.size()) {
	// 	pr_err("Cannot f_gets %d bytes\n", len);
	// 	return nullptr;
	// }

	// auto msg = IntercoreModuleFS::GetS{
	// 	.fil = *fil,
	// 	.buffer = impl->file_buffer.subspan(0, len),
	// };

	// auto response = impl->get_response_or_timeout<IntercoreModuleFS::GetS>(msg, 3000);
	// if (response) {
	// 	*fil = response->fil;
	// 	// copy buffer until we hit a \0
	// 	std::strcpy(buffer, response->buffer.data());
	// 	return msg.res;
	// }
	return nullptr;
}

FRESULT FS::f_stat(const char *path, Fileinfo *info) {
	auto fullpath = impl->full_path(path);

	fs_trace("f_stat(%s, %p)\n", fullpath.c_str(), info);

	// auto msg = IntercoreModuleFS::Stat{
	// 	.path = fullpath.c_str(),
	// 	// .info = *info, //will be overwritten TODO: check
	// };

	// if (auto response = impl->get_response_or_timeout<IntercoreModuleFS::Stat>(msg, 3000)) {
	// 	*info = response->info;
	// 	return response->res;
	// }

	return FR_TIMEOUT;
}

// DIRS (READ-ONLY)

FRESULT FS::f_opendir(Dir *dir, const char *path) {
	auto fullpath = impl->full_path(path);

	fs_trace("f_opendir(%p, %s)\n", dir, fullpath.c_str());

	// auto msg = IntercoreModuleFS::OpenDir{
	// 	.dir = *dir,
	// 	.path = fullpath.c_str(),
	// };

	// if (auto response = impl->get_response_or_timeout<IntercoreModuleFS::OpenDir>(msg, 3000)) {
	// 	*dir = response->dir;
	// 	return response->res;
	// }

	return FR_TIMEOUT;
}

FRESULT FS::f_closedir(Dir *dir) {
	fs_trace("f_closedir(%p)\n", dir);

	// auto msg = IntercoreModuleFS::CloseDir{
	// 	.dir = *dir,
	// };

	// if (auto response = impl->get_response_or_timeout<IntercoreModuleFS::CloseDir>(msg, 3000)) {
	// 	*dir = response->dir;
	// 	return response->res;
	// }

	return FR_TIMEOUT;
}

FRESULT FS::f_readdir(Dir *dir, Fileinfo *info) {
	fs_trace("f_readdir(%p, %p)\n", dir, info);
	// auto msg = IntercoreModuleFS::ReadDir{
	// 	.dir = *dir,
	// 	.info = *info,
	// };

	// if (auto response = impl->get_response_or_timeout<IntercoreModuleFS::ReadDir>(msg, 3000)) {
	// 	*dir = response->dir;
	// 	*info = response->info;
	// 	return response->res;
	// }

	return FR_TIMEOUT;
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
