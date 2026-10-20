#pragma once
#include "console.hh"
#include "params/metaparams.hh"
#include <cstdint>

namespace MetaModule
{

// Navigate the GUI with keys typed into the serial console (alongside the hardware controls).
// Same keys as the simulator:
//   Right / Left arrow (or d / a): turn the encoder
//   Enter (or Down arrow, s):      click the encoder
//   Backspace (or Up arrow, w):    Back button
class ConsoleKeys {
public:
	// Call often: the UART's RX FIFO only holds 8 characters (an arrow key is 3)
	void poll() {
		uint8_t c;
		while (A35Console::receive(c))
			parse(c);
	}

	// Call before each GUI page update, after the GUI reads the params from the audio (which
	// overwrite the button states): each click or Back is a press for one update, and a release
	// for the next. Between clicks, the button states are left alone, so the hardware buttons work.
	void update(MetaParams &m) {
		if (encoder_pressed) {
			m.rotary_button.set_state_no_events(1);
			m.rotary_button.register_state(0);
			encoder_pressed = false;
		} else if (clicks) {
			clicks--;
			m.rotary_button.register_state(1);
			encoder_pressed = true;
		}

		if (back_pressed) {
			m.meta_buttons[0].set_state_no_events(1);
			m.meta_buttons[0].register_state(0);
			back_pressed = false;
		} else if (backs) {
			backs--;
			m.meta_buttons[0].register_state(1);
			back_pressed = true;
		}

		if (turns) {
			m.rotary.add_motion({.abs_pos = 0, .motion = turns});
			turns = 0;
		}
	}

private:
	int32_t turns = 0;
	unsigned clicks = 0;
	unsigned backs = 0;
	bool encoder_pressed = false;
	bool back_pressed = false;

	enum class Escape { None, Esc, Csi } escape = Escape::None;
	uint8_t last_key = 0;

	void parse(uint8_t c) {
		switch (escape) {
			case Escape::None:
				if (c == 0x1B)
					escape = Escape::Esc;
				else
					key(c);
				break;

			case Escape::Esc:
				escape = (c == '[' || c == 'O') ? Escape::Csi : Escape::None;
				break;

			case Escape::Csi:
				// Arrow keys: ESC [ A/B/C/D
				escape = Escape::None;
				if (c == 'A')
					key('w');
				else if (c == 'B')
					key('s');
				else if (c == 'C')
					key('d');
				else if (c == 'D')
					key('a');
				break;
		}
	}

	void key(uint8_t c) {
		// Enter is \r, \n, or \r\n depending on the terminal
		bool is_crlf = (c == '\n' && last_key == '\r');
		last_key = c;
		if (is_crlf)
			return;

		switch (c) {
			case 'd':
			case 'D':
				turns++;
				break;

			case 'a':
			case 'A':
				turns--;
				break;

			case '\r':
			case '\n':
			case 's':
			case 'S':
				clicks++;
				break;

			case 0x7F: // Backspace (most terminals)
			case 0x08: // Backspace (some terminals), Ctrl-H
			case 'w':
			case 'W':
				backs++;
				break;
		}
	}
};

} // namespace MetaModule
