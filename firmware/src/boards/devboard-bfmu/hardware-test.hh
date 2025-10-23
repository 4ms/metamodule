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
			HAL_Delay(1);
			pin.low();
			HAL_Delay(1);
		}
	};

	for (int j = 0; j < 10; j++) {

		printf("*******************************************\n");
		printf("Testing pins. Press and release USB DFU button after each step to continue\n");
		printf("Press DFU button now to start\n");
		pause();

		printf("Clock out will pulse 10 times\n");
		toggle_pin(ControlPins::clock_out);

		printf("Haptic out will pulse 10 times\n");
		toggle_pin(ControlPins::haptic_out);

		printf("Neopixel A out will pulse 10 times\n");
		toggle_pin(ControlPins::neopixel_a);

		printf("Neopixel B out will pulse 10 times\n");
		toggle_pin(ControlPins::neopixel_b);

		printf("Neopixel VU out will pulse 10 times\n");
		toggle_pin(ControlPins::neopixel_vu);

		printf("CV DAC Out 1 will pulse 10 times\n");
		toggle_pin(ControlPins::cv_out_1);

		printf("CV DAC Out 2 will pulse 10 times\n");
		toggle_pin(ControlPins::cv_out_2);

		printf("Button/LED GPIO Expander I2C bus SCL pin will toggle 10 times\n");
		toggle_pin(ButtonLedExpander::i2c_conf.SCL);

		printf("Button/LED GPIO Expander I2C bus SDA pin will toggle 10 times\n");
		toggle_pin(ButtonLedExpander::i2c_conf.SDA);

		printf("MUX selector pin A will toggle 10 times\n");
		toggle_pin(ADCs::mux_a);

		printf("MUX selector pin B will toggle 10 times\n");
		toggle_pin(ADCs::mux_b);

		printf("MUX selector pin C will toggle 10 times\n");
		toggle_pin(ADCs::mux_c);

		printf("SPI SCLK will toggle 10 times\n");
		toggle_pin(ScreenConf::ScreenSpiConf::SCLK);

		printf("SPI Data (MOSI) will toggle 10 times\n");
		toggle_pin(ScreenConf::ScreenSpiConf::COPI);

		printf("SPI CS will toggle 10 times\n");
		toggle_pin(ScreenConf::ScreenSpiConf::CS0);

		printf("SPI D/C will toggle 10 times\n");
		toggle_pin(ScreenConf::DCPinDef);

		printf("SPI Reset will toggle 10 times\n");
		toggle_pin(ScreenConf::ResetPin);

		printf("MIDI TX will send bytes: 0x90 0x55 0x11 0x80 0x55 0x00\n");
		pause();
		uart_midi.transmit(0x90);
		uart_midi.transmit(0x55);
		uart_midi.transmit(0x11);
		uart_midi.transmit(0x80);
		uart_midi.transmit(0x55);
		uart_midi.transmit(0x00);

		///////////////////////////////
		// Inputs

		printf("Will print the state of all inputs once per second\n");
		printf("Press button now to start. Press and hold it for 1 second to stop\n");
		pause();
		HAL_Delay(100);

		mdrivlib::Pin rand_gate{ControlPins::random_gate_in, PinMode::Input, PinPull::None, PinPolarity::Inverted};
		mdrivlib::Pin trig{ControlPins::trig_in, PinMode::Input, PinPull::None, PinPolarity::Inverted};
		mdrivlib::Pin sync{ControlPins::sync_in, PinMode::Input, PinPull::None, PinPolarity::Inverted};
		mdrivlib::Pin rec_gate{ControlPins::rec_gate_in, PinMode::Input, PinPull::None, PinPolarity::Inverted};

		mdrivlib::Pin encoder1a{ControlPins::encoders[0].A, PinMode::Input, PinPull::Up, PinPolarity::Normal};
		mdrivlib::Pin encoder1b{ControlPins::encoders[0].B, PinMode::Input, PinPull::Up, PinPolarity::Normal};
		mdrivlib::Pin encoder2a{ControlPins::encoders[1].A, PinMode::Input, PinPull::Up, PinPolarity::Normal};
		mdrivlib::Pin encoder2b{ControlPins::encoders[1].B, PinMode::Input, PinPull::Up, PinPolarity::Normal};

		mdrivlib::Pin MIDI_rx{ControlPins::MIDI_Uart.RXPin, PinMode::Input, PinPull::None, PinPolarity::Normal};

		mdrivlib::Pin gpio_exp_irq{ButtonLedExpander::irq_pin, PinMode::Input, PinPull::None, PinPolarity::Normal};

		while (!DFU_Button.is_on()) {
			printf("Rand gate: %d\n", rand_gate.is_on());
			printf("Trig: %d\n", trig.is_on());
			printf("Sync: %d\n", sync.is_on());
			printf("Rec gate: %d\n", rec_gate.is_on());
			printf("Encoder 1 Pin A: %d Pin B: %d\n", encoder1a.is_on(), encoder1b.is_on());
			printf("Encoder 2 Pin A: %d Pin B: %d\n", encoder2a.is_on(), encoder2b.is_on());

			printf("MIDI RX pin (raw pin, not decoded) %d\n", MIDI_rx.is_on());

			printf("GPIO expander IRQ pin %d\n", MIDI_rx.is_on());

			printf("ADC Mux1 = %u\n", pot_vals[ADCs::Mux1]);
			printf("ADC Mux2 = %u\n", pot_vals[ADCs::Mux2]);
			printf("ADC Mux3 = %u\n", pot_vals[ADCs::Mux3]);
			printf("ADC Mux4 = %u\n", pot_vals[ADCs::Mux4]);
			printf("ADC Mux5 = %u\n", pot_vals[ADCs::Mux5]);
			printf("ADC Voct = %u\n", pot_vals[ADCs::VOct]);
			printf("ADC CV1 = %u\n", pot_vals[ADCs::CV1]);
			printf("ADC CV2 = %u\n", pot_vals[ADCs::CV2]);
			printf("ADC CV3 = %u\n", pot_vals[ADCs::CV3]);
			printf("ADC CV4 = %u\n", pot_vals[ADCs::CV4]);

			HAL_Delay(1000);
		}
	}
}
} // namespace MetaModule
