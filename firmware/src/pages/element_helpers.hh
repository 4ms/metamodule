#pragma once
#include "CoreModules/module_info_base.hh"
#include "draw_helpers.hh" //for std::vector<DrawHelper::MKnob> mapped_knobs,
#include "lvgl/lvgl.h"
#include "patch/patch_data.hh"

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
LV_IMG_DECLARE(switch_center);
LV_IMG_DECLARE(switch_center_120);

namespace MetaModule
{
struct ElementDrawHelper {

	static void draw_module_knobs(lv_obj_t *canvas,
								  const std::span<const KnobElement> Knobs,
								  const PatchData &patch,
								  std::vector<DrawHelper::MKnob> &mapped_knobs,
								  uint32_t module_id,
								  uint32_t module_height) {
		for (const auto &el : info.Knobs) {
			// auto knob = DrawHelper::draw_knob(canvas, el, 120);
			// if (knob) {
			// 	lv_obj_t *knob_obj = knob.value();
			// 	auto anim_method = DrawHelper::get_anim_method(el);
			// 	if (auto mapped_knob = patch.find_mapped_knob(module_id, el.id)) {
			// 		mapped_knobs.push_back({knob_obj, *mapped_knob, anim_method});
			// 		DrawHelper::draw_control_ring(canvas, el, mapped_knob->panel_knob_id, module_height);
			// 	}
			// }
		}
	}
};
} // namespace MetaModule
