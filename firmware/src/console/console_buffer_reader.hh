#pragma once
#include "console/concurrent_buffer.hh"
#include "util/term_codes.hh"
#include <algorithm>
#include <array>
#include <cstring>
#include <span>
#include <string_view>

namespace MetaModule
{

// Keeps a read position per buffer and copies out contiguous chunks, optionally
// wrapping each chunk in a per-core terminal color. Only one reader may be actively
// draining the buffers at a time: the UART drain by default, or the USB CDC console
// while a host is connected (see console_routing.hh).
class ConsoleBufferReader {
public:
	static constexpr size_t NumBuffers = 3;

	ConsoleBufferReader(std::array<ConcurrentBuffer *, NumBuffers> buffers)
		: buffers{buffers} {
	}

	// Drop any pending backlog: continue from each buffer's current position.
	// Call when switching UART<->USB CDC
	void resync() {
		for (auto i = 0u; i < NumBuffers; i++) {
			read_pos[i] = buffers[i]->write_pos;
			buffers[i]->read_pos = read_pos[i];
		}
	}

	void set_color(bool enabled) {
		use_color = enabled;
	}

	// Copy the next pending chunk from one of the buffers into `out`
	// Returns the number of bytes written.
	size_t next_chunk(std::span<uint8_t> out) {
		for (auto scan = 0u; scan < NumBuffers; scan++) {
			auto i = next_idx;
			next_idx = (next_idx + 1) % NumBuffers;

			auto payload = out;
			size_t prefix_len = 0, suffix_len = 0;
			if (use_color) {
				prefix_len = strlen(core_colors[i]);
				suffix_len = strlen(Term::Normal);
				if (out.size() <= prefix_len + suffix_len)
					return 0;
				payload = out.subspan(prefix_len, out.size() - prefix_len - suffix_len);
			}

			auto len = read_from(i, payload);
			if (len == 0)
				continue;

			if (use_color) {
				memcpy(out.data(), core_colors[i], prefix_len);
				memcpy(out.data() + prefix_len + len, Term::Normal, suffix_len);
				return prefix_len + len + suffix_len;
			}
			return len;
		}
		return 0;
	}

private:
	// Copy pending bytes from buffer i into `out`, returning the count (0 = no data)
	size_t read_from(unsigned i, std::span<uint8_t> out) {
		auto &buf = *buffers[i];
		const uint32_t start = read_pos[i];

		const uint32_t wpos = buf.write_pos;
		ConcurrentBuffer::barrier(); // load write_pos before loading the data it covers

		const uint32_t avail = wpos - start;
		if (avail == 0)
			return 0;

		if (avail > ConcurrentBuffer::Size) {
			// Writer lapped us (we stalled, or output came way too fast): the
			// backlog is partly overwritten, so drop it all and say so
			read_pos[i] = wpos;
			buf.read_pos = wpos;
			constexpr std::string_view msg = "\n<console overrun>\n";
			auto n = std::min(msg.size(), out.size());
			memcpy(out.data(), msg.data(), n);
			return n;
		}

		const uint32_t offset = start & (ConcurrentBuffer::Size - 1);
		auto n = std::min<uint32_t>({avail, (uint32_t)out.size(), ConcurrentBuffer::Size - offset});
		memcpy(out.data(), &buf.buffer.data[offset], n);

		ConcurrentBuffer::barrier(); // finish copying before re-checking write_pos
		if (buf.write_pos - start > ConcurrentBuffer::Size) {
			// Writer wrapped into the region while we were copying: data is torn
			read_pos[i] = buf.write_pos;
			buf.read_pos = read_pos[i];
			return 0;
		}

		// Prefer ending a chunk at a line boundary, so that when chunks from
		// different cores interleave, they don't splice mid-line. If the chunk
		// has no newline at all (a partial or extra-long line), emit it as-is.
		if (out[n - 1] != '\n') {
			auto k = n;
			while (k > 0 && out[k - 1] != '\n')
				k--;
			if (k > 0)
				n = k;
		}

		read_pos[i] = start + n;
		buf.read_pos = read_pos[i]; // let writers see our progress (backpressure)
		return n;
	}

	std::array<ConcurrentBuffer *, NumBuffers> buffers;
	std::array<uint32_t, NumBuffers> read_pos{};
	unsigned next_idx = 0;
	bool use_color = false;

	// Buffer index -> color: A7 core 0, A7 core 1, M4
	static constexpr std::array<const char *, NumBuffers> core_colors{Term::Blue, Term::Green, Term::Yellow};
};

} // namespace MetaModule
