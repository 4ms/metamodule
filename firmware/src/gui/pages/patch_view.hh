#pragma once
#include "CoreModules/elements/element_counter.hh"
#include "gui/dyn_display.hh"
#include "gui/elements/map_ring_animate.hh"
#include "gui/elements/module_drawer.hh"
#include "gui/elements/redraw.hh"
#include "gui/elements/redraw_display.hh"
#include "gui/elements/redraw_light.hh"
#include "gui/helpers/load_meter.hh"
#include "gui/helpers/lv_helpers.hh"
#include "gui/pages/base.hh"
#include "gui/pages/cable_drawer.hh"
#include "gui/pages/description_panel.hh"
#include "gui/pages/make_cable.hh"
#include "gui/pages/page_list.hh"
#include "gui/pages/patch_view_file_menu.hh"
#include "gui/pages/patch_view_settings_menu.hh"
#include "gui/styles.hh"
#include "pr_dbg.hh"
#include "util/countzip.hh"

namespace MetaModule
{

struct PatchViewPage : PageBase {
	PatchViewPage(PatchContext info, FileSaveDialog &file_save_dialog)
		: PageBase{info, PageId::PatchView}
		, base(ui_PatchViewPage)
		, modules_cont(ui_ModulesPanel)
		, cable_drawer{modules_cont, drawn_elements}
		, page_settings{settings.patch_view}
		, settings_menu{settings.patch_view, gui_state}
		, file_menu{patch_playloader, patch_storage, patches, file_save_dialog, notify_queue, page_list, gui_state}
		, map_ring_display{settings.patch_view} {

		init_bg(base);
		lv_group_set_editing(group, false);

		lv_obj_add_event_cb(ui_PlayButton, playbut_cb, LV_EVENT_CLICKED, this);
		lv_obj_add_event_cb(ui_AddButton, add_module_cb, LV_EVENT_CLICKED, this);
		lv_obj_add_event_cb(ui_KnobButton, knob_button_cb, LV_EVENT_CLICKED, this);
		lv_obj_add_event_cb(ui_InfoButton, desc_open_cb, LV_EVENT_CLICKED, this);

		// Scroll to top when focussing on a button
		lv_obj_add_event_cb(ui_PlayButton, button_focussed_cb, LV_EVENT_FOCUSED, this);
		lv_obj_add_event_cb(ui_SaveButton, button_focussed_cb, LV_EVENT_FOCUSED, this);
		lv_obj_add_event_cb(ui_InfoButton, button_focussed_cb, LV_EVENT_FOCUSED, this);
		lv_obj_add_event_cb(ui_KnobButton, button_focussed_cb, LV_EVENT_FOCUSED, this);
		lv_obj_add_event_cb(ui_SettingsButton, button_focussed_cb, LV_EVENT_FOCUSED, this);
		lv_obj_add_event_cb(ui_AddButton, button_focussed_cb, LV_EVENT_FOCUSED, this);

		lv_obj_add_event_cb(ui_PatchViewPage, scroll_end_cb, LV_EVENT_SCROLL, this);

		desc_panel.hide();

		lv_label_set_text(ui_ModuleName, "");
		lv_hide(ui_ModuleName);
	}

