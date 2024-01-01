#pragma once
#include "gui/helpers/lv_helpers.hh"
#include "gui/slsexport/meta5/ui.h"
#include "gui/styles.hh"
#include "patch_data.hh"
#include "pr_dbg.hh"
#include "src/core/lv_event.h"

namespace MetaModule
{

struct PatchDescriptionPanel {

	PatchDescriptionPanel()
		: group(lv_group_create()) {

		lv_group_add_obj(group, ui_DescriptionEditButton);
		lv_group_add_obj(group, ui_DescriptionClose);

		lv_hide(ui_DescriptionEditPanel);
		lv_group_add_obj(group, ui_PatchNameEditTextArea);
		lv_group_add_obj(group, ui_DescriptionEditTextArea);

		lv_group_set_editing(group, false);

		lv_obj_add_event_cb(ui_InfoButton, openbut_cb, LV_EVENT_CLICKED, this);
		lv_obj_add_event_cb(ui_DescriptionClose, closebut_cb, LV_EVENT_CLICKED, this);
		lv_obj_add_event_cb(ui_DescriptionEditButton, editbut_cb, LV_EVENT_CLICKED, this);
	}

	void prepare_focus(lv_group_t *base_group, PatchData const &patch) {
		parent_group = base_group;

		lv_hide(ui_DescriptionPanel);
		lv_label_set_text(ui_Description, patch.description.c_str());
		lv_label_set_text(ui_DescPanelPatchName, patch.patch_name.c_str());

		// remove all callbacks
		while (lv_obj_remove_event_cb(ui_Keyboard, nullptr))
			;
		lv_obj_add_event_cb(ui_Keyboard, lv_keyboard_def_event_cb, LV_EVENT_VALUE_CHANGED, nullptr);
		lv_obj_add_event_cb(ui_Keyboard, keyboard_cb, LV_EVENT_READY, this);
		lv_obj_add_event_cb(ui_Keyboard, keyboard_cb, LV_EVENT_CANCEL, this);
	}

	bool is_visible() {
		return is_showing;
	}

	void show() {
		lv_show(ui_DescriptionPanel);
		lv_hide(ui_DescriptionEditPanel);
		lv_indev_set_group(lv_indev_get_act(), group);
		lv_group_focus_obj(ui_DescriptionClose);
		lv_group_set_editing(group, false);
		is_showing = true;
	}

	void hide() {
		lv_hide(ui_DescriptionPanel);
		lv_hide(ui_DescriptionEditPanel);
		lv_hide(ui_Keyboard);
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
		auto page = static_cast<PatchDescriptionPanel *>(event->user_data);
		lv_hide(ui_DescriptionPanel);
		lv_show(ui_DescriptionEditPanel);
		lv_textarea_set_placeholder_text(ui_PatchNameEditTextArea, lv_label_get_text(ui_DescPanelPatchName));
		lv_textarea_set_placeholder_text(ui_DescriptionEditTextArea, lv_label_get_text(ui_Description));

		lv_show(ui_Keyboard);
		lv_group_add_obj(page->group, ui_Keyboard);
		lv_group_focus_obj(ui_Keyboard);
		lv_group_set_editing(page->group, true);

		lv_obj_set_parent(ui_Keyboard, ui_PatchViewPage);
		lv_keyboard_set_textarea(ui_Keyboard, ui_PatchNameEditTextArea);
		lv_obj_set_y(ui_Keyboard, 128);
	}

	static void keyboard_cb(lv_event_t *event) {
		if (!event || !event->user_data)
			return;

		// auto page = static_cast<PatchDescriptionPanel *>(event->user_data);
		if (event->code == LV_EVENT_READY || event->code == LV_EVENT_CANCEL) {
			lv_group_focus_obj(ui_PatchNameEditTextArea);
			lv_group_remove_obj(ui_Keyboard);
			lv_hide(ui_Keyboard);
			// page->map.alias_name = lv_textarea_get_text(ui_AliasTextArea);
		}
	}
};

} // namespace MetaModule
