#pragma once
#include "calibrate/calibration_measurer.hh"
#include "conf/board_codec_conf.hh"
#include "drivers/cache.hh"
#include "expanders.hh"
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
	enum class JackCalStatus { NotCal, Settling, LowOnly, HighOnly, Error, Done };

	CalibrationRoutine(ParamsMidiState &params,
					   MetaParams &metaparams,
					   FileStorageProxy &storage,
					   PatchModQueue &patch_mod_queue)
		: storage{storage}
		, patch_mod_queue{patch_mod_queue}
		, params{params}
		, metaparams{metaparams}
		, measurer{{Calibration::DefaultLowV, Calibration::DefaultHighV}} {

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
			state = State::StartReadingCal;

		} else if (state == State::StartReadingCal || state == State::ReadingCal) {
			update_read_flash();

		} else if (state == State::CalibratingIns) {
			update_cal_ins_routine();

		} else if (state == State::CalibratingOuts) {
			update_cal_outs_routine();

		} else if (state == State::StartWritingCal || state == State::WritingCal) {
			update_write_flash();

		} else if (state == State::Verify) {
			verify_cal();

		} else if (state == State::UpdateAudioStream) {
			update_audio_stream();
		}
	}

	bool did_complete() {
		if (state == State::Complete) {
			state = State::Idle;
			return true;
		} else {
			return false;
		}
	}

	void start() {
		first_input_panel_index = 0;
		first_input = 0;
		first_output = 0;
		is_expander = false;
		lv_label_set_text(ui_CalibrationInstructionLabel,
						  "Play a C1 (1.00V) and a\nC4 (4.00V) into each jack\nto re-calibrate.");
		start_routine();
	}

	void start_expander() {
		first_input_panel_index = PanelDef::NumUserFacingInJacks; //First expander jack is after main audio + gate ins
		first_input = PanelDef::NumAudioIn;						  //First expander jack index is after main audio ins
		first_output = PanelDef::NumAudioOut;					  //First output is after last main panel output
		is_expander = true;
		lv_label_set_text(ui_CalibrationInstructionLabel,
						  "Play a C1 (1.00V) and a\nC4 (4.00V) into each Expander jack to re-calibrate.");
		start_routine();
	}

	void abort() {
		lv_hide(ui_CalibrationProcedureCont);
		lv_hide(ui_CalibrationInputStatusCont);
		lv_hide(ui_CalibrationOutputStatusCont);
		lv_show(ui_SystemCalibrationButton);
		lv_show(ui_SystemExpCalibrationButton, Expanders::get_connected().ext_audio_connected);
		lv_show(ui_SystemCalCheckButton);
		lv_show(ui_SystemResetInternalPatchesCont);
		lv_show(ui_SystemHardwareCheckCont);
		lv_group_focus_obj(ui_SystemCalibrationButton);

		patch_mod_queue.put(CalibrationOnOff{.enable = true});

		state = State::Idle;
	}

	bool is_calibrating() {
		return state != State::Idle;
	}

private:
	void start_routine() {
		lv_hide(ui_CalibrationOutputStatusCont);
		lv_hide(ui_SystemCalibrationButton);
		lv_hide(ui_SystemExpCalibrationButton);
		lv_hide(ui_SystemCalCheckButton);
		lv_hide(ui_SystemResetInternalPatchesCont);
		lv_hide(ui_SystemHardwareCheckCont);

		lv_show(ui_CalibrationButtonCont);
		lv_show(ui_CalibrationInputStatusCont);
		lv_show(ui_CalibrationMeasurementLabel);
		lv_show(ui_CalibrationProcedureCont);

		lv_group_focus_obj(ui_CalibrationCancelButton);

		lv_label_set_text(ui_CalibrationMeasurementLabel, "");

		lv_obj_scroll_to_y(ui_SystemMenuSystemTab, 0, LV_ANIM_OFF);
		lv_obj_scroll_to_view_recursive(ui_SystemCalibrationTitle, LV_ANIM_OFF);

		next_step = false;
		is_reading_to_verify = false;

		for (auto i = 0u; i < NumInputs; i++) {
			set_input_status(i, JackCalStatus::Error); //clear
			set_input_status(i, JackCalStatus::NotCal);
			jack_plugged[i] = false;
		}

		state = State::Init;
	}

