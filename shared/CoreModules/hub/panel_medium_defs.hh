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
	static constexpr std::array<std::string_view, NumKnobs> KnobNames{
		"A", "B", "C", "D", "E", "F", "u", "v", "w", "x", "y", "z"};

	static constexpr std::array<std::string_view, 2> MidiParamNames{"MidiNote", "MidiGate"};
	static constexpr std::array<std::string_view, 2> MidiParamAbbrev{"MN", "MG"};
	static constexpr uint32_t NumMidiParams = MidiParamNames.size();

	static constexpr std::string_view get_map_param_name(uint32_t id) {
		if (id < KnobNames.size())
			return KnobNames[id];
		id -= NumKnobs;
		if (id < MidiParamNames.size())
			return MidiParamNames[id];
		return "?";
	}

	// User-facing in jacks, like "Audio In 1", is an output jack as seen by other virtual modules
	static constexpr int NumUserFacingInJacks = NumAudioIn + NumCVIn + NumGateIn;

	static constexpr std::array<std::string_view, NumUserFacingInJacks> InJackNames{
		"In1", "In2", "In3", "In4", "In5", "In6", "GateIn1", "GateIn2"};

	static constexpr std::array<std::string_view, NumUserFacingInJacks> InJackAbbrev{
		"1", "2", "3", "4", "5", "6", "G1", "G2"};

	static constexpr std::array<std::string_view, 2> MidiJackMapNames{"MIDIGate", "MIDINote"};
	static constexpr std::array<std::string_view, 2> MidiJackMapAbbrev{"MG", "MN"};
	static constexpr int NumMidiJackMaps = MidiJackMapNames.size();

	static constexpr std::string_view get_map_injack_name(uint32_t id) {
		if (id < NumUserFacingInJacks)
			return InJackNames[id];
		id -= NumUserFacingInJacks;
		if (id < NumMidiJackMaps)
			return MidiJackMapAbbrev[id];
		return "?";
	}

	static constexpr std::string_view get_map_injack_abbrev(uint32_t id) {
		if (id < NumUserFacingInJacks)
			return InJackAbbrev[id];
		id -= NumUserFacingInJacks;
		if (id < NumMidiJackMaps)
			return MidiJackMapNames[id];
		return "?";
	}

	// User-facing out jacks, like "Audio Out 3", is an input jack as seen by other virtual modules
	static constexpr int NumUserFacingOutJacks = NumAudioOut + NumDACOut + NumGateOut;

	static constexpr std::array<std::string_view, NumUserFacingOutJacks> OutJackNames{
		"Out1", "Out2", "Out3", "Out4", "Out5", "Out6", "Out7", "Out8"};

	static constexpr std::array<std::string_view, NumUserFacingOutJacks> OutJackAbbrevs{
		"1", "2", "3", "4", "5", "6", "7", "8"};

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

	static constexpr char NumJacks = NumUserFacingInJacks + NumUserFacingOutJacks + NumMetaCV;

	//Array index is codec channel number 0-5
	//Value is panel jack number (Audio In 0 - 5)
	//This is hardware-dependant
	static constexpr uint32_t audioin_order[NumAudioIn] = {3, 2, 1, 0, 5, 4};
};
