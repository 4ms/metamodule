#pragma once
#include <cstdint>

extern char *_params_ptr;

class SharedMemeory {
	template<typename T>
	void write_address_of(T object, uint32_t offset)
	{
		uint32_t *loc_ptr = reinterpret_cast<uint32_t *>(&_params_ptr);
		*(loc_ptr + offset) = reinterpret_cast<uint32_t>(&object);
	}

	static constexpr uint32_t ParamsPtrLocation = 0;
};
