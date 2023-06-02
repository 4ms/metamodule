#pragma once
#include "CoreModules/elements.hh"
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

	const lv_img_dsc_t *get_img(const Element &) {
		return nullptr;
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
		// return scale_px == 240 ? &BananaBlack : &jack_x_120; //FIXME: _120px
		return scale_px == 240 ? &jack_x : &jack_x_120; //FIXME: _120px
	}

	const lv_img_dsc_t *get_img(const OutJackElement &) {
		return scale_px == 240 ? &jack_x : &jack_x_120;
	}
	const lv_img_dsc_t *get_img(const JackOutput &) {
		return scale_px == 240 ? &jack_x : &jack_x_120;
	}
	const lv_img_dsc_t *get_img(const BefacoOutputPort &) {
		// 	return scale_px == 240 ? &BananaRed : &BananaRed; //FIXME: _120px
		return scale_px == 240 ? &jack_x : &jack_x_120;
	}

	struct Rect {
		uint32_t left, top, width, height;
	};

	std::pair<uint32_t, uint32_t> get_left_top(const BaseElement &el, float width, float height) {
		auto left = static_cast<uint32_t>(std::round(ElementInfoBase::mm_to_px(el.x_mm, scale_px) - width / 2.f));
		auto top = static_cast<uint32_t>(std::round(ElementInfoBase::mm_to_px(el.y_mm, scale_px) - height / 2.f));
		return {left, top};
	}
};

struct ElementAnimMethod {
	// clang-format off
	auto operator()(const BaseElement) { return DrawHelper::ParamAnimMethods::None; }
	auto operator()(const Knob) { return DrawHelper::ParamAnimMethods::RotaryPot; }
	auto operator()(const Slider) { return DrawHelper::ParamAnimMethods::LinearSlider; }
	auto operator()(const Toggle2pos) { return DrawHelper::ParamAnimMethods::Toggle2pos; }
	auto operator()(const Toggle3pos) { return DrawHelper::ParamAnimMethods::Toggle3pos; }
	auto operator()(const Encoder) { return DrawHelper::ParamAnimMethods::Encoder; }
	auto operator()(const MomentaryButton) { return DrawHelper::ParamAnimMethods::MomentaryButton; }
	auto operator()(const LatchingButton) { return DrawHelper::ParamAnimMethods::LatchingButton; }
	// clang-format on
};

struct ElementDrawHelper {

	static std::pair<lv_obj_t *, uint32_t>
	draw_module_element(lv_obj_t *base, const Element &element, uint32_t module_height) {
		ElementImage image_helper{module_height};

		auto img = std::visit([&](auto &el) { return image_helper.get_img(el); }, element);
		if (!img)
			return {nullptr, 0};

		auto el = std::visit([&](auto &el) { return static_cast<BaseElement>(el); }, element);

		uint32_t width = img->header.w;
		uint32_t height = img->header.h;
		uint32_t left = std::round(ElementInfoBase::mm_to_px(el.x_mm, module_height) - width / 2.f);
		uint32_t top = std::round(ElementInfoBase::mm_to_px(el.y_mm, module_height) - height / 2.f);

		lv_obj_t *obj = lv_img_create(base);
		lv_img_set_src(obj, img);
		lv_obj_set_pos(obj, left, top);
		lv_img_set_pivot(obj, width / 2, height / 2);
		lv_obj_add_style(obj, &Gui::mapped_knob_style, LV_PART_MAIN);

		return {obj, el.idx};
	}
};
} // namespace MetaModule
