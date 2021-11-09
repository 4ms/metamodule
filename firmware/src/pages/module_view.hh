#pragma once
#include "CoreModules/info/enosc_info.hh"
#include "CoreModules/info/module_info_base.hh"
#include "pages/base.hh"

namespace MetaModule
{
struct ModuleViewPage : PageBase {
	using Info = EnOscInfo;

	static inline lv_style_t style_highlight;
	static inline int32_t cur_selected = -1;
	static inline lv_obj_t *button[Info::NumKnobs + Info::NumInJacks + Info::NumOutJacks + Info::NumSwitches];

	ModuleViewPage(PatchInfo info)
		: PageBase{info} {
	}

	static void roller_cb(lv_obj_t *obj, lv_event_t event) {
		if (obj != ui->module_test_small_roller_2)
			return;

		if (event == LV_EVENT_KEY) {
			// Turn off old button
			if (cur_selected >= 0) {
				lv_obj_remove_style(button[cur_selected], LV_BTN_PART_MAIN, &style_highlight);
				lv_event_send_refresh(button[cur_selected]);
			}

			// Get the new button
			cur_selected = lv_roller_get_selected(obj);
			printf("cur_selected: %d\r\n", cur_selected);

			// Turn on new button
			lv_obj_add_style(button[cur_selected], LV_BTN_PART_MAIN, &style_highlight);
			lv_event_send_refresh(button[cur_selected]);
		}
	}

	lv_obj_t *base;
	lv_obj_t *module_img;
	lv_obj_t *roller;
	lv_style_t button_style;
	lv_style_t roller_style;
	lv_style_t roller_sel_style;

