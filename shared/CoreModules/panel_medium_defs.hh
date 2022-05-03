#pragma once
#include "util/static_string.hh"
#include <cstdint>

struct PanelDef {
	static constexpr uint32_t PanelID = 1;
	static constexpr char typeID[20] = "PanelMedium";

	static constexpr uint32_t NumAudioIn = 6;
	static constexpr uint32_t NumAudioOut = 8;
	static constexpr uint32_t NumDACOut = 0;
	static constexpr uint32_t NumPot = 12;
	static constexpr uint32_t NumCVIn = 0;
	static constexpr uint32_t NumGateIn = 2;
	static constexpr uint32_t NumGateOut = 0;
	static constexpr uint32_t NumMetaCV = 0;
	static constexpr uint32_t NumRgbButton = 0;
	static constexpr uint32_t NumMetaRgbButton = 1;

	static constexpr int NumKnobs = NumPot;
	static constexpr std::string_view KnobNames[NumPot] = {"A", "B", "C", "D", "E", "F", "u", "v", "w", "x", "y", "z"};

	static constexpr int NumOutJacks = NumAudioIn + NumCVIn + NumGateIn;
	static constexpr int NumInJacks = NumAudioOut + NumDACOut + NumGateOut;
	// User-facing out jacks, like "Audio Out 3", is an input jack as seen by other virtual modules
	static constexpr int NumUserFacingOutJacks = NumInJacks;
	// User-facing in jacks, like "Audio In 1", is an output jack as seen by other virtual modules
	static constexpr int NumUserFacingInJacks = NumOutJacks;

	static constexpr char NumJacks = NumInJacks + NumOutJacks + NumMetaCV;
	static constexpr char InJackNames[NumUserFacingInJacks][5] = {
		"In1",
		"In2",
		"In3",
		"In4",
		"In5",
		"In6",
		"GIn1",
		"GIn2",
	};
	static constexpr char OutJackNames[NumUserFacingOutJacks][5] = {
		"Out1",
		"Out2",
		"Out3",
		"Out4",
		"Out5",
		"Out6",
		"Out7",
		"Out8",
	};
	static constexpr char ShortJackNames[NumJacks][5] = {
		"In1",
		"In2",
		"In3",
		"In4",
		"In5",
		"In6",
		"GIn1",
		"GIn2",
		"Out1",
		"Out2",
		"Out3",
		"Out4",
		"Out5",
		"Out6",
		"Out7",
		"Out8",
	};
	static constexpr uint32_t audioin_order[NumAudioIn] = {3, 2, 1, 0, 5, 4};
};
