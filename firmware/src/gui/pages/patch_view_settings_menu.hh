#pragma once
#include "gui/gui_state.hh"
#include "gui/helpers/lv_helpers.hh"
#include "gui/slsexport/meta5/ui.h"
#include "gui/slsexport/ui_local.h"
#include "lvgl.h"
#include "user_settings/view_settings.hh"
#include <algorithm>

namespace MetaModule
{

struct PatchViewSettingsMenu {
	PatchViewSettingsMenu(ModuleDisplaySettings &settings, GuiState &gui_state)
		: settings_menu_group(lv_group_create())
		, settings{settings}
		, gui_state{gui_state} {

		auto graphics_title = create_settings_menu_title(ui_PVSettingsMenu, "GRAPHICS");

		auto graphics_settings = create_settings_menu_switch(ui_PVSettingsMenu, "Draw Screens");
		graphics_show_check = lv_obj_get_child(graphics_settings, 1);

		graphics_update_rate_label = create_settings_menu_slider(ui_PVSettingsMenu, "Update Rate");
		lv_obj_set_style_text_font(graphics_update_rate_label, &ui_font_MuseoSansRounded50014, 0);
		lv_obj_set_width(graphics_update_rate_label, lv_pct(100));
		lv_obj_set_align(graphics_update_rate_label, LV_ALIGN_LEFT_MID);

		graphics_update_rate_slider = lv_obj_get_child(graphics_update_rate_label, 0);
		lv_obj_set_width(graphics_update_rate_slider, lv_pct(40));
		lv_slider_set_range(graphics_update_rate_slider, 0, ModuleDisplaySettings::ThrottleAmounts.size() - 1);
		lv_slider_set_value(
			graphics_update_rate_slider, ModuleDisplaySettings::ThrottleAmounts.size() - 2, LV_ANIM_OFF);

		lv_obj_move_to_index(graphics_title, 1);
		lv_obj_move_to_index(graphics_settings, 2);
		lv_obj_move_to_index(graphics_update_rate_label, 3);

		auto bar_title = create_settings_menu_title(ui_PVSettingsMenu, "STATUS BAR");

		auto show_samplerate_cont = create_settings_menu_switch(ui_PVSettingsMenu, "Show Audio Settings");
		show_samplerate_check = lv_obj_get_child(show_samplerate_cont, 1);

		auto float_samplerate_cont = create_settings_menu_switch(ui_PVSettingsMenu, "Keep Status on top");
		lv_obj_set_style_border_width(float_samplerate_cont, 0, 0);
		float_audioload_check = lv_obj_get_child(float_samplerate_cont, 1);

		auto show_knobset_cont = create_settings_menu_switch(ui_PVSettingsMenu, "Show KnobSet Name");
		show_knobset_name_check = lv_obj_get_child(show_knobset_cont, 1);

		lv_obj_move_to_index(bar_title, 4);
		lv_obj_move_to_index(show_samplerate_cont, 5);
		lv_obj_move_to_index(float_samplerate_cont, 6);
		lv_obj_move_to_index(show_knobset_cont, 7);

		lv_obj_set_parent(ui_PVSettingsMenu, lv_layer_top());
		lv_obj_add_event_cb(ui_SettingsButton, settings_button_cb, LV_EVENT_CLICKED, this);

		lv_obj_add_event_cb(ui_PVSettingsCloseButton, settings_button_cb, LV_EVENT_CLICKED, this);

		lv_obj_add_event_cb(ui_PVShowControlMapsCheck, map_settings_value_change_cb, LV_EVENT_VALUE_CHANGED, this);
		lv_obj_add_event_cb(ui_PVControlMapTranspSlider, map_settings_value_change_cb, LV_EVENT_VALUE_CHANGED, this);
		lv_obj_add_event_cb(ui_PVFlashMapCheck, map_settings_value_change_cb, LV_EVENT_VALUE_CHANGED, this);

		lv_obj_add_event_cb(ui_PVShowJackMapsCheck, map_settings_value_change_cb, LV_EVENT_VALUE_CHANGED, this);
		lv_obj_add_event_cb(ui_PVJackMapTranspSlider, map_settings_value_change_cb, LV_EVENT_VALUE_CHANGED, this);

		lv_obj_add_event_cb(ui_PVShowMapsAlwaysCheck, map_settings_value_change_cb, LV_EVENT_VALUE_CHANGED, this);
		lv_obj_add_event_cb(ui_PVShowMapsAllModulesCheck, map_settings_value_change_cb, LV_EVENT_VALUE_CHANGED, this);

		lv_obj_add_event_cb(ui_PVShowAllCablesCheck, cable_settings_value_change_cb, LV_EVENT_VALUE_CHANGED, this);
		lv_obj_add_event_cb(ui_PVCablesTranspSlider, cable_settings_value_change_cb, LV_EVENT_VALUE_CHANGED, this);

		lv_obj_set_x(ui_PVSettingsMenu, 220);

		lv_obj_add_event_cb(graphics_show_check, graphics_settings_value_change_cb, LV_EVENT_VALUE_CHANGED, this);
		lv_obj_add_event_cb(
			graphics_update_rate_slider, graphics_settings_value_change_cb, LV_EVENT_VALUE_CHANGED, this);

		lv_obj_add_event_cb(graphics_show_check, scroll_menu_down_cb, LV_EVENT_FOCUSED, this);

		lv_obj_add_event_cb(show_samplerate_check, show_titlebar_cb, LV_EVENT_VALUE_CHANGED, this);
		lv_obj_add_event_cb(float_audioload_check, show_titlebar_cb, LV_EVENT_VALUE_CHANGED, this);
		lv_obj_add_event_cb(show_knobset_name_check, show_titlebar_cb, LV_EVENT_VALUE_CHANGED, this);

		lv_group_remove_all_objs(settings_menu_group);
		lv_group_set_editing(settings_menu_group, false);
		lv_group_add_obj(settings_menu_group, ui_PVSettingsCloseButton);

		lv_group_add_obj(settings_menu_group, graphics_show_check);
		lv_group_add_obj(settings_menu_group, graphics_update_rate_slider);

		lv_group_add_obj(settings_menu_group, show_samplerate_check);
		lv_group_add_obj(settings_menu_group, float_audioload_check);
		lv_group_add_obj(settings_menu_group, show_knobset_name_check);

		lv_group_add_obj(settings_menu_group, ui_PVShowControlMapsCheck);
		lv_group_add_obj(settings_menu_group, ui_PVControlMapTranspSlider);
		lv_group_add_obj(settings_menu_group, ui_PVFlashMapCheck);

		lv_group_add_obj(settings_menu_group, ui_PVShowJackMapsCheck);
		lv_group_add_obj(settings_menu_group, ui_PVJackMapTranspSlider);

		lv_group_add_obj(settings_menu_group, ui_PVShowMapsAlwaysCheck);
		lv_group_add_obj(settings_menu_group, ui_PVShowMapsAllModulesCheck);

		lv_group_add_obj(settings_menu_group, ui_PVShowAllCablesCheck);
		lv_group_add_obj(settings_menu_group, ui_PVCablesTranspSlider);
	}

