#pragma once
#include "CoreModules/elements/element_info.hh"
#include "gui/elements/element_name.hh"
#include "gui/elements/map_ring_animate.hh"
#include "gui/elements/module_drawer.hh"
#include "gui/elements/redraw.hh"
#include "gui/elements/redraw_display.hh"
#include "gui/elements/redraw_light.hh"
#include "gui/pages/base.hh"
#include "gui/pages/cable_drawer.hh"
#include "gui/pages/module_view_action_menu.hh"
#include "gui/pages/module_view_mapping_pane.hh"
#include "gui/pages/module_view_settings_menu.hh"
#include "gui/pages/page_list.hh"
#include "gui/slsexport/meta5/ui.h"
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
		, mapping_pane{patches, module_mods, params, args, page_list, notify_queue, gui_state}
		, action_menu{module_mods, patches, page_list, patch_playloader, notify_queue} {

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
		lv_group_add_obj(group, ui_ModuleViewActionBut);
		lv_group_add_obj(group, ui_ModuleViewSettingsBut);
		lv_group_add_obj(group, ui_ModuleViewCableCancelBut);
		lv_group_add_obj(group, ui_ElementRoller);
		lv_group_focus_obj(ui_ElementRoller);

		lv_group_set_wrap(group, false);

		lv_obj_add_event_cb(ui_ElementRoller, roller_scrolled_cb, LV_EVENT_KEY, this);
		lv_obj_add_event_cb(ui_ElementRoller, roller_click_cb, LV_EVENT_CLICKED, this);
		lv_obj_add_event_cb(ui_ElementRoller, roller_focus_cb, LV_EVENT_FOCUSED, this);
		lv_obj_add_event_cb(ui_ModuleViewCableCancelBut, cancel_cable_cb, LV_EVENT_CLICKED, this);
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

		auto module_display_name = ModuleFactory::getModuleDisplayName(slug);
		lv_label_set_text(ui_ElementRollerModuleName, module_display_name.data());

		redraw_module();

		lv_hide(ui_ModuleViewActionMenu);
		lv_hide(ui_AutoMapSelectPanel);
		lv_hide(ui_MIDIMapPanel);

		if (gui_state.new_cable) {
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
			auto &gui_el = drawn_element.gui_element;

			watch_lights(drawn_element);

			add_button(gui_el.obj);

			auto base = base_element(drawn_element.element);

			if (base.short_name.size() == 0) {
				pr_info("Skipping element with no name\n");
				continue;
			}

			if (is_light_only(gui_el))
				continue;

			if (should_skip_for_cable_mode(gui_state.new_cable, gui_el))
				continue;

			if (append_header(opts, last_type, gui_el.count)) {
				roller_idx++;
				roller_drawn_el_idx.push_back(-1);
			}
			last_type = gui_el.count;

			opts.append(" ");
			opts.append(base.short_name);

			if (gui_el.mapped_panel_id) {
				append_panel_name(opts, drawn_element.element, gui_el.mapped_panel_id.value());
			}

			append_connected_jack_name(opts, gui_el, *patch);

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

		if (roller_idx <= 1) {
			if (gui_state.new_cable) {
				opts.append("No available jacks to patch\n");
			}
		}

		// remove final \n
		if (opts.length() > 0)
			opts.pop_back();

		//Show Roller and select it
		lv_obj_set_pos(ui_ElementRollerPanel, 0, 0);
		auto roller_width = std::min<lv_coord_t>(320 - display_widthpx, 220); //roller is no more than 220px wide
		lv_obj_set_size(ui_ElementRollerPanel, roller_width, 240);
		lv_obj_clear_flag(ui_ElementRollerPanel, LV_OBJ_FLAG_HIDDEN);

		// Add text list to roller options
		lv_roller_set_options(ui_ElementRoller, opts.c_str(), LV_ROLLER_MODE_NORMAL);

		lv_roller_set_selected(ui_ElementRoller, cur_selected, LV_ANIM_OFF);

		if (cur_selected > 0 && cur_selected < button.size()) {
			if (auto idx = roller_drawn_el_idx[cur_selected]; (size_t)idx < button.size())
				lv_obj_add_style(button[idx], &Gui::panel_highlight_style, LV_PART_MAIN);
		} else {
			pr_err("Current selected is not in range (%d/%zu)\n", cur_selected, button.size());
		}

		update_map_ring_style();

		cable_drawer.set_height(240);
		update_cable_style(true);

		mapping_pane.prepare_focus(group, roller_width, is_patch_playing);

		// TODO: useful to make a PageArgument that selects an item from the roller but stays in List mode?
		if (cur_el && args.detail_mode == true) {
			mode = ViewMode::Mapping;
			mapping_pane.hide();
			mapping_pane.show(*cur_el);
		} else {
			show_roller();
		}
	}

	void watch_lights(DrawnElement const &drawn_element) {
		auto gui_el = drawn_element.gui_element;
		std::visit(overloaded{
					   [&](auto const &el) {
						   for (unsigned i = 0; i < gui_el.count.num_lights; i++) {
							   params.lights.start_watching_light(this_module_id, gui_el.idx.light_idx + i);
						   }
					   },
					   [&](DynamicTextDisplay const &el) {
						   params.displays.start_watching_display(this_module_id, gui_el.idx.light_idx);
					   },
				   },
				   drawn_element.element);
	}

	bool is_light_only(GuiElement const &gui_el) const {
		return (gui_el.count.num_lights > 0) && (gui_el.count.num_params == 0) && (gui_el.count.num_outputs == 0) &&
			   (gui_el.count.num_inputs == 0);
	}

	bool should_skip_for_cable_mode(std::optional<GuiState::CableBeginning> const &new_cable,
									GuiElement const &gui_el) const {
		if (gui_state.new_cable.has_value()) {
			uint16_t this_jack_id{};
			if (gui_el.count.num_inputs > 0)
				this_jack_id = gui_el.idx.input_idx;
			else if (gui_el.count.num_outputs > 0)
				this_jack_id = gui_el.idx.output_idx;
			else
				return true;
			auto this_jack_type = (gui_el.count.num_inputs > 0) ? ElementType::Input : ElementType::Output;
			if (!can_finish_cable(gui_state.new_cable.value(),
								  patch,
								  Jack{.module_id = this_module_id, .jack_id = this_jack_id},
								  this_jack_type,
								  gui_el.mapped_panel_id.has_value()))
				return true;
		}
		return false;
	}

	bool append_header(std::string &opts, ElementCount::Counts last_type, ElementCount::Counts this_type) {
		if (last_type.num_params == 0 && this_type.num_params > 0) {
			opts += Gui::orange_text("Params:") + "\n";
			return true;

		} else if ((last_type.num_inputs == 0 && last_type.num_outputs == 0) &&
				   (this_type.num_inputs > 0 || this_type.num_outputs > 0))
		{
			opts += Gui::orange_text("Jacks:") + "\n";
			return true;

		} else if (last_type.num_lights == 0 && this_type.num_lights > 0 && this_type.num_params == 0) {
			opts += Gui::orange_text("Lights:") + "\n";
			return true;
		} else {
			return false;
		}
	}

	bool is_creating_map() const {
		return mapping_pane.is_creating_map();
	}

	void update() override {
		if (gui_state.back_button.is_just_released()) {

			if (action_menu.is_visible()) {
				action_menu.hide();

			} else if (settings_menu.is_visible()) {
				settings_menu.hide();

			} else if (mode == ViewMode::List) {
				args.module_id = this_module_id;
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
			redraw_module();

			if (mode == ViewMode::Mapping)
				mapping_pane.refresh();
		}

		if (page_settings.changed) {
			page_settings.changed = false;
			update_map_ring_style();
			update_cable_style();
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

				if (was_redrawn && page_settings.map_ring_flash_active) {
					map_ring_display.flash_once(gui_el.map_ring, true);
				}

				update_light(drawn_el, light_vals);

				redraw_display(drawn_el, this_module_id, params.displays.watch_displays);
			}
		}

		if (handle_patch_mods()) {
			redraw_module();
			mapping_pane.refresh();
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
			if (is_patch_playing)
				patch_mod_queue.put(patch_mod.value());
		}

		return refresh;
	}

	// This gets called after map_ring_style changes
	void update_map_ring_style() {
		for (auto &drawn_el : drawn_elements) {
			map_ring_display.update(drawn_el, true, is_patch_playing);
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

	void blur() final {
		params.lights.stop_watching_all();
		params.displays.stop_watching_all();
		settings_menu.hide();
		action_menu.hide();
	}

private:
	void show_roller() {
		mode = ViewMode::List;
		mapping_pane.hide();
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

		auto cur_sel = lv_roller_get_selected(ui_ElementRoller);
		if (cur_sel >= page->roller_drawn_el_idx.size())
			return;

		auto prev_sel = page->cur_selected;
		auto cur_idx = page->roller_drawn_el_idx[cur_sel];

		// Skip over headers by scrolling over them in the same direction we just scrolled
		if (cur_idx < 0) {
			if (prev_sel < cur_sel) {
				if (cur_sel < lv_roller_get_option_cnt(ui_ElementRoller) - 1)
					cur_sel++;
				else
					// Don't scroll off the end of the roller
					cur_sel = prev_sel;

			} else {
				if (cur_sel)
					cur_sel--;
				else {
					//Scrolling up from first header -> defocus roller and focus button bar
					page->focus_button_bar();
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
	}

	void unhighlight_component(uint32_t prev_sel) {
		if (auto prev_idx = get_drawn_idx(prev_sel)) {
			lv_obj_remove_style(button[*prev_idx], &Gui::panel_highlight_style, LV_PART_MAIN);
			lv_event_send(button[*prev_idx], LV_EVENT_REFRESH, nullptr);
		}
	}

	void highlight_component(size_t idx) {
		if (idx < button.size()) {
			lv_obj_add_style(button[idx], &Gui::panel_highlight_style, LV_PART_MAIN);
			lv_event_send(button[idx], LV_EVENT_REFRESH, nullptr);
			lv_obj_scroll_to_view(button[idx], LV_ANIM_ON);
		}
	}

	void focus_button_bar() {
		if (gui_state.new_cable)
			lv_group_focus_obj(ui_ModuleViewCableCancelBut);
		else
			lv_group_focus_obj(ui_ModuleViewSettingsBut);

		lv_group_set_editing(group, false);
		cur_selected = 1;
		lv_roller_set_selected(ui_ElementRoller, cur_selected, LV_ANIM_OFF);
		unhighlight_component(cur_selected);
	}

	static void roller_click_cb(lv_event_t *event) {
		auto page = static_cast<ModuleViewPage *>(event->user_data);

		if (auto drawn_idx = page->get_drawn_idx(page->cur_selected)) {
			if (page->gui_state.new_cable) {
				// Determine id and type of this element
				std::optional<Jack> this_jack{};
				ElementType this_jack_type{};
				auto idx = page->drawn_elements[*drawn_idx].gui_element.idx;

				std::visit(overloaded{[](auto const &) {},
									  [&](const JackInput &) {
										  this_jack_type = ElementType::Input;
										  this_jack = Jack{.module_id = page->this_module_id, .jack_id = idx.input_idx};
									  },
									  [&](const JackOutput &) {
										  this_jack_type = ElementType::Output;
										  this_jack =
											  Jack{.module_id = page->this_module_id, .jack_id = idx.output_idx};
									  }},
						   page->drawn_elements[*drawn_idx].element);

				if (this_jack) {
					make_cable(page->gui_state.new_cable.value(),
							   page->patch,
							   page->module_mods,
							   page->notify_queue,
							   *this_jack,
							   this_jack_type);

					page->handle_patch_mods();

					page->gui_state.new_cable = std::nullopt;

					// Do not show instructions again this session
					page->gui_state.already_displayed_cable_instructions = true;

					page->gui_state.force_redraw_patch = true;
					PageArguments args = {.patch_loc = page->args.patch_loc,
										  .patch_loc_hash = page->args.patch_loc_hash,
										  .module_id = page->args.module_id,
										  .detail_mode = false};
					page->page_list.request_new_page(PageId::PatchView, args);
				} else
					pr_err("Error completing cable\n");

			} else {
				page->mode = ViewMode::Mapping;
				page->args.detail_mode = true;
				lv_hide(ui_ElementRollerPanel);

				page->mapping_pane.show(page->drawn_elements[*drawn_idx]);
			}
		}
	}

	static void roller_focus_cb(lv_event_t *event) {
		auto page = static_cast<ModuleViewPage *>(event->user_data);
		if (page) {
			if (page->roller_drawn_el_idx.size() <= 1) {
				page->focus_button_bar();
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
