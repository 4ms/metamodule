#pragma once
#include "CoreModules/elements/element_info.hh"
#include "gui/elements/element_name.hh"
#include "gui/elements/map_ring_animate.hh"
#include "gui/elements/module_drawer.hh"
#include "gui/elements/module_param.hh"
#include "gui/elements/redraw_light.hh"
#include "gui/elements/update.hh"
#include "gui/images/faceplate_images.hh"
#include "gui/pages/base.hh"
#include "gui/pages/module_view_mapping_pane.hh"
#include "gui/pages/page_list.hh"
#include "gui/slsexport/meta5/ui.h"
#include "gui/styles.hh"

namespace MetaModule
{
struct ModuleViewPage : PageBase {

	ViewSettings settings;

	ModuleViewPage(PatchInfo info)
		: PageBase{info, PageId::ModuleView}
		, map_ring_display{settings}
		, patch{patch_storage.get_view_patch()}
		, roller{ui_ElementRoller}
		, mapping_pane{info.patch_storage, module_mods, params, args, page_list} {

		init_bg(ui_MappingMenu);

		lv_draw_img_dsc_init(&img_dsc);

		lv_obj_remove_style(roller, nullptr, LV_STATE_EDITED);
		lv_obj_remove_style(roller, nullptr, LV_STATE_FOCUS_KEY);

		lv_obj_add_flag(ui_MappingParameters, LV_OBJ_FLAG_HIDDEN);

		button.clear();
		module_controls.clear();
		mapping_pane.init();

		lv_group_remove_all_objs(group);
		lv_group_add_obj(group, roller);
		lv_group_focus_obj(roller);

		lv_obj_add_event_cb(roller, roller_cb, LV_EVENT_KEY, this);
		lv_obj_add_event_cb(roller, roller_click_cb, LV_EVENT_CLICKED, this);
	}

	void prepare_focus() override {
		patch = patch_storage.get_view_patch();

		is_patch_playing = patch_is_playing(args.patch_loc_hash);

		this_module_id = args.module_id.value_or(this_module_id);

		if (!read_slug()) {
			msg_queue.append_message("Module View page cannot read module slug.\n");
			return;
		}

		moduleinfo = ModuleFactory::getModuleInfo(slug);
		if (moduleinfo.width_hp == 0) {
			msg_queue.append_message("Module View page got empty module info.\r\n");
			return;
		}

		lv_label_set_text(ui_ElementRollerModuleName, slug.data());

		redraw_module();
	}

	void redraw_module() {
		reset_module_page();

		size_t num_elements = moduleinfo.elements.size();
		opts.reserve(num_elements * 32); // 32 chars per roller item
		button.reserve(num_elements);
		drawn_elements.reserve(num_elements);
		module_controls.reserve(num_elements);

		auto module_drawer = ModuleDrawer{ui_ModuleImage, 240};
		canvas = module_drawer.draw_faceplate(slug, buffer);

		lv_obj_refr_size(canvas);
		auto width_px = lv_obj_get_width(canvas);
		//module img + padding is no more than 190px wide
		auto display_widthpx = std::min<lv_coord_t>(width_px + 4, 190);
		lv_obj_set_width(ui_ModuleImage, display_widthpx);
		lv_obj_refr_size(ui_ModuleImage);

		active_knob_set = page_list.get_active_knobset();

		module_drawer.draw_mapped_elements(
			patch, this_module_id, active_knob_set, canvas, drawn_elements, is_patch_playing);

		lv_obj_update_layout(canvas);

		// Populate Roller and highlighter buttons
		unsigned roller_idx = 0;
		DrawnElement const *cur_el = nullptr;

		for (const auto &drawn_element : drawn_elements) {
			auto &drawn = drawn_element.gui_element;

			for (unsigned i = 0; i < drawn.count.num_lights; i++) {
				params.lights.start_watching_light(this_module_id, drawn.idx.light_idx + i);
			}

			if (!drawn.obj)
				continue;

			std::visit(
				[this, drawn = drawn](auto &el) {
					opts += el.short_name;

					if (drawn.mapped_panel_id)
						opts = opts + " [" + get_panel_name<PanelDef>(el, drawn.mapped_panel_id.value()) + ']';

					append_connected_jack_name(opts, drawn, patch);

					opts += "\n";
					add_button(drawn.obj);
				},
				drawn_element.element);

			module_controls.emplace_back(drawn_element.element, drawn_element.gui_element.idx);

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
		lv_roller_set_options(roller, opts.c_str(), LV_ROLLER_MODE_NORMAL);
		lv_roller_set_visible_row_count(roller, 10);

		lv_roller_set_selected(roller, cur_selected, LV_ANIM_OFF);

		if (button.size() > 0) {
			lv_obj_add_style(button[cur_selected], &Gui::panel_highlight_style, LV_PART_MAIN);
		}

		update_map_ring_style();

		mapping_pane.prepare_focus(group, roller_width, is_patch_playing);

		if (cur_el) {
			mode = ViewMode::Mapping;
			mapping_pane.hide();
			mapping_pane.show(*cur_el);
		} else {
			mode = ViewMode::List;
			show_roller();
		}
	}

	void update() override {
		if (metaparams.meta_buttons[0].is_just_released()) {
			if (mapping_pane.manual_control_visible()) {
				mapping_pane.hide_manual_control();

			} else if (mode == ViewMode::List) {
				load_prev_page();

			} else if (mapping_pane.addmap_visible()) {
				mapping_pane.hide_addmap();

			} else {
				mode = ViewMode::List;
				show_roller();
			}
		}

		if (mode == ViewMode::Mapping)
			mapping_pane.update();

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

				auto did_move = std::visit(UpdateElement{params, patch, gui_el}, drawn_el.element);

				if (did_move && settings.map_ring_flash_active) {
					map_ring_display.flash_once(gui_el.map_ring, true);
				}

				update_light(drawn_el, light_vals);
			}
		}

