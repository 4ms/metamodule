#include "core_m4/midi_controls.hh"
#include "doctest.h"
#include "patch/midi_def.hh"
#include <algorithm>
#include <array>
#include <memory>

// Tests for the all-notes-off sequence, aka MIDI panic (started on MIDI
// disconnect). The sequence must emit a NoteOff for every MIDI note number
// (0..127) on every channel: the A7 keeps per-note gate state keyed by
// event.note (note-gate mappings) as well as poly note gates keyed by
// event.poly_chan, and both must be released or notes held at disconnect
// stay stuck.

using namespace MetaModule;

namespace
{

MidiMessage note_on(uint8_t chan, uint8_t note, uint8_t vel = 100) {
	return MidiMessage{uint8_t(0x90 | (chan & 0x0F)), note, vel};
}

MidiMessage note_off(uint8_t chan, uint8_t note) {
	return MidiMessage{uint8_t(0x80 | (chan & 0x0F)), note, 0};
}

// Run the sequence to completion, checking every emitted event.
// Returns the number of NoteOff events emitted.
unsigned run_noteoff_sequence(Midi::MessageParser &parser) {
	unsigned noteoffs = 0;

	while (true) {
		auto event = parser.step_all_notes_off_sequence();
		REQUIRE(event.has_value());

		if (event->type == Midi::Event::Type::None)
			return noteoffs;

		CHECK(event->type == Midi::Event::Type::NoteOff);
		CHECK(event->note < NumMidiNotes);
		// midi_chan is a bitfield: copy it out, since CHECK takes a reference
		CHECK(unsigned(event->midi_chan) < Midi::MessageParser::NumMidiChannels);
		// poly_chan mirrors the note number so the A7 clears poly note gates
		// (it ignores poly_chan >= the active poly count)
		CHECK(event->poly_chan == event->note);
		noteoffs++;

		// Bound so a runaway sequence fails instead of hanging
		REQUIRE(noteoffs <= NumMidiNotes * Midi::MessageParser::NumMidiChannels);
	}
}

} // namespace

TEST_CASE("Panic sequence emits NoteOff for every note number on every channel") {
	Midi::MessageParser parser;

	parser.start_all_notes_off_sequence();

	for (unsigned chan = 0; chan < Midi::MessageParser::NumMidiChannels; chan++) {
		for (unsigned note = 0; note < NumMidiNotes; note++) {
			auto event = parser.step_all_notes_off_sequence();
			REQUIRE(event.has_value());
			CHECK(event->type == Midi::Event::Type::NoteOff);
			CHECK(unsigned(event->midi_chan) == chan);
			CHECK(event->note == note);
		}
	}

	// Terminator, then not-running
	auto done = parser.step_all_notes_off_sequence();
	REQUIRE(done.has_value());
	CHECK(done->type == Midi::Event::Type::None);
	CHECK_FALSE(parser.step_all_notes_off_sequence().has_value());
}

TEST_CASE("Panic sequence covers all notes regardless of a reduced poly count") {
	Midi::MessageParser parser;
	parser.set_poly_num(2);

	parser.start_all_notes_off_sequence();
	auto noteoffs = run_noteoff_sequence(parser);

	CHECK(noteoffs == Midi::MessageParser::NumMidiChannels * NumMidiNotes);
}

TEST_CASE("Panic sequence writes nothing outside the parser") {
	// Sandwich the parser between canary buffers. The regression's
	// out-of-bounds writes cleared single bytes hundreds of bytes past the
	// note containers, past the end of the parser object itself.
	struct Sandwich {
		std::array<uint8_t, 512> canary_before;
		Midi::MessageParser parser;
		std::array<uint8_t, 512> canary_after;
	};

	auto sandwich = std::make_unique<Sandwich>();
	sandwich->canary_before.fill(0xAA);
	sandwich->canary_after.fill(0xAA);

	// Hold notes so the sequence has real gates to clear, including with a
	// reduced poly count (fewer tracker slots than sequence steps)
	sandwich->parser.set_poly_num(3);
	for (uint8_t chan = 0; chan < Midi::MessageParser::NumMidiChannels; chan++)
		for (uint8_t n = 0; n < MaxMidiPolyphony; n++)
			sandwich->parser.parse(note_on(chan, uint8_t(60 + n)));

	sandwich->parser.start_all_notes_off_sequence();
	run_noteoff_sequence(sandwich->parser);

	CHECK(std::ranges::all_of(sandwich->canary_before, [](uint8_t b) { return b == 0xAA; }));
	CHECK(std::ranges::all_of(sandwich->canary_after, [](uint8_t b) { return b == 0xAA; }));
}

TEST_CASE("Parser still tracks notes correctly after a panic sequence") {
	Midi::MessageParser parser;

	// Hold notes on a few channels, then run the disconnect sequence
	parser.parse(note_on(0, 60));
	parser.parse(note_on(5, 72));
	parser.start_all_notes_off_sequence();
	run_noteoff_sequence(parser);

	// The sequence must have cleared all gates: a NoteOff for a previously-held
	// note no longer finds it...
	auto off = parser.parse(note_off(0, 60));
	CHECK(off.type == Midi::Event::Type::NoteOff);
	CHECK(off.poly_chan == 0xFF); // -1: not found among held notes

	// ...and normal note tracking still works (the original crash was a fault
	// right here, when parse() walked the corrupted note containers)
	auto on = parser.parse(note_on(3, 64));
	CHECK(on.type == Midi::Event::Type::NoteOn);
	auto on_poly_chan = on.poly_chan;
	CHECK(on_poly_chan < MaxMidiPolyphony);

	auto off2 = parser.parse(note_off(3, 64));
	CHECK(off2.type == Midi::Event::Type::NoteOff);
	CHECK(off2.poly_chan == on_poly_chan);
}
