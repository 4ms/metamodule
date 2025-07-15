#pragma once
#include "gui/helpers/lv_helpers.hh"
#include "gui/slsexport/meta5/ui.h"
#include "gui/styles.hh"
#include "patch/patch_data.hh"
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
		lv_hide(ui_PatchNameEditTextArea);
		lv_group_add_obj(group, ui_DescriptionEditTextArea);

		lv_group_add_obj(group, ui_DescriptionEditSaveButton);
		lv_group_add_obj(group, ui_DescriptionEditCancelButton);

		lv_group_set_editing(group, false);

		lv_obj_add_event_cb(ui_DescriptionClose, closebut_cb, LV_EVENT_CLICKED, this);
		lv_obj_add_event_cb(ui_DescriptionEditButton, editbut_cb, LV_EVENT_CLICKED, this);

		lv_obj_add_event_cb(ui_DescriptionEditTextArea, textarea_cb, LV_EVENT_CLICKED, this);

		lv_obj_add_event_cb(ui_DescriptionEditSaveButton, save_cb, LV_EVENT_CLICKED, this);
		lv_obj_add_event_cb(ui_DescriptionEditCancelButton, cancel_cb, LV_EVENT_CLICKED, this);
	}

	void prepare_focus(lv_group_t *base_group) {
		parent_group = base_group;
		lv_hide(ui_DescriptionPanel);
	}

	void set_patch(PatchData *cur_patch) {
		patch = cur_patch;
	}

	void set_filename(std::string_view name) {
		filename = name;
	}

	bool is_visible() {
		return is_showing;
	}

	bool did_update_names() {
		bool temp = did_save;
		did_save = false;
		return temp;
	}

	void back_event() {
		if (kb_visible) {
			hide_keyboard();
		} else if (edit_panel_visible) {
			show();
		} else {
			hide();
		}
	}

	void show() {
		lv_show(ui_DescriptionPanel);
		lv_hide(ui_DescriptionEditPanel);

		lv_obj_set_parent(ui_DescPanelPatchName, ui_DescriptionPanel);
		lv_obj_move_background(ui_DescPanelPatchName);

		lv_indev_set_group(lv_indev_get_next(nullptr), group);
		lv_group_focus_obj(ui_DescriptionClose);
		lv_group_set_editing(group, false);
		is_showing = true;
		edit_panel_visible = false;

		lv_label_set_text(ui_Description, patch->description.c_str());
		lv_label_set_text(ui_DescPanelPatchName, patch->patch_name.c_str());

		lv_label_set_text(ui_DescPanelFileName, filename.c_str());

		if (patch->midi_poly_num)
			lv_label_set_text_fmt(ui_DescMIDIPolyNumLabel, "MIDI Poly Chans: %u", (unsigned)patch->midi_poly_num);
		else
			lv_label_set_text(ui_DescMIDIPolyNumLabel, "");

		set_content_max_height(ui_DescriptionPanel, 230);
	}

	void hide() {
		lv_hide(ui_DescriptionPanel);
		lv_hide(ui_DescriptionEditPanel);
		lv_hide(ui_Keyboard);
		if (parent_group)
			lv_indev_set_group(lv_indev_get_next(nullptr), parent_group);
		is_showing = false;
		kb_visible = false;
		edit_panel_visible = false;
	}

