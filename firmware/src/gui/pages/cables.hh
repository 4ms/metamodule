#pragma once
#include "CoreModules/elements/element_info.hh"
#include "gui/elements/context.hh"
#include "gui/styles.hh"
#include "lvgl.h"
#include "moduleFactory.hh"
#include "patch/patch_data.hh"
#include <cmath>

namespace MetaModule
{

class CableDrawer {
	PatchData &patch;
	const std::vector<DrawnElement> &drawn;
	uint32_t module_height;

	lv_obj_t *canvas;
	lv_draw_line_dsc_t drawline_dsc;

	static constexpr uint32_t Height = 4 * 240 + 8;
	static inline std::array<uint8_t, LV_CANVAS_BUF_SIZE_TRUE_COLOR_ALPHA(320, Height)> cable_buf;

	struct Vec2 {
		int32_t x;
		int32_t y;
	};

public:
	CableDrawer(lv_obj_t *parent,
				PatchData &patch,
				const std::vector<DrawnElement> &drawn_elements,
				uint32_t module_height)
		: patch{patch}
		, drawn{drawn_elements}
		, module_height{module_height}
		, canvas(lv_canvas_create(parent)) {
		lv_obj_set_size(canvas, 320, Height); //TODO: same as modules_cont height
		lv_obj_set_align(canvas, LV_ALIGN_TOP_LEFT);
		lv_obj_add_flag(canvas, LV_OBJ_FLAG_OVERFLOW_VISIBLE | LV_OBJ_FLAG_IGNORE_LAYOUT);
		lv_obj_add_flag(canvas, LV_OBJ_FLAG_SCROLLABLE);
		lv_canvas_set_buffer(canvas, cable_buf.data(), 320, Height, LV_IMG_CF_TRUE_COLOR_ALPHA);

		lv_draw_line_dsc_init(&drawline_dsc);
		drawline_dsc.width = 4;
		drawline_dsc.opa = LV_OPA_60;
		drawline_dsc.blend_mode = LV_BLEND_MODE_NORMAL;
	}

	std::optional<Vec2> find_outjack_xy(Jack jack) {
		for (const auto &d : drawn) {
			if (d.gui_element.module_idx != jack.module_id || d.gui_element.count.num_outputs == 0)
				continue;
			if (d.gui_element.idx.output_idx == jack.jack_id) {
				auto x = lv_obj_get_x(d.gui_element.obj);
				auto y = lv_obj_get_x(d.gui_element.obj);
				return Vec2{x, y};
			}
		}
		return std::nullopt;
	}

	std::optional<Vec2> find_injack_xy(Jack jack) {
		for (const auto &d : drawn) {
			if (d.gui_element.module_idx != jack.module_id || d.gui_element.count.num_inputs == 0)
				continue;
			if (d.gui_element.idx.input_idx == jack.jack_id) {
				lv_obj_update_layout(d.gui_element.obj);
				auto x = lv_obj_get_x(d.gui_element.obj);
				auto y = lv_obj_get_x(d.gui_element.obj);
				return Vec2{x, y};
			}
		}
		return std::nullopt;
	}

	void draw() {
		lv_canvas_fill_bg(canvas, lv_color_white(), LV_OPA_0);

		for (const auto &cable : patch.int_cables) {
			if (auto outpos = find_outjack_xy(cable.out)) {

				for (const auto &in : cable.ins) {
					if (auto inpos = find_injack_xy(in)) {
						printf_("Cable: %d,%d -> %d,%d\n", outpos->x, outpos->y, inpos->x, inpos->y);
						draw_cable({outpos->x, outpos->y}, {inpos->x, inpos->y});
					}
				}
			}
		}
		// Draw all cables connected to this module
		// TODO: gotta be a cleaner way to do this...
		// 		push Jack{c.out}, this_module_obj, Jack{in}, outmodule_obj
		// 		draw_cable(Jack out, Jack in, lv_obj_t *out_module, lv_obj_t *in_module);
		// const auto thismoduleinfo = ModuleFactory::getModuleInfo(this_slug);
		// if (thismoduleinfo.width_hp > 0) {
		//for (const auto &c : patch.int_cables) {
		//	// Draw cable(s) if out jack is on this module
		//	if (c.out.module_id == module_id) {
		//		auto end = DrawHelper::get_jack_xy(thismoduleinfo.OutJacks, this_module_obj, c.out, height);

		//		// Draw a cable from this out jack to all in jacks it's connected to
		//		for (const auto &in : c.ins) {
		//			// Iterate through all modules to find the one with a matching id (TODO: better way to do this?)
		//			for (auto inmodule_obj : page->modules) {
		//				uint32_t t_module_id = *(static_cast<uint32_t *>(lv_obj_get_user_data(inmodule_obj)));
		//				if (t_module_id == in.module_id) {
		//					const auto inmodule_info =
		//						ModuleFactory::getModuleInfo(patch.module_slugs[t_module_id]);
		//					auto start = DrawHelper::get_jack_xy(inmodule_info.InJacks, inmodule_obj, in, height);
		//					page->cable_drawline_dsc.color = DrawHelper::get_cable_color(in);
		//					DrawHelper::draw_cable(start, end, page->cable_layer, &page->cable_drawline_dsc);
		//					break;
		//				}
		//			}
		//		}
		//		continue; //We drew the output to all inputs, no need to check if any inputs are on this module
		//	}
		//	// Draw cable if in jack is on this module
		//	for (const auto &in : c.ins) {
		//		if (in.module_id == module_id) {
		//			auto start = DrawHelper::get_jack_xy(thismoduleinfo.InJacks, this_module_obj, in, height);
		//			//Find output jack on another module
		//			for (auto outmodule_obj : page->modules) {
		//				uint32_t t_module_id = *(static_cast<uint32_t *>(lv_obj_get_user_data(outmodule_obj)));
		//				if (t_module_id == c.out.module_id) {
		//					auto outmodule_info = ModuleFactory::getModuleInfo(patch.module_slugs[t_module_id]);
		//					auto end =
		//						DrawHelper::get_jack_xy(outmodule_info.OutJacks, outmodule_obj, c.out, height);
		//					page->cable_drawline_dsc.color = DrawHelper::get_cable_color(in);
		//					DrawHelper::draw_cable(start, end, page->cable_layer, &page->cable_drawline_dsc);
		//					break;
		//				}
		//			}
		//		}
		//	}
		// }
		// }
	}

	void draw_cable(Vec2 start, Vec2 end, const Jack &outjack) {
		drawline_dsc.color = get_cable_color(outjack);
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

	std::pair<int, int> scale_center(BaseElement const &el) {
		const float adj = (float)(module_height) / 240.f;
		uint16_t x = std::round(ModuleInfoBase::mm_to_px(el.x_mm, module_height) * adj);
		uint16_t y = std::round(ModuleInfoBase::mm_to_px(el.y_mm, module_height) * adj);
		return std::make_pair(x, y);
	}

	// Vec2 get_jack_xy(std::span<BaseElement> jacklist, lv_obj_t *module_obj, Jack const &in) {
	// 	auto [x, y] = CableDrawer::scale_center(jacklist[in.jack_id]);
	// 	lv_area_t coords;
	// 	lv_obj_get_coords(module_obj, &coords);
	// 	x += coords.x1;
	// 	y += coords.y1;
	// 	return {x, y};
	// }
};

} // namespace MetaModule
