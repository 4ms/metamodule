#pragma once
#include "CoreModules/elements/element_info.hh"
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
LV_IMG_DECLARE(BananaBlack_240);
LV_IMG_DECLARE(BananaBlack_120);
LV_IMG_DECLARE(BananaRed_240);
LV_IMG_DECLARE(BananaRed_120);
LV_IMG_DECLARE(Davies1900hRed_240);
LV_IMG_DECLARE(Davies1900hRed_120);
LV_IMG_DECLARE(Davies1900hWhite_240);
LV_IMG_DECLARE(Davies1900hWhite_120);
LV_IMG_DECLARE(MediumLight_240);
LV_IMG_DECLARE(MediumLight_120);
LV_IMG_DECLARE(Rogan2SGray_240);
LV_IMG_DECLARE(Rogan2SGray_120);
LV_IMG_DECLARE(Rogan2PSWhite_240);
LV_IMG_DECLARE(Rogan2PSWhite_120);
LV_IMG_DECLARE(Rogan2PSGreen_240);
LV_IMG_DECLARE(Rogan2PSGreen_120);
LV_IMG_DECLARE(Rogan2PSRed_240);
LV_IMG_DECLARE(Rogan2PSRed_120);

LV_IMG_DECLARE(braids_display_240);

namespace MetaModule
{

struct ElementImage {
	uint32_t scale_px;

	ElementImage(uint32_t module_height)
		: scale_px{module_height} {
	}

	const lv_img_dsc_t *get_img(const Element &) {
		pr_dbg("get_img->unknown\n");
		return nullptr;
	}
	const lv_img_dsc_t *get_img(const Pot &) {
		pr_dbg("get_img->Pot\n");
		return scale_px == 240 ? &knob_x : &knob_x_120;
	}
	const lv_img_dsc_t *get_img(const Davies1900hWhiteKnob &) {
		pr_dbg("get_img->Davies1900hWhiteKnob\n");
		return scale_px == 240 ? &Davies1900hWhite_240 : &Davies1900hWhite_120;
	}
	const lv_img_dsc_t *get_img(const Davies1900hRedKnob &) {
		pr_dbg("get_img->Davies1900hRedKnob\n");
		return scale_px == 240 ? &Davies1900hRed_240 : &Davies1900hRed_120;
	}
	const lv_img_dsc_t *get_img(const Davies1900hBlackKnob &) {
		pr_dbg("get_img->Davies1900hBlackKno\n");
		return scale_px == 240 ? &knob_x : &knob_x_120;
	}
	const lv_img_dsc_t *get_img(const DaviesLargeKnob &) {
		pr_dbg("get_img->DaviesLargeKnob\n");
		return scale_px == 240 ? &knob_large_x : &knob_large_x_120;
	}
	const lv_img_dsc_t *get_img(const Knob9mm &) {
		pr_dbg("get_img->Knob9mm\n");
		return scale_px == 240 ? &knob9mm_x : &knob9mm_x_120;
	}
	const lv_img_dsc_t *get_img(const Rogan2SGray &) {
		pr_dbg("get_img->Rogan2SGray\n");
		return scale_px == 240 ? &Rogan2SGray_240 : &Rogan2SGray_120;
	}
	const lv_img_dsc_t *get_img(const Rogan2PSWhite &) {
		pr_dbg("get_img->Rogan2PSWhite\n");
		return scale_px == 240 ? &Rogan2PSWhite_240 : &Rogan2PSWhite_120;
	}
	const lv_img_dsc_t *get_img(const Rogan2PSRed &) {
		pr_dbg("get_img->Rogan2PSRed\n");
		return scale_px == 240 ? &Rogan2PSRed_240 : &Rogan2PSRed_120;
	}
	const lv_img_dsc_t *get_img(const Rogan2PSGreen &) {
		pr_dbg("get_img->Rogan2PSGreen\n");
		return scale_px == 240 ? &Rogan2PSGreen_240 : &Rogan2PSGreen_120;
	}

	const lv_img_dsc_t *get_img(const JackInput &) {
		pr_dbg("get_img->JackInput\n");
		return scale_px == 240 ? &jack_x : &jack_x_120;
	}
	const lv_img_dsc_t *get_img(const PJ301MPortIn &) {
		pr_dbg("get_img->PJ301MPort\n");
		return scale_px == 240 ? &jack_x : &jack_x_120;
	}
	const lv_img_dsc_t *get_img(const PJ301MPortOut &) {
		pr_dbg("get_img->PJ301MPort\n");
		return scale_px == 240 ? &jack_x : &jack_x_120;
	}
	const lv_img_dsc_t *get_img(const BefacoInputPort &) {
		pr_dbg("get_img->BananaRed\n");
		return scale_px == 240 ? &BananaBlack_240 : &BananaBlack_120;
	}
	const lv_img_dsc_t *get_img(const JackOutput &) {
		pr_dbg("get_img->JackOutput\n");
		return scale_px == 240 ? &jack_x : &jack_x_120;
	}
	const lv_img_dsc_t *get_img(const BefacoOutputPort &) {
		pr_dbg("get_img->BananaRed\n");
		return scale_px == 240 ? &BananaRed_240 : &BananaRed_120;
	}
	const lv_img_dsc_t *get_img(const MediumLight<RedGreenBlueLight> &) {
		pr_dbg("get_img->MediumLight<RedGreenBlueLight>\n");
		return scale_px == 240 ? &MediumLight_240 : &MediumLight_120;
	}

	const lv_img_dsc_t *get_img(const BraidsDisplay148x56 &) {
		pr_dbg("get_img->BraidsDisplay148x56\n");
		return scale_px == 240 ? &braids_display_240 : &braids_display_240;
	}
};

} // namespace MetaModule
