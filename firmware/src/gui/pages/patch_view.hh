#pragma once
#include "CoreModules/elements/element_counter.hh"
#include "gui/elements/element_drawer.hh"
#include "gui/elements/map_ring_animate.hh"
#include "gui/elements/map_ring_drawer.hh"
#include "gui/elements/mapping.hh"
#include "gui/elements/module_drawer.hh"
#include "gui/elements/update.hh"
#include "gui/images/faceplate_images.hh"
#include "gui/pages/base.hh"
#include "gui/pages/page_list.hh"
#include "gui/pages/patch_view_knobset_menu.hh"
#include "gui/pages/patch_view_settings_menu.hh"
#include "gui/styles.hh"
#include "lvgl.h"
#include "pr_dbg.hh"
#include "util/countzip.hh"

extern "C" {
#include "gui/slsexport/meta5/ui.h"
}

namespace MetaModule
{

struct PatchViewPage : PageBase {
	static inline uint32_t Height = 180;

	PatchViewPage(PatchInfo info)
		: PageBase{info} {
		PageList::register_page(this, PageId::PatchView);

		ui_PatchViewPage_screen_init();
		base = ui_PatchViewPage; //NOLINT

		init_bg(base);
		lv_group_set_editing(group, false);

		lv_obj_set_flex_flow(base, LV_FLEX_FLOW_ROW_WRAP);
		lv_obj_set_flex_align(base, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_END, LV_FLEX_ALIGN_START);
		lv_obj_set_style_pad_gap(base, 4, LV_STATE_DEFAULT);
		lv_obj_add_flag(base, LV_OBJ_FLAG_SCROLLABLE);
		lv_obj_set_scroll_dir(base, LV_DIR_VER);
		lv_obj_set_scrollbar_mode(base, LV_SCROLLBAR_MODE_ACTIVE);

		// lv_obj_add_event_cb(base, base_scroll_cb, LV_EVENT_SCROLL, (void *)this);

		patchname = ui_PatchName; //NOLINT

		playbut = ui_PlayButton; //NOLINT
		lv_obj_add_flag(playbut, LV_OBJ_FLAG_SCROLL_ON_FOCUS);
		lv_obj_clear_flag(playbut, LV_OBJ_FLAG_SCROLLABLE);
		lv_obj_add_event_cb(playbut, playbut_cb, LV_EVENT_PRESSED, this);

		lv_obj_add_flag(ui_AddButton, LV_OBJ_FLAG_SCROLL_ON_FOCUS);
		lv_obj_add_flag(ui_InfoButton, LV_OBJ_FLAG_SCROLL_ON_FOCUS);
		lv_obj_add_flag(ui_KnobButton, LV_OBJ_FLAG_SCROLL_ON_FOCUS);
		lv_obj_add_flag(ui_SettingsButton, LV_OBJ_FLAG_SCROLL_ON_FOCUS);

		// Scroll to top when focussing on a button
		lv_obj_add_event_cb(playbut, button_focussed_cb, LV_EVENT_FOCUSED, this);
		lv_obj_add_event_cb(ui_AddButton, button_focussed_cb, LV_EVENT_FOCUSED, this);
		lv_obj_add_event_cb(ui_InfoButton, button_focussed_cb, LV_EVENT_FOCUSED, this);
		lv_obj_add_event_cb(ui_KnobButton, button_focussed_cb, LV_EVENT_FOCUSED, this);
		lv_obj_add_event_cb(ui_SettingsButton, button_focussed_cb, LV_EVENT_FOCUSED, this);

		// Settings menu
		settings_menu.init();
		knobset_menu.init();

		module_name = lv_label_create(base); //NOLINT
		lv_obj_add_style(module_name, &Gui::header_style, LV_PART_MAIN);
		lv_label_set_text(module_name, "Select a module:");

		modules_cont = lv_obj_create(base); //NOLINT
		lv_obj_set_size(modules_cont, 320, 4 * Height + 8);
		lv_obj_set_style_bg_color(modules_cont, lv_color_black(), LV_STATE_DEFAULT);
		lv_obj_set_style_border_width(modules_cont, 0, LV_STATE_DEFAULT);
		lv_obj_set_style_border_color(modules_cont, lv_color_black(), LV_STATE_DEFAULT);
		lv_obj_set_flex_flow(modules_cont, LV_FLEX_FLOW_ROW_WRAP);
		lv_obj_set_style_pad_gap(modules_cont, 3, LV_STATE_DEFAULT);
		lv_obj_set_style_pad_all(modules_cont, 2, LV_STATE_DEFAULT);
		lv_obj_set_style_radius(modules_cont, 0, LV_STATE_DEFAULT);
		lv_obj_add_flag(modules_cont, LV_OBJ_FLAG_SCROLLABLE);
		lv_obj_add_flag(modules_cont, LV_OBJ_FLAG_SCROLL_ON_FOCUS);

		cable_layer = lv_canvas_create(lv_layer_top()); // NOLINT
		lv_obj_set_size(cable_layer, 320, 240);
		lv_obj_set_align(cable_layer, LV_ALIGN_CENTER);
		lv_canvas_set_buffer(cable_layer, cable_buf.data(), 320, 240, LV_IMG_CF_TRUE_COLOR_ALPHA);

		lv_draw_line_dsc_init(&cable_drawline_dsc);
		cable_drawline_dsc.width = 4;
		cable_drawline_dsc.opa = LV_OPA_60;
		cable_drawline_dsc.blend_mode = LV_BLEND_MODE_NORMAL;
	}