	void prepare_focus() override {

		is_ready = false;

		if (args.patch_loc_hash.value_or(PatchLocHash{}) == PatchLocHash{}) {
			pr_err("Error: Tried to load PatchView with no patch\n");
			return;
		}

		is_patch_playloaded = patch_is_playing(args.patch_loc_hash);

		if (is_patch_playloaded && !patch_playloader.is_audio_muted()) {
			lv_label_set_text_fmt(ui_LoadMeter2, "%d%%", metaparams.audio_load);
			lv_show(ui_LoadMeter2);
			lv_obj_add_state(ui_PlayButton, LV_STATE_USER_2);
		} else {
			lv_label_set_text(ui_LoadMeter2, "");
			lv_hide(ui_LoadMeter2);
			lv_obj_clear_state(ui_PlayButton, LV_STATE_USER_2);
		}

		bool needs_refresh = false;

		if (gui_state.force_redraw_patch)
			needs_refresh = true;
		if (patch_revision != patches.get_view_patch_modification_count())
			needs_refresh = true;
		if (displayed_patch_loc_hash != args.patch_loc_hash)
			needs_refresh = true;

		file_change_poll.force_next_poll(); // avoid 500ms delay before refreshing the patch
		poll_patch_file_changed();

		if (patch_file_timestamp != patches.get_view_patch_timestamp()) {
			needs_refresh = true;
		}

		if (!needs_refresh) {
			is_ready = true;
			watch_modules();
			update_map_ring_style();
			prepare_dynamic_elements();

			if (args.module_id) {
				auto canvas = std::ranges::find_if(module_canvases, [module_id = args.module_id](lv_obj_t *canv) {
					return module_id == *(static_cast<uint32_t *>(lv_obj_get_user_data(canv)));
				});
				if (canvas != module_canvases.end()) {
					lv_obj_scroll_to_view_recursive(*canvas, LV_ANIM_ON);
				}
			}
			return;
		}

		gui_state.force_redraw_patch = false;

		// Prepare the knobset menu with the actively playing patch's knobset
		if (is_patch_playloaded)
			active_knobset = page_list.get_active_knobset();

		else {
			// Reset to first knobset when we view a different patch than previously viewed
			if (displayed_patch_loc_hash != args.patch_loc_hash) {
				args.view_knobset_id = 0;
			}
			active_knobset = args.view_knobset_id.value_or(0);
		}

		if (args.patch_loc_hash)
			displayed_patch_loc_hash = args.patch_loc_hash.value();

		patch_revision = patches.get_view_patch_modification_count();

		redraw_patch();
		prepare_dynamic_elements();
	}

