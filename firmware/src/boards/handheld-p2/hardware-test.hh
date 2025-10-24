#pragma once
#include "conf/screen_conf.hh"
#include "controls.hh"

namespace MetaModule
{

void Controls::test_pins() {
	using mdrivlib::GPIO;
	using mdrivlib::PinAF;
	using mdrivlib::PinMode;
	using mdrivlib::PinNum;
	using mdrivlib::PinPolarity;
	using mdrivlib::PinPull;

	mdrivlib::Pin DFU_Button{GPIO::D, PinNum::_8, PinMode::Input, PinAF::AFNone, PinPull::None, PinPolarity::Normal};

	auto pause = [&DFU_Button] {
		// printf("Pausing until DFU button is pressed and released\n");
		// wait until button is pressed
		while (!DFU_Button.is_on())
			;
		// debounce
		HAL_Delay(100);
		// wait until released
		while (DFU_Button.is_on())
			;
		// debounce
		HAL_Delay(100);
	};

	auto toggle_pin = [&](mdrivlib::PinDef pindef) {
		mdrivlib::Pin pin{pindef, PinMode::Output};
		pause();
		for (auto i = 0; i < 10; i++) {
			pin.high();
			HAL_Delay(10);
			pin.low();
			HAL_Delay(10);
		}
	};

	printf("*******************************************\n");
	printf("Press button to toggle PWM pin 10 times\n");
	toggle_pin({GPIO::E, PinNum::_4});
	// mdrivlib::Pin lcd_pwm{GPIO::E, PinNum::_4, PinMode::Output};
	// lcd_pwm.on();

	HAL_Delay(100);

	uint32_t last_read = HAL_GetTick() - 900;

	while (!DFU_Button.is_on()) {
		update_debouncers();

		if (HAL_GetTick() - last_read > 1000) {
			last_read = HAL_GetTick();

			accel.update();

			printf("Encoder 1: %d\n", (int)encoder1.read());
			printf("Encoder 2: %d\n", (int)encoder2.read());
			printf("Encoder 1 but: %d\n", (int)encoder1_but.is_pressed());
			printf("Encoder 2 but: %d\n", (int)encoder2_but.is_pressed());
			printf("Button 1: %d\n", (int)button_1.is_pressed());
			printf("Button 2: %d\n", (int)button_2.is_pressed());
			printf("Button 3: %d\n", (int)button_3.is_pressed());
			printf("Button 4: %d\n", (int)button_4.is_pressed());
			printf("In jack sense: %d\n", (int)sense_in_jack.is_pressed());
			printf("Out jack sense: %d\n", (int)sense_out_jack.is_pressed());

			// auto xyz = accel.read_xyz();
			auto xyz = accel.get_latest();
			printf("Accel: x:%d y:%d z:%d\n", xyz.x, xyz.y, xyz.z);

			printf("\n");
		}
	}
}
} // namespace MetaModule
