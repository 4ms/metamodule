#pragma once
#include "sdcard.hh"
#include "settings.hh"
#include "str_util.h"
#include "sts_filesystem.hh"

namespace SamplerKit
{

struct UserSettingsStorage {
	UserSettings settings;
	Sdcard &sd;
	Flags &flags;

	enum Settings {
		NoSetting,
		StereoMode,
		RecordSampleBits,
		RecordSampleRate,
		AutoStopSampleChange,
		PlayStopsLengthFull,
		QuantizeChannel1,
		QuantizeChannel2,
		PercEnvelope,
		FadeEnvelope,
		StartUpBank_ch1,
		StartUpBank_ch2,
		TrigDelay,
		FadeUpDownTime,
		AutoIncRecSlot,
		UseCues,
	};

	UserSettingsStorage(Sdcard &sd, Flags &flags)
		: sd{sd}
		, flags{flags} {
		set_default_user_settings();
		read_user_settings();
		settings.update_timing_calcs();
	}

	void handle_events() {
		if (flags.read(Flag::WriteSettingsToSD)) {
			save_user_settings();
			flags.clear(Flag::WriteSettingsToSD);
		}
	}

	void set_default_user_settings() {
		settings.stereo_mode = false;
		settings.auto_stop_on_sample_change = AutoStopMode::Off;
		settings.length_full_start_stop = false;
		settings.quantize = false;
		settings.perc_env = true;
		settings.fadeupdown_env = true;
		settings.startup_bank = 0;
		settings.trig_delay = 8;
		settings.fade_time_ms = 24;
		settings.auto_inc_slot_num_after_rec_trig = false;
		settings.use_cues = false;
	}

