#pragma once
#include <array>
#include <cstdint>
#include <string_view>

struct PanelDef {
	static constexpr uint32_t PanelID = 1;
	static constexpr char typeID[20] = "HubMedium";

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

	static constexpr uint32_t NumKnobs = NumPot;
	static constexpr int NumUserFacingInJacks = NumAudioIn + NumCVIn + NumGateIn;
	static constexpr int NumUserFacingOutJacks = NumAudioOut + NumDACOut + NumGateOut;
	static constexpr char NumJacks = NumUserFacingInJacks + NumUserFacingOutJacks + NumMetaCV;

	static constexpr std::array<std::string_view, NumKnobs> KnobNames{
		"A", "B", "C", "D", "E", "F", "u", "v", "w", "x", "y", "z"};

	static constexpr std::array<std::string_view, NumUserFacingInJacks> InJackNames{
		"In1", "In2", "In3", "In4", "In5", "In6", "GateIn1", "GateIn2"};

	static constexpr std::array<std::string_view, NumUserFacingInJacks> InJackAbbrev{
		"1", "2", "3", "4", "5", "6", "G1", "G2"};

	static constexpr std::array<std::string_view, NumUserFacingOutJacks> OutJackNames{
		"Out1", "Out2", "Out3", "Out4", "Out5", "Out6", "Out7", "Out8"};

	static constexpr std::array<std::string_view, NumUserFacingOutJacks> OutJackAbbrevs{
		"1", "2", "3", "4", "5", "6", "7", "8"};

	static constexpr std::array<std::string_view, 8> MidiNoteNames{

	};

	static constexpr std::string_view get_map_param_name(uint32_t id) {
		if (id < KnobNames.size())
			return KnobNames[id];
		return "?";
	}

	static constexpr std::string_view get_map_injack_name(uint32_t id) {
		if (id < NumUserFacingInJacks)
			return InJackNames[id];
		return "?";
	}

	static constexpr std::string_view get_map_injack_abbrev(uint32_t id) {
		if (id < NumUserFacingInJacks)
			return InJackAbbrev[id];
		return "?";
	}

	static constexpr std::string_view get_map_outjack_name(uint32_t id) {
		if (id < NumUserFacingOutJacks)
			return OutJackNames[id];
		return "?";
	}

	static constexpr std::string_view get_map_outjack_abbrev(uint32_t id) {
		if (id < NumUserFacingOutJacks)
			return OutJackNames[id];
		return "?";
	}

	//Array index is codec channel number 0-5
	//Value is panel jack number (Audio In 0 - 5)
	//This is hardware-dependant
	static constexpr uint32_t audioin_order[NumAudioIn] = {3, 2, 1, 0, 5, 4};
};
