#pragma once
#include "CoreModules/elements/element_info.hh"
#include "gui/elements/element_name.hh"
#include "gui/elements/map_ring_animate.hh"
#include "gui/elements/module_drawer.hh"
#include "gui/elements/module_param.hh"
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

	struct ViewSettings {
		bool map_ring_flash_active = true;
		MapRingDisplay::Style map_ring_style = {.mode = MapRingDisplay::StyleMode::HideAlways, .opa = LV_OPA_50};
	};
	ViewSettings settings;

	ModuleViewPage(PatchInfo info)
		: PageBase{info}
		, patch{patch_storage.get_view_patch()}
		, base{ui_MappingMenu}
		, roller{ui_ElementRoller}
		, mapping_pane{info.patch_storage, module_mods} {
		PageList::register_page(this, PageId::ModuleView);

		init_bg(base);

		lv_draw_img_dsc_init(&img_dsc);

		lv_obj_remove_style(roller, nullptr, LV_STATE_EDITED);
		lv_obj_remove_style(roller, nullptr, LV_STATE_FOCUS_KEY);

		lv_obj_add_flag(ui_MappingParameters, LV_OBJ_FLAG_HIDDEN);

		button.clear();
		module_controls.clear();
		mapping_pane.init();

		lv_obj_add_event_cb(roller, roller_cb, LV_EVENT_KEY, this);
		lv_obj_add_event_cb(roller, roller_click_cb, LV_EVENT_PRESSED, this);
	}

	void prepare_focus() override {
		mapping_pane.hide();

		patch = patch_storage.get_view_patch();

		is_patch_playing = PageList::get_selected_patch_location() == patch_playloader.cur_patch_location();
		mode = ViewMode::List;

		this_module_id = PageList::get_selected_module_id();

		if (!read_slug()) {
			msg_queue.append_message("Module View page cannot read module slug.\n");
			return;
		}

		moduleinfo = ModuleFactory::getModuleInfo(slug);
		if (moduleinfo.width_hp == 0) {
			msg_queue.append_message("Module View page got empty module info.\r\n");
			return;
		}

		reset_module_page();

		size_t num_elements = moduleinfo.elements.size();
		opts.reserve(num_elements * 16); // 16 chars per roller item
		button.reserve(num_elements);
		drawn_elements.reserve(num_elements);
		module_controls.reserve(num_elements);

		auto module_drawer = ModuleDrawer{ui_ModuleImage, 240};
		canvas = module_drawer.draw_faceplate(slug, buffer);

		lv_obj_refr_size(canvas);
		auto width_px = lv_obj_get_width(canvas);

		active_knob_set = PageList::get_active_knobset();

		module_drawer.draw_mapped_elements(
			patch, this_module_id, active_knob_set, canvas, drawn_elements, is_patch_playing);

		lv_obj_update_layout(canvas);

		for (const auto &drawn_element : drawn_elements) {
			std::visit(
				[this, drawn = drawn_element.gui_element](auto &el) {
					if (!drawn.obj)
						return;

					opts += el.short_name;
					if (drawn.mapped_panel_id) {
						opts += " [";
						opts += get_panel_name<PanelDef>(el, drawn.mapped_panel_id.value());
						opts += "]";
					}
					opts += "\n";

					add_button(drawn.obj);
				},
				drawn_element.element);
			module_controls.emplace_back(drawn_element.element, drawn_element.gui_element.idx);
		}

		// remove final \n
		if (opts.length() > 0)
			opts.pop_back();

		//Show Roller and select it
		lv_obj_set_pos(roller, 0, 0);
		auto roller_width = std::min(320 - width_px, 220);
		lv_obj_set_size(roller, roller_width, 240);
		lv_obj_clear_flag(roller, LV_OBJ_FLAG_HIDDEN);

		// Add text list to roller options
		lv_roller_set_options(roller, opts.c_str(), LV_ROLLER_MODE_NORMAL);
		lv_roller_set_visible_row_count(roller, 11);

		// Select first element
		lv_roller_set_selected(roller, 0, LV_ANIM_OFF);
		cur_selected = 0;

		if (button.size() > 0) {
			lv_obj_add_style(button[cur_selected], &Gui::panel_highlight_style, LV_PART_MAIN);
		}

		update_map_ring_style();

		lv_group_remove_all_objs(group);
		lv_group_add_obj(group, roller);

		lv_group_focus_obj(roller);

		mapping_pane.prepare_focus(group, roller_width, is_patch_playing);
	}

	void update() override {
		if (metaparams.meta_buttons[0].is_just_released()) {
			if (mode == ViewMode::List) {
				if (PageList::request_last_page()) {
					blur();
				}
			} else {
				mode = ViewMode::List;
				lv_show(ui_ElementRoller);
				mapping_pane.hide();
				lv_group_focus_obj(roller);
				lv_obj_clear_state(roller, LV_STATE_PRESSED);
				lv_group_set_editing(group, true);
			}
		}

		if (mode == ViewMode::Knob)
			mapping_pane.update(params);

		if (is_patch_playing) {
			for (auto &drawn_el : drawn_elements) {
				auto was_redrawn = std::visit(UpdateElement{params, patch, drawn_el.gui_element}, drawn_el.element);

				if (was_redrawn && settings.map_ring_flash_active) {
					MapRingDisplay::flash_once(drawn_el.gui_element.map_ring, settings.map_ring_style, true);
				}
			}
		}

		if (auto patch_mod = module_mods.get(); patch_mod.has_value()) {
			PageList::increment_patch_revision();

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
			prepare_focus();
		}
	}

	void apply_add_midi_map(AddMidiMap &mod) {
		if (patch.add_update_midi_map(mod.map)) {
			prepare_focus();
		}
	}

	// This gets called after map_ring_style changes
	void update_map_ring_style() {
		using enum MapRingDisplay::StyleMode;

		for (auto &drawn_el : drawn_elements) {
			auto map_ring = drawn_el.gui_element.map_ring;

			switch (settings.map_ring_style.mode) {
				case ShowAllIfPlaying:
				case CurModuleIfPlaying:
					if (is_patch_playing)
						MapRingDisplay::show(map_ring, settings.map_ring_style.opa);
					else
						MapRingDisplay::hide(map_ring);

					break;

				case CurModule:
				case ShowAll:
					MapRingDisplay::show(map_ring, settings.map_ring_style.opa);
					break;

				case HideAlways:
					MapRingDisplay::hide(map_ring);
					break;
			}
		}
	}

	void blur() final {
		// drawn_elements.clear(); // doing this might lead to fragmentation?
	}

