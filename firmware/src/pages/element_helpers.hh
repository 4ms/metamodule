#pragma once
#include "CoreModules/elements/elements.hh"
#include "CoreModules/module_info_base.hh"
#include "draw_helpers.hh" //for std::vector<DrawHelper::MKnob> mapped_knobs,
#include "lvgl/lvgl.h"
#include "patch/patch_data.hh"

#include "printf.h"

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

namespace MetaModule
{
namespace
{
template<typename... Ts>
static void pr_dbg(Ts... args) {
	printf_(args...);
}
} // namespace

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
	const lv_img_dsc_t *get_img(const PJ301MPort &) {
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
};

struct ElementDrawer {
	uint32_t module_height;
	lv_obj_t *canvas;

	lv_obj_t *draw_element(const BaseElement &, const lv_img_dsc_t *) {
		pr_dbg("draw_element(BaseElement), not found\n");
		return nullptr;
	}

	// Pot -- create lvgl image object so it can be animated later
	lv_obj_t *draw_element(const Pot &el, const lv_img_dsc_t *img) {
		if (!img) {
			pr_dbg("draw_element(Pot), image not found\n");
			return nullptr;
		}
		uint32_t width = img->header.w;
		uint32_t height = img->header.h;
		// if x,y are top-left corner:
		uint32_t left = std::round(ElementInfoBase::mm_to_px(el.x_mm, module_height));
		uint32_t top = std::round(ElementInfoBase::mm_to_px(el.y_mm, module_height));
		// if x,y are center:
		// uint32_t left = std::round(ElementInfoBase::mm_to_px(el.x_mm, module_height) - width / 2.f);
		// uint32_t top = std::round(ElementInfoBase::mm_to_px(el.y_mm, module_height) - height / 2.f);

		lv_obj_t *obj = lv_img_create(canvas);
		lv_img_set_src(obj, img);
		lv_obj_set_pos(obj, left, top);
		lv_img_set_pivot(obj, width / 2, height / 2);
		lv_obj_add_style(obj, &Gui::mapped_knob_style, LV_PART_MAIN);
		pr_dbg("Draw pot at %d, %d (w:%d h:%d) module_height=%d\n", left, top, width, height, module_height);
		return obj;
	}

	// Jack -- draw knob on canvas
	lv_obj_t *draw_element(const JackElement &el, const lv_img_dsc_t *img) {
		if (!img) {
			pr_dbg("draw_element(JackElement), image not found\n");
			return nullptr;
		}
		uint32_t width = img->header.w;
		uint32_t height = img->header.h;
		uint32_t left = std::round(ElementInfoBase::mm_to_px(el.x_mm, module_height));
		uint32_t top = std::round(ElementInfoBase::mm_to_px(el.y_mm, module_height));

		lv_draw_img_dsc_t draw_img_dsc;
		lv_draw_img_dsc_init(&draw_img_dsc);
		lv_canvas_draw_img(canvas, left, top, img, &draw_img_dsc);

		pr_dbg("Draw jack at %d, %d (w:%d h:%d) module_height=%d\n", left, top, width, height, module_height);

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

		uint16_t c_x = std::round(ElementInfoBase::mm_to_px(el.x_mm, module_height) + img->header.w / 2.f);
		uint16_t c_y = std::round(ElementInfoBase::mm_to_px(el.y_mm, module_height) + img->header.h / 2.f);

		ring.color = Gui::knob_palette[panel_knob_id % 6];
		// TODO: how to draw MIDI maps?

		ring.width = ring_thickness * scale;

		lv_canvas_draw_arc(canvas, c_x, c_y, radius, 0, 3600, &ring);
	}

	void draw_control_ring(const Slider &el, const lv_img_dsc_t *img, uint32_t panel_knob_id) {
		// Parameters for ring size
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
		uint16_t c_x = std::round(ElementInfoBase::mm_to_px(el.x_mm, module_height) + img->header.w / 2.f);
		uint16_t c_y = std::round(ElementInfoBase::mm_to_px(el.y_mm, module_height) + img->header.h / 2.f);

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
		if (!element_obj || !element_img)
			return;
		if (auto mapped_knob = patch.find_mapped_knob(module_idx, el.idx)) {
			mappings.knobs.push_back({element_obj, *mapped_knob, DrawHelper::RotaryPot});

			MapRingDrawer{module_height, canvas}.draw_control_ring(el, element_img, mapped_knob->panel_knob_id);
		}
	}
	//TODO: this is the same as Knob&, how to not repeat?
	void operator()(const Slider &el) {
		if (!element_obj || !element_img)
			return;
		if (auto mapped_knob = patch.find_mapped_knob(module_idx, el.idx)) {
			mappings.knobs.push_back({element_obj, *mapped_knob, DrawHelper::LinearSlider});

			MapRingDrawer{module_height, canvas}.draw_control_ring(el, element_img, mapped_knob->panel_knob_id);
		}
	}

	void operator()(const JackInput &el) {
		if (!element_img)
			return;
		if (auto mapped_jack = patch.find_mapped_injack(Jack{(uint16_t)module_idx, (uint16_t)el.idx})) {
			MapRingDrawer{module_height, canvas}.draw_jack_ring(el, element_img, mapped_jack->panel_jack_id);
		}
	}

	void operator()(const JackOutput &el) {
		if (!element_img)
			return;
		if (auto mapped_jack = patch.find_mapped_outjack(Jack{(uint16_t)module_idx, (uint16_t)el.idx})) {
			MapRingDrawer{module_height, canvas}.draw_jack_ring(el, element_img, mapped_jack->panel_jack_id);
		}
	}
};
} // namespace MetaModule
