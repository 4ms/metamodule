#pragma once
#include "CoreModules/info/module_info_base.hh"
#include "lvgl/lvgl.h"
#include "pages/styles.hh"
#include "patch/patch_data.hh"
#include <cmath>

LV_IMG_DECLARE(jack_x);
LV_IMG_DECLARE(jack_x_120);
LV_IMG_DECLARE(knob9mm_x);
LV_IMG_DECLARE(knob9mm_x_120);
LV_IMG_DECLARE(knob_x);
LV_IMG_DECLARE(knob_x_120);
LV_IMG_DECLARE(button_x);
LV_IMG_DECLARE(button_x_120);
LV_IMG_DECLARE(knob_unlined_x);
LV_IMG_DECLARE(knob_unlined_x_120);
LV_IMG_DECLARE(knob_large_x);
LV_IMG_DECLARE(knob_large_x_120);
LV_IMG_DECLARE(slider_x);
LV_IMG_DECLARE(slider_x_120);
LV_IMG_DECLARE(switch_left);
LV_IMG_DECLARE(switch_left_120);
LV_IMG_DECLARE(switch_right);
LV_IMG_DECLARE(switch_right_120);
LV_IMG_DECLARE(switch_up);
LV_IMG_DECLARE(switch_up_120);
LV_IMG_DECLARE(switch_down);
LV_IMG_DECLARE(switch_down_120);

namespace MetaModule
{
struct DrawHelper {
	enum ParamAnimMethods { RotaryPot, LinearSlider, MomentaryButton, LatchingButton, Toggle2pos, Toggle3pos, Encoder };

	//TODO: Knob or Switch ==> rename to MParam?
	struct MKnob {
		lv_obj_t *obj;
		const MappedKnob &mapped_knob;
		ParamAnimMethods anim_method = RotaryPot;
		float last_pot_reading = 0.5f;
	};

	struct SKnob {
		lv_obj_t *obj;
		const StaticParam &static_knob;
		ParamAnimMethods anim_method = RotaryPot;
		float last_pot_reading = 0.5f;
	};

	static void debug_outline(lv_obj_t *obj) {
		lv_obj_set_style_border_width(obj, 1, 0);
		lv_obj_set_style_border_opa(obj, LV_OPA_50, 0);
		lv_obj_set_style_border_color(obj, lv_palette_main(LV_PALETTE_CYAN), 0);
	}

	static const lv_img_dsc_t *get_knob_img_240(KnobDef::Style knob_style) {
		if (knob_style == KnobDef::Small)
			return &knob9mm_x;
		else if (knob_style == KnobDef::Medium)
			return &knob_x;
		else if (knob_style == KnobDef::Large)
			return &knob_large_x;
		else if (knob_style == KnobDef::Slider25mm)
			return &slider_x;
		else
			return nullptr;
	}

	static const lv_img_dsc_t *get_knob_img_120(KnobDef::Style knob_style) {
		if (knob_style == KnobDef::Small)
			return &knob9mm_x_120;
		else if (knob_style == KnobDef::Medium)
			return &knob_x_120;
		else if (knob_style == KnobDef::Large)
			return &knob_large_x_120;
		else if (knob_style == KnobDef::Slider25mm)
			return &slider_x_120;
		else
			return nullptr;
	}

	static const lv_img_dsc_t *get_switch_img_240(SwitchDef::Style switch_style) {
		if (switch_style == SwitchDef::Toggle2pos || switch_style == SwitchDef::Toggle3pos)
			return &switch_left;
		else if (switch_style == SwitchDef::Encoder)
			return &knob_unlined_x;
		else if (switch_style == SwitchDef::MomentaryButton || switch_style == SwitchDef::LatchingButton)
			return &button_x;
		else
			return nullptr;
	}

	static const lv_img_dsc_t *get_switch_img_120(SwitchDef::Style switch_style) {
		if (switch_style == SwitchDef::Toggle2pos || switch_style == SwitchDef::Toggle3pos)
			return &switch_left_120;
		else if (switch_style == SwitchDef::Encoder)
			return &knob_unlined_x_120;
		else if (switch_style == SwitchDef::MomentaryButton || switch_style == SwitchDef::LatchingButton)
			return &button_x_120;
		else
			return nullptr;
	}

	static std::pair<int, int> scale_center(auto el, float module_height) {
		const float adj = (float)(module_height) / 240.f;
		uint16_t x = std::round(ModuleInfoBase::mm_to_px<240>(el.x_mm) * adj);
		uint16_t y = std::round(ModuleInfoBase::mm_to_px<240>(el.y_mm) * adj);
		return std::make_pair(x, y);
	}

