// #define GCC_OPTIMIZE_OFF __attribute__((optimize("-O0")))
#include <stdio.h>

// Overridden by alloc_rescue.cc: if an OOM-rescue scope is armed for the
// current process (e.g. a plugin aborting during init), rolls back via
// longjmp instead of dying here. Weak no-op so other targets still link.
__attribute__((weak)) void mm_abort_rescue(void) {
}

__attribute__((used)) void _init(void) {
}

__attribute__((used)) void _fini(void) {
}

__attribute__((used)) void _exit(int x) {
	mm_abort_rescue();
	puts("_exit\n");
	while (1)
		;
}

__attribute__((used)) int _kill(int x) {
	mm_abort_rescue();
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

void *__dso_handle = (void *)&__dso_handle;
