#pragma once
#include "gui/elements/map_ring_animate.hh"
#include "gui/helpers/lv_helpers.hh"
#include "gui/pages/view_settings.hh"
#include "gui/slsexport/meta5/ui.h"
#include "lvgl.h"
#include <algorithm>

namespace MetaModule
{

struct ModuleViewSettingsMenu {
	ModuleViewSettingsMenu(ModuleDisplaySettings &settings)
		: settings_menu_group(lv_group_create())
		, settings{settings} {

		lv_obj_add_event_cb(ui_ModuleViewSettingsBut, settings_button_cb, LV_EVENT_CLICKED, this);

		lv_obj_add_event_cb(ui_MVSettingsCloseButton, settings_button_cb, LV_EVENT_CLICKED, this);

		lv_obj_add_event_cb(ui_MVShowControlMapsCheck, map_settings_value_change_cb, LV_EVENT_VALUE_CHANGED, this);
		lv_obj_add_event_cb(ui_MVControlMapTranspSlider, map_settings_value_change_cb, LV_EVENT_VALUE_CHANGED, this);
		lv_obj_add_event_cb(ui_MVFlashMapCheck, map_settings_value_change_cb, LV_EVENT_VALUE_CHANGED, this);

		lv_obj_add_event_cb(ui_MVShowJackMapsCheck, map_settings_value_change_cb, LV_EVENT_VALUE_CHANGED, this);
		lv_obj_add_event_cb(ui_MVJackMapTranspSlider, map_settings_value_change_cb, LV_EVENT_VALUE_CHANGED, this);

		lv_obj_add_event_cb(ui_MVShowPlayingMapsCheck, map_settings_value_change_cb, LV_EVENT_VALUE_CHANGED, this);

		lv_obj_add_event_cb(ui_MVShowAllCablesCheck, cable_settings_value_change_cb, LV_EVENT_VALUE_CHANGED, this);
		lv_obj_add_event_cb(ui_MVCablesTranspSlider, cable_settings_value_change_cb, LV_EVENT_VALUE_CHANGED, this);

		lv_obj_set_x(ui_MVSettingsMenu, 220);
	}

	void prepare_focus(lv_group_t *group) {
		lv_group_remove_all_objs(settings_menu_group);
		lv_group_set_editing(settings_menu_group, false);

		lv_group_add_obj(settings_menu_group, ui_MVSettingsCloseButton);

		lv_group_add_obj(settings_menu_group, ui_MVShowControlMapsCheck);
		lv_group_add_obj(settings_menu_group, ui_MVControlMapTranspSlider);
		lv_group_add_obj(settings_menu_group, ui_MVFlashMapCheck);

		lv_group_add_obj(settings_menu_group, ui_MVShowJackMapsCheck);
		lv_group_add_obj(settings_menu_group, ui_MVJackMapTranspSlider);

		lv_group_add_obj(settings_menu_group, ui_MVShowPlayingMapsCheck);

		lv_group_add_obj(settings_menu_group, ui_MVShowAllCablesCheck);
		lv_group_add_obj(settings_menu_group, ui_MVCablesTranspSlider);

		base_group = group;
		using enum MapRingStyle::Mode;

		fix_forbidden_states();

		lv_check(ui_MVShowControlMapsCheck, settings.param_style.mode != HideAlways);
		lv_check(ui_MVShowJackMapsCheck, settings.param_style.mode != HideAlways);
		lv_check(ui_MVShowAllCablesCheck, settings.cable_style.mode != HideAlways);
		lv_check(ui_MVFlashMapCheck, settings.map_ring_flash_active);

		// "Hide When Not Playing"
		if (settings.param_style.mode == HideAlways && settings.paneljack_style.mode == HideAlways) {
			// Disable if hiding all maps
			lv_disable(ui_MVShowPlayingMapsCheck);
			lv_uncheck(ui_MVShowPlayingMapsCheck);
		} else if (settings.param_style.mode == ShowAllIfPlaying || settings.paneljack_style.mode == ShowAllIfPlaying) {
			lv_enable(ui_MVShowPlayingMapsCheck);
			lv_check(ui_MVShowPlayingMapsCheck);
		} else {
			lv_enable(ui_MVShowPlayingMapsCheck);
			lv_uncheck(ui_MVShowPlayingMapsCheck);
		}

		// 0..100 => 0..255
		{
			uint32_t opacity = (float)settings.param_style.opa / 2.5f;
			opacity = std::clamp<unsigned>(opacity, LV_OPA_0, LV_OPA_COVER);
			lv_slider_set_value(ui_MVControlMapTranspSlider, opacity, LV_ANIM_OFF);
		}
		{
			uint32_t opacity = (float)settings.paneljack_style.opa / 2.5f;
			opacity = std::clamp<unsigned>(opacity, LV_OPA_0, LV_OPA_COVER);
			lv_slider_set_value(ui_MVJackMapTranspSlider, opacity, LV_ANIM_OFF);
		}
		{
			uint32_t opacity = (float)settings.cable_style.opa / 2.5f;
			opacity = std::clamp<unsigned>(opacity, LV_OPA_0, LV_OPA_COVER);
			lv_slider_set_value(ui_MVCablesTranspSlider, opacity, LV_ANIM_OFF);
		}
	}

