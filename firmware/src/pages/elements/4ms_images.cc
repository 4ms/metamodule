#include "CoreModules/elements/elements.hh"
#include "lvgl/lvgl.h"
#include "pr_dbg.hh"

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

namespace MetaModule::ElementImageImpl
{

const lv_img_dsc_t *get_img(const Pot &, uint32_t scale_px) {
	pr_dbg("get_img->Pot\n");
	return scale_px == 240 ? &knob_x : &knob_x_120;
}

const lv_img_dsc_t *get_img(const Davies1900hBlackKnob &, uint32_t scale_px) {
	pr_dbg("get_img->Davies1900hBlackKno\n");
	return scale_px == 240 ? &knob_x : &knob_x_120;
}

const lv_img_dsc_t *get_img(const DaviesLargeKnob &, uint32_t scale_px) {
	pr_dbg("get_img->DaviesLargeKnob\n");
	return scale_px == 240 ? &knob_large_x : &knob_large_x_120;
}

const lv_img_dsc_t *get_img(const Knob9mm &, uint32_t scale_px) {
	pr_dbg("get_img->Knob9mm\n");
	return scale_px == 240 ? &knob9mm_x : &knob9mm_x_120;
}

const lv_img_dsc_t *get_img(const JackInput &, uint32_t scale_px) {
	pr_dbg("get_img->JackInput\n");
	return scale_px == 240 ? &jack_x : &jack_x_120;
}

const lv_img_dsc_t *get_img(const JackOutput &, uint32_t scale_px) {
	pr_dbg("get_img->JackOutput\n");
	return scale_px == 240 ? &jack_x : &jack_x_120;
}

} // namespace MetaModule::ElementImageImpl
