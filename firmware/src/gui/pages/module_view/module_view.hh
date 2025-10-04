#pragma once
#include "gui/dyn_display.hh"
#include "gui/elements/map_ring_animate.hh"
#include "gui/helpers/roller_hover_text.hh"
#include "gui/module_menu/plugin_module_menu.hh"
#include "gui/pages/base.hh"
#include "gui/pages/cable_drawer.hh"
#include "gui/pages/make_cable.hh"
#include "gui/pages/module_view/action_menu.hh"
#include "gui/pages/module_view/mapping_pane.hh"
#include "gui/pages/module_view/settings_menu.hh"
#include "gui/pages/page_list.hh"

namespace MetaModule
{

struct ModuleViewPage : PageBase {

	ModuleViewPage(PatchContext context)
		: PageBase{context, PageId::ModuleView}
		, cable_drawer{ui_ModuleImage, drawn_elements}
		, map_ring_display{settings.module_view}
		, page_settings{settings.module_view}
		, settings_menu{settings.module_view, gui_state}
		, patch{patches.get_view_patch()}
		, mapping_pane{patches,
					   module_mods,
					   params,
					   metaparams,
					   args,
					   page_list,
					   notify_queue,
					   gui_state,
					   patch_playloader}
		, action_menu{module_mods, patches, page_list, patch_playloader, notify_queue, context.ramdisk, gui_state}
		, roller_hover(ui_ElementRollerPanel, ui_ElementRoller)
		, module_context_menu{patch_playloader}
		, dyn_draw{patch_playloader} {

		init_bg(ui_MappingMenu);

		lv_draw_img_dsc_init(&img_dsc);

		lv_obj_remove_style(ui_ElementRoller, nullptr, LV_STATE_EDITED);
		lv_obj_remove_style(ui_ElementRoller, nullptr, LV_STATE_FOCUS_KEY);

		lv_obj_add_flag(ui_MappingParameters, LV_OBJ_FLAG_HIDDEN);

		element_highlights.clear();

		auto roller_label = lv_obj_get_child(ui_ElementRoller, 0);
		lv_label_set_recolor(roller_label, true);

		lv_hide(ui_ModuleViewCableCancelBut);

		lv_group_remove_all_objs(group);
		lv_group_add_obj(group, ui_ModuleViewHideBut);
		lv_group_add_obj(group, ui_ModuleViewActionBut);
		lv_group_add_obj(group, ui_ModuleViewSettingsBut);
		lv_group_add_obj(group, ui_ModuleViewCableCancelBut);
		lv_group_add_obj(group, ui_ElementRoller);
		lv_group_focus_obj(ui_ElementRoller);

		lv_group_add_obj(group, ui_ModuleViewExtraMenuRoller);
		lv_hide(ui_ModuleViewExtraMenuRoller);

		lv_group_set_wrap(group, false);

		lv_obj_add_event_cb(ui_ElementRoller, roller_scrolled_cb, LV_EVENT_KEY, this);
		lv_obj_add_event_cb(ui_ElementRoller, roller_click_cb, LV_EVENT_SHORT_CLICKED, this);
		lv_obj_add_event_cb(ui_ElementRoller, roller_focus_cb, LV_EVENT_FOCUSED, this);
		lv_obj_add_event_cb(ui_ElementRoller, roller_pressed_cb, LV_EVENT_PRESSED, this);
		lv_obj_add_event_cb(ui_ModuleViewCableCancelBut, cancel_cable_cb, LV_EVENT_CLICKED, this);
		lv_obj_add_event_cb(ui_ModuleViewHideBut, fullscreen_but_cb, LV_EVENT_CLICKED, this);

		lv_obj_add_event_cb(ui_ModuleViewHideBut, jump_to_roller_cb, LV_EVENT_FOCUSED, this);
		lv_obj_add_event_cb(ui_ModuleViewActionBut, jump_to_roller_cb, LV_EVENT_FOCUSED, this);
		lv_obj_add_event_cb(ui_ModuleViewSettingsBut, jump_to_roller_cb, LV_EVENT_FOCUSED, this);
	}

