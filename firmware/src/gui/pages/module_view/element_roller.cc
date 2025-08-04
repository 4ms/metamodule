#include "gui/pages/module_view/module_view.hh"
#include "gui/pages/module_view/roller_helpers.hh"

namespace MetaModule
{

void ModuleViewPage::show_roller() {
	metaparams.rotary_pushed.use_motion();
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

void ModuleViewPage::populate_roller() {
	size_t num_elements = moduleinfo.elements.size();
	opts.reserve(num_elements * 32); // estimate avg. 32 chars per roller item
	element_highlights.reserve(num_elements);

	// Populate Roller and element highlights
	unsigned roller_idx = 0;
	DrawnElement const *cur_el = nullptr;
	ElementCount::Counts last_type{};

	for (auto [drawn_el_idx, drawn_element] : enumerate(drawn_elements)) {
		auto &gui_el = drawn_element.gui_element;

		watch_element(drawn_element);

		add_element_highlight(gui_el.obj);

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
			roller_drawn_el_idx.push_back(RollerHeaderTag);
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
			roller_drawn_el_idx.push_back(RollerHeaderTag);
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

	/////////////////

	lv_show(ui_ElementRollerPanel);

	// Add text list to roller options
	lv_roller_set_options(ui_ElementRoller, opts.c_str(), LV_ROLLER_MODE_NORMAL);

	lv_roller_set_selected(ui_ElementRoller, cur_selected, LV_ANIM_OFF);

	if (cur_selected > 0 && cur_selected < element_highlights.size()) {
		if (auto idx = roller_drawn_el_idx[cur_selected]; (size_t)idx < element_highlights.size()) {
			if (lv_obj_get_height(element_highlights[idx]) > 100 || lv_obj_get_width(element_highlights[idx]) > 100) {
				lv_obj_add_style(element_highlights[idx], &Gui::panel_large_highlight_style, LV_PART_MAIN);
			} else {
				lv_obj_add_style(element_highlights[idx], &Gui::panel_highlight_style, LV_PART_MAIN);
			}
		}
	} else {
		pr_err("Current selected is not in range (%d/%zu)\n", cur_selected, element_highlights.size());
	}

	/////////

	if (cur_el && args.detail_mode == true) {
		mode = ViewMode::Mapping;
		mapping_pane.hide();
		mapping_pane.show(*cur_el);
	} else {
		show_roller();
	}
}

void ModuleViewPage::add_element_highlight(lv_obj_t *obj) {
	auto &b = element_highlights.emplace_back();
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

void ModuleViewPage::unhighlight_component(uint32_t prev_sel) {
	if (auto prev_idx = get_drawn_idx(prev_sel)) {
		lv_obj_remove_style(element_highlights[*prev_idx], &Gui::panel_bright_highlight_style, LV_PART_MAIN);
		if (lv_obj_get_height(element_highlights[*prev_idx]) > 100 ||
			lv_obj_get_width(element_highlights[*prev_idx]) > 100)
		{
			lv_obj_remove_style(element_highlights[*prev_idx], &Gui::panel_large_highlight_style, LV_PART_MAIN);
		} else {
			lv_obj_remove_style(element_highlights[*prev_idx], &Gui::panel_highlight_style, LV_PART_MAIN);
		}
		lv_obj_set_style_border_width(element_highlights[*prev_idx], 0, LV_PART_MAIN);
		lv_event_send(element_highlights[*prev_idx], LV_EVENT_REFRESH, nullptr);
	}
}

void ModuleViewPage::highlight_component(size_t idx) {
	if (idx < element_highlights.size()) {
		lv_obj_remove_style(element_highlights[idx], &Gui::panel_bright_highlight_style, LV_PART_MAIN);
		if (lv_obj_get_height(element_highlights[idx]) > 100 || lv_obj_get_width(element_highlights[idx]) > 100) {
			lv_obj_add_style(element_highlights[idx], &Gui::panel_large_highlight_style, LV_PART_MAIN);
		} else {
			lv_obj_add_style(element_highlights[idx], &Gui::panel_highlight_style, LV_PART_MAIN);
		}
		lv_obj_set_style_border_width(element_highlights[idx], 0, LV_PART_MAIN);
		lv_event_send(element_highlights[idx], LV_EVENT_REFRESH, nullptr);
		lv_obj_scroll_to_view(element_highlights[idx], LV_ANIM_ON);
	}
}

void ModuleViewPage::outline_component(size_t idx) {
	lv_obj_add_style(element_highlights[idx], &Gui::panel_bright_highlight_style, LV_PART_MAIN);
	lv_event_send(element_highlights[idx], LV_EVENT_REFRESH, nullptr);
	lv_obj_scroll_to_view(element_highlights[idx], LV_ANIM_ON);
}

void ModuleViewPage::unoutline_component(size_t idx) {
	lv_obj_remove_style(element_highlights[idx], &Gui::panel_bright_highlight_style, LV_PART_MAIN);
	lv_event_send(element_highlights[idx], LV_EVENT_REFRESH, nullptr);
	lv_obj_scroll_to_view(element_highlights[idx], LV_ANIM_ON);
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

	// Skip over headers by scrolling over them in the same direction we just scrolled
	if (cur_idx == RollerHeaderTag) {
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

	page->cur_selected = cur_sel;

	// Save current select in args so we can navigate back to this item
	page->args.element_indices = page->drawn_elements[cur_idx].gui_element.idx;

	if (page->get_drawn_idx(prev_sel) != cur_idx) {
		page->unhighlight_component(prev_sel);
		page->highlight_component(cur_idx);
	}

	page->roller_hover.hide();
}

void ModuleViewPage::focus_button_bar() {
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
		if (auto drawn_idx = get_drawn_idx(cur_selected)) {
			outline_component(*drawn_idx);
		}
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

		} else if (page->full_screen_mode && !std::get_if<JackInput>(&drawn_element.element) &&
				   !std::get_if<JackOutput>(&drawn_element.element))
		{
			// Allow immediate manual control in full-screen mode (popup is hidden but still works)
			page->manual_control_popup(drawn_element);

		} else {
			page->click_normal_element(drawn_element);
		}

		//Not an element: Is it the Context Menu?
	} else if (roller_idx < page->roller_drawn_el_idx.size()) {
		if (page->roller_drawn_el_idx[roller_idx] == ContextMenuTag) {
			page->show_context_menu();
		}
	}
}

void ModuleViewPage::roller_focus_cb(lv_event_t *event) {
	auto page = static_cast<ModuleViewPage *>(event->user_data);
	if (page) {
		if (event->code == LV_EVENT_PRESSED) {
			auto roller = (lv_roller_t *)ui_ElementRoller;
			roller->sel_opt_id_ori = roller->sel_opt_id;
		} else {
			if (page->roller_drawn_el_idx.size() <= 1) {
				page->focus_button_bar();
				page->roller_hover.hide();
				return;
			}

			// Change to "edit" mode if not already editting
			if (lv_group_get_editing(page->group) == false) {
				// Must send a PRESS event to enter "edit" mode
				lv_event_send(ui_ElementRoller, LV_EVENT_PRESSED, nullptr);
				// This sends another FOCUSED event:
				lv_group_set_editing(page->group, true);
			}

			if (auto drawn_idx = page->get_drawn_idx(page->cur_selected)) {
				page->highlight_component(*drawn_idx);
			}
		}
	}
}

void ModuleViewPage::jump_to_roller_cb(lv_event_t *event) {
	if (!event || !event->user_data)
		return;
	auto page = static_cast<ModuleViewPage *>(event->user_data);
	if (page->full_screen_mode) {
		lv_group_focus_obj(ui_ElementRoller);
	}
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
