#pragma once
#include "CoreModules/elements/element_info.hh"
#include "gui/elements/element_name.hh"
#include "gui/elements/map_ring_animate.hh"
#include "gui/elements/module_drawer.hh"
#include "gui/elements/redraw.hh"
#include "gui/elements/redraw_light.hh"
#include "gui/pages/base.hh"
#include "gui/pages/cable_drawer.hh"
#include "gui/pages/module_view_action_menu.hh"
#include "gui/pages/module_view_mapping_pane.hh"
#include "gui/pages/page_list.hh"
#include "gui/slsexport/meta5/ui.h"
#include "gui/styles.hh"

namespace MetaModule
{
struct ModuleViewPage : PageBase {

	ModuleViewPage(PatchContext context)
		: PageBase{context, PageId::ModuleView}
		, cable_drawer{ui_ModuleImage, drawn_elements}
		, map_ring_display{settings}
		, patch{patches.get_view_patch()}
		, mapping_pane{patches, module_mods, params, args, page_list, notify_queue, gui_state}
		, action_menu{patch_mod_queue, patches} {

		init_bg(ui_MappingMenu);

		lv_draw_img_dsc_init(&img_dsc);

		lv_obj_remove_style(ui_ElementRoller, nullptr, LV_STATE_EDITED);
		lv_obj_remove_style(ui_ElementRoller, nullptr, LV_STATE_FOCUS_KEY);

		lv_obj_add_flag(ui_MappingParameters, LV_OBJ_FLAG_HIDDEN);

		button.clear();

		auto roller_label = lv_obj_get_child(ui_ElementRoller, 0);
		lv_label_set_recolor(roller_label, true);

		lv_group_remove_all_objs(group);
		lv_group_add_obj(group, ui_ElementRoller);
		lv_group_add_obj(group, ui_ModuleViewActionBut);
		lv_group_add_obj(group, ui_ModuleViewSettingsBut);
		lv_group_focus_obj(ui_ElementRoller);

		lv_obj_add_event_cb(ui_ElementRoller, roller_scrolled_cb, LV_EVENT_KEY, this);
		lv_obj_add_event_cb(ui_ElementRoller, roller_click_cb, LV_EVENT_CLICKED, this);
		lv_obj_add_event_cb(ui_ElementRoller, roller_focus_cb, LV_EVENT_FOCUSED, this);
	}

	void prepare_focus() override {
		patch = patches.get_view_patch();

		is_patch_playing = patch_is_playing(args.patch_loc_hash);

		this_module_id = args.module_id.value_or(this_module_id);

		if (!read_slug()) {
			notify_queue.put(
				{"Cannot determine module to view. Patch file may be corrupted.", Notification::Priority::Error});
			return;
		}

		moduleinfo = ModuleFactory::getModuleInfo(slug);
		if (moduleinfo.width_hp == 0) {
			notify_queue.put(
				{"Cannot show module " + std::string(slug) + ". Never heard of it!", Notification::Priority::Error});
			return;
		}

		module_slug = module_name(slug);
		lv_label_set_text(ui_ElementRollerModuleName, module_slug.c_str());

		redraw_module();

		lv_hide(ui_ModuleViewActionMenu);

		action_menu.prepare_focus(group, this_module_id);
	}

