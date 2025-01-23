// #define GCC_OPTIMIZE_OFF __attribute__((optimize("-O0")))
#include <stdio.h>

__attribute__((used)) void _init(void) {
}

__attribute__((used)) void _fini(void) {
}

__attribute__((used)) void _exit(int x) {
	puts("_exit\n");
	while (1)
		;
}

__attribute__((used)) int _kill(int x) {
	puts("_kill\n");
	return -1;
}

__attribute__((used)) int _getpid() {
	return -1;
}

__attribute__((used)) int *__errno() {
	static int errno = 0;
	return &errno;
}

__attribute__((used)) int _fstat(int x, void *p) {
	return 0;
}

__attribute__((used)) int _isatty(int x) {
	return -1;
}

void *__dso_handle = (void *)&__dso_handle;
