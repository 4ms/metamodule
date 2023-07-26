#pragma once
#include "lvgl.h"

extern "C" {
#include "gui/slsexport/patchview/ui.h"
}

struct PatchViewSettingsMenu {
	PatchViewSettingsMenu(lv_group_t *base_group)
		: base_group{base_group} {
	}

	void show_settings_menu() {
		auto indev = lv_indev_get_next(nullptr);
		if (!indev)
			return;
		lv_indev_set_group(indev, settings_menu_group);
		lv_group_focus_obj(ui_SettingsCloseButton);
		lv_obj_clear_state(ui_SettingsCloseButton, LV_STATE_PRESSED);
		lv_obj_clear_flag(ui_SettingsMenu, LV_OBJ_FLAG_HIDDEN);
	}

	void hide_settings_menu() {
		auto indev = lv_indev_get_next(nullptr);
		if (!indev)
			return;
		lv_indev_set_group(indev, base_group);
		lv_obj_clear_state(ui_SettingsButton, LV_STATE_PRESSED);
		lv_obj_add_flag(ui_SettingsMenu, LV_OBJ_FLAG_HIDDEN);
	}

	lv_group_t *base_group;
	lv_group_t *settings_menu_group;
};
