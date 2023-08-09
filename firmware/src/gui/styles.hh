#pragma once
#include "lvgl.h"
#include <array>
#include <span>

// LV_FONT_DECLARE(MuseoSansRounded_500_12);
// LV_FONT_DECLARE(MuseoSansRounded_700_12);
// LV_FONT_DECLARE(MuseoSansRounded_700_14);
// LV_FONT_DECLARE(MuseoSansRounded_700_16);
// LV_FONT_DECLARE(MuseoSansRounded_700_18);

extern "C" {
LV_FONT_DECLARE(ui_font_MuseoSansRounded50012);
LV_FONT_DECLARE(ui_font_MuseoSansRounded70014);
LV_FONT_DECLARE(ui_font_MuseoSansRounded70016);
}

// lvgl has prop1 and has_group fields out of order, thus not C++ friendly
#define LV_STYLE_CONST_CPP(prop_array)                                                                                 \
	lv_style_t {                                                                                                       \
		.v_p = {.const_props = prop_array}, .prop1 = LV_STYLE_PROP_ANY, .has_group = 0xFF,                             \
		.prop_cnt = (sizeof(prop_array) / sizeof((prop_array)[0])),                                                    \
	}

//constexpr helper
static constexpr lv_color16_t lv_color_make_rgb565(uint8_t r8, uint8_t g8, uint8_t b8) {
	return {{(uint8_t)((b8 >> 3) & 0x1FU), (uint8_t)((g8 >> 2) & 0x3FU), (uint8_t)((r8 >> 3) & 0x1FU)}};
}

namespace MetaModule
{

struct Gui {

	// standard roller
	static inline lv_style_t roller_style;
	static inline lv_style_t roller_sel_style;

	// removes border, outline, shadow
	static inline lv_style_t plain_border_style;

	// orange border
	static inline lv_style_t module_border_style;

	// transparent with no border, etc
	static inline lv_style_t invisible_style;

	// highlight a selected knob, jack, etc on a faceplate
	static inline lv_style_t panel_highlight_style;

	// highlight of a mapped knob, jack, etc on a faceplate
	static inline lv_style_t mapped_knob_style;
	static inline lv_draw_arc_dsc_t mapped_knob_arcdsc;
	static inline lv_draw_arc_dsc_t mapped_knob_small_arcdsc;
	static inline lv_draw_arc_dsc_t mapped_jack_arcdsc;
	static inline lv_draw_arc_dsc_t mapped_jack_small_arcdsc;

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
	static constexpr std::array<lv_color_t, 19> palette_main = {
		lv_color_make_rgb565(0xF4, 0x00, 0x00), // RED
		lv_color_make_rgb565(0xE9, 0x3E, 0x83), // PINK,
		lv_color_make_rgb565(0x9C, 0x27, 0xB0), // PURPLE,
		lv_color_make_rgb565(0x67, 0x3A, 0xB7), // DEEP_PURPLE,
		lv_color_make_rgb565(0x3F, 0x51, 0xB5), // INDIGO,
		lv_color_make_rgb565(0x21, 0x96, 0xF3), // BLUE,
		lv_color_make_rgb565(0x03, 0xA9, 0xF4), // LIGHT_BLUE,
		lv_color_make_rgb565(0x00, 0xBC, 0xD4), // CYAN,
		lv_color_make_rgb565(0x00, 0x96, 0x88), // TEAL,
		lv_color_make_rgb565(0x4C, 0xAF, 0x50), // GREEN,
		lv_color_make_rgb565(0x8B, 0xC3, 0x4A), // LIGHT_GREEN,
		lv_color_make_rgb565(0xCD, 0xDC, 0x39), // LIME,
		lv_color_make_rgb565(0xFF, 0xEB, 0x3B), // YELLOW,
		lv_color_make_rgb565(0xFF, 0xC1, 0x07), // AMBER,
		lv_color_make_rgb565(0xFF, 0x98, 0x00), // ORANGE,
		lv_color_make_rgb565(0xFF, 0x57, 0x22), // DEEP_ORANGE,
		lv_color_make_rgb565(0x79, 0x55, 0x48), // BROWN,
		lv_color_make_rgb565(0x60, 0x7D, 0x8B), // BLUE_GREY,
		lv_color_make_rgb565(0x9E, 0x9E, 0x9E),
	}; // GREY,

	static inline std::array<lv_color_t, 8> knob_palette{
		palette_main[LV_PALETTE_RED],
		palette_main[LV_PALETTE_YELLOW],
		palette_main[LV_PALETTE_CYAN],
		palette_main[LV_PALETTE_PINK],
		palette_main[LV_PALETTE_ORANGE],
		palette_main[LV_PALETTE_GREEN],
		palette_main[LV_PALETTE_GREY],		//?
		palette_main[LV_PALETTE_BLUE_GREY], //?
	};

