#pragma once
#include "console/concurrent_buffer.hh"
#include <algorithm>
#include <atomic>
#include <cstddef>
#include <cstdint>

namespace MetaModule
{

// Writes one core's console output into its ConcurrentBuffer: MP1's UartLog::write_buffered()
// (console/uart_log.cc), for MP2's cores. IrqGuard masks the core's interrupts while it exists.
//
// All of a core's writers (main loop, interrupts) are nested, never concurrent, so interrupts are
// only masked to reserve the bytes and to publish them, not during the copy. Only the outermost
// write publishes, which publishes the nested writes' bytes too.
//
// Not shared between cores. Aligned to cache lines, so two cores' writers don't share one.
template<typename IrqGuard>
class alignas(64) ConsoleBufferWriter {
public:
	void attach(ConcurrentBuffer *buffer) {
		reserve_pos = buffer->write_pos.load();
		depth = 0;
		buff = buffer;
	}

	void detach() {
		buff = nullptr;
	}

	bool attached() const {
		return buff != nullptr;
	}

	// may_wait: a write from outside any interrupt can wait for the reader to make room, a chunk at
	// a time, so a long one isn't overwritten. (Not on the core that runs the reader.)
	void write(const char *ptr, size_t len, bool may_wait) {
		if (may_wait && depth == 0) {
			constexpr size_t MaxChunk = ConcurrentBuffer::Size / 4;
			while (len > 0) {
				const auto chunk = std::min(len, MaxChunk);
				wait_for_space(chunk);
				write_reserved(ptr, chunk);
				ptr += chunk;
				len -= chunk;
			}
			return;
		}

		write_reserved(ptr, len);
	}

private:
	void write_reserved(const char *ptr, size_t len) {
		uint32_t start;
		{
			IrqGuard irqs;
			depth = depth + 1;
			start = reserve_pos;
			reserve_pos = start + len;
		}

		buff->copy_in({ptr, len}, start);

		IrqGuard irqs;
		if (depth == 1)
			buff->publish(reserve_pos);
		depth = depth - 1;
	}

	// Times out if the reader is hung
	void wait_for_space(uint32_t len) {
		uint32_t spins = 500'000'000;
		while ((reserve_pos - buff->read_pos) + len > ConcurrentBuffer::Size) {
			if (--spins == 0)
				return;
		}
	}

	ConcurrentBuffer *buff = nullptr;
	std::atomic<uint32_t> reserve_pos{0}; // next free byte; all of [write_pos, reserve_pos) is claimed
	std::atomic<uint32_t> depth{0};		  // how many writes on this core are in flight (nested)
};

} // namespace MetaModule
