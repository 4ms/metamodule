// FIXME: MP1 has file access through libc (src/fs/syscall, src/fs/dirent), for plugins and some
// modules: files on the RamDisk directly, and on other volumes through the M4. Until that's ported
// to MP2, there are no files to open.
#include "filesystem/dirent.h"
#include <cerrno>
#include <sys/stat.h>

extern "C" int _open(const char *, int, int) {
	errno = ENOENT;
	return -1;
}

extern "C" int _stat(const char *, struct stat *) {
	errno = ENOENT;
	return -1;
}

DIR *opendir(const char *) {
	errno = ENOENT;
	return nullptr;
}

struct dirent *readdir(DIR *) {
	return nullptr;
}

int closedir(DIR *) {
	return -1;
}