	void prepare_focus(lv_group_t *group) {
		base_group = group;

		fix_forbidden_states();

		using enum MapRingStyle::Mode;

		lv_check(ui_PVShowControlMapsCheck, settings.param_style.mode != HideAlways);
		lv_check(ui_PVShowJackMapsCheck, settings.paneljack_style.mode != HideAlways);
		lv_check(ui_PVShowAllCablesCheck, settings.cable_style.mode != HideAlways);
		lv_check(ui_PVFlashMapCheck, settings.map_ring_flash_active);

		lv_check(ui_PVShowMapsAlwaysCheck,
				 settings.param_style.mode == ShowAll || settings.param_style.mode == CurModule ||
					 settings.paneljack_style.mode == ShowAll || settings.paneljack_style.mode == CurModule);

		lv_check(ui_PVShowMapsAllModulesCheck,
				 settings.param_style.mode == ShowAll || settings.param_style.mode == ShowAllIfPlaying ||
					 settings.paneljack_style.mode == ShowAll || settings.paneljack_style.mode == ShowAllIfPlaying);

		lv_check(graphics_show_check, settings.show_graphic_screens);

		lv_check(show_samplerate_check, settings.show_samplerate);
		lv_check(float_audioload_check, settings.float_loadmeter);
		lv_check(show_knobset_name_check, settings.show_knobset_name);

		update_interactive_states();

		// 0..100 => 0..255
		{
			uint32_t opacity = (float)settings.param_style.opa / 2.5f;
			opacity = std::clamp<unsigned>(opacity, LV_OPA_0, LV_OPA_COVER);
			lv_slider_set_value(ui_PVControlMapTranspSlider, opacity, LV_ANIM_OFF);
		}
		{
			uint32_t opacity = (float)settings.paneljack_style.opa / 2.5f;
			opacity = std::clamp<unsigned>(opacity, LV_OPA_0, LV_OPA_COVER);
			lv_slider_set_value(ui_PVJackMapTranspSlider, opacity, LV_ANIM_OFF);
		}
		{
			uint32_t opacity = (float)settings.cable_style.opa / 2.5f;
			opacity = std::clamp<unsigned>(opacity, LV_OPA_0, LV_OPA_COVER);
			lv_slider_set_value(ui_PVCablesTranspSlider, opacity, LV_ANIM_OFF);
		}
		{
			int slider_val = ModuleDisplaySettings::ThrottleAmounts.size() - 2;
			auto throttle = settings.graphic_screen_throttle;
			if (auto found = std::ranges::find(ModuleDisplaySettings::ThrottleAmounts, throttle)) {
				slider_val = std::distance(ModuleDisplaySettings::ThrottleAmounts.begin(), found);
			}
			lv_slider_set_value(graphics_update_rate_slider, slider_val, LV_ANIM_OFF);
		}
	}