	FRESULT save_user_settings() {
		FRESULT res;
		char filepath[255];
		FIL settings_file;

		// Check sys_dir is ok
		res = sd.check_sys_dir();
		if (res != FR_OK)
			return res;

		// Create/overwrite the settings file
		str_cat(filepath, SYS_DIR_SLASH, SETTINGS_FILE);
		res = f_open(&settings_file, filepath, FA_CREATE_ALWAYS | FA_WRITE);
		if (res != FR_OK)
			return (res);

		// Write the header
		f_printf(&settings_file, "##\n");
		f_printf(&settings_file, "## 4ms Stereo Triggered Sampler\n");
		f_printf(&settings_file, "## Settings File\n");
		f_printf(&settings_file, "## http://www.4mscompany.com/sts.php\n");
		f_printf(&settings_file, "##\n");
		f_printf(&settings_file, "## [STEREO MODE] can be \"stereo\" or \"mono\" (default)\n");
		f_printf(&settings_file, "## [RECORD SAMPLE BITS] can be 24 or 16 (default)\n");
		f_printf(&settings_file, "## [RECORD SAMPLE RATE] can be 96k, 88.2k, 48k, or 44.1k (default)\n");
		f_printf(&settings_file,
				 "## [AUTO STOP ON SAMPLE CHANGE] can be \"No\", \"Looping Only\" or \"Yes\" (default)\n");
		f_printf(&settings_file, "## [PLAY BUTTON STOPS WITH LENGTH AT FULL] can be \"No\" or \"Yes\" (default)\n");
		f_printf(&settings_file, "## [QUANTIZE CHANNEL 1 1V/OCT JACK] can be \"Yes\" or \"No\" (default)\n");
		f_printf(&settings_file, "## [QUANTIZE CHANNEL 2 1V/OCT JACK] can be \"Yes\" or \"No\" (default)\n");
		f_printf(&settings_file, "## [SHORT SAMPLE PERCUSSIVE ENVELOPE] can be \"No\" or \"Yes\" (default)\n");
		f_printf(&settings_file, "## [CROSSFADE SAMPLE END POINTS] can be \"No\" or \"Yes\" (default)\n");
		f_printf(&settings_file,
				 "## [STARTUP BANK CHANNEL 1] can be a number between 0 and 59 (default is 0, which is the White "
				 "bank)\n");
		f_printf(&settings_file,
				 "## [STARTUP BANK CHANNEL 2] can be a number between 0 and 59 (default is 0, which is the White "
				 "bank)\n");
		f_printf(&settings_file,
				 "## [TRIG DELAY] can be a number between 1 and 10 which translates to a delay between 0.5ms and 20ms, "
				 "respectively (default is 5)\n");
		f_printf(&settings_file,
				 "## [FADE TIME] can be a number between 0 and 255 which sets the fade in/out time in milliseconds. "
				 "(0 is actually 0.36ms, and 255 is 255ms. Default is 24)\n");
		f_printf(&settings_file, "## [AUTO INCREMENT REC SLOT ON TRIG] can be \"Yes\" or \"No\" (default)\n");
		f_printf(&settings_file, "## [USE CUES] can be \"Yes\" or \"No\" (default)\n");
		f_printf(&settings_file, "##\n");
		f_printf(&settings_file, "## Deleting this file will restore default settings\n");
		f_printf(&settings_file, "##\n\n");

		// Write the stereo mode setting
		f_printf(&settings_file, "[STEREO MODE]\n");

		if (settings.stereo_mode)
			f_printf(&settings_file, "stereo\n\n");
		else
			f_printf(&settings_file, "mono\n\n");

		// Write the 24bit record mode setting
		f_printf(&settings_file, "[RECORD SAMPLE BITS]\n");

		if (settings.rec_24bits)
			f_printf(&settings_file, "24\n\n");
		else
			f_printf(&settings_file, "16\n\n");

		// Write the record sample rate setting
		f_printf(&settings_file, "[RECORD SAMPLE RATE]\n");

		if (settings.record_sample_rate == 48000)
			f_printf(&settings_file, "48k\n\n");
		else if (settings.record_sample_rate == 88200)
			f_printf(&settings_file, "88.2k\n\n");
		else if (settings.record_sample_rate == 96000)
			f_printf(&settings_file, "96k\n\n");
		else
			f_printf(&settings_file, "44.1k\n\n");

		// Write the Auto Stop on Sample Change mode setting
		f_printf(&settings_file, "[AUTO STOP ON SAMPLE CHANGE]\n");

		if (settings.auto_stop_on_sample_change == AutoStopMode::Always)
			f_printf(&settings_file, "Yes\n\n");
		else if (settings.auto_stop_on_sample_change == AutoStopMode::Off)
			f_printf(&settings_file, "No\n\n");
		else if (settings.auto_stop_on_sample_change == AutoStopMode::Looping)
			f_printf(&settings_file, "Looping Only\n\n");

		// Write the Auto Stop on Sample Change mode setting
		f_printf(&settings_file, "[PLAY BUTTON STOPS WITH LENGTH AT FULL]\n");

		if (settings.length_full_start_stop)
			f_printf(&settings_file, "Yes\n\n");
		else
			f_printf(&settings_file, "No\n\n");

		// Write the Quantize Channel 1 setting
		f_printf(&settings_file, "[QUANTIZE CHANNEL 1 1V/OCT JACK]\n");

		if (settings.quantize)
			f_printf(&settings_file, "Yes\n\n");
		else
			f_printf(&settings_file, "No\n\n");

		// Write the Quantize Channel 2 setting
		f_printf(&settings_file, "[QUANTIZE CHANNEL 2 1V/OCT JACK]\n");

		if (settings.quantize)
			f_printf(&settings_file, "Yes\n\n");
		else
			f_printf(&settings_file, "No\n\n");

		// Write the Perc Envelope setting
		f_printf(&settings_file, "[SHORT SAMPLE PERCUSSIVE ENVELOPE]\n");

		if (settings.perc_env)
			f_printf(&settings_file, "Yes\n\n");
		else
			f_printf(&settings_file, "No\n\n");

		// Write the Fade Up/Down Envelope setting
		f_printf(&settings_file, "[CROSSFADE SAMPLE END POINTS]\n");

		if (settings.fadeupdown_env)
			f_printf(&settings_file, "Yes\n\n");
		else
			f_printf(&settings_file, "No\n\n");

		// Write the Channel 1 startup bank setting
		f_printf(&settings_file, "[STARTUP BANK CHANNEL 1]\n");
		f_printf(&settings_file, "%d\n\n", settings.startup_bank);

		// Write the Channel 2 startup bank setting
		f_printf(&settings_file, "[STARTUP BANK CHANNEL 2]\n");
		f_printf(&settings_file, "%d\n\n", settings.startup_bank);

		// Write the Trig Delay setting
		f_printf(&settings_file, "[TRIG DELAY]\n");
		f_printf(&settings_file, "%d\n\n", settings.trig_delay);

		// Write the Trig Delay setting
		f_printf(&settings_file, "[FADE TIME]\n");
		f_printf(&settings_file, "%d\n\n", settings.fade_time_ms);

		// Write Auto Inc Rec Slot setting
		f_printf(&settings_file, "[AUTO INCREMENT REC SLOT ON TRIG]\n");
		f_printf(&settings_file, "%s\n\n", settings.auto_inc_slot_num_after_rec_trig ? "Yes" : "No");

		// Write Cues setting
		f_printf(&settings_file, "[USE CUES]\n");
		f_printf(&settings_file, "%s\n\n", settings.use_cues ? "Yes" : "No");

		res = f_close(&settings_file);

		return res;
	}

