#pragma once
#include "bank.hh"
#include "brain_conf.hh"
#include "button_actions.hh"
#include "calibration_storage.hh"
#include "controls.hh"
#include "elements.hh"
#include "flags.hh"
#include "leds.hh"
#include "lut/pitch_pot_lut.h"
#include "lut/voltoct.h"
#include "pot_state.hh"
#include "sample_pot_detents.hh"
#include "settings.hh"
#include "tuning_calcs.hh"
#include "util/colors.hh"
#include "util/countzip.hh"
#include "util/math.hh"
#ifndef METAMODULE
#include "cv_calibration.hh"
#endif

namespace SamplerKit
{

// Params holds all the modes, settings and parameters for the sampler
// Params are set by controls (knobs, jacks, buttons, etc)
struct Params {

	Controls &controls;
	Flags &flags;
	UserSettings &settings;
	BankManager &banks;

	CalibrationStorage &cal_storage;
	CalibrationData &calibration{cal_storage.cal_data};
#ifndef METAMODULE
	CVCalibrator cv_cal{flags};
#endif

	Leds leds{flags, controls};
	ButtonActionHandler button_handler{flags, controls, pot_state, settings};

	uint32_t bank = 0;
	uint32_t sample = 0;
	bool reverse = 0;
	bool looping = 0;

	float pitch = 1.0f;
	float start = 0.f;
	float length = 1.f;
	float volume = 1.f;

	float bank_cv_sel = 0.f;

	uint32_t display_bank = 0;
	bool is_hovering = false;

	// These are what's playing, even if the controls have selected something else
	uint8_t sample_num_now_playing = 0;
	uint8_t sample_bank_now_playing = 0;

	uint32_t play_trig_timestamp = 0;
	int32_t voct_latch_value = 0;

	uint32_t bank_button_sel = 0;

	PlayStates play_state = PlayStates::SILENT;
	RecStates rec_state = RecStates::REC_OFF;

	OperationMode op_mode = OperationMode::Playback;

	Params(
		Controls &controls, Flags &flags, UserSettings &settings, BankManager &banks, CalibrationStorage &cal_storage)
		: controls{controls}
		, flags{flags}
		, settings{settings}
		, banks{banks}
		, cal_storage{cal_storage} {

		controls.bank_led.set_color_calibration(calibration.bank_rgb_adj);
		controls.play_led.set_color_calibration(calibration.play_rgb_adj);
		controls.rev_led.set_color_calibration(calibration.rev_rgb_adj);
		controls.start();
	}

	uint32_t time;

	uint32_t get_time() {
		return time;
	}

	void update(uint32_t time) {
		this->time = time;

		controls.update();

		update_endout_jack();
		update_trig_jacks();

		update_pot_states();
		update_cv_states();

		update_bank_button();

		update_length();
		update_startpos();
		update_sample();
		update_pitch();

		update_bank_cv();
		update_hover_bank();
		combine_bank_sels();

		button_handler.process(op_mode, looping);

#ifndef METAMODULE
		update_cv_cal();
#endif

		leds.update({op_mode, play_state, rec_state, reverse, looping, display_bank, settings.stereo_mode}, time);
	}

	void startup_animation() {
		controls.update();
		leds.animate_startup();
	}

private:
	void update_pitch() {
		auto &pot = pot_state[PitchPot];
		auto potval = std::clamp(pot.cur_val + (int16_t)calibration.pitch_pot_detent_offset, 0, 4095);

		// Flag::LatchVoltOctCV is set after a Play Trig happens
		// and the current CV value is stored into voct_latch_value.
		// After a delay, the latch flag is released and playback begins
		int16_t pitch_cv;
		if (flags.read(Flag::LatchVoltOctCV))
			pitch_cv = voct_latch_value;
		else
			pitch_cv = cv_state[PitchCV].cur_val;

		pitch_cv = MathTools::plateau<12, 2048>(pitch_cv) + 2048;

		uint32_t compensated_pitch_cv = TuningCalcs::apply_tracking_compensation(pitch_cv, calibration.tracking_comp);

		if (settings.quantize)
			pitch = pitch_pot_lut[potval] * TuningCalcs::quantized_semitone_voct(compensated_pitch_cv);
		else
			pitch = pitch_pot_lut[potval] * voltoct[compensated_pitch_cv];
	}

	void update_length() {
		auto &pot = pot_state[LengthPot];
		float potval;

		potval = (pot.moved_while_bank_down || pot.moved_while_rev_down || pot.is_catching_up) ? pot.latched_val :
																								 pot.cur_val;

		// Bank + Length handled in update_hover_bank()

		if (pot.moved_while_rev_down && !pot.moved_while_bank_down) {
			// Rev + Length = envelope fade time
			settings.fade_time_ms = pot.cur_val / 102.4f; // 0..40ms
			settings.update_fade_rates();

			// disable envelopes when setting is close to zero
			settings.perc_env = settings.perc_env ? (pot.cur_val > 30) : (pot.cur_val > 40);
			settings.fadeupdown_env = settings.perc_env;
		}

		length = (potval + cv_state[LengthCV].cur_val) / 4096.f;
		if (length < 0.005f)
			length = 0.005f;
		if (length > 0.990f)
			length = 1.f;
	}

