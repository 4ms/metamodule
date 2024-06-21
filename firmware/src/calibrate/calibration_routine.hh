#pragma once
#include "calibrate/calibrator.hh"
#include "drivers/cache.hh"
#include "fs/norflash_layout.hh"
#include "gui/helpers/lv_helpers.hh"
#include "gui/slsexport/meta5/ui.h"
#include "gui/styles.hh"
#include "metaparams.hh"
#include "params_state.hh"
#include "patch_file/file_storage_proxy.hh"
#include "patch_play/patch_mod_queue.hh"
#include "util/calibrator.hh"

namespace MetaModule
{

struct CalibrationRoutine {
	enum class JackCalStatus { NotCal, LowOnly, HighOnly, Error, Done };

	CalibrationRoutine(ParamsMidiState &params,
					   MetaParams &metaparams,
					   FileStorageProxy &storage,
					   PatchModQueue &patch_mod_queue)
		: storage{storage}
		, patch_mod_queue{patch_mod_queue}
		, params{params}
		, metaparams{metaparams}
		, measurer{{Calibration::DefaultLowV, Calibration::DefaultHighV, Calibration::from_volts(0.1f)}} {

		for (auto label : input_status_labels) {
			lv_obj_set_style_outline_color(label, Gui::orange_highlight, LV_PART_MAIN);
			lv_obj_set_style_outline_opa(label, LV_OPA_0, LV_PART_MAIN);
			lv_obj_set_style_outline_width(label, 2, LV_PART_MAIN);
			lv_obj_set_style_outline_pad(label, 4, LV_PART_MAIN);
		}

		for (auto label : output_status_labels) {
			lv_obj_set_style_outline_color(label, Gui::orange_highlight, LV_PART_MAIN);
			lv_obj_set_style_outline_opa(label, LV_OPA_0, LV_PART_MAIN);
			lv_obj_set_style_outline_width(label, 2, LV_PART_MAIN);
			lv_obj_set_style_outline_pad(label, 4, LV_PART_MAIN);
		}

		lv_obj_add_event_cb(ui_CalibrationCancelButton, cancel_cb, LV_EVENT_CLICKED, this);
		lv_obj_add_event_cb(ui_CalibrationNextButton, next_cb, LV_EVENT_CLICKED, this);
	}

	void update() {
		if (state == State::Init) {
			patch_mod_queue.put(CalibrationOnOff{.enable = false});
			state = State::CalibratingIns;

		} else if (state == State::CalibratingIns) {
			update_cal_ins_routine();

		} else if (state == State::CalibratingOuts) {
			update_cal_outs_routine();

		} else if (state == State::StartWritingCal || state == State::WritingCal) {
			update_cal_write();
		}
	}

	void start() {
		lv_hide(ui_CalibrationOutputStatusCont);
		lv_hide(ui_SystemCalibrationButton);
		lv_hide(ui_SystemResetInternalPatchesCont);

		lv_show(ui_CalibrationButtonCont);
		lv_show(ui_CalibrationInputStatusCont);
		lv_show(ui_CalibrationMeasurementLabel);
		lv_show(ui_CalibrationProcedureCont);

		lv_label_set_text(ui_CalibrationInstructionLabel,
						  "Play a C2 and a C4 into each jack you wish to re-calibrate.");
		lv_label_set_text(ui_CalibrationMeasurementLabel, "");

		lv_obj_scroll_to_y(ui_SystemMenuSystemTab, 0, LV_ANIM_OFF);
		lv_obj_scroll_to_view_recursive(ui_SystemCalibrationTitle, LV_ANIM_OFF);

		state = State::CalibratingIns;
		next_step = false;

		for (auto i = 0u; i < PanelDef::NumAudioIn; i++) {
			set_input_status(i, JackCalStatus::Error); //clear
			set_input_status(i, JackCalStatus::NotCal);
			jack_plugged[i] = false;
		}

		// TODO: read cal data
		saved_cal_data.reset_to_default();
	}