	static std::pair<int, int> scale_topleft(auto el, const lv_img_dsc_t *img, float size_adj) {
		auto x = static_cast<int>(
			std::round(ModuleInfoBase::mm_to_px<240>(el.x_mm) * size_adj - (float)img->header.w / 2.f));
		auto y = static_cast<int>(
			std::round(ModuleInfoBase::mm_to_px<240>(el.y_mm) * size_adj - (float)img->header.h / 2.f));
		return std::make_pair(x, y);
	};

	// static ParamAnimMethods get_knob_anim_method(const KnobDef &el) {
	// 	return el.knob_style == KnobDef::Slider25mm ? LinearSlider : RotaryPot;
	// }

	static ParamAnimMethods get_anim_method(const KnobDef &el) {
		return el.knob_style == KnobDef::Slider25mm ? LinearSlider : RotaryPot;
	}

	static ParamAnimMethods get_anim_method(const SwitchDef &el) {
		return el.switch_type == SwitchDef::MomentaryButton ? MomentaryButton :
			   el.switch_type == SwitchDef::LatchingButton	? LatchingButton :
			   el.switch_type == SwitchDef::Toggle2pos		? Toggle2pos :
			   el.switch_type == SwitchDef::Toggle3pos		? Toggle3pos :
			   el.switch_type == SwitchDef::Encoder			? Encoder :
															  MomentaryButton;
		;
	}

	static std::optional<lv_obj_t *> draw_knob(lv_obj_t *base, const KnobDef &el, uint32_t module_height) {
		const float adj = (float)module_height / 240.f;
		const bool fullsize = module_height > 120;
		const lv_img_dsc_t *knob = fullsize ? get_knob_img_240(el.knob_style) : get_knob_img_120(el.knob_style);
		if (!knob)
			return std::nullopt;

		auto [left, top] = scale_topleft(el, knob, adj);
		int width = knob->header.w;
		int height = knob->header.h;

		lv_obj_t *obj = lv_img_create(base);
		lv_img_set_src(obj, knob);
		lv_obj_set_pos(obj, left, top);
		lv_img_set_pivot(obj, width / 2, height / 2);
		lv_obj_add_style(obj, &Gui::mapped_knob_style, LV_PART_MAIN);
		return obj;
	}

	static std::optional<lv_obj_t *> draw_switch(lv_obj_t *base, const SwitchDef &el, uint32_t module_height) {
		const float adj = (float)module_height / 240.f;
		const bool fullsize = module_height > 120;
		const lv_img_dsc_t *switch_img_dsc =
			fullsize ? get_switch_img_240(el.switch_type) : get_switch_img_120(el.switch_type);
		if (!switch_img_dsc)
			return std::nullopt;

		auto [left, top] = scale_topleft(el, switch_img_dsc, adj);
		int width = switch_img_dsc->header.w;
		int height = switch_img_dsc->header.h;

		lv_obj_t *obj = lv_img_create(base);
		lv_img_set_src(obj, switch_img_dsc);
		lv_obj_set_pos(obj, left, top);
		lv_img_set_pivot(obj, width / 2, height / 2);
		lv_obj_add_style(obj, &Gui::mapped_knob_style, LV_PART_MAIN);
		return obj;
	}

	static std::optional<lv_obj_t *> draw_param(lv_obj_t *base, const KnobDef &el, uint32_t module_height) {
		return draw_knob(base, el, module_height);
	}
	static std::optional<lv_obj_t *> draw_param(lv_obj_t *base, const SwitchDef &el, uint32_t module_height) {
		return draw_switch(base, el, module_height);
	}

	// Draw circle around mapped knobs
	static void draw_knob_ring(lv_obj_t *canvas, const KnobDef &el, uint32_t panel_knob_id, uint32_t module_height) {
		lv_draw_arc_dsc_t arc_dsc;
		lv_draw_arc_dsc_init(&arc_dsc);
		arc_dsc.opa = LV_OPA_50;

		const bool fullsize = module_height > 120;

		float radius;
		{
			// Get width of knob image
			const lv_img_dsc_t *knob = fullsize ? get_knob_img_240(el.knob_style) : get_knob_img_120(el.knob_style);
			if (!knob)
				return;
			auto width = knob->header.w;

			const float concentric_offset = 8.f * (float)module_height / 240.f;
			radius = width * 0.5f + concentric_offset;
		}

		auto [c_x, c_y] = scale_center(el, module_height);
		arc_dsc.color = Gui::knob_palette[panel_knob_id % 6];

		// Thinner circle for uvwxyz small panel knobs
		if (panel_knob_id >= 6)
			arc_dsc.width = fullsize ? 4 : 2;
		else
			arc_dsc.width = fullsize ? 10 : 5;

		lv_canvas_draw_arc(canvas, c_x, c_y, radius, 0, 3600, &arc_dsc);
	}

