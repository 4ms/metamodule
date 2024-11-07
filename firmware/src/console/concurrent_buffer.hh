#pragma once

#include "util/circular_buffer_block.hh"
#include <atomic>
#include <span>

struct ConcurrentBuffer {
	CircularBufferBlock<uint8_t, 256 * 1024> buffer{};
	int writer_ref_count{0};
	int current_write_pos{0};
	bool use_color = false;

	void write(std::span<const uint8_t> data) {
		auto start = current_write_pos;
		current_write_pos += data.size();
		buffer.write(data, start);
	}

	void write(std::span<const char> data) {
		write({(uint8_t *)data.data(), data.size()});
	}
};