	void prepare_focus() override {
		lv_disable_long_press();

		roller_hover.hide();

		patch = patches.get_view_patch();

		is_patch_playloaded = patch_is_playing(args.patch_loc_hash);

		this_module_id = args.module_id.value_or(this_module_id);

		if (args.patch_loc_hash) {
			file_change_poll.force_next_poll();
			poll_patch_file_changed();
		}

		if (!read_slug()) {
			page_list.request_new_page(PageId::PatchView, args);
			pr_err("Module id out of range, or patch is invalid\n");
			return;
		}

		moduleinfo = ModuleFactory::getModuleInfo(slug);
		if (moduleinfo.width_hp == 0) {
			page_list.request_new_page(PageId::PatchView, args);
			pr_err("Module hp is 0, cannot draw module\n");
			return;
		}

		auto module_display_name = ModuleFactory::getModuleDisplayName(slug);
		lv_label_set_text(ui_ElementRollerModuleName, module_display_name.data());

		has_context_menu = module_context_menu.create_options_menu(this_module_id);

		redraw_module();

		lv_hide(ui_ModuleViewActionMenu);
		lv_hide(ui_AutoMapSelectPanel);
		lv_hide(ui_MIDIMapPanel);

		if (gui_state.new_cable) {
			lv_hide(ui_ModuleViewHideBut);
			lv_hide(ui_ModuleViewActionBut);
			lv_hide(ui_ModuleViewSettingsBut);
			lv_show(ui_ModuleViewCableCancelBut);
			lv_show(ui_ModuleViewCableCreateLabel);
			lv_label_set_text(ui_ModuleViewCableCreateLabel, "Creating a cable");
			lv_obj_set_height(ui_ElementRoller, 132);
			lv_obj_set_style_pad_bottom(ui_ElementRollerButtonCont, 8, LV_PART_MAIN);
			lv_obj_set_style_pad_row(ui_ElementRollerButtonCont, 8, LV_PART_MAIN);
			lv_obj_set_flex_align(
				ui_ElementRollerButtonCont, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_START);
		} else {
			lv_show(ui_ModuleViewHideBut);
			lv_show(ui_ModuleViewActionBut);
			lv_show(ui_ModuleViewSettingsBut);
			lv_hide(ui_ModuleViewCableCancelBut);
			lv_hide(ui_ModuleViewCableCreateLabel);
			lv_obj_set_height(ui_ElementRoller, 186);
			lv_obj_set_style_pad_bottom(ui_ElementRollerButtonCont, 2, LV_PART_MAIN);
			lv_obj_set_style_pad_row(ui_ElementRollerButtonCont, -4, LV_PART_MAIN);
			lv_obj_set_flex_align(
				ui_ElementRollerButtonCont, LV_FLEX_ALIGN_END, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_START);
			settings_menu.prepare_focus(group);
			action_menu.prepare_focus(group, this_module_id);
		}

		quick_control_mode = false;
		suppress_next_click = false;
	}

	void update() override {
		// Back button
		if (gui_state.back_button.is_just_released()) {

			if (action_menu.is_visible()) {
				action_menu.back();

			} else if (settings_menu.is_visible()) {
				settings_menu.hide();

			} else if (metaparams.rotary_button.is_pressed() && mode == ViewMode::List) {
				handle_encoder_back_removal();

			} else if (mode == ViewMode::Mapping) {
				mapping_pane.back_event();

			} else if (mode == ViewMode::ModuleContextMenu) {
				module_context_menu.back_event();

			} else if (mapping_pane.control_popup_visible()) {
				mapping_pane.hide_control_popup();

			} else if (full_screen_mode) {
				full_screen_mode = false;
				resize_module_image(190);

			} else if (mode == ViewMode::List) {
				args.module_id = this_module_id;
				load_prev_page();
			}
		}

		// File Browser
		if (gui_state.file_browser_visible.just_went_low()) {
			// File Browser detected as just closed
			if (mode == ViewMode::ModuleContextMenu) {
				show_roller();
			}
		}

		// Mapping pane
		if (mode == ViewMode::Mapping) {
			mapping_pane.update();
			if (mapping_pane.wants_to_close()) {
				if (mapping_pane.modified_elements())
					populate_roller();
				else
					show_roller();
			}

			// Right-click menu
		} else if (mode == ViewMode::ModuleContextMenu) {
			module_context_menu.update();
			if (module_context_menu.wants_to_close()) {
				show_roller();
			}
		}

		// Action menu
		if (action_menu.is_visible()) {
			action_menu.update();
		}

		// Knobset changed
		if (is_patch_playloaded && active_knobset != page_list.get_active_knobset()) {
			args.view_knobset_id = page_list.get_active_knobset();
			active_knobset = page_list.get_active_knobset();
			redraw_module();

			if (mode == ViewMode::Mapping)
				mapping_pane.refresh();
		}

		// Settings changed
		if (page_settings.changed) {
			page_settings.changed = false;
			update_map_ring_style();
			update_cable_style();
			update_graphic_throttle_setting();
			populate_roller();
		}

		// Patch file changed via wifi/disk
		poll_patch_file_changed();

		if (gui_state.force_redraw_patch || gui_state.view_patch_file_changed) {

			abort_cable(gui_state, notify_queue);

			// Check if module slug changed: go to patch view if it did
			// Otherwise re-draw the patch
			auto prev_slug = slug;
			patch = patches.get_view_patch();
			auto ok = read_slug();
			if (!ok || prev_slug != slug) {
				page_list.request_new_page(PageId::PatchView, args);
			} else {
				if (gui_state.force_redraw_patch)
					blur();
				prepare_focus();
			}

			gui_state.force_redraw_patch = false;
			gui_state.view_patch_file_changed = false;
		}

		// Handle patch modification requests
		if (handle_patch_mods()) {
			redraw_module();
			mapping_pane.refresh();
		}

		// Draw the on-screen elements (knobs, lights, etc)
		if (is_patch_playloaded) {
			redraw_elements();
		}

		// Hover text
		roller_hover.update();

		// Hide the hover text if we are on one of the action buttons
		if (lv_group_get_focused(group) == ui_ModuleViewActionBut ||
			lv_group_get_focused(group) == ui_ModuleViewSettingsBut ||
			lv_group_get_focused(group) == ui_ModuleViewHideBut)
		{
			roller_hover.hide();
		}

		if (mode == ViewMode::List && !action_menu.is_visible() && !settings_menu.is_visible()) {
			handle_quick_assign();
		}
	}

