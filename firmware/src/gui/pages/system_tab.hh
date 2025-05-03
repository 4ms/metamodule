#pragma once
#include "calibrate/cal_check.hh"
#include "calibrate/calibration_routine.hh"
#include "expanders.hh"
#include "fs/norflash_layout.hh"
#include "git_version.h"
#include "gui/helpers/lv_helpers.hh"
#include "gui/pages/base.hh"
#include "gui/pages/confirm_popup.hh"
#include "gui/pages/hardware_test_popup.hh"
#include "gui/pages/page_list.hh"
#include "gui/pages/system_menu_tab_base.hh"
#include "gui/slsexport/meta5/ui.h"
#include "gui/styles.hh"
#include "util/calibrator.hh"

namespace MetaModule
{

struct SystemTab : SystemMenuTab {

	SystemTab(FileStorageProxy &patch_storage,
			  ParamsMidiState &params,
			  MetaParams &metaparams,
			  PatchPlayLoader &patch_playloader,
			  PatchModQueue &patch_mod_queue)
		: storage{patch_storage}
		, patch_playloader{patch_playloader}
		, cal_routine{params, storage, patch_mod_queue}
		, cal_check{params}
		, hw_check{params, metaparams} {

		lv_obj_add_event_cb(ui_SystemCalibrationButton, calibrate_cb, LV_EVENT_CLICKED, this);
		lv_obj_add_event_cb(ui_SystemExpCalibrationButton, calibrate_cb, LV_EVENT_CLICKED, this);
		lv_obj_add_event_cb(ui_SystemCalCheckButton, cal_check_cb, LV_EVENT_CLICKED, this);
		lv_obj_add_event_cb(ui_ResetFactoryPatchesButton, resetbut_cb, LV_EVENT_CLICKED, this);
		lv_obj_add_event_cb(ui_CheckHardwareButton, hwcheck_cb, LV_EVENT_CLICKED, this);

		lv_obj_add_event_cb(ui_SystemCalibrationButton, scroll_up_cb, LV_EVENT_FOCUSED, this);
		lv_obj_add_event_cb(ui_SystemExpCalibrationButton, scroll_up_cb, LV_EVENT_FOCUSED, this);
	}

	void prepare_focus(lv_group_t *group) override {
		this->group = group;

		lv_hide(ui_CalibrationProcedureCont);
		lv_show(ui_SystemCalibrationCont);
		lv_show(ui_SystemCalibrationButton);
		lv_show(ui_SystemExpCalibrationButton, Expanders::get_connected().ext_audio_connected);
		lv_show(ui_SystemCalCheckButton);
		lv_show(ui_SystemResetInternalPatchesCont);
		lv_show(ui_SystemHardwareCheckCont);

		lv_group_remove_obj(ui_SystemCalCheckButton);
		lv_group_remove_obj(ui_SystemCalibrationButton);
		lv_group_remove_obj(ui_SystemExpCalibrationButton);
		lv_group_remove_obj(ui_CalibrationCancelButton);
		lv_group_remove_obj(ui_CalibrationNextButton);
		lv_group_remove_obj(ui_ResetFactoryPatchesButton);
		lv_group_remove_obj(ui_CheckHardwareButton);

		lv_group_add_obj(group, ui_SystemCalCheckButton);
		lv_group_add_obj(group, ui_SystemCalibrationButton);
		lv_group_add_obj(group, ui_SystemExpCalibrationButton);
		lv_group_add_obj(group, ui_CheckHardwareButton);
		lv_group_add_obj(group, ui_ResetFactoryPatchesButton);
		lv_group_add_obj(group, ui_CalibrationCancelButton);
		lv_group_add_obj(group, ui_CalibrationNextButton);

		lv_group_focus_obj(ui_SystemCalCheckButton);
		confirm_popup.init(ui_SystemMenu, group);
	}

	// Returns true if this page uses the back event
	bool consume_back_event() override {
		if (confirm_popup.is_visible()) {
			confirm_popup.hide();
			return true;

		} else if (cal_routine.is_calibrating()) {
			cal_routine.abort();
			patch_playloader.request_reload_playing_patch();
			return true;

		} else if (cal_check.is_visible()) {
			cal_check.hide();
			patch_playloader.request_reload_playing_patch();
			return true;

		} else if (hw_check.is_visible()) {
			hw_check.hide();
			patch_playloader.request_reload_playing_patch();
			return true;

		} else {
			return false;
		}
	}

	void update() override {
		cal_routine.update();
		if (cal_routine.did_complete()) {
			patch_playloader.request_reload_playing_patch();
		}

		if (cal_check.is_visible())
			cal_check.update();

		if (hw_check.is_visible())
			hw_check.update();
	}

private:
	static void calibrate_cb(lv_event_t *event) {
		if (!event || !event->user_data)
			return;
		auto page = static_cast<SystemTab *>(event->user_data);

		page->patch_playloader.request_load_calibration_patch();
		if (event->target == ui_SystemCalibrationButton)
			page->cal_routine.start();
		else if (event->target == ui_SystemExpCalibrationButton)
			page->cal_routine.start_expander();
	}

	static void scroll_up_cb(lv_event_t *event) {
		lv_obj_scroll_to_y(ui_SystemMenuSystemTab, 0, LV_ANIM_ON);
	}

	static void cal_check_cb(lv_event_t *event) {
		if (!event || !event->user_data)
			return;
		auto page = static_cast<SystemTab *>(event->user_data);

		page->patch_playloader.request_load_cal_check_patch();
		page->cal_check.start();
	}

	static void hwcheck_cb(lv_event_t *event) {
		if (!event || !event->user_data)
			return;
		auto page = static_cast<SystemTab *>(event->user_data);

		page->patch_playloader.request_load_hardware_check_patch();
		page->hw_check.show(page->group);
	}

	static void resetbut_cb(lv_event_t *event) {
		if (!event || !event->user_data)
			return;

		auto page = static_cast<SystemTab *>(event->user_data);
		page->confirm_popup.show(
			[page](bool ok) {
				if (ok) {
					page->storage.request_reset_factory_patches();
					while (true) {
						auto msg = page->storage.get_message();
						if (msg.message_type == FileStorageProxy::FactoryResetDone)
							break;
					}
				}
			},
			"Do you really want to PERMANENTLY DELETE all settings and all patches stored internally? The "
			"factory default patches will be restored. You must reboot.\n",
			"Delete");
	}

	FileStorageProxy &storage;
	PatchPlayLoader &patch_playloader;
	ConfirmPopup confirm_popup;
	CalibrationRoutine cal_routine;
	CalCheck cal_check;
	HardwareCheckPopup hw_check;

	lv_group_t *group = nullptr;
};
} // namespace MetaModule