	void show() {
		if (!visible) {
			DropInFromLeft_Animation(ui_PVSettingsMenu, 0);
			auto indev = lv_indev_get_next(nullptr);
			if (!indev)
				return;
			lv_indev_set_group(indev, settings_menu_group);
			lv_group_focus_obj(ui_PVSettingsCloseButton);
			lv_obj_clear_state(ui_PVSettingsCloseButton, LV_STATE_PRESSED);
			lv_obj_scroll_to_y(ui_PVSettingsMenu, 0, LV_ANIM_OFF);

			visible = true;
			changed_while_visible = false;
		}
	}

	void hide() {
		if (visible) {
			DropOutToRight_Animation(ui_PVSettingsMenu, 0);
			auto indev = lv_indev_get_next(nullptr);
			if (!indev)
				return;
			if (base_group)
				lv_indev_set_group(indev, base_group);
			lv_obj_clear_state(ui_SettingsButton, LV_STATE_PRESSED);

			visible = false;

			if (changed_while_visible)
				gui_state.do_write_settings = true;
		}
	}

	bool is_visible() {
		return visible;
	}

private:
	void fix_forbidden_states() {
		using enum MapRingStyle::Mode;

		// Control Maps and PanelJack Maps share the "Show if Playing" switch
		// If param_style is the IfPlaying version, then set paneljack_style to the IfPlaying version
		if (settings.param_style.mode == ShowAllIfPlaying || settings.param_style.mode == CurModuleIfPlaying) {
			if (settings.paneljack_style.mode == ShowAll)
				settings.paneljack_style.mode = ShowAllIfPlaying;

			if (settings.paneljack_style.mode == CurModule)
				settings.paneljack_style.mode = CurModuleIfPlaying;

		} else if (settings.param_style.mode == ShowAll || settings.param_style.mode == CurModule) {
			if (settings.paneljack_style.mode == ShowAllIfPlaying)
				settings.paneljack_style.mode = ShowAll;

			if (settings.paneljack_style.mode == CurModuleIfPlaying)
				settings.paneljack_style.mode = CurModule;
		}

		// Control Maps and PanelJack Maps share the "Show All Modules" switch
		// set paneljack_style to the same ShowAll vs. CurModule as param_style
		if (settings.param_style.mode == ShowAllIfPlaying || settings.param_style.mode == ShowAll) {
			if (settings.paneljack_style.mode == CurModuleIfPlaying)
				settings.paneljack_style.mode = ShowAllIfPlaying;

			if (settings.paneljack_style.mode == CurModule)
				settings.paneljack_style.mode = ShowAll;

		} else if (settings.param_style.mode == CurModuleIfPlaying || settings.param_style.mode == CurModule) {
			if (settings.paneljack_style.mode == ShowAllIfPlaying)
				settings.paneljack_style.mode = CurModuleIfPlaying;

			if (settings.paneljack_style.mode == ShowAll)
				settings.paneljack_style.mode = CurModule;
		}

		// Cables are either hidden or shown, no other states allowed
		if (settings.cable_style.mode != HideAlways)
			settings.cable_style.mode = ShowAll;
	}

