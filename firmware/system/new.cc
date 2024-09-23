#include <cstdlib>
#include <new>

#ifdef CPU_TEST_ALL_MODULES
#include "alloc_watch.hh"

AllocationWatch *watch = nullptr;
#endif

#ifdef __clang__
#define THROW_SPEC _THROW_BAD_ALLOC
#else
#define THROW_SPEC
#endif

void *operator new(size_t size) THROW_SPEC {
#ifdef CPU_TEST_ALL_MODULES
	auto ptr = malloc(size);
	if (watch)
		watch->register_alloc(size, ptr);
	return ptr;
#else
	return malloc(size);
#endif
}

void operator delete(void *p) noexcept {
#ifdef CPU_TEST_ALL_MODULES
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
	return operator new(size);
}

void *operator new(size_t size, std::align_val_t align) {
	return operator new(size);
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
	return operator new(size);
}

void operator delete[](void *p, std::nothrow_t) noexcept {
	operator delete(p);
}
