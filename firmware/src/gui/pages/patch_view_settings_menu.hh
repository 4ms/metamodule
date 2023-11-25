#pragma once
#include "gui/elements/map_ring_animate.hh"
#include "gui/slsexport/meta5/ui.h"
#include "lvgl.h"
#include <algorithm>

namespace MetaModule
{

struct PatchViewSettingsMenu {
	struct ViewSettings {
		bool map_ring_flash_active = true;
		bool scroll_to_active_param = false;
		MapRingDisplay::Style map_ring_style = {.mode = MapRingDisplay::StyleMode::CurModuleIfPlaying,
												.opa = LV_OPA_50};
		MapRingDisplay::Style cable_style = {.mode = MapRingDisplay::StyleMode::ShowAll, .opa = LV_OPA_50};
		bool changed = true;
	};

	PatchViewSettingsMenu(ViewSettings &settings)
		: settings{settings} {
	}

	void init() {
		//Must be called after ui_PatchViewPage_screen_init(), so this can't be in the constructor:
		lv_obj_set_parent(ui_SettingsMenu, lv_layer_top());
		lv_obj_add_event_cb(ui_SettingsButton, settings_button_cb, LV_EVENT_CLICKED, this);
		lv_obj_add_event_cb(ui_SettingsCloseButton, settings_button_cb, LV_EVENT_CLICKED, this);

		lv_obj_add_event_cb(ui_ShowAllMapsCheck, map_settings_value_change_cb, LV_EVENT_VALUE_CHANGED, this);
		lv_obj_add_event_cb(ui_ShowSelectedMapsCheck, map_settings_value_change_cb, LV_EVENT_VALUE_CHANGED, this);
		lv_obj_add_event_cb(ui_ShowPlayingMapsCheck, map_settings_value_change_cb, LV_EVENT_VALUE_CHANGED, this);
		lv_obj_add_event_cb(ui_FlashMapCheck, map_settings_value_change_cb, LV_EVENT_VALUE_CHANGED, this);
		lv_obj_add_event_cb(ui_MapTranspSlider, map_settings_value_change_cb, LV_EVENT_VALUE_CHANGED, this);

		lv_obj_add_event_cb(ui_ShowAllCablesCheck, cable_settings_value_change_cb, LV_EVENT_VALUE_CHANGED, this);
		lv_obj_add_event_cb(ui_CablesTranspSlider, cable_settings_value_change_cb, LV_EVENT_VALUE_CHANGED, this);

		visible = false;
		lv_obj_set_x(ui_SettingsMenu, 220);
	}

	void focus(lv_group_t *group) {
		base_group = group;
		settings_menu_group = lv_group_create();
		lv_group_remove_all_objs(settings_menu_group);
		lv_group_set_editing(settings_menu_group, false);
		lv_group_add_obj(settings_menu_group, ui_SettingsCloseButton);
		lv_group_add_obj(settings_menu_group, ui_ShowAllMapsCheck);
		lv_group_add_obj(settings_menu_group, ui_ShowSelectedMapsCheck);
		lv_group_add_obj(settings_menu_group, ui_ShowPlayingMapsCheck);
		lv_group_add_obj(settings_menu_group, ui_FlashMapCheck);
		lv_group_add_obj(settings_menu_group, ui_MapTranspSlider);
		lv_group_add_obj(settings_menu_group, ui_ShowAllCablesCheck);
		lv_group_add_obj(settings_menu_group, ui_CablesTranspSlider);

		using enum MapRingDisplay::StyleMode;
		switch (settings.map_ring_style.mode) {
			case ShowAllIfPlaying:
				lv_obj_add_state(ui_ShowAllMapsCheck, LV_STATE_CHECKED);
				lv_obj_clear_state(ui_ShowSelectedMapsCheck, LV_STATE_CHECKED);
				lv_obj_add_state(ui_ShowPlayingMapsCheck, LV_STATE_CHECKED);
				break;

			case ShowAll:
				lv_obj_add_state(ui_ShowAllMapsCheck, LV_STATE_CHECKED);
				lv_obj_clear_state(ui_ShowSelectedMapsCheck, LV_STATE_CHECKED);
				lv_obj_clear_state(ui_ShowPlayingMapsCheck, LV_STATE_CHECKED);
				break;

			case CurModuleIfPlaying:
				lv_obj_clear_state(ui_ShowAllMapsCheck, LV_STATE_CHECKED);
				lv_obj_add_state(ui_ShowSelectedMapsCheck, LV_STATE_CHECKED);
				lv_obj_add_state(ui_ShowPlayingMapsCheck, LV_STATE_CHECKED);
				break;

			case CurModule:
				lv_obj_clear_state(ui_ShowAllMapsCheck, LV_STATE_CHECKED);
				lv_obj_add_state(ui_ShowSelectedMapsCheck, LV_STATE_CHECKED);
				lv_obj_clear_state(ui_ShowPlayingMapsCheck, LV_STATE_CHECKED);
				break;

			case HideAlways:
				lv_obj_clear_state(ui_ShowAllMapsCheck, LV_STATE_CHECKED);
				lv_obj_add_state(ui_ShowSelectedMapsCheck, LV_STATE_CHECKED);
				lv_obj_clear_state(ui_ShowPlayingMapsCheck, LV_STATE_CHECKED);
				break;
		}

		if (settings.map_ring_flash_active)
			lv_obj_add_state(ui_FlashMapCheck, LV_STATE_CHECKED);
		else
			lv_obj_clear_state(ui_FlashMapCheck, LV_STATE_CHECKED);

		// 0..100 => 0..255
		uint32_t opacity = (float)settings.map_ring_style.opa / 2.5f;
		opacity = std::clamp<unsigned>(opacity, LV_OPA_0, LV_OPA_COVER);
	}

