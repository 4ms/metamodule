#include "CoreModules/fatfs_adaptor.hh"
#include "console/pr_dbg.hh"
#include "core_intercom/intercore_modulefs_message.hh"
#include "drivers/inter_core_comm.hh"
#include "fs_proxy.hh"
#include "util/padded_aligned.hh"
#include <cstdarg>
#include <cstring>
#include <optional>
#include <string>
#include <string_view>

namespace MetaModule
{

namespace StaticBuffers
{
extern IntercoreModuleFS::Message icc_module_fs_message_core0;
extern IntercoreModuleFS::Message icc_module_fs_message_core1;
} // namespace StaticBuffers

namespace
{

static constexpr bool print_fs_calls = false;
static constexpr bool write_access = false;

void fs_trace(const char *str) {
	if constexpr (print_fs_calls)
		printf("%s", str);
}

void fs_trace(auto... args) {
	if constexpr (print_fs_calls)
		printf(args...);
}

} // namespace

FatFS::FatFS(std::string_view root)
	: impl{new FsProxy()}
	, root{}
	, cwd{} {
}

FatFS::~FatFS() = default;

std::array<std::string_view, 2> valid_roots{
	"0:/", //USB
	"1:/", //SD Card
};

// Tries to find the given path on mounted volumes
bool FatFS::find_valid_root(std::string_view path) {
	auto t_root = root;
	auto t_cwd = cwd;

	for (auto rt : valid_roots) {
		root = rt;
		cwd = "";

		bool is_valid_root = false;
		if (path == "") {
			// f_stat cannot open root dir, so we use f_opendir;
			Dir dir;

			auto res = f_opendir(&dir, path.data());
			is_valid_root = (res == FR_OK);
			f_closedir(&dir);
		} else {
			Fileinfo info{};
			auto res = f_stat(path.data(), &info);
			is_valid_root = (res == FR_OK);
		}

		if (is_valid_root) {
			cwd = path;
			pr_dbg("Found valid root '%s'\n", path.data());
			return true;
		}
	}

	// no valid root found. restore previous values
	root = t_root;
	cwd = t_cwd;
	pr_dbg("No valid root found\n");

	return false;
}

std::string FatFS::full_path(const char *path) {
	return root + cwd + path;
}

// READING

FRESULT FatFS::f_open(File *fp, const char *path, uint8_t mode) {
	auto fullpath = full_path(path);

	if (!write_access)
		mode &= ~(FA_WRITE | FA_CREATE_NEW | FA_CREATE_ALWAYS | FA_OPEN_APPEND);

	fs_trace("f_open(%p, '%s', %d)\n", &fp->fil, fullpath.c_str(), mode);

	auto msg = IntercoreModuleFS::Open{
		.fil = fp->fil,
		.path = std::string_view{fullpath},
		.access_mode = mode,
	};

	if (auto response = impl->get_response_or_timeout<IntercoreModuleFS::Open>(msg, 3000)) {
		fp->fil = response->fil; //copy FIL back
		return response->res;
	}

	return FR_TIMEOUT;
}

FRESULT FatFS::f_close(File *fil) {
	fs_trace("f_close(%p)\n", &fil->fil);

	auto msg = IntercoreModuleFS::Close{
		.fil = fil->fil,
	};

	if (auto response = impl->get_response_or_timeout<IntercoreModuleFS::Close>(msg, 3000)) {
		fil->fil = response->fil;
		return response->res;
	}

	return FR_TIMEOUT;
}

FRESULT FatFS::f_lseek(File *fil, uint64_t offset) {
	fs_trace("f_lseek(%p, %lld)\n", &fil->fil, offset);

	auto msg = IntercoreModuleFS::Seek{
		.fil = fil->fil,
		.file_offset = offset,
		.whence = IntercoreModuleFS::Seek::Whence::Beginning,
	};

	if (auto response = impl->get_response_or_timeout<IntercoreModuleFS::Seek>(msg, 3000)) {
		fil->fil = response->fil; //copy File back
		return response->res;
	}

	return FR_TIMEOUT;
}

FRESULT FatFS::f_read(File *fil, void *buff, unsigned bytes_to_read, unsigned *br) {
	fs_trace("f_read(%p, %p, %u, ...)\n", &fil->fil, buff, bytes_to_read);

	if (bytes_to_read > impl->file_buffer().size()) {
		pr_err("Cannot f_read %d bytes\n", bytes_to_read);
		return FR_NOT_ENOUGH_CORE;
	}

	auto msg = IntercoreModuleFS::Read{
		.fil = fil->fil,
		.buffer = impl->file_buffer().subspan(0, bytes_to_read),
	};

	if (auto response = impl->get_response_or_timeout<IntercoreModuleFS::Read>(msg, 3000)) {
		fil->fil = response->fil;
		*br = response->bytes_read;
		std::copy(response->buffer.begin(), std::next(response->buffer.begin(), response->bytes_read), (char *)buff);

		return FR_OK;
	}
	return FR_TIMEOUT;
}

char *FatFS::f_gets(char *buffer, int len, File *fil) {
	fs_trace("f_gets(%p, %d, %p)\n", buffer, len, &fil->fil);

	if ((size_t)len > impl->file_buffer().size()) {
		pr_err("Cannot f_gets %d bytes\n", len);
		return nullptr;
	}

	auto msg = IntercoreModuleFS::GetS{
		.fil = fil->fil,
		.buffer = impl->file_buffer().subspan(0, len),
	};

	auto response = impl->get_response_or_timeout<IntercoreModuleFS::GetS>(msg, 3000);
	if (response) {
		fil->fil = response->fil;
		// copy buffer until we hit a \0
		std::strcpy(buffer, response->buffer.data());
		return msg.res;
	}
	return nullptr;
}

FRESULT FatFS::f_stat(const char *path, Fileinfo *info) {
	auto fullpath = full_path(path);
	fs_trace("f_stat(%s, %p)\n", fullpath.c_str(), info);

	if (!info)
		return FR_INVALID_PARAMETER;

	auto msg = IntercoreModuleFS::Stat{
		.path = fullpath.c_str(),
		// .info = *info, //will be overwritten TODO: check
	};

	if (auto response = impl->get_response_or_timeout<IntercoreModuleFS::Stat>(msg, 3000)) {
		info->filinfo = response->info;
		return response->res;
	}

	return FR_TIMEOUT;
}

// DIRS (READ-ONLY)

FRESULT FatFS::f_opendir(Dir *dir, const char *path) {
	auto fullpath = full_path(path);

	fs_trace("f_opendir(%p, %s)\n", dir, fullpath.c_str());

	auto msg = IntercoreModuleFS::OpenDir{
		.dir = dir->dir,
		.path = fullpath.c_str(),
	};

	if (auto response = impl->get_response_or_timeout<IntercoreModuleFS::OpenDir>(msg, 3000)) {
		dir->dir = response->dir;
		return response->res;
	}

	return FR_TIMEOUT;
}

FRESULT FatFS::f_closedir(Dir *dir) {
	fs_trace("f_closedir(%p)\n", dir);

	auto msg = IntercoreModuleFS::CloseDir{
		.dir = dir->dir,
	};

	if (auto response = impl->get_response_or_timeout<IntercoreModuleFS::CloseDir>(msg, 3000)) {
		dir->dir = response->dir;
		return response->res;
	}

	return FR_TIMEOUT;
}

FRESULT FatFS::f_readdir(Dir *dir, Fileinfo *info) {
	fs_trace("f_readdir(%p, %p)\n", dir, info);
	auto msg = IntercoreModuleFS::ReadDir{
		.dir = dir->dir,
		.info = info->filinfo,
	};

	if (auto response = impl->get_response_or_timeout<IntercoreModuleFS::ReadDir>(msg, 3000)) {
		dir->dir = response->dir;
		info->filinfo = response->info;
		return response->res;
	}

	return FR_TIMEOUT;
}

FRESULT FatFS::f_findfirst(Dir *dir, Fileinfo *info, const char *path, const char *pattern) {
	auto fullpath = full_path(path);

	fs_trace("f_findfirst(%p, %p, %s, %s)\n", dir, info, fullpath.c_str(), pattern);

	auto msg = IntercoreModuleFS::FindFirst{
		.dir = dir->dir,
		.info = info->filinfo,
		.path = fullpath.c_str(),
		.pattern = pattern,
	};

	if (auto response = impl->get_response_or_timeout<IntercoreModuleFS::FindFirst>(msg, 3000)) {
		dir->dir = response->dir;
		info->filinfo = response->info;
		return response->res;
	}

	return FR_TIMEOUT;
}

FRESULT FatFS::f_findnext(Dir *dir, Fileinfo *info) {
	fs_trace("f_findnext %p\n", dir);

	auto msg = IntercoreModuleFS::FindNext{
		.dir = dir->dir,
		.info = info->filinfo,
	};

	if (auto response = impl->get_response_or_timeout<IntercoreModuleFS::FindNext>(msg, 3000)) {
		dir->dir = response->dir;
		info->filinfo = response->info;
		return response->res;
	}

	return FR_TIMEOUT;
}

// CREATE DIR

FRESULT FatFS::f_mkdir(const char *path) {
	auto fullpath = full_path(path);

	fs_trace("f_mkdir(%s)\n", fullpath.c_str());

	if (write_access) {
		auto msg = IntercoreModuleFS::MkDir{
			.path = fullpath.c_str(),
		};

		if (auto response = impl->get_response_or_timeout<IntercoreModuleFS::MkDir>(msg, 3000)) {
			return response->res;
		}
	}

	return FR_TIMEOUT;
}

// WRITING

FRESULT FatFS::f_write(File *fp, const void *buff, unsigned btw, unsigned *bw) {
	if (write_access) {
		fs_trace("f_write(%p, ...)\n", fp);
	}
	return FR_INT_ERR;
}

FRESULT FatFS::f_sync(File *fp) {
	fs_trace("f_sync(%p)\n", fp);
	if (write_access) {
	}
	return FR_INT_ERR;
}

FRESULT FatFS::f_truncate(File *fp) {
	fs_trace("f_truncate(%p)\n", fp);
	if (write_access) {
	}
	return FR_INT_ERR;
}

int FatFS::f_putc(char c, File *fp) {
	char s[2]{c, 0};
	return f_puts(s, fp);
}

int FatFS::f_puts(const char *str, File *fp) {
	if (write_access) {
		fs_trace("f_puts(\"%s\", %p)\n", str, fp);
	}
	return FR_INT_ERR;
}

int FatFS::f_printf(File *fp, const char *fmt, ...) {
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

FRESULT FatFS::f_expand(File *fp, uint64_t fsz, uint8_t opt) {
	fs_trace("f_expand(%p...)\n", fp);
	if (write_access) {
	}
	return FR_INT_ERR;
}

// OTHER (write-access)

FRESULT FatFS::f_unlink(const char *path) {
	auto fullpath = full_path(path);

	fs_trace("f_unlink(%s)\n", fullpath.c_str());

	if (write_access) {
	}
	return FR_INT_ERR;
}

FRESULT FatFS::f_rename(const char *path_old, const char *path_new) {
	auto fullpath_old = full_path(path_old);
	auto fullpath_new = full_path(path_new);

	fs_trace("f_rename(%s, %s)\n", path_old, path_new);
	if (write_access) {
	}
	return FR_INT_ERR;
}

FRESULT FatFS::f_utime(const char *path, const Fileinfo *fno) {
	auto fullpath = full_path(path);

	fs_trace("f_utime(%s)\n", fullpath.c_str());

	if (write_access) {
	}
	return FR_INT_ERR;
}

// Working Dir:

FRESULT FatFS::f_chdir(const char *path) {
	fs_trace("f_chdir(%s)\n", path);

	//TODO: ensure ends in a slash
	cwd = path;

	return FR_OK;
}

FRESULT FatFS::f_getcwd(char *buff, unsigned len) {
	fs_trace("f_getcwd()\n");

	if (buff == nullptr)
		return FR_INVALID_PARAMETER;

	auto sz = std::min(len, cwd.size());
	std::copy(cwd.begin(), std::next(cwd.begin(), sz), buff);

	return FR_OK;
}

void FatFS::reset_dir(Dir *dp) {
	dp->reset();
	// dp->dir.obj.fs = nullptr;
}

void FatFS::reset_file(File *fp) {
	fp->reset();
	// fp->fil.obj.fs = nullptr;
	// fp->fil.cltbl = nullptr;
}

bool FatFS::is_file_reset(File *fp) {
	return fp->is_reset();
	// return fp->fil.obj.fs == nullptr;
}

bool FatFS::is_dir_reset(Dir *dp) {
	return dp->is_reset();
	// return dp->dir.obj.fs == nullptr;
}

bool FatFS::f_eof(File *fp) {
	return fp->fil.fptr == fp->fil.obj.objsize;
}

uint8_t FatFS::f_error(File *fp) {
	return fp->fil.err;
}

uint64_t FatFS::f_tell(File *fp) {
	return fp->fil.fptr;
}

uint64_t FatFS::f_size(File *fp) {
	return fp->fil.obj.objsize;
}

FRESULT FatFS::f_rewind(File *fp) {
	return this->f_lseek(fp, 0);
}

FRESULT FatFS::f_rewinddir(Dir *dp) {
	return this->f_readdir(dp, nullptr);
}

FRESULT FatFS::f_rmdir(const char *path) {
	return this->f_unlink(path);
}

// Not supported:
//FRESULT FatFS::f_chdrive(const char *path);
// FRESULT FatFS::f_getfree(const char *path, DWORD *nclst, FATFS **fatfs); /* Get number of free clusters on the drive */
// FRESULT FatFS::f_getlabel(const char *path, char *label, DWORD *vsn);   /* Get volume label */
// FRESULT FatFS::f_setlabel(const char *label);							   /* Set volume label */
// FRESULT FatFS::f_mount(FATFS *fs, const char *path, uint8_t opt); /* Mount/Unmount a logical drive */
// FRESULT FatFS::f_mkfs (const char* path, const MKFS_PARM* opt, void* work, unsigned len);	/* Create a FAT volume */
// FRESULT FatFS::f_fdisk(uint8_t pdrv, const LBA_t ptbl[], void *work); /* Divide a physical drive into some partitions */
// FRESULT FatFS::f_setcp(WORD cp);					  /* Set current code page */
// FRESULT FatFS::f_forward(File *fp, unsigned (*func)(const uint8_t *, unsigned), unsigned btf, unsigned *bf); /* Forward data to the stream */

} // namespace MetaModule
