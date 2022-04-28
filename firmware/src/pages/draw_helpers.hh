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
	static void draw_module_controls(lv_obj_t *canvas, const ModuleInfoView &info, uint32_t module_height) {
		static lv_draw_img_dsc_t draw_img_dsc;
		lv_draw_img_dsc_init(&draw_img_dsc);
		// draw_img_dsc.zoom = zoom;

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
			const lv_img_dsc_t *knob = nullptr;
			if (el.knob_style == KnobDef::Small)
				knob = fullsize ? &knob9mm_x : &knob9mm_x_120;
			else if (el.knob_style == KnobDef::Medium)
				knob = fullsize ? &knob_x : &knob_x_120;
			else if (el.knob_style == KnobDef::Large)
				knob = fullsize ? &knob_large_x : &knob_large_x_120;
			else if (el.knob_style == KnobDef::Slider25mm)
				knob = fullsize ? &slider_x : &slider_x_120;
			else
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
			const lv_img_dsc_t *sw = nullptr;
			if (el.switch_type == SwitchDef::Toggle2pos || el.switch_type == SwitchDef::Toggle3pos)
				sw = fullsize ? &switch_left : &switch_left_120;
			else if (el.switch_type == SwitchDef::Encoder)
				sw = fullsize ? &knob_unlined_x : &knob_unlined_x_120;
			else if (el.switch_type == SwitchDef::MomentaryButton || el.switch_type == SwitchDef::LatchingButton)
				sw = fullsize ? &button_x : &button_x_120;
			else
				continue;
			auto [x, y] = scale_center(el, sw->header);
			lv_canvas_draw_img(canvas, x, y, sw, &draw_img_dsc);
		}
	}
};
} // namespace MetaModule