	bool handle_patch_mods() {
		bool refresh = false;

		while (auto patch_mod = module_mods.get()) {
			patches.mark_view_patch_modified();

			// Apply to this thread's copy of patch
			std::visit(overloaded{
						   [&, this](AddMapping &mod) { refresh = patch->add_update_mapped_knob(mod.set_id, mod.map); },
						   [&, this](AddMidiMap &mod) { refresh = patch->add_update_midi_map(mod.map); },
						   [&, this](AddInternalCable &mod) {
							   refresh = true;
							   patch->add_internal_cable(mod.in, mod.out);
						   },
						   [&, this](AddJackMapping &mod) {
							   mod.type == ElementType::Output ?
								   patch->add_mapped_outjack(mod.panel_jack_id, mod.jack) :
								   patch->add_mapped_injack(mod.panel_jack_id, mod.jack);
							   refresh = true;
						   },
						   [&, this](DisconnectJack &mod) {
							   mod.type == ElementType::Output ? patch->disconnect_outjack(mod.jack) :
																 patch->disconnect_injack(mod.jack);
							   refresh = true;
						   },
						   [&, this](RemoveJackMappings &mod) {
							   mod.type == ElementType::Output ? patch->remove_outjack_mappings(mod.jack) :
																 patch->remove_injack_mappings(mod.jack);
							   refresh = true;
						   },
						   [&, this](RemoveMapping &mod) {
							   patch->remove_mapping(mod.set_id, mod.map);
							   refresh = true;
						   },
						   [&](auto &m) { refresh = false; },
					   },
					   patch_mod.value());

			// Forward the mod to the audio/patch_player queue
			if (is_patch_playloaded)
				patch_mod_queue.put(patch_mod.value());
		}

		return refresh;
	}

	void blur() final {
		module_context_menu.blur();
		dyn_draw.blur();
		params.text_displays.stop_watching_all();
		settings_menu.hide();
		action_menu.hide();
		lv_enable_long_press();
	}

private:
	void reset_module_page() {
		for (auto &b : element_highlights)
			lv_obj_del(b);
		element_highlights.clear();

		dyn_draw.blur();

		// This should delete all canvas children
		// which includes drawn_elements and dyn canvases
		if (canvas)
			lv_obj_del(canvas);

		drawn_elements.clear();

		opts.clear();
		roller_drawn_el_idx.clear();
		cur_selected = 1;
	}

	bool read_slug() {
		if (!args.module_id)
			return false;
		auto module_id = args.module_id.value();

		if (module_id >= patch->module_slugs.size())
			return false;

		slug = patch->module_slugs[module_id];
		return true;
	}

	void show_context_menu() {
		if (!full_screen_mode) {
			mode = ViewMode::ModuleContextMenu;
			lv_hide(ui_ElementRoller);
			roller_hover.hide();
			module_context_menu.show();
		}
	}

	static void cancel_cable_cb(lv_event_t *event) {
		if (!event || !event->user_data)
			return;
		auto page = static_cast<ModuleViewPage *>(event->user_data);

		abort_cable(page->gui_state, page->notify_queue);
		page->page_list.request_new_page(PageId::PatchView, page->args);
	}

