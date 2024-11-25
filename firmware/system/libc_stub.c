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
void _fstat(int x, void *p) {
}
void _isatty() {
}
int *__errno() {
	static int errno = 0;
	return &errno;
}
