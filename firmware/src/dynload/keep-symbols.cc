#include "jansson.h"
#include <cmath>
#include <cstring>
#include <memory>

void __attribute__((optimize("-O0"))) keep_symbols() {
	// Force these symbols from libc and other libs
	// TODO: how to do this otherwise?
	// We can't link the plugin to libc unless we compile a libc with it, since the arm-none-eabi libc
	// was not compiled with -fPIC
	// - Linker KEEP()?
	// - build libc with the plugin, mabye musl libc?
	// - build plugin with json library
	exp(0.5f);
	expf(0.5f);
	fmod(0.5f, 1.f);
	sinf(0.5f);
	tanf(0.5f);
	tanh(0.5f);
	volatile auto keep = std::allocator<char>{}; //seems to do nothing
	volatile int x = strlen("ABCD");
	volatile auto savefunc = &json_object_set_new;
}