	void redraw_patch() {
		lv_group_remove_all_objs(group);
		lv_group_set_editing(group, false);

		clear();

		lv_hide(modules_cont);

		patch = patches.get_view_patch();

		if (!patch) {
			pr_err("view patch is null\n");
			return;
		}

		if (patch->patch_name.length() == 0)
			return;

		lv_label_set_text(ui_PatchName, patch->patch_name.c_str());

		module_canvases.reserve(patch->module_slugs.size());
		module_ids.reserve(patch->module_slugs.size());

		lv_group_add_obj(group, ui_PlayButton);
		lv_group_add_obj(group, ui_InfoButton);
		lv_group_add_obj(group, ui_KnobButton);
		lv_group_add_obj(group, ui_AddButton);
		lv_group_add_obj(group, ui_SaveButton);
		lv_group_add_obj(group, ui_SettingsButton);

		lv_show(modules_cont);

		auto module_drawer = ModuleDrawer{modules_cont, page_settings.view_height_px};

		auto canvas_buf = std::span<lv_color_t>{page_pixel_buffer};
		int bottom = 0;
		lv_obj_t *initial_selected_module = nullptr;

		unsigned modules_skipped_for_size = 0;
		std::string modules_skipped_slugs;

		for (auto [module_idx, slug] : enumerate(patch->module_slugs)) {
			module_ids.push_back(module_idx);

			auto [faceplate, width] = module_drawer.read_faceplate(slug);
			if (faceplate.size() == 0 || width == 0)
				continue; // file not found or corrupted, ignore this

			if ((width * page_settings.view_height_px) > canvas_buf.size()) {
				modules_skipped_for_size++;
				if (modules_skipped_for_size < 6) {
					modules_skipped_slugs.append(slug.c_str());
					modules_skipped_slugs.append(", ");
				} else if (modules_skipped_for_size == 6) {
					modules_skipped_slugs.append("and others ");
				}
				continue;
			}

			auto canvas = module_drawer.draw_faceplate(faceplate, width, canvas_buf);
			if (!canvas)
				continue;

			module_drawer.draw_mapped_elements(
				*patch, module_idx, active_knobset, canvas, drawn_elements, is_patch_playloaded);

			// Increment the buffer
			lv_obj_refr_size(canvas);
			canvas_buf = canvas_buf.subspan(lv_obj_get_width(canvas) * page_settings.view_height_px);
			int this_bottom = lv_obj_get_y(canvas) + lv_obj_get_height(canvas);
			bottom = std::max(bottom, this_bottom);

			module_canvases.push_back(canvas);
			style_module(canvas);

			// Give the callback access to the module_idx:
			lv_obj_set_user_data(canvas, (void *)(&module_ids[module_ids.size() - 1]));
			lv_obj_add_event_cb(canvas, module_click_cb, LV_EVENT_CLICKED, (void *)this);
			lv_obj_add_event_cb(canvas, module_focus_cb, LV_EVENT_FOCUSED, (void *)this);
			lv_obj_add_flag(canvas, LV_OBJ_FLAG_SCROLL_ON_FOCUS);
			if (args.module_id.has_value()) {
				if (args.module_id.value() == module_idx) {
					initial_selected_module = canvas;
				}
			}
		}

		if (modules_skipped_for_size) {
			std::string msg = "Not displaying: " + modules_skipped_slugs + "because graphics buffer is full";
			notify_queue.put({msg, Notification::Priority::Info, 4000});
		}

		is_ready = true;

		watch_modules();

		highlighted_module_id = std::nullopt;
		highlighted_module_obj = nullptr;
		update_map_ring_style();

		cable_drawer.set_height(bottom + 30);
		update_cable_style(true);

		settings_menu.prepare_focus(group);
		file_menu.prepare_focus(group);

		patch = patches.get_view_patch();
		desc_panel.prepare_focus(group);

		if (initial_selected_module) {
			lv_obj_refr_size(base);
			lv_obj_refr_pos(base);
			lv_group_focus_obj(initial_selected_module);
			lv_obj_scroll_to_view_recursive(initial_selected_module, LV_ANIM_OFF);
		} else {
			lv_obj_scroll_to_y(base, 0, LV_ANIM_OFF);
		}

		dyn_module_idx = 0;
	}

	void redraw_map_rings() {
		for (auto &drawn_el : drawn_elements) {
			auto &gui_el = drawn_el.gui_element;

			if (gui_el.count.num_params > 0 && gui_el.map_ring) {
				lv_obj_del(gui_el.map_ring);
				gui_el.map_ring = nullptr;
			}
		}

		for (auto &drawn_el : drawn_elements) {
			auto knobset = active_knobset;
			auto module_id = drawn_el.gui_element.module_idx;
			auto canvas = lv_obj_get_parent(drawn_el.gui_element.obj);

			ModuleDrawer{modules_cont, page_settings.view_height_px}.draw_mapped_ring(
				*patch, module_id, knobset, canvas, drawn_el);
		}
		update_map_ring_style();
	}

	void blur() override {
		settings_menu.hide();
		desc_panel.hide();
		file_menu.hide();
		params.text_displays.stop_watching_all();

		pr_dbg("PatchView::blur()\n");
		dyn_draws.clear();

		dynamic_elements_prepared = false;
	}

