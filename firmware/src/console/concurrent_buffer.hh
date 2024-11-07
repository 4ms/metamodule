#pragma once

#include "util/circular_buffer_block.hh"
#include <atomic>
#include <span>

struct ConcurrentBuffer {
	CircularBufferBlock<uint8_t, 256 * 1024> buffer{};
	int writer_ref_count{0};
	int current_write_pos{0};
};