	void prepare_focus() override {

		patch = patch_storage.get_view_patch();

		is_patch_playing = PageList::get_selected_patch_id() == patch_playloader.cur_patch_index();

		if (patch.patch_name.length() == 0)
			return;

		active_knob_set = PageList::get_active_knobset();

		lv_label_set_text(patchname, patch.patch_name.c_str());

		module_canvases.reserve(patch.module_slugs.size());
		module_ids.reserve(patch.module_slugs.size());

		lv_group_remove_all_objs(group);
		lv_group_set_editing(group, false);

		lv_group_add_obj(group, playbut);
		lv_group_add_obj(group, ui_KnobButton);
		lv_group_add_obj(group, ui_AddButton);
		lv_group_add_obj(group, ui_InfoButton);
		lv_group_add_obj(group, ui_SettingsButton);

		auto module_drawer = ModuleDrawer{modules_cont, Height};

		auto canvas_buf = std::span<lv_color_t>{page_pixel_buffer};

		for (auto [module_idx, slug] : enumerate(patch.module_slugs)) {
			module_ids.push_back(module_idx);

			auto canvas = module_drawer.draw_faceplate(slug, canvas_buf);
			if (!canvas)
				continue;

			module_drawer.draw_mapped_elements(
				patch, module_idx, active_knob_set, canvas, drawn_elements, is_patch_playing);

			// Increment the buffer
			lv_obj_refr_size(canvas);
			canvas_buf = canvas_buf.subspan(LV_CANVAS_BUF_SIZE_TRUE_COLOR(1, 1) * lv_obj_get_width(canvas) * Height);

			module_canvases.push_back(canvas);

			lv_group_add_obj(group, canvas);
			lv_obj_add_flag(canvas, LV_OBJ_FLAG_SNAPPABLE);

			lv_obj_add_style(canvas, &Gui::plain_border_style, LV_STATE_DEFAULT);
			lv_obj_add_style(canvas, &Gui::selected_module_style, LV_STATE_FOCUS_KEY);
			lv_obj_add_flag(canvas, LV_OBJ_FLAG_CLICKABLE | LV_OBJ_FLAG_SCROLL_ON_FOCUS);
			lv_obj_clear_flag(canvas, LV_OBJ_FLAG_SCROLLABLE);

			// Give the callback access to the module_idx:
			lv_obj_set_user_data(canvas, (void *)(&module_ids[module_ids.size() - 1]));
			lv_obj_add_event_cb(canvas, module_pressed_cb, LV_EVENT_PRESSED, (void *)this);
			lv_obj_add_event_cb(canvas, module_focus_cb, LV_EVENT_FOCUSED, (void *)this);
			lv_obj_add_event_cb(canvas, module_defocus_cb, LV_EVENT_DEFOCUSED, (void *)this);
		}

		highlighted_module_id = std::nullopt;
		update_map_ring_style();
		//auto cable_drawer = CableDrawer{cable_cont, modules, patch, height};
		//cable_drawer.draw_all();

		lv_obj_scroll_to_y(base, 0, LV_ANIM_OFF);

		settings_menu.focus(group);
		knobset_menu.focus(group, patch.knob_sets);
	}

	void blur() override {
		settings_menu.hide();
		lv_obj_clear_state(ui_SettingsButton, LV_STATE_PRESSED);
		lv_obj_clear_state(ui_SettingsButton, LV_STATE_FOCUSED);

		for (auto &m : module_canvases)
			lv_obj_del(m);

		module_canvases.clear();
		drawn_elements.clear();
		module_ids.clear();
		settings_menu.blur();
		knobset_menu.blur();
	}