	void abort() {
		lv_hide(ui_CalibrationProcedureCont);
		lv_hide(ui_CalibrationInputStatusCont);
		lv_hide(ui_CalibrationOutputStatusCont);
		lv_show(ui_SystemCalibrationButton);
		lv_show(ui_SystemResetInternalPatchesCont);
		lv_group_focus_obj(ui_SystemCalibrationButton);
		state = State::Idle;
	}

	bool is_calibrating() {
		return state != State::Idle;
	}

private:
	void display_measurement(float val) {
		lv_label_set_text_fmt(ui_CalibrationMeasurementLabel, "%.3fV", (double)val);
	}

	///
	/// INPUTS
	///

	void update_cal_ins_routine() {
		unsigned num_done = 0;
		unsigned num_displayed = 0;

		for (unsigned i = 0; i < PanelDef::NumAudioIn; i++) {
			if (params.is_input_plugged(i)) {
				set_input_plugged(i, true);

				in_signals[i].update(metaparams.ins[i].iir);

				if (num_displayed == 0)
					display_measurement(saved_cal_data.in_cal[i].adjust(in_signals[i].iir));
				num_displayed++;

				if (jack_status[i] != JackCalStatus::Done) {
					measure_input(i);
				}

			} else {
				set_input_plugged(i, false);
				if (jack_status[i] == JackCalStatus::LowOnly || jack_status[i] == JackCalStatus::HighOnly)
					set_input_status(i, JackCalStatus::Error);
			}

			if (jack_status[i] == JackCalStatus::Done)
				num_done++;
		}

		if (num_done == PanelDef::NumAudioIn || next_step) {
			next_step = false;
			start_calibrate_outs();
		}
	}

	void measure_input(unsigned idx) {
		// Measure each jack and advance state

		using enum CalibrationMeasurer::CalibrationEvent;

		auto event = measurer.read(idx, in_signals[idx]);

		if (event == MeasuredLow) {
			if (jack_status[idx] == JackCalStatus::NotCal)
				set_input_status(idx, JackCalStatus::LowOnly);

			else if (jack_status[idx] == JackCalStatus::HighOnly)
				set_input_status(idx, JackCalStatus::Done);
		}

		else if (event == MeasuredHigh)
		{
			if (jack_status[idx] == JackCalStatus::NotCal)
				set_input_status(idx, JackCalStatus::HighOnly);

			else if (jack_status[idx] == JackCalStatus::LowOnly) {
				set_input_status(idx, JackCalStatus::Done);
				save_cal_in_readings(idx, measurer.get_cal_data(idx));
			}
		}
	}

	void set_input_status(unsigned idx, JackCalStatus status) {
		if (jack_status[idx] != status) {
			jack_status[idx] = status;

			auto *label = input_status_labels[idx];
			switch (status) {
				case JackCalStatus::LowOnly:
					lv_label_set_text_fmt(label, "In %d:\n #00a551 C2# #aaaaaa C4#", idx + 1);
					break;
				case JackCalStatus::HighOnly:
					lv_label_set_text_fmt(label, "In %d:\n #aaaaaa C2# #00a551 C4#", idx + 1);
					break;
				case JackCalStatus::NotCal:
					lv_label_set_text_fmt(label, "In %d:\n #aaaaaa C2 C4#", idx + 1);
					break;
				case JackCalStatus::Done:
					lv_label_set_text_fmt(label, "In %d:\n#00a551 OK#", idx + 1);
					break;
				case JackCalStatus::Error:
					lv_label_set_text_fmt(label, "In %d:\n#f40000 FAIL#", idx + 1);
					break;
			}
		}
	}

	void set_input_plugged(unsigned idx, bool plugged) {
		auto *label = input_status_labels[idx];

		if (plugged && !jack_plugged[idx]) {
			jack_plugged[idx] = true;
			measurer.start_chan(idx);
			lv_obj_set_style_outline_opa(label, LV_OPA_100, LV_PART_MAIN);
			set_input_status(idx, JackCalStatus::NotCal);

		} else if (!plugged && jack_plugged[idx]) {
			jack_plugged[idx] = false;
			lv_obj_set_style_outline_opa(label, LV_OPA_0, LV_PART_MAIN);
		}
	}

