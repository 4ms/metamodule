// Heap for newlib malloc: grows from _sheap to _eheap (the .heap section in the linker script).
// A minimal version of firmware/system/sbrk.cc (which also shares the heap with the plugin arena).
//
// Like MP1's plugin arena slabs, a block can be claimed from the top of the heap region, out of
// malloc's reach until it's released (heap_claim_top()). Big, occasional blocks come from there,
// so they don't depend on finding a big enough hole in malloc's heap each time.
#include <cerrno>
#include <cstddef>
#include <cstdint>

extern char _sheap;
extern char _eheap;

static char *heap_end = nullptr;
static char *heap_limit = &_eheap; // malloc's heap ends here: above it is claimed

extern "C" void *_sbrk(ptrdiff_t incr) {
	if (heap_end == nullptr)
		heap_end = &_sheap;

	char *prev_heap_end = heap_end;
	if (incr > (heap_limit - heap_end) || incr < (&_sheap - heap_end)) {
		errno = ENOMEM;
		return reinterpret_cast<void *>(-1);
	}

	heap_end += incr;
	return prev_heap_end;
}

size_t get_heap_size() {
	return size_t((heap_end ? heap_end : &_sheap) - &_sheap);
}

// Claim size bytes, aligned to align (a power of 2), at the top of the heap region. One claim at a
// time. Returns nullptr if malloc's heap already reaches into it.
void *heap_claim_top(size_t size, size_t align) {
	if (heap_limit != &_eheap)
		return nullptr;

	auto top = reinterpret_cast<uintptr_t>(&_eheap);
	auto start = (top - size) & ~uintptr_t(align - 1);
	auto end = reinterpret_cast<uintptr_t>(heap_end ? heap_end : &_sheap);
	if (size > top - reinterpret_cast<uintptr_t>(&_sheap) || start < end)
		return nullptr;

	heap_limit = reinterpret_cast<char *>(start);
	return heap_limit;
}

void heap_release_top(void *ptr) {
	if (ptr == heap_limit)
		heap_limit = &_eheap;
}
