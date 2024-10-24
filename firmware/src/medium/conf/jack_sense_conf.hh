#pragma once
#include "CoreModules/hub/panel_medium_defs.hh"
#include <cstdint>
#include <optional>

constexpr unsigned jacksense_pin_order[16] = {
	/*in*/ 14, 11, 15, 13, 10, 8, /*gate in*/ 12, 9, /*out*/ 4, 5, 6, 1, 2, 7, 3, 0};

constexpr inline bool jack_is_patched(uint32_t jack_sense_reading, unsigned panel_jack_idx) {
	return (jack_sense_reading >> jacksense_pin_order[panel_jack_idx]) & 1;
}

constexpr inline std::optional<unsigned> main_jacksense_output_bit(unsigned panel_outjack_idx) {
	if (PanelDef::is_main_panel_output(panel_outjack_idx))
		return jacksense_pin_order[panel_outjack_idx + PanelDef::NumUserFacingInJacks];
	else
		return {};
}

constexpr inline std::optional<unsigned> main_jacksense_input_bit(unsigned panel_injack_idx) {
	if (PanelDef::is_main_panel_input(panel_injack_idx))
		return jacksense_pin_order[panel_injack_idx];
	else
		return {};
}
