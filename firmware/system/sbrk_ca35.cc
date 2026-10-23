// The A35's heap for newlib malloc (MP2). A minimal version of firmware/system/sbrk.cc (which also
// shares the heap with the plugin arena). The M33 uses system/sbrk_mp2.cc.
//
// The heap is a region of DDR of its own, A35_HEAP_ADDR/SIZE (cmake/mp2.cmake). It's outside the
// DDR that TF-A opens to secure masters, so the first call here opens it to the A35 in the DDR
// firewall (RISAF4). If that's not possible (RISAF4 is locked), the heap is the rest of RAM
// instead (the .heap section in the linker script), which is much smaller.
//
// Like MP1's plugin arena slabs, a block can be claimed from the top of the heap region, out of
// malloc's reach until it's released (heap_claim_top()). Big, occasional blocks come from there,
// so they don't depend on finding a big enough hole in malloc's heap each time.
#include "drivers/risaf.hh"
#include <cerrno>
#include <cstddef>
#include <cstdint>
#include <malloc.h>

extern char _sheap;
extern char _eheap;

namespace
{
// RISAF4 region for the heap (see core_a35/main.cc for the others)
constexpr unsigned HeapRegionIndex = 9;

char *heap_start = nullptr; // set by init_heap()
char *heap_top = nullptr;	// end of the heap region
char *heap_end = nullptr;	// malloc's heap is heap_start to here
char *heap_limit = nullptr; // malloc's heap can grow up to here: above it is claimed

void init_heap() {
	if (heap_start)
		return;

	using namespace mdrivlib::RISAF;
	if (add_ddr_region(HeapRegionIndex, A35_HEAP_ADDR, A35_HEAP_ADDR + A35_HEAP_SIZE - 1, CID_A35, CID_A35, true)) {
		asm volatile("dsb sy" ::: "memory");
		heap_start = reinterpret_cast<char *>(A35_HEAP_ADDR);
		heap_top = heap_start + A35_HEAP_SIZE;
	} else {
		heap_start = &_sheap;
		heap_top = &_eheap;
	}

	heap_end = heap_start;
	heap_limit = heap_top;
}

// Locks out malloc (and so sbrk) on the other core, for claims from the top of the heap
struct HeapLock {
	HeapLock() {
		__malloc_lock(_REENT);
	}
	~HeapLock() {
		__malloc_unlock(_REENT);
	}
};
} // namespace

// Called by malloc, which holds its lock
extern "C" void *_sbrk(ptrdiff_t incr) {
	init_heap();

	char *prev_heap_end = heap_end;
	if (incr > (heap_limit - heap_end) || incr < (heap_start - heap_end)) {
		errno = ENOMEM;
		return reinterpret_cast<void *>(-1);
	}

	heap_end += incr;
	return prev_heap_end;
}

size_t get_heap_size() {
	HeapLock lock;
	init_heap();
	return size_t(heap_end - heap_start);
}

uintptr_t heap_region_start() {
	HeapLock lock;
	init_heap();
	return reinterpret_cast<uintptr_t>(heap_start);
}

size_t heap_region_size() {
	HeapLock lock;
	init_heap();
	return size_t(heap_top - heap_start);
}

// Claim size bytes, aligned to align (a power of 2), at the top of the heap region. One claim at a
// time. Returns nullptr if malloc's heap already reaches into it.
void *heap_claim_top(size_t size, size_t align) {
	HeapLock lock;
	init_heap();

	if (heap_limit != heap_top)
		return nullptr;

	auto top = reinterpret_cast<uintptr_t>(heap_top);
	auto start = (top - size) & ~uintptr_t(align - 1);
	auto end = reinterpret_cast<uintptr_t>(heap_end);
	if (size > top - reinterpret_cast<uintptr_t>(heap_start) || start < end)
		return nullptr;

	heap_limit = reinterpret_cast<char *>(start);
	return heap_limit;
}

void heap_release_top(void *ptr) {
	HeapLock lock;
	if (ptr == heap_limit)
		heap_limit = heap_top;
}
