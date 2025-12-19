#pragma once

// These is the maximum number of knobs and buttons defined in the patch format
// (independent of any particular hardware)
static constexpr auto MaxPanelKnobs = 48; // 5 MUX x 8 channels (include the unused pin) + extra to spare
static constexpr auto MaxButtons = 48;	  // 3 MUX x 16 channels (include the unused pins)
static constexpr auto NumTotalParams = MaxPanelKnobs + MaxButtons;

// These IDs
namespace Mousai
{
enum ParamMapIds {
	// 0 - 47: Knobs/Sliders/Exp Pedal
	LastPossibleKnob = MaxPanelKnobs - 1,

	// 48 - 95: Buttons
	FirstButton = LastPossibleKnob + 1,
	LastButton = LastPossibleKnob + MaxButtons
};

enum InputJackMapIds {
	AudioInputLeft = 0,
	AudioInputRight = 1,

	VoctIn = 2,
	CVInJack1 = 3,
	CVInJack2 = 4,
	CVInJack3 = 5,
	CVInJack4 = 6,

	RandomGateIn = 7,
	SyncIn = 8,
	RecGateIn = 9,
	TrigIn = 10,

};

enum OutputJackMapIds {
	AudioOutputLeft = 0,
	AudioOutputRight = 1,

	LFOOut1 = 2,
	LFOOut2 = 3,
	ClockOut = 4,
};

} // namespace Mousai
