#pragma once
// #include "gui-guider/guider_fonts.h"
#include "lvgl/lvgl.h"
#include <array>
// LV_FONT_DECLARE(lv_font_MuseoSansRounded_700_14);
// LV_FONT_DECLARE(lv_font_MuseoSansRounded_700_16);
LV_FONT_DECLARE(MuseoSansRounded_500_12);
LV_FONT_DECLARE(MuseoSansRounded_700_12);
LV_FONT_DECLARE(MuseoSansRounded_700_14);
LV_FONT_DECLARE(MuseoSansRounded_700_16);
LV_FONT_DECLARE(MuseoSansRounded_700_18);

namespace MetaModule
{

struct Gui {

	// standard roller
	static inline lv_style_t roller_style;
	static inline lv_style_t roller_sel_style;

	// removes border, outline, shadow
	static inline lv_style_t plain_border_style;
	// transparent with no border, etc
	static inline lv_style_t invisible_style;

	// highlight a selected knob, jack, etc on a faceplate
	static inline lv_style_t panel_highlight_style;

	// highlight of a mapped knob, jack, etc on a faceplate
	static inline lv_style_t mapped_knob_style;
	static inline lv_draw_arc_dsc_t mapped_knob_arcdsc;
	static inline lv_draw_arc_dsc_t mapped_knob_small_arcdsc;
	static inline lv_draw_arc_dsc_t mapped_injack_small_arcdsc;
	static inline lv_draw_arc_dsc_t mapped_outjack_small_arcdsc;

	// module selected in patch view
	static inline lv_style_t selected_module_style;

	// text
	static inline lv_style_t header_style;
	static inline lv_style_t button_label_style;
	static inline lv_style_t text_block_style;

	// popup dialog box
	static inline lv_style_t popup_box_style;

	// COLORS
	static inline lv_color_t orange_highlight = lv_palette_lighten(LV_PALETTE_ORANGE, 2);

	static inline lv_theme_t *theme;
	static inline lv_disp_t *display;

	static inline std::array<lv_color_t, 8> cable_palette{
		lv_palette_lighten(LV_PALETTE_RED, 1),
		lv_palette_lighten(LV_PALETTE_BLUE, 1),
		lv_palette_lighten(LV_PALETTE_GREEN, 1),
		lv_palette_lighten(LV_PALETTE_GREY, 1),
		lv_palette_lighten(LV_PALETTE_YELLOW, 1),
		lv_palette_lighten(LV_PALETTE_ORANGE, 1),
		lv_palette_lighten(LV_PALETTE_PINK, 1),
		lv_palette_lighten(LV_PALETTE_PURPLE, 1),
	};
	// const lv_style_const_prop_t style1_props[] = {
	// 	LV_STYLE_CONST_WIDTH(50),
	// 	LV_STYLE_CONST_HEIGHT(50),
	// 	LV_STYLE_PROP_INV,
	// };

	// LV_STYLE_CONST_INIT(style1, style1_props);