	static void draw_module_jacks(lv_obj_t *canvas,
								  const ModuleInfoView &info,
								  const PatchData &patch,
								  uint32_t module_id,
								  uint32_t module_height) {

		lv_draw_img_dsc_t draw_img_dsc;
		lv_draw_img_dsc_init(&draw_img_dsc);

		const float adj = (float)(module_height) / 240.f;
		const bool fullsize = module_height > 120;

		auto calc_radius = [](auto img) { return (img->header.w + 6) / 2; };

		for (const auto el : info.InJacks) {
			auto jack = fullsize ? &jack_x : &jack_x_120;
			auto [left, top] = scale_topleft(el, jack, adj);
			lv_canvas_draw_img(canvas, left, top, jack, &draw_img_dsc);

			if (patch.find_mapped_injack(Jack{uint16_t(module_id), uint16_t(el.id)})) {
				auto [c_x, c_y] = scale_center(el, module_height);
				Gui::mapped_jack_small_arcdsc.color = Gui::palette_main[el.id % 8];
				lv_canvas_draw_arc(canvas, c_x, c_y, calc_radius(jack), 0, 3600, &Gui::mapped_jack_small_arcdsc);
			}
		}
		for (const auto el : info.OutJacks) {
			auto jack = fullsize ? &jack_x : &jack_x_120;
			auto [left, top] = scale_topleft(el, jack, adj);
			lv_canvas_draw_img(canvas, left, top, jack, &draw_img_dsc);

			if (patch.find_mapped_outjack(Jack{uint16_t(module_id), uint16_t(el.id)})) {
				Gui::mapped_jack_small_arcdsc.color = Gui::palette_main[el.id % 8];
				auto [c_x, c_y] = scale_center(el, module_height);
				lv_canvas_draw_arc(canvas, c_x, c_y, calc_radius(jack), 0, 3600, &Gui::mapped_jack_small_arcdsc);
			}
		}

		// for (const auto el : info.Switches) {
		// 	const lv_img_dsc_t *sw = fullsize ? get_switch_img_240(el.switch_type) : get_switch_img_120(el.switch_type);
		// 	if (!sw)
		// 		continue;

		// 	auto [left, top] = scale_topleft(el, sw, adj);
		// 	lv_canvas_draw_img(canvas, left, top, sw, &draw_img_dsc);

		// 	// if (patch.find_mapped_knob(module_id, el.id)) {
		// 	// 	auto [c_x, c_y] = scale_center(el, module_height);
		// 	// 	lv_canvas_draw_arc(canvas, c_x, c_y, calc_radius(sw), 0, 3600, &Gui::mapped_knob_small_arcdsc);
		// 	// }
		// }
	}

	struct Vec2 {
		int32_t x;
		int32_t y;
	};

	static void draw_cable(Vec2 start, Vec2 end, lv_obj_t *canvas, lv_draw_line_dsc_t *drawline_dsc) {
		float dist = std::abs(start.x - end.x);
		DrawHelper::Vec2 control{(start.x + end.x) / 2, ((start.y + end.y) / 2) + (int32_t)dist};
		DrawHelper::draw_bezier<8>(start, end, control, canvas, drawline_dsc);
		// printf("Cable: [%d, %d] to [%d, %d]\n", start.x, start.y, end.x, end.y);
	}

	static lv_color_t get_cable_color(Jack jack) {
		return Gui::cable_palette[(jack.jack_id + jack.module_id) % Gui::cable_palette.size()];
	}

	template<size_t steps>
	static void draw_bezier(Vec2 start, Vec2 end, Vec2 control, lv_obj_t *canvas, lv_draw_line_dsc_t *drawline_dsc) {
		constexpr float step_size = 1.0f / steps;
		lv_point_t points[steps + 1];
		for (unsigned i = 0; i <= steps; i++) {
			auto newpt = DrawHelper::get_quadratic_bezier_pt(start, end, control, (float)i * step_size);
			points[i] = {(int16_t)newpt.x, (int16_t)newpt.y};
		}
		lv_canvas_draw_line(canvas, points, steps + 1, drawline_dsc);
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

	static Vec2 get_jack_xy(auto jacklist, lv_obj_t *module_obj, const Jack &in, uint32_t module_height) {
		// const int y_adjust = module_height == 120 ? -6 : 6;
		auto [x, y] = DrawHelper::scale_center(jacklist[in.jack_id], module_height);
		lv_area_t coords;
		lv_obj_get_coords(module_obj, &coords);
		// auto sn = lv_obj_get_scroll_y(lv_obj_get_parent(lv_obj_get_parent(module_obj)));
		// printf("module [%d, %d], [%d, %d], %d\n", coords.x1, coords.y1, coords.x2, coords.y2, sn);
		x += coords.x1;
		y += coords.y1; // + y_adjust;
		return {x, y};
	}
};
} // namespace MetaModule
