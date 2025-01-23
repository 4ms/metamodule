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

int _fstat(int x, void *p) {
	return 0;
}

int _isatty(int fd) {
	return 0;
}
