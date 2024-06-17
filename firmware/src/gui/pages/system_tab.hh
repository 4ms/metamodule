#pragma once
#include "audio/calibrator.hh"
#include "fs/norflash_layout.hh"
#include "git_version.h"
#include "gui/helpers/lv_helpers.hh"
#include "gui/pages/base.hh"
#include "gui/pages/confirm_popup.hh"
#include "gui/pages/page_list.hh"
#include "gui/pages/system_menu_tab_base.hh"
#include "gui/slsexport/meta5/ui.h"
#include "gui/styles.hh"

namespace MetaModule
{

struct SystemTab : SystemMenuTab {

	SystemTab(FileStorageProxy &patch_storage, ParamsMidiState &params, MetaParams &metaparams)
		: storage{patch_storage}
		, params{params}
		, metaparams{metaparams}
		, cal{{Calibration::DefaultLowV, Calibration::DefaultHighV, Calibration::from_volts(0.1f)}} {

		lv_obj_add_event_cb(ui_SystemCalibrationButton, calibrate_cb, LV_EVENT_CLICKED, this);
		lv_obj_add_event_cb(ui_ResetFactoryPatchesButton, resetbut_cb, LV_EVENT_CLICKED, this);

		for (auto label : input_status_labels) {
			lv_obj_set_style_outline_color(label, Gui::orange_highlight, LV_PART_MAIN);
			lv_obj_set_style_outline_opa(label, LV_OPA_0, LV_PART_MAIN);
			lv_obj_set_style_outline_width(label, 1, LV_PART_MAIN);
			lv_obj_set_style_outline_pad(label, 4, LV_PART_MAIN);
		}
	}

	void prepare_focus(lv_group_t *group) override {
		this->group = group;

		lv_hide(ui_CalibrationProcedureCont);
		lv_show(ui_SystemCalibrationCont);
		lv_show(ui_SystemCalibrationButton);
		lv_show(ui_SystemResetInternalPatchesCont);

		lv_group_remove_obj(ui_SystemCalibrationButton);
		lv_group_remove_obj(ui_ResetFactoryPatchesButton);
		lv_group_remove_obj(ui_CalibrationCancelButton);

		lv_group_add_obj(group, ui_SystemCalibrationButton);
		lv_group_add_obj(group, ui_ResetFactoryPatchesButton);
		lv_group_add_obj(group, ui_CalibrationCancelButton);

		lv_group_focus_obj(ui_SystemCalibrationButton);
		confirm_popup.init(ui_SystemMenu, group);
	}

	// Returns true if this pages uses the back event
	bool consume_back_event() override {
		if (confirm_popup.is_visible()) {
			confirm_popup.hide();
			return true;
		}
		return false;
	}

	void update() override {
		if (state == State::TryingReadCal || state == State::ReadingCal) {
			update_read_saved_cal();

		} else if (state == State::CalibratingIns) {
			update_cal_ins_routine();

		} else if (state == State::CalibratingOuts) {
			update_cal_outs_routine();
		}
	}

private:
	enum class JackCalStatus { NotCal, LowOnly, HighOnly, Error, Done };

	void start_calibrate_ins() {
		// send message via PatchPlayLoader to tell audio to disable calibration?

		lv_show(ui_CalibrationProcedureCont);
		lv_hide(ui_SystemCalibrationButton);
		lv_hide(ui_SystemResetInternalPatchesCont);

		lv_label_set_text(ui_CalibrationInstructionLabel,
						  "Play a C2 and then a C4 into each jack you wish to re-calibrate.");

		lv_obj_scroll_to_y(ui_SystemMenuSystemTab, 0, LV_ANIM_OFF);
		lv_obj_scroll_to_view_recursive(ui_SystemCalibrationTitle, LV_ANIM_OFF);

		state = State::TryingReadCal;

		for (auto i = 0u; i < input_status.size(); i++) {
			set_input_status(i, JackCalStatus::NotCal);
			input_plugged[i] = false;
		}
	}

	void start_calibrate_outs() {
		// send message via PatchPlayLoader to tell audio to not play patch

		lv_show(ui_CalibrationProcedureCont);
		lv_hide(ui_SystemCalibrationButton);
		lv_hide(ui_SystemResetInternalPatchesCont);

		lv_label_set_text(ui_CalibrationInstructionLabel, "Patch each Out jack to Audio/CV Ins 1, one at a time.");

		lv_obj_scroll_to_y(ui_SystemMenuSystemTab, 0, LV_ANIM_OFF);
		lv_obj_scroll_to_view_recursive(ui_SystemCalibrationTitle, LV_ANIM_OFF);

		// for (auto i = 0u; i < input_status.size(); i++) {
		// 	set_input_status(i, JackCalStatus::NotCal);
		// 	input_plugged[i] = false;
		// }
	}

	void update_read_saved_cal() {
		if (state == State::TryingReadCal) {

			auto caldata_span = std::span<uint8_t>{reinterpret_cast<uint8_t *>(&caldata), sizeof(caldata)};
			auto ok = storage.request_read_flash(caldata_span, CalDataFlashOffset, &caldata_bytes_read);
			if (ok)
				state = State::ReadingCal;

		} else if (state == State::ReadingCal) {

			auto msg = storage.get_message();
			if (msg.message_type == IntercoreStorageMessage::MessageType::ReadFlashOk) {
				if (caldata_bytes_read == sizeof(caldata)) {
					pr_trace("Read calibration data\n");
					state = State::CalibratingIns;
				} else {
					pr_err("Wrong size calibration data read (%d read, expected %d)\n",
						   caldata_bytes_read,
						   sizeof(caldata));
					state = State::CalibratingIns;
				}

			} else if (msg.message_type == IntercoreStorageMessage::MessageType::ReadFlashFailed) {
				pr_err("Failed to read calibration data\n");
				state = State::CalibratingIns;
			}
		}
	}

