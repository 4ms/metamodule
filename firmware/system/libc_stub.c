void _init(void) {
}
void _fini(void) {
}
void *__dso_handle = (void *)&__dso_handle;

void _exit(int x) {
	while (1)
		;
}
void _kill(int x) {
}
int _getpid() {
	return -1;
}
void _close(int x) {
}
void _fstat(int x, void *p) {
}
void _isatty() {
}
void _lseek() {
}
int _read(int file, char *ptr, int len) {
	return 0;
}
int *__errno() {
	static int errno = 0;
	return &errno;
}
int _open(const char *filename, int flags, int mode) {
	return 0;
}
