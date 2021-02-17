#pragma once
#include <cstddef>

template<unsigned int BASEADDR>
struct AllocForever {
	void *operator new(size_t size)
	{
		char *prev_end = alloc_ptr;
		alloc_ptr += size;
		return prev_end;
	}
	void operator delete(void *v)
	{
		// nothing is ever deleted
	}
	static void reset()
	{
		alloc_ptr = (char *)BASEADDR;
	}

private:
	static inline char *alloc_ptr = (char *)BASEADDR;
};

template<typename T, unsigned int ADDR>
struct AllocAt : T, AllocForever<ADDR> {};

static const unsigned int SDRAM_BASE_ADDR = 0xC0000000;

template<typename T>
using BigAlloc = AllocAt<T, SDRAM_BASE_ADDR>;

