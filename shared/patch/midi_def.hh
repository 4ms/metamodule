#pragma once
#include "CoreModules/hub/panel_medium_defs.hh"

enum {
	MidiMonoNoteJack = PanelDef::NumUserFacingInJacks,
	MidiMonoGateJack,

	LastMidiJack
};

enum {
	MidiMonoNoteParam = PanelDef::NumKnobs,
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
