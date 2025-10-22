#pragma once

#include <array>
#include <cstdint>
#include <optional>
#include <string_view>

struct PanelDef {
	static constexpr uint32_t PanelID = 4;
	static constexpr char typeID[] = "Devboard-bfmu";

	// These are used for numbering the jacks and controls and outputs
	static constexpr uint32_t NumAudioIn = 2;
	static constexpr uint32_t NumAudioOut = 2;
	static constexpr uint32_t NumDACOut = 2;

	// TODO: count all muxed pots
	static constexpr uint32_t NumPot = 5;
	static constexpr uint32_t NumCVIn = 5;

	static constexpr uint32_t NumGateIn = 4;
	static constexpr uint32_t NumGateOut = 2;

	static constexpr uint32_t NumMetaCV = 0;
	static constexpr uint32_t NumRgbButton = 0;
	static constexpr uint32_t NumMetaRgbButton = 0;

	static constexpr uint32_t NumKnobs = NumPot;
	static constexpr int NumUserFacingInJacks = NumAudioIn + NumCVIn + NumGateIn;
	static constexpr int NumUserFacingOutJacks = NumAudioOut + NumDACOut + NumGateOut;
	static constexpr char NumJacks = NumUserFacingInJacks + NumUserFacingOutJacks + NumMetaCV;

	static constexpr std::array<std::string_view, NumKnobs> KnobNames{};

	static constexpr std::array<std::string_view, NumUserFacingInJacks> InJackNames{"InL", "InR"};

	static constexpr std::array<std::string_view, NumUserFacingInJacks> InJackAbbrev{"L", "R"};

	static constexpr std::array<std::string_view, NumUserFacingOutJacks> OutJackNames{"OutL", "OutR"};

	static constexpr std::array<std::string_view, NumUserFacingOutJacks> OutJackAbbrevs{"L", "R"};

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
	static constexpr std::array<uint32_t, 2> audioin_order{0, 1};

	static constexpr bool is_main_panel_input(unsigned panel_jack_idx) {
		return panel_jack_idx < PanelDef::NumUserFacingInJacks;
	}

	static constexpr bool is_main_panel_output(unsigned panel_jack_idx) {
		return panel_jack_idx < PanelDef::NumUserFacingOutJacks;
	}
};

namespace MetaModule::AudioExpander
{
static constexpr uint32_t NumInJacks = 0;

static constexpr uint32_t NumOutJacks = 0;

static constexpr auto NumJacks = NumInJacks + NumOutJacks;

} // namespace MetaModule::AudioExpander
