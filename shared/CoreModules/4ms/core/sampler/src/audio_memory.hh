#pragma once
#include "audio_stream_conf.hh"
#include "conf/board_conf.hh"

namespace SamplerKit
{

struct Memory {

	static void clear() {
		uint32_t i;
		for (i = Brain::MemoryStartAddr; i < Brain::MemoryEndAddr; i += 4)
			*((uint32_t *)i) = 0x00000000;
	}

	static void wait_until_ready() {
		//
	}
};
} // namespace SamplerKit
