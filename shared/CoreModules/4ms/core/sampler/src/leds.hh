#pragma once

#include "bank_blink.hh"
#include "controls.hh"
#include "flags.hh"
// #include "log.hh"
#include "palette.hh"
#include "settings.hh"

namespace SamplerKit
{
struct Leds {
	Flags &flags;
	Controls &controls;

	Leds(Flags &flags, Controls &controls)
		: flags{flags}
		, controls{controls} {
	}

	struct LedCriteria {
		OperationMode op_mode;
		PlayStates play_state;
		RecStates rec_state;
		bool reverse;
		bool looping;
		uint32_t bank;
		bool stereo_mode;
	};

	Color last_play_color = Colors::off;
	Color last_rev_color = Colors::off;
	Color last_bank_color = Colors::off;

	bool is_writing_index = false;

	void update(LedCriteria state, uint32_t cur_time) {
		const OperationMode &op_mode = state.op_mode;
		const PlayStates &play_state = state.play_state;
		const RecStates &rec_state = state.rec_state;
		const bool &reverse = state.reverse;
		const bool &looping = state.looping;
		const uint32_t &bank = state.bank;
		const bool &stereo_mode = state.stereo_mode;

		Color rev_color;
		Color play_color;
		Color bank_color;

		if (op_mode == OperationMode::Playback) {
			rev_color = reverse ? Colors::blue : Colors::off;

			if (play_state != PlayStates::SILENT && play_state != PlayStates::PREBUFFERING) {
				play_color = stereo_mode ? (looping ? SamplerColors::cyan : SamplerColors::yellow) :
										   (looping ? SamplerColors::blue : SamplerColors::green);
			} else
				play_color = Colors::off;
		}
		if (op_mode == OperationMode::Record) {
			rev_color = Colors::off;
			if (rec_state == RecStates::REC_OFF) {
				play_color = Colors::off;
				if (!flags.read(Flag::EnterPlayMode)) // don't flash is exiting rec mode is pending
					controls.play_led.breathe(Colors::red, 4.f);
			} else {
				play_color = Colors::red;
				controls.play_led.reset_breathe();
			}
		}

		if (op_mode == OperationMode::CVCalibrate) {
			if (flags.take(Flag::CVCalibrationStep1Animate)) {
				rev_color = Colors::blue;
				play_color = Colors::blue;
				bank_color = Colors::blue;
			} else if (flags.take(Flag::CVCalibrationStep2Animate)) {
				rev_color = Colors::purple;
				play_color = Colors::purple;
				bank_color = Colors::purple;
			} else {
				rev_color = last_rev_color;
				play_color = last_play_color;
				bank_color = last_bank_color;
			}
		} else {
			bank_color = blink_bank(bank, cur_time) ? BankColors[bank % 10] : Colors::off;
		}

		if (op_mode == OperationMode::SystemMode) {
			// TODO: calibration and system modes
		}

		// Output to the LEDs
		if (last_play_color != play_color) {
			last_play_color = play_color;
			controls.play_led.set_base_color(play_color);
		}
		if (last_rev_color != rev_color) {
			last_rev_color = rev_color;
			controls.rev_led.set_base_color(rev_color);
		}
		if (last_bank_color != bank_color) {
			last_bank_color = bank_color;
			controls.bank_led.set_base_color(bank_color);
		}

		// Breathe / flash
		if (flags.take(Flag::StartupDone)) {
			controls.bank_led.reset_breathe();
		}

		if (flags.take(Flag::CVCalibrateAllJacksAnimate)) {
			controls.rev_led.fade_once_ms(Colors::green, 500);
			controls.bank_led.fade_once_ms(Colors::green, 500);
		}

		if (flags.take(Flag::CVCalibrationSuccessAnimate)) {
			controls.rev_led.reset_breathe();
			controls.bank_led.reset_breathe();
			controls.rev_led.fade_once_ms(Colors::green, 1000);
			controls.bank_led.fade_once_ms(Colors::green, 1000);
			controls.play_led.fade_once_ms(Colors::green, 1000);
		}
		if (flags.take(Flag::CVCalibrationFailAnimate)) {
			controls.rev_led.reset_breathe();
			controls.bank_led.reset_breathe();
			controls.rev_led.fade_once_ms(Colors::red, 1000);
			controls.bank_led.fade_once_ms(Colors::red, 1000);
			controls.play_led.fade_once_ms(Colors::red, 1000);
		}

		if (flags.take(Flag::ToggleStereoModeAnimate)) {
			if (stereo_mode) {
				// mono->stereo
				controls.rev_led.fade_once_ms(Colors::cyan, 500);
				controls.bank_led.fade_once_ms(Colors::black, 500);
			} else {
				// stereo -> mono
				controls.play_led.fade_once_ms(Colors::white, 500);
			}
		}

		if (!is_writing_index && (flags.read(Flag::WriteSettingsToSD) || flags.read(Flag::WriteIndexToSD))) {
			is_writing_index = true;
			controls.bank_led.fade_once_ms(Colors::white, 200);
			controls.play_led.fade_once_ms(Colors::white, 200);
			controls.rev_led.fade_once_ms(Colors::white, 200);
		} else if (is_writing_index) {
			is_writing_index = false;
			controls.bank_led.reset_breathe();
			controls.play_led.reset_breathe();
			controls.rev_led.reset_breathe();
		}

		// Sample Slot Change
		if (flags.take(Flag::PlaySampleChangedValid))
			controls.play_led.flash_once_ms(Colors::white, 20);
		if (flags.take(Flag::PlaySampleChangedValidBright))
			controls.play_led.flash_once_ms(Colors::white, 120);
		if (flags.take(Flag::PlaySampleChangedEmpty))
			controls.play_led.flash_once_ms(Colors::red, 20);
		if (flags.take(Flag::PlaySampleChangedEmptyBright))
			controls.play_led.flash_once_ms(Colors::red, 120);
	}

	void animate_startup() {
		// Startup sequence
		if (flags.take(Flag::StartupParsing))
			controls.rev_led.flash_once_ms(Colors::yellow, 100);
		if (flags.take(Flag::StartupLoadingIndex)) {
			controls.bank_led.set_base_color(Colors::orange);
			controls.bank_led.breathe(SamplerColors::Bank::purple, 1);
		}
		if (flags.take(Flag::StartupNewIndex)) {
			controls.bank_led.set_base_color(Colors::off);
			controls.bank_led.breathe(Colors::white, 1);
		}
		if (flags.take(Flag::StartupWritingIndex)) {
			controls.bank_led.set_base_color(Colors::off);
			controls.bank_led.breathe(Colors::magenta, 1);
		}
		if (flags.take(Flag::StartupWritingHTML)) {
			controls.bank_led.set_base_color(Colors::off);
			controls.bank_led.breathe(Colors::magenta, 0.5);
		}
	}
};
} // namespace SamplerKit
