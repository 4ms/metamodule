#include <cstdlib>
#include <new>

void *operator new(size_t size)
{
	return malloc(size);
}

void operator delete(void *p) noexcept
{
	free(p);
}

void *operator new[](size_t size)
{
	return operator new(size);
}

void operator delete[](void *p) noexcept
{
	operator delete(p);
}

void *operator new(size_t size, std::nothrow_t) noexcept
{
	return operator new(size);
}

void operator delete(void *p, std::nothrow_t) noexcept
{
	operator delete(p);
}

void operator delete(void *p, std::size_t) noexcept
{
	operator delete(p);
}

void *operator new[](size_t size, std::nothrow_t) noexcept
{
	return operator new(size);
}

void operator delete[](void *p, std::nothrow_t) noexcept
{
	operator delete(p);
}

static char *heap_end;
extern char _sheap;

size_t get_heap_size()
{
	return reinterpret_cast<size_t>(heap_end) - reinterpret_cast<size_t>(&_sheap);
}

extern "C" size_t _sbrk(int incr)
{
	// Defined by the linker
	extern char _eheap;

	char *prev_heap_end;

	if (heap_end == 0) {
		heap_end = &_sheap;
	}
	prev_heap_end = heap_end;

	if (heap_end + incr > &_eheap) {
		// OOM!!!
		while (1)
			;
	}

	heap_end += incr;
	return (size_t)prev_heap_end;
}

namespace std
{
void __throw_bad_function_call()
{
	while (1)
		;
}
void __throw_bad_alloc()
{
	while (1)
		;
}
void __throw_length_error(char const *)
{
	while (1)
		;
}
} // namespace std