	void blur() {
		if (settings_menu_group) {
			lv_group_del(settings_menu_group);
			settings_menu_group = nullptr;
		}
	}

	void show() {
		if (!visible) {
			Dropdown_Animation(ui_SettingsMenu, 0);
			auto indev = lv_indev_get_next(nullptr);
			if (!indev)
				return;
			lv_indev_set_group(indev, settings_menu_group);
			lv_group_focus_obj(ui_SettingsCloseButton);
			lv_obj_clear_state(ui_SettingsCloseButton, LV_STATE_PRESSED);
			lv_obj_scroll_to_y(ui_SettingsMenu, 0, LV_ANIM_OFF);
			visible = true;
		}
	}

	void hide() {
		if (visible) {
			Dropup_Animation(ui_SettingsMenu, 0);
			auto indev = lv_indev_get_next(nullptr);
			if (!indev)
				return;
			if (base_group)
				lv_indev_set_group(indev, base_group);
			lv_obj_clear_state(ui_SettingsButton, LV_STATE_PRESSED);
			visible = false;
		}
	}

	static void settings_button_cb(lv_event_t *event) {
		if (!event || !event->user_data)
			return;
		auto page = static_cast<PatchViewSettingsMenu *>(event->user_data);

		if (page->visible) {
			page->hide();
		} else {
			page->show();
		}
	}

	static void map_settings_value_change_cb(lv_event_t *event) {
		if (!event || !event->user_data)
			return;
		lv_event_code_t event_code = lv_event_get_code(event);
		auto obj = lv_event_get_target(event);

		if (event_code == LV_EVENT_VALUE_CHANGED) {
			auto show_all = lv_obj_has_state(ui_ShowAllMapsCheck, LV_STATE_CHECKED);
			auto show_selected = lv_obj_has_state(ui_ShowSelectedMapsCheck, LV_STATE_CHECKED);
			auto show_only_playing = lv_obj_has_state(ui_ShowPlayingMapsCheck, LV_STATE_CHECKED);
			auto flash_active = lv_obj_has_state(ui_FlashMapCheck, LV_STATE_CHECKED);

			// Do not allow both ShowAll and ShowSelected to be checked
			if (obj == ui_ShowAllMapsCheck && show_all) {
				lv_obj_clear_state(ui_ShowSelectedMapsCheck, LV_STATE_CHECKED);
				show_selected = false;
			} else if (obj == ui_ShowSelectedMapsCheck && show_selected) {
				lv_obj_clear_state(ui_ShowAllMapsCheck, LV_STATE_CHECKED);
				show_all = false;
			}

			auto page = static_cast<PatchViewSettingsMenu *>(event->user_data);
			{
				using enum MapRingDisplay::StyleMode;
				auto &style = page->settings.map_ring_style;

				style.mode = show_only_playing ? ShowAllIfPlaying : ShowAll;
				if (show_all)
					style.mode = show_only_playing ? ShowAllIfPlaying : ShowAll;
				else if (show_selected)
					style.mode = show_only_playing ? CurModuleIfPlaying : CurModule;
				else
					style.mode = HideAlways;
			}

			auto opacity = lv_slider_get_value(ui_MapTranspSlider); //0..100
			opacity = (float)opacity * 2.5f;
			page->settings.map_ring_style.opa = opacity;
			page->settings.map_ring_flash_active = flash_active;
			page->settings.changed = true;
		}
	}

	static void cable_settings_value_change_cb(lv_event_t *event) {
		if (!event || !event->user_data)
			return;
		lv_event_code_t event_code = lv_event_get_code(event);

		if (event_code == LV_EVENT_VALUE_CHANGED) {
			auto show_all = lv_obj_has_state(ui_ShowAllCablesCheck, LV_STATE_CHECKED);
			auto page = static_cast<PatchViewSettingsMenu *>(event->user_data);
			using enum MapRingDisplay::StyleMode;
			page->settings.cable_style.mode = show_all ? ShowAll : HideAlways;

			auto opacity = lv_slider_get_value(ui_CablesTranspSlider); //0..100
			opacity = (float)opacity * 2.5f;
			page->settings.cable_style.opa = opacity;
			page->settings.changed = true;
		}
	}

	lv_group_t *base_group = nullptr;
	lv_group_t *settings_menu_group = nullptr;
	bool visible = false;
	ViewSettings &settings;
};

} // namespace MetaModule
