#pragma once
#include "CoreModules/info/EnOsc_info.hh"
#include "CoreModules/info/module_info_base.hh"
#include "pages/base.hh"
#include "pages/images/image_list.hh"
#include <string>

LV_IMG_DECLARE(jack_x);
LV_IMG_DECLARE(knob9mm_x);
LV_IMG_DECLARE(knob_x);
LV_IMG_DECLARE(button_x);
LV_IMG_DECLARE(knob_unlined_x);
LV_IMG_DECLARE(knob_large_x);
LV_IMG_DECLARE(slider_x);
LV_IMG_DECLARE(switch_left);
LV_IMG_DECLARE(switch_right);
LV_IMG_DECLARE(switch_up);
LV_IMG_DECLARE(switch_down);

namespace MetaModule
{
struct ModuleViewPage : PageBase {
	static inline lv_style_t style_highlight;
	static inline int32_t cur_selected = -1;
	static inline std::vector<lv_obj_t *> button;
	static inline lv_obj_t *base;
	static inline lv_obj_t *module_img;
	static inline lv_obj_t *roller;
	static inline lv_style_t button_style;
	static inline lv_style_t roller_style;
	static inline lv_style_t roller_sel_style;
	static inline std::string opts;

	static inline lv_color_t buffer[LV_CANVAS_BUF_SIZE_TRUE_COLOR_ALPHA(240, 240)];
	static inline lv_obj_t *canvas;
	static inline lv_draw_img_dsc_t img_dsc;

	std::string_view slug;

	ModuleViewPage(PatchInfo info)
		: PageBase{info}
		, slug{"EnOsc"} {
	}

	ModuleViewPage(PatchInfo info, std::string_view module_slug)
		: PageBase{info}
		, slug(module_slug) {
	}

	void load_module_page(std::string_view module_slug) {
		set_slug(module_slug);
		init();
	}

	void set_slug(std::string_view module_slug) {
		slug = module_slug;
	}