	void init() override {
		constexpr auto width_px = static_cast<int>(Info::width_hp * 9.488f);
		base = lv_obj_create(nullptr, nullptr);
		module_img = lv_img_create(base, nullptr);
		lv_obj_set_pos(module_img, 0, 0);
		lv_obj_set_size(module_img, width_px, 240); // TODO: get image width?
		lv_obj_set_click(module_img, true);
		// TODO: get_image_from_slug: Info::slug
		// lv_img_set_src(module_img, &_module_graphic_SMR_small_alpha_246x240);
		lv_img_set_pivot(module_img, 0, 0);
		lv_img_set_angle(module_img, 0);

		// Button style
		lv_style_reset(&button_style);
		lv_style_set_radius(&button_style, LV_STATE_DEFAULT, 50);
		lv_style_set_bg_color(&button_style, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
		lv_style_set_bg_grad_color(&button_style, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
		lv_style_set_bg_grad_dir(&button_style, LV_STATE_DEFAULT, LV_GRAD_DIR_VER);
		lv_style_set_bg_opa(&button_style, LV_STATE_DEFAULT, 0);
		lv_style_set_border_color(&button_style, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
		lv_style_set_border_width(&button_style, LV_STATE_DEFAULT, 2);
		lv_style_set_border_opa(&button_style, LV_STATE_DEFAULT, 0);
		lv_style_set_outline_color(&button_style, LV_STATE_DEFAULT, lv_color_make(0xff, 0xd6, 0x00));
		lv_style_set_outline_opa(&button_style, LV_STATE_DEFAULT, 0);

		// TODO: combine Knobs+InJacks+OutJacks+Switches and sort by X/Y
		// then, do lv_btn_create, add_style, etc
		// Draw an element (or copy an img?) at each knob/jack/switch/button/slider position
		int i = 0;
		for (const auto kn : Info::Knobs) {
			button[i] = lv_btn_create(base, nullptr);
			lv_obj_add_style(button[i], LV_BTN_PART_MAIN, &button_style);
			lv_obj_set_pos(button[i], Info::mm_to_px<240>(kn.x_mm), Info::mm_to_px<240>(kn.y_mm));
			lv_obj_set_size(button[i], 13, 13);
			i++;
		}

		roller = lv_roller_create(base, nullptr);

		// Style for roller items
		lv_style_reset(&roller_style);
		lv_style_set_radius(&roller_style, LV_STATE_DEFAULT, 5);
		lv_style_set_bg_color(&roller_style, LV_STATE_DEFAULT, lv_color_make(0x00, 0x00, 0x00));
		lv_style_set_bg_grad_color(&roller_style, LV_STATE_DEFAULT, lv_color_make(0x00, 0x00, 0x00));
		lv_style_set_bg_grad_dir(&roller_style, LV_STATE_DEFAULT, LV_GRAD_DIR_VER);
		lv_style_set_bg_opa(&roller_style, LV_STATE_DEFAULT, 255);
		lv_style_set_border_color(&roller_style, LV_STATE_DEFAULT, lv_color_make(0xdf, 0xe7, 0xed));
		lv_style_set_border_width(&roller_style, LV_STATE_DEFAULT, 0);
		lv_style_set_text_color(&roller_style, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
		lv_style_set_pad_hor(&roller_style, LV_STATE_DEFAULT, 2);
		lv_style_set_pad_ver(&roller_style, LV_STATE_DEFAULT, 10);
		lv_style_set_pad_inner(&roller_style, LV_STATE_DEFAULT, 0);
		lv_style_set_text_line_space(&roller_style, LV_STATE_DEFAULT, 7);
		lv_obj_add_style(roller, LV_ROLLER_PART_BG, &roller_style);

		// Style for roller selection
		lv_style_reset(&roller_sel_style);
		lv_style_set_bg_color(&roller_sel_style, LV_STATE_DEFAULT, lv_color_make(0xff, 0xc3, 0x70));
		lv_style_set_bg_grad_color(&roller_sel_style, LV_STATE_DEFAULT, lv_color_make(0xff, 0xc3, 0x70));
		lv_style_set_bg_grad_dir(&roller_sel_style, LV_STATE_DEFAULT, LV_GRAD_DIR_VER);
		lv_style_set_bg_opa(&roller_sel_style, LV_STATE_DEFAULT, 255);
		lv_style_set_text_color(&roller_sel_style, LV_STATE_DEFAULT, lv_color_make(0x00, 0x00, 0x00));
		lv_style_set_pad_hor(&roller_sel_style, LV_STATE_DEFAULT, 2);
		lv_style_set_pad_ver(&roller_sel_style, LV_STATE_DEFAULT, 10);
		lv_style_set_pad_inner(&roller_sel_style, LV_STATE_DEFAULT, 0);
		lv_style_set_text_line_space(&roller_sel_style, LV_STATE_DEFAULT, 7);

		lv_obj_add_style(roller, LV_ROLLER_PART_SELECTED, &roller_sel_style);

		lv_obj_set_pos(roller, width_px, 1);

		lv_obj_set_style_local_text_font(roller, LV_ROLLER_PART_BG, LV_STATE_DEFAULT, &lv_font_MuseoSansRounded_700_12);
		lv_obj_set_style_local_text_font(
			roller, LV_ROLLER_PART_SELECTED, LV_STATE_DEFAULT, &lv_font_MuseoSansRounded_700_12);

		init_bg(base);

		// Event and group for roller
		lv_group_add_obj(group, roller);
		lv_obj_set_event_cb(roller, roller_cb);

		// Highlight for buttons
		lv_style_init(&style_highlight);
		lv_style_set_radius(&style_highlight, LV_STATE_DEFAULT, 120);
		lv_style_set_outline_color(&style_highlight, LV_STATE_DEFAULT, lv_color_make(0xff, 0xc3, 0x70));
		lv_style_set_outline_width(&style_highlight, LV_STATE_DEFAULT, 4);
		lv_style_set_outline_opa(&style_highlight, LV_STATE_DEFAULT, 200);

		// Add options
		lv_roller_set_align(roller, LV_ALIGN_CENTER);
		lv_roller_set_options(roller, "\n", LV_ROLLER_MODE_INFINITE);
		lv_roller_set_visible_row_count(roller, 7);
	}
};

} // namespace MetaModule
