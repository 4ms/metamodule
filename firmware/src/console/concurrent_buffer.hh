#pragma once

#include "util/circular_buffer_block.hh"
#include <atomic>
#include <span>

struct ConcurrentBuffer {
	// std::atomic<int> writer_ref_count{};
	// std::atomic<int> current_write_pos{};
	int writer_ref_count{0};
	int current_write_pos{0};
	CircularBufferBlock<uint8_t, 256 * 1024> buffer{};
};
