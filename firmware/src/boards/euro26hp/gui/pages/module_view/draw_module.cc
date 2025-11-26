#include "gui/elements/module_drawer.hh"
#include "gui/elements/redraw.hh"
#include "gui/elements/redraw_display.hh"
#include "gui/elements/redraw_light.hh"
#include "gui/pages/module_view/module_view.hh"

namespace MetaModule
{
unsigned ModuleViewPage::resize_module_image(unsigned max) {
	lv_obj_refr_size(canvas);
	auto width_px = lv_obj_get_width(canvas);
	//module img + padding is no more than 190px wide
	auto display_widthpx = std::min<lv_coord_t>(width_px, max);
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

void ModuleViewPage::redraw_module() {
	reset_module_page();

	size_t num_elements = moduleinfo.elements.size();
	drawn_elements.reserve(num_elements);

	auto module_drawer = ModuleDrawer{.container = ui_ModuleImage, .height = 240};

	auto [faceplate, width] = module_drawer.read_faceplate(slug);
	canvas = module_drawer.draw_faceplate(faceplate, width, buffer);

	active_knobset = page_list.get_active_knobset();

	module_drawer.draw_mapped_elements(
		*patch, this_module_id, active_knobset, canvas, drawn_elements, is_patch_playloaded);

	lv_obj_update_layout(canvas);

	// Populate Roller and highlighter buttons
	populate_element_objects();
	populate_roller();

	//Size Module Image and Roller
	lv_obj_set_pos(ui_ElementRollerPanel, 0, 0);

	resize_module_image(170);
	full_screen_mode = false;

	update_map_ring_style();

	cable_drawer.set_height(240);
	update_cable_style(true);

	lv_obj_refr_size(ui_ElementRollerPanel);
	auto roller_width = lv_obj_get_width(ui_ElementRollerPanel);
	mapping_pane.prepare_focus(group, roller_width, is_patch_playloaded);

	dynamic_elements_prepared = false;
	update_graphic_throttle_setting();
}

void ModuleViewPage::watch_element(DrawnElement const &drawn_element) {
	if (std::get_if<DynamicTextDisplay>(&drawn_element.element)) {
		params.text_displays.start_watching_display(this_module_id, drawn_element.gui_element.idx.light_idx);
	}
}

void ModuleViewPage::redraw_elements() {
	for (auto &drawn_el : drawn_elements) {
		auto &gui_el = drawn_el.gui_element;

		auto value = patch_playloader.param_value(drawn_el.gui_element.module_idx, drawn_el.gui_element.idx.param_idx);
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

void ModuleViewPage::update_map_ring_style() {
	for (auto &drawn_el : drawn_elements) {
		map_ring_display.update(drawn_el, true, is_patch_playloaded);
	}
}

void ModuleViewPage::update_cable_style(bool force) {
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

void ModuleViewPage::update_graphic_throttle_setting() {
	if (page_settings.show_graphic_screens) {
		dyn_draw_throttle = std::max(page_settings.graphic_screen_throttle, 1u);
	} else {
		dyn_draw_throttle = 0;
	}
}

void ModuleViewPage::prepare_dynamic_elements() {
	if (!dynamic_elements_prepared) {
		dyn_draw.prepare_module(drawn_elements, this_module_id, canvas);
		dynamic_elements_prepared = true;
	}
}

} // namespace MetaModule
