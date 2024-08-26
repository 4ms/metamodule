#include "CoreModules/fs_access.hh"
#include "console/pr_dbg.hh"
#include "core_intercom/intercore_modulefs_message.hh"
#include "drivers/inter_core_comm.hh"
#include "fs_access_impl.hh"
#include "util/padded_aligned.hh"
#include <cstring>
#include <optional>
#include <string_view>

namespace MetaModule
{

namespace StaticBuffers
{
extern IntercoreModuleFS::Message icc_module_fs_message_core0;
extern IntercoreModuleFS::Message icc_module_fs_message_core1;
} // namespace StaticBuffers

FS::FS(std::string_view root)
	: impl{new Impl(root)} {
}

FS::~FS() = default;

FRESULT FS::f_open(FIL *fp, const TCHAR *path, BYTE mode) {
	std::string fullpath = impl->root + path;
	pr_dbg("f_open (%p, \"%s\", %d)\n", fp, fullpath.c_str(), mode);

	return impl->send_open_message(fp, fullpath, mode);
}

FRESULT FS::f_close(FIL *fp) {
	pr_dbg("f_close(%p)\n", fp);
	return impl->send_close_message(fp);
}

FRESULT FS::f_read(FIL *fp, void *buff, UINT btr, UINT *br) {
	pr_dbg("f_read(%p, %p, %u, ...)\n", fp, buff, btr);
	return impl->send_read_message(fp, (char *)buff, btr, br);
}

TCHAR *FS::f_gets(TCHAR *buff, int len, FIL *fp) {
	if (len < 0) {
		return nullptr;
	}
	pr_dbg("f_gets(%p, %d, %p)\n", buff, len, fp);
	return impl->send_gets_message(fp, std::span<char>(buff, (size_t)len));
}

FRESULT FS::f_lseek(FIL *fp, uint64_t ofs) {
	pr_dbg("f_lseek(%p, %llu)\n", fp, ofs);
	return impl->send_seek_message(fp, ofs);
}

FRESULT FS::f_write(FIL *fp, const void *buff, UINT btw, UINT *bw) {
	pr_dbg("f_write %p\n", fp);
	return FR_INT_ERR;
}

FRESULT FS::f_truncate(FIL *fp) {
	return FR_INT_ERR;
}

FRESULT FS::f_sync(FIL *fp) {
	pr_dbg("f_sync %p\n", fp);
	return FR_INT_ERR;
}

FRESULT FS::f_opendir(DIR *dp, const TCHAR *path) {
	pr_dbg("f_opendir %p %s\n", dp, path);
	return FR_INT_ERR;
}

FRESULT FS::f_closedir(DIR *dp) {
	pr_dbg("f_closedir %p\n", dp);
	return FR_INT_ERR;
}

FRESULT FS::f_readdir(DIR *dp, FILINFO *fno) {
	pr_dbg("f_readdir %p\n", dp);
	return FR_INT_ERR;
}

FRESULT FS::f_findfirst(DIR *dp, FILINFO *fno, const TCHAR *path, const TCHAR *pattern) {
	pr_dbg("f_findfirst %p %s %s\n", dp, path, pattern);
	return FR_INT_ERR;
}

FRESULT FS::f_findnext(DIR *dp, FILINFO *fno) {
	pr_dbg("f_findnext %p\n", dp);
	return FR_INT_ERR;
}

FRESULT FS::f_mkdir(const TCHAR *path) {
	pr_dbg("f_mkdir %s\n", path);
	return FR_INT_ERR;
}

FRESULT FS::f_unlink(const TCHAR *path) {
	return FR_INT_ERR;
}

FRESULT FS::f_rename(const TCHAR *path_old, const TCHAR *path_new) {
	return FR_INT_ERR;
}

FRESULT FS::f_stat(const TCHAR *path, FILINFO *fno) {
	pr_dbg("f_stat %s\n", path);
	return FR_INT_ERR;
}

FRESULT FS::f_utime(const TCHAR *path, const FILINFO *fno) {
	return FR_INT_ERR;
}

FRESULT FS::f_chdir(const TCHAR *path) {
	pr_dbg("f_chdir %s\n", path);
	return FR_INT_ERR;
}

FRESULT FS::f_getcwd(TCHAR *buff, UINT len) {
	return FR_INT_ERR;
}

FRESULT FS::f_expand(FIL *fp, FSIZE_t fsz, BYTE opt) {
	return FR_INT_ERR;
}

int FS::f_putc(TCHAR c, FIL *fp) {
	return FR_INT_ERR;
}

int FS::f_puts(const TCHAR *str, FIL *cp) {
	return FR_INT_ERR;
}

int FS::f_printf(FIL *fp, const TCHAR *str, ...) {
	return FR_INT_ERR;
}

//FRESULT FS::f_chdrive(const TCHAR *path);
// FRESULT FS::f_getfree(const TCHAR *path, DWORD *nclst, FATFS **fatfs); /* Get number of free clusters on the drive */
// FRESULT FS::f_getlabel(const TCHAR *path, TCHAR *label, DWORD *vsn);   /* Get volume label */
// FRESULT FS::f_setlabel(const TCHAR *label);							   /* Set volume label */
// FRESULT FS::f_mount(FATFS *fs, const TCHAR *path, BYTE opt); /* Mount/Unmount a logical drive */
// FRESULT FS::f_mkfs (const TCHAR* path, const MKFS_PARM* opt, void* work, UINT len);	/* Create a FAT volume */
// FRESULT FS::f_fdisk(BYTE pdrv, const LBA_t ptbl[], void *work); /* Divide a physical drive into some partitions */
// FRESULT FS::f_setcp(WORD cp);					  /* Set current code page */
// FRESULT FS::f_forward(FIL *fp, UINT (*func)(const BYTE *, UINT), UINT btf, UINT *bf); /* Forward data to the stream */

} // namespace MetaModule
