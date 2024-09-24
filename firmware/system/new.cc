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

void *operator new(size_t size, std::align_val_t align)
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

void operator delete(void *p, std::size_t, std::align_val_t) noexcept
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