	static void fullscreen_but_cb(lv_event_t *event) {
		if (!event || !event->user_data)
			return;
		auto page = static_cast<ModuleViewPage *>(event->user_data);

		page->resize_module_image(320);
		lv_obj_scroll_to_x(ui_ModuleImage, 0, LV_ANIM_ON);

		page->cur_selected = 1;
		lv_group_focus_obj(ui_ElementRoller);
		lv_roller_set_selected(ui_ElementRoller, page->cur_selected, LV_ANIM_OFF);
		lv_event_send(ui_ElementRoller, LV_EVENT_SCROLL, nullptr);

		page->full_screen_mode = true;
	}

	// Defined in module_view/element_roller.cc:
	void show_roller();
	void populate_roller();
	void populate_element_objects();
	void add_element_highlight(lv_obj_t *obj);
	void unhighlight_component(uint32_t prev_sel);
	void highlight_component(size_t idx);
	void focus_button_bar();
	void click_cable_destination(unsigned drawn_idx);
	void click_altparam_action(DrawnElement const &drawn_element);
	void manual_control_popup(DrawnElement const &drawn_element);
	void send_param_value(float value, GuiElement const &gui_element);
	void click_graphic_display(DrawnElement const &drawn_element, DynamicGraphicDisplay const *el);
	void click_normal_element(DrawnElement const &drawn_element);
	static void roller_scrolled_cb(lv_event_t *event);
	static void roller_click_cb(lv_event_t *event);
	static void roller_focus_cb(lv_event_t *event);
	static void roller_pressed_cb(lv_event_t *event);
	static void jump_to_roller_cb(lv_event_t *event);
	std::optional<unsigned> get_drawn_idx(unsigned roller_idx);

	// Defined in module_view/draw_module.cc
	void prepare_dynamic_elements();
	unsigned resize_module_image(unsigned max);
	void redraw_module();
	void watch_element(DrawnElement const &drawn_element);
	void redraw_elements();
	void update_map_ring_style();
	void update_cable_style(bool force = false);
	void update_graphic_throttle_setting();

	// Defined in module_view/quick_assign.cc
	void handle_quick_assign();
	void handle_encoder_back_removal();
	const DrawnElement *get_highlighted_element();
	void remove_nonmidi_mappings(uint16_t module_id, uint16_t param_id);
	void remove_mappings(uint16_t module_id, uint16_t param_id, unsigned target_knobset);
	void perform_knob_assign(uint16_t knob_id, const DrawnElement *element);
	void perform_midi_assign(uint16_t midi_id, const DrawnElement *element);
	void perform_jack_assign(const DrawnElement *element, ElementType jack_type);
	bool cycle_port_selection(const DrawnElement *element, int motion, ElementType jack_type);

	CableDrawer<240> cable_drawer;

	ModuleInfoView moduleinfo;
	PatchModQueue module_mods;

	MapRingDisplay map_ring_display;

	ModuleDisplaySettings &page_settings;
	ModuleViewSettingsMenu settings_menu;

	std::string opts;
	uint16_t this_module_id = 0;
	uint32_t cur_selected = 0;
	std::string_view slug = "";
	bool is_patch_playloaded = false;
	PatchData *patch;

	unsigned active_knobset = 0;

	std::vector<lv_obj_t *> element_highlights;
	std::vector<DrawnElement> drawn_elements;
	std::vector<int> roller_drawn_el_idx;

	lv_obj_t *canvas = nullptr;
	ModuleViewMappingPane mapping_pane;

	ModuleViewActionMenu action_menu;

	lv_color_t buffer[LV_CANVAS_BUF_SIZE_TRUE_COLOR_ALPHA(240, 240)]{};
	lv_draw_img_dsc_t img_dsc{};

	enum class ViewMode { List, Mapping, ModuleContextMenu } mode{ViewMode::List};

	RollerHoverText roller_hover;

	PluginModuleMenu module_context_menu;
	bool has_context_menu = false;

	DynamicDisplay dyn_draw;
	bool dynamic_elements_prepared = false;
	unsigned dyn_draw_throttle_ctr = 0;
	unsigned dyn_draw_throttle = 16;

	bool full_screen_mode = false;

	std::optional<GuiElement> pending_action_param_clear{};

	enum { RollerHeaderTag = -1, ContextMenuTag = -2 };

	uint16_t selected_input_port = 0;
	uint16_t selected_output_port = 0;

	bool suppress_next_click = false;
	bool quick_control_mode = false;
	Toggler quickmap_rotary_button;
};

} // namespace MetaModule