		if (auto patch_mod = module_mods.get(); patch_mod.has_value()) {
			page_list.increment_patch_revision();

			// Apply to this thread's copy of patch
			std::visit(overloaded{
						   [this](AddMapping &mod) { apply_add_mapping(mod); },
						   [this](AddMidiMap &mod) { apply_add_midi_map(mod); },
						   [](auto &m) {},
					   },
					   patch_mod.value());

			// Forward the mod to the audio/patch_player queue
			if (is_patch_playing)
				patch_mod_queue.put(patch_mod.value());
		}
	}

	void apply_add_mapping(AddMapping &mod) {
		if (patch.add_update_mapped_knob(mod.set_id, mod.map)) {
			redraw_module();
			mapping_pane.refresh();
		}
	}

	void apply_add_midi_map(AddMidiMap &mod) {
		if (patch.add_update_midi_map(mod.map)) {
			redraw_module();
			mapping_pane.refresh();
		}
	}

	// This gets called after map_ring_style changes
	void update_map_ring_style() {
		for (auto &drawn_el : drawn_elements) {
			map_ring_display.update(drawn_el, true, is_patch_playing);
		}
	}

	void blur() final {
		params.lights.stop_watching_all();
	}

private:
	void show_roller() {
		mapping_pane.hide();
		lv_show(ui_ElementRollerPanel);
		lv_obj_set_height(roller, 210);
		lv_group_focus_obj(roller);
		lv_group_set_editing(group, true);
	}

	void add_button(lv_obj_t *obj) {
		auto &b = button.emplace_back();
		b = lv_btn_create(ui_ModuleImage);
		lv_obj_add_style(b, &Gui::invisible_style, LV_PART_MAIN);

		float width = lv_obj_get_width(obj);
		float height = lv_obj_get_height(obj);
		float c_x = (float)lv_obj_get_x(obj) + width / 2.f;
		float c_y = (float)lv_obj_get_y(obj) + height / 2.f;

		auto x_padding = std::min(width * 0.75f, 12.f);
		auto y_padding = std::min(height * 0.75f, 12.f);
		auto x_size = x_padding + width;
		auto y_size = y_padding + height;
		lv_obj_set_pos(b, std::round(c_x - x_size / 2.f), std::round(c_y - y_size / 2.f));
		lv_obj_set_size(b, std::round(x_size), std::round(y_size));
		lv_obj_add_flag(b, LV_OBJ_FLAG_SCROLL_ON_FOCUS);
	}

	void reset_module_page() {
		for (auto &b : button)
			lv_obj_del(b);

		if (canvas)
			lv_obj_del(canvas);

		button.clear();
		drawn_elements.clear();
		module_controls.clear();
		opts.clear();
		cur_selected = 0;
	}

	bool read_slug() {
		if (!args.module_id)
			return false;
		auto module_id = args.module_id.value();

		if (module_id >= patch.module_slugs.size())
			return false;

		slug = patch.module_slugs[module_id];
		return true;
	}

	static void roller_cb(lv_event_t *event) {
		auto page = static_cast<ModuleViewPage *>(event->user_data);
		auto &cur_sel = page->cur_selected;
		auto &but = page->button;

		// Turn off old button
		if (cur_sel >= 0) {
			lv_obj_remove_style(but[cur_sel], &Gui::panel_highlight_style, LV_PART_MAIN);
			lv_event_send(but[cur_sel], LV_EVENT_REFRESH, nullptr);
		}

		// Get the new button
		cur_sel = lv_roller_get_selected(page->roller);

		// Turn on new button
		lv_obj_add_style(but[cur_sel], &Gui::panel_highlight_style, LV_PART_MAIN);
		lv_event_send(but[cur_sel], LV_EVENT_REFRESH, nullptr);
		lv_obj_scroll_to_view(but[cur_sel], LV_ANIM_ON);
	}

	static void roller_click_cb(lv_event_t *event) {
		auto page = static_cast<ModuleViewPage *>(event->user_data);
		auto cur_sel = page->cur_selected;
		auto &module_controls = page->module_controls;

		if (cur_sel < module_controls.size()) {
			page->mode = ViewMode::Mapping;
			lv_hide(ui_ElementRollerPanel);
			page->mapping_pane.show(page->drawn_elements[cur_sel]);
		}
	}

	ModuleInfoView moduleinfo;
	PatchModQueue module_mods;

	MapRingDisplay map_ring_display;

	std::string opts;
	uint16_t this_module_id = 0;
	uint32_t cur_selected = 0;
	std::string_view slug = "";
	bool is_patch_playing = false;
	PatchData &patch;

	unsigned active_knob_set = 0;

	std::vector<lv_obj_t *> button;
	std::vector<ModuleParam> module_controls;
	std::vector<DrawnElement> drawn_elements;
	std::array<float, MAX_LIGHTS_PER_MODULE> light_vals{};

	lv_obj_t *canvas = nullptr;
	lv_obj_t *roller = nullptr;
	ModuleViewMappingPane mapping_pane;

	lv_color_t buffer[LV_CANVAS_BUF_SIZE_TRUE_COLOR_ALPHA(240, 240)]{};
	lv_draw_img_dsc_t img_dsc{};

	enum class ViewMode { List, Mapping } mode{ViewMode::List};
};

} // namespace MetaModule
