#include <cstdio>

static char *heap_end = nullptr;
// Defined by the linker
extern char _sheap;

size_t get_heap_size() {
	return reinterpret_cast<size_t>(heap_end) - reinterpret_cast<size_t>(&_sheap);
}

extern "C" size_t _sbrk(int incr) {
	// Defined by the linker
	extern char _eheap;

	char *prev_heap_end;

	if (heap_end == nullptr) {
		heap_end = &_sheap;
	}
	prev_heap_end = heap_end;

	if (heap_end + incr > &_eheap) {
		printf("Out of memory\n");
		return 0;
		// OOM!!!
		// while (true)
		// 	;
	}

	heap_end += incr;
	return (size_t)prev_heap_end;
}
