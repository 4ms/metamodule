#ifndef __SYS_ALLOC_BUFFER_HH
#define __SYS_ALLOC_BUFFER_HH
#include <cstddef>

template<typename T>
using BigAlloc = T;

struct BigAllocControl {
	static size_t get_memory_usage()
	{
		return 0;
	}
	static void reset() {}
};

struct BigHeapAllocation {};

#endif