	void save_cal_in_readings(unsigned idx, std::pair<float, float> readings) {
		saved_cal_data.in_cal[idx].calibrate_chan({Calibration::DefaultLowV, Calibration::DefaultHighV}, readings);
		pr_dbg("Calibrated IN %d: %f %f\n", idx, readings.first, readings.second);
	}

	///
	/// OUTPUTS
	///
	void start_calibrate_outs() {
		lv_show(ui_CalibrationProcedureCont);
		lv_hide(ui_CalibrationInputStatusCont);
		lv_show(ui_CalibrationOutputStatusCont);
		lv_hide(ui_SystemCalibrationButton);
		lv_hide(ui_SystemResetInternalPatchesCont);

		lv_label_set_text(ui_CalibrationInstructionLabel, "Patch each Out jack to In 1 jack (one at a time).");
		lv_label_set_text(ui_CalibrationMeasurementLabel, "");

		lv_obj_scroll_to_y(ui_SystemMenuSystemTab, 0, LV_ANIM_OFF);
		lv_obj_scroll_to_view_recursive(ui_SystemCalibrationTitle, LV_ANIM_OFF);

		for (auto i = 0u; i < PanelDef::NumAudioOut; i++) {
			set_output_status(i, JackCalStatus::Error); //clear
			set_output_status(i, JackCalStatus::NotCal);
			jack_plugged[i] = false;
		}
		state = State::CalibratingOuts;

		current_output = std::nullopt;
	}

	void update_cal_outs_routine() {
		unsigned num_done = 0;
		unsigned num_patched = 0;
		unsigned active_output = 0;

		for (unsigned i = 0; i < PanelDef::NumAudioOut; i++) {
			if (params.is_output_plugged(i) && params.is_input_plugged(0)) {
				num_patched++;
				active_output = i;
				set_output_plugged(i, true);
			} else {
				set_output_plugged(i, false);

				if (jack_status[i] == JackCalStatus::LowOnly || jack_status[i] == JackCalStatus::HighOnly)
					set_output_status(i, JackCalStatus::Error);
			}

			if (jack_status[i] == JackCalStatus::Done)
				num_done++;
		}

		if (num_patched == 1) {

			display_measurement(in_signals[0].iir);

			// First time detected as patched
			if (active_output != current_output) {
				current_output = active_output;

				lv_label_set_text_fmt(
					ui_CalibrationInstructionLabel, "Calibrating Out %d, please wait", active_output + 1);

				start_output_channel(active_output, out_check.low, JackCalStatus::NotCal);

			} else if (jack_status[active_output] == JackCalStatus::NotCal) {
				if (measure_validate_output(active_output, out_check.low)) {
					output_cal_meas.low = in_signals[0].iir;
					start_output_channel(active_output, out_check.high, JackCalStatus::LowOnly);
				}

			} else if (jack_status[active_output] == JackCalStatus::LowOnly) {
				if (measure_validate_output(active_output, out_check.high)) {
					output_cal_meas.high = in_signals[0].iir;
					start_output_channel(active_output, out_check.zero, JackCalStatus::HighOnly);
				}

			} else if (jack_status[active_output] == JackCalStatus::HighOnly) {
				if (measure_validate_output(active_output, out_check.zero)) {
					output_cal_meas.zero = in_signals[0].iir;

					auto uncal = CalData::DefaultOutput;

					saved_cal_data.out_cal[active_output].calibrate_chan(
						{uncal.adjust(out_check.low), uncal.adjust(out_check.high)},
						{output_cal_meas.low, output_cal_meas.high});

					pr_dbg("Calibrated: L:%f H:%f, l:%f h:%f -> s:%f o:%f\n",
						   uncal.adjust(out_check.low),
						   uncal.adjust(out_check.high),
						   output_cal_meas.low,
						   output_cal_meas.high,
						   saved_cal_data.out_cal[active_output].slope(),
						   saved_cal_data.out_cal[active_output].offset());

					float offset_error =
						std::fabs(saved_cal_data.out_cal[active_output].offset() - output_cal_meas.zero);

					pr_dbg("Offset error: %f\n", offset_error);

					if (offset_error > 0.020f) {
						pr_err("Offset error is too large: %f\n", offset_error);
						current_output = std::nullopt;

					} else {
						set_output_status(active_output, JackCalStatus::Done);
						lv_label_set_text_fmt(ui_CalibrationInstructionLabel,
											  "Calibrated Out %d. Patch another Out jack to In 1",
											  active_output + 1);
					}
				}
			}

		} else if (num_patched > 1) {
			current_output = std::nullopt;
			lv_label_set_text(ui_CalibrationInstructionLabel, "Patch one output jack at a time!");
		}

		if (num_done == PanelDef::NumAudioOut || next_step) {
			next_step = false;

			for (auto chan : saved_cal_data.in_cal)
				pr_dbg("In 1/%f %f\n", 1.f / chan.slope(), chan.offset());

			for (auto chan : saved_cal_data.out_cal)
				pr_dbg("Out %f %f\n", chan.slope(), chan.offset());

			if (saved_cal_data.validate())
				start_calibrate_write();
			else {
				pr_err("Invalid calibration data\n");
				lv_label_set_text(ui_CalibrationInstructionLabel, "Calibration data is not valid, please retry.");
				state = State::Idle;
			}
		}
	}

