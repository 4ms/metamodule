#pragma once
#include <cstddef>
#include <cstdint>

template<size_t SIZE_BYTES, size_t BLOCK_SIZE>
struct RamDisk {
	static constexpr uint32_t SizeBytes = SIZE_BYTES;
	static constexpr uint32_t BlockSize = BLOCK_SIZE;
	static constexpr uint32_t NumBlocks = SizeBytes / BlockSize;

	uint8_t virtdrive[SizeBytes];
};