	void update() override {
		bool last_is_patch_playing = is_patch_playing;
		is_patch_playing = PageList::get_selected_patch_id() == patch_playloader.cur_patch_index();

		if (is_patch_playing != last_is_patch_playing || map_settings.changed) {
			map_settings.changed = false;
			update_map_ring_style();
		}

		if (is_patch_playing != last_is_patch_playing || knobset_settings.changed) {
			knobset_settings.changed = false;
			update_active_knobset();
		}

		if (metaparams.meta_buttons[0].is_just_released()) {
			if (settings_menu.visible) {
				settings_menu.hide();
			} else if (knobset_menu.visible) {
				knobset_menu.hide();
			} else if (PageList::request_last_page()) {
				blur();
			}
		}

		if (is_patch_playing) {
			for (auto &drawn_el : drawn_elements) {
				std::visit(
					[this, gui_el = drawn_el.gui_element](auto &el) -> void {
						bool did_update = update_element(el, this->params, patch, gui_el);
						if (did_update) {
							if (map_settings.map_ring_flash_active)
								MapRingDisplay::flash_once(gui_el.map_ring,
														   map_settings.map_ring_style,
														   highlighted_module_id == gui_el.module_idx);

							if (map_settings.scroll_to_active_param)
								lv_obj_scroll_to_view_recursive(gui_el.obj, LV_ANIM_ON);
						}
					},
					drawn_el.element);
			}
		}
	}

	void update_map_ring_style() {
		for (auto &drawn_el : drawn_elements) {
			auto map_ring = drawn_el.gui_element.map_ring;
			bool is_on_highlighted_module = (drawn_el.gui_element.module_idx == highlighted_module_id);
			MapRingDisplay::update(map_ring, map_settings.map_ring_style, is_on_highlighted_module, is_patch_playing);
		}
	}

	void update_active_knobset() {
		blur();
		active_knob_set = knobset_settings.active_knobset;
		PageList::set_active_knobset(active_knob_set);
		prepare_focus();
	}

	static void module_pressed_cb(lv_event_t *event) {
		auto page = static_cast<PatchViewPage *>(event->user_data);
		if (!page)
			return;
		lv_canvas_fill_bg(page->cable_layer, lv_color_white(), LV_OPA_0);

		auto obj = event->current_target;
		uint32_t module_id = *(static_cast<uint32_t *>(lv_obj_get_user_data(obj)));
		PageList::set_selected_module_id(module_id);
		PageList::request_new_page(PageId::ModuleView);
	}

	static void module_focus_cb(lv_event_t *event) {
		auto page = static_cast<PatchViewPage *>(event->user_data);
		if (!page)
			return;

		auto this_module_obj = lv_group_get_focused(page->group);
		if (!this_module_obj)
			return;

		auto user_data = lv_obj_get_user_data(this_module_obj);
		if (!user_data)
			return;

		uint32_t module_id = *(static_cast<uint32_t *>(user_data));
		if (module_id >= page->patch.module_slugs.size())
			return;

		page->highlighted_module_id = module_id;

		const auto this_slug = page->patch.module_slugs[module_id];
		lv_label_set_text(page->module_name, this_slug.c_str());

		page->update_map_ring_style();
	}

	static void module_defocus_cb(lv_event_t *event) {
		auto page = static_cast<PatchViewPage *>(event->user_data);
		lv_canvas_fill_bg(page->cable_layer, lv_color_white(), LV_OPA_0);
	}

	static void playbut_cb(lv_event_t *event) {
		auto page = static_cast<PatchViewPage *>(event->user_data);
		page->start_changing_patch();
	}

	static void button_focussed_cb(lv_event_t *event) {
		auto page = static_cast<PatchViewPage *>(event->user_data);
		lv_label_set_text(page->module_name, "Select a module:");
		lv_obj_scroll_to_y(page->base, 0, LV_ANIM_ON);
		page->highlighted_module_id = std::nullopt;
		page->settings_menu.hide();
		page->knobset_menu.hide();
	}

private:
	// lv_obj_t *description;
	lv_obj_t *base;
	lv_obj_t *patchname;
	lv_obj_t *modules_cont;
	lv_obj_t *module_name;
	lv_obj_t *playbut;
	lv_obj_t *cable_layer;

	PatchViewSettingsMenu::ViewSettings map_settings;
	PatchViewSettingsMenu settings_menu{map_settings};

	PatchViewKnobsetMenu::Settings knobset_settings;
	PatchViewKnobsetMenu knobset_menu{knobset_settings};

	std::optional<uint32_t> highlighted_module_id{};

	PatchData &patch = patch_storage.get_view_patch();

	std::vector<lv_obj_t *> module_canvases;
	std::vector<uint32_t> module_ids;
	std::vector<DrawnElement> drawn_elements;
	bool is_patch_playing = false;

	lv_draw_line_dsc_t cable_drawline_dsc;

	unsigned active_knob_set = 0;

	struct focussed_context {
		PatchViewPage *page;
		uint32_t selected_module_id;
	};

	void start_changing_patch() {
		patch_playloader.request_load_view_patch();
	}
};

} // namespace MetaModule