	void update() override {
		bool last_is_patch_playloaded = is_patch_playloaded;

		lv_show(ui_SaveButtonRedDot, patches.get_view_patch_modification_count() > 0);

		patch = patches.get_view_patch();

		is_patch_playloaded = patch_is_playing(displayed_patch_loc_hash);

		if (is_patch_playloaded != last_is_patch_playloaded || page_settings.changed) {
			page_settings.changed = false;
			update_map_ring_style();
			update_cable_style();
			watch_modules();
		}

		if (is_patch_playloaded != last_is_patch_playloaded) {
			args.view_knobset_id = active_knobset;
			page_list.set_active_knobset(active_knobset);
			patch_mod_queue.put(ChangeKnobSet{active_knobset});
			redraw_map_rings();
		}

		if (is_patch_playloaded && active_knobset != page_list.get_active_knobset()) {
			args.view_knobset_id = page_list.get_active_knobset();
			active_knobset = page_list.get_active_knobset();
			redraw_map_rings();
		}

		if (gui_state.view_patch_file_changed) {
			gui_state.view_patch_file_changed = false;

			abort_cable(gui_state, notify_queue);

			if (auto obj = lv_group_get_focused(group)) {
				if (std::ranges::find(module_canvases, obj) != module_canvases.end()) {
					if (auto user_data = lv_obj_get_user_data(obj)) {
						args.module_id = *(static_cast<uint32_t *>(user_data));
					}
				}
			}
			redraw_patch();
		}

		if (gui_state.back_button.is_just_released()) {
			if (settings_menu.is_visible()) {
				settings_menu.hide();

			} else if (desc_panel.is_visible()) {
				desc_panel.back_event();

			} else if (file_menu.is_visible()) {
				file_menu.back();

			} else if (gui_state.new_cable) {
				abort_cable(gui_state, notify_queue);

			} else if (highlighted_module_id.has_value() && highlighted_module_obj != nullptr) {
				lv_group_focus_obj(ui_PlayButton);

			} else {
				page_list.request_new_page_no_history(PageId::MainMenu, args);
				// blur();
			}
		}

		if (desc_panel.did_update_names()) {
			patches.mark_view_patch_modified();
			lv_label_set_text(ui_PatchName, patch->patch_name.c_str());
		}

		if (file_menu.did_filesystem_change()) {
			displayed_patch_loc_hash = patches.get_view_patch_loc_hash();
			args.patch_loc_hash = patches.get_view_patch_loc_hash();
			lv_label_set_text(ui_PatchName, patches.get_view_patch_filename().data());
		}

		if (is_patch_playloaded && !patch_playloader.is_audio_muted()) {
			redraw_elements();

			lv_obj_set_style_border_width(ui_PlayButton, 0, LV_PART_MAIN);

			if (!lv_obj_has_state(ui_PlayButton, LV_STATE_USER_2)) {
				lv_obj_add_state(ui_PlayButton, LV_STATE_USER_2);
			}

			update_load_text(metaparams, ui_LoadMeter2);

			prepare_dynamic_elements();

			draw_dynamic_elements();

		} else {
			if (lv_obj_has_state(ui_PlayButton, LV_STATE_USER_2)) {
				lv_hide(ui_LoadMeter2);
				lv_obj_clear_state(ui_PlayButton, LV_STATE_USER_2);
			}
		}

		file_menu.update();

		// Don't poll for patch changes while file menu is open to prevent races on the filesystem.
		if (!file_menu.is_visible())
			poll_patch_file_changed();
	}

private:
	void prepare_dynamic_elements() {

		if (dynamic_elements_prepared)
			return;

		if (!is_patch_playloaded || patch_playloader.is_audio_muted())
			return;

		for (auto &canvas : module_canvases) {
			if (!canvas)
				continue;

			auto user_data = lv_obj_get_user_data(canvas);
			if (!user_data)
				continue;

			auto module_idx = *(static_cast<uint32_t *>(user_data));
			if (module_idx >= patch->module_slugs.size())
				continue;

			auto slug = patch->module_slugs[module_idx];

			auto &dyn = dyn_draws.emplace_back(patch_playloader);
			if (!dyn.prepare_module(slug, module_idx, canvas, page_settings.view_height_px)) {
				pr_dbg("Failed to create dyn draw, removing from PatchView dyn draw vector\n");
				dyn_draws.pop_back();
			}
		}

		dynamic_elements_prepared = true;
	}

	void draw_dynamic_elements() {
		if (dyn_draws.size() == 0)
			return;

		if (++dyn_frame_throttle_ctr >= DynFrameThrottle) {
			dyn_frame_throttle_ctr = 0;

			dyn_module_idx++;
			if (dyn_module_idx >= dyn_draws.size())
				dyn_module_idx = 0;

			dyn_draws[dyn_module_idx].draw();
		}
	}

