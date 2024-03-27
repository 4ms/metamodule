#pragma once
#include "CoreModules/elements/element_info.hh"
#include "CoreModules/moduleFactory.hh"
#include "gui/elements/context.hh"
#include "gui/styles.hh"
#include "lvgl.h"
#include "patch/patch_data.hh"
#include "src/misc/lv_style.h"
#include <cmath>

namespace MetaModule
{

template<unsigned MaxCanvasHeight>
class CableDrawer {
	const std::vector<DrawnElement> &drawn;

	lv_obj_t *canvas;
	lv_draw_line_dsc_t cable_dsc;
	lv_draw_line_dsc_t inner_outline_dsc;
	lv_draw_line_dsc_t outer_outline_dsc;
	lv_draw_rect_dsc_t injack_dsc;
	lv_draw_rect_dsc_t outjack_dsc;

	static constexpr uint32_t Height = MaxCanvasHeight;
	static inline std::array<uint8_t, LV_CANVAS_BUF_SIZE_TRUE_COLOR_ALPHA(320, Height)> cable_buf;

	struct Vec2 {
		int32_t x;
		int32_t y;
	};

public:
	CableDrawer(lv_obj_t *parent, const std::vector<DrawnElement> &drawn_elements)
		: drawn{drawn_elements}
		, canvas(lv_canvas_create(parent)) {
		lv_obj_set_size(canvas, 320, Height);
		lv_obj_set_align(canvas, LV_ALIGN_TOP_LEFT);
		lv_obj_add_flag(canvas, LV_OBJ_FLAG_OVERFLOW_VISIBLE | LV_OBJ_FLAG_IGNORE_LAYOUT);
		lv_obj_add_flag(canvas, LV_OBJ_FLAG_SCROLLABLE);
		lv_canvas_set_buffer(canvas, cable_buf.data(), 320, Height, LV_IMG_CF_TRUE_COLOR_ALPHA);

		lv_draw_line_dsc_init(&cable_dsc);
		cable_dsc.width = 3;
		cable_dsc.opa = LV_OPA_100;
		cable_dsc.blend_mode = LV_BLEND_MODE_NORMAL;

		lv_draw_line_dsc_init(&inner_outline_dsc);
		inner_outline_dsc.width = 5;
		inner_outline_dsc.opa = LV_OPA_100;
		inner_outline_dsc.blend_mode = LV_BLEND_MODE_NORMAL;
		inner_outline_dsc.color = lv_color_white();

		lv_draw_line_dsc_init(&outer_outline_dsc);
		outer_outline_dsc.width = 7;
		outer_outline_dsc.opa = LV_OPA_100;
		outer_outline_dsc.blend_mode = LV_BLEND_MODE_NORMAL;
		outer_outline_dsc.color = lv_color_black();

		lv_draw_rect_dsc_init(&injack_dsc);
		injack_dsc.bg_opa = LV_OPA_100;
		injack_dsc.bg_img_opa = LV_OPA_0;
		injack_dsc.outline_opa = LV_OPA_0;
		injack_dsc.shadow_opa = LV_OPA_0;
		injack_dsc.border_opa = LV_OPA_100;
		injack_dsc.border_color = lv_color_black();
		injack_dsc.border_width = 4;
		injack_dsc.blend_mode = LV_BLEND_MODE_NORMAL;
		injack_dsc.radius = 2;

		lv_draw_rect_dsc_init(&outjack_dsc);
		outjack_dsc.bg_opa = LV_OPA_50;
		outjack_dsc.bg_img_opa = LV_OPA_0;
		outjack_dsc.outline_opa = LV_OPA_0;
		outjack_dsc.shadow_opa = LV_OPA_0;
		outjack_dsc.border_opa = LV_OPA_100;
		outjack_dsc.border_color = lv_color_black();
		outjack_dsc.border_width = 3;
		outjack_dsc.blend_mode = LV_BLEND_MODE_NORMAL;
		outjack_dsc.radius = 2;

		set_opacity(LV_OPA_60);
	}

	void clear() {
		lv_canvas_fill_bg(canvas, lv_color_white(), LV_OPA_0);
	}

	void set_height(int16_t height) {
		lv_obj_set_height(canvas, height);
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

	void draw_single_module(const PatchData &patch, uint32_t module_id) {
		clear();
		lv_obj_move_foreground(canvas);
		lv_canvas_fill_bg(canvas, lv_color_white(), LV_OPA_0);

		for (const auto &cable : patch.int_cables) {
			if (cable.out.module_id == module_id) {
				if (auto outpos = find_outjack_xy(cable.out)) {
					draw_outjack({outpos->x, outpos->y}, cable);
				}
			}

			for (const auto &in : cable.ins) {
				if (in.module_id == module_id) {
					if (auto inpos = find_injack_xy(in)) {
						draw_injack({inpos->x, inpos->y}, cable);
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
		uint16_t default_color = get_cable_color(cable.out).full;
		cable_dsc.color.full = cable.color.value_or(default_color);
		draw_cable(start, end);
	}

	void draw_cable(Vec2 start, Vec2 end) {
		float dist_x = std::abs(start.x - end.x);
		float dist_y = std::abs(start.y - end.y);
		CableDrawer::Vec2 control{(start.x + end.x) / 2, ((start.y + end.y) / 2) + (int32_t)dist_x};
		auto steps = std::max<unsigned>(dist_x * dist_y / 1000, 8);
		CableDrawer::draw_bezier(start, end, control, steps);
	}

	void draw_injack(Vec2 location, const InternalCable &cable) {
		uint16_t default_color = get_cable_color(cable.out).full;
		injack_dsc.border_color.full = cable.color.value_or(default_color);
		injack_dsc.bg_color =
			(injack_dsc.border_color.full == lv_color_black().full) ? lv_color_white() : injack_dsc.border_color;
		lv_canvas_draw_rect(canvas, location.x - 4, location.y - 4, 9, 9, &injack_dsc);
	}

	void draw_outjack(Vec2 location, const InternalCable &cable) {
		uint16_t default_color = get_cable_color(cable.out).full;
		outjack_dsc.border_color.full = cable.color.value_or(default_color);
		outjack_dsc.bg_color = outjack_dsc.border_color;
		lv_canvas_draw_rect(canvas, location.x - 9, location.y - 9, 19, 19, &outjack_dsc);
	}

	static lv_color_t get_cable_color(Jack jack) {
		return Gui::cable_palette[(jack.jack_id + jack.module_id) % Gui::cable_palette.size()];
	}

	void draw_bezier(Vec2 start, Vec2 end, Vec2 control, unsigned steps) {
		constexpr size_t MAX_STEPS = 128;

		float step_size = 1.0f / steps;
		lv_point_t points[MAX_STEPS];
		for (unsigned i = 0; i <= steps; i++) {
			auto newpt = CableDrawer::get_quadratic_bezier_pt(start, end, control, (float)i * step_size);
			points[i] = {(int16_t)newpt.x, (int16_t)newpt.y};
		}

		// outlines to make cable stand out on a black or white background
		lv_canvas_draw_line(canvas, points, steps + 1, &outer_outline_dsc);
		lv_canvas_draw_line(canvas, points, steps + 1, &inner_outline_dsc);

		//colored center:
		lv_canvas_draw_line(canvas, points, steps + 1, &cable_dsc);
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
