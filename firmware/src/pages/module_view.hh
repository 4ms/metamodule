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

	void init() override {
		base = lv_obj_create(nullptr, nullptr);
		module_img = lv_img_create(base, nullptr);
		lv_obj_set_pos(module_img, 0, 0);
		lv_obj_set_size(module_img, (Info::width_hp * 9.488f), 240); // TODO: get image width?
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

		// All buttons
		int i = 0;
		for (const auto kn : Info::Knobs) {
			button[i] = lv_btn_create(base, nullptr);
			lv_obj_add_style(button[i], LV_BTN_PART_MAIN, &button_style);
			lv_obj_set_pos(button[i], Info::mm_to_px<240>(kn.x_mm), Info::mm_to_px<240>(kn.y_mm));
			lv_obj_set_size(button[i], 13, 13);
			i++;
		}
		// Repeat for Jacks, Switches
		// Then sort by top-left (maybe floor(top, 20px) ?)

		roller = lv_roller_create(base, nullptr);
		lv_style_reset(&roller_style);
		lv_style_set_radius(&roller_style, LV_STATE_DEFAULT, 5);
		lv_style_set_bg_color(&roller_style, LV_STATE_DEFAULT, lv_color_make(0x00, 0x00, 0x00));
		lv_style_set_bg_grad_color(&roller_style, LV_STATE_DEFAULT, lv_color_make(0x00, 0x00, 0x00));
		lv_style_set_bg_grad_dir(&roller_style, LV_STATE_DEFAULT, LV_GRAD_DIR_VER);
		lv_style_set_bg_opa(&roller_style, LV_STATE_DEFAULT, 255);
		lv_style_set_border_color(&roller_style, LV_STATE_DEFAULT, lv_color_make(0xdf, 0xe7, 0xed));
		lv_style_set_border_width(&roller_style, LV_STATE_DEFAULT, 0);
		lv_style_set_text_color(&roller_style, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
		lv_obj_add_style(roller, LV_ROLLER_PART_BG, &roller_style);
		//
		// Write style LV_ROLLER_PART_SELECTED for module_test_small_roller_2
		// static lv_style_t style_module_test_small_roller_2_selected;
		// lv_style_reset(&style_module_test_small_roller_2_selected);

		////Write style state: LV_STATE_DEFAULT for style_module_test_small_roller_2_selected
		// lv_style_set_bg_color(&style_module_test_small_roller_2_selected, LV_STATE_DEFAULT, lv_color_make(0xff, 0xc3,
		// 0x70)); lv_style_set_bg_grad_color(&style_module_test_small_roller_2_selected, LV_STATE_DEFAULT,
		// lv_color_make(0xff, 0xc3, 0x70)); lv_style_set_bg_grad_dir(&style_module_test_small_roller_2_selected,
		// LV_STATE_DEFAULT, LV_GRAD_DIR_VER); lv_style_set_bg_opa(&style_module_test_small_roller_2_selected,
		// LV_STATE_DEFAULT, 255); lv_style_set_text_color(&style_module_test_small_roller_2_selected, LV_STATE_DEFAULT,
		// lv_color_make(0x00, 0x00, 0x00)); lv_obj_add_style(ui->module_test_small_roller_2, LV_ROLLER_PART_SELECTED,
		// &style_module_test_small_roller_2_selected); lv_obj_set_pos(ui->module_test_small_roller_2, 248, 1);
		// lv_roller_set_options(ui->module_test_small_roller_2,"PARAM\n PARAM\n PARAM\n PARAM\n PARAM\n PARAM\n PARAM\n
		// PARAM\n PARAM\n PARAM\n PARAM\n PARAM\n PARAM\n PARAM\n PARAM\n PARAM\n PARAM\n PARAM\n PARAM\n PARAM\n
		// PARAM\n PARAM 1\nPARAM 2\nPARAM 3\nPARAM 4\nPARAM 5\nPARAM 6\nPARAM 7\nPARAM 8\nPARAM
		// 9\n",LV_ROLLER_MODE_INIFINITE); lv_obj_set_style_local_text_font(ui->module_test_small_roller_2,
		// LV_ROLLER_PART_BG, LV_STATE_DEFAULT, &lv_font_MuseoSansRounded_500_12);
		// lv_obj_set_style_local_text_font(ui->module_test_small_roller_2, LV_ROLLER_PART_BG, LV_STATE_FOCUSED,
		// &lv_font_MuseoSansRounded_700_12); lv_obj_set_style_local_text_font(ui->module_test_small_roller_2,
		// LV_ROLLER_PART_SELECTED, LV_STATE_DEFAULT, &lv_font_MuseoSansRounded_500_12);
		// lv_roller_set_visible_row_count(ui->module_test_small_roller_2,7);

		init_bg(base);

		// Event and group for roller
		// group = lv_group_create();
		lv_group_add_obj(group, ui->module_test_small_roller_2);
		lv_obj_set_event_cb(ui->module_test_small_roller_2, roller_cb);
	}
};

} // namespace MetaModule
