#pragma once
#include <array>
#include <cstdint>

namespace MetaModule::Midi
{

struct Event {
	enum class Type : uint8_t {
		None,
		NoteOn,
		NoteOff,
		Aft,
		ChanPress,
		Retrig,
		GateNote,
		CC,
		Bend,
		Time,
		PC,
	} type = Type::None;

	enum Port { USB = 0, TRS = 1, DIN5 = 2 };
	uint8_t port : 4 = 0;
	uint8_t midi_chan : 4 = 0;
	uint8_t poly_chan = 0; // (0-7) may expand to 0-15: top 4/5 bits unused
	uint8_t note = 0;	   // GateNote: note value; CC: ccnum; Time: event type
	int16_t val = 0;	   //velocity, pitchBend, or on/off
};
static constexpr auto sizeofEvent = sizeof(Event);

enum DivClock : uint8_t {
	DivClock1,
	DivClock2,
	DivClock3,
	DivClock6,
	DivClock12,
	DivClock24,
	DivClock48,
	DivClock96,
	NumDivClocks
};

static constexpr uint8_t DivClockAmt[] = {1, 2, 3, 6, 12, 24, 48, 96};

} // namespace MetaModule::Midi
