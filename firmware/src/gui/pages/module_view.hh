#pragma once
#include "gui/dyn_display.hh"
#include "gui/elements/element_name.hh"
#include "gui/elements/map_ring_animate.hh"
#include "gui/elements/module_drawer.hh"
#include "gui/elements/redraw.hh"
#include "gui/elements/redraw_display.hh"
#include "gui/elements/redraw_light.hh"
#include "gui/helpers/roller_hover_text.hh"
#include "gui/module_menu/plugin_module_menu.hh"
#include "gui/pages/base.hh"
#include "gui/pages/cable_drawer.hh"
#include "gui/pages/module_view_action_menu.hh"
#include "gui/pages/module_view_mapping_pane.hh"
#include "gui/pages/module_view_roller_helpers.hh"
#include "gui/pages/module_view_settings_menu.hh"
#include "gui/pages/page_list.hh"
#include "gui/styles.hh"

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
		, mapping_pane{patches, module_mods, params, args, page_list, notify_queue, gui_state, patch_playloader}
		, action_menu{module_mods, patches, page_list, patch_playloader, notify_queue, context.ramdisk}
		, roller_hover(ui_ElementRollerPanel, ui_ElementRoller)
		, module_context_menu{patch_playloader}
		, dyn_draw{patch_playloader} {

		init_bg(ui_MappingMenu);

		lv_draw_img_dsc_init(&img_dsc);

		lv_obj_remove_style(ui_ElementRoller, nullptr, LV_STATE_EDITED);
		lv_obj_remove_style(ui_ElementRoller, nullptr, LV_STATE_FOCUS_KEY);

		lv_obj_add_flag(ui_MappingParameters, LV_OBJ_FLAG_HIDDEN);

		button.clear();

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
		lv_obj_add_event_cb(ui_ElementRoller, roller_click_cb, LV_EVENT_CLICKED, this);
		lv_obj_add_event_cb(ui_ElementRoller, roller_focus_cb, LV_EVENT_FOCUSED, this);
		lv_obj_add_event_cb(ui_ModuleViewCableCancelBut, cancel_cable_cb, LV_EVENT_CLICKED, this);
		lv_obj_add_event_cb(ui_ModuleViewHideBut, fullscreen_but_cb, LV_EVENT_CLICKED, this);

		lv_obj_add_event_cb(ui_ModuleViewHideBut, jump_to_roller_cb, LV_EVENT_FOCUSED, this);
		lv_obj_add_event_cb(ui_ModuleViewActionBut, jump_to_roller_cb, LV_EVENT_FOCUSED, this);
		lv_obj_add_event_cb(ui_ModuleViewSettingsBut, jump_to_roller_cb, LV_EVENT_FOCUSED, this);
	}

	void prepare_focus() override {
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
	}

	unsigned resize_module_image(unsigned max) {
		lv_obj_refr_size(canvas);
		auto width_px = lv_obj_get_width(canvas);
		//module img + padding is no more than 190px wide
		auto display_widthpx = std::min<lv_coord_t>(width_px + 4, max);
		lv_obj_set_width(ui_ModuleImage, display_widthpx);
		lv_obj_refr_size(ui_ModuleImage);
		if (lv_obj_get_width(ui_ModuleImage) > width_px) {
			lv_obj_clear_flag(ui_ModuleImage, LV_OBJ_FLAG_SCROLLABLE);
		} else {
			lv_obj_add_flag(ui_ModuleImage, LV_OBJ_FLAG_SCROLLABLE);
		}

		lv_obj_clear_flag(canvas, LV_OBJ_FLAG_SCROLLABLE);

		auto roller_width = std::min<lv_coord_t>(320 - display_widthpx, 220); //roller is no more than 220px wide
		lv_obj_set_size(ui_ElementRollerPanel, roller_width, 240);
		if (max == 320) {
			lv_obj_set_x(ui_ElementRollerPanel, 320);
		} else {
			lv_obj_set_x(ui_ElementRollerPanel, 0);
		}

		return display_widthpx;
	}

	void redraw_module() {
		reset_module_page();

		size_t num_elements = moduleinfo.elements.size();
		opts.reserve(num_elements * 32); // estimate avg. 32 chars per roller item
		button.reserve(num_elements);
		drawn_elements.reserve(num_elements);

		auto module_drawer = ModuleDrawer{.container = ui_ModuleImage, .height = 240};

		auto [faceplate, width] = module_drawer.read_faceplate(slug);
		canvas = module_drawer.draw_faceplate(faceplate, width, buffer);

		active_knobset = page_list.get_active_knobset();

		module_drawer.draw_mapped_elements(
			*patch, this_module_id, active_knobset, canvas, drawn_elements, is_patch_playloaded);

		lv_obj_update_layout(canvas);

		// Populate Roller and highlighter buttons
		unsigned roller_idx = 0;
		DrawnElement const *cur_el = nullptr;
		ElementCount::Counts last_type{};

		for (auto [drawn_el_idx, drawn_element] : enumerate(drawn_elements)) {
			auto &gui_el = drawn_element.gui_element;

			watch_element(drawn_element);

			add_button(gui_el.obj);

			auto base = base_element(drawn_element.element);

			if (base.short_name.size() == 0) {
				pr_info("Element roller: Skipping element with no name\n");
				continue;
			}

			if (ModView::is_light_only(drawn_element))
				continue;

			if (ModView::should_skip_for_cable_mode(gui_state.new_cable, gui_el, gui_state, patch, this_module_id))
				continue;

			if (ModView::append_header(opts, last_type, gui_el.count)) {
				roller_idx++;
				roller_drawn_el_idx.push_back(-1);
			}
			last_type = gui_el.count;

			opts.append(" ");
			// Display up to the first newline (if any)
			opts.append(base.short_name.substr(0, base.short_name.find_first_of("\0\n")));

			if (gui_el.mapped_panel_id) {
				append_panel_name(opts, drawn_element.element, gui_el.mapped_panel_id.value());
			}

			append_connected_jack_name(opts, gui_el.idx, gui_el.module_idx, *patch);

			opts += "\n";
			roller_drawn_el_idx.push_back(drawn_el_idx);

			// Pre-select an element
			if (args.element_indices.has_value()) {
				if (ElementCount::matched(*args.element_indices, gui_el.idx)) {
					cur_selected = roller_idx;
					cur_el = &drawn_element;
				}
			}

			roller_idx++;
		}

		if (is_patch_playloaded) {
			if (has_context_menu) {
				opts += Gui::orange_text("Options:") + "\n";
				opts += " >>>\n";
				roller_drawn_el_idx.push_back(-1);
				roller_drawn_el_idx.push_back(ContextMenuTag);
				roller_idx += 2;
			}
		}

		if (roller_idx <= 1) {
			if (gui_state.new_cable) {
				opts.append("No available jacks to patch\n");
			}
		}

		// remove final \n
		if (opts.length() > 0)
			opts.pop_back();

		//Size Module Image and Roller
		lv_obj_set_pos(ui_ElementRollerPanel, 0, 0);

		resize_module_image(190);
		full_screen_mode = false;

		lv_show(ui_ElementRollerPanel);

		// Add text list to roller options
		lv_roller_set_options(ui_ElementRoller, opts.c_str(), LV_ROLLER_MODE_NORMAL);

		lv_roller_set_selected(ui_ElementRoller, cur_selected, LV_ANIM_OFF);

		if (cur_selected > 0 && cur_selected < button.size()) {
			if (auto idx = roller_drawn_el_idx[cur_selected]; (size_t)idx < button.size()) {
				if (lv_obj_get_height(button[idx]) > 100 || lv_obj_get_width(button[idx]) > 100) {
					lv_obj_add_style(button[idx], &Gui::panel_large_highlight_style, LV_PART_MAIN);
				} else {
					lv_obj_add_style(button[idx], &Gui::panel_highlight_style, LV_PART_MAIN);
				}
			}
		} else {
			pr_err("Current selected is not in range (%d/%zu)\n", cur_selected, button.size());
		}

		update_map_ring_style();

		cable_drawer.set_height(240);
		update_cable_style(true);

		lv_obj_refr_size(ui_ElementRollerPanel);
		auto roller_width = lv_obj_get_width(ui_ElementRollerPanel);
		mapping_pane.prepare_focus(group, roller_width, is_patch_playloaded);

		if (cur_el && args.detail_mode == true) {
			mode = ViewMode::Mapping;
			mapping_pane.hide();
			mapping_pane.show(*cur_el);
		} else {
			show_roller();
		}

		dynamic_elements_prepared = false;
		update_graphic_throttle_setting();
	}

	void prepare_dynamic_elements() {
		if (!dynamic_elements_prepared) {
			dyn_draw.prepare_module(drawn_elements, this_module_id, canvas);
			dynamic_elements_prepared = true;
		}
	}

	void watch_element(DrawnElement const &drawn_element) {
		if (std::get_if<DynamicTextDisplay>(&drawn_element.element)) {
			params.text_displays.start_watching_display(this_module_id, drawn_element.gui_element.idx.light_idx);
		}
	}

	bool is_creating_map() const {
		return mapping_pane.is_creating_map();
	}

	void update() override {
		if (gui_state.back_button.is_just_released()) {

			if (action_menu.is_visible()) {
				action_menu.back();

			} else if (settings_menu.is_visible()) {
				settings_menu.hide();

			} else if (mode == ViewMode::Mapping) {
				mapping_pane.back_event();

			} else if (mode == ViewMode::ModuleContextMenu) {
				module_context_menu.back_event();

			} else if (full_screen_mode) {
				full_screen_mode = false;
				resize_module_image(190);

			} else if (mode == ViewMode::List) {
				args.module_id = this_module_id;
				load_prev_page();
			}
		}

		if (gui_state.file_browser_visible.just_went_low()) {
			// File Browser detected as just closed
			if (mode == ViewMode::ModuleContextMenu) {
				show_roller();
			}
		}

		if (mode == ViewMode::Mapping) {
			mapping_pane.update();
			if (mapping_pane.wants_to_close()) {
				show_roller();
			}

		} else if (mode == ViewMode::ModuleContextMenu) {
			module_context_menu.update();
			if (module_context_menu.wants_to_close()) {
				show_roller();
			}
		}

		if (action_menu.is_visible()) {
			action_menu.update();
		}

		if (is_patch_playloaded && active_knobset != page_list.get_active_knobset()) {
			args.view_knobset_id = page_list.get_active_knobset();
			active_knobset = page_list.get_active_knobset();
			redraw_module();

			if (mode == ViewMode::Mapping)
				mapping_pane.refresh();
		}

		if (page_settings.changed) {
			page_settings.changed = false;
			update_map_ring_style();
			update_cable_style();
			update_graphic_throttle_setting();
		}

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

		// if (is_patch_playloaded) {
		if (is_patch_playloaded && !patch_playloader.is_audio_muted()) {
			redraw_elements();
		}

		if (handle_patch_mods()) {
			redraw_module();
			mapping_pane.refresh();
		}

		roller_hover.update();

		// Hide the hover text if we are on one of the action buttons
		if (lv_group_get_focused(group) == ui_ModuleViewActionBut ||
			lv_group_get_focused(group) == ui_ModuleViewSettingsBut ||
			lv_group_get_focused(group) == ui_ModuleViewHideBut)
		{
			roller_hover.hide();
		}
	}

	void redraw_elements() {
		for (auto &drawn_el : drawn_elements) {
			auto &gui_el = drawn_el.gui_element;

			auto value =
				patch_playloader.param_value(drawn_el.gui_element.module_idx, drawn_el.gui_element.idx.param_idx);
			auto was_redrawn = redraw_param(drawn_el, value);

			if (was_redrawn && page_settings.map_ring_flash_active) {
				map_ring_display.flash_once(gui_el.map_ring, true);
			}

			if (auto num_light_elements = gui_el.count.num_lights) {

				std::array<float, 3> storage{};
				auto light_vals = std::span{storage.data(), std::min(storage.size(), num_light_elements)};

				for (auto i = 0u; auto &val : light_vals) {
					val = patch_playloader.light_value(gui_el.module_idx, gui_el.idx.light_idx + i);
					i++;
				}

				update_light(drawn_el, light_vals);
			}

			redraw_text_display(drawn_el, this_module_id, params.text_displays.watch_displays);
		}

		if (dyn_draw_throttle && (++dyn_draw_throttle_ctr >= dyn_draw_throttle)) {
			dyn_draw_throttle_ctr = 0;
			prepare_dynamic_elements();
			dyn_draw.draw();
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
						   [&](auto &m) { refresh = false; },
					   },
					   patch_mod.value());

			// Forward the mod to the audio/patch_player queue
			if (is_patch_playloaded)
				patch_mod_queue.put(patch_mod.value());
		}

		return refresh;
	}

	// This gets called after map_ring_style changes
	void update_map_ring_style() {
		for (auto &drawn_el : drawn_elements) {
			map_ring_display.update(drawn_el, true, is_patch_playloaded);
		}
	}

	void update_cable_style(bool force = false) {
		static MapRingStyle last_cable_style;

		cable_drawer.set_opacity(page_settings.cable_style.opa);

		if (force || page_settings.cable_style.mode != last_cable_style.mode) {
			if (page_settings.cable_style.mode == MapRingStyle::Mode::ShowAll)
				cable_drawer.draw_single_module(*patch, this_module_id);
			else
				cable_drawer.clear();
		}
		last_cable_style = page_settings.cable_style;
	}

	void update_graphic_throttle_setting() {
		if (page_settings.show_graphic_screens) {
			dyn_draw_throttle = std::max(page_settings.graphic_screen_throttle, 1u);
		} else {
			dyn_draw_throttle = 0;
		}
	}

	void blur() final {
		module_context_menu.blur();
		dyn_draw.blur();
		params.text_displays.stop_watching_all();
		settings_menu.hide();
		action_menu.hide();
	}

