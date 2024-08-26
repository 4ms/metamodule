#pragma once
#include "controls.hh"
#include "flags.hh"
// #include "log.hh"
#include "pot_state.hh"
#include "settings.hh"
// #include "util/voct_calibrator.hh"

namespace SamplerKit
{

struct ButtonActionHandler {
	Flags &flags;
	Controls &controls;
	UserSettings &settings;
	std::array<PotState, NumPots> &pot_state;

	bool ignore_bank_release = false;
	bool ignore_rev_release = false;
	bool ignore_play_release = false;

	static constexpr uint32_t short_press = AudioStreamConf::FrameRate * 0.6f;
	static constexpr uint32_t half_sec = AudioStreamConf::FrameRate * 0.5f;
	static constexpr uint32_t one_sec = AudioStreamConf::FrameRate;
	static constexpr uint32_t two_sec = AudioStreamConf::FrameRate * 2.f;
	static constexpr uint32_t three_sec = AudioStreamConf::FrameRate * 3.f;

	ButtonActionHandler(Flags &flags,
						Controls &controls,
						std::array<PotState, NumPots> &pot_state,
						UserSettings &settings)
		: flags{flags}
		, controls{controls}
		, settings{settings}
		, pot_state{pot_state} {
	}

	// TODO: put all button ops in process() and check in each button combo for op_mode
	void process(OperationMode op_mode, bool looping) {
		switch (op_mode) {
			case OperationMode::CVCalibrate:
				process_cvcal_mode();
				break;

			case OperationMode::SystemMode:
				break;

			case OperationMode::Playback:
				process_play_mode(looping);
				break;

			case OperationMode::Record:
				process_rec_mode();
				break;
		}
	}

	void process_play_mode(bool looping) {
		if (controls.play_button.is_just_pressed()) {
			if (!controls.rev_button.is_pressed() && !controls.bank_button.is_pressed()) {
				if (!looping)
					flags.set(Flag::PlayBut);
			}
		}

		if (controls.play_button.is_just_released()) {
			if (looping && !ignore_play_release) {
				flags.set(Flag::PlayBut);
			}

			ignore_play_release = false;
		}

		// Long hold Play and Rev to toggle Rec/Play mode
		if (!ignore_rev_release && controls.rev_button.how_long_held_pressed() > two_sec) {
			if (!ignore_play_release && controls.play_button.how_long_held_pressed() > two_sec) {
				if (!controls.bank_button.is_pressed()) {
					flags.set(Flag::EnterRecordMode);
					ignore_play_release = true;
					ignore_rev_release = true;
				}
			}
		}

		// Hold Play to toggle looping
		if (!ignore_play_release && controls.play_button.how_long_held_pressed() > short_press) {
			if (!controls.rev_button.is_pressed() && !controls.bank_button.is_pressed()) {
				flags.set(Flag::ToggleLooping);
				ignore_play_release = true;
			}
		}

		// Long hold Bank + Rev for CV Calibration
		if (!ignore_bank_release && controls.bank_button.how_long_held_pressed() > one_sec) {
			if (!ignore_rev_release && controls.rev_button.how_long_held_pressed() > one_sec) {
				if (!controls.play_button.is_pressed()) {
					flags.set(Flag::EnterCVCalibrateMode);
					ignore_bank_release = true;
					ignore_rev_release = true;
				}
			}
		}

		// Long hold Play + Bank to toggle stereo mode
		if (!ignore_bank_release && controls.bank_button.how_long_held_pressed() > one_sec) {
			if (!ignore_play_release && controls.play_button.how_long_held_pressed() > one_sec) {
				if (!controls.rev_button.is_pressed()) {
					flags.set(Flag::ToggleStereoMode);
					ignore_bank_release = true;
					ignore_play_release = true;
				}
			}
		}

		// Long hold Play + Bank + Rev to save index
		if (!ignore_bank_release && controls.bank_button.how_long_held_pressed() > three_sec) {
			if (!ignore_rev_release && controls.rev_button.how_long_held_pressed() > three_sec) {
				if (!ignore_play_release && controls.play_button.how_long_held_pressed() > three_sec) {
					flags.set(Flag::WriteIndexToSD);
					flags.set(Flag::WriteSettingsToSD);
					ignore_bank_release = true;
					ignore_play_release = true;
					ignore_rev_release = true;
				}
			}
		}

		// Bank -> change bank
		if (controls.bank_button.is_just_released()) {
			flags.set(Flag::BankReleased);

			if (!ignore_bank_release) {
				if (controls.rev_button.is_pressed()) {
					flags.set(Flag::BankPrev);
					ignore_rev_release = true;
				} else {
					flags.set(Flag::BankNext);
				}
			}

			for (auto &pot : pot_state) {
				if (pot.moved_while_bank_down)
					pot.is_catching_up = true;
				pot.moved_while_bank_down = false;
			}

			ignore_bank_release = false;
		}

		// Reverse -> toggle
		if (controls.rev_button.is_just_released()) {
			if (!ignore_rev_release) {
				flags.set(Flag::RevTrig);
			}

			for (auto &pot : pot_state) {
				if (pot.moved_while_rev_down)
					pot.is_catching_up = true;
				pot.moved_while_rev_down = false;
			}

			ignore_rev_release = false;
		} else {
			for (auto &pot : pot_state) {
				if (pot.moved_while_rev_down)
					ignore_rev_release = true;
			}
		}
	}

	void process_rec_mode() {
		if (controls.play_button.is_just_pressed()) {
		}

		if (controls.play_button.is_just_released()) {
			if (!ignore_play_release && !controls.rev_button.is_pressed() && !controls.bank_button.is_pressed())
				flags.set(Flag::RecBut);
			ignore_play_release = false;
		}

		// Long hold Play and Rev to toggle Rec/Play mode
		if (!ignore_rev_release && controls.rev_button.how_long_held_pressed() > one_sec) {
			if (!ignore_play_release && controls.play_button.how_long_held_pressed() > one_sec) {
				controls.play_led.reset_breathe();
				flags.set(Flag::EnterPlayMode);
				ignore_play_release = true;
				ignore_rev_release = true;
			}
		}

		if (controls.bank_button.is_just_released()) {
			flags.set(Flag::BankReleased);

			if (!ignore_bank_release) {
				if (controls.rev_button.is_pressed()) {
					flags.set(Flag::BankPrev);
					ignore_rev_release = true;
				} else {
					flags.set(Flag::BankNext);
				}
			}

			for (auto &pot : pot_state) {
				if (pot.moved_while_bank_down)
					pot.is_catching_up = true;
				pot.moved_while_bank_down = false;
			}

			ignore_bank_release = false;
		}

		if (controls.rev_button.is_just_released()) {
			ignore_rev_release = false;
		}
	}

	void process_cvcal_mode() {
		// Bank + Rev to calibrate unpatched reading of non-Pitch CV jacks
		if (controls.rev_button.is_just_released()) {
			if (!ignore_rev_release && controls.bank_button.is_pressed()) {
				flags.set(Flag::CVCalibrateAllJacks);
			}
			ignore_rev_release = false;
		}

		if (controls.bank_button.is_just_released()) {
			if (!ignore_bank_release && controls.rev_button.is_pressed()) {
				flags.set(Flag::CVCalibrateAllJacks);
			}
			ignore_bank_release = false;
		}

		if (controls.play_button.is_just_released()) {
			flags.set(Flag::StepCVCalibration);
			ignore_play_release = false;
		}
	}
};

} // namespace SamplerKit