	void watch_modules() {
		params.text_displays.stop_watching_all();

		if (is_patch_playloaded) {
			for (const auto &drawn_element : drawn_elements) {
				auto &gui_el = drawn_element.gui_element;

				std::visit(overloaded{
							   [](auto const &el) {},
							   [&](DynamicTextDisplay const &el) {
								   params.text_displays.start_watching_display(gui_el.module_idx, gui_el.idx.light_idx);
							   },
						   },
						   drawn_element.element);
			}
		}
	}

	void redraw_elements() {
		// Redraw all elements that have changed state (knobs, lights, etc)
		auto is_visible = [](lv_coord_t pos) {
			auto visible_top = lv_obj_get_scroll_y(ui_PatchViewPage);
			auto visible_bot = visible_top + 240;
			return pos >= visible_top && pos < visible_bot;
		};

		for (auto &drawn_el : drawn_elements) {
			if (!drawn_el.gui_element.obj)
				continue;

			auto module_top_to_obj = lv_obj_get_y(drawn_el.gui_element.obj);
			auto panel_top_to_module_top = lv_obj_get_y(lv_obj_get_parent(drawn_el.gui_element.obj));
			auto panel_top_pos = lv_obj_get_y(ui_ModulesPanel);
			auto ypos = module_top_to_obj + panel_top_to_module_top + panel_top_pos;
			auto y2pos = ypos + lv_obj_get_height(drawn_el.gui_element.obj);

			if (!is_visible(ypos) && !is_visible(y2pos))
				continue;

			auto &gui_el = drawn_el.gui_element;

			if (drawn_el.gui_element.count.num_params > 0) {
				auto value =
					patch_playloader.param_value(drawn_el.gui_element.module_idx, drawn_el.gui_element.idx.param_idx);
				auto was_redrawn = redraw_param(drawn_el, value);

				if (was_redrawn) {
					if (page_settings.map_ring_flash_active)
						map_ring_display.flash_once(gui_el.map_ring, highlighted_module_id == gui_el.module_idx);

					if (page_settings.scroll_to_active_param) {
						lv_obj_scroll_to_view_recursive(gui_el.obj, LV_ANIM_ON);
					}
				}
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

			redraw_text_display(drawn_el, gui_el.module_idx, params.text_displays.watch_displays);
		}
	}

	void update_map_ring_style() {
		if (!is_ready) {
			return;
		}

		for (auto &drawn_el : drawn_elements) {
			bool is_on_highlighted_module = (drawn_el.gui_element.module_idx == highlighted_module_id);
			map_ring_display.update(drawn_el, is_on_highlighted_module, is_patch_playloaded);
		}
	}

	void update_cable_style(bool force = false) {
		static MapRingStyle last_cable_style;

		cable_drawer.set_opacity(page_settings.cable_style.opa);

		if (force || page_settings.cable_style.mode != last_cable_style.mode) {
			if (page_settings.cable_style.mode == MapRingStyle::Mode::ShowAll)
				cable_drawer.draw(*patch);
			else
				cable_drawer.clear();
		}
		last_cable_style = page_settings.cable_style;
	}

	void redraw_modulename() {
		auto module_id = highlighted_module_id.value_or(0xFFFFFFFF);
		if (module_id >= patch->module_slugs.size())
			return;

		if (highlighted_module_obj == nullptr)
			return;

		lv_show(ui_ModuleName);

		auto module_y = lv_obj_get_y(highlighted_module_obj);
		auto scroll_y = lv_obj_get_scroll_top(ui_PatchViewPage);
		auto header_y = lv_obj_get_y(ui_ModulesPanel);
		int16_t module_top_on_screen = header_y - scroll_y + module_y;
		int16_t module_bot_on_screen = module_top_on_screen + page_settings.view_height_px;
		int16_t space_above = module_top_on_screen;
		int16_t space_below = 240 - module_bot_on_screen;
		if (space_below > space_above) {
			lv_obj_set_y(ui_ModuleName, module_bot_on_screen - 120 + 16);
		} else {
			lv_obj_set_y(ui_ModuleName, module_top_on_screen - 120 - 9);
		}
	}

	void clear() {
		for (auto &m : module_canvases) {
			if (m)
				lv_obj_del(m);
			m = nullptr;
		}
		highlighted_module_obj = nullptr;
		highlighted_module_id = std::nullopt;

		module_canvases.clear();
		drawn_elements.clear();
		module_ids.clear();
	}

	void style_module(lv_obj_t *canvas) {
		lv_group_add_obj(group, canvas);
		lv_obj_add_flag(canvas, LV_OBJ_FLAG_SNAPPABLE);

		lv_obj_add_style(canvas, &Gui::plain_border_style, LV_STATE_DEFAULT);
		lv_obj_add_style(canvas, &Gui::selected_module_style, LV_STATE_FOCUS_KEY);
		lv_obj_add_flag(canvas, LV_OBJ_FLAG_CLICKABLE | LV_OBJ_FLAG_SCROLL_ON_FOCUS);
		lv_obj_clear_flag(canvas, LV_OBJ_FLAG_SCROLLABLE);
	}

	static void module_click_cb(lv_event_t *event) {
		auto page = static_cast<PatchViewPage *>(event->user_data);
		if (!page)
			return;

		auto obj = event->current_target;
		if (!obj)
			return;
		page->args.module_id = *(static_cast<uint32_t *>(lv_obj_get_user_data(obj)));
		page->args.element_indices = {};
		page->args.detail_mode = false;
		page->page_list.update_state(PageId::PatchView, page->args);
		page->page_list.request_new_page(PageId::ModuleView, page->args);
	}

	static void module_focus_cb(lv_event_t *event) {
		auto page = static_cast<PatchViewPage *>(event->user_data);
		if (!page)
			return;

		auto this_module_obj = lv_group_get_focused(page->group);
		if (!this_module_obj)
			return;

		auto user_data = lv_obj_get_user_data(this_module_obj);
		if (!user_data) {
			return;
		}

		uint32_t module_id = *(static_cast<uint32_t *>(user_data));
		if (module_id >= page->patch->module_slugs.size())
			return;

		page->highlighted_module_id = module_id;
		page->highlighted_module_obj = this_module_obj;

		const auto this_slug = page->patch->module_slugs[module_id];
		if (auto display_name = ModuleFactory::getModuleDisplayName(this_slug); display_name.length()) {
			lv_label_set_text(ui_ModuleName, display_name.data());
		} else {
			lv_label_set_text(ui_ModuleName, "");
		}

		auto module_x = lv_obj_get_x(page->highlighted_module_obj);
		lv_obj_set_x(ui_ModuleName, module_x);

		page->redraw_modulename();

		page->update_map_ring_style();
	}

	static void scroll_end_cb(lv_event_t *event) {
		auto page = static_cast<PatchViewPage *>(event->user_data);
		page->redraw_modulename();
	}

	void save_last_opened_patch_in_settings() {
		if (settings.last_patch_vol != patches.get_view_patch_vol() ||
			settings.last_patch_opened != patches.get_view_patch_filename())
		{
			settings.last_patch_vol = patches.get_view_patch_vol();
			settings.last_patch_opened = patches.get_view_patch_filename();
			pr_info("Will set last_patch opened to %s on %d\n",
					settings.last_patch_opened.c_str(),
					settings.last_patch_vol);

			if (gui_state.write_settings_after_ms == 0) {
				gui_state.write_settings_after_ms = get_time() + 60 * 1000; //1 minute delay
				pr_info("Setting timer...\n");
			}
		}
	}

	static void playbut_cb(lv_event_t *event) {
		auto page = static_cast<PatchViewPage *>(event->user_data);
		if (!page->is_patch_playloaded) {
			page->patch_playloader.request_load_view_patch();
			page->save_last_opened_patch_in_settings();
			page->gui_state.playing_patch_needs_manual_reload = false;

		} else {
			if (page->patch_playloader.is_audio_muted()) {
				if (page->gui_state.playing_patch_needs_manual_reload) {
					page->patch_playloader.request_load_view_patch();
					page->gui_state.playing_patch_needs_manual_reload = false;
				} else {
					page->patch_playloader.start_audio();
				}
			} else {
				page->patch_playloader.stop_audio();
			}
		}
	}

	static void button_focussed_cb(lv_event_t *event) {
		auto page = static_cast<PatchViewPage *>(event->user_data);
		if (!page)
			return;
		lv_label_set_text(ui_ModuleName, "");
		lv_hide(ui_ModuleName);
		lv_obj_scroll_to_y(page->base, 0, LV_ANIM_ON);
		page->highlighted_module_id = std::nullopt;
		page->update_map_ring_style();
		page->settings_menu.hide();
		page->file_menu.hide();

		if (event->target == ui_SaveButton) {
			lv_label_set_text(ui_PatchName, page->patches.get_view_patch_filename().c_str());
		} else {
			lv_label_set_text(ui_PatchName, page->patch->patch_name.c_str());
		}
	}

	static void add_module_cb(lv_event_t *event) {
		auto page = static_cast<PatchViewPage *>(event->user_data);
		if (!page)
			return;
		abort_cable(page->gui_state, page->notify_queue);
		page->load_page(PageId::ModuleList, page->args);
	}

	static void knob_button_cb(lv_event_t *event) {
		if (!event || !event->user_data)
			return;
		auto page = static_cast<PatchViewPage *>(event->user_data);

		abort_cable(page->gui_state, page->notify_queue);
		page->load_page(PageId::KnobSetView,
						{.patch_loc_hash = page->args.patch_loc_hash, .view_knobset_id = page->active_knobset});
	}

	static void desc_open_cb(lv_event_t *event) {
		auto page = static_cast<PatchViewPage *>(event->user_data);
		abort_cable(page->gui_state, page->notify_queue);
		page->show_desc_panel();
	}

	void show_desc_panel() {
		desc_panel.set_patch(patch);
		desc_panel.set_filename(patches.get_view_patch_filename());
		desc_panel.show();
	}

private:
	lv_obj_t *base;
	lv_obj_t *modules_cont;
	CableDrawer<MaxBufferHeight> cable_drawer;

	ModuleDisplaySettings &page_settings;
	PatchViewSettingsMenu settings_menu;

	unsigned active_knobset = 0;

	PatchDescriptionPanel desc_panel;

	PatchViewFileMenu file_menu;

	MapRingDisplay map_ring_display;

	std::optional<uint32_t> highlighted_module_id{};
	lv_obj_t *highlighted_module_obj = nullptr;

	PatchData *patch = patches.get_view_patch();

	std::vector<lv_obj_t *> module_canvases;
	std::vector<uint32_t> module_ids;
	std::vector<DrawnElement> drawn_elements;
	bool is_patch_playloaded = false; //loaded into the player: might be paused or playing
	bool is_ready = false;

	PatchLocHash displayed_patch_loc_hash;
	uint32_t patch_revision = 0xFFFFFFFF;
	uint32_t patch_file_timestamp = 0;

	struct focussed_context {
		PatchViewPage *page;
		uint32_t selected_module_id;
	};

	// std::vector<std::vector<float>> light_vals;

	std::vector<DynamicDisplay> dyn_draws;
	unsigned dyn_frame_throttle_ctr = 1;
	unsigned dyn_module_idx = 0;
	constexpr static unsigned DynFrameThrottle = 2;
	bool dynamic_elements_prepared = false;
};

} // namespace MetaModule