	void redraw_module() {
		reset_module_page();

		size_t num_elements = moduleinfo.elements.size();
		opts.reserve(num_elements * 32); // 32 chars per roller item
		button.reserve(num_elements);
		drawn_elements.reserve(num_elements);

		auto module_drawer = ModuleDrawer{ui_ModuleImage, 240};
		canvas = module_drawer.draw_faceplate(slug, buffer);

		lv_obj_refr_size(canvas);
		auto width_px = lv_obj_get_width(canvas);
		//module img + padding is no more than 190px wide
		auto display_widthpx = std::min<lv_coord_t>(width_px + 4, 190);
		lv_obj_set_width(ui_ModuleImage, display_widthpx);
		lv_obj_refr_size(ui_ModuleImage);
		if (lv_obj_get_width(ui_ModuleImage) > width_px) {
			lv_obj_clear_flag(ui_ModuleImage, LV_OBJ_FLAG_SCROLLABLE);
		} else {
			lv_obj_add_flag(ui_ModuleImage, LV_OBJ_FLAG_SCROLLABLE);
		}

		lv_obj_clear_flag(canvas, LV_OBJ_FLAG_SCROLLABLE);

		active_knobset = page_list.get_active_knobset();

		module_drawer.draw_mapped_elements(
			*patch, this_module_id, active_knobset, canvas, drawn_elements, is_patch_playing);

		lv_obj_update_layout(canvas);

		// Populate Roller and highlighter buttons
		unsigned roller_idx = 0;
		DrawnElement const *cur_el = nullptr;
		ElementCount::Counts last_type{};

		for (auto [drawn_el_idx, drawn_element] : enumerate(drawn_elements)) {
			auto &drawn = drawn_element.gui_element;

			for (unsigned i = 0; i < drawn.count.num_lights; i++) {
				params.lights.start_watching_light(this_module_id, drawn.idx.light_idx + i);
			}

			auto base = base_element(drawn_element.element);

			if (base.short_name.size() == 0) {
				pr_info("Skipping element with no name\n");
				continue;
			}

			if (last_type.num_params == 0 && drawn.count.num_params > 0) {
				opts += Gui::orange_highlight_html_str + "Params:" + LV_TXT_COLOR_CMD + "\n";
				roller_idx++;
				roller_drawn_el_idx.push_back(-1);

			} else if (last_type.num_params > 0 && (drawn.count.num_inputs > 0 || drawn.count.num_outputs > 0)) {
				opts += Gui::orange_highlight_html_str + "Jacks:" + LV_TXT_COLOR_CMD + "\n";
				roller_idx++;
				roller_drawn_el_idx.push_back(-1);

			} else if (last_type.num_lights == 0 && drawn.count.num_lights > 0 && drawn.count.num_params == 0) {
				opts += Gui::orange_highlight_html_str + "Lights:" + LV_TXT_COLOR_CMD + "\n";
				roller_idx++;
				roller_drawn_el_idx.push_back(-1);
			}
			last_type = drawn.count;

			opts.append(" ");
			opts.append(base.short_name);

			if (drawn.mapped_panel_id) {
				append_panel_name(opts, drawn_element.element, drawn.mapped_panel_id.value());
			}

			append_connected_jack_name(opts, drawn, *patch);

			opts += "\n";
			add_button(drawn.obj);
			roller_drawn_el_idx.push_back(drawn_el_idx);

			if (args.element_indices.has_value()) {
				if (ElementCount::matched(*args.element_indices, drawn.idx)) {
					cur_selected = roller_idx;
					cur_el = &drawn_element;
				}
			}

			roller_idx++;
		}

		// remove final \n
		if (opts.length() > 0)
			opts.pop_back();

		//Show Roller and select it
		lv_obj_set_pos(ui_ElementRollerPanel, 0, 0);
		auto roller_width = std::min(320 - display_widthpx, 220); //roller is no more than 220px wide
		lv_obj_set_size(ui_ElementRollerPanel, roller_width, 240);
		lv_obj_clear_flag(ui_ElementRollerPanel, LV_OBJ_FLAG_HIDDEN);

		// Add text list to roller options
		lv_roller_set_options(ui_ElementRoller, opts.c_str(), LV_ROLLER_MODE_NORMAL);

		lv_roller_set_selected(ui_ElementRoller, cur_selected, LV_ANIM_OFF);

		if (cur_selected < button.size() && button.size() > 0) {
			lv_obj_add_style(button[cur_selected], &Gui::panel_highlight_style, LV_PART_MAIN);
		} else {
			pr_err("Current selected is not in range (%d/%zu)\n", cur_selected, button.size());
		}

		update_map_ring_style();

		cable_drawer.set_height(240);
		update_cable_style(true);

		mapping_pane.prepare_focus(group, roller_width, is_patch_playing);

		// TODO: useful to make a PageArgument that selects an item from the roller but stays in List mode?
		if (cur_el) {
			mode = ViewMode::Mapping;
			mapping_pane.hide();
			mapping_pane.show(*cur_el);
		} else {
			show_roller();
		}
	}