	void update_cal_ins_routine() {
		unsigned num_done = 0;

		for (unsigned i = 0; i < PanelDef::NumAudioIn; i++) {
			if (params.is_input_plugged(i)) {
				set_input_plugged(i, true);

				in_signals[i].update(metaparams.ins[i].iir);

				if (input_status[i] != JackCalStatus::Done) {
					measure(i);
				}

			} else {
				set_input_plugged(i, false);
				if (input_status[i] == JackCalStatus::LowOnly || input_status[i] == JackCalStatus::HighOnly)
					set_input_status(i, JackCalStatus::Error);
			}

			if (input_status[i] == JackCalStatus::Done)
				num_done++;
		}

		if (num_done == 6) {
			state = State::CalibratingOuts;
		}
	}

	void update_cal_outs_routine() {
		unsigned num_done = 0;

		for (unsigned i = 0; i < PanelDef::NumAudioOut; i++) {
			//TODO:
		}

		if (num_done == 6) {
			state = State::WritingCal;
		}
	}

	void measure(unsigned idx) {
		// Measure each jack and advance state

		using enum CalibrationMeasurer::CalibrationEvent;

		auto event = cal.read(idx, in_signals[idx]);

		if (event == MeasuredLow) {
			if (input_status[idx] == JackCalStatus::NotCal)
				set_input_status(idx, JackCalStatus::LowOnly);
			else if (input_status[idx] == JackCalStatus::HighOnly)
				set_input_status(idx, JackCalStatus::Done);
		}

		else if (event == MeasuredHigh)
		{
			if (input_status[idx] == JackCalStatus::NotCal)
				set_input_status(idx, JackCalStatus::HighOnly);
			else if (input_status[idx] == JackCalStatus::LowOnly)
				set_input_status(idx, JackCalStatus::Done);
		}
	}

	void set_input_status(unsigned idx, JackCalStatus status) {
		if (input_status[idx] != status) {
			input_status[idx] = status;

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
					lv_label_set_text_fmt(label, "In %d:\n#00a551 OK#", idx + 1);
					caldata.ins_data[idx] = cal.get_cal_data(idx);
					pr_dbg("Calibrated IN %d: %f %f\n", idx, caldata.ins_data[idx].first, caldata.ins_data[idx].second);
				} break;

				case JackCalStatus::Error: {
					lv_label_set_text_fmt(label, "In %d:\n#f40000 FAIL#", idx + 1);
				} break;
			}
		}
	}

	void set_input_plugged(unsigned idx, bool plugged) {
		auto *label = input_status_labels[idx];

		if (plugged && !input_plugged[idx]) {
			input_plugged[idx] = true;
			cal.start_chan(idx);
			lv_obj_set_style_outline_opa(label, LV_OPA_100, LV_PART_MAIN);
			set_input_status(idx, JackCalStatus::NotCal);

		} else if (!plugged && input_plugged[idx]) {
			input_plugged[idx] = false;
			lv_obj_set_style_outline_opa(label, LV_OPA_0, LV_PART_MAIN);
		}
	}

	static void calibrate_cb(lv_event_t *event) {
		if (!event || !event->user_data)
			return;

		auto page = static_cast<SystemTab *>(event->user_data);

		page->start_calibrate_ins();
	}

	static void resetbut_cb(lv_event_t *event) {
		if (!event || !event->user_data)
			return;

		auto page = static_cast<SystemTab *>(event->user_data);
		page->confirm_popup.show(
			[page](bool ok) {
				if (ok) {
					page->storage.request_reset_factory_patches();
				}
			},
			"Do you really want to PERMANENTLY DELETE all patches stored internally? This will replace them with "
			"factory default patches.\n",
			"Delete");
	}

	FileStorageProxy &storage;
	ParamsMidiState &params;
	MetaParams &metaparams;

	ConfirmPopup confirm_popup;
	CalibrationMeasurer cal;
	CalData caldata;
	uint32_t caldata_bytes_read = 0;

	static constexpr float coef = 1.f / 4.f;
	std::array<AnalyzedSig, PanelDef::NumAudioIn> in_signals{coef, coef, coef, coef, coef, coef};

	enum class State {
		Idle,
		TryingReadCal,
		ReadingCal,
		CalibratingIns,
		CalibratingOuts,
		WritingCal
	} state = State::Idle;

	std::array<bool, PanelDef::NumAudioIn> input_plugged{};
	std::array<JackCalStatus, PanelDef::NumAudioIn> input_status{};
	std::array<lv_obj_t *, PanelDef::NumAudioIn> input_status_labels{ui_CalibrationIn1Label,
																	 ui_CalibrationIn2Label,
																	 ui_CalibrationIn3Label,
																	 ui_CalibrationIn4Label,
																	 ui_CalibrationIn5Label,
																	 ui_CalibrationIn6Label};

	lv_group_t *group = nullptr;
};
} // namespace MetaModule
