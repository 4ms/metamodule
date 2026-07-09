#include "alloc_diag.hh"
#include <cstdlib>
#include <new>

#ifdef MM_LOADTEST_MEASURE_MEMORY
#include "alloc_watch.hh"

AllocationWatcher *watch = nullptr;
#endif

namespace
{

void *track(void *ptr, size_t size) {
#ifdef MM_LOADTEST_MEASURE_MEMORY
	if (watch && ptr)
		watch->register_alloc(size, ptr);
#endif
	return ptr;
}

// The throwing forms of operator new must never return nullptr: with exceptions
// disabled, callers (including everything in libstdc++) do not check, and the
// resulting crash lands far from the cause. Report and halt at the point of
// failure instead. The std::nothrow forms are the explicit "I will check for
// nullptr" opt-in, so they keep honest failure semantics.
void *checked(void *ptr, size_t size, size_t align) {
	if (!ptr)
		MetaModule::alloc_failed(size, align);
	return ptr;
}

} // namespace

#ifdef __APPLE__
static void *aligned_malloc(size_t align, size_t size) {
	void *ptr = nullptr;
	if (posix_memalign(&ptr, align, size))
		return nullptr;
	return ptr;
}
#else
#include <malloc.h>
static void *aligned_malloc(size_t align, size_t size) {
	return memalign(align, size);
}
#endif

#ifdef __clang__
#define THROW_SPEC _THROW_BAD_ALLOC
#else
#define THROW_SPEC
#endif

void *operator new(size_t size) THROW_SPEC {
	return checked(track(malloc(size), size), size, alignof(std::max_align_t));
}

void operator delete(void *p) noexcept {
#ifdef MM_LOADTEST_MEASURE_MEMORY
	if (watch)
		watch->register_dealloc(p);
	free(p);
#else
	free(p);
#endif
}

void *operator new[](size_t size) {
	return operator new(size);
}

void operator delete[](void *p) noexcept {
	operator delete(p);
}

void *operator new(size_t size, std::nothrow_t) noexcept {
	return track(malloc(size), size);
}

// Over-aligned types (e.g. classes with NEON float32x4_t members) must get the
// alignment they ask for: malloc only guarantees 8 bytes, and a 16-byte-aligned
// NEON store to an 8-byte-aligned object raises a Data Abort.
// Blocks from memalign/posix_memalign are valid to pass to free().
void *operator new(size_t size, std::align_val_t align) {
	auto al = static_cast<size_t>(align);
	return checked(track(aligned_malloc(al, size), size), size, al);
}

void *operator new[](size_t size, std::align_val_t align) {
	return operator new(size, align);
}

void operator delete(void *p, std::align_val_t) noexcept {
	operator delete(p);
}

void operator delete[](void *p, std::align_val_t) noexcept {
	operator delete(p);
}

void operator delete(void *p, std::nothrow_t) noexcept {
	operator delete(p);
}

void operator delete(void *p, std::size_t) noexcept {
	operator delete(p);
}

void operator delete(void *p, std::size_t, std::align_val_t) noexcept {
	operator delete(p);
}

void *operator new[](size_t size, std::nothrow_t) noexcept {
	return track(malloc(size), size);
}

void operator delete[](void *p, std::nothrow_t) noexcept {
	operator delete(p);
}