private:
	void display_measurement(float val) {
		lv_label_set_text_fmt(ui_CalibrationMeasurementLabel, "%.3fV", (double)val);
	}

	void display_measurement(unsigned idx, float val) {
		lv_label_set_text_fmt(
			ui_CalibrationMeasurementLabel, "%.3fV\n%.3fV", (double)val, (double)calibrated_value(idx, val));
	}

	///
	/// INPUTS
	///

	void update_cal_ins_routine() {
		unsigned num_done = 0;
		unsigned num_plugged = 0;
		unsigned num_displayed = 0;

		for (unsigned i = 0; i < NumInputs; i++) {
			if (params.is_input_plugged(i + first_input_panel_index)) {
				num_plugged++;

				set_input_plugged(i, true);

				// during input cal routine, in_signals uses default cal values
				in_signals[i].update(params.smoothed_ins[i + first_input].val());

				if (++num_displayed == 1)
					display_measurement(i, in_signals[i].iir);

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

		if ((num_done == PanelDef::NumAudioIn && num_plugged == 0) || next_step) {
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

			else if (jack_status[idx] == JackCalStatus::HighOnly) {
				set_input_status(idx, JackCalStatus::Done);
				save_cal_in_readings(idx, measurer.get_cal_data(idx));
			}
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
			std::string in = std::string("In ") + std::to_string(idx + first_input + 1) + "\n";

			switch (status) {
				case JackCalStatus::LowOnly: {
					std::string stat = in + Gui::green_text("C1") + Gui::grey_text(" C4");
					lv_label_set_text(label, stat.c_str());
				} break;

				case JackCalStatus::HighOnly: {
					std::string stat = in + Gui::grey_text("C1") + Gui::green_text(" C4");
					lv_label_set_text(label, stat.c_str());
				} break;

				case JackCalStatus::NotCal: {
					std::string stat = in + Gui::grey_text("C1") + Gui::grey_text(" C4");
					lv_label_set_text(label, stat.c_str());
				} break;

				case JackCalStatus::Done: {
					std::string stat = in + Gui::green_text("OK");
					lv_label_set_text(label, stat.c_str());
				} break;

				case JackCalStatus::Error: {
					std::string stat = in + Gui::red_text("FAIL");
					lv_label_set_text(label, stat.c_str());
				} break;

				case JackCalStatus::Settling:
					break;
			}
		}
	}

	void set_input_plugged(unsigned idx, bool plugged) {
		auto *label = input_status_labels[idx];

		if (plugged && !jack_plugged[idx]) {
			jack_plugged[idx] = true;

			if (jack_status[idx] != JackCalStatus::Done) {
				measurer.start_chan();
				set_input_status(idx, JackCalStatus::NotCal);
			}

			lv_obj_set_style_outline_opa(label, LV_OPA_100, LV_PART_MAIN);

		} else if (!plugged && jack_plugged[idx]) {
			jack_plugged[idx] = false;
			lv_obj_set_style_outline_opa(label, LV_OPA_0, LV_PART_MAIN);
		}
	}

	void save_cal_in_readings(unsigned idx, std::pair<float, float> readings) {
		// Calculate the actual codec 24-bit reading by reversing the default calibration
		auto uncal = CalData::DefaultInput;
		readings = {uncal.reverse_calibrate(readings.first), uncal.reverse_calibrate(readings.second)};
		cal_data.in_cal[idx].calibrate_chan({Calibration::DefaultLowV, Calibration::DefaultHighV}, readings);
	}

	float calibrated_value(unsigned idx, float reading) {
		auto uncal = CalData::DefaultInput;
		auto raw = uncal.reverse_calibrate(reading);
		return cal_data.in_cal[idx].adjust(raw);
	}

	///
	/// OUTPUTS
	///
	void start_calibrate_outs() {
		lv_hide(ui_CalibrationInputStatusCont);
		lv_show(ui_CalibrationOutputStatusCont);

		lv_label_set_text(ui_CalibrationInstructionLabel, "Patch each Out jack to In 1 jack (one at a time).");
		lv_label_set_text(ui_CalibrationMeasurementLabel, "");

		lv_obj_scroll_to_y(ui_SystemMenuSystemTab, 0, LV_ANIM_OFF);
		lv_obj_scroll_to_view_recursive(ui_SystemCalibrationTitle, LV_ANIM_OFF);

		for (auto i = 0u; i < NumOutputs; i++) {
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

		for (unsigned i = 0; i < NumOutputs; i++) {
			if (params.is_output_plugged(i + first_output) && params.is_input_plugged(0)) {
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

				lv_label_set_text_fmt(ui_CalibrationInstructionLabel,
									  "Calibrating Out %d, please wait",
									  int(active_output + first_output + 1));

				start_output_channel(active_output, out_target.low, JackCalStatus::Settling);

				delay_measurement = 8;

			} else if (jack_status[active_output] == JackCalStatus::Settling) {
				if (delay_measurement)
					delay_measurement--;

				if (delay_measurement == 0)
					start_output_channel(active_output, out_target.low, JackCalStatus::NotCal);

			} else if (jack_status[active_output] == JackCalStatus::NotCal) {
				if (measure_validate_output(out_target.low)) {
					output_cal_meas.low = in_signals[0].iir;
					start_output_channel(active_output, out_target.high, JackCalStatus::LowOnly);
				}

			} else if (jack_status[active_output] == JackCalStatus::LowOnly) {
				if (measure_validate_output(out_target.high)) {
					output_cal_meas.high = in_signals[0].iir;
					start_output_channel(active_output, out_target.zero, JackCalStatus::HighOnly);
				}

			} else if (jack_status[active_output] == JackCalStatus::HighOnly) {
				if (measure_validate_output(out_target.zero)) {
					output_cal_meas.zero = in_signals[0].iir;

					calc_output_cal_data(active_output);

					if (check_offset_error(active_output)) {
						set_output_status(active_output, JackCalStatus::Done);
						lv_label_set_text_fmt(ui_CalibrationInstructionLabel,
											  "Calibrated Out %d. Patch another Out jack to In 1",
											  int(active_output + first_output + 1));
					} else {
						current_output = std::nullopt;
						// will automatically retry
					}
				}
			}

		} else if (num_patched > 1) {
			current_output = std::nullopt;
			lv_label_set_text(ui_CalibrationInstructionLabel, "Patch one output jack at a time!");
		}

		if (num_done == PanelDef::NumAudioOut || next_step) {
			next_step = false;

			cal_data.print_calibration();

			if (cal_data.validate())
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

	bool measure_validate_output(float target_volts) {
		constexpr float Tolerance = 0.25f;

		bool is_valid = false;

		// Calculate the raw codec 24-bit reading by reversing the default calibration
		// Then apply the new input calibration values to the raw value to determine a calibrated value
		auto default_cal = CalData::DefaultInput;
		auto raw_adc = default_cal.reverse_calibrate(params.smoothed_ins[0].val());
		in_signals[0].update(cal_data.in_cal[0].adjust(raw_adc));

		if (delay_measurement++ >= 2) {
			if (measurer.validate_reading(in_signals[0], target_volts, Tolerance)) {
				pr_trace("Validated Out %d: %f [%f,%f => delta %f] vs: %5f +/- %5f\n",
						 current_output.value(),
						 in_signals[0].iir,
						 in_signals[0].min,
						 in_signals[0].max,
						 std::fabs(in_signals[0].min - in_signals[0].max),
						 target_volts,
						 Tolerance);

				is_valid = true;
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
			std::string out = "Out " + std::to_string(idx + first_output + 1);

			switch (status) {
				case JackCalStatus::NotCal: {
					lv_label_set_text(label, Gui::grey_text(out).c_str());
				} break;

				case JackCalStatus::Done: {
					lv_label_set_text(label, Gui::green_text(out).c_str());
				} break;

				case JackCalStatus::Error: {
					lv_label_set_text(label, Gui::red_text(out).c_str());
				} break;

				case JackCalStatus::LowOnly:
				case JackCalStatus::HighOnly:
				case JackCalStatus::Settling:
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

	void calc_output_cal_data(unsigned active_output) {
		int32_t dac_val_on_low = std::round(CalData::DefaultOutput.adjust(out_target.low));	  //814428
		int32_t dac_val_on_high = std::round(CalData::DefaultOutput.adjust(out_target.high)); //4072140
		cal_data.out_cal[active_output].calibrate_chan({dac_val_on_low, dac_val_on_high},
													   {output_cal_meas.low, output_cal_meas.high});
	}

	float check_offset_error(unsigned active_output) {
		constexpr float offset_tolerance = 0.020f;

		float offset_error = std::fabs(cal_data.out_cal[active_output].offset() - output_cal_meas.zero);

		if (offset_error < offset_tolerance) {
			return true;
		} else {
			pr_err("Offset error is too large: %f. Tolerance is %f\n", offset_error, offset_tolerance);
			return false;
		}
	}

	//
	// Reading/Writing Flash
	//

	void update_read_flash() {
		if (state == State::StartReadingCal) {

			if (is_expander) {
				auto caldata_span = std::span<uint8_t>{reinterpret_cast<uint8_t *>(&cal_data), sizeof(cal_data)};
				if (Hardware::codec_ext_memory.read(0, caldata_span)) {
					state = is_reading_to_verify ? State::Verify : State::CalibratingIns;
				}
			} else {

				auto caldata_span = std::span<uint8_t>{reinterpret_cast<uint8_t *>(&cal_data), sizeof(cal_data)};

				mdrivlib::SystemCache::clean_dcache_by_range(&padded_cal_data, sizeof(PaddedCalData));

				if (storage.request_read_flash(caldata_span, CalDataFlashOffset)) {
					state = State::ReadingCal;
				} else
					pr_warn("Failed to request reading cal from flash, trying again\n");
			}

		} else if (state == State::ReadingCal) {

			auto msg = storage.get_message();

			if (msg.message_type == IntercoreStorageMessage::MessageType::ReadFlashOk) {

				mdrivlib::SystemCache::invalidate_dcache_by_range(&padded_cal_data, sizeof(PaddedCalData));

				if (msg.bytes_read != sizeof(cal_data)) {
					pr_err("Internal error reading flash (%u bytes read)\n", msg.bytes_read);
				}

				state = is_reading_to_verify ? State::Verify : State::CalibratingIns;

			} else if (msg.message_type == IntercoreStorageMessage::MessageType::ReadFlashFailed) {
				pr_err("Failed to read calibration data\n");
				state = is_reading_to_verify ? State::Verify : State::CalibratingIns;
			}
		}
	}

	void start_calibrate_write() {
		state = State::StartWritingCal;
		lv_hide(ui_CalibrationInputStatusCont);
		lv_hide(ui_CalibrationOutputStatusCont);
		lv_label_set_text(ui_CalibrationMeasurementLabel, "");
		lv_label_set_text(ui_CalibrationInstructionLabel, "Click Next to write calibration data to internal memory");
	}

	void update_write_flash() {
		bool success = false;
		bool failure = false;

		if (state == State::StartWritingCal) {
			// Wait for Next button
			if (next_step) {
				if (is_expander) {
					if (Hardware::codec_ext_memory.write(cal_data, 0)) {
						success = true;
					} else {
						failure = true;
					}
				} else {
					mdrivlib::SystemCache::clean_dcache_by_range(&cal_data, sizeof(PaddedCalData));

					if (storage.request_file_flash(IntercoreStorageMessage::FlashTarget::QSPI,
												   {(uint8_t *)(&cal_data), sizeof(cal_data)},
												   CalDataFlashOffset,
												   std::nullopt,
												   &dummy)) //we don't need to know how many bytes were written
						state = State::WritingCal;
				}
			}
		} else if (state == State::WritingCal) {
			auto msg = storage.get_message();
			if (msg.message_type == IntercoreStorageMessage::MessageType::FlashingOk) {
				success = true;

			} else if (msg.message_type == IntercoreStorageMessage::MessageType::FlashingFailed) {
				failure = true;
			}
		}

		if (success) {
			pr_info("Flashing success!\n");
			lv_label_set_text(ui_CalibrationInstructionLabel, "Calibration data is saved, verifying.");
			lv_hide(ui_CalibrationButtonCont);
			cal_data.print_calibration();
			is_reading_to_verify = true;
			cal_data_check = cal_data;
			state = State::StartReadingCal;
		}

		if (failure) {
			pr_err("Writing cal data failed!\n");
			lv_label_set_text(ui_CalibrationInstructionLabel, "FAILED! Could not write calibration data");
			// hang in this state until the User goes back
		}
	}

	void verify_cal() {
		bool verified = true;
		for (auto [a, b] : zip(cal_data.in_cal, cal_data_check.in_cal)) {
			if (a.slope() != b.slope() || a.offset() != b.offset())
				verified = false;
		}
		for (auto [a, b] : zip(cal_data.out_cal, cal_data_check.out_cal)) {
			if (a.slope() != b.slope() || a.offset() != b.offset())
				verified = false;
		}
		if (verified) {
			lv_label_set_text(ui_CalibrationInstructionLabel,
							  "Calibration data saved and verified, updating audio stream's cal values.");
			state = State::UpdateAudioStream;
		} else {
			lv_label_set_text(ui_CalibrationInstructionLabel, "Error: Calibration data corrupted");
			state = State::Idle;
		}
	}

	void update_audio_stream() {
		for (auto [i, chan] : enumerate(cal_data.in_cal)) {
			i += first_input;
			bool ok = patch_mod_queue.put(SetChanCalibration{
				.slope = chan.slope(), .offset = chan.offset(), .channel = (uint16_t)i, .is_input = true});

			if (!ok) {
				pr_err("Error: patch mod queue full\n");
				break;
			}
		}

		for (auto [i, chan] : enumerate(cal_data.out_cal)) {
			i += first_output;
			auto ok = patch_mod_queue.put(SetChanCalibration{
				.slope = chan.slope(), .offset = chan.offset(), .channel = (uint16_t)i, .is_input = false});

			if (!ok) {
				pr_err("Error: patch mod queue full\n");
				break;
			}
		}

		if (!patch_mod_queue.put(CalibrationOnOff{.enable = true})) {
			pr_err("Error: patch mod queue full\n");
		}

		state = State::Complete;
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
		WritingCal,
		Verify,
		UpdateAudioStream,
		Complete,
	};
	static constexpr auto NumInputs = PanelDef::NumAudioIn;
	static constexpr auto NumOutputs = PanelDef::NumAudioOut;
	static constexpr size_t MaxJacks = std::max(NumInputs, NumOutputs);
	static constexpr float coef = 1.f / 4.f;
	struct OutputCalVoltages {
		float zero{};
		float low{};
		float high{};
	};
	static constexpr OutputCalVoltages out_target{0.f, 1.f, 5.f};

	FileStorageProxy &storage;
	PatchModQueue &patch_mod_queue;
	ParamsMidiState &params;
	MetaParams &metaparams;

	// Pad calibration data so does not share cache lines with other data
	struct PaddedCalData {
		CalData cal_data{};
		char padding[128 - sizeof(cal_data)]{};

		static_assert(sizeof(CalData) >= 64 && sizeof(CalData) < 128);
	};
	alignas(64) PaddedCalData padded_cal_data{};
	static_assert(sizeof padded_cal_data % 64 == 0, "CalData must not share cache lines with other data");

	CalData &cal_data = padded_cal_data.cal_data;
	uint32_t dummy = 0;

	uint32_t first_input_panel_index = 0;
	uint32_t first_input = 0;
	uint32_t first_output = 0;
	bool is_expander = false;

	CalData cal_data_check{};
	bool is_reading_to_verify = false;

	OutputCalVoltages output_cal_meas{};

	CalibrationMeasurer measurer;

	State state = State::Idle;

	bool next_step = false;

	std::array<bool, MaxJacks> jack_plugged{};
	std::array<JackCalStatus, MaxJacks> jack_status{};

	std::array<AnalyzedSig, NumInputs> in_signals{coef, coef, coef, coef, coef, coef};

	unsigned delay_measurement = 0;
	std::optional<unsigned> current_output = 0;

	std::array<lv_obj_t *, NumInputs> input_status_labels{
		ui_CalibrationIn1Label,
		ui_CalibrationIn2Label,
		ui_CalibrationIn3Label,
		ui_CalibrationIn4Label,
		ui_CalibrationIn5Label,
		ui_CalibrationIn6Label,
	};
	std::array<lv_obj_t *, NumOutputs> output_status_labels{
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
