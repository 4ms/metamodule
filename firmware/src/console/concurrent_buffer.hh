#pragma once

#include "util/circular_buffer_block.hh"
#include <atomic>
#include <span>

struct ConcurrentBuffer {
	std::atomic<int> writer_ref_count{};
	std::atomic<int> current_write_pos{};
	CircularBufferBlock<uint8_t, 256 * 1024> buffer{};
};
