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
		, cal{{Calibration::DefaultLowV, Calibration::DefaultHighV, Calibration::from_volts(0.1f)}} {

		for (auto label : input_status_labels) {
			lv_obj_set_style_outline_color(label, Gui::orange_highlight, LV_PART_MAIN);
			lv_obj_set_style_outline_opa(label, LV_OPA_0, LV_PART_MAIN);
			lv_obj_set_style_outline_width(label, 1, LV_PART_MAIN);
			lv_obj_set_style_outline_pad(label, 4, LV_PART_MAIN);
		}
	}

	void update() {
		if (state == State::Init) {
			patch_mod_queue.put(CalibrationOnOff{.enable = false});
			state = State::CalibratingIns;

		} else if (state == State::CalibratingIns) {
			update_cal_ins_routine();

		} else if (state == State::CalibratingOuts) {
			update_cal_outs_routine();
		}
	}

	void start() {
		// send message via PatchPlayLoader to tell audio to disable calibration?

		lv_show(ui_CalibrationProcedureCont);
		lv_show(ui_CalibrationInputStatusCont);
		lv_hide(ui_CalibrationOutputStatusCont);
		lv_hide(ui_SystemCalibrationButton);
		lv_hide(ui_SystemResetInternalPatchesCont);

		lv_label_set_text(ui_CalibrationInstructionLabel,
						  "Play a C2 and a C4 into each jack you wish to re-calibrate.");

		lv_obj_scroll_to_y(ui_SystemMenuSystemTab, 0, LV_ANIM_OFF);
		lv_obj_scroll_to_view_recursive(ui_SystemCalibrationTitle, LV_ANIM_OFF);

		state = State::CalibratingIns;

		for (auto i = 0u; i < PanelDef::NumAudioIn; i++) {
			set_input_status(i, JackCalStatus::NotCal);
			jack_plugged[i] = false;
		}

		caldata.ins_target_volts = {Calibration::DefaultLowV, Calibration::DefaultHighV};
	}

	void abort() {
		lv_hide(ui_CalibrationProcedureCont);
		lv_hide(ui_CalibrationInputStatusCont);
		lv_hide(ui_CalibrationOutputStatusCont);
		lv_show(ui_SystemCalibrationButton);
		lv_show(ui_SystemResetInternalPatchesCont);
		state = State::Idle;
	}

	bool is_calibrating() {
		return state != State::Idle;
	}

