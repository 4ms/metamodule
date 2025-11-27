#pragma once
#include "gui/gui_state.hh"
#include "gui/helpers/lv_helpers.hh"
#include "gui/pages/confirm_popup.hh"
#include "gui/ui_lvgl/meta5/ui.h"
#include "util/callable.hh"

namespace MetaModule
{

struct KeyboardEntry {

	KeyboardEntry()
		: group{lv_group_create()} {
	}

	void prepare_focus(lv_obj_t *parent_obj, lv_group_t *group) {
		parent_group = group;
		text_field = nullptr;
		reset_keyboard();
		lv_obj_set_parent(ui_Keyboard, parent_obj);
		kb_popup.init(parent_obj, parent_group);
	}

	void show_keyboard(lv_obj_t *textarea_field, FunctionSized<16, void(std::string_view)> save_callback) {
		text_field = textarea_field;

		save_cb = save_callback;

		if (!text_field)
			return;

		lv_show(ui_Keyboard);

		lv_group_add_obj(group, ui_Keyboard);
		lv_group_focus_obj(ui_Keyboard);
		lv_group_set_editing(group, true);

		lv_group_activate(group);

		lv_keyboard_set_textarea(ui_Keyboard, text_field);
		lv_obj_add_state(text_field, LV_STATE_USER_1);

		text_value = lv_textarea_get_text(text_field);

		kb_visible = true;
	}

	bool is_visible() const {
		return kb_visible;
	}

	void back() {
		if (kb_popup.is_visible()) {
			kb_popup.hide();

		} else if (kb_visible && text_field) {
			if (text_value == lv_textarea_get_text(text_field)) {
				hide();
			} else {
				kb_popup.show(
					[this](bool ok) {
						if (ok)
							save();
						else
							lv_textarea_set_text(text_field, text_value.c_str());

						hide();
					},
					"Do you want to keep your edits?",
					"Keep");
			}
		}
	}

	void hide() {
		if (kb_visible) {
			if (text_field) {
				lv_obj_clear_state(text_field, LV_STATE_USER_1);
				lv_group_focus_obj(text_field);
			}
			lv_group_remove_obj(ui_Keyboard);
			lv_hide(ui_Keyboard);
			kb_visible = false;
			text_field = nullptr;

			lv_group_activate(parent_group);
		}
	}

private:
	void reset_keyboard() {
		while (lv_obj_remove_event_cb(ui_Keyboard, nullptr))
			;
		lv_obj_add_event_cb(ui_Keyboard, lv_keyboard_def_event_cb, LV_EVENT_VALUE_CHANGED, nullptr);
		lv_obj_add_event_cb(ui_Keyboard, keyboard_cb, LV_EVENT_READY, this);
		lv_obj_add_event_cb(ui_Keyboard, keyboard_cb, LV_EVENT_CANCEL, this);

		lv_hide(ui_Keyboard);
	}

	void save() {
		if (text_field)
			text_value = lv_textarea_get_text(text_field);
		if (save_cb)
			save_cb(text_value.c_str());
	}

	static void keyboard_cb(lv_event_t *event) {
		if (!event || !event->user_data)
			return;
		auto page = static_cast<KeyboardEntry *>(event->user_data);

		if (event->code == LV_EVENT_READY || event->code == LV_EVENT_CANCEL) {
			page->save();
			page->hide();
		}
	}

	lv_group_t *group = nullptr;
	lv_group_t *parent_group = nullptr;

	lv_obj_t *text_field = nullptr;

	bool kb_visible = false;
	ConfirmPopup kb_popup;

	FunctionSized<16, void(std::string_view)> save_cb;
	std::string text_value;
};

//
} // namespace MetaModule
