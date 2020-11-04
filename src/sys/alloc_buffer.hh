#pragma once
#include "interp_array.hh"

template<unsigned int ADDR>
struct AllocOnly {
	void *operator new(unsigned int size)
	{
		char *prev_end = alloc_ptr;
		alloc_ptr += size;
		return prev_end;
	}
private:
	static inline char *alloc_ptr = (char*)ADDR;
};

template<typename T, unsigned int Size>
struct AllocInterpArray : AllocOnly<0xC0000000>, public InterpArray<T, Size> {
};


template<typename T, unsigned int ADDR>
struct AllocAt : T, AllocOnly<ADDR> {
};