	void update_interactive_states() {
		auto show_control_maps = lv_obj_has_state(ui_PVShowControlMapsCheck, LV_STATE_CHECKED);
		auto show_jack_maps = lv_obj_has_state(ui_PVShowJackMapsCheck, LV_STATE_CHECKED);
		auto show_cables = lv_obj_has_state(ui_PVShowAllCablesCheck, LV_STATE_CHECKED);
		auto show_graphics = lv_obj_has_state(graphics_show_check, LV_STATE_CHECKED);

		lv_enable(ui_PVControlMapTranspSlider, show_control_maps);
		lv_enable(ui_PVJackMapTranspSlider, show_jack_maps);
		lv_enable(ui_PVCablesTranspSlider, show_cables);
		lv_enable(graphics_update_rate_slider, show_graphics);

		if (!show_control_maps && !show_jack_maps) {
			lv_disable(ui_PVShowMapsAlwaysCheck);
			lv_disable(ui_PVShowMapsAllModulesCheck);
			lv_label_set_text(ui_PVMapsWillBeHiddenNote, "");
			lv_label_set_text(ui_PVMapsWillShowSelectedModuleNote, "");
		} else {
			lv_enable(ui_PVShowMapsAlwaysCheck);
			lv_enable(ui_PVShowMapsAllModulesCheck);

			if (lv_obj_has_state(ui_PVShowMapsAlwaysCheck, LV_STATE_CHECKED))
				lv_label_set_text(ui_PVMapsWillBeHiddenNote, "Maps will show even if not playing");
			else
				lv_label_set_text(ui_PVMapsWillBeHiddenNote, "Maps will only show when playing");

			if (lv_obj_has_state(ui_PVShowMapsAllModulesCheck, LV_STATE_CHECKED))
				lv_label_set_text(ui_PVMapsWillShowSelectedModuleNote, "Maps will show on all modules");
			else
				lv_label_set_text(ui_PVMapsWillShowSelectedModuleNote, "Will only show on selected module");
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

		auto page = static_cast<PatchViewSettingsMenu *>(event->user_data);

		page->update_interactive_states();

		auto show_always = lv_obj_has_state(ui_PVShowMapsAlwaysCheck, LV_STATE_CHECKED);
		auto show_all_modules = lv_obj_has_state(ui_PVShowMapsAllModulesCheck, LV_STATE_CHECKED);
		auto show_control_maps = lv_obj_has_state(ui_PVShowControlMapsCheck, LV_STATE_CHECKED);
		auto show_jack_maps = lv_obj_has_state(ui_PVShowJackMapsCheck, LV_STATE_CHECKED);
		auto flash_active = lv_obj_has_state(ui_PVFlashMapCheck, LV_STATE_CHECKED);

		using enum MapRingStyle::Mode;

		page->settings.param_style.mode = show_control_maps && show_always && show_all_modules	 ? ShowAll :
										  show_control_maps && !show_always && show_all_modules	 ? ShowAllIfPlaying :
										  show_control_maps && show_always && !show_all_modules	 ? CurModule :
										  show_control_maps && !show_always && !show_all_modules ? CurModuleIfPlaying :
																								   HideAlways;

		page->settings.paneljack_style.mode = show_jack_maps && show_always && show_all_modules	  ? ShowAll :
											  show_jack_maps && !show_always && show_all_modules  ? ShowAllIfPlaying :
											  show_jack_maps && show_always && !show_all_modules  ? CurModule :
											  show_jack_maps && !show_always && !show_all_modules ? CurModuleIfPlaying :
																									HideAlways;
		auto opacity = lv_slider_get_value(ui_PVControlMapTranspSlider); //0..100
		opacity = (float)opacity * 2.5f;
		page->settings.param_style.opa = opacity;

		opacity = lv_slider_get_value(ui_PVJackMapTranspSlider); //0..100
		opacity = (float)opacity * 2.5f;
		page->settings.paneljack_style.opa = opacity;

		page->settings.map_ring_flash_active = flash_active;

		page->settings.changed = true;
		page->changed_while_visible = true;
	}

	static void cable_settings_value_change_cb(lv_event_t *event) {
		if (!event || !event->user_data)
			return;

		using enum MapRingStyle::Mode;

		auto show_all = lv_obj_has_state(ui_PVShowAllCablesCheck, LV_STATE_CHECKED);
		auto page = static_cast<PatchViewSettingsMenu *>(event->user_data);

		page->update_interactive_states();

		page->settings.cable_style.mode = show_all ? ShowAll : HideAlways;

		auto opacity = lv_slider_get_value(ui_PVCablesTranspSlider); //0..100
		opacity = (float)opacity * 2.5f;
		page->settings.cable_style.opa = opacity;

		page->settings.changed = true;
		page->changed_while_visible = true;
	}

	static void graphics_settings_value_change_cb(lv_event_t *event) {
		if (!event || !event->user_data)
			return;

		auto page = static_cast<PatchViewSettingsMenu *>(event->user_data);

		auto show_graphics = lv_obj_has_state(page->graphics_show_check, LV_STATE_CHECKED);

		page->settings.show_graphic_screens = show_graphics;

		auto updaterate = lv_slider_get_value(page->graphics_update_rate_slider);
		updaterate = std::clamp<int32_t>(updaterate, 0, ModuleDisplaySettings::ThrottleAmounts.size() - 1);
		page->settings.graphic_screen_throttle = ModuleDisplaySettings::ThrottleAmounts[updaterate];

		page->update_interactive_states();

		page->settings.changed = true;
		page->changed_while_visible = true;
	}

	static void scroll_menu_down_cb(lv_event_t *event) {
		if (!event || !event->user_data)
			return;

		auto page = static_cast<PatchViewSettingsMenu *>(event->user_data);

		lv_obj_scroll_to_view_recursive(page->graphics_update_rate_slider, LV_ANIM_ON);
	}

	static void show_titlebar_cb(lv_event_t *event) {
		if (!event || !event->user_data)
			return;

		auto page = static_cast<PatchViewSettingsMenu *>(event->user_data);

		page->settings.show_samplerate = lv_obj_has_state(page->show_samplerate_check, LV_STATE_CHECKED);
		page->settings.float_loadmeter = lv_obj_has_state(page->float_audioload_check, LV_STATE_CHECKED);
		page->settings.show_knobset_name = lv_obj_has_state(page->show_knobset_name_check, LV_STATE_CHECKED);

		page->settings.changed = true;
		page->changed_while_visible = true;
	}

	lv_group_t *base_group = nullptr;
	lv_group_t *settings_menu_group = nullptr;

	lv_obj_t *graphics_show_check;
	lv_obj_t *graphics_update_rate_label;
	lv_obj_t *graphics_update_rate_slider;

	lv_obj_t *show_samplerate_check;
	lv_obj_t *float_audioload_check;
	lv_obj_t *show_knobset_name_check;

	bool visible = false;
	bool changed_while_visible = false;
	ModuleDisplaySettings &settings;
	GuiState &gui_state;
};

} // namespace MetaModule
