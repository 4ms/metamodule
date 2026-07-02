#include "core_m4/midi_controls.hh"
#include "doctest.h"
#include "patch/midi_def.hh"

// Tests for MIDI 14-bit CC support (issue #508).
//
// The M4 core's MessageParser always emits CC values in a 14-bit range so the A7 core
// can use one fixed conversion regardless of mode:
//   - 14-bit mode OFF: 7-bit CC value is left-shifted by 7 (127 -> 16256).
//   - 14-bit mode ON:  CC 0-31 are MSBs, CC 32-63 are the matching LSBs (CC n+32),
//                      combined into a 0..16383 value emitted on the MSB's CC number.

using namespace MetaModule;

namespace
{
// Build a Control Change MidiMessage on the given channel (0-15).
MidiMessage cc_msg(uint8_t chan, uint8_t ccnum, uint8_t ccval) {
	return MidiMessage{uint8_t(0xB0 | (chan & 0x0F)), ccnum, ccval};
}
} // namespace

TEST_CASE("7-bit CC values are left-shifted by 7 when 14-bit mode is off") {
	Midi::MessageParser parser;
	parser.set_14bit_mode(false);

	auto full = parser.parse(cc_msg(0, 1, 127));
	CHECK(full.type == Midi::Event::Type::CC);
	CHECK(full.note == 1);
	CHECK(full.val == (127 << 7)); // 16256

	// The example from the issue: CC value of 10 is sent as 1280.
	auto small = parser.parse(cc_msg(0, 1, 10));
	CHECK(small.val == 1280);

	auto zero = parser.parse(cc_msg(0, 5, 0));
	CHECK(zero.val == 0);
}

TEST_CASE("14-bit mode combines MSB (CC 0-31) and LSB (CC 32-63)") {
	Midi::MessageParser parser;
	parser.set_14bit_mode(true);

	// MSB on CC1 = 100 -> coarse value, emitted on CC1
	auto msb = parser.parse(cc_msg(0, 1, 100));
	CHECK(msb.note == 1);
	CHECK(msb.val == (100 << 7));

	// LSB on CC33 (= 1 + 32) = 50 -> combined value, still emitted on CC1
	auto lsb = parser.parse(cc_msg(0, 33, 50));
	CHECK(lsb.note == 1);
	CHECK(lsb.val == ((100 << 7) | 50));

	// Full scale: MSB=127 then LSB=127 -> 16383, emitted on CC2
	parser.parse(cc_msg(0, 2, 127));
	auto fullscale = parser.parse(cc_msg(0, 34, 127));
	CHECK(fullscale.note == 2);
	CHECK(fullscale.val == 16383);
}

TEST_CASE("14-bit mode: receiving an MSB resets the LSB to 0") {
	Midi::MessageParser parser;
	parser.set_14bit_mode(true);

	parser.parse(cc_msg(0, 1, 100));
	parser.parse(cc_msg(0, 33, 127)); // LSB = 127

	// New MSB should reset the implicit LSB back to 0
	auto msb = parser.parse(cc_msg(0, 1, 64));
	CHECK(msb.val == (64 << 7));

	// An LSB of 0 confirms the combined value has no leftover fine bits
	auto lsb = parser.parse(cc_msg(0, 33, 0));
	CHECK(lsb.val == (64 << 7));
}

TEST_CASE("14-bit mode leaves CC 64-127 as plain (shifted) 7-bit values") {
	Midi::MessageParser parser;
	parser.set_14bit_mode(true);

	auto e = parser.parse(cc_msg(0, 74, 127));
	CHECK(e.note == 74);
	CHECK(e.val == (127 << 7));
}

TEST_CASE("u14cc_to_volts maps the 14-bit CC range to 0-10V") {
	// 7-bit full-scale (127<<7) maps to exactly 10V, preserving legacy behavior.
	CHECK(Midi::u14cc_to_volts<10>(127 << 7) == doctest::Approx(10.f));
	CHECK(Midi::u14cc_to_volts<10>(10 << 7) == doctest::Approx(10.f / 12.7f));
	CHECK(Midi::u14cc_to_volts<10>(0) == doctest::Approx(0.f));
	// 14-bit full-scale slightly exceeds 10V (expected, ~0.8%).
	CHECK(Midi::u14cc_to_volts<10>(16383) > 10.f);
	CHECK(Midi::u14cc_to_volts<10>(16383) < 10.1f);
}