	void start_output_channel(unsigned chan, float target, JackCalStatus status) {
		set_output_volts(chan, target);
		in_signals[0].reset_to(target);
		delay_measurement = 0;
		set_output_status(chan, status);
	}

	bool measure_validate_output(unsigned idx, float target_volts) {
		constexpr float Tolerance = 0.25f;
		constexpr float MaxNoise = 0.001f;

		bool is_valid = false;

		in_signals[0].update(saved_cal_data.in_cal[0].adjust(metaparams.ins[0].iir));

		if (delay_measurement++ >= 16) {
			if (measurer.validate_reading(in_signals[0], target_volts, Tolerance, MaxNoise)) {

				pr_dbg("Got reading for %f volts: %f\n", target_volts, in_signals[0].iir);
				is_valid = true;

			} else {
				pr_err("Not validated reading: %f [%f,%f] vs: %f +/- %f\n",
					   in_signals[0].iir,
					   in_signals[0].min,
					   in_signals[0].max,
					   target_volts,
					   Tolerance);
			}

			delay_measurement = 0;
			in_signals[0].reset_to(in_signals[0].iir);
		}

		return is_valid;
	}

	void set_output_status(unsigned idx, JackCalStatus status) {
		if (jack_status[idx] != status) {
			jack_status[idx] = status;

			auto *label = output_status_labels[idx];
			switch (status) {
				case JackCalStatus::NotCal: {
					lv_label_set_text_fmt(label, "#ffffff Out %d#", idx + 1);
				} break;

				case JackCalStatus::Done: {
					lv_label_set_text_fmt(label, "#00a551 Out %d#", idx + 1);
				} break;

				case JackCalStatus::Error: {
					lv_label_set_text_fmt(label, "#f40000 Out %d#", idx + 1);
				} break;

				case JackCalStatus::LowOnly:
				case JackCalStatus::HighOnly:
					break;
			}
		}
	}

	void set_output_volts(unsigned idx, float volts) {
		if (volts < -5.f || volts > 5.f)
			return;

		StaticParam p{};
		p.module_id = (idx / 2) + 1;
		p.param_id = idx % 2;
		p.value = volts / 10.f + 0.5f;

		patch_mod_queue.put(SetStaticParam{p});
	}

	void set_output_plugged(unsigned idx, bool plugged) {
		auto *label = output_status_labels[idx];

		if (plugged && !jack_plugged[idx]) {
			jack_plugged[idx] = true;
			lv_obj_set_style_outline_opa(label, LV_OPA_100, LV_PART_MAIN);
		} else if (!plugged && jack_plugged[idx]) {
			jack_plugged[idx] = false;
			lv_obj_set_style_outline_opa(label, LV_OPA_0, LV_PART_MAIN);
		}
	}

