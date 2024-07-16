#pragma once
#include "calibrate/cal_check.hh"
#include "calibrate/calibration_routine.hh"
#include "fs/norflash_layout.hh"
#include "git_version.h"
#include "gui/helpers/lv_helpers.hh"
#include "gui/pages/base.hh"
#include "gui/pages/confirm_popup.hh"
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
		, cal_routine{params, metaparams, storage, patch_mod_queue}
		, cal_check{params, metaparams} {

		lv_obj_add_event_cb(ui_SystemCalibrationButton, calibrate_cb, LV_EVENT_CLICKED, this);
		lv_obj_add_event_cb(ui_SystemCalCheckButton, cal_check_cb, LV_EVENT_CLICKED, this);
		lv_obj_add_event_cb(ui_ResetFactoryPatchesButton, resetbut_cb, LV_EVENT_CLICKED, this);
	}

	void prepare_focus(lv_group_t *group) override {
		this->group = group;

		lv_hide(ui_CalibrationProcedureCont);
		lv_show(ui_SystemCalibrationCont);
		lv_show(ui_SystemCalibrationButton);
		lv_show(ui_SystemCalCheckButton);
		lv_show(ui_SystemResetInternalPatchesCont);

		lv_group_remove_obj(ui_SystemCalibrationButton);
		lv_group_remove_obj(ui_SystemCalCheckButton);
		lv_group_remove_obj(ui_CalibrationCancelButton);
		lv_group_remove_obj(ui_CalibrationNextButton);
		lv_group_remove_obj(ui_ResetFactoryPatchesButton);

		lv_group_add_obj(group, ui_SystemCalibrationButton);
		lv_group_add_obj(group, ui_SystemCalCheckButton);
		lv_group_add_obj(group, ui_ResetFactoryPatchesButton);
		lv_group_add_obj(group, ui_CalibrationCancelButton);
		lv_group_add_obj(group, ui_CalibrationNextButton);

		lv_group_focus_obj(ui_SystemCalibrationButton);
		confirm_popup.init(ui_SystemMenu, group);
	}

	// Returns true if this pages uses the back event
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
	}

private:
	static void calibrate_cb(lv_event_t *event) {
		if (!event || !event->user_data)
			return;
		auto page = static_cast<SystemTab *>(event->user_data);

		page->patch_playloader.request_load_calibration_patch();
		page->cal_routine.start();
	}

	static void cal_check_cb(lv_event_t *event) {
		if (!event || !event->user_data)
			return;
		auto page = static_cast<SystemTab *>(event->user_data);

		page->patch_playloader.request_load_cal_check_patch();
		page->cal_check.start();
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
	PatchPlayLoader &patch_playloader;
	ConfirmPopup confirm_popup;
	CalibrationRoutine cal_routine;
	CalCheck cal_check;

	lv_group_t *group = nullptr;
};
} // namespace MetaModule
