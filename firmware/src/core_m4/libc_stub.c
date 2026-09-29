#include <sys/stat.h>

int _open(const char *filename, int flags, int mode) {
	return -1;
}

int _close(int fd) {
	return -1;
}

int _lseek(int fd, int offset, int whenc) {
	return -1;
}

int _read(int fd, char *ptr, int len) {
	return -1;
}

// stdout must look like a tty so newlib line-buffers it (flushing each newline).
// Otherwise it gets fully buffered and printf() output is held back until 1kB accumulates
__attribute__((used)) int _fstat(int x, struct stat *st) {
	st->st_mode = S_IFCHR;
	return 0;
}

__attribute__((used)) int _isatty(int x) {
	return 1;
}
