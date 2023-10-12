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

	MidiCC0 = 0x200, // MidiModWheelJack,
	//...
	MidiCC127 = 0x27F,
	MidiPitchWheelJack = 0x280,

	MidiGateNote0 = 0x300, //Note 0 (C-2) -> Gate
	//...
	MidiGateNote127 = 0x37F, //Note 127 (G8) -> Gate

	MidiRetriggerJack,
	MidiClockJack,
	MidiClockDivJack,
	MidiStartJack,
	MidiStopJack,
	MidiContinueJack,

	LastMidiJack
};

static constexpr unsigned MidiMaxSimulGates = 8;
static constexpr unsigned MidiPolyphony = 4;

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