	void show() {
		if (!visible) {
			DropInFromLeft_Animation(ui_MVSettingsMenu, 0);
			auto indev = lv_indev_get_next(nullptr);
			if (!indev)
				return;
			lv_indev_set_group(indev, settings_menu_group);
			lv_group_focus_obj(ui_MVSettingsCloseButton);
			lv_obj_scroll_to_y(ui_MVSettingsMenu, 0, LV_ANIM_OFF);
			visible = true;
		}
	}

	void hide() {
		if (visible) {
			DropOutToRight_Animation(ui_MVSettingsMenu, 0);
			auto indev = lv_indev_get_next(nullptr);
			if (!indev)
				return;
			if (base_group)
				lv_indev_set_group(indev, base_group);
			visible = false;
		}
	}

	bool is_visible() {
		return visible;
	}

private:
	void fix_forbidden_states() {
		using enum MapRingStyle::Mode;

		if (settings.param_style.mode == CurModuleIfPlaying)
			settings.param_style.mode = ShowAllIfPlaying;
		else if (settings.param_style.mode == CurModule)
			settings.param_style.mode = ShowAll;

		if (settings.paneljack_style.mode == CurModuleIfPlaying)
			settings.paneljack_style.mode = ShowAllIfPlaying;
		else if (settings.paneljack_style.mode == CurModule)
			settings.paneljack_style.mode = ShowAll;

		if (settings.param_style.mode == ShowAllIfPlaying && settings.paneljack_style.mode == ShowAll)
			settings.paneljack_style.mode = ShowAllIfPlaying;

		else if (settings.param_style.mode == ShowAll && settings.paneljack_style.mode == ShowAllIfPlaying)
			settings.paneljack_style.mode = ShowAll;

		if (settings.cable_style.mode != HideAlways)
			settings.cable_style.mode = ShowAll;
	}

	static void settings_button_cb(lv_event_t *event) {
		if (!event || !event->user_data)
			return;
		auto page = static_cast<ModuleViewSettingsMenu *>(event->user_data);

		if (page->visible) {
			page->hide();
		} else {
			page->show();
		}
	}

	static void map_settings_value_change_cb(lv_event_t *event) {
		if (!event || !event->user_data)
			return;

		auto page = static_cast<ModuleViewSettingsMenu *>(event->user_data);

		auto if_playing = lv_obj_has_state(ui_MVShowPlayingMapsCheck, LV_STATE_CHECKED);
		auto show_control_maps = lv_obj_has_state(ui_MVShowControlMapsLabel, LV_STATE_CHECKED);
		auto flash_active = lv_obj_has_state(ui_MVFlashMapCheck, LV_STATE_CHECKED);
		auto show_jack_maps = lv_obj_has_state(ui_MVShowJackMapsCheck, LV_STATE_CHECKED);

		using enum MapRingStyle::Mode;

		page->settings.param_style.mode = show_control_maps && if_playing  ? ShowAllIfPlaying :
										  show_control_maps && !if_playing ? ShowAll :
																			 HideAlways;

		page->settings.paneljack_style.mode = show_jack_maps && if_playing	? ShowAllIfPlaying :
											  show_jack_maps && !if_playing ? ShowAll :
																			  HideAlways;

		auto opacity = lv_slider_get_value(ui_MVControlMapTranspSlider); //0..100
		opacity = (float)opacity * 2.5f;
		page->settings.param_style.opa = opacity;

		opacity = lv_slider_get_value(ui_MVJackMapTranspSlider); //0..100
		opacity = (float)opacity * 2.5f;
		page->settings.paneljack_style.opa = opacity;

		page->settings.map_ring_flash_active = flash_active;
		page->settings.changed = true;

		if (!show_control_maps && !show_jack_maps && if_playing)
			lv_uncheck(ui_MVShowPlayingMapsCheck);
	}

	static void cable_settings_value_change_cb(lv_event_t *event) {
		if (!event || !event->user_data)
			return;
		lv_event_code_t event_code = lv_event_get_code(event);

		if (event_code == LV_EVENT_VALUE_CHANGED) {
			using enum MapRingStyle::Mode;

			auto page = static_cast<ModuleViewSettingsMenu *>(event->user_data);
			auto show_all = lv_obj_has_state(ui_MVShowAllCablesCheck, LV_STATE_CHECKED);

			page->settings.cable_style.mode = show_all ? ShowAll : HideAlways;

			auto opacity = lv_slider_get_value(ui_MVCablesTranspSlider); //0..100
			opacity = (float)opacity * 2.5f;
			page->settings.cable_style.opa = opacity;
			page->settings.changed = true;
		}
	}

	lv_group_t *base_group = nullptr;
	lv_group_t *settings_menu_group = nullptr;
	bool visible = false;
	ModuleDisplaySettings &settings;
};

} // namespace MetaModule
