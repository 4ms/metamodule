#pragma once
#include "audio/calibrator.hh"
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
		, metaparams{metaparams} {
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
		if (state == State::Calibrating) {
			cal.update(cur_cal_chan, metaparams.ins[cur_cal_chan]);

			for (unsigned i = 0; i < PanelDef::NumAudioIn; i++) {
				if (params.is_input_plugged(i)) {
					set_input_plugged(i, true);
				} else {
					set_input_plugged(i, false);
				}
			}
		}
	}

private:
	enum class JackCalStatus { NotCal, Error, Done };

	void start_calibration() {
		lv_show(ui_CalibrationProcedureCont);
		lv_hide(ui_SystemCalibrationButton);
		lv_hide(ui_SystemResetInternalPatchesCont);

		lv_label_set_text(ui_CalibrationInstructionLabel,
						  "Play a C2 and then a C4 into each jack you wish to re-calibrate.");

		lv_obj_scroll_to_y(ui_SystemMenuSystemTab, 0, LV_ANIM_OFF);
		lv_obj_scroll_to_view_recursive(ui_SystemCalibrationTitle, LV_ANIM_OFF);

		cal.start();
		cur_cal_chan = 0;
		state = State::Calibrating;

		for (auto i = 0u; i < input_status.size(); i++) {
			set_input_status(i, JackCalStatus::NotCal);
		}
	}

	void set_input_status(unsigned idx, JackCalStatus status) {
		if (idx >= input_status.size())
			return;

		input_status[idx] = status;
		auto *label = input_status_labels[idx];
		switch (status) {
			case JackCalStatus::NotCal: {
				lv_label_set_text_fmt(label, "In %d: --", idx);
				lv_obj_set_style_text_color(label, lv_color_white(), LV_PART_MAIN);
			} break;

			case JackCalStatus::Done: {
				lv_label_set_text_fmt(label, "In %d: OK", idx);
				lv_obj_set_style_text_color(label, Gui::palette_main[LV_PALETTE_GREEN], LV_PART_MAIN);
			} break;

			case JackCalStatus::Error: {
				lv_label_set_text_fmt(label, "In %d: BAD", idx);
				lv_obj_set_style_text_color(label, Gui::palette_main[LV_PALETTE_RED], LV_PART_MAIN);
			} break;
		}
	}

	void set_input_plugged(unsigned idx, bool plugged) {
		if (idx >= input_plugged.size())
			return;

		auto *label = input_status_labels[idx];
		if (plugged && !input_plugged[idx]) {
			input_plugged[idx] = true;
			lv_obj_set_style_outline_opa(label, LV_OPA_100, LV_PART_MAIN);
			set_input_status(idx, JackCalStatus::NotCal);

		} else if (!plugged && input_plugged[idx]) {
			input_plugged[idx] = false;
			lv_obj_set_style_outline_opa(label, LV_OPA_0, LV_PART_MAIN);
			// TODO: Check if cal is completed, and set status to Done or Error
		}
	}

	static void calibrate_cb(lv_event_t *event) {
		if (!event || !event->user_data)
			return;

		auto page = static_cast<SystemTab *>(event->user_data);

		page->start_calibration();
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
	Calibrator cal;

	enum class State { Idle, Calibrating } state = State::Idle;
	unsigned cur_cal_chan = 0;

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