	bool read_user_settings(void) {
		FRESULT res;
		char filepath[FF_MAX_LFN];
		char read_buffer[255];
		FIL settings_file;
		uint8_t cur_setting_found;

		// Check sys_dir is ok
		res = sd.check_sys_dir();
		if (res != FR_OK)
			return false;

		// Open the settings file read-only
		str_cat(filepath, SYS_DIR_SLASH, SETTINGS_FILE);
		res = f_open(&settings_file, filepath, FA_READ);
		if (res != FR_OK)
			return false;

		cur_setting_found = NoSetting;
		while (!f_eof(&settings_file)) {
			// Read next line
			if (f_gets(read_buffer, 255, &settings_file) == 0)
				return false;

			// Ignore lines starting with #
			if (read_buffer[0] == '#')
				continue;

			// Ignore blank lines
			if (read_buffer[0] == 0)
				continue;

			// Remove /n from buffer
			read_buffer[str_len(read_buffer) - 1] = 0;

			// Look for a settings section header
			if (read_buffer[0] == '[') {
				if (str_startswith_nocase(read_buffer, "[STEREO MODE]")) {
					cur_setting_found = StereoMode; // stereo mode section detected
					continue;
				}

				if (str_startswith_nocase(read_buffer, "[RECORD SAMPLE BITS]")) {
					cur_setting_found = RecordSampleBits; // 24bit recording mode section detected
					continue;
				}

				if (str_startswith_nocase(read_buffer, "[RECORD SAMPLE RATE")) {
					cur_setting_found = RecordSampleRate; // Sample rate section detected
					continue;
				}

				if (str_startswith_nocase(read_buffer, "[AUTO STOP ON SAMPLE CHANGE]")) {
					cur_setting_found = AutoStopSampleChange; // Auto Stop Mode section detected
					continue;
				}

				if (str_startswith_nocase(read_buffer, "[PLAY BUTTON STOPS WITH LENGTH AT FULL]")) {
					cur_setting_found = PlayStopsLengthFull;
					continue;
				}
				if (str_startswith_nocase(read_buffer, "[QUANTIZE CHANNEL 1")) {
					cur_setting_found = QuantizeChannel1;
					continue;
				}
				if (str_startswith_nocase(read_buffer, "[QUANTIZE CHANNEL 2")) {
					cur_setting_found = QuantizeChannel2;
					continue;
				}
				if (str_startswith_nocase(read_buffer, "[SHORT SAMPLE PERCUSSIVE ENVELOPE")) {
					cur_setting_found = PercEnvelope;
					continue;
				}
				if (str_startswith_nocase(read_buffer, "[CROSSFADE SAMPLE END POINTS")) {
					cur_setting_found = FadeEnvelope;
					continue;
				}
				if (str_startswith_nocase(read_buffer, "[STARTUP BANK CHANNEL 1")) {
					cur_setting_found = StartUpBank_ch1;
					continue;
				}
				if (str_startswith_nocase(read_buffer, "[STARTUP BANK CHANNEL 2")) {
					cur_setting_found = StartUpBank_ch2;
					continue;
				}
				if (str_startswith_nocase(read_buffer, "[TRIG DELAY")) {
					cur_setting_found = TrigDelay;
					continue;
				}

				if (str_startswith_nocase(read_buffer, "[FADE TIME")) {
					cur_setting_found = FadeUpDownTime;
					continue;
				}

				if (str_startswith_nocase(read_buffer, "[AUTO INCREMENT REC SLOT ON TRIG")) {
					cur_setting_found = AutoIncRecSlot;
					continue;
				}

				if (str_startswith_nocase(read_buffer, "[USE CUES")) {
					cur_setting_found = UseCues;
					continue;
				}
			}

			// Look for setting values

			if (cur_setting_found == StereoMode) {
				if (str_startswith_nocase(read_buffer, "stereo"))
					settings.stereo_mode = 1;
				else if (str_startswith_nocase(read_buffer, "mono"))
					settings.stereo_mode = 0;

				cur_setting_found = NoSetting; // back to looking for headers
			}

			if (cur_setting_found == RecordSampleBits) {
				if (str_startswith_nocase(read_buffer, "24"))
					settings.rec_24bits = 1;
				else
					// if (str_startswith_nocase(read_buffer, "16"))
					settings.rec_24bits = 0;

				cur_setting_found = NoSetting; // back to looking for headers
			}

			if (cur_setting_found == RecordSampleRate) {
				// FIXME: only supports 48k right now
				//  if (str_startswith_nocase(read_buffer, "48"))
				settings.record_sample_rate = 48000;
				// else if (str_startswith_nocase(read_buffer, "88"))
				// 	settings.record_sample_rate = 88200;
				// else if (str_startswith_nocase(read_buffer, "96"))
				// 	settings.record_sample_rate = 96000;
				// else
				// 	settings.record_sample_rate = 44100;

				cur_setting_found = NoSetting; // back to looking for headers
			}

			if (cur_setting_found == AutoStopSampleChange) {
				if (str_startswith_nocase(read_buffer, "Yes"))
					settings.auto_stop_on_sample_change = AutoStopMode::Always;
				else if (str_startswith_nocase(read_buffer, "Looping Only"))
					settings.auto_stop_on_sample_change = AutoStopMode::Looping;
				else
					settings.auto_stop_on_sample_change = AutoStopMode::Off;

				cur_setting_found = NoSetting; // back to looking for headers
			}

			if (cur_setting_found == PlayStopsLengthFull) {
				if (str_startswith_nocase(read_buffer, "Yes"))
					settings.length_full_start_stop = 1;
				else
					settings.length_full_start_stop = 0;

				cur_setting_found = NoSetting; // back to looking for headers
			}

			if (cur_setting_found == QuantizeChannel1) {
				if (str_startswith_nocase(read_buffer, "Yes"))
					settings.quantize = 1;
				else
					settings.quantize = 0;

				cur_setting_found = NoSetting; // back to looking for headers
			}

			if (cur_setting_found == QuantizeChannel2) {
				if (str_startswith_nocase(read_buffer, "Yes"))
					settings.quantize = 1;
				else
					settings.quantize = 0;

				cur_setting_found = NoSetting; // back to looking for headers
			}

			if (cur_setting_found == PercEnvelope) {
				// Use FadeUpDownTime to set PercEnvelope
				// if (str_startswith_nocase(read_buffer, "Yes"))
				// 	settings.perc_env = 1;
				// else
				// 	settings.perc_env = 0;

				cur_setting_found = NoSetting; // back to looking for headers
			}

			if (cur_setting_found == FadeEnvelope) {
				// Use FadeUpDownTime to set FadeEnvelope
				// if (str_startswith_nocase(read_buffer, "Yes"))
				// 	settings.fadeupdown_env = 1;
				// else
				// 	settings.fadeupdown_env = 0;

				cur_setting_found = NoSetting; // back to looking for headers
			}

			if (cur_setting_found == StartUpBank_ch1) {
				settings.startup_bank = str_xt_int(read_buffer);

				cur_setting_found = NoSetting; // back to looking for headers
			}
			if (cur_setting_found == StartUpBank_ch2) {
				settings.startup_bank = str_xt_int(read_buffer);

				cur_setting_found = NoSetting; // back to looking for headers
			}

			if (cur_setting_found == TrigDelay) {
				settings.trig_delay = str_xt_int(read_buffer);
				if (settings.trig_delay < 1 || settings.trig_delay > 20)
					settings.trig_delay = 8;

				cur_setting_found = NoSetting; // back to looking for headers
			}

			if (cur_setting_found == FadeUpDownTime) {
				settings.fade_time_ms = str_xt_int(read_buffer);
				if (settings.fade_time_ms < 0 || settings.fade_time_ms > 255)
					settings.fade_time_ms = 24;

				settings.fadeupdown_env = (settings.fade_time_ms > 0);
				settings.perc_env = (settings.fade_time_ms > 0);

				cur_setting_found = NoSetting; // back to looking for headers
			}

			if (cur_setting_found == AutoIncRecSlot) {
				settings.auto_inc_slot_num_after_rec_trig = (str_startswith_nocase(read_buffer, "Yes")) ? 1 : 0;

				cur_setting_found = NoSetting; // back to looking for headers
			}

			if (cur_setting_found == UseCues) {
				settings.use_cues = (str_startswith_nocase(read_buffer, "Yes")) ? 1 : 0;

				cur_setting_found = NoSetting; // back to looking for headers
			}
		}

		res = f_close(&settings_file);
		return res == FR_OK;
	}
};
} // namespace SamplerKit