	void update_startpos() {
		auto &pot = pot_state[StartPot];

		float pot_start;

		if (pot.moved_while_rev_down) {
			// Rev + StartPos = Volume
			pot_start = pot.latched_val;
			volume = pot.cur_val / 4095.f;
		} else {
			pot_start = pot.is_catching_up ? pot.latched_val : pot.cur_val;
		}

		start = (pot_start + cv_state[StartCV].cur_val) / 4096.f;
		if (start < 0.01f)
			start = 0.f;
		if (start > 0.99f)
			start = 1.f;
	}

	void update_sample() {
		auto &pot = pot_state[SamplePot];

		// Sample pot does not do catch-up mode
		float potval = (pot.moved_while_bank_down) ? pot.latched_val : pot.cur_val;

		auto new_sample = detent_num_antihys(potval + cv_state[SampleCV].cur_val, sample);
		if (new_sample != sample) {
			sample = new_sample;
			flags.set(Flag::PlaySampleChanged);
		}
	}

	void update_pot_states() {
		for (auto [i, pot] : enumerate(pot_state)) {
			pot.cur_val = (int16_t)controls.read_pot(static_cast<PotAdcElement>(i));

			int16_t diff = std::abs(pot.cur_val - pot.prev_val);
			if (diff > Brain::MinPotChange) {
				pot.track_moving_ctr = 50;
			}

			if (pot.track_moving_ctr) {
				pot.track_moving_ctr--;

				if (controls.rev_button.is_pressed()) {
					if (!pot.moved_while_rev_down && !pot.is_catching_up)
						pot.latched_val = pot.prev_val;

					pot.moved_while_rev_down = true;
					if (i == StartPot)
						button_handler.ignore_rev_release = true;
				}

				if (controls.bank_button.is_pressed()) {
					if (!pot.moved_while_bank_down && !pot.is_catching_up)
						pot.latched_val = pot.prev_val;

					pot.moved_while_bank_down = true;
					button_handler.ignore_bank_release = true;
				}

				if (pot.is_catching_up && std::abs(pot.latched_val - pot.cur_val) < (Brain::MinPotChange * 2))
					pot.is_catching_up = false;

				pot.delta = diff;
				pot.prev_val = pot.cur_val;
			}
		}
	}

	void update_cv_states() {
		for (auto [i, cv] : enumerate(cv_state)) {
			cv.cur_val = (int16_t)controls.read_cv(static_cast<CVAdcElement>(i));
			if (op_mode != OperationMode::CVCalibrate)
				cv.cur_val += calibration.cv_calibration_offset[i];

			int16_t diff = std::abs(cv.cur_val - cv.prev_val);
			if (diff > Brain::MinCVChange) {
				cv.delta = diff;
				cv.prev_val = cv.cur_val;
			}
		}
	}

	void update_trig_jacks() {
		if (op_mode == OperationMode::Playback) {
			if (controls.play_jack.is_just_pressed()) {
				if (play_state == PlayStates::PLAYING)
					play_state = PlayStates::PLAY_FADEDOWN;

				voct_latch_value = cv_state[PitchCV].cur_val;
				play_trig_timestamp = get_time();
				flags.set(Flag::PlayTrigDelaying);
			}
		}

		if (op_mode == OperationMode::Record) {
			if (controls.play_jack.is_just_pressed()) {
				flags.set(Flag::RecTrig);
			}
		}

		if (controls.rev_jack.is_just_pressed()) {
			flags.set(Flag::RevTrig);
		}
	}

	void update_endout_jack() {
		if (flags.take(Flag::EndOutShort))
			end_out_ctr = 8;

		if (flags.take(Flag::EndOutLong))
			end_out_ctr = 35;

		if (end_out_ctr == 1) {
			controls.end_out.low();
			end_out_ctr = 0;
		} else if (end_out_ctr > 1) {
			controls.end_out.high();
			end_out_ctr--;
		}
	}

	void update_bank_button() {
		if (flags.take(Flag::BankNext)) {
			if (op_mode == OperationMode::Playback)
				bank_button_sel = banks.next_enabled_bank(bank_button_sel);
			else
				bank_button_sel = banks.next_bank(bank_button_sel);
		}
		if (flags.take(Flag::BankPrev)) {
			if (op_mode == OperationMode::Playback)
				bank_button_sel = banks.prev_enabled_bank(bank_button_sel);
			else
				bank_button_sel = banks.prev_bank(bank_button_sel);
		}
	}