	// Slider Handle Style
	static constexpr lv_style_const_prop_t slider_handle_style_props[8] = {
		LV_STYLE_CONST_BG_OPA(LV_OPA_100),
		LV_STYLE_CONST_BG_COLOR(lv_color_make_rgb565(0xFF, 0xFF, 0xFF)),
		LV_STYLE_CONST_OUTLINE_OPA(LV_OPA_100),
		LV_STYLE_CONST_OUTLINE_COLOR(lv_color_make_rgb565(0x80, 0x80, 0x80)),
		LV_STYLE_CONST_OUTLINE_WIDTH(1),
		LV_STYLE_CONST_BORDER_COLOR(lv_color_make_rgb565(0, 0, 0)),
		LV_STYLE_CONST_BORDER_WIDTH(1),
		LV_STYLE_CONST_RADIUS(2),
	};
	static inline auto slider_handle_style = LV_STYLE_CONST_CPP(slider_handle_style_props);

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

		lv_draw_arc_dsc_init(&mapped_jack_arcdsc);
		mapped_jack_arcdsc.width = 2;
		mapped_jack_arcdsc.color = palette_main[LV_PALETTE_RED];
		mapped_jack_arcdsc.opa = LV_OPA_50;

		lv_draw_arc_dsc_init(&mapped_jack_small_arcdsc);
		mapped_jack_small_arcdsc.width = 2;
		mapped_jack_small_arcdsc.color = lv_palette_main(LV_PALETTE_RED);
		mapped_jack_small_arcdsc.opa = LV_OPA_50;

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
		lv_style_set_text_font(&header_style, &ui_font_MuseoSansRounded70016);
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
		lv_style_set_text_font(&text_block_style, &ui_font_MuseoSansRounded50012);
		lv_style_set_text_color(&text_block_style, lv_color_white());
		lv_style_set_text_opa(&text_block_style, LV_OPA_COVER);
		lv_style_set_bg_opa(&text_block_style, LV_OPA_COVER);
		lv_style_set_bg_color(&text_block_style, lv_color_black());
		lv_style_set_text_line_space(&text_block_style, 2);
		lv_style_set_pad_hor(&text_block_style, 8);
		lv_style_set_pad_ver(&text_block_style, 4);

		// button_label_style
		lv_style_init(&button_label_style);
		lv_style_set_text_font(&button_label_style, &ui_font_MuseoSansRounded70014);
		lv_style_set_text_color(&button_label_style, lv_color_white());
		lv_style_set_text_opa(&button_label_style, LV_OPA_COVER);
		lv_style_set_pad_ver(&button_label_style, 1);

		// roller_style
		lv_style_init(&roller_style);
		lv_style_set_radius(&roller_style, 0);
		lv_style_set_bg_opa(&roller_style, LV_OPA_COVER);
		lv_style_set_bg_color(&roller_style, lv_color_black());
		lv_style_set_text_align(&roller_style, LV_TEXT_ALIGN_LEFT);
		lv_style_set_text_font(&roller_style, &ui_font_MuseoSansRounded70014);
		// lv_style_set_text_font(&roller_style, &lv_font_montserrat_14);
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

		//module border
		lv_style_init(&module_border_style);
		lv_style_set_outline_width(&module_border_style, 1);
		lv_style_set_outline_color(&module_border_style, lv_palette_main(LV_PALETTE_ORANGE));
		lv_style_set_border_width(&module_border_style, 0);
		lv_style_set_shadow_opa(&module_border_style, LV_OPA_TRANSP);
		lv_style_set_pad_all(&module_border_style, 0);
		lv_style_set_pad_gap(&module_border_style, 0);

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