	//
	// Writing
	//

	void start_calibrate_write() {
		state = State::StartWritingCal;
		lv_hide(ui_CalibrationInputStatusCont);
		lv_hide(ui_CalibrationOutputStatusCont);
		lv_label_set_text(ui_CalibrationMeasurementLabel, "");
		lv_label_set_text(ui_CalibrationInstructionLabel, "Click Next to write calibration data to internal memory");
	}

	void update_cal_write() {
		if (state == State::StartWritingCal) {
			if (next_step) {
				if (storage.request_file_flash(IntercoreStorageMessage::FlashTarget::QSPI,
											   {(uint8_t *)(&saved_cal_data), sizeof(saved_cal_data)},
											   CalDataFlashOffset,
											   &bytes_written))
					state = State::WritingCal;
			}
		} else if (state == State::WritingCal) {
			auto msg = storage.get_message();
			if (msg.message_type == IntercoreStorageMessage::MessageType::FlashingOk) {
				pr_info("Flashing success!\n");
				lv_label_set_text(ui_CalibrationInstructionLabel, "Calibration data is saved.");
				lv_hide(ui_CalibrationButtonCont);
				state = State::Idle;

			} else if (msg.message_type == IntercoreStorageMessage::MessageType::FlashingFailed) {
				pr_err("Flashing failed!\n");
				lv_label_set_text(ui_CalibrationInstructionLabel, "FAILED! Could not write calibration data to flash");
				// hang in this state until the User goes back
			}
		}
	}

private:
	static void cancel_cb(lv_event_t *event) {
		if (!event || !event->user_data)
			return;
		auto page = static_cast<CalibrationRoutine *>(event->user_data);
		page->abort();
	}

	static void next_cb(lv_event_t *event) {
		if (!event || !event->user_data)
			return;
		auto page = static_cast<CalibrationRoutine *>(event->user_data);
		page->next_step = true;
	}

	enum class State {
		Idle,
		Init,
		StartReadingCal,
		ReadingCal,
		CalibratingIns,
		CalibratingOuts,
		StartWritingCal,
		WritingCal
	};
	static constexpr size_t MaxJacks = std::max(PanelDef::NumAudioIn, PanelDef::NumAudioOut);
	static constexpr float coef = 1.f / 4.f;
	struct OutputCalVoltages {
		float zero{};
		float low{};
		float high{};
	};
	static constexpr OutputCalVoltages out_check{0.f, 1.f, 5.f};

	FileStorageProxy &storage;
	PatchModQueue &patch_mod_queue;
	ParamsMidiState &params;
	MetaParams &metaparams;

	CalData saved_cal_data{};

	OutputCalVoltages output_cal_meas{};

	CalibrationMeasurer measurer;

	State state = State::Idle;

	bool next_step = false;

	std::array<bool, MaxJacks> jack_plugged{};
	std::array<JackCalStatus, MaxJacks> jack_status{};

	std::array<AnalyzedSig, PanelDef::NumAudioIn> in_signals{coef, coef, coef, coef, coef, coef};

	unsigned delay_measurement = 0;
	std::optional<unsigned> current_output = 0;

	uint32_t bytes_written{};

	std::array<lv_obj_t *, PanelDef::NumAudioIn> input_status_labels{
		ui_CalibrationIn1Label,
		ui_CalibrationIn2Label,
		ui_CalibrationIn3Label,
		ui_CalibrationIn4Label,
		ui_CalibrationIn5Label,
		ui_CalibrationIn6Label,
	};
	std::array<lv_obj_t *, PanelDef::NumAudioOut> output_status_labels{
		ui_CalibrationOut1Label,
		ui_CalibrationOut2Label,
		ui_CalibrationOut3Label,
		ui_CalibrationOut4Label,
		ui_CalibrationOut5Label,
		ui_CalibrationOut6Label,
		ui_CalibrationOut7Label,
		ui_CalibrationOut8Label,
	};
};

} // namespace MetaModule
