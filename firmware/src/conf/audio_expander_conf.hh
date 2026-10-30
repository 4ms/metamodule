#pragma once
#include "patch-serial/patch/panels/medium/audio_expander_defs.hh"
#include <array>
#include <cstdint>
#include <optional>

// The Audio Expander's hardware: which of its jacks each codec channel and jack sense pin is.
// (Its jacks' IDs and names are in patch-serial's panels/medium/audio_expander_defs.hh)
// The pro has no expander port, but builds the medium's expander code with this.
namespace MetaModule::AudioExpander
{

// The expander input jack (0 = ExpIn7) that each expander codec input channel reads
static constexpr std::array<uint32_t, NumInJacks> in_order{0, 1, 2, 3, 4, 5};

// The expander output jack (0 = ExpOut9) that each expander codec output channel drives
static constexpr std::array<uint32_t, 8> out_order{2, 0, 4, 6, 7, 5, 3, 1};

// Jack sensing:
// Note: pins 8 and 10 are not connected (that is, bits 24 and 26 of jack_sense are not used)
constexpr unsigned jacksense_pin_order[NumJacks] = {
	/*in:*/ 16, 21, 17, 20, 19, 23, /*out:*/ 18, 22, 31, 25, 30, 27, 29, 28};

constexpr inline std::optional<unsigned> jacksense_output_bit(unsigned panel_outjack_idx) {
	if (is_expander_output(panel_outjack_idx))
		return jacksense_pin_order[panel_to_exp_output(panel_outjack_idx) + NumInJacks];
	else
		return {};
}

constexpr inline std::optional<unsigned> jacksense_input_bit(unsigned panel_injack_idx) {
	if (is_expander_input(panel_injack_idx))
		return jacksense_pin_order[panel_to_exp_input(panel_injack_idx)];
	else
		return {};
}

// Given expander jack ID (0..5 = Expander Inputs, 6..13 = Expander Outputs)
// Not bounds-checked (used in audio loop)
constexpr inline bool jack_is_patched(uint32_t jack_sense_reading, unsigned exp_panel_jack_idx) {
	return (jack_sense_reading >> jacksense_pin_order[exp_panel_jack_idx]) & 1;
}

} // namespace MetaModule::AudioExpander
