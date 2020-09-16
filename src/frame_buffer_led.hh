#pragma once
#include <cstdint>

class FrameBufferLED {
public:
	FrameBufferLED(uint32_t *frame_buffer_element)
		: buffer(frame_buffer_element)
	{}
	void set(uint32_t val) const
	{
		*buffer = val << 16;
	}

private:
	uint32_t *buffer;
};