private:
	void add_button(lv_obj_t *obj) {
		auto &b = button.emplace_back();
		b = lv_btn_create(ui_ModuleImage);
		lv_obj_add_style(b, &Gui::invisible_style, LV_PART_MAIN);

		float width = lv_obj_get_width(obj) / 2.f;
		float height = lv_obj_get_height(obj) / 2.f;
		float c_x = (float)lv_obj_get_x(obj) + width;
		float c_y = (float)lv_obj_get_y(obj) + height;

		lv_obj_set_pos(b, std::round(c_x - width * 1.5f), std::round(c_y - height * 1.5f));
		lv_obj_set_size(b, (width * 3.f), (height * 3.f));
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
	}

	bool read_slug() {
		auto module_id = PageList::get_selected_module_id();
		if (patch.patch_name.length() == 0)
			return false;
		if (module_id >= patch.module_slugs.size())
			return false;

		slug = patch.module_slugs[module_id];
		return true;
	}

	static void roller_cb(lv_event_t *event) {
		auto page = static_cast<ModuleViewPage *>(event->user_data);
		auto roller = page->roller;
		auto &cur_sel = page->cur_selected;
		auto &but = page->button;

		// Turn off old button
		if (cur_sel >= 0) {
			lv_obj_remove_style(but[cur_sel], &Gui::panel_highlight_style, LV_PART_MAIN);
			lv_event_send(but[cur_sel], LV_EVENT_REFRESH, nullptr);
		}

		// Get the new button
		cur_sel = lv_roller_get_selected(roller);

		// Turn on new button
		lv_obj_add_style(but[cur_sel], &Gui::panel_highlight_style, LV_PART_MAIN);
		lv_event_send(but[cur_sel], LV_EVENT_REFRESH, nullptr);
	}

	static void roller_click_cb(lv_event_t *event) {
		auto page = static_cast<ModuleViewPage *>(event->user_data);
		auto cur_sel = page->cur_selected;
		auto &module_controls = page->module_controls;

		if (cur_sel < module_controls.size()) {
			page->mode = ViewMode::Knob;
			lv_hide(ui_ElementRoller);
			page->mapping_pane.show(page->drawn_elements[cur_sel]);
		}
	}

	ModuleInfoView moduleinfo;
	PatchModQueue module_mods;

	std::string opts;
	uint16_t this_module_id;
	uint32_t cur_selected = 0;
	std::string_view slug = "";
	bool is_patch_playing = false;
	PatchData &patch;

	unsigned active_knob_set = 0;

	std::vector<lv_obj_t *> button;
	std::vector<ModuleParam> module_controls;
	std::vector<DrawnElement> drawn_elements;

	lv_obj_t *base = nullptr;
	lv_obj_t *canvas = nullptr;
	lv_obj_t *roller = nullptr;
	ModuleViewMappingPane mapping_pane;

	lv_color_t buffer[LV_CANVAS_BUF_SIZE_TRUE_COLOR_ALPHA(240, 240)];
	lv_draw_img_dsc_t img_dsc;

	enum class ViewMode { List, Knob } mode;
};

} // namespace MetaModule
