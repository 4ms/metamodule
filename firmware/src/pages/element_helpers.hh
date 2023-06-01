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
LV_IMG_DECLARE(BananaBlack);
LV_IMG_DECLARE(BananaRed);
LV_IMG_DECLARE(Davies1900hRed);
LV_IMG_DECLARE(Davies1900hWhite);
LV_IMG_DECLARE(MediumLight);

namespace MetaModule
{
static std::pair<int, int> scale_center(auto el, float module_height) {
	const float adj = (float)(module_height) / 240.f;
	uint16_t x = std::round(ModuleInfoBase::mm_to_px<240>(el.x_mm) * adj);
	uint16_t y = std::round(ModuleInfoBase::mm_to_px<240>(el.y_mm) * adj);
	return std::make_pair(x, y);
}

static std::pair<int, int> scale_topleft(auto el, const lv_img_dsc_t *img, float size_adj) {
	auto x =
		static_cast<int>(std::round(ModuleInfoBase::mm_to_px<240>(el.x_mm) * size_adj - (float)img->header.w / 2.f));
	auto y =
		static_cast<int>(std::round(ModuleInfoBase::mm_to_px<240>(el.y_mm) * size_adj - (float)img->header.h / 2.f));
	return std::make_pair(x, y);
};

struct ElementImage {
	uint32_t scale_px;
	ElementImage(uint32_t module_height)
		: scale_px{module_height} {
	}

	const lv_img_dsc_t *get_img(const KnobElement &) {
		return &knob_x; //default knob
	}
	const lv_img_dsc_t *get_img(const Davies1900hWhiteKnob &) {
		return scale_px == 240 ? &Davies1900hWhite : &Davies1900hWhite; //FIXME: _120
	}
	const lv_img_dsc_t *get_img(const Davies1900hRedKnob &) {
		return scale_px == 240 ? &Davies1900hRed : &Davies1900hRed; //FIXME: _120
	}
	const lv_img_dsc_t *get_img(const Davies1900hBlackKnob &) {
		return scale_px == 240 ? &knob_x : &knob_x_120;
	}
	const lv_img_dsc_t *get_img(const DaviesLargeKnob &) {
		return scale_px == 240 ? &knob_large_x : &knob_large_x_120;
	}
	const lv_img_dsc_t *get_img(const Knob9mm &) {
		return scale_px == 240 ? &knob9mm_x : &knob9mm_x_120;
	}

	const lv_img_dsc_t *get_img(const InJackElement &) {
		return scale_px == 240 ? &jack_x : &jack_x_120;
	}
	const lv_img_dsc_t *get_img(const JackInput &) {
		return scale_px == 240 ? &jack_x : &jack_x_120;
	}
	const lv_img_dsc_t *get_img(const BefacoInputPort &) {
		return scale_px == 240 ? &BananaBlack : &BananaBlack; //FIXME: _120px
	}

	const lv_img_dsc_t *get_img(const OutJackElement &) {
		return scale_px == 240 ? &jack_x : &jack_x_120;
	}
	const lv_img_dsc_t *get_img(const JackOutput &) {
		return scale_px == 240 ? &jack_x : &jack_x_120;
	}
	const lv_img_dsc_t *get_img(const BefacoOutputPort &) {
		return scale_px == 240 ? &BananaRed : &BananaRed; //FIXME: _120px
	}

	// void draw(lv_obj_t *obj, uint32_t scale, Davies1900hRedKnob knob) {
	// }
	// void draw(lv_obj_t *obj, uint32_t scale, Davies1900hBlackKnob knob) {
	// }
};

struct ElementDrawHelper {

	static void draw_module_knobs(lv_obj_t *canvas,
								  const std::span<const KnobElement> knobs,
								  const PatchData &patch,
								  std::vector<DrawHelper::MKnob> &mapped_knobs,
								  uint32_t module_id,
								  uint32_t scale_px) {
		for (const auto &knob : knobs) {
			auto img = std::visit([&](auto &el) { return ElementImage{scale_px}.get_img(el); }, knob);

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
