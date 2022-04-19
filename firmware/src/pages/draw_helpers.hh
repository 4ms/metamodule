#pragma once
#include "CoreModules/info/module_info_base.hh"
#include "lvgl/lvgl.h"

LV_IMG_DECLARE(jack_x);
LV_IMG_DECLARE(knob9mm_x);
LV_IMG_DECLARE(knob_x);
LV_IMG_DECLARE(button_x);
LV_IMG_DECLARE(knob_unlined_x);
LV_IMG_DECLARE(knob_large_x);
LV_IMG_DECLARE(slider_x);
LV_IMG_DECLARE(switch_left);
LV_IMG_DECLARE(switch_right);
LV_IMG_DECLARE(switch_up);
LV_IMG_DECLARE(switch_down);

namespace MetaModule
{
struct DrawHelper {
	static void draw_module_controls(lv_obj_t *canvas, const ModuleInfoView &info, uint32_t zoom) {
		static lv_draw_img_dsc_t draw_img_dsc;
		lv_draw_img_dsc_init(&draw_img_dsc);
		draw_img_dsc.zoom = zoom;
		float adj = (float)(zoom) / 256.f;

		auto scale_center = [adj](auto el, auto img_header) -> std::pair<int, int> {
			auto x = static_cast<int>(0.5f + (ModuleInfoBase::mm_to_px<240>(el.x_mm) - img_header.w / 2) * adj);
			auto y = static_cast<int>(0.5f + (ModuleInfoBase::mm_to_px<240>(el.y_mm) - img_header.h / 2) * adj);
			return std::make_pair(x, y);
		};

		for (const auto el : info.Knobs) {
			const lv_img_dsc_t *knob = nullptr;
			if (el.knob_style == KnobDef::Small)
				knob = &knob9mm_x;
			else if (el.knob_style == KnobDef::Medium)
				knob = &knob_x;
			else if (el.knob_style == KnobDef::Large)
				knob = &knob_large_x;
			else if (el.knob_style == KnobDef::Slider25mm)
				knob = &slider_x;
			else
				continue;

			auto [x, y] = scale_center(el, knob->header);
			lv_canvas_draw_img(canvas, x, y, knob, &draw_img_dsc);
		}
		for (const auto el : info.InJacks) {
			auto [x, y] = scale_center(el, jack_x.header);
			lv_canvas_draw_img(canvas, x, y, &jack_x, &draw_img_dsc);
		}
		for (const auto el : info.OutJacks) {
			auto [x, y] = scale_center(el, jack_x.header);
			lv_canvas_draw_img(canvas, x, y, &jack_x, &draw_img_dsc);
		}
		for (const auto el : info.Switches) {
			const lv_img_dsc_t *sw = nullptr;
			if (el.switch_type == SwitchDef::Toggle2pos || el.switch_type == SwitchDef::Toggle3pos)
				sw = &switch_left;
			else if (el.switch_type == SwitchDef::Encoder)
				sw = &knob_unlined_x;
			else if (el.switch_type == SwitchDef::MomentaryButton || el.switch_type == SwitchDef::LatchingButton)
				sw = &button_x;
			else
				continue;
			auto [x, y] = scale_center(el, sw->header);
			lv_canvas_draw_img(canvas, x, y, sw, &draw_img_dsc);
		}
	}
};
} // namespace MetaModule