	static void init_lvgl_styles() {
		// invisible_style
		lv_style_init(&invisible_style);
		lv_style_set_bg_opa(&invisible_style, 0);
		lv_style_set_border_width(&invisible_style, 0);
		lv_style_set_outline_width(&invisible_style, 0);
		lv_style_set_shadow_opa(&invisible_style, 0);

		// panel_highlight_style
		lv_style_init(&panel_highlight_style);
		lv_style_set_radius(&panel_highlight_style, 120);
		lv_style_set_bg_color(&panel_highlight_style, orange_highlight);
		lv_style_set_bg_opa(&panel_highlight_style, LV_OPA_50);

		// mapped_knob_style
		lv_style_init(&mapped_knob_style);

		// Mapped arcs:
		lv_draw_arc_dsc_init(&mapped_knob_arcdsc);
		mapped_knob_arcdsc.width = 4;
		mapped_knob_arcdsc.color = lv_palette_main(LV_PALETTE_BLUE);
		mapped_knob_arcdsc.opa = LV_OPA_50;

		lv_draw_arc_dsc_init(&mapped_knob_small_arcdsc);
		mapped_knob_small_arcdsc.width = 2;
		mapped_knob_small_arcdsc.color = lv_palette_main(LV_PALETTE_BLUE);
		mapped_knob_small_arcdsc.opa = LV_OPA_50;

		lv_draw_arc_dsc_init(&mapped_injack_small_arcdsc);
		mapped_injack_small_arcdsc.width = 2;
		mapped_injack_small_arcdsc.color = lv_palette_main(LV_PALETTE_RED);
		mapped_injack_small_arcdsc.opa = LV_OPA_50;

		lv_draw_arc_dsc_init(&mapped_outjack_small_arcdsc);
		mapped_outjack_small_arcdsc.width = 2;
		mapped_outjack_small_arcdsc.color = lv_palette_lighten(LV_PALETTE_ORANGE, 1);
		mapped_outjack_small_arcdsc.opa = LV_OPA_50;

		// selected_module_style

		lv_style_init(&selected_module_style);
		lv_style_set_outline_color(&selected_module_style, lv_palette_lighten(LV_PALETTE_ORANGE, 1));
		lv_style_set_outline_width(&selected_module_style, 3);
		lv_style_set_outline_opa(&selected_module_style, LV_OPA_100);
		lv_style_set_radius(&selected_module_style, 0);

		// header_style (text)
		lv_style_init(&header_style);
		lv_style_set_text_align(&header_style, LV_TEXT_ALIGN_CENTER);
		// lv_style_set_text_font(&header_style, &lv_font_montserrat_14);
		lv_style_set_text_font(&header_style, &MuseoSansRounded_700_16);
		lv_style_set_text_color(&header_style, lv_color_white());
		lv_style_set_text_opa(&header_style, LV_OPA_COVER);
		lv_style_set_bg_opa(&header_style, LV_OPA_COVER);
		lv_style_set_bg_color(&header_style, lv_color_black());
		lv_style_set_text_line_space(&header_style, 5);
		lv_style_set_pad_hor(&header_style, 6);
		lv_style_set_pad_ver(&header_style, 2);

		// text_block_style
		lv_style_init(&text_block_style);
		lv_style_set_text_align(&text_block_style, LV_TEXT_ALIGN_LEFT);
		lv_style_set_text_font(&text_block_style, &MuseoSansRounded_500_12);
		lv_style_set_text_color(&text_block_style, lv_color_white());
		lv_style_set_text_opa(&text_block_style, LV_OPA_COVER);
		lv_style_set_bg_opa(&text_block_style, LV_OPA_COVER);
		lv_style_set_bg_color(&text_block_style, lv_color_black());
		lv_style_set_text_line_space(&text_block_style, 2);
		lv_style_set_pad_hor(&text_block_style, 8);
		lv_style_set_pad_ver(&text_block_style, 4);

		// button_label_style
		lv_style_init(&button_label_style);
		lv_style_set_text_font(&button_label_style, &MuseoSansRounded_700_14);
		lv_style_set_text_color(&button_label_style, lv_color_white());
		lv_style_set_text_opa(&button_label_style, LV_OPA_COVER);
		lv_style_set_pad_ver(&button_label_style, 1);

		// roller_style
		lv_style_init(&roller_style);
		lv_style_set_radius(&roller_style, 0);
		lv_style_set_bg_opa(&roller_style, LV_OPA_COVER);
		lv_style_set_bg_color(&roller_style, lv_color_black());
		lv_style_set_text_align(&roller_style, LV_TEXT_ALIGN_LEFT);
		lv_style_set_text_font(&roller_style, &MuseoSansRounded_700_14);
		lv_style_set_text_color(&roller_style, lv_color_white());
		lv_style_set_text_opa(&roller_style, LV_OPA_COVER);
		lv_style_set_text_line_space(&roller_style, 5);
		lv_style_set_pad_hor(&roller_style, 2);
		lv_style_set_pad_ver(&roller_style, 1);
		lv_style_set_pad_gap(&roller_style, 2);
		lv_style_set_line_color(&roller_style, lv_palette_main(LV_PALETTE_GREY));
		lv_style_set_line_width(&roller_style, 12);

		// roller_sel_style
		lv_style_init(&roller_sel_style);
		lv_style_set_bg_color(&roller_sel_style, lv_palette_main(LV_PALETTE_ORANGE));
		lv_style_set_bg_opa(&roller_sel_style, LV_OPA_COVER);
		lv_style_set_text_color(&roller_sel_style, lv_color_black());
		lv_style_set_border_width(&roller_sel_style, 0);

		// plain_border_style
		lv_style_init(&plain_border_style);
		lv_style_set_border_width(&plain_border_style, 0);
		lv_style_set_outline_width(&plain_border_style, 0);
		lv_style_set_shadow_opa(&plain_border_style, LV_OPA_TRANSP);

		//popup_box_style
		lv_style_init(&popup_box_style);
		lv_style_set_radius(&popup_box_style, 0);
		lv_style_set_bg_color(&popup_box_style, lv_palette_lighten(LV_PALETTE_GREY, 2));
		lv_style_set_bg_opa(&popup_box_style, 255);
		lv_style_set_border_width(&popup_box_style, 0);
		lv_style_set_border_opa(&popup_box_style, 0);
		lv_style_set_pad_gap(&popup_box_style, 10);
		lv_style_set_pad_all(&popup_box_style, 4);

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
