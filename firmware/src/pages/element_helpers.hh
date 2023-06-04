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
};

struct ElementDrawer {
	uint32_t module_height;
	lv_obj_t *canvas;

	lv_obj_t *draw_element(const BaseElement &, const lv_img_dsc_t *) {
		return nullptr;
	}

	// Pot -- create lvgl image object so it can be animated later
	lv_obj_t *draw_element(const Pot &el, const lv_img_dsc_t *img) {
		uint32_t width = img->header.w;
		uint32_t height = img->header.h;
		uint32_t left = std::round(ElementInfoBase::mm_to_px(el.x_mm, module_height) - width / 2.f);
		uint32_t top = std::round(ElementInfoBase::mm_to_px(el.y_mm, module_height) - height / 2.f);

		lv_obj_t *obj = lv_img_create(canvas);
		lv_img_set_src(obj, img);
		lv_obj_set_pos(obj, left, top);
		lv_img_set_pivot(obj, width / 2, height / 2);
		lv_obj_add_style(obj, &Gui::mapped_knob_style, LV_PART_MAIN);

		return obj;
	}

	// Jack -- draw knob on canvas
	lv_obj_t *draw_element(const JackElement &el, const lv_img_dsc_t *img) {
		uint32_t width = img->header.w;
		uint32_t height = img->header.h;
		uint32_t left = std::round(ElementInfoBase::mm_to_px(el.x_mm, module_height) - width / 2.f);
		uint32_t top = std::round(ElementInfoBase::mm_to_px(el.y_mm, module_height) - height / 2.f);

		lv_draw_img_dsc_t draw_img_dsc;
		lv_draw_img_dsc_init(&draw_img_dsc);
		lv_canvas_draw_img(canvas, left, top, img, &draw_img_dsc);

		return nullptr;
	}
};

struct MapRingDrawer {
	uint32_t module_height;
	lv_obj_t *canvas;

	// Control Ring

	void draw_control_ring(const Knob &el, const lv_img_dsc_t *img, uint32_t panel_knob_id) {
		// Parameters for ring size
		constexpr float ring_offset = 8.f;
		// Thinner circle for uvwxyz small panel knobs
		const float ring_thickness = (panel_knob_id >= 6) ? 4.f : 10.f;

		lv_draw_arc_dsc_t ring;
		lv_draw_arc_dsc_init(&ring);
		ring.opa = LV_OPA_50;

		float scale = module_height / 240.f;
		float radius = img->header.w * 0.5f + ring_offset * scale;

		uint16_t c_x = std::round(ElementInfoBase::mm_to_px(el.x_mm, module_height));
		uint16_t c_y = std::round(ElementInfoBase::mm_to_px(el.y_mm, module_height));

		ring.color = Gui::knob_palette[panel_knob_id % 6];
		// TODO: how to draw MIDI maps?

		ring.width = ring_thickness * scale;

		lv_canvas_draw_arc(canvas, c_x, c_y, radius, 0, 3600, &ring);
	}

	void draw_control_ring(const Slider &el, const lv_img_dsc_t *img, uint32_t panel_knob_id) {
		// Parameters for ring size
		constexpr float ring_offset = 8.f;
		// Thinner circle for uvwxyz small panel knobs
		const float ring_thickness = (panel_knob_id >= 6) ? 4.f : 10.f;

		float scale = module_height / 240.f;

		lv_draw_rect_dsc_t ring;
		lv_draw_rect_dsc_init(&ring);
		ring.border_opa = LV_OPA_50;
		ring.border_width = ring_thickness * scale;
		ring.border_color = Gui::knob_palette[panel_knob_id % 6];
		ring.bg_opa = LV_OPA_0;
		ring.outline_opa = LV_OPA_0;
		ring.shadow_opa = LV_OPA_0;

		auto w = img->header.w;
		auto h = img->header.h;
		uint16_t x = std::round(ElementInfoBase::mm_to_px(el.x_mm, module_height) - w / 2.f);
		uint16_t y = std::round(ElementInfoBase::mm_to_px(el.y_mm, module_height) - h / 2.f);
		lv_canvas_draw_rect(canvas, x, y, w, h, &ring);
	}

	void draw_jack_ring(const JackElement &el, const lv_img_dsc_t *img, uint32_t panel_jack_id) {
		uint16_t c_x = std::round(ElementInfoBase::mm_to_px(el.x_mm, module_height));
		uint16_t c_y = std::round(ElementInfoBase::mm_to_px(el.y_mm, module_height));

		Gui::mapped_jack_small_arcdsc.color = Gui::palette_main[panel_jack_id % 8];
		uint16_t radius = (img->header.w + 6) / 2;
		lv_canvas_draw_arc(canvas, c_x, c_y, radius, 0, 3600, &Gui::mapped_jack_small_arcdsc);
	}
};

struct Mappings {
	std::vector<DrawHelper::MKnob> knobs;
};

struct MappedElement {
	uint32_t module_height;
	uint32_t module_idx;
	lv_obj_t *element_obj;
	lv_obj_t *canvas;
	const lv_img_dsc_t *element_img;
	const PatchData &patch;
	Mappings &mappings;

	void operator()(const BaseElement &) {
	}

	void operator()(const Knob &el) {
		if (!element_obj)
			return;
		if (auto mapped_knob = patch.find_mapped_knob(module_idx, el.idx)) {
			mappings.knobs.push_back({element_obj, *mapped_knob, DrawHelper::RotaryPot});

			MapRingDrawer{module_height, canvas}.draw_control_ring(el, element_img, mapped_knob->panel_knob_id);
		}
	}
	//TODO: this is the same as Knob&, how to not repeat?
	void operator()(const Slider &el) {
		if (!element_obj)
			return;
		if (auto mapped_knob = patch.find_mapped_knob(module_idx, el.idx)) {
			mappings.knobs.push_back({element_obj, *mapped_knob, DrawHelper::LinearSlider});

			MapRingDrawer{module_height, canvas}.draw_control_ring(el, element_img, mapped_knob->panel_knob_id);
		}
	}

	void operator()(const JackInput &el) {
		if (auto mapped_jack = patch.find_mapped_injack(Jack{(uint16_t)module_idx, (uint16_t)el.idx})) {
			MapRingDrawer{module_height, canvas}.draw_jack_ring(el, element_img, mapped_jack->panel_jack_id);
		}
	}
};
} // namespace MetaModule
