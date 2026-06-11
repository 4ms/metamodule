#pragma once
#include "midi/usb_midi_packet_checker.hh"
#include <array>
#include <cstdint>
#include <cstdio>

namespace MetaModule
{

// Debug monitor for USB MIDI packet streams.
// log() is called from ISR context: it records the packet in a RAM ring and
// runs the SysEx order checker -- it never prints (a blocking printf in the
// 48kHz FrameRate ISR stalls the param-block walk and loses packets for real).
// print_report() is called from the main loop and prints a once-per-second
// summary when there was traffic, plus the packets surrounding the first
// error captured since the last report.
struct MidiPacketMonitor {
	static constexpr uint32_t ReportIntervalMs = 1000;
	static constexpr uint32_t RingSize = 32; // power of 2

	UsbMidiPacketChecker checker{};
	uint32_t transport_drops = 0; // transmit() returned false (caller increments)

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

	// Main loop context only
	void print_report(uint32_t now_ms) {
		if (now_ms - last_report_ms < ReportIntervalMs)
			return;
		auto elapsed_ms = now_ms - last_report_ms;
		last_report_ms = now_ms;

		// Copy counters: log() may run while we read them
		auto c = checker;
		auto drops = transport_drops;
		auto pkts = c.sysex_packets + c.other_packets + c.zero_packets;
		auto errors = c.total_errors() + drops;

		if (pkts == last_pkts && errors == last_errors)
			return; // no traffic, no news

		printf("[%s] %u pkt/s %u msg/s | total: %u pkts %u msgs | err: %u seq %u framing %u zero-pkt %u drop | %u non-sysex\n",
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

		if (c.seq_errors != last_seq_errors)
			printf("[%s] last seq err: expected %02x got %02x\n", name, c.last_seq_expected, c.last_seq_got);

		if (c.framing_errors != last_framing_errors && c.last_bad_msg_len != 0)
			printf("[%s] last bad msg len: %u\n", name, (unsigned)c.last_bad_msg_len);

		if (snapshot_valid) {
			printf("[%s] packets around first error (oldest first):\n", name);
			for (auto i = 0u; i < snapshot_len; i++) {
				printf(" %08x", (unsigned)snapshot[i]);
				if ((i % 8) == 7 || i == snapshot_len - 1)
					printf("\n");
			}
			snapshot_valid = false; // re-arm capture
		}

		last_pkts = pkts;
		last_msgs = c.messages;
		last_errors = errors;
		last_seq_errors = c.seq_errors;
		last_framing_errors = c.framing_errors;
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
};

} // namespace MetaModule
