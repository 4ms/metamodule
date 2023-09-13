#pragma once
#include "CoreModules/elements/element_info.hh"
#include "CoreModules/moduleFactory.hh"
#include "gui/elements/context.hh"
#include "gui/styles.hh"
#include "lvgl.h"
#include "patch/patch_data.hh"
#include <cmath>

namespace MetaModule
{

class CableDrawer {
	const std::vector<DrawnElement> &drawn;

	lv_obj_t *canvas;
	lv_draw_line_dsc_t drawline_dsc;

	static constexpr uint32_t Height = 4 * 240 + 8;
	static inline std::array<uint8_t, LV_CANVAS_BUF_SIZE_TRUE_COLOR_ALPHA(320, Height)> cable_buf;

	struct Vec2 {
		int32_t x;
		int32_t y;
	};

public:
	CableDrawer(lv_obj_t *parent, const std::vector<DrawnElement> &drawn_elements)
		: drawn{drawn_elements}
		, canvas(lv_canvas_create(parent)) {
		lv_obj_set_size(canvas, 320, Height); //TODO: same as modules_cont height
		lv_obj_set_align(canvas, LV_ALIGN_TOP_LEFT);
		lv_obj_add_flag(canvas, LV_OBJ_FLAG_OVERFLOW_VISIBLE | LV_OBJ_FLAG_IGNORE_LAYOUT);
		lv_obj_add_flag(canvas, LV_OBJ_FLAG_SCROLLABLE);
		lv_canvas_set_buffer(canvas, cable_buf.data(), 320, Height, LV_IMG_CF_TRUE_COLOR_ALPHA);

		lv_draw_line_dsc_init(&drawline_dsc);
		drawline_dsc.width = 4;
		drawline_dsc.opa = LV_OPA_100;
		drawline_dsc.blend_mode = LV_BLEND_MODE_NORMAL;
		set_opacity(LV_OPA_60);
	}

	void clear() {
		lv_canvas_fill_bg(canvas, lv_color_white(), LV_OPA_0);
	}

	void draw(const PatchData &patch) {
		clear();
		lv_obj_move_foreground(canvas);
		lv_canvas_fill_bg(canvas, lv_color_white(), LV_OPA_0);

		for (const auto &cable : patch.int_cables) {
			if (auto outpos = find_outjack_xy(cable.out)) {

				for (const auto &in : cable.ins) {
					if (auto inpos = find_injack_xy(in)) {
						draw_cable({outpos->x, outpos->y}, {inpos->x, inpos->y}, cable);
					}
				}
			}
		}
	}

	void set_opacity(lv_opa_t opa) {
		lv_obj_set_style_opa(canvas, opa, LV_PART_MAIN);
	}

	std::optional<Vec2> find_outjack_xy(Jack jack) {
		for (const auto &d : drawn) {
			if (d.gui_element.module_idx == jack.module_id && d.gui_element.count.num_outputs > 0 &&
				d.gui_element.idx.output_idx == jack.jack_id)
			{
				return get_obj_xy(d.gui_element.obj);
			}
		}
		return std::nullopt;
	}

	std::optional<Vec2> find_injack_xy(Jack jack) {
		for (const auto &d : drawn) {
			if (d.gui_element.module_idx == jack.module_id && d.gui_element.count.num_inputs > 0 &&
				d.gui_element.idx.input_idx == jack.jack_id)
			{
				return get_obj_xy(d.gui_element.obj);
			}
		}
		return std::nullopt;
	}

	static Vec2 get_obj_xy(lv_obj_t *obj) {
		lv_obj_refr_pos(obj);
		lv_area_t coords;
		lv_obj_get_coords(obj, &coords);
		auto w = coords.x2 - coords.x1;
		auto h = coords.y2 - coords.y1;
		auto x = lv_obj_get_x(obj) + w / 2;
		auto y = lv_obj_get_y(obj) + h / 2;
		auto parent = lv_obj_get_parent(obj);
		if (parent) {
			auto offsetx = lv_obj_get_x(parent);
			auto offsety = lv_obj_get_y(parent);
			x += offsetx;
			y += offsety;
		}
		return Vec2{x, y};
	}

	void draw_cable(Vec2 start, Vec2 end, const InternalCable &cable) {		
		drawline_dsc.color.full = cable.color;
		draw_cable(start, end);
	}

	void draw_cable(Vec2 start, Vec2 end) {
		float dist = std::abs(start.x - end.x);
		CableDrawer::Vec2 control{(start.x + end.x) / 2, ((start.y + end.y) / 2) + (int32_t)dist};
		CableDrawer::draw_bezier<8>(start, end, control);
	}

	static lv_color_t get_cable_color(Jack jack) {		
		return Gui::cable_palette[(jack.jack_id + jack.module_id) % Gui::cable_palette.size()];
	}

	template<size_t steps>
	void draw_bezier(Vec2 start, Vec2 end, Vec2 control) {
		constexpr float step_size = 1.0f / steps;
		lv_point_t points[steps + 1];
		for (unsigned i = 0; i <= steps; i++) {
			auto newpt = CableDrawer::get_quadratic_bezier_pt(start, end, control, (float)i * step_size);
			points[i] = {(int16_t)newpt.x, (int16_t)newpt.y};
		}
		lv_canvas_draw_line(canvas, points, steps + 1, &drawline_dsc);
	}

	static Vec2 get_quadratic_bezier_pt(Vec2 start, Vec2 end, Vec2 control, float step) {
		auto get_midpt = [](Vec2 n1, Vec2 n2, float step) -> Vec2 {
			int32_t x = n1.x + ((n2.x - n1.x) * step);
			int32_t y = n1.y + ((n2.y - n1.y) * step);
			return {x, y};
		};
		Vec2 a = get_midpt(start, control, step);
		Vec2 b = get_midpt(control, end, step);
		return get_midpt(a, b, step);
	}
};

} // namespace MetaModule
