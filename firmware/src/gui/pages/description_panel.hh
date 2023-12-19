#pragma once
#include "gui/helpers/lv_helpers.hh"
#include "gui/slsexport/meta5/ui.h"
#include "gui/styles.hh"
#include "patch_data.hh"
#include "pr_dbg.hh"

namespace MetaModule
{

struct PatchDescriptionPanel {

	PatchDescriptionPanel()
		: group(lv_group_create()) {

		lv_group_add_obj(group, ui_DescriptionEdit);
		lv_group_add_obj(group, ui_DescriptionClose);
		lv_group_set_editing(group, false);

		lv_obj_add_event_cb(ui_InfoButton, openbut_cb, LV_EVENT_CLICKED, this);
		lv_obj_add_event_cb(ui_DescriptionClose, closebut_cb, LV_EVENT_CLICKED, this);
		lv_obj_add_event_cb(ui_DescriptionEdit, editbut_cb, LV_EVENT_CLICKED, this);
	}

	void prepare_focus(lv_group_t *base_group, PatchData const &patch) {
		parent_group = base_group;

		lv_hide(ui_DescriptionPanel);
		lv_label_set_text(ui_Description, patch.description.c_str());
		lv_label_set_text(ui_DescPanelPatchName, patch.patch_name.c_str());
	}

	bool is_visible() {
		return is_showing;
	}

	void show() {
		lv_show(ui_DescriptionPanel);
		lv_indev_set_group(lv_indev_get_act(), group);
		lv_group_focus_obj(ui_DescriptionClose);
		lv_group_set_editing(group, false);
		is_showing = true;
	}

	void hide() {
		lv_hide(ui_DescriptionPanel);
		if (parent_group)
			lv_indev_set_group(lv_indev_get_next(nullptr), parent_group);
		is_showing = false;
	}

private:
	lv_group_t *group = nullptr;
	lv_group_t *parent_group = nullptr;
	bool is_showing = false;

	static void closebut_cb(lv_event_t *event) {
		auto page = static_cast<PatchDescriptionPanel *>(event->user_data);
		page->hide();
	}

	static void openbut_cb(lv_event_t *event) {
		auto page = static_cast<PatchDescriptionPanel *>(event->user_data);
		page->show();
	}

	static void editbut_cb(lv_event_t *event) {
		// auto page = static_cast<PatchDescriptionPanel *>(event->user_data);
	}
};

} // namespace MetaModule
