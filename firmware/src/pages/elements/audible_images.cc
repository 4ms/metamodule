#include "CoreModules/elements/elements.hh"
#include "lvgl/lvgl.h"
#include "pr_dbg.hh"

LV_IMG_DECLARE(jack_x);
LV_IMG_DECLARE(jack_x_120);
LV_IMG_DECLARE(Rogan2SGray_240);
LV_IMG_DECLARE(Rogan2SGray_120);
LV_IMG_DECLARE(Rogan2PSWhite_240);
LV_IMG_DECLARE(Rogan2PSWhite_120);
LV_IMG_DECLARE(Rogan2PSGreen_240);
LV_IMG_DECLARE(Rogan2PSGreen_120);
LV_IMG_DECLARE(Rogan2PSRed_240);
LV_IMG_DECLARE(Rogan2PSRed_120);
LV_IMG_DECLARE(braids_display_240);

namespace MetaModule::ElementImageImpl
{

const lv_img_dsc_t *get_img(const Rogan2SGray &, uint32_t scale_px) {
	pr_dbg("get_img->Rogan2SGray\n");
	return scale_px == 240 ? &Rogan2SGray_240 : &Rogan2SGray_120;
}

const lv_img_dsc_t *get_img(const Rogan2PSWhite &, uint32_t scale_px) {
	pr_dbg("get_img->Rogan2PSWhite\n");
	return scale_px == 240 ? &Rogan2PSWhite_240 : &Rogan2PSWhite_120;
}

const lv_img_dsc_t *get_img(const Rogan2PSRed &, uint32_t scale_px) {
	pr_dbg("get_img->Rogan2PSRed\n");
	return scale_px == 240 ? &Rogan2PSRed_240 : &Rogan2PSRed_120;
}

const lv_img_dsc_t *get_img(const Rogan2PSGreen &, uint32_t scale_px) {
	pr_dbg("get_img->Rogan2PSGreen\n");
	return scale_px == 240 ? &Rogan2PSGreen_240 : &Rogan2PSGreen_120;
}

const lv_img_dsc_t *get_img(const PJ301MPortIn &, uint32_t scale_px) {
	pr_dbg("get_img->PJ301MPort\n");
	return scale_px == 240 ? &jack_x : &jack_x_120;
}

const lv_img_dsc_t *get_img(const PJ301MPortOut &, uint32_t scale_px) {
	pr_dbg("get_img->PJ301MPort\n");
	return scale_px == 240 ? &jack_x : &jack_x_120;
}

const lv_img_dsc_t *get_img(const BraidsDisplay148x56 &, uint32_t scale_px) {
	pr_dbg("get_img->BraidsDisplay148x56\n");
	return scale_px == 240 ? &braids_display_240 : &braids_display_240;
}

} // namespace MetaModule::ElementImageImpl