	// Holding Bank while turning Sample "hovers" over a bank
	// which is selected when Bank is released
	void update_hover_bank() {
		if (auto &pot = pot_state[LengthPot]; pot.moved_while_bank_down) {
			is_hovering = true;
			uint32_t blinks = pot.prev_val / 683; // 0..5
			uint32_t color = display_bank % 10;
			uint32_t test_bank = color + (blinks * 10);
			if (op_mode == OperationMode::Record || banks.is_bank_enabled(test_bank))
				display_bank = test_bank;
		}

		if (auto &pot = pot_state[SamplePot]; pot.moved_while_bank_down) {
			is_hovering = true;
			uint32_t blinks = display_bank / 10;
			uint32_t color = pot.prev_val / 410; // 0..9
			uint32_t test_bank = color + (blinks * 10);
			if (op_mode == OperationMode::Record || banks.is_bank_enabled(test_bank))
				display_bank = test_bank;
		}

		if (flags.take(Flag::BankReleased)) {
			if (is_hovering) {
				is_hovering = false;

				int t_bank = display_bank - (int)(bank_cv_sel + 0.5f);
				if (t_bank < 0)
					t_bank += 60;
				if (t_bank >= 60)
					t_bank -= 60;

				bank_button_sel = t_bank;
			}
		}

		if (!is_hovering) {
			display_bank = bank;
		}
	}

	void update_bank_cv() {
		float new_bank_cv_sel =
			(float)cv_state[BankCV].prev_val / (4096.f - calibration.cv_calibration_offset[BankCV] * 4) * 60.f;

		// TODO: actual anti-hysteresis
		static float last_bank_cv = 0.f;
		if (std::abs(last_bank_cv - new_bank_cv_sel) < 0.15f)
			return;

		last_bank_cv = new_bank_cv_sel;
		bank_cv_sel = new_bank_cv_sel;
	}

	void combine_bank_sels() {
		static int32_t last_t_bank = 0xFFFFFFFF;

		int32_t t_bank = (uint32_t)(bank_cv_sel + 0.5f) + bank_button_sel;
		if (last_t_bank == t_bank)
			return;
		last_t_bank = t_bank;

		if (t_bank >= 60)
			t_bank = t_bank % 60;

		// Allow disabled banks in Record mode
		if (op_mode == OperationMode::Record) {
			bank = t_bank;
			return;
		}

		// Ensure we select an enabled bank
		if (banks.is_bank_enabled(t_bank)) {
			bank = t_bank;
			return;
		}

		int32_t last_bank = banks.prev_enabled_bank(0);
		if (t_bank > last_bank)
			t_bank = t_bank % (last_bank + 1);

		if (banks.is_bank_enabled(t_bank)) {
			bank = t_bank;
			return;
		}

		// Pick nearest of next or prev enabled bank, without wrapping
		int32_t next = banks.next_enabled_bank(t_bank);
		int32_t prev = banks.prev_enabled_bank(t_bank);
		int32_t next_diff = std::abs(next - t_bank);
		int32_t prev_diff = std::abs(t_bank - prev);
		bank = (next_diff < prev_diff) ? next : prev;
	}

#ifndef METAMODULE
	void update_cv_cal() {
		// Handle CV Cal mode
		if (flags.take(Flag::EnterCVCalibrateMode)) {
			cv_cal.reset();
			op_mode = OperationMode::CVCalibrate;
			flags.set(Flag::CVCalibrationStep1Animate);

			flags.clear(Flag::CVCalibrateAllJacks);
		}

		if (op_mode == OperationMode::CVCalibrate)
			cv_cal.update(cv_state[PitchCV].cur_val);

		if (flags.take(Flag::CVCalibrationFail)) {
			op_mode = OperationMode::Playback;
			flags.set(Flag::CVCalibrationFailAnimate);
		}

		if (flags.take(Flag::CVCalibrateAllJacks)) {
			static_assert(PitchCV == 0);
			for (unsigned i = PitchCV + 1; i < NumCVs; i++) {
				if (cv_state[i].cur_val < 100)
					calibration.cv_calibration_offset[i] = -cv_state[i].cur_val;
			}
			flags.set(Flag::CVCalibrateAllJacksAnimate);
			cal_storage.save_flash_params();
			pr_log("Calibrated unpatched CV jacks: Start: %d, Length: %d, Sample: %d, Bank: %d\n",
				   calibration.cv_calibration_offset[StartCV],
				   calibration.cv_calibration_offset[LengthCV],
				   calibration.cv_calibration_offset[SampleCV],
				   calibration.cv_calibration_offset[BankCV]);
		}

		if (flags.take(Flag::CVCalibrationSuccess)) {
			calibration.cv_calibration_offset[PitchCV] = 2048.f - cv_cal.offset();
			calibration.tracking_comp = -cv_cal.slope() / 409.6f;
			op_mode = OperationMode::Playback;
			flags.set(Flag::CVCalibrationSuccessAnimate);
			cal_storage.save_flash_params();
			pr_log("Calibrated tracking = %f, offset = %d\n",
				   (double)calibration.tracking_comp,
				   calibration.cv_calibration_offset[PitchCV]);
		}
	}
#endif

private:
	std::array<PotState, NumPots> pot_state;

	struct CVState {
		int16_t cur_val = 0;
		int16_t prev_val = 0;
		int16_t delta = 0;
	};
	std::array<CVState, NumCVs> cv_state;

	uint32_t end_out_ctr = 0;
};

constexpr auto ParamsSize = sizeof(Params);

} // namespace SamplerKit
