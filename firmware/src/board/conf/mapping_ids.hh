#pragma once

// This is the maximum number of knobs and buttons defined in the patch format
// (independent of any particular hardware)
//

static constexpr auto MaxPanelKnobs = 48; // 5 MUX x 8 channels (include the unused pin) + extra to spare
static constexpr auto MaxButtons = 48;	  // 3 MUX x 16 channels (include the unused pins)

enum {
	LastPossibleKnob = MaxPanelKnobs,		   //40
	FirstButton = LastPossibleKnob + 1,		   //41
	LastButton = LastPossibleKnob + MaxButtons //75
};

static constexpr auto NumTotalParams = LastButton;

constexpr bool is_button(unsigned panel_knob_id) {
	return panel_knob_id >= FirstButton && panel_knob_id <= LastButton;
}

constexpr bool is_panel_knob(unsigned panel_knob_id) {
	return panel_knob_id < MaxPanelKnobs;
}
