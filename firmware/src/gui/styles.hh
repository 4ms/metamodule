#pragma once
#include "lvgl.h"
#include "slsexport/meta5/ui.h"
#include <array>
#include <span>

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

	// standard roller: keep this to apply to DIY lists
	static inline lv_style_t roller_style;	   //X
	static inline lv_style_t roller_sel_style; //X

	// removes border, outline, shadow
	static inline lv_style_t plain_border_style;

	// orange border
	static inline lv_style_t module_border_style;

	// transparent with no border, etc
	static inline lv_style_t invisible_style;

	// highlight a selected knob, jack, etc on a faceplate
	static inline lv_style_t panel_highlight_style;

	// module selected in patch view
	static inline lv_style_t selected_module_style;

	// Volume or subdir name in Drives panel on PatchSelector
	static inline lv_style_t subdir_panel_item_style;
	static inline lv_style_t subdir_panel_item_sel_style;

	static inline lv_style_t mapped_circle_style;
	static inline lv_style_t mapped_jack_circle_label_style;

	static inline lv_style_t dropdown_style;
	static inline lv_style_t dropdown_style_main_checked;
	static inline lv_style_t dropdown_style_selected;

	// General outline for focused objects (FOCUS and FOCUS_KEY)
	static inline lv_style_t focus_style;

	// COLORS
	static inline lv_color_t orange_highlight = lv_color_hex(0xfd8b18);
	static inline const char *orange_highlight_html = "#fd8b18 ";
	static inline lv_color_t yellow_highlight = lv_color_hex(0x8bfd18);
	static inline const char *yellow_highlight_html = "#d7ff6a ";
	static inline const char *blue_highlight_html = "#188bfd ";
	static inline const char *brown_highlight_html = "#A26E3E ";

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
		lv_color_make_rgb565(0xF0, 0x63, 0x92), // PINK, F06392
		lv_color_make_rgb565(0x9C, 0x27, 0xB0), // PURPLE,
		lv_color_make_rgb565(0x67, 0x3A, 0xB7), // DEEP_PURPLE,
		lv_color_make_rgb565(0x3F, 0x51, 0xB5), // INDIGO,
		lv_color_make_rgb565(0x21, 0x96, 0xF3), // BLUE,
		lv_color_make_rgb565(0x03, 0xA9, 0xF4), // LIGHT_BLUE,
		lv_color_make_rgb565(0x00, 0xAD, 0xEE), // CYAN, 00ADEE
		lv_color_make_rgb565(0x00, 0x96, 0x88), // TEAL,
		lv_color_make_rgb565(0x00, 0xA5, 0x51), // GREEN, 00A551
		lv_color_make_rgb565(0x8B, 0xC3, 0x4A), // LIGHT_GREEN,
		lv_color_make_rgb565(0xCD, 0xDC, 0x39), // LIME,
		lv_color_make_rgb565(0xFF, 0xF1, 0x00), // YELLOW, FFF100
		lv_color_make_rgb565(0xFF, 0xC1, 0x07), // AMBER,
		lv_color_make_rgb565(0xFA, 0xA6, 0x29), // ORANGE, FAA629
		lv_color_make_rgb565(0xFF, 0x57, 0x22), // DEEP_ORANGE,
		lv_color_make_rgb565(0x79, 0x55, 0x48), // BROWN,
		lv_color_make_rgb565(0x60, 0x7D, 0x8B), // BLUE_GREY,
		lv_color_make_rgb565(0x9E, 0x9E, 0x9E), // GREY
	};

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
		LV_STYLE_CONST_OUTLINE_COLOR(lv_color_make_rgb565(0xC0, 0xC0, 0xC0)),
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
		lv_style_set_bg_opa(&panel_highlight_style, LV_OPA_20);
		lv_style_set_border_opa(&panel_highlight_style, LV_OPA_50);
		lv_style_set_border_width(&panel_highlight_style, 1);
		lv_style_set_border_color(&panel_highlight_style, orange_highlight);

		// selected_module_style
		lv_style_init(&selected_module_style);
		lv_style_set_outline_color(&selected_module_style, lv_palette_lighten(LV_PALETTE_ORANGE, 1));
		lv_style_set_outline_width(&selected_module_style, 3);
		lv_style_set_outline_opa(&selected_module_style, LV_OPA_100);
		lv_style_set_radius(&selected_module_style, 0);

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

		// Map circle
		lv_style_init(&mapped_circle_style);
		lv_style_set_radius(&mapped_circle_style, 40);
		lv_style_set_border_color(&mapped_circle_style, lv_color_white());
		lv_style_set_border_width(&mapped_circle_style, 12);
		lv_style_set_border_opa(&mapped_circle_style, LV_OPA_50);
		lv_style_set_bg_opa(&mapped_circle_style, LV_OPA_0);
		lv_style_set_outline_opa(&mapped_circle_style, LV_OPA_100);
		lv_style_set_outline_width(&mapped_circle_style, 3);
		lv_style_set_outline_pad(&mapped_circle_style, 0);
		lv_style_set_radius(&mapped_circle_style, 40);
		lv_style_set_text_color(&mapped_circle_style, lv_color_hex(0x000000));
		lv_style_set_text_opa(&mapped_circle_style, 255);
		lv_style_set_text_font(&mapped_circle_style, &ui_font_MuseoSansRounded50010);

		// Map circle label style for jacks
		lv_style_init(&mapped_jack_circle_label_style);
		lv_style_set_pad_left(&mapped_jack_circle_label_style, -2);
		lv_style_set_pad_right(&mapped_jack_circle_label_style, 0);
		lv_style_set_pad_top(&mapped_jack_circle_label_style, -1);
		lv_style_set_pad_bottom(&mapped_jack_circle_label_style, 0);

		// Subdir panel
		lv_style_init(&subdir_panel_item_style);
		lv_style_set_width(&subdir_panel_item_style, LV_PCT(100));
		lv_style_set_height(&subdir_panel_item_style, 20);
		lv_style_set_pad_top(&subdir_panel_item_style, 2);
		lv_style_set_pad_bottom(&subdir_panel_item_style, 0);
		lv_style_set_pad_right(&subdir_panel_item_style, 0);
		lv_style_set_pad_left(&subdir_panel_item_style, 12);
		lv_style_set_bg_opa(&subdir_panel_item_style, LV_OPA_0);
		lv_style_set_outline_width(&subdir_panel_item_style, 0);
		lv_style_set_border_width(&subdir_panel_item_style, 0);
		lv_style_set_radius(&subdir_panel_item_style, 0);

		lv_style_init(&subdir_panel_item_sel_style);
		lv_style_set_bg_color(&subdir_panel_item_sel_style, Gui::orange_highlight);
		lv_style_set_bg_opa(&subdir_panel_item_sel_style, LV_OPA_100);
		lv_style_set_outline_width(&subdir_panel_item_sel_style, 0);
		lv_style_set_border_width(&subdir_panel_item_sel_style, 0);

		// Dropdown
		lv_style_init(&dropdown_style);
		lv_style_set_bg_color(&dropdown_style, lv_color_hex(0x333333));
		lv_style_set_text_color(&dropdown_style, lv_color_white());
		lv_style_set_text_opa(&dropdown_style, 255);
		lv_style_set_text_font(&dropdown_style, &lv_font_montserrat_14);
		lv_style_set_pad_ver(&dropdown_style, 4);

		// Dropdown: Part Selected
		lv_style_init(&dropdown_style_selected);
		lv_style_set_bg_color(&dropdown_style_selected, orange_highlight);

		lv_style_init(&dropdown_style_main_checked);
		// lv_style_set_border_color(&dropdown_style_main_checked, lv_color_hex(0xFF00FF));
		// lv_style_set_border_opa(&dropdown_style_main_checked, LV_OPA_0);
		lv_style_set_outline_color(&dropdown_style_main_checked, orange_highlight);
		lv_style_set_outline_opa(&dropdown_style_main_checked, LV_OPA_100);
		lv_style_set_outline_width(&dropdown_style_main_checked, 0);
		lv_style_set_outline_pad(&dropdown_style_main_checked, 1);

		// Focus
		lv_style_init(&focus_style);
		lv_style_set_outline_color(&focus_style, orange_highlight);
		lv_style_set_outline_opa(&focus_style, LV_OPA_100);
		lv_style_set_outline_width(&focus_style, 3);
		lv_style_set_outline_pad(&focus_style, 2);
	}

	static lv_obj_t *create_map_circle(lv_obj_t *parent) {
		lv_obj_t *circle = lv_btn_create(parent);
		lv_obj_set_align(circle, LV_ALIGN_TOP_LEFT);
		lv_obj_add_flag(circle, LV_OBJ_FLAG_OVERFLOW_VISIBLE | LV_OBJ_FLAG_SCROLL_ON_FOCUS);
		lv_obj_clear_flag(circle,
						  LV_OBJ_FLAG_PRESS_LOCK | LV_OBJ_FLAG_CLICK_FOCUSABLE | LV_OBJ_FLAG_SCROLLABLE |
							  LV_OBJ_FLAG_SCROLL_CHAIN);
		lv_obj_add_style(circle, &mapped_circle_style, LV_PART_MAIN);

		lv_obj_t *label = lv_label_create(circle);
		lv_obj_set_width(label, LV_SIZE_CONTENT);
		lv_obj_set_height(label, LV_SIZE_CONTENT);
		lv_obj_set_align(label, LV_ALIGN_CENTER);

		lv_obj_add_style(label, &mapped_jack_circle_label_style, LV_PART_MAIN);

		return circle;
	}
};
} // namespace MetaModule
