#pragma once
#include <cstdint>

namespace MetaModule::Midi
{

struct Note {
	uint8_t note = 0;
	float gate = 0;
};

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
		Time
	} type = Type::None;

	uint8_t midi_chan = 0; //currently not implemented
	uint8_t poly_chan = 0;
	uint8_t note = 0; // GateNote: note value; CC: ccnum; Time: event type
	float val = 0;	  //velocity or on/off
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