	void update() override {
		if (metaparams.back_button.is_just_released()) {

			if (action_menu.is_visible()) {
				action_menu.hide();

			} else if (mode == ViewMode::List) {
				load_prev_page();

			} else if (mode == ViewMode::Mapping) {
				mapping_pane.back_event();
			}
		}

		if (mode == ViewMode::Mapping) {
			mapping_pane.update();
			if (mapping_pane.wants_to_close()) {
				show_roller();
			}
		}

		if (action_menu.is_visible())
			action_menu.update();

		if (is_patch_playing && active_knobset != page_list.get_active_knobset()) {
			args.view_knobset_id = page_list.get_active_knobset();
			active_knobset = page_list.get_active_knobset();
			redraw_map_rings();
		}

		if (is_patch_playing) {
			// copy light values from params, indexed by light element id
			for (auto &wl : params.lights.watch_lights) {
				if (wl.light_id >= MAX_LIGHTS_PER_MODULE)
					continue;

				if (wl.is_active() && wl.module_id == this_module_id) {
					light_vals[wl.light_id] = wl.value;
				}
			}

			for (auto &drawn_el : drawn_elements) {
				auto &gui_el = drawn_el.gui_element;

				auto was_redrawn = std::visit(RedrawElement{patch, drawn_el.gui_element}, drawn_el.element);

				if (was_redrawn && settings.map_ring_flash_active) {
					map_ring_display.flash_once(gui_el.map_ring, true);
				}

				update_light(drawn_el, light_vals);
			}
		}

		if (auto patch_mod = module_mods.get(); patch_mod.has_value()) {
			patches.mark_view_patch_modified();

			bool refresh = true;
			// Apply to this thread's copy of patch
			std::visit(overloaded{
						   [&, this](AddMapping &mod) { refresh = patch->add_update_mapped_knob(mod.set_id, mod.map); },
						   [&, this](AddMidiMap &mod) { refresh = patch->add_update_midi_map(mod.map); },
						   [&, this](AddInternalCable &mod) { patch->add_internal_cable(mod.in, mod.out); },
						   [&, this](AddJackMapping &mod) {
							   mod.type == ElementType::Output ?
								   patch->add_mapped_outjack(mod.panel_jack_id, mod.jack) :
								   patch->add_mapped_injack(mod.panel_jack_id, mod.jack);
						   },
						   [&, this](DisconnectJack &mod) {
							   mod.type == ElementType::Output ? patch->disconnect_outjack(mod.jack) :
																 patch->disconnect_injack(mod.jack);
						   },
						   [&](auto &m) { refresh = false; },
					   },
					   patch_mod.value());

			if (refresh) {
				redraw_module();
				mapping_pane.refresh();
			}

			// Forward the mod to the audio/patch_player queue
			if (is_patch_playing)
				patch_mod_queue.put(patch_mod.value());
		}
	}

	void redraw_map_rings() {
		for (auto &drawn_el : drawn_elements) {
			auto &gui_el = drawn_el.gui_element;

			if (gui_el.count.num_params > 0 && gui_el.map_ring) {
				lv_obj_del_async(gui_el.map_ring);
				gui_el.map_ring = nullptr;
			}
		}

		for (auto &drawn_el : drawn_elements) {
			auto module_id = drawn_el.gui_element.module_idx;
			auto canvas = lv_obj_get_parent(drawn_el.gui_element.obj);

			ModuleDrawer{ui_ModuleImage, 240}.draw_mapped_ring(*patch, module_id, active_knobset, canvas, drawn_el);
		}
		update_map_ring_style();
	}

	// This gets called after map_ring_style changes
	void update_map_ring_style() {
		for (auto &drawn_el : drawn_elements) {
			map_ring_display.update(drawn_el, true, is_patch_playing);
		}
	}

	void update_cable_style(bool force = false) {
		static MapRingStyle last_cable_style;

		cable_drawer.set_opacity(settings.cable_style.opa);

		if (force || settings.cable_style.mode != last_cable_style.mode) {
			if (settings.cable_style.mode == MapRingStyle::Mode::ShowAll)
				cable_drawer.draw_single_module(*patch, this_module_id);
			else
				cable_drawer.clear();
		}
		last_cable_style = settings.cable_style;
	}

