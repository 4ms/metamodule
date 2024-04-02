#pragma once

#include "elements.hh"
#include "../mocks/mocks.hh"

namespace LDKit
{

class Controls {

public:
	Controls() = default;

	// Buttons/Switches:
	Mocks::MockedButton ping_button;
	Mocks::MockedButton rev_button;
	Mocks::MockedButton inf_button;
	Mocks::MockedSwitch3Pos time_switch;

	// Trig Jacks
	Mocks::MockedTrigger rev_jack;
	Mocks::MockedTrigger inf_jack;

	// LEDs:
	Mocks::MockedLED ping_led;
	Mocks::MockedLED inf_led;
	Mocks::MockedLED rev_led;

	using SwitchPos = Mocks::SwitchPos;

	uint16_t read_pot(PotAdcElement adcnum) {
		// TODO
		return 0;
	}
	uint16_t read_cv(CVAdcElement adcnum) {
		// TODO
		return 0;
	}

	SwitchPos read_time_switch() {
		return static_cast<SwitchPos>(time_switch.read());
	}

	void start() {
	}

	void update() {
		ping_button.update();
		rev_button.update();
		inf_button.update();

		// ping_jack.update();
		rev_jack.update();
		inf_jack.update();
	}
};
} // namespace LDKit
