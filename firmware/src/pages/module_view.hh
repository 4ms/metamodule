#pragma once
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

	ModuleViewPage(PatchInfo info, std::string_view module_slug = "EnOsc")
		: PageBase{info}
		, base(lv_obj_create(nullptr))
		, canvas(lv_canvas_create(base))
		, slug(module_slug) {

		_instance = this;
		_init_styles();
		init_bg(base);
		lv_canvas_set_buffer(canvas, buffer, 240, 240, LV_IMG_CF_TRUE_COLOR_ALPHA);
		lv_draw_img_dsc_init(&img_dsc);
		img_dsc.opa = LV_OPA_COVER;

		roller = lv_roller_create(base);
		lv_group_add_obj(group, roller);
		lv_obj_add_event_cb(roller, roller_cb, LV_EVENT_KEY, nullptr);

		button.clear();

		lv_obj_add_style(roller, &roller_style, LV_PART_MAIN);		   //LV_ROLLER_PART_BG
		lv_obj_add_style(roller, &roller_sel_style, LV_PART_SELECTED); //LV_ROLLER_PART_SELECTED
	}

	void load_module_page(std::string_view module_slug) {
		for (auto &b : button) {
			lv_obj_del(b);
		}
		button.clear();
		opts.clear();
		set_slug(module_slug);
		init();
	}

	void set_slug(std::string_view module_slug) {
		slug = module_slug;
	}

	void init() override {

		//Draw module image
		const lv_img_dsc_t *img = ModuleImages::get_image_by_slug(slug);
		auto width_px = img->header.w;
		// auto height_px = img->header.h; // assert == 240?
		lv_canvas_fill_bg(canvas, lv_color_make(0, 0, 0), LV_OPA_COVER);
		lv_canvas_draw_img(canvas, 0, 0, img, &img_dsc);

		//Create text list (roller options) and buttons over components

		auto info = ModuleFactory::getModuleInfo(slug);
		if (info.width_hp == 0) {
			mbox.append_message("Module View page got empty module slug.\r\n");
			return;
		}

		size_t num_controls = info.InJacks.size() + info.OutJacks.size() + info.Knobs.size() + info.Switches.size();
		opts.reserve(num_controls * 12);
		button.reserve(num_controls);

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

		lv_obj_set_pos(roller, width_px, 0);
		lv_obj_set_size(roller, 320 - width_px, 240);

		// Add text list to roller options
		lv_roller_set_options(roller, opts.c_str(), LV_ROLLER_MODE_NORMAL);
		lv_roller_set_visible_row_count(roller, 11);

		//Select first element
		lv_roller_set_selected(roller, 0, LV_ANIM_OFF);
		cur_selected = 0;
		lv_obj_add_style(button[cur_selected], &style_highlight, LV_PART_MAIN); //LV_BTN_PART_MAIN
	}

	void update() override {
	}

private:
	static inline ModuleViewPage *_instance;

	static inline lv_style_t button_style;
	static inline lv_style_t roller_style;
	static inline lv_style_t roller_sel_style;
	static inline lv_style_t style_highlight;

	// static inline lv_color_t orange_highlight = lv_color_make(0xff, 0xd6, 0x00);
	static inline lv_color_t orange_highlight = lv_color_make(0xff, 0xc3, 0x70);

	std::string opts;
	int32_t cur_selected = 0;
	std::vector<lv_obj_t *> button;
	lv_obj_t *roller = nullptr;
	lv_obj_t *base = nullptr;
	lv_color_t buffer[LV_CANVAS_BUF_SIZE_TRUE_COLOR_ALPHA(240, 240)];
	lv_obj_t *canvas = nullptr;
	lv_draw_img_dsc_t img_dsc;

	std::string_view slug;

	static void roller_cb(lv_event_t *event) {
		auto obj = _instance->roller;

		auto &but = _instance->button;

		// Turn off old button
		if (_instance->cur_selected >= 0) {
			lv_obj_remove_style(but[_instance->cur_selected], &_instance->style_highlight, LV_PART_MAIN);
			lv_event_send(but[_instance->cur_selected], LV_EVENT_REFRESH, nullptr);
		}

		// Get the new button
		_instance->cur_selected = lv_roller_get_selected(obj);
		char buf[48];
		lv_roller_get_selected_str(_instance->roller, buf, 48);
		// printf("moduleview: cur_selected: %d = %s\r\n", _instance->cur_selected, buf);

		// Turn on new button
		lv_obj_add_style(but[_instance->cur_selected], &_instance->style_highlight, LV_PART_MAIN);
		lv_event_send(but[_instance->cur_selected], LV_EVENT_REFRESH, nullptr);
	}

	void _add_button(int x, int y) {
		auto &b = button.emplace_back();
		b = lv_btn_create(base);
		lv_obj_add_style(b, &button_style, LV_PART_MAIN);
		lv_obj_set_pos(b, x - 6, y - 6);
		lv_obj_set_size(b, 12, 12);
	}

	void _init_styles() {

		// Style for invisible buttons over the components
		lv_style_reset(&button_style);
		lv_style_set_radius(&button_style, 50);
		lv_style_set_bg_color(&button_style, lv_color_white());
		lv_style_set_bg_grad_color(&button_style, lv_color_white());
		lv_style_set_bg_grad_dir(&button_style, LV_GRAD_DIR_VER);
		lv_style_set_bg_opa(&button_style, 0);
		lv_style_set_border_color(&button_style, lv_color_white());
		lv_style_set_border_width(&button_style, 2);
		lv_style_set_border_opa(&button_style, 0);
		lv_style_set_outline_color(&button_style, orange_highlight);
		lv_style_set_outline_opa(&button_style, 0);

		// Style for the component button when selected
		lv_style_init(&style_highlight);
		lv_style_set_radius(&style_highlight, 120);
		lv_style_set_outline_color(&style_highlight, orange_highlight);
		lv_style_set_outline_width(&style_highlight, 4);
		lv_style_set_outline_opa(&style_highlight, 255);

		// Style for roller items
		lv_style_reset(&roller_style);
		lv_style_set_radius(&roller_style, 0);
		lv_style_set_bg_opa(&roller_style, LV_OPA_COVER);
		lv_style_set_bg_color(&roller_style, lv_color_black());
		lv_style_set_border_color(&roller_style, lv_color_black());
		lv_style_set_border_width(&roller_style, 0);
		lv_style_set_border_post(&roller_style, false);
		lv_style_set_text_align(&roller_style, LV_TEXT_ALIGN_CENTER);
		// lv_style_set_text_font(&roller_style, &lv_font_MuseoSansRounded_700_12);
		lv_style_set_text_color(&roller_style, lv_palette_main(LV_PALETTE_GREY)); //lv_color_white());
		lv_style_set_text_opa(&roller_style, LV_OPA_COVER);
		lv_style_set_text_line_space(&roller_style, 5);
		lv_style_set_pad_hor(&roller_style, 2);
		lv_style_set_pad_ver(&roller_style, 1);
		lv_style_set_pad_gap(&roller_style, 2);
		lv_style_set_line_color(&roller_style, lv_palette_main(LV_PALETTE_GREY));
		lv_style_set_line_width(&roller_style, 1);

		// Style for roller selection
		lv_style_reset(&roller_sel_style);
		lv_style_set_bg_color(&roller_sel_style, lv_palette_main(LV_PALETTE_ORANGE));
		lv_style_set_text_color(&roller_sel_style, lv_color_black());
	}
};

} // namespace MetaModule
