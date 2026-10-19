// Minimal newlib syscalls for printf() to the console (_write is in src/core_a35/console.cc).
// There's no file I/O through libc: files go through FatFS (and on the M33, PatchStorage).
#include <errno.h>
#include <sys/stat.h>

int _close(int fd) {
	(void)fd;
	errno = EBADF;
	return -1;
}

int _fstat(int fd, struct stat *st) {
	(void)fd;
	st->st_mode = S_IFCHR;
	return 0;
}

int _isatty(int fd) {
	(void)fd;
	return 1;
}

int _lseek(int fd, int offset, int whence) {
	(void)fd;
	(void)offset;
	(void)whence;
	errno = ESPIPE;
	return -1;
}

int _read(int fd, char *ptr, int len) {
	(void)fd;
	(void)ptr;
	(void)len;
	errno = EBADF;
	return -1;
}

