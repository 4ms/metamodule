#include "doctest.h"
#include "midi/usb_midi_packet_checker.hh"
#include <vector>

using MetaModule::UsbMidiPacketChecker;

namespace
{

uint32_t pkt(uint8_t cin, uint8_t b0, uint8_t b1, uint8_t b2) {
	return (uint32_t(cin) << 24) | (uint32_t(b0) << 16) | (uint32_t(b1) << 8) | uint32_t(b2);
}

// Mirror the modified CV_MIDI test generator: one 32-data-byte SysEx message,
// drawn from a running counter masked with 0x7F. 12 packets per message:
// [04 F0 d d] [04 d d d] x10 [05 F7 00 00]
std::vector<uint32_t> make_message(unsigned &counter) {
	auto next = [&counter] { return uint8_t(counter++ & 0x7F); };

	std::vector<uint32_t> packets;
	auto d0 = next();
	auto d1 = next();
	packets.push_back(pkt(0x4, 0xF0, d0, d1));
	for (auto i = 0; i < 10; i++) {
		auto a = next();
		auto b = next();
		auto c = next();
		packets.push_back(pkt(0x4, a, b, c));
	}
	packets.push_back(pkt(0x5, 0xF7, 0x00, 0x00));
	return packets;
}

std::vector<uint32_t> make_messages(unsigned num, unsigned &counter) {
	std::vector<uint32_t> packets;
	for (auto i = 0u; i < num; i++) {
		auto msg = make_message(counter);
		packets.insert(packets.end(), msg.begin(), msg.end());
	}
	return packets;
}

void feed(UsbMidiPacketChecker &checker, const std::vector<uint32_t> &packets) {
	for (auto p : packets)
		checker.check(p);
}

} // namespace

TEST_CASE("Perfect stream: no errors, counter wraps at 0x80") {
	UsbMidiPacketChecker checker;
	unsigned counter = 0;

	// 8 messages x 32 bytes = 256 data bytes: wraps the 0..0x7F counter twice
	feed(checker, make_messages(8, counter));

	CHECK(checker.sysex_packets == 8 * 12);
	CHECK(checker.messages == 8);
	CHECK(checker.seq_errors == 0);
	CHECK(checker.framing_errors == 0);
	CHECK(checker.zero_packets == 0);
	CHECK(checker.other_packets == 0);
	CHECK(checker.total_errors() == 0);
}

TEST_CASE("Dropped continuation packet: seq error and short message") {
	UsbMidiPacketChecker checker;
	unsigned counter = 0;

	auto packets = make_messages(2, counter);
	packets.erase(packets.begin() + 5); // a mid-message continuation of msg 1
	feed(checker, packets);

	CHECK(checker.messages == 2);
	CHECK(checker.seq_errors == 1);
	CHECK(checker.framing_errors == 1); // msg 1 is 29 bytes, not 32
	CHECK(checker.last_bad_msg_len == 29);
	CHECK(checker.last_seq_expected == 0x0e); // pkt 5 held 0x0e 0x0f 0x10
	CHECK(checker.last_seq_got == 0x11);
}

TEST_CASE("Dropped SysEx End: framing error, data sequence still intact") {
	UsbMidiPacketChecker checker;
	unsigned counter = 0;

	auto packets = make_messages(3, counter);
	packets.erase(packets.begin() + 11); // msg 1's F7 packet
	feed(checker, packets);

	CHECK(checker.messages == 2);		// only 2 F7s seen
	CHECK(checker.framing_errors == 1); // F0 arrived while still in a message
	CHECK(checker.seq_errors == 0);		// data bytes continue across messages
}

TEST_CASE("Dropped SysEx Start: framing and seq errors") {
	UsbMidiPacketChecker checker;
	unsigned counter = 0;

	auto packets = make_messages(3, counter);
	packets.erase(packets.begin() + 12); // msg 2's F0 packet (2 data bytes lost)
	feed(checker, packets);

	CHECK(checker.messages == 3);
	CHECK(checker.framing_errors >= 1); // data with no F0, then a short message
	CHECK(checker.seq_errors == 1);		// jumped over the 2 data bytes in the F0 packet
	CHECK(checker.last_seq_expected == 0x20);
	CHECK(checker.last_seq_got == 0x22);
}

TEST_CASE("Empty-message artifact packets are counted separately") {
	UsbMidiPacketChecker checker;
	unsigned counter = 0;

	auto packets = make_messages(1, counter);
	packets.insert(packets.begin() + 4, 0x04000000);
	feed(checker, packets);

	CHECK(checker.zero_packets == 1);
	CHECK(checker.messages == 1);
	CHECK(checker.seq_errors == 0); // not treated as stream data
	CHECK(checker.framing_errors == 0);
	CHECK(checker.total_errors() == 1);
}

TEST_CASE("Non-SysEx packets are counted but not checked") {
	UsbMidiPacketChecker checker;
	unsigned counter = 0;

	auto packets = make_messages(1, counter);
	packets.insert(packets.begin() + 3, pkt(0x9, 0x90, 0x3C, 0x64)); // note-on
	packets.insert(packets.begin(), pkt(0xF, 0xF8, 0x00, 0x00));	 // timing clock
	feed(checker, packets);

	CHECK(checker.other_packets == 2);
	CHECK(checker.sysex_packets == 12);
	CHECK(checker.total_errors() == 0);
}

TEST_CASE("Joining mid-stream: quiet until the first F0") {
	UsbMidiPacketChecker checker;
	unsigned counter = 0;

	auto packets = make_messages(3, counter);
	// Start listening in the middle of msg 1
	packets.erase(packets.begin(), packets.begin() + 5);
	feed(checker, packets);

	CHECK(checker.messages == 2); // partial first message not counted
	CHECK(checker.seq_errors == 0);
	CHECK(checker.framing_errors == 0);
}
