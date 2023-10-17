#pragma once
#include "CoreModules/hub/panel_medium_defs.hh"

enum {

	MidiMonoNoteJack = 0x100,
	MidiNote2Jack,
	MidiNote3Jack,
	MidiNote4Jack,
	MidiNote5Jack,
	MidiNote6Jack,
	MidiNote7Jack,
	MidiNote8Jack,

	MidiMonoGateJack = 0x110,
	MidiGate2Jack,
	MidiGate3Jack,
	MidiGate4Jack,
	MidiGate5Jack,
	MidiGate6Jack,
	MidiGate7Jack,
	MidiGate8Jack,

	MidiMonoVelJack = 0x120,
	MidiVel2Jack,
	MidiVel3Jack,
	MidiVel4Jack,
	MidiVel5Jack,
	MidiVel6Jack,
	MidiVel7Jack,
	MidiVel8Jack,

	MidiMonoAftertouchJack = 0x130,
	MidiAftertouch2Jack,
	MidiAftertouch3Jack,
	MidiAftertouch4Jack,
	MidiAftertouch5Jack,
	MidiAftertouch6Jack,
	MidiAftertouch7Jack,
	MidiAftertouch8Jack,

	MidiMonoRetrigJack = 0x140,
	MidiRetrig2Jack,
	MidiRetrig3Jack,
	MidiRetrig4Jack,
	MidiRetrig5Jack,
	MidiRetrig6Jack,
	MidiRetrig7Jack,
	MidiRetrig8Jack,

	MidiCC0 = 0x200,
	MidiCC1, // MidiModWheelJack,
	//...
	MidiCC127 = 0x27F,
	MidiPitchWheelJack = 0x280,

	MidiGateNote0 = 0x300, //Note 0 (C-2) -> Gate
	//...
	MidiGateNote127 = 0x37F, //Note 127 (G8) -> Gate

	MidiClockJack = 0x400,			 // 24 PPQN clock (not divided)
	MidiClockDiv1Jack = 0x400 + 1,	 // 24 PPQN (alias for MidiClockJack)
	MidiClockDiv2Jack = 0x400 + 2,	 // 12 PPQN
	MidiClockDiv3Jack = 0x400 + 3,	 // 32nd note = 3 pulses
	MidiClockDiv6Jack = 0x400 + 6,	 // 16th note = 6 pulses
	MidiClockDiv12Jack = 0x400 + 12, // 8th note = 12 pulses
	MidiClockDiv24Jack = 0x400 + 24, // Quarter note = 24 pulses
	MidiClockDiv48Jack = 0x400 + 48, // Half notes = 2 quarter notes
	MidiClockDiv96Jack = 0x400 + 96, // Whole note = 4 quarter notes

	MidiStartJack = 0x500,
	MidiStopJack,
	MidiContinueJack,

	LastMidiJack
};

namespace TimingEvents
{
enum : uint8_t { Clock = 0, DivClock = 1, Start = 2, Stop = 3, Cont = 4 };
}

enum { MidiModWheelJack = MidiCC1 };

static constexpr unsigned MaxMidiPolyphony = 8;

static constexpr size_t NumMidiNotes = 128;
static constexpr size_t NumMidiCCs = 128;
static constexpr size_t NumMidiCCsPW = NumMidiCCs + 1; //plus pitch wheel (aka bend)
static constexpr size_t NumMidiClockJacks = MidiClockDiv96Jack - MidiClockJack + 1;

enum {
	MidiMonoNoteParam = 0x100,
	MidiMonoGateParam,

	// DuoNote1Param,
	// DuoNote2Param,
	// DuoGate1Param,
	// DuoGate2Param,

	// QuadNote1Param,
	// QuadNote2Param,
	// QuadNote3Param,
	// QuadNote4Param,
	// QuadGate1Param,
	// QuadGate2Param,
	// QuadGate3Param,
	// QuadGate4Param,

	// OctNote1Param,
	// OctNote2Param,
	// OctNote3Param,
	// OctNote4Param,
	// OctNote5Param,
	// OctNote6Param,
	// OctNote7Param,
	// OctNote8Param,
	// OctGate1Param,
	// OctGate2Param,
	// OctGate3Param,
	// OctGate4Param,
	// OctGate5Param,
	// OctGate6Param,
	// OctGate7Param,
	// OctGate8Param,

	LastMidiParam,
};
