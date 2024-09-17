#pragma once
#include "CoreModules/elements/element_state_conversion.hh"
#include "CoreModules/elements/elements.hh"
#include "gui/elements/context.hh"
#include "gui/images/paths.hh"
#include "lvgl.h"
#include "patch/patch_data.hh"
#include "patch_play/param_watch.hh"
#include "pr_dbg.hh"
#include <cmath>

// TODO: there should be no dependency on a specific brand here
#include "CoreModules/4ms/4ms_element_state_conversions.hh"

namespace MetaModule
{

inline bool redraw_element(const Knob &, const GuiElement &gui_el, float val) {
	bool did_update_position = false;

	constexpr int32_t threshold_centidegrees = 10; // 10 centidegrees = 1.0 degrees

	int32_t angle = val * 3000.f - 1500.f;
	while (angle < 0)
		angle += 3600;

	bool is_img = lv_obj_has_class(gui_el.obj, &lv_img_class);

	int32_t cur_angle =
		is_img ? lv_img_get_angle(gui_el.obj) : lv_obj_get_style_transform_angle(gui_el.obj, LV_PART_MAIN);

	if (std::abs(angle - cur_angle) > threshold_centidegrees) {
		if (is_img)
			lv_img_set_angle(gui_el.obj, angle);
		else
			lv_obj_set_style_transform_angle(gui_el.obj, angle, LV_PART_MAIN);

		did_update_position = true;
	}

	return did_update_position;
}

// Slider update
inline bool redraw_element(const Slider &element, const GuiElement &gui_el, float val) {
	bool did_update_position = false;

	auto handle = lv_obj_get_child(gui_el.obj, 0);
	if (!handle) {
		pr_err("No handle sub-object for slider %16s\n", element.short_name.data());
		return false;
	}
	auto height = lv_obj_get_height(gui_el.obj);
	auto width = lv_obj_get_width(gui_el.obj);

	if (height > width) {
		// Vertical Slider
		auto handle_height = lv_obj_get_height(handle);
		int32_t pos = (1.f - val) * (height - handle_height);
		int32_t cur_pos = lv_obj_get_y(handle);
		if (pos != cur_pos) {
			lv_obj_set_y(handle, pos);
			did_update_position = true;
		}

	} else {
		// Horizontal Slider
		auto handle_width = lv_obj_get_width(handle);
		int32_t pos = val * (width - handle_width);
		int32_t cur_pos = lv_obj_get_x(handle);
		if (pos != cur_pos) {
			lv_obj_set_x(handle, pos);
			did_update_position = true;
		}
	}

	return did_update_position;
}

inline bool redraw_element(const FlipSwitch &element, const GuiElement &gui_el, float val) {
	bool did_change_frame = false;

	unsigned frame_num = StateConversion::convertState(element, val);

	if (frame_num < element.frames.size()) {

		auto img = ComponentImages::get_comp_path(element.frames[frame_num]);
		if (!img.length())
			return false;

		auto cur_img_src = lv_img_get_src(gui_el.obj);
		auto cur_img = std::string_view{static_cast<const char *>(cur_img_src)};

		if (img != cur_img) {
			lv_img_set_src(gui_el.obj, img.c_str());
			did_change_frame = true;
		}
	}

	return did_change_frame;
}

inline bool redraw_element(const MomentaryButton &element, const GuiElement &gui_el, float val) {
	bool did_change_image = false;

	auto state = StateConversion::convertState(element, val);
	auto image_name = state == MomentaryButton::State_t::PRESSED ? element.pressed_image : element.image;

	auto img = ComponentImages::get_comp_path(image_name);
	if (!img.length())
		return false;

	auto cur_img_src = lv_img_get_src(gui_el.obj);
	auto cur_img = std::string_view{static_cast<const char *>(cur_img_src)};

	if (img != cur_img) {
		lv_img_set_src(gui_el.obj, img.c_str());
		did_change_image = true;
	}

	return did_change_image;
}

inline bool redraw_element(const SlideSwitch &element, const GuiElement &gui_el, float val) {
	auto handle = lv_obj_get_child(gui_el.obj, 0);
	if (!handle) {
		pr_err("No handle object for SlideSwitch\n");
		return false;
	}
	// major axis = height if vertical, width if horizontal.

	auto height = lv_obj_get_height(gui_el.obj);
	auto width = lv_obj_get_width(gui_el.obj);
	bool vert = height > width;
	auto major_dim = vert ? height : width;
	auto handle_major_dim = major_dim / element.num_pos;
	lv_coord_t major_range = major_dim - handle_major_dim;

	lv_obj_refr_size(handle);
	lv_obj_refr_pos(handle);
	int32_t cur_pos = vert ? lv_obj_get_y(handle) : lv_obj_get_x(handle);

	if (element.direction == SlideSwitch::Ascend::UpLeft)
		cur_pos = major_range - cur_pos;

	// cur_pos ranges from 0 to major_range
	auto cur_state = StateConversion::convertState(element, (float)cur_pos / (float)major_range);
	auto new_state = StateConversion::convertState(element, val); //0..N-1 0..6

	bool did_update_position = false;

	if (new_state != cur_state) {
		lv_coord_t new_pos = ((float)new_state / (float)(element.num_pos - 1)) * major_range;

		if (element.direction == SlideSwitch::Ascend::UpLeft)
			new_pos = major_range - new_pos;

		if (vert)
			lv_obj_set_y(handle, new_pos);
		else
			lv_obj_set_x(handle, new_pos);
		did_update_position = true;
	}

	return did_update_position;
}

inline bool redraw_element(const BaseElement &, const GuiElement &, float) {
	return false;
}

struct RedrawElement {
	PatchData const *patch;
	GuiElement &gui_el;

	bool operator()(auto &el) {
		if (!gui_el.obj)
			return false;

		if (auto s_param = patch->find_static_knob(gui_el.module_idx, gui_el.idx.param_idx))
			return redraw_element(el, gui_el, s_param->value);
		else
			return false;
	}
};

inline bool redraw_param(DrawnElement &drawn_el,
						 std::array<WatchedParam, ParamWatcher::MaxParamsToWatch> const &watched_params) {
	bool was_redrawn = false;
	if (drawn_el.element.index() == Element{DynamicTextDisplay{}}.index()) {

		// Scan all watched_params to find a match
		for (auto &p : watched_params) {
			if (p.is_active() && p.module_id == drawn_el.gui_element.module_idx &&
				p.param_id != drawn_el.gui_element.idx.param_idx)

				was_redrawn = std::visit([&](auto &el) { return redraw_element(el, drawn_el.gui_element, p.value); },
										 drawn_el.element);

			break;
		}
	}
	return was_redrawn;
}

} // namespace MetaModule