private:
	///
	/// INPUTS
	///

	void update_cal_ins_routine() {
		unsigned num_done = 0;

		for (unsigned i = 0; i < PanelDef::NumAudioIn; i++) {
			if (params.is_input_plugged(i)) {
				set_input_plugged(i, true);

				in_signals[i].update(metaparams.ins[i].iir);

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

		if (num_done == 1) { //FIXME: 1==debug only //PanelDef::NumAudioIn) {
			start_calibrate_outs();
		}
	}

	void measure_input(unsigned idx) {
		// Measure each jack and advance state

		using enum CalibrationMeasurer::CalibrationEvent;

		auto event = cal.read(idx, in_signals[idx]);

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

			else if (jack_status[idx] == JackCalStatus::LowOnly)
				set_input_status(idx, JackCalStatus::Done);
		}
	}

	void set_input_status(unsigned idx, JackCalStatus status) {
		if (jack_status[idx] != status) {
			jack_status[idx] = status;

			auto *label = input_status_labels[idx];
			switch (status) {
				case JackCalStatus::LowOnly: {
					lv_label_set_text_fmt(label, "In %d:\n #00a551 C2# #aaaaaa C4#", idx + 1);
				} break;
				case JackCalStatus::HighOnly: {
					lv_label_set_text_fmt(label, "In %d:\n #aaaaaa C2# #00a551 C4#", idx + 1);
				} break;
				case JackCalStatus::NotCal: {
					lv_label_set_text_fmt(label, "In %d:\n #aaaaaa C2 C4#", idx + 1);
				} break;

				case JackCalStatus::Done: {
					save_cal_in_readings(idx, cal.get_cal_data(idx));
					lv_label_set_text_fmt(label, "In %d:\n#00a551 OK#", idx + 1);
				} break;

				case JackCalStatus::Error: {
					lv_label_set_text_fmt(label, "In %d:\n#f40000 FAIL#", idx + 1);
				} break;
			}
		}
	}

	void set_input_plugged(unsigned idx, bool plugged) {
		auto *label = input_status_labels[idx];

		if (plugged && !jack_plugged[idx]) {
			jack_plugged[idx] = true;
			cal.start_chan(idx);
			lv_obj_set_style_outline_opa(label, LV_OPA_100, LV_PART_MAIN);
			set_input_status(idx, JackCalStatus::NotCal);

		} else if (!plugged && jack_plugged[idx]) {
			jack_plugged[idx] = false;
			lv_obj_set_style_outline_opa(label, LV_OPA_0, LV_PART_MAIN);
		}
	}

	void save_cal_in_readings(unsigned idx, std::pair<float, float> readings) {
		caldata.ins_data[idx] = readings;
		pr_dbg("Calibrated IN %d: %f %f\n", idx, caldata.ins_data[idx].first, caldata.ins_data[idx].second);
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

		// lv_label_set_text(ui_CalibrationInstructionLabel, "Patch each Out jack to In 1 jack.");

		lv_obj_scroll_to_y(ui_SystemMenuSystemTab, 0, LV_ANIM_OFF);
		lv_obj_scroll_to_view_recursive(ui_SystemCalibrationTitle, LV_ANIM_OFF);

		for (auto i = 0u; i < PanelDef::NumAudioOut; i++) {
			set_input_status(i, JackCalStatus::NotCal);
			jack_plugged[i] = false;
		}
		state = State::CalibratingOuts;

		calibrated_in.calibrate_chan(caldata.ins_target_volts.first,
									 caldata.ins_target_volts.second,
									 caldata.ins_data[0].first,
									 caldata.ins_data[0].second);
		// pr_dbg("Input 1: slope: %f offset: %f\n", calibrated_in._slope, calibrated_in._offset);

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
			}
		}

		if (num_patched == 1) {
			// First time detected as patched
			if (active_output != current_output) {
				current_output = active_output;

				lv_label_set_text_fmt(
					ui_CalibrationInstructionLabel, "Calibrating Out %d, please wait...", active_output);

				jack_status[active_output] = JackCalStatus::NotCal;

				set_output_volts(active_output, 2.5f);
				in_signals[0].reset_to(2.5f);
				delay_measurement = 0;
			}

			else if (jack_status[active_output] == JackCalStatus::NotCal)
			{
				measure_validate_output(active_output, 2.5f);
				// auto measured_volts =
				//measure, validate, update output
			} else if (jack_status[active_output] == JackCalStatus::LowOnly) {
				//measure, validate, update output
			} else if (jack_status[active_output] == JackCalStatus::HighOnly) {
				//measure, validate, update output
			}

		} else if (num_patched > 1) {
			current_output = std::nullopt;
			lv_label_set_text(ui_CalibrationInstructionLabel, "Patch one output jack at a time!");
		}

		if (num_done == PanelDef::NumAudioOut) {
			state = State::WritingCal;
		}
	}

	bool measure_validate_output(unsigned idx, float target_volts) {
		constexpr float Tolerance = 1.25f;

		in_signals[0].update(calibrated_in.adjust(metaparams.ins[0].iir));

		if (delay_measurement++ >= 64) {
			if (cal.validate_reading(in_signals[0], target_volts, Tolerance)) {

				pr_dbg("Got reading for %f volts: %f\n", target_volts, in_signals[0].iir);
				//TODO save this
				return true;
			} else {
				pr_err("Not validated reading: %f [%f,%f] vs: %f +/- %f\n",
					   in_signals[0].iir,
					   in_signals[0].min,
					   in_signals[0].max,
					   target_volts,
					   Tolerance);
				return false;
			}

			delay_measurement = 0;
			in_signals[0].reset_to(in_signals[0].iir);
			pr_dbg("in_signals[0] reset to %f\n", in_signals[0].iir);
		}
		return false;
	}

	void set_output_status(unsigned idx, JackCalStatus status) {
		if (jack_status[idx] != status) {
			jack_status[idx] = status;

			auto *label = output_status_labels[idx];
			switch (status) {
				case JackCalStatus::NotCal: {
					lv_label_set_text_fmt(label, "#aaaaaa Out %d#", idx + 1);
				} break;

				case JackCalStatus::Done: {
					lv_label_set_text_fmt(label, "#00a551 Out %d#", idx + 1);
					// TODO
					// caldata.outs_data[idx] = cal.get_cal_data(0);
					// pr_dbg("Calibrated Out %d: %f %f\n", idx, caldata.outs_data[idx].first, caldata.outs_data[idx].second);
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

private:
	FileStorageProxy &storage;
	PatchModQueue &patch_mod_queue;
	ParamsMidiState &params;
	MetaParams &metaparams;

	SavedCalData saved_cal_data{};
	CalData caldata;

	CalibrationMeasurer cal;
	Calibrator calibrated_in;

	enum class State { Idle, Init, ReadingCal, CalibratingIns, CalibratingOuts, WritingCal };
	static constexpr size_t MaxJacks = std::max(PanelDef::NumAudioIn, PanelDef::NumAudioOut);
	static constexpr float coef = 1.f / 4.f;

	State state = State::Idle;

	std::array<bool, MaxJacks> jack_plugged{};
	std::array<JackCalStatus, MaxJacks> jack_status{};

	std::array<AnalyzedSig, PanelDef::NumAudioIn> in_signals{coef, coef, coef, coef, coef, coef};

	unsigned delay_measurement = 0;
	std::optional<unsigned> current_output = 0;

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