private:
	void show_roller() {
		module_context_menu.hide();
		mode = ViewMode::List;
		mapping_pane.hide();
		lv_show(ui_ElementRoller);
		lv_show(ui_ElementRollerPanel);
		lv_group_focus_obj(ui_ElementRoller);
		lv_group_set_editing(group, true);
		lv_group_set_wrap(group, false);
		args.detail_mode = false;
	}

	void add_button(lv_obj_t *obj) {

		auto &b = button.emplace_back();
		b = lv_btn_create(ui_ModuleImage);
		lv_obj_add_style(b, &Gui::invisible_style, LV_PART_MAIN);

		if (obj) {
			float width = lv_obj_get_width(obj);
			float height = lv_obj_get_height(obj);
			float c_x = (float)lv_obj_get_x(obj) + width / 2.f;
			float c_y = (float)lv_obj_get_y(obj) + height / 2.f;

			auto x_padding = std::min(width * 0.75f, 12.f);
			auto y_padding = std::min(height * 0.75f, 12.f);
			auto x_size = x_padding + width;
			auto y_size = y_padding + height;
			lv_obj_add_flag(b, LV_OBJ_FLAG_SCROLL_ON_FOCUS);
			lv_obj_set_pos(b, std::round(c_x - x_size / 2.f), std::round(c_y - y_size / 2.f));
			lv_obj_set_size(b, std::round(x_size), std::round(y_size));
			lv_obj_refr_size(b);
			lv_obj_refr_pos(b);
		} else {
			lv_obj_set_pos(b, 0, 0);
			lv_obj_set_size(b, 0, 0);
		}
	}

	void reset_module_page() {
		for (auto &b : button)
			lv_obj_del(b);
		button.clear();

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

	static void roller_scrolled_cb(lv_event_t *event) {
		auto page = static_cast<ModuleViewPage *>(event->user_data);

		auto cur_sel = lv_roller_get_selected(ui_ElementRoller);
		if (cur_sel >= page->roller_drawn_el_idx.size()) {
			page->roller_hover.hide();
			return;
		}

		auto prev_sel = page->cur_selected;
		auto cur_idx = page->roller_drawn_el_idx[cur_sel];

		// Extra menu:
		if (cur_idx == ContextMenuTag) {
			page->unhighlight_component(prev_sel);
			page->cur_selected = cur_sel;
			page->roller_hover.hide();
			return;
		}

		// Skip over headers by scrolling over them in the same direction we just scrolled
		if (cur_idx == -1) {
			if (prev_sel < cur_sel) {
				if (cur_sel < lv_roller_get_option_cnt(ui_ElementRoller) - 1)
					cur_sel++;
				else
					// Don't scroll off the end of the roller
					cur_sel = prev_sel;

			} else {
				if (cur_sel)
					cur_sel--;

				else if (!page->full_screen_mode) {
					//Scrolling up from first header -> defocus roller and focus button bar
					page->focus_button_bar();
					page->roller_hover.hide();
					return;
				} else {
					// stay on the first item in the roller
					return;
				}
			}
			// cur_sel changed, so we need to update the roller position and our drawn_el idx
			lv_roller_set_selected(ui_ElementRoller, cur_sel, LV_ANIM_ON);
			cur_idx = page->roller_drawn_el_idx[cur_sel];
		}

		page->cur_selected = cur_sel;

		// Save current select in args so we can navigate back to this item
		page->args.element_indices = page->drawn_elements[cur_idx].gui_element.idx;

		page->unhighlight_component(prev_sel);
		page->highlight_component(cur_idx);

		page->roller_hover.hide();
	}

	void unhighlight_component(uint32_t prev_sel) {
		if (auto prev_idx = get_drawn_idx(prev_sel)) {
			if (lv_obj_get_height(button[*prev_idx]) > 100 || lv_obj_get_width(button[*prev_idx]) > 100) {
				lv_obj_remove_style(button[*prev_idx], &Gui::panel_large_highlight_style, LV_PART_MAIN);
			} else {
				lv_obj_remove_style(button[*prev_idx], &Gui::panel_highlight_style, LV_PART_MAIN);
			}
			lv_event_send(button[*prev_idx], LV_EVENT_REFRESH, nullptr);
		}
	}

	void highlight_component(size_t idx) {
		if (idx < button.size()) {

			if (lv_obj_get_height(button[idx]) > 100 || lv_obj_get_width(button[idx]) > 100) {
				lv_obj_add_style(button[idx], &Gui::panel_large_highlight_style, LV_PART_MAIN);
			} else {
				lv_obj_add_style(button[idx], &Gui::panel_highlight_style, LV_PART_MAIN);
			}
			lv_event_send(button[idx], LV_EVENT_REFRESH, nullptr);
			lv_obj_scroll_to_view(button[idx], LV_ANIM_ON);
		}
	}

	void focus_button_bar() {
		if (!full_screen_mode) {
			if (gui_state.new_cable)
				lv_group_focus_obj(ui_ModuleViewCableCancelBut);
			else
				lv_group_focus_obj(ui_ModuleViewSettingsBut);

			lv_group_set_editing(group, false);
			cur_selected = 1;
			lv_roller_set_selected(ui_ElementRoller, cur_selected, LV_ANIM_OFF);
			unhighlight_component(cur_selected);
		}
	}

	void click_cable_destination(unsigned drawn_idx) {
		// Determine id and type of this element
		std::optional<Jack> this_jack{};
		ElementType this_jack_type{};
		auto idx = drawn_elements[drawn_idx].gui_element.idx;

		std::visit(overloaded{[](auto const &) {},
							  [&](const JackInput &) {
								  this_jack_type = ElementType::Input;
								  this_jack = Jack{.module_id = this_module_id, .jack_id = idx.input_idx};
							  },
							  [&](const JackOutput &) {
								  this_jack_type = ElementType::Output;
								  this_jack = Jack{.module_id = this_module_id, .jack_id = idx.output_idx};
							  }},
				   drawn_elements[drawn_idx].element);

		if (this_jack) {
			make_cable(gui_state.new_cable.value(), patch, module_mods, notify_queue, *this_jack, this_jack_type);

			handle_patch_mods();

			gui_state.new_cable = std::nullopt;

			// Do not show instructions again this session
			gui_state.already_displayed_cable_instructions = true;

			gui_state.force_redraw_patch = true;
			PageArguments nextargs = {.patch_loc = args.patch_loc,
									  .patch_loc_hash = args.patch_loc_hash,
									  .module_id = args.module_id,
									  .detail_mode = false};
			page_list.update_state(PageId::ModuleView, nextargs);
			page_list.request_new_page(PageId::PatchView, nextargs);
			roller_hover.hide();
		} else
			pr_err("Error completing cable\n");
	}

	void click_normal_element(unsigned drawn_idx) {
		auto &drawn_element = drawn_elements[drawn_idx];
		args.element_indices = drawn_element.gui_element.idx;

		if (auto el = std::get_if<DynamicGraphicDisplay>(&drawn_element.element)) {
			PageArguments nextargs = {
				.patch_loc_hash = args.patch_loc_hash,
				.module_id = this_module_id,
				.element_indices = drawn_element.gui_element.idx,
				.element_mm = std::pair<float, float>{el->width_mm, el->height_mm},
			};
			page_list.update_state(PageId::ModuleView, nextargs);
			page_list.request_new_page(PageId::FullscreenGraphic, nextargs);
			roller_hover.hide();

		} else {
			//TODO: sometimes open manual popup immediately. (alt params, performance mode)
			// sometimes keep it hidden, but act as if it were open (full screen mode, performance mode with buttons)
			if (full_screen_mode) {
				//...
			}
			mode = ViewMode::Mapping;
			args.detail_mode = true;
			lv_hide(ui_ElementRollerPanel);
			roller_hover.hide();

			mapping_pane.show(drawn_element);
		}
	}

	void show_context_menu() {
		// Ignore clicking on Context Menu when in full_screen_mode
		if (!full_screen_mode) {
			mode = ViewMode::ModuleContextMenu;
			lv_hide(ui_ElementRoller);
			roller_hover.hide();
			module_context_menu.show();
		}
	}

	static void roller_click_cb(lv_event_t *event) {
		auto page = static_cast<ModuleViewPage *>(event->user_data);
		auto roller_idx = page->cur_selected;

		if (auto drawn_idx = page->get_drawn_idx(roller_idx)) {

			if (page->gui_state.new_cable) {
				page->click_cable_destination(*drawn_idx);
			} else {
				page->click_normal_element(*drawn_idx);
			}

			//Not an element: Is it the Extra Menu?
		} else if (roller_idx < page->roller_drawn_el_idx.size()) {
			if (page->roller_drawn_el_idx[roller_idx] == ContextMenuTag) {
				page->show_context_menu();
			}
		}
	}

	static void roller_focus_cb(lv_event_t *event) {
		auto page = static_cast<ModuleViewPage *>(event->user_data);
		if (page) {
			if (page->roller_drawn_el_idx.size() <= 1) {
				page->focus_button_bar();
				page->roller_hover.hide();
				return;
			}

			if (event->param != page) {
				lv_group_set_editing(page->group, true);
				lv_event_send(ui_ElementRoller, LV_EVENT_PRESSED, nullptr);

				if (auto drawn_idx = page->get_drawn_idx(page->cur_selected)) {
					page->highlight_component(*drawn_idx);
				}
			}
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
		page->full_screen_mode = true;
	}

	static void jump_to_roller_cb(lv_event_t *event) {
		if (!event || !event->user_data)
			return;
		auto page = static_cast<ModuleViewPage *>(event->user_data);
		if (page->full_screen_mode) {
			lv_group_focus_obj(ui_ElementRoller);
		}
	}

	std::optional<unsigned> get_drawn_idx(unsigned roller_idx) {
		if (roller_idx < roller_drawn_el_idx.size()) {
			auto drawn_idx = roller_drawn_el_idx[roller_idx];
			if ((size_t)drawn_idx < drawn_elements.size()) {
				return drawn_idx;
			}
		}
		return std::nullopt;
	}

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

	std::vector<lv_obj_t *> button;
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

	enum { ContextMenuTag = -2 };
};

} // namespace MetaModule
