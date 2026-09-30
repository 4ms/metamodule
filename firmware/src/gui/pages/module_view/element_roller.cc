#include "CoreModules/elements/units.hh"
#include "gui/elements/redraw.hh"
#include "gui/pages/module_view/group_member_name.hh"
#include "gui/pages/module_view/module_view.hh"
#include "gui/pages/module_view/roller_helpers.hh"
#include "util/countzip.hh"
#include "util/string_compare.hh"
#include <algorithm>

namespace MetaModule
{

static void move_selected_control_foreground(std::span<DrawnElement> drawn_elements,
											 DrawnElement const &drawn_element) {
	auto *obj = drawn_element.gui_element.obj;
	if (!obj)
		return;

	if (std::holds_alternative<Knob>(drawn_element.element) ||
		std::holds_alternative<KnobSnapped>(drawn_element.element))
	{
		lv_obj_move_foreground(obj);
		raise_lights_over(drawn_elements, drawn_element);
	}
}

void ModuleViewPage::show_roller() {
	// 322 when closed, 102 when open
	if (lv_obj_get_x(ui_MVSettingsMenu) > 200) {
		metaparams.rotary_pushed.use_motion();
		module_context_menu.hide();
		mode = ViewMode::List;
		mapping_pane.hide();
		lv_show(ui_ElementRoller);
		lv_show(ui_ElementRollerPanel);
		lv_group_focus_obj(ui_ElementRoller);
		lv_group_set_editing(group, true);
		args.detail_mode = false;
	}
	lv_group_set_wrap(group, settings.module_view.nav_wrapping);
}

void ModuleViewPage::populate_element_objects() {
	size_t num_elements = moduleinfo.elements.size();
	element_highlights.reserve(num_elements);

	for (auto drawn_element : drawn_elements) {
		watch_element(drawn_element);
		add_element_highlight(drawn_element);
	}
}

void ModuleViewPage::populate_roller() {
	size_t num_elements = moduleinfo.elements.size();
	opts = "";
	opts.reserve(num_elements * 32); // estimate avg. 32 chars per roller item
	roller_drawn_el_idx.clear();

	if (current_group && *current_group >= layout.group_names.size())
		current_group.reset();

	// Arriving at an element that's in a group (e.g. from the map view) opens its group
	if (open_group_for_target && !current_group && args.element_indices) {
		if (auto drawn_idx = find_drawn_idx(*args.element_indices)) {
			if (layout.element_group[*drawn_idx] != ElementLayout::NoGroup)
				current_group = layout.element_group[*drawn_idx];
		}
	}
	open_group_for_target = false;

	std::string title = current_group ? Gui::blue_text(layout.group_names[*current_group]) :
										module_display_name(*patch, this_module_id);
	lv_label_set_text(ui_ElementRollerModuleName, title.c_str());

	// Populate Roller and element highlights
	unsigned roller_idx = 0;
	DrawnElement const *cur_el = nullptr;
	ElementCount::Counts last_type{};
	bool last_is_altparam = false;

	if (current_group) {
		opts += Gui::yellow_text(LV_SYMBOL_LEFT " Back") + "\n";
		roller_drawn_el_idx.push_back(BackTag);
		roller_idx++;
	}

	auto append_element = [&](unsigned drawn_el_idx) {
		auto const &drawn_element = drawn_elements[drawn_el_idx];
		auto const &gui_el = drawn_element.gui_element;
		auto base = base_element(drawn_element.element);

		if (base.short_name.size() == 0)
			pr_info("Element roller: Skipping element with no name\n");

		if (!is_listed(drawn_el_idx))
			return;

		auto this_is_altparam = ModView::is_altparam(drawn_element.element);
		if (ModView::append_header(opts, last_type, last_is_altparam, gui_el.count, this_is_altparam)) {
			roller_idx++;
			roller_drawn_el_idx.push_back(RollerHeaderTag);
		}
		last_type = gui_el.count;
		last_is_altparam = this_is_altparam;

		opts.append(" ");

		// Handle names that contain a newline or null char
		// Must use sv literal so the trailing \0 is considered a char, not a terminator
		using namespace std::literals;
		auto name = base.short_name.substr(0, base.short_name.find_first_of("\n\0"sv));

		// A custom name is shown as it's written. Otherwise, inside groups remove the group words
		if (layout.element_display_name[drawn_el_idx].size())
			opts.append(layout.element_display_name[drawn_el_idx]);
		else if (current_group)
			opts.append(ModView::group_member_name(name, layout.group_names[*current_group]));
		else
			opts.append(name);

		if (gui_el.midi_mapped_id) {
			// If the mapping and the MIDI mapping are different, then show both
			// Compare stripped ports because mapped_panel_id never has a port
			if (gui_el.mapped_panel_id && Midi::strip_port(*gui_el.midi_mapped_id) != *gui_el.mapped_panel_id) {
				append_panel_name(opts, drawn_element.element, gui_el.mapped_panel_id.value());
				opts.append("/");
			}
			append_panel_name(opts, drawn_element.element, gui_el.midi_mapped_id.value());

		} else if (gui_el.mapped_panel_id) {
			append_panel_name(opts, drawn_element.element, gui_el.mapped_panel_id.value());
		}

		if (settings.module_view.show_jack_aliases) {
			append_jack_alias(opts, drawn_element.gui_element, patch);
		}
		if (settings.module_view.show_knob_aliases) {
			append_param_alias(opts, drawn_element.gui_element, patch, active_knobset);
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
	};

	auto append_group_row = [&](unsigned group) {
		// A group only gets a row if it has something listable, even if we're currently
		// hiding all its members because we're patching a cable
		if (std::ranges::none_of(layout.group_members[group], [this](unsigned i) { return is_listable(i); }))
			return;

		opts += Gui::blue_text(std::string(layout.group_names[group]) + " " LV_SYMBOL_RIGHT) + "\n";
		roller_drawn_el_idx.push_back(group_row_tag(group));
		roller_idx++;

		// last_type is left alone: the type headers describe the elements
		// that are actually listed, and a group row shouldn't repeat one
	};

	if (current_group) {
		for (auto drawn_el_idx : layout.group_members[*current_group])
			append_element(drawn_el_idx);

	} else {
		for (auto entry : layout.top_level_entries) {
			if (entry.is_group)
				append_group_row(entry.idx);
			else
				append_element(entry.idx);
		}
	}

	if (is_patch_playloaded && !current_group) {
		if (has_context_menu) {
			opts += Gui::orange_text("Options:") + "\n";
			opts += " >>>\n";
			roller_drawn_el_idx.push_back(RollerHeaderTag);
			roller_drawn_el_idx.push_back(ContextMenuTag);
			roller_idx += 2;
		}
	}

	if (roller_idx <= 1 && !current_group) {
		if (gui_state.new_cable) {
			opts.append("No available jacks to patch\n");
		}
	}

	// remove final \n
	if (opts.length() > 0)
		opts.pop_back();

	lv_show(ui_ElementRollerPanel);

	// Add text list to roller options
	lv_roller_set_options(ui_ElementRoller, opts.c_str(), LV_ROLLER_MODE_NORMAL);

	if (cur_selected >= roller_drawn_el_idx.size())
		cur_selected = default_row();

	lv_roller_set_selected(ui_ElementRoller, cur_selected, LV_ANIM_OFF);

	highlight_row(cur_selected);

	if (cur_el && args.detail_mode == true) {
		mode = ViewMode::Mapping;
		mapping_pane.hide();
		mapping_pane.show(*cur_el);
	} else {
		show_roller();
	}
}

void ModuleViewPage::add_element_highlight(DrawnElement const &drawn_element) {
	auto const &gui_el = drawn_element.gui_element;
	auto const *obj = gui_el.obj;

	auto &b = element_highlights.emplace_back();
	b = lv_btn_create(ui_ModuleImage);
	lv_obj_remove_style(b, &Gui::invisible_style, LV_PART_MAIN);
	lv_obj_add_style(b, &Gui::invisible_style, LV_PART_MAIN);

	// Vertically position the highlights the same as the module canvas
	auto canvas_y = module_y_offset();

	if (obj) {
		float width = lv_obj_get_width(obj);
		float height = lv_obj_get_height(obj);
		float c_x = (float)lv_obj_get_x(obj) + width / 2.f;
		float c_y = (float)lv_obj_get_y(obj) + (float)canvas_y + height / 2.f;

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
		auto w = base_element(drawn_element.element).width_mm;
		auto h = base_element(drawn_element.element).height_mm;
		auto x = base_element(drawn_element.element).x_mm;
		auto y = base_element(drawn_element.element).y_mm;
		lv_obj_set_pos(b, mm_to_px(x, module_height), mm_to_px(y, module_height) + canvas_y);
		lv_obj_set_size(b, mm_to_px(w, module_height), mm_to_px(h, module_height));
	}
}

void ModuleViewPage::unhighlight_element(size_t idx) {
	if (idx < element_highlights.size()) {
		if (lv_obj_get_height(element_highlights[idx]) > 100 || lv_obj_get_width(element_highlights[idx]) > 100) {
			lv_obj_remove_style(element_highlights[idx], &Gui::panel_large_highlight_style, LV_PART_MAIN);
		} else {
			lv_obj_remove_style(element_highlights[idx], &Gui::panel_highlight_style, LV_PART_MAIN);
		}
		lv_event_send(element_highlights[idx], LV_EVENT_REFRESH, nullptr);
	}
}

void ModuleViewPage::unhighlight_component(uint32_t prev_sel) {
	if (auto prev_idx = get_drawn_idx(prev_sel)) {
		unhighlight_element(*prev_idx);
	} else if (auto group = get_group_idx(prev_sel)) {
		for (auto drawn_idx : layout.group_members[*group])
			unhighlight_element(drawn_idx);
	}
}

// Highlight what a roller row stands for on the panel: its element, or each listed member of its group
void ModuleViewPage::highlight_row(uint32_t roller_idx) {
	if (auto drawn_idx = get_drawn_idx(roller_idx)) {
		highlight_component(*drawn_idx);
		move_selected_control_foreground(drawn_elements, drawn_elements[*drawn_idx]);

	} else if (auto group = get_group_idx(roller_idx)) {
		// Scroll to the first member, where opening the group will start
		bool scroll_into_view = true;
		for (auto drawn_idx : layout.group_members[*group]) {
			if (is_listed(drawn_idx)) {
				highlight_component(drawn_idx, scroll_into_view);
				scroll_into_view = false;
			}
		}
	}
}

void ModuleViewPage::highlight_component(size_t idx, bool scroll_into_view) {
	if (idx < element_highlights.size()) {
		if (lv_obj_get_height(element_highlights[idx]) > 100 || lv_obj_get_width(element_highlights[idx]) > 100) {
			lv_obj_remove_style(element_highlights[idx], &Gui::panel_large_highlight_style, LV_PART_MAIN);
			lv_obj_add_style(element_highlights[idx], &Gui::panel_large_highlight_style, LV_PART_MAIN);
		} else {
			lv_obj_remove_style(element_highlights[idx], &Gui::panel_highlight_style, LV_PART_MAIN);
			lv_obj_add_style(element_highlights[idx], &Gui::panel_highlight_style, LV_PART_MAIN);
		}
		lv_event_send(element_highlights[idx], LV_EVENT_REFRESH, nullptr);
		if (scroll_into_view)
			lv_obj_scroll_to_view(element_highlights[idx], LV_ANIM_ON);
	}
}

void ModuleViewPage::roller_scrolled_cb(lv_event_t *event) {
	auto page = static_cast<ModuleViewPage *>(event->user_data);

	auto cur_sel = lv_roller_get_selected(ui_ElementRoller);
	if (cur_sel >= page->roller_drawn_el_idx.size()) {
		page->roller_hover.hide();
		return;
	}

	auto prev_sel = page->cur_selected;
	auto cur_idx = page->roller_drawn_el_idx[cur_sel];

	// Wrap off bottom back to button bar when scrolling down
	auto key = lv_event_get_key(event);
	bool const scrolled_down = key == LV_KEY_RIGHT || key == LV_KEY_DOWN;
	if (page->settings.module_view.nav_wrapping && scrolled_down) {
		if (prev_sel == (uint32_t)cur_sel && cur_sel == lv_roller_get_option_cnt(ui_ElementRoller) - 1) {
			page->focus_button_bar(true);
			page->roller_hover.hide();
			return;
		}
	}

	// Skip over headers by scrolling over them in the same direction we just scrolled
	if (cur_idx == RollerHeaderTag) {
		if (prev_sel < cur_sel) {
			// Scroll down:
			if (cur_sel < lv_roller_get_option_cnt(ui_ElementRoller) - 1)
				cur_sel++;
			else
				// Don't scroll off the end of the roller
				cur_sel = prev_sel;

		} else {
			// Scroll up:
			if (cur_sel)
				cur_sel--;

			else if (!page->full_screen_mode) {
				//Scrolling up from first header -> defocus roller and focus button bar
				page->focus_button_bar();
				page->roller_hover.hide();
				return;
			} else {
				// stay on the first item in the roller
				cur_sel = 1;
			}
		}
		// cur_sel changed, so we need to update the roller position and our drawn_el idx
		lv_roller_set_selected(ui_ElementRoller, cur_sel, LV_ANIM_ON);
		cur_idx = page->roller_drawn_el_idx[cur_sel];
	}

	// Context menu:
	if (cur_idx == ContextMenuTag) {
		if (page->full_screen_mode) {
			// Not allowed in full screen mode: go back to previous item
			cur_sel = prev_sel;
			lv_roller_set_selected(ui_ElementRoller, cur_sel, LV_ANIM_ON);
		} else {
			page->unhighlight_component(prev_sel);
			page->cur_selected = cur_sel;
			page->roller_hover.hide();
		}
		return;
	}

	// Back and group rows don't select an element. A group row highlights its members.
	if (cur_idx == BackTag || is_group_tag(cur_idx)) {
		// Scrolling up from one of these rows at the top of the roller -> focus the button bar.
		bool const scrolled_up = key == LV_KEY_LEFT || key == LV_KEY_UP;
		if (scrolled_up && cur_sel == 0 && prev_sel == 0 && !page->full_screen_mode) {
			page->focus_button_bar();
			page->roller_hover.hide();
			return;
		}

		page->unhighlight_component(prev_sel);
		page->highlight_row(cur_sel);
		page->cur_selected = cur_sel;
		page->roller_hover.hide();
		return;
	}

	page->cur_selected = cur_sel;

	// Save current select in args so we can navigate back to this item
	page->args.element_indices = page->drawn_elements[cur_idx].gui_element.idx;

	if (page->get_drawn_idx(prev_sel) != cur_idx) {
		page->unhighlight_component(prev_sel);
		page->highlight_component(cur_idx);
	}

	move_selected_control_foreground(page->drawn_elements, page->drawn_elements[cur_idx]);
	page->roller_hover.hide();
}

void ModuleViewPage::focus_button_bar(bool first_item) {
	if (!full_screen_mode) {
		if (gui_state.new_cable)
			lv_group_focus_obj(ui_ModuleViewCableCancelBut);
		else
			lv_group_focus_obj(first_item ? ui_ModuleViewHideBut : ui_ModuleViewSettingsBut);

		lv_group_set_editing(group, false);
		if (first_item) {
			auto cur_sel = lv_roller_get_option_cnt(ui_ElementRoller) - 1;
			lv_roller_set_selected(ui_ElementRoller, cur_sel, LV_ANIM_OFF);
			cur_selected = cur_sel;
			unhighlight_component(cur_sel);
		} else {
			cur_selected = first_selectable_row();
			lv_roller_set_selected(ui_ElementRoller, cur_selected, LV_ANIM_OFF);
			unhighlight_component(cur_selected);
		}
	}
}

void ModuleViewPage::click_cable_destination(unsigned drawn_idx) {
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

void ModuleViewPage::click_altparam_action(DrawnElement const &drawn_element) {
	args.element_indices = drawn_element.gui_element.idx;

	if (is_patch_playloaded) {
		StaticParam sp{
			.module_id = drawn_element.gui_element.module_idx,
			.param_id = drawn_element.gui_element.idx.param_idx,
			.value = 1,
		};
		patch_mod_queue.put(SetStaticParam{.param = sp});

		patch->set_or_add_static_knob_value(sp.module_id, sp.param_id, sp.value);
	}
}

void ModuleViewPage::manual_control_popup(DrawnElement const &drawn_element) {
	args.element_indices = drawn_element.gui_element.idx;

	if (is_patch_playloaded) {
		quick_control_mode = false;
		mapping_pane.show_control_popup(group, ui_ElementRollerPanel, drawn_element);
	}
}

void ModuleViewPage::click_graphic_display(DrawnElement const &drawn_element, DynamicGraphicDisplay const *el) {
	args.element_indices = drawn_element.gui_element.idx;

	PageArguments nextargs = {
		.patch_loc_hash = args.patch_loc_hash,
		.module_id = this_module_id,
		.element_indices = drawn_element.gui_element.idx,
		.element_mm = std::pair<float, float>{el->width_mm, el->height_mm},
	};
	page_list.update_state(PageId::ModuleView, nextargs);
	page_list.request_new_page(PageId::FullscreenGraphic, nextargs);
	roller_hover.hide();
}

void ModuleViewPage::click_normal_element(DrawnElement const &drawn_element) {
	// Ignore click if we just did a quick assignment (prevents unwanted mapping pane opening)
	if (suppress_next_click) {
		suppress_next_click = false;
		return;
	}

	args.element_indices = drawn_element.gui_element.idx;

	mode = ViewMode::Mapping;
	args.detail_mode = true;
	lv_hide(ui_ElementRollerPanel);
	roller_hover.hide();

	mapping_pane.show(drawn_element);
}

void ModuleViewPage::roller_click_cb(lv_event_t *event) {
	auto page = static_cast<ModuleViewPage *>(event->user_data);
	auto roller_idx = page->cur_selected;

	if (auto drawn_idx = page->get_drawn_idx(roller_idx)) {

		auto &drawn_element = page->drawn_elements[*drawn_idx];

		if (page->gui_state.new_cable) {
			page->click_cable_destination(*drawn_idx);

		} else if (std::get_if<AltParamAction>(&drawn_element.element)) {
			page->click_altparam_action(drawn_element);

		} else if (std::get_if<AltParamContinuous>(&drawn_element.element) ||
				   std::get_if<AltParamChoice>(&drawn_element.element) ||
				   std::get_if<AltParamChoiceLabeled>(&drawn_element.element))
		{
			page->manual_control_popup(drawn_element);

		} else if (auto el = std::get_if<DynamicGraphicDisplay>(&drawn_element.element)) {
			page->click_graphic_display(drawn_element, el);

		} else {
			page->click_normal_element(drawn_element);
		}

		//Not an element: Is it the Context Menu, a group row, or Back?
	} else if (roller_idx < page->roller_drawn_el_idx.size()) {
		auto tag = page->roller_drawn_el_idx[roller_idx];

		if (tag == ContextMenuTag)
			page->show_context_menu();

		else if (tag == BackTag)
			page->exit_group();

		else if (is_group_tag(tag))
			page->enter_group(group_from_tag(tag));
	}
}

void ModuleViewPage::roller_pressed_cb(lv_event_t *event) {
	auto page = static_cast<ModuleViewPage *>(event->user_data);
	if (page) {
		auto roller = (lv_roller_t *)ui_ElementRoller;
		roller->sel_opt_id_ori = roller->sel_opt_id;
		page->roller_hover.force_redraw();
	}
}

void ModuleViewPage::roller_focus_cb(lv_event_t *event) {
	auto page = static_cast<ModuleViewPage *>(event->user_data);
	if (page) {
		// Nothing to select: go to the button bar
		if (page->roller_drawn_el_idx.size() <= 1 && !page->current_group) {
			page->focus_button_bar();
			page->roller_hover.hide();
			return;
		}

		// Change to "edit" mode if not already editting
		if (lv_group_get_editing(page->group) == false) {

			if (page->settings.module_view.nav_wrapping && page->last_button_focused == ui_ModuleViewHideBut) {
				auto cur_sel = lv_roller_get_option_cnt(ui_ElementRoller) - 1;
				lv_roller_set_selected(ui_ElementRoller, cur_sel, LV_ANIM_OFF);
				page->cur_selected = cur_sel;
			}
			if (page->last_button_focused == ui_ModuleViewSettingsBut) {
				auto cur_sel = page->first_selectable_row();
				lv_roller_set_selected(ui_ElementRoller, cur_sel, LV_ANIM_OFF);
				page->cur_selected = cur_sel;
			}

			// Must send a PRESS event to enter "edit" mode
			lv_event_send(ui_ElementRoller, LV_EVENT_PRESSED, nullptr);
			// This sends another FOCUSED event:
			lv_group_set_editing(page->group, true);
		}
		page->highlight_row(page->cur_selected);
		page->last_button_focused = nullptr;
	}
}

void ModuleViewPage::jump_to_roller_cb(lv_event_t *event) {
	if (!event || !event->user_data)
		return;
	auto page = static_cast<ModuleViewPage *>(event->user_data);
	if (page->full_screen_mode) {
		lv_group_focus_obj(ui_ElementRoller);
	} else {
		page->last_button_focused = event->target;
	}
}

std::optional<unsigned> ModuleViewPage::find_drawn_idx(ElementCount::Indices indices) const {
	for (auto [i, drawn_element] : enumerate(drawn_elements)) {
		if (ElementCount::matched(indices, drawn_element.gui_element.idx))
			return i;
	}
	return std::nullopt;
}

// Resolve this module's registered groups, order, and custom names against its drawn elements.
void ModuleViewPage::build_element_layout() {
	layout.build(slug, drawn_elements);

	std::string err_notif;
	for (auto const &[i, error] : enumerate(layout.errors)) {
		pr_dev("Module %.*s: plugin-mm.json: %s\n", (int)slug.size(), slug.data(), error.c_str());

		if (i < 3)
			err_notif += error + "\n";
		else if (i == 3)
			err_notif += "...and more\n";
	}
	auto err_count = layout.errors.size();

#ifdef SIMULATOR
	const bool do_show_error_notif = true;
#else
	const bool do_show_error_notif = settings.developer.enabled;
#endif
	if (err_count && do_show_error_notif) {
		std::string leader =
			err_count == 1 ? "Found an error for '" : "Found " + std::to_string(err_count) + " errors for '";

		notify_queue.put({leader + std::string(slug) + "' in plugin-mm.json:\n" + err_notif + "See console log",
						  Notification::Priority::Error,
						  10000});
	}
}

// Open a group: show only its elements, with a "< Back" row above them
void ModuleViewPage::enter_group(unsigned group_idx) {
	if (group_idx >= layout.group_names.size())
		return;

	unhighlight_component(cur_selected);

	current_group = group_idx;
	args.element_indices = std::nullopt; // don't re-open the group we came from
	cur_selected = 1;
	populate_roller();

	// Start on the group's first highlight-able element unless the group is
	// empty (while patching a cable), then default to the Back row (0)
	cur_selected = 0;
	for (auto [i, drawn_idx] : enumerate(roller_drawn_el_idx)) {
		if (drawn_idx >= 0) {
			cur_selected = i;
			highlight_component(drawn_idx);
			move_selected_control_foreground(drawn_elements, drawn_elements[drawn_idx]);
			break;
		}
	}
	lv_roller_set_selected(ui_ElementRoller, cur_selected, LV_ANIM_OFF);
}

// Return to the top-level list, with the group we just left selected
void ModuleViewPage::exit_group() {
	auto left_group = current_group;

	// The element we were on isn't in the top-level list
	unhighlight_component(cur_selected);

	current_group.reset();
	args.element_indices = std::nullopt;
	cur_selected = 0;
	populate_roller();

	if (!left_group)
		return;

	auto tag = group_row_tag(*left_group);
	for (auto [i, drawn_idx] : enumerate(roller_drawn_el_idx)) {
		if (drawn_idx == tag) {
			// populate_roller() highlighted the first row
			unhighlight_component(cur_selected);
			cur_selected = i;
			lv_roller_set_selected(ui_ElementRoller, cur_selected, LV_ANIM_OFF);
			highlight_row(cur_selected);
			break;
		}
	}
}

// The row to select when coming into the roller from the top (skip headers)
unsigned ModuleViewPage::first_selectable_row() const {
	if (!roller_drawn_el_idx.empty() && roller_drawn_el_idx[0] != RollerHeaderTag)
		return 0;
	return 1;
}

unsigned ModuleViewPage::default_row() const {
	for (auto [i, tag] : enumerate(roller_drawn_el_idx)) {
		if (tag >= 0 || is_group_tag(tag))
			return i;
	}
	return first_selectable_row();
}

std::optional<unsigned> ModuleViewPage::get_group_idx(unsigned roller_idx) const {
	if (roller_idx < roller_drawn_el_idx.size()) {
		auto tag = roller_drawn_el_idx[roller_idx];
		if (is_group_tag(tag) && group_from_tag(tag) < layout.group_members.size())
			return group_from_tag(tag);
	}
	return std::nullopt;
}

// Elements that are ever listed. While patching a cable, some of these are also
// filtered out (see is_listed), but groups and order are kept as they are.
bool ModuleViewPage::is_listable(unsigned drawn_idx) const {
	auto const &drawn_element = drawn_elements[drawn_idx];
	return base_element(drawn_element.element).short_name.size() > 0 && !ModView::is_light_only(drawn_element);
}

// Elements that are listed right now
bool ModuleViewPage::is_listed(unsigned drawn_idx) const {
	return is_listable(drawn_idx) &&
		   !ModView::should_skip_for_cable_mode(
			   gui_state.new_cable, drawn_elements[drawn_idx].gui_element, gui_state, patch, this_module_id);
}

std::optional<unsigned> ModuleViewPage::get_drawn_idx(unsigned roller_idx) {
	if (roller_idx < roller_drawn_el_idx.size()) {
		auto drawn_idx = roller_drawn_el_idx[roller_idx];
		if ((size_t)drawn_idx < drawn_elements.size()) {
			return drawn_idx;
		}
	}
	return std::nullopt;
}

} // namespace MetaModule
