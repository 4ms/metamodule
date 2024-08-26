#pragma once
#include "circular_buffer.hh"
#include <cstdint>

namespace SamplerKit
{
struct Cache {
	// file position address that corresponds to lowest position in file that's cached
	uint32_t low;

	// file position address that corresponds to highest position in file that's cached
	uint32_t high;

	// size in bytes of the cache (should always equal play_buff[]->size / 2 * sampleByteSize)
	uint32_t size;

	// address in play_buff[] that corresponds to cache.low
	uint32_t map_pt;

	//
	// Given: the starting address of the cache, and the address in the buffer to which it refers.
	// Returns: a cache address equivalent to the buffer_point
	// Assumes cache_start is the lowest value of the cache
	//

	uint32_t map_buffer_to_cache(uint32_t buffer_point, uint8_t sampleByteSize, CircularBuffer *b) const {

		// Find out how far ahead the buffer_point is from the buffer reference
		uint32_t p = b->distance_points(buffer_point, map_pt, b->size, 0);

		// Divide that by 2 to get the number of samples
		// and multiply by the sampleByteSize to get the position in the cache
		p = (p * sampleByteSize) >> 1;

		// add that to the cache reference
		p += low;

		return p;
	}

	//
	// Given: the starting address of the cache, and the address in the buffer to which it refers.
	// Returns: a buffer address equivalent to cache_point
	// Assumes cache_start is the lowest value of the cache
	//

	uint32_t map_cache_to_buffer(uint32_t cache_point, uint8_t sampleByteSize, CircularBuffer *b) const {
		if (cache_point < low)
			return b->min; // error condition

		// Find how far ahead the cache_point is from the start of the cache
		uint32_t p = cache_point - low;

		// Find how many samples that is
		p = p / sampleByteSize;

		// Multiply that by 2 to get the address offset in b
		p *= 2;

		// Add the offset to the start of the buffer
		p += map_pt;

		// Shorter way to write it is this:
		// p = buffer_start + (((cache_point - cache_start) * 2) / sampleByteSize);

		// Wrap the circular buffer
		while (p > b->max)
			p -= b->size;

		return p;
	}

	/////////////////// DELETE:
	static uint32_t STS_map_buffer_to_cache(
		uint32_t buffer_point, uint8_t sampleByteSize, uint32_t cache_start, uint32_t buffer_start, CircularBuffer *b) {

		// Find out how far ahead the buffer_point is from the buffer reference
		uint32_t p = b->distance_points(buffer_point, buffer_start, b->size, 0);

		// Divide that by 2 to get the number of samples
		// and multiply by the sampleByteSize to get the position in the cache
		p = (p * sampleByteSize) >> 1;

		// add that to the cache reference
		p += cache_start;

		return p;
	}
	static uint32_t STS_map_cache_to_buffer(
		uint32_t cache_point, uint8_t sampleByteSize, uint32_t cache_start, uint32_t buffer_start, CircularBuffer *b) {

		if (cache_point < cache_start)
			return b->min; // error condition

		// Find how far ahead the cache_point is from the start of the cache
		uint32_t p = cache_point - cache_start;

		// Find how many samples that is
		p = p / sampleByteSize;

		// Multiply that by 2 to get the address offset in b
		p *= 2;

		// Add the offset to the start of the buffer
		p += buffer_start;

		// Shorter way to write it is this:
		// p = buffer_start + (((cache_point - cache_start) * 2) / sampleByteSize);

		// Wrap the circular buffer
		while (p > b->max)
			p -= b->size;

		return p;
	}
};

} // namespace SamplerKit
