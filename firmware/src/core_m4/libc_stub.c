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

__attribute__((used)) int _fstat(int x, void *p) {
	return 0;
}

__attribute__((used)) int _isatty(int x) {
	return -1;
}

__attribute__((used)) int _kill(int x) {
	return -1;
}
