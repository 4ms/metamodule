#include "doctest.h"
#include "midi/midi_stream_parser.hh"
#include <vector>

// Tests for the serial MIDI (DIN/TRS) byte stream parser.
//
// The MIDI Expander hands over raw wire bytes, not USB-MIDI packets, so this is
// where running status, interleaved System Real Time and multi-packet SysEx get
// turned back into MidiMessages.

using namespace MetaModule;

namespace
{

// Feed a whole stream and collect everything it produces
std::vector<MidiMessage> feed(Midi::StreamParser &parser, std::vector<uint8_t> const &bytes) {
	std::vector<MidiMessage> out;

	for (auto byte : bytes) {
		if (auto msg = parser.parse(byte))
			out.push_back(*msg);
	}

	return out;
}

} // namespace

TEST_CASE("Channel voice messages") {
	Midi::StreamParser parser;

	SUBCASE("Three-byte message emits once, on the last byte") {
		CHECK(!parser.parse(0x90).has_value());
		CHECK(!parser.parse(60).has_value());

		auto msg = parser.parse(100);
		REQUIRE(msg.has_value());
		CHECK(unsigned(msg->status) == 0x90);
		CHECK(msg->note() == 60);
		CHECK(msg->velocity() == 100);
	}

	SUBCASE("Program Change is two bytes, not three") {
		auto msgs = feed(parser, {0xC3, 42});

		REQUIRE(msgs.size() == 1);
		CHECK(unsigned(msgs[0].status) == 0xC3);
		CHECK(msgs[0].pcval() == 42);
	}

	SUBCASE("Channel Pressure is two bytes") {
		auto msgs = feed(parser, {0xD0, 77});

		REQUIRE(msgs.size() == 1);
		CHECK(msgs[0].chan_pressure() == 77);
	}
}

TEST_CASE("Running status") {
	Midi::StreamParser parser;

	SUBCASE("A bare data pair reuses the previous channel-voice status") {
		auto msgs = feed(parser, {0x92, 60, 100, 62, 101, 64, 102});

		REQUIRE(msgs.size() == 3);
		for (auto &msg : msgs)
			CHECK(unsigned(msg.status) == 0x92);

		CHECK(msgs[1].note() == 62);
		CHECK(msgs[2].note() == 64);
	}

	SUBCASE("System Common cancels running status") {
		// Song Select in the middle, then a bare data pair which must be dropped
		auto msgs = feed(parser, {0x90, 60, 100, 0xF3, 5, 62, 101});

		REQUIRE(msgs.size() == 2);
		CHECK(unsigned(msgs[0].status) == 0x90);
		CHECK(unsigned(msgs[1].status) == 0xF3);
	}

	SUBCASE("Data bytes before any status are dropped") {
		auto msgs = feed(parser, {60, 100, 62});
		CHECK(msgs.size() == 0);
	}
}

TEST_CASE("System Real Time") {
	Midi::StreamParser parser;

	SUBCASE("Passes straight through") {
		auto msgs = feed(parser, {0xF8});

		REQUIRE(msgs.size() == 1);
		CHECK(unsigned(msgs[0].status) == 0xF8);
	}

	SUBCASE("Interleaved mid-message without disturbing it") {
		// Clock arrives between the note number and the velocity
		auto msgs = feed(parser, {0x90, 60, 0xF8, 100});

		REQUIRE(msgs.size() == 2);
		CHECK(unsigned(msgs[0].status) == 0xF8);
		CHECK(unsigned(msgs[1].status) == 0x90);
		CHECK(msgs[1].note() == 60);
		CHECK(msgs[1].velocity() == 100);
	}

	SUBCASE("Does not break running status") {
		auto msgs = feed(parser, {0x90, 60, 100, 0xFE, 62, 101});

		REQUIRE(msgs.size() == 3);
		CHECK(unsigned(msgs[1].status) == 0xFE); // Active Sensing
		CHECK(unsigned(msgs[2].status) == 0x90);
		CHECK(msgs[2].note() == 62);
	}
}

TEST_CASE("System Common") {
	Midi::StreamParser parser;

	SUBCASE("Tune Request has no data bytes") {
		auto msgs = feed(parser, {0xF6});

		REQUIRE(msgs.size() == 1);
		CHECK(unsigned(msgs[0].status) == 0xF6);
	}

	SUBCASE("Song Position Pointer takes two") {
		auto msgs = feed(parser, {0xF2, 0x10, 0x20});

		REQUIRE(msgs.size() == 1);
		CHECK(unsigned(msgs[0].status) == 0xF2);
	}
}

TEST_CASE("SysEx") {
	Midi::StreamParser parser;

	SUBCASE("Full three-byte groups carry CIN 0x4") {
		// F0 41 42 | 43 44 F7 -> one continuation packet, then a 3-byte end
		auto msgs = feed(parser, {0xF0, 0x41, 0x42, 0x43, 0x44, 0xF7});

		REQUIRE(msgs.size() == 2);
		CHECK(unsigned(msgs[0].usb_hdr.cin) == 0x4);
		CHECK(unsigned(msgs[1].usb_hdr.cin) == 0x7); // ends with three bytes
		CHECK(msgs[0].is_sysex());
		CHECK(msgs[1].is_sysex());
	}

	SUBCASE("Ending with one byte carries CIN 0x5") {
		// F0 41 42 fills a group, then F7 alone ends it
		auto msgs = feed(parser, {0xF0, 0x41, 0x42, 0xF7});

		REQUIRE(msgs.size() == 2);
		CHECK(unsigned(msgs[0].usb_hdr.cin) == 0x4);
		CHECK(unsigned(msgs[1].usb_hdr.cin) == 0x5);
	}

	SUBCASE("Ending with two bytes carries CIN 0x6") {
		auto msgs = feed(parser, {0xF0, 0x41, 0x42, 0x43, 0xF7});

		REQUIRE(msgs.size() == 2);
		CHECK(unsigned(msgs[0].usb_hdr.cin) == 0x4);
		CHECK(unsigned(msgs[1].usb_hdr.cin) == 0x6);
	}

	SUBCASE("Real Time may appear inside a SysEx") {
		auto msgs = feed(parser, {0xF0, 0x41, 0xF8, 0x42, 0xF7});

		REQUIRE(msgs.size() == 3);
		CHECK(unsigned(msgs[0].status) == 0xF8); // clock came out first
		CHECK(unsigned(msgs[1].usb_hdr.cin) == 0x4);		 // F0 41 42
		CHECK(unsigned(msgs[2].usb_hdr.cin) == 0x5);		 // F7 alone
	}

	SUBCASE("A status byte abandons an unterminated SysEx") {
		auto msgs = feed(parser, {0xF0, 0x41, 0x90, 60, 100});

		REQUIRE(msgs.size() == 1);
		CHECK(unsigned(msgs[0].status) == 0x90);
	}

	SUBCASE("A stray F7 is ignored") {
		auto msgs = feed(parser, {0xF7, 0x90, 60, 100});

		REQUIRE(msgs.size() == 1);
		CHECK(unsigned(msgs[0].status) == 0x90);
	}
}

TEST_CASE("reset() drops a partial message") {
	Midi::StreamParser parser;

	CHECK(!parser.parse(0x90).has_value());
	CHECK(!parser.parse(60).has_value());

	parser.reset();

	// The velocity byte has nothing to attach to now
	CHECK(!parser.parse(100).has_value());
}
