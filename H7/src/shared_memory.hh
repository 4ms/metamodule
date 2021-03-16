#pragma once
#include <cstdint>

//Defined in linker script
extern char *_params_ptr;

struct SharedMemory {
	SharedMemory() = delete;

	template<typename T>
	static void write_address_of(T *object, uint32_t offset)
	{
		uint32_t *loc_ptr = reinterpret_cast<uint32_t *>(&_params_ptr);
		*(loc_ptr + offset) = reinterpret_cast<uint32_t>(object);
	}

	template<typename T>
	static T read_address_of(uint32_t offset)
	{
		uint32_t *loc_ptr = reinterpret_cast<uint32_t *>(&_params_ptr);
		return reinterpret_cast<T>(*(loc_ptr + offset));
	}

	static constexpr uint32_t ParamsPtrLocation = 0;
	static constexpr uint32_t LEDFrameBufferLocation = 1;
	static constexpr uint32_t ScreenFrameBufferLocation = 2;
};