private:
	static void closebut_cb(lv_event_t *event) {
		auto page = static_cast<PatchDescriptionPanel *>(event->user_data);
		page->hide();
	}

	// Edit button: hide panel, show editable panel
	static void editbut_cb(lv_event_t *event) {
		if (!event || !event->user_data)
			return;
		auto page = static_cast<PatchDescriptionPanel *>(event->user_data);
		lv_hide(ui_DescriptionPanel);
		lv_show(ui_DescriptionEditPanel);

		lv_obj_set_parent(ui_DescPanelPatchName, ui_DescriptionEditPanel);
		lv_obj_move_background(ui_DescPanelPatchName);

		lv_textarea_set_text(ui_DescriptionEditTextArea, lv_label_get_text(ui_Description));
		lv_group_set_editing(page->group, false);

		set_content_max_height(ui_DescriptionEditPanel, 230);

		page->edit_panel_visible = true;
	}

	// Any text area: show keyboard
	static void textarea_cb(lv_event_t *event) {
		if (!event || !event->user_data)
			return;
		auto page = static_cast<PatchDescriptionPanel *>(event->user_data);
		auto kb_hidden = lv_obj_has_flag(ui_Keyboard, LV_OBJ_FLAG_HIDDEN);
		if (kb_hidden) {
			if (event->target == ui_DescriptionEditTextArea) {
				page->show_keyboard();
				lv_keyboard_set_textarea(ui_Keyboard, event->target);
				lv_obj_add_state(event->target, LV_STATE_USER_1);
				set_content_max_height(ui_DescriptionEditPanel, 128);
				set_content_max_height(event->target, 128);
				lv_obj_scroll_to_view_recursive(event->target, LV_ANIM_ON);
				page->active_ta = event->target;
			}
		}
	}

	void show_keyboard() {
		// replace callbacks
		while (lv_obj_remove_event_cb(ui_Keyboard, nullptr))
			;
		lv_obj_add_event_cb(ui_Keyboard, lv_keyboard_def_event_cb, LV_EVENT_VALUE_CHANGED, nullptr);
		lv_obj_add_event_cb(ui_Keyboard, keyboard_cb, LV_EVENT_READY, this);
		lv_obj_add_event_cb(ui_Keyboard, keyboard_cb, LV_EVENT_CANCEL, this);

		lv_show(ui_Keyboard);
		lv_group_add_obj(group, ui_Keyboard);
		lv_group_focus_obj(ui_Keyboard);
		lv_group_set_editing(group, true);

		lv_obj_set_parent(ui_Keyboard, ui_PatchViewPage);
		lv_obj_set_y(ui_Keyboard, 128);
		kb_visible = true;
	}

	void hide_keyboard() {
		lv_obj_clear_state(ui_DescriptionEditTextArea, LV_STATE_USER_1);
		if (active_ta)
			lv_group_focus_obj(active_ta);
		lv_group_remove_obj(ui_Keyboard);
		lv_hide(ui_Keyboard);

		lv_obj_set_height(ui_DescriptionEditTextArea, LV_SIZE_CONTENT);
		set_content_max_height(ui_DescriptionEditPanel, 230);
		kb_visible = false;
	}

	static void save_cb(lv_event_t *event) {
		if (!event || !event->user_data)
			return;
		auto page = static_cast<PatchDescriptionPanel *>(event->user_data);

		if (page->patch) {
			page->patch->description = lv_textarea_get_text(ui_DescriptionEditTextArea);
			lv_label_set_text(ui_Description, lv_textarea_get_text(ui_DescriptionEditTextArea));
			page->did_save = true;
		}
		page->hide();
	}

	static void cancel_cb(lv_event_t *event) {
		if (!event || !event->user_data)
			return;
		auto page = static_cast<PatchDescriptionPanel *>(event->user_data);
		page->hide();
	}

	static void keyboard_cb(lv_event_t *event) {
		if (!event || !event->user_data)
			return;
		auto page = static_cast<PatchDescriptionPanel *>(event->user_data);

		if (event->code == LV_EVENT_READY || event->code == LV_EVENT_CANCEL) {
			page->hide_keyboard();
		}
	}

	lv_group_t *group;
	lv_group_t *parent_group = nullptr;

	lv_obj_t *active_ta = nullptr;

	PatchData *patch = nullptr;

	std::string filename;

	bool is_showing = false;
	bool edit_panel_visible = false;
	bool kb_visible = false;
	bool did_save = false;
};

} // namespace MetaModule
