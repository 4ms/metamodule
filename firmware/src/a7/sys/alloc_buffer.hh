#ifndef __SYS_ALLOC_BUFFER_HH
#define __SYS_ALLOC_BUFFER_HH

#include <cstddef>
template<typename T>
using BigAlloc = T;

struct BigHeapAllocation {};

struct BigAllocControl {
	static void reset()
	{
		// AllocForever<SDRAM_BASE_ADDR>::reset();
	}

	static size_t get_memory_usage()
	{
		return 0;
		// return AllocForever<SDRAM_BASE_ADDR>::get_memory_usage();
	}
};

#endif
