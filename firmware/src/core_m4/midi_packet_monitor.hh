#pragma once
#include "console/pr_dbg.hh"
#include "midi/usb_midi_packet_checker.hh"
#include <array>
#include <cstdint>

namespace MetaModule
{

#ifdef USB_MIDI_MONITOR

// Debug monitor for USB MIDI packet streams (enabled with the USB_MIDI_MONITOR
// cmake option; reports print at LOG_LEVEL TRACE or higher).
//
// log() is called from ISR context: it records the packet in a RAM ring and
// runs the SysEx framing checker -- it never prints (a blocking print in the
// 48kHz FrameRate ISR stalls the param-block walk and loses packets for real).
// print_report() is called from the main loop and prints a once-per-second
// summary when there was traffic, plus the packets surrounding the first
// error captured since the last report.
struct MidiPacketMonitor {
	static constexpr uint32_t ReportIntervalMs = 1000;
	static constexpr uint32_t RingSize = 64; // power of 2

	UsbMidiPacketChecker checker{};
	uint32_t transport_drops = 0; // transmit() returned false (caller increments)

	// Transport-level stats, filled by callers that see whole URBs/transfers
	uint32_t urbs = 0;
	uint32_t urb_bytes = 0;
	uint32_t urb_max_len = 0;
	uint32_t urb_zero_len = 0;
	uint32_t urb_ragged = 0; // length not a multiple of 4

	MidiPacketMonitor(const char *name)
		: name{name} {
	}

	// ISR context: record and check. No printing.
	void log(uint32_t raw) {
		ring[write_idx & (RingSize - 1)] = raw;
		write_idx++;

		auto errors_before = checker.total_errors();
		checker.check(raw);

		if (checker.total_errors() != errors_before && !snapshot_valid) {
			// Keep the ring contents around the first error until it's printed
			snapshot_len = write_idx < RingSize ? write_idx : RingSize;
			auto oldest = write_idx - snapshot_len;
			for (auto i = 0u; i < snapshot_len; i++)
				snapshot[i] = ring[(oldest + i) & (RingSize - 1)];
			snapshot_valid = true;
		}
	}

	// ISR context: record a marker word in the ring only (not checked, not
	// counted as a packet). Markers show up in error snapshots.
	void mark(uint32_t word) {
		ring[write_idx & (RingSize - 1)] = word;
		write_idx++;
	}

	// Record one URB/transfer and mark its boundary in the ring as
	// 0xEEnnnnnn (n = length in bytes), so error snapshots show where
	// transfers began relative to any lost packet.
	void add_urb(uint32_t len) {
		urbs++;
		urb_bytes += len;
		if (len > urb_max_len)
			urb_max_len = len;
		if (len == 0)
			urb_zero_len++;
		if (len % 4)
			urb_ragged++;
		mark(0xEE000000 | (len & 0x00FFFFFF));
	}

	// Main loop context only
	void print_report(uint32_t now_ms) {
		if (now_ms - last_report_ms < ReportIntervalMs)
			return;
		auto elapsed_ms = now_ms - last_report_ms;
		last_report_ms = now_ms;

		// Copy counters: log() may run while we read them
		auto c = checker;
		auto drops = transport_drops;
		auto cur_urbs = urbs;
		auto pkts = c.sysex_packets + c.other_packets + c.zero_packets;
		auto errors = c.total_errors() + drops;

		if (pkts == last_pkts && errors == last_errors && cur_urbs == last_urbs)
			return; // no traffic, no news

		pr_trace("[%s] %u pkt/s %u msg/s | total: %u pkts %u msgs | err: %u seq %u framing %u zero-pkt %u drop | %u non-sysex\n",
				 name,
				 (unsigned)((pkts - last_pkts) * 1000 / elapsed_ms),
				 (unsigned)((c.messages - last_msgs) * 1000 / elapsed_ms),
				 (unsigned)pkts,
				 (unsigned)c.messages,
				 (unsigned)c.seq_errors,
				 (unsigned)c.framing_errors,
				 (unsigned)c.zero_packets,
				 (unsigned)drops,
				 (unsigned)c.other_packets);

		if (cur_urbs != last_urbs) {
			auto n_urbs = cur_urbs - last_urbs;
			pr_trace("[%s] %u urb/s avg %u B | total %u urbs %u B | max %u B, %u zero-len, %u ragged\n",
					 name,
					 (unsigned)(n_urbs * 1000 / elapsed_ms),
					 (unsigned)((urb_bytes - last_urb_bytes) / n_urbs),
					 (unsigned)cur_urbs,
					 (unsigned)urb_bytes,
					 (unsigned)urb_max_len,
					 (unsigned)urb_zero_len,
					 (unsigned)urb_ragged);
		}

		if (c.seq_errors != last_seq_errors)
			pr_trace("[%s] last seq err: expected %02x got %02x\n", name, c.last_seq_expected, c.last_seq_got);

		if (c.framing_errors != last_framing_errors && c.last_bad_msg_len != 0)
			pr_trace("[%s] last bad msg len: %u\n", name, (unsigned)c.last_bad_msg_len);

		if (snapshot_valid) {
			pr_trace("[%s] packets around first error (oldest first):\n", name);
			for (auto i = 0u; i < snapshot_len; i++) {
				pr_trace(" %08x", (unsigned)snapshot[i]);
				if ((i % 8) == 7 || i == snapshot_len - 1)
					pr_trace("\n");
			}
			snapshot_valid = false; // re-arm capture
		}

		last_pkts = pkts;
		last_msgs = c.messages;
		last_errors = errors;
		last_seq_errors = c.seq_errors;
		last_framing_errors = c.framing_errors;
		last_urbs = cur_urbs;
		last_urb_bytes = urb_bytes;
	}

private:
	const char *name;

	std::array<uint32_t, RingSize> ring{};
	uint32_t write_idx = 0;

	std::array<uint32_t, RingSize> snapshot{};
	uint32_t snapshot_len = 0;
	volatile bool snapshot_valid = false;

	uint32_t last_report_ms = 0;
	uint32_t last_pkts = 0;
	uint32_t last_msgs = 0;
	uint32_t last_errors = 0;
	uint32_t last_seq_errors = 0;
	uint32_t last_framing_errors = 0;
	uint32_t last_urbs = 0;
	uint32_t last_urb_bytes = 0;
};

#else

// Monitoring disabled (default): all calls compile to nothing.
// Enable with cmake -DUSB_MIDI_MONITOR=ON
struct MidiPacketMonitor {
	uint32_t transport_drops = 0;

	MidiPacketMonitor(const char *) {
	}
	void log(uint32_t) {
	}
	void mark(uint32_t) {
	}
	void add_urb(uint32_t) {
	}
	void print_report(uint32_t) {
	}
};

#endif // USB_MIDI_MONITOR

} // namespace MetaModule
