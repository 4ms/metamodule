#pragma once
#include "elements.hh"
#include "sampler/mocks/mocks.hh"

namespace SamplerKit
{

class Controls {
public:
	// ADCs (Pots and CV):
	std::array<uint16_t, NumCVs> cvs;
	std::array<uint16_t, NumPots> pots;

	// Buttons/Switches:
	Mocks::Button play_button;
	Mocks::Button rev_button;
	Mocks::Button bank_button;

	// Trig Jacks
	Mocks::TrigIn play_jack;
	Mocks::TrigIn rev_jack;

	Mocks::TrigOut end_out;

	// LEDs:
	struct rgb {
		uint8_t r;
		uint8_t g;
		uint8_t b;
	};
	rgb play_led_data;
	rgb rev_led_data;
	rgb bank_led_data;
	Mocks::RgbLed play_led{play_led_data.r, play_led_data.g, play_led_data.b};
	Mocks::RgbLed rev_led{rev_led_data.r, rev_led_data.g, rev_led_data.b};
	Mocks::RgbLed bank_led{bank_led_data.r, bank_led_data.g, bank_led_data.b};

	Mocks::LED playing_led; //TODO not in Sampler, only STS

	uint32_t sample_rate = 48000;
	uint32_t led_throttle_ctr = 0;

	uint16_t read_pot(PotAdcElement adcnum) {
		return pots[adcnum];
	}

	uint16_t read_cv(CVAdcElement adcnum) {
		return cvs[adcnum];
	}

	void start() {
	}

	void set_samplerate(float sr) {
		sample_rate = std::round(sr);
	}

	void update() {
		play_button.update();
		rev_button.update();
		bank_button.update();
		play_jack.update();
		rev_jack.update();

		uint32_t led_throttle = sample_rate / LEDUpdateRateHz;
		if (led_throttle_ctr++ > led_throttle) {
			led_throttle_ctr = 0;
			play_led.update_animation();
			rev_led.update_animation();
			bank_led.update_animation();
		}
	}
};

} // namespace SamplerKit