	void init() override {
		const lv_img_dsc_t *img = ModuleImages::get_image_by_slug(slug);
		auto width_px = img->header.w;
		auto height_px = img->header.h; // assert == 240?

		base = lv_obj_create(nullptr, nullptr);

		canvas = lv_canvas_create(base, nullptr);
		lv_canvas_set_buffer(canvas, buffer, width_px, height_px, LV_IMG_CF_TRUE_COLOR_ALPHA);
		lv_draw_img_dsc_init(&img_dsc);
		img_dsc.opa = LV_OPA_COVER;
		lv_canvas_draw_img(canvas, 0, 0, img, &img_dsc);

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

		// TODO: make buttons_ordered[] an ordered array of copies of the button[] ptrs, and browse using that
		// ... also need to sort the strngs, too.. hmm...
		opts.clear();
		auto info = ModuleFactory::getModuleInfo(slug);

		for (const auto el : info.Knobs) {
			int x = ModuleInfoBase::mm_to_px<240>(el.x_mm);
			int y = ModuleInfoBase::mm_to_px<240>(el.y_mm);
			_add_button(x, y);
			opts += el.short_name;
			opts += "\n";

			const lv_img_dsc_t *knob = nullptr;
			if (el.knob_style == KnobDef::Small)
				knob = &knob9mm_x;
			else if (el.knob_style == KnobDef::Medium)
				knob = &knob_x;
			else if (el.knob_style == KnobDef::Large)
				knob = &knob_large_x;
			else if (el.knob_style == KnobDef::Slider25mm)
				knob = &slider_x;
			else
				continue;
			lv_canvas_draw_img(canvas, x - knob->header.w / 2, y - knob->header.h / 2, knob, &img_dsc);
		}
		for (const auto el : info.InJacks) {
			int x = ModuleInfoBase::mm_to_px<240>(el.x_mm);
			int y = ModuleInfoBase::mm_to_px<240>(el.y_mm);
			_add_button(x, y);
			opts += el.short_name;
			opts += "\n";
			lv_canvas_draw_img(canvas, x - jack_x.header.w / 2, y - jack_x.header.h / 2, &jack_x, &img_dsc);
		}
		for (const auto el : info.OutJacks) {
			int x = ModuleInfoBase::mm_to_px<240>(el.x_mm);
			int y = ModuleInfoBase::mm_to_px<240>(el.y_mm);
			_add_button(x, y);
			opts += el.short_name;
			opts += "\n";
			lv_canvas_draw_img(canvas, x - jack_x.header.w / 2, y - jack_x.header.h / 2, &jack_x, &img_dsc);
		}
		for (const auto el : info.Switches) {
			int x = ModuleInfoBase::mm_to_px<240>(el.x_mm);
			int y = ModuleInfoBase::mm_to_px<240>(el.y_mm);
			_add_button(x, y);
			opts += el.short_name;
			opts += "\n";
			const lv_img_dsc_t *sw = nullptr;
			if (el.switch_type == SwitchDef::Toggle2pos || el.switch_type == SwitchDef::Toggle3pos)
				sw = &switch_left;
			else if (el.switch_type == SwitchDef::Encoder)
				sw = &knob_unlined_x;
			else if (el.switch_type == SwitchDef::MomentaryButton || el.switch_type == SwitchDef::LatchingButton)
				sw = &button_x;
			else
				continue;
			lv_canvas_draw_img(canvas, x - sw->header.w / 2, y - sw->header.h / 2, sw, &img_dsc);
		}

		// remove final \n
		if (opts.length() > 0)
			opts.pop_back();

		roller = lv_roller_create(base, nullptr);
		lv_obj_set_pos(roller, width_px, 1);

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

		// Roller font styles
		lv_obj_set_style_local_text_font(roller, LV_ROLLER_PART_BG, LV_STATE_DEFAULT, &lv_font_MuseoSansRounded_700_12);
		lv_obj_set_style_local_text_font(
			roller, LV_ROLLER_PART_SELECTED, LV_STATE_DEFAULT, &lv_font_MuseoSansRounded_700_12);
		lv_roller_set_align(roller, LV_ALIGN_CENTER);

		// Event and group for roller
		init_bg(base);
		lv_group_add_obj(group, roller);
		lv_obj_set_event_cb(roller, roller_cb);

		// Style for highlighted button
		lv_style_init(&style_highlight);
		lv_style_set_radius(&style_highlight, LV_STATE_DEFAULT, 120);
		lv_style_set_outline_color(&style_highlight, LV_STATE_DEFAULT, lv_color_make(0xff, 0xc3, 0x70));
		lv_style_set_outline_width(&style_highlight, LV_STATE_DEFAULT, 4);
		lv_style_set_outline_opa(&style_highlight, LV_STATE_DEFAULT, 255);

		// Add options
		lv_roller_set_options(roller, opts.c_str(), LV_ROLLER_MODE_NORMAL);
		lv_roller_set_visible_row_count(roller, 11);
	}

	void update() override {
	}

private:
	static void roller_cb(lv_obj_t *obj, lv_event_t event) {
		if (obj != roller)
			return;

		if (event == LV_EVENT_KEY) {
			// Turn off old button
			if (cur_selected >= 0) {
				lv_obj_remove_style(button[cur_selected], LV_BTN_PART_MAIN, &style_highlight);
				lv_event_send_refresh(button[cur_selected]);
			}

			// Get the new button
			cur_selected = lv_roller_get_selected(obj);
			printf("moduleview: cur_selected: %d\r\n", cur_selected);

			// Turn on new button
			lv_obj_add_style(button[cur_selected], LV_BTN_PART_MAIN, &style_highlight);
			lv_event_send_refresh(button[cur_selected]);
		}
	}

	void _add_button(int x, int y) {
		auto &b = button.emplace_back();
		b = lv_btn_create(base, nullptr);
		lv_obj_add_style(b, LV_BTN_PART_MAIN, &button_style);
		lv_obj_set_pos(b, x - 6, y - 6);
		lv_obj_set_size(b, 12, 12);
	}
};

} // namespace MetaModule