	void blur() final {
		params.lights.stop_watching_all();
		action_menu.hide();
	}

private:
	void show_roller() {
		mode = ViewMode::List;
		mapping_pane.hide();
		lv_show(ui_ElementRollerPanel);
		lv_group_focus_obj(ui_ElementRoller);
		lv_group_set_editing(group, true);
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
		} else {
			lv_obj_set_pos(b, 0, 0);
			lv_obj_set_size(b, 0, 0);
		}
	}

	void reset_module_page() {
		for (auto &b : button)
			lv_obj_del(b);

		if (canvas)
			lv_obj_del(canvas);

		button.clear();
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
		auto &but = page->button;

		auto cur_sel = page->cur_selected;

		auto next_sel = lv_roller_get_selected(ui_ElementRoller);

		// Turn off old button
		if (cur_sel < page->roller_drawn_el_idx.size()) {
			if (size_t idx = page->roller_drawn_el_idx[cur_sel]; idx < but.size()) {
				lv_obj_remove_style(but[idx], &Gui::panel_highlight_style, LV_PART_MAIN);
				lv_event_send(but[idx], LV_EVENT_REFRESH, nullptr);
			}
		}

		// Get the new button
		page->cur_selected = next_sel;
		if (next_sel < page->roller_drawn_el_idx.size()) {
			if (size_t idx = page->roller_drawn_el_idx[next_sel]; idx < but.size()) {
				// Turn on new button
				lv_obj_add_style(but[idx], &Gui::panel_highlight_style, LV_PART_MAIN);
				lv_event_send(but[idx], LV_EVENT_REFRESH, nullptr);
				lv_obj_scroll_to_view(but[idx], LV_ANIM_ON);
			} else {
				// Skip over headers
				if (cur_sel < next_sel) {
					if (next_sel < lv_roller_get_option_cnt(ui_ElementRoller) - 1)
						next_sel++;
					else
						next_sel = cur_sel;
				} else {
					if (next_sel)
						next_sel--;
					else {
						//Going up from first header -> defocus roller and focus button bar
						lv_group_focus_obj(ui_ModuleViewSettingsBut);
						lv_group_set_editing(page->group, false);
						page->cur_selected = cur_sel;
						lv_roller_set_selected(ui_ElementRoller, cur_sel, LV_ANIM_OFF);
						return;
					}
				}
				lv_roller_set_selected(ui_ElementRoller, next_sel, LV_ANIM_ON);
				page->cur_selected = next_sel;
			}
		}
	}

	static void roller_click_cb(lv_event_t *event) {
		auto page = static_cast<ModuleViewPage *>(event->user_data);
		auto cur_sel = page->cur_selected;

		if (cur_sel < page->drawn_elements.size()) {
			page->mode = ViewMode::Mapping;
			lv_hide(ui_ElementRollerPanel);

			auto drawn_idx = page->roller_drawn_el_idx[cur_sel];
			if (drawn_idx >= 0)
				page->mapping_pane.show(page->drawn_elements[drawn_idx]);
		}
	}

	static void roller_focus_cb(lv_event_t *event) {
		auto page = static_cast<ModuleViewPage *>(event->user_data);
		if (page) {
			if (event->param != page) {
				lv_group_set_editing(page->group, true);
				lv_event_send(ui_ElementRoller, LV_EVENT_PRESSED, nullptr);
			}
		}
	}

	CableDrawer<240> cable_drawer;

	ModuleInfoView moduleinfo;
	PatchModQueue module_mods;

	MapRingDisplay map_ring_display;

	std::string opts;
	uint16_t this_module_id = 0;
	uint32_t cur_selected = 0;
	std::string_view slug = "";
	ModuleTypeSlug module_slug;
	bool is_patch_playing = false;
	PatchData *patch;

	unsigned active_knobset = 0;

	std::vector<lv_obj_t *> button;
	std::vector<DrawnElement> drawn_elements;
	std::vector<int> roller_drawn_el_idx;

	std::array<float, MAX_LIGHTS_PER_MODULE> light_vals{};

	lv_obj_t *canvas = nullptr;
	ModuleViewMappingPane mapping_pane;

	ModuleViewActionMenu action_menu;

	lv_color_t buffer[LV_CANVAS_BUF_SIZE_TRUE_COLOR_ALPHA(240, 240)]{};
	lv_draw_img_dsc_t img_dsc{};

	enum class ViewMode { List, Mapping } mode{ViewMode::List};
};

} // namespace MetaModule
