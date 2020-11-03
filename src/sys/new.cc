#include <cstdlib>
#include <new>

void *operator new(size_t size) noexcept
{
	return malloc(size);
}

void operator delete(void *p) noexcept
{
	free(p);
}

void *operator new[](size_t size) noexcept
{
	return operator new(size); // Same as regular new
}

void operator delete[](void *p) noexcept
{
	operator delete(p); // Same as regular delete
}

void *operator new(size_t size, std::nothrow_t) noexcept
{
	return operator new(size); // Same as regular new
}

void operator delete(void *p, std::nothrow_t) noexcept
{
	operator delete(p); // Same as regular delete
}

void *operator new[](size_t size, std::nothrow_t) noexcept
{
	return operator new(size); // Same as regular new
}

void operator delete[](void *p, std::nothrow_t) noexcept
{
	operator delete(p); // Same as regular delete
}

extern "C" size_t _sbrk(int incr)
{
	while (1) {
		;
		//force infinite loop
	}
	extern char _fmc_start; // Defined by the linker
	// extern char _end; // Defined by the linker
	static char *heap_end;
	char *prev_heap_end;

	if (heap_end == 0) {
		heap_end = &_fmc_start;
		//heap_end = (char *)(0x20014000);
		// heap_end = &_end;
	}
	prev_heap_end = heap_end;
	// if (heap_end + incr > stack_ptr) {
	// 	write(1, "Heap and stack collision\n", 25);
	// 	abort();
	// }

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
} // namespace std
