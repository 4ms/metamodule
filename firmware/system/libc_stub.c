// #define GCC_OPTIMIZE_OFF __attribute__((optimize("-O0")))

void _init(void) {
}
void _fini(void) {
}
void *__dso_handle = (void *)&__dso_handle;

void _exit(int x) {
	while (1)
		;
}

// GCC_OPTIMIZE_OFF
int _kill(int x, int y) {
	return 0;
}

int _getpid() {
	return -1;
}
int _fstat(int x, void *p) {
	return 0;
}
int _isatty(int x) {
	return -1;
}
int *__errno() {
	static int errno = 0;
	return &errno;
}
