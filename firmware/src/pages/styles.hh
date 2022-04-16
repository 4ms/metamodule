#pragma once
#include "lvgl/lvgl.h"

LV_FONT_DECLARE(lv_font_MuseoSansRounded_700_14);
LV_FONT_DECLARE(lv_font_MuseoSansRounded_700_16);

namespace MetaModule
{

struct Gui {
	static inline lv_style_t button_style;
	static inline lv_style_t roller_style;
	static inline lv_style_t plain_border_style;
	static inline lv_style_t roller_sel_style;
	static inline lv_style_t panel_highlight_style;
	static inline lv_style_t header_style;

	static inline lv_color_t orange_highlight = lv_palette_lighten(LV_PALETTE_ORANGE, 2);

	static inline lv_theme_t *theme;
	static inline lv_disp_t *display;

	static void init_lvgl_styles() {
		// Style for invisible buttons over the components
		lv_style_reset(&button_style);
		lv_style_set_bg_opa(&button_style, 0);
		lv_style_set_border_opa(&button_style, 0);
		lv_style_set_outline_opa(&button_style, 0);

		// Style for the component button when selected
		lv_style_init(&panel_highlight_style);
		lv_style_set_radius(&panel_highlight_style, 120);
		lv_style_set_outline_color(&panel_highlight_style, orange_highlight);
		lv_style_set_outline_width(&panel_highlight_style, 4);
		lv_style_set_outline_opa(&panel_highlight_style, 255);

		// Header text
		lv_style_init(&header_style);
		lv_style_set_text_align(&header_style, LV_TEXT_ALIGN_CENTER);
		lv_style_set_text_font(&header_style, &lv_font_MuseoSansRounded_700_16);
		lv_style_set_text_color(&header_style, lv_color_white());
		lv_style_set_text_opa(&header_style, LV_OPA_COVER);
		lv_style_set_bg_opa(&header_style, LV_OPA_COVER);
		lv_style_set_bg_color(&header_style, lv_color_black());
		// lv_style_set_text_line_space(&header_style, 5);

		// Roller
		lv_style_reset(&roller_style);
		lv_style_set_radius(&roller_style, 0);
		lv_style_set_bg_opa(&roller_style, LV_OPA_COVER);
		lv_style_set_bg_color(&roller_style, lv_color_black());
		lv_style_set_text_align(&roller_style, LV_TEXT_ALIGN_CENTER);
		lv_style_set_text_font(&roller_style, &lv_font_MuseoSansRounded_700_14);
		lv_style_set_text_color(&roller_style, lv_color_white());
		lv_style_set_text_opa(&roller_style, LV_OPA_COVER);
		lv_style_set_text_line_space(&roller_style, 5);
		lv_style_set_pad_hor(&roller_style, 2);
		lv_style_set_pad_ver(&roller_style, 1);
		lv_style_set_pad_gap(&roller_style, 2);
		lv_style_set_line_color(&roller_style, lv_palette_main(LV_PALETTE_GREY));
		lv_style_set_line_width(&roller_style, 12);

		lv_style_reset(&roller_sel_style);
		lv_style_set_bg_color(&roller_sel_style, lv_palette_main(LV_PALETTE_ORANGE));
		lv_style_set_bg_opa(&roller_sel_style, LV_OPA_COVER);
		lv_style_set_text_color(&roller_sel_style, lv_color_black());
		lv_style_set_border_width(&roller_sel_style, 0);

		lv_style_reset(&plain_border_style);
		lv_style_set_border_width(&plain_border_style, 0);
		lv_style_set_outline_width(&plain_border_style, 0);
		lv_style_set_shadow_opa(&plain_border_style, LV_OPA_TRANSP);

		// display = ...
		// theme = lv_theme_default_init(display, // NOLINT
		// 							  lv_palette_main(LV_PALETTE_BLUE),
		// 							  lv_palette_main(LV_PALETTE_GREY),
		// 							  true,
		// 							  &lv_font_MuseoSansRounded_700_12);
		// lv_disp_set_theme(display, theme);
	}
};
} // namespace MetaModule
