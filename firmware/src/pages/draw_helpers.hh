#pragma once
#include "CoreModules/info/module_info_base.hh"
#include "lvgl/lvgl.h"

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

	static void draw_module_controls(lv_obj_t *canvas, const ModuleInfoView &info, uint32_t module_height) {
		static lv_draw_img_dsc_t draw_img_dsc;
		lv_draw_img_dsc_init(&draw_img_dsc);

		const float adj = (float)(module_height) / 240.f;
		const bool fullsize = module_height > 120;

		auto scale_center = [adj](auto el, auto img_header) -> std::pair<int, int> {
			auto x =
				static_cast<int>((ModuleInfoBase::mm_to_px<240>(el.x_mm) * adj - (float)img_header.w / 2.f) + 0.5f);
			auto y =
				static_cast<int>((ModuleInfoBase::mm_to_px<240>(el.y_mm) * adj - (float)img_header.h / 2.f) + 0.5f);
			return std::make_pair(x, y);
		};

		for (const auto el : info.Knobs) {
			const lv_img_dsc_t *knob = fullsize ? get_knob_img_240(el.knob_style) : get_knob_img_120(el.knob_style);
			if (!knob)
				continue;

			auto [x, y] = scale_center(el, knob->header);
			lv_canvas_draw_img(canvas, x, y, knob, &draw_img_dsc);
		}
		for (const auto el : info.InJacks) {
			auto jack = fullsize ? &jack_x : &jack_x_120;
			auto [x, y] = scale_center(el, jack->header);
			lv_canvas_draw_img(canvas, x, y, jack, &draw_img_dsc);
		}
		for (const auto el : info.OutJacks) {
			auto jack = fullsize ? &jack_x : &jack_x_120;
			auto [x, y] = scale_center(el, jack->header);
			lv_canvas_draw_img(canvas, x, y, jack, &draw_img_dsc);
		}
		for (const auto el : info.Switches) {
			const lv_img_dsc_t *sw = fullsize ? get_switch_img_240(el.switch_type) : get_switch_img_120(el.switch_type);
			if (!sw)
				continue;
			auto [x, y] = scale_center(el, sw->header);
			lv_canvas_draw_img(canvas, x, y, sw, &draw_img_dsc);
		}
	}
};
} // namespace MetaModule
