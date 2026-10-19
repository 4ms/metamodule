// Heap for newlib malloc: grows from _sheap to _eheap (the .heap section in the linker script).
// A minimal version of firmware/system/sbrk.cc (which also shares the heap with the plugin arena).
#include <cerrno>
#include <cstddef>

extern char _sheap;
extern char _eheap;

static char *heap_end = nullptr;

extern "C" void *_sbrk(ptrdiff_t incr) {
	if (heap_end == nullptr)
		heap_end = &_sheap;

	char *prev_heap_end = heap_end;
	if (incr > (&_eheap - heap_end) || incr < (&_sheap - heap_end)) {
		errno = ENOMEM;
		return reinterpret_cast<void *>(-1);
	}

	heap_end += incr;
	return prev_heap_end;
}

size_t get_heap_size() {
	return size_t((heap_end ? heap_end : &_sheap) - &_sheap);
}
