#pragma once
#include <cstdint>

namespace MetaModule
{

// Validates a stream of 4-byte USB-MIDI event packets carrying the SysEx test
// pattern sent by the modified CV_MIDI module: each message is F0, then
// `expected_msg_len` data bytes, then F7. The data bytes form one continuous
// sequence across messages, incrementing and wrapping at 0x80 (the generator
// masks a running counter with 0x7F).
//
// Pure logic, no I/O: safe to call from ISR context, unit-testable on host.
struct UsbMidiPacketChecker {
	uint32_t expected_msg_len = 32;

	// Counters. Single words: safe enough to read from the main loop while
	// check() runs in an ISR.
	uint32_t sysex_packets = 0;	 // packets with a SysEx CIN (0x4..0x7)
	uint32_t other_packets = 0;	 // any other CIN: counted, not checked
	uint32_t zero_packets = 0;	 // literal 0x04000000 (empty-message artifact)
	uint32_t messages = 0;		 // completed messages (F7 seen)
	uint32_t seq_errors = 0;	 // data byte != previous + 1 (wrapping at 0x80)
	uint32_t framing_errors = 0; // missing/early F0 or F7, or bad message length

	// Context of the most recent errors
	uint8_t last_seq_expected = 0;
	uint8_t last_seq_got = 0;
	uint32_t last_bad_msg_len = 0;

	uint32_t total_errors() const {
		return seq_errors + framing_errors + zero_packets;
	}

	// `raw` is in MidiMessage::raw() format: [cable|CIN] [byte0] [byte1] [byte2]
	void check(uint32_t raw) {
		auto cin = (raw >> 24) & 0xF;

		// Number of valid MIDI bytes in a SysEx event packet, by CIN:
		// 0x4: start/continue (3 bytes), 0x5: end with F7 only (1 byte),
		// 0x6: 1 data byte + F7 (2 bytes), 0x7: 2 data bytes + F7 (3 bytes)
		unsigned num_bytes = (cin == 0x4 || cin == 0x7) ? 3 : (cin == 0x6) ? 2 : (cin == 0x5) ? 1 : 0;

		if (num_bytes == 0) {
			other_packets++;
			return;
		}

		if (raw == 0x04000000) {
			// An empty MidiMessage run through make_usb_msg() produces exactly
			// this packet. The generated stream never contains three
			// consecutive zero data bytes, so count it as its own error class.
			zero_packets++;
			return;
		}

		sysex_packets++;

		check_byte(uint8_t(raw >> 16));
		if (num_bytes > 1)
			check_byte(uint8_t(raw >> 8));
		if (num_bytes > 2)
			check_byte(uint8_t(raw >> 0));
	}

private:
	bool synced = false; // saw the first F0: don't flag a partial first message
	bool in_msg = false;
	bool have_expected = false;
	uint8_t expected = 0;
	uint32_t msg_len = 0;

	void check_byte(uint8_t byte) {
		if (byte == 0xF0) {
			if (in_msg) {
				// Previous message never got its F7
				framing_errors++;
				last_bad_msg_len = msg_len;
			}
			synced = true;
			in_msg = true;
			msg_len = 0;

		} else if (byte == 0xF7) {
			if (!synced)
				return;

			if (!in_msg) {
				framing_errors++; // F7 with no matching F0
			} else {
				if (msg_len != expected_msg_len) {
					framing_errors++;
					last_bad_msg_len = msg_len;
				}
				messages++;
			}
			in_msg = false;

		} else if (byte >= 0x80) {
			// Status/realtime byte: not valid inside this SysEx stream
			if (synced)
				framing_errors++;

		} else { // data byte
			if (!synced)
				return;

			if (!in_msg) {
				// Data with no F0 (lost the start packet): resync into a message
				framing_errors++;
				in_msg = true;
				msg_len = 0;
			}

			if (have_expected && byte != expected) {
				seq_errors++;
				last_seq_expected = expected;
				last_seq_got = byte;
			}
			expected = (byte + 1) & 0x7F;
			have_expected = true;
			msg_len++;
		}
	}
};

} // namespace MetaModule
