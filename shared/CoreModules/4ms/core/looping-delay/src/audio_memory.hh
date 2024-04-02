#pragma once
#include "conf/board_conf.hh"
#include "loop_util.hh"
#include <cstdint>
#include <cstring>

namespace LDKit
{

struct Memory {
	static void clear() {
		std::memset(reinterpret_cast<void *>(Brain::MemoryStartAddr), 0, Brain::MemorySizeBytes);
		// On F427: Takes 700ms to clear the channel buffer in 32-bit chunks, roughly 83ns per write
		// for (uint32_t i = Brain::MemoryStartAddr; i < Brain::MemoryEndAddr; i += 4)
		// 	*reinterpret_cast<uint32_t *>(i) = 0x00000000U;
	}
};
} // namespace LDKit
