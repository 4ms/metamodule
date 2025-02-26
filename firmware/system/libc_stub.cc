#include <stdio.h>

namespace MetaModule
{
namespace StaticBuffers
{
extern bool kill_signal;
}
} // namespace MetaModule

extern "C" {

__attribute__((used)) void _init(void) {
}

__attribute__((used)) void _fini(void) {
}

__attribute__((used)) void _exit(int x) {
	puts("_exit\n");
	while (1)
		;
}

__attribute__((used)) int _getpid() {
	return -1;
}

__attribute__((used)) int *__errno() {
	static int errno = 0;
	return &errno;
}

void *__dso_handle = (void *)&__dso_handle;
}
