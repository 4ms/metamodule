#pragma once

#include <array>
#include <cstdint>
#include <optional>
#include <string_view>

struct PanelDef {
	static constexpr uint32_t PanelID = 2;
	static constexpr char typeID[20] = "Handheld-p1";

	static constexpr uint32_t NumAudioIn = 2;
	static constexpr uint32_t NumAudioOut = 2;
	static constexpr uint32_t NumDACOut = 0;
	static constexpr uint32_t NumPot = 0;
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

static constexpr std::array<uint32_t, NumInJacks> in_order;
static constexpr std::array<std::string_view, NumInJacks> InJackNames;
static constexpr std::array<std::string_view, NumInJacks> InJackAbbrevs;
static constexpr std::string_view get_map_injack_name(uint32_t id) {
	return "";
}

// 0..5 => 8..13
static constexpr uint32_t get_map_injack_num(uint32_t id) {
	return 0;
}

//// Outs

static constexpr uint32_t NumOutJacks = 0;
static constexpr uint32_t NumUserFacingOutJacks = NumOutJacks;

static constexpr std::array<uint32_t, NumOutJacks> out_order;
static constexpr std::array<std::string_view, NumUserFacingOutJacks> OutJackNames;
static constexpr std::array<std::string_view, NumUserFacingOutJacks> OutJackAbbrevs;
static constexpr std::string_view get_map_outjack_name(uint32_t id) {
	return "";
}

static constexpr uint32_t get_map_outjack_num(uint32_t id) {
	return 0;
}

//////////

static constexpr auto NumJacks = NumInJacks + NumOutJacks;

static constexpr uint32_t exp_to_panel_input(uint32_t exp_injack_idx) {
	return exp_injack_idx + PanelDef::NumUserFacingInJacks;
}

static constexpr unsigned panel_to_exp_input(unsigned panel_injack_idx) {
	return panel_injack_idx - PanelDef::NumUserFacingInJacks;
}

static constexpr uint32_t exp_to_panel_output(uint32_t exp_outjack_idx) {
	return exp_outjack_idx + PanelDef::NumUserFacingOutJacks;
}

static constexpr uint32_t panel_to_exp_output(uint32_t panel_outjack_idx) {
	return panel_outjack_idx - PanelDef::NumUserFacingOutJacks;
}

static constexpr bool is_expander_input(unsigned panel_injack_idx) {
	return panel_injack_idx < PanelDef::NumUserFacingInJacks + NumInJacks &&
		   panel_injack_idx >= PanelDef::NumUserFacingInJacks;
}

static constexpr bool is_expander_output(unsigned panel_outjack_idx) {
	return panel_outjack_idx < PanelDef::NumUserFacingOutJacks + NumOutJacks &&
		   panel_outjack_idx >= PanelDef::NumUserFacingOutJacks;
}

constexpr unsigned jacksense_pin_order[NumJacks]{};
constexpr inline std::optional<unsigned> jacksense_output_bit(unsigned panel_outjack_idx) {
	return {};
}
constexpr inline std::optional<unsigned> jacksense_input_bit(unsigned panel_injack_idx) {
	return {};
}
constexpr inline bool jack_is_patched(uint32_t jack_sense_reading, unsigned exp_panel_jack_idx) {
	return false;
}

} // namespace MetaModule::AudioExpander
