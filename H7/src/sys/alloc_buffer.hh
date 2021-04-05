#ifndef __SYS_ALLOC_BUFFER_HH
#define __SYS_ALLOC_BUFFER_HH

#include <cstddef>

// namespace MetaModule
// {

constexpr size_t SDRAM_BASE_ADDR = 0xC0000000;
template<size_t BASEADDR>
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

	static size_t get_memory_usage()
	{
		return reinterpret_cast<size_t>(alloc_ptr) - SDRAM_BASE_ADDR;
	}

private:
	static inline char *alloc_ptr = (char *)BASEADDR;
};

template<typename T, size_t ADDR>
struct AllocAt : T, AllocForever<ADDR> {};

// These are exported:

template<typename T>
using BigAlloc = AllocAt<T, SDRAM_BASE_ADDR>;

struct BigAllocControl {
	static void reset()
	{
		AllocForever<SDRAM_BASE_ADDR>::reset();
	}

	static size_t get_memory_usage()
	{
		return AllocForever<SDRAM_BASE_ADDR>::get_memory_usage();
	}
};

using BigHeapAllocation = AllocForever<SDRAM_BASE_ADDR>;

// } // namespace MetaModule
#endif
