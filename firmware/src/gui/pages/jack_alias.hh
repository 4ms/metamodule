#pragma once
#include "gui/gui_state.hh"
#include "gui/helpers/lv_helpers.hh"
#include "gui/pages/confirm_popup.hh"
#include "gui/slsexport/meta5/ui.h"

namespace MetaModule
{

struct JackAliasNameEdit {

	JackAliasNameEdit(GuiState &gui_state)
		: group{lv_group_create()}
		, text_field_popup{lv_obj_create(lv_layer_top())}
		, text_field{lv_label_create(text_field_popup)}
		, gui_state{gui_state} {
		lv_hide(text_field_popup);
		lv_hide(text_field);

		lv_obj_set_align(text_field_popup, LV_ALIGN_TOP_MID);
		lv_obj_set_pos(text_field_popup, 0, 0);
		lv_obj_set_size(text_field_popup, lv_pct(100), lv_pct(80));
		lv_obj_set_style_bg_color(text_field, lv_color_hex(0x333333), 0);
		lv_obj_set_style_bg_opa(text_field, LV_OPA_100, 0);

		lv_obj_set_pos(text_field, 0, 0);
		lv_obj_set_size(text_field, 160, 28);
		lv_obj_set_align(text_field, LV_ALIGN_TOP_MID);
		lv_obj_set_style_bg_color(text_field, lv_color_hex(0x666666), 0);
		lv_obj_set_style_bg_opa(text_field, LV_OPA_100, 0);

		lv_obj_set_style_border_color(text_field, lv_color_hex(0x999999), 0);
		lv_obj_set_style_border_opa(text_field, LV_OPA_100, 0);

		lv_group_add_obj(group, text_field);
	}

	void prepare_focus(lv_obj_t *, lv_group_t *group) {
		parent_group = group;
		reset_keyboard(text_field_popup);
		kb_popup.init(text_field_popup, parent_group);
	}

	void update() {
		// if (!kb_visible)
		// 	lv_group_set_editing(group, false);

		// if (!text_field)
		// 	return;
	}

	bool is_visible() const {
		return kb_visible;
	}

	void back() {
		if (kb_visible) {
			if (alias == lv_textarea_get_text(text_field)) {
				save_jackalias_name(false);
			} else {
				kb_popup.show([this](bool ok) { save_jackalias_name(ok); }, "Do you want to keep your edits?", "Keep");
			}
		} else if (kb_popup.is_visible()) {
			kb_popup.hide();
		}
	}

	void reset_keyboard(lv_obj_t *parent_obj) {
		while (lv_obj_remove_event_cb(ui_Keyboard, nullptr))
			;
		lv_obj_add_event_cb(ui_Keyboard, lv_keyboard_def_event_cb, LV_EVENT_VALUE_CHANGED, nullptr);
		lv_obj_add_event_cb(ui_Keyboard, keyboard_cb, LV_EVENT_READY, this);
		lv_obj_add_event_cb(ui_Keyboard, keyboard_cb, LV_EVENT_CANCEL, this);

		lv_obj_set_parent(ui_Keyboard, parent_obj);
		lv_obj_set_y(ui_Keyboard, 40);

		lv_hide(ui_Keyboard);
		lv_hide(text_field_popup);
	}

	void save_jackalias_name(bool save = true) {
		lv_obj_clear_state(text_field, LV_STATE_USER_1);
		lv_group_focus_obj(text_field);
		lv_group_remove_obj(ui_Keyboard);
		lv_hide(ui_Keyboard);
		kb_visible = false;

		if (save) {
			alias = lv_textarea_get_text(text_field);
			printf("Save alias: %s\n", alias.c_str());

			// patches.mark_view_patch_modified();
		}

		// update_knobset_text_area();

		lv_group_activate(parent_group);
	}

	void show_keyboard(uint32_t panel_jack_id, bool is_input) {
		lv_show(text_field_popup);
		lv_show(text_field);
		lv_show(ui_Keyboard);

		lv_group_add_obj(group, ui_Keyboard);
		lv_group_focus_obj(ui_Keyboard);
		lv_group_set_editing(group, true);

		lv_group_activate(group);

		lv_keyboard_set_textarea(ui_Keyboard, text_field);
		lv_obj_add_state(text_field, LV_STATE_USER_1);

		kb_visible = true;
	}

	static void keyboard_cb(lv_event_t *event) {
		if (!event || !event->user_data)
			return;
		auto page = static_cast<JackAliasNameEdit *>(event->user_data);

		if (event->code == LV_EVENT_READY || event->code == LV_EVENT_CANCEL) {
			page->save_jackalias_name();
		}
	}

private:
	lv_group_t *group = nullptr;
	lv_group_t *parent_group = nullptr;

	lv_obj_t *text_field_popup;
	lv_obj_t *text_field;

	bool kb_visible = false;
	GuiState &gui_state;
	ConfirmPopup kb_popup;

	std::string alias;
};

//
} // namespace MetaModule