	static void style_menu_item_slider(lv_obj_t *panel, lv_obj_t *label, lv_obj_t *switchobj) {
		lv_obj_set_width(panel, 175);
		lv_obj_set_height(panel, 28);
		lv_obj_set_align(panel, LV_ALIGN_CENTER);
		lv_obj_set_flex_flow(panel, LV_FLEX_FLOW_ROW);
		lv_obj_set_flex_align(panel, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER);
		lv_obj_add_flag(panel, LV_OBJ_FLAG_OVERFLOW_VISIBLE);
		lv_obj_clear_flag(panel,
						  LV_OBJ_FLAG_CLICKABLE | LV_OBJ_FLAG_PRESS_LOCK | LV_OBJ_FLAG_CLICK_FOCUSABLE |
							  LV_OBJ_FLAG_GESTURE_BUBBLE | LV_OBJ_FLAG_SNAPPABLE | LV_OBJ_FLAG_SCROLL_ELASTIC |
							  LV_OBJ_FLAG_SCROLL_MOMENTUM | LV_OBJ_FLAG_SCROLL_CHAIN);
		lv_obj_set_style_radius(panel, 0, (uint32_t)LV_PART_MAIN | LV_STATE_DEFAULT);
		// lv_obj_set_style_bg_color(panel, lv_color_hex(0xFFFFFF), (uint32_t)LV_PART_MAIN | LV_STATE_DEFAULT);
		lv_obj_set_style_bg_opa(panel, 0, (uint32_t)LV_PART_MAIN | LV_STATE_DEFAULT);
		// lv_obj_set_style_border_color(panel, lv_color_hex(0x000000), (uint32_t)LV_PART_MAIN | LV_STATE_DEFAULT);
		// lv_obj_set_style_border_opa(panel, 0, (uint32_t)LV_PART_MAIN | LV_STATE_DEFAULT);
		lv_obj_set_style_border_width(panel, 0, (uint32_t)LV_PART_MAIN | LV_STATE_DEFAULT);
		lv_obj_set_style_pad_left(panel, 2, (uint32_t)LV_PART_MAIN | LV_STATE_DEFAULT);
		lv_obj_set_style_pad_right(panel, 0, (uint32_t)LV_PART_MAIN | LV_STATE_DEFAULT);
		lv_obj_set_style_pad_top(panel, 0, (uint32_t)LV_PART_MAIN | LV_STATE_DEFAULT);
		lv_obj_set_style_pad_bottom(panel, 0, (uint32_t)LV_PART_MAIN | LV_STATE_DEFAULT);
		// lv_obj_set_style_pad_row(panel, 0, (uint32_t)LV_PART_MAIN | LV_STATE_DEFAULT);
		// lv_obj_set_style_pad_column(panel, 8, (uint32_t)LV_PART_MAIN | LV_STATE_DEFAULT);

		lv_obj_set_width(label, 125);
		lv_obj_set_height(label, LV_SIZE_CONTENT);
		lv_obj_set_align(label, LV_ALIGN_LEFT_MID);
		lv_label_set_long_mode(label, LV_LABEL_LONG_SCROLL);
		lv_obj_clear_flag(label,
						  LV_OBJ_FLAG_PRESS_LOCK | LV_OBJ_FLAG_GESTURE_BUBBLE | LV_OBJ_FLAG_SNAPPABLE |
							  LV_OBJ_FLAG_SCROLLABLE | LV_OBJ_FLAG_SCROLL_ELASTIC | LV_OBJ_FLAG_SCROLL_MOMENTUM |
							  LV_OBJ_FLAG_SCROLL_CHAIN);
		lv_obj_set_style_text_color(label, lv_color_hex(0xEEEEEE), (uint32_t)LV_PART_MAIN | LV_STATE_DEFAULT);
		lv_obj_set_style_text_opa(label, 255, (uint32_t)LV_PART_MAIN | LV_STATE_DEFAULT);
		lv_obj_set_style_text_letter_space(label, 1, (uint32_t)LV_PART_MAIN | LV_STATE_DEFAULT);

		lv_obj_set_width(switchobj, 26);
		lv_obj_set_height(switchobj, 25);
		lv_obj_set_align(switchobj, LV_ALIGN_LEFT_MID);
		lv_obj_add_flag(switchobj, LV_OBJ_FLAG_SCROLL_ON_FOCUS | LV_OBJ_FLAG_OVERFLOW_VISIBLE);
		lv_obj_clear_flag(switchobj, LV_OBJ_FLAG_PRESS_LOCK | LV_OBJ_FLAG_GESTURE_BUBBLE);

		lv_obj_set_style_radius(switchobj, 14, (uint32_t)LV_PART_INDICATOR | LV_STATE_DEFAULT);
		lv_obj_set_style_bg_color(switchobj, lv_color_hex(0x202328), (uint32_t)LV_PART_INDICATOR | LV_STATE_DEFAULT);
		lv_obj_set_style_bg_opa(switchobj, 255, (uint32_t)LV_PART_INDICATOR | LV_STATE_DEFAULT);
		lv_obj_set_style_bg_color(switchobj, lv_color_hex(0x4067D3), (uint32_t)LV_PART_INDICATOR | LV_STATE_CHECKED);

		lv_obj_set_style_pad_left(switchobj, -6, (uint32_t)LV_PART_KNOB | LV_STATE_DEFAULT);
		lv_obj_set_style_pad_right(switchobj, -6, (uint32_t)LV_PART_KNOB | LV_STATE_DEFAULT);
		lv_obj_set_style_pad_top(switchobj, -6, (uint32_t)LV_PART_KNOB | LV_STATE_DEFAULT);
		lv_obj_set_style_pad_bottom(switchobj, -6, (uint32_t)LV_PART_KNOB | LV_STATE_DEFAULT);
	}
};
} // namespace MetaModule
