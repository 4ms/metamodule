#pragma once

#include "util/circular_buffer_block.hh"
#include <atomic>
#include <cstdint>
#include <span>

// Per-core console log buffer, living in shared, non-cached memory (.consolebuf).
// Written by the core that owns it, read by the M4 which writes to UART or USB CDC.
//
// Note: no read-modify-write atomics (LDREX/STREX) in this struct. On the A7,
// exclusives to non-cacheable memory need a global exclusive monitor in the
// interconnect, which the STM32MP15 does not have and the M4 does not go through the MMU.
// Plain aligned 32-bit loads/stores are single-copy atomic on both cores,
// so SPSC + explicit barriers is enough.
struct ConcurrentBuffer {
	static constexpr uint32_t Size = 256 * 1024;

	CircularBufferBlock<uint8_t, Size> buffer{};
	std::atomic<uint32_t> write_pos{0};
	std::atomic<uint32_t> read_pos{0};

	static void barrier() {
#if defined(CORE_CA7) || defined(CORE_CM4)
		// Full-system barrier ("dmb sy") is required (not "dmb ish" which is only for
		// inner-shareable i.e. not the M4).
		asm volatile("dmb sy" ::: "memory");
#else
		// Host builds (tests/simulator)
		std::atomic_thread_fence(std::memory_order_seq_cst);
#endif
	}

	// Copy data into the ring at pos without publishing it. Re-entrant: callers
	// writing to non-overlapping regions can safely interrupt each other.
	void copy_in(std::span<const uint8_t> data, uint32_t pos) {
		buffer.write(data, pos);
	}

	void copy_in(std::span<const char> data, uint32_t pos) {
		copy_in({reinterpret_cast<const uint8_t *>(data.data()), data.size()}, pos);
	}

	// Make everything up to pos visible to the reader
	void publish(uint32_t pos) {
		barrier(); // data must be visible before the new write_pos is
		write_pos = pos;
	}
};
