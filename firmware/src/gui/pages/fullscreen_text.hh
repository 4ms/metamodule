#pragma once
#include "gui/elements/draw.hh"
#include "gui/elements/redraw_display.hh"
#include "gui/pages/base.hh"
#include "gui/pages/page_list.hh"

namespace MetaModule
{

struct FullscreenTextPage : PageBase {

	FullscreenTextPage(PatchContext info)
		: PageBase{info, PageId::FullscreenGraphic} {

		screen = lv_obj_create(NULL);
		lv_obj_clear_flag(screen, LV_OBJ_FLAG_SCROLLABLE);
		lv_obj_set_style_opa(screen, LV_OPA_100, LV_PART_MAIN);
		lv_obj_set_style_bg_color(screen, lv_color_black(), LV_PART_MAIN);
		lv_obj_set_size(screen, 320, 240);
		lv_obj_set_style_pad_all(screen, 0, LV_PART_MAIN);
		lv_obj_set_style_border_width(screen, 0, LV_PART_MAIN);
		lv_obj_set_style_outline_width(screen, 0, LV_PART_MAIN);

		lv_obj_clear_flag(screen, LV_OBJ_FLAG_SCROLLABLE);
		lv_obj_set_style_bg_opa(screen, LV_OPA_100, LV_PART_MAIN);

		label = lv_label_create(screen);

		init_bg(screen);
	}

	void prepare_focus() final {
		if (!patch_is_playing(args.patch_loc_hash))
			return;

		if (!args.module_id.has_value() || !args.element_indices.has_value())
			return;

		if (args.element_indices->light_idx == ElementCount::Indices::NoElementMarker)
			return;

		auto const *el = std::get_if<DynamicTextDisplay>(&args.element);
		if (!el)
			return;

		const float ratio = el->width_mm / el->height_mm;
		const float screen_ratio = 320.f / 240.f;
		uint16_t w = (ratio >= screen_ratio) ? 320 : std::round(240 * ratio);
		uint16_t h = (ratio <= screen_ratio) ? 240 : std::round(320 / ratio);

		lv_label_set_text(label, el->text.data());
		lv_obj_set_style_text_font(label, Fonts::get_font(el->font.data()), LV_PART_MAIN);
		lv_obj_set_style_text_color(label, lv_color_t{.full = el->color.raw()}, LV_PART_MAIN);

		lv_obj_set_size(label, w, h);
		lv_obj_align(label, LV_ALIGN_CENTER, 0, 0);
		lv_obj_refr_size(label);
		lv_obj_update_layout(label);

		light_idx = args.element_indices->light_idx;
		module_id = *args.module_id;

		// Debug border:
		// lv_obj_set_style_border_width(canvas, 1, LV_PART_MAIN);
		// lv_obj_set_style_border_color(canvas, lv_color_hex(0xff0000), LV_PART_MAIN);
		// lv_obj_set_style_border_opa(canvas, LV_OPA_50, LV_PART_MAIN);

		params.text_displays.stop_watching_all();
		params.text_displays.start_watching_display(*args.module_id, args.element_indices->light_idx);
	}

	void update() final {
		if (gui_state.back_button.is_just_released()) {
			page_list.request_last_page();
		}
		for (auto &disp : params.text_displays.watch_displays) {
			redraw_text_display(label, light_idx, module_id, disp);
		}
	}

	void blur() final {
		params.text_displays.stop_watching_all();
		lv_label_set_text(label, "");
		module_id = 0;
		light_idx = 0;
	}

private:
	lv_obj_t *screen;
	lv_obj_t *label;
	unsigned light_idx = 0;
	unsigned module_id = 0;
};

} // namespace MetaModule
