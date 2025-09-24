#pragma once
#include "lvgl.h"
#include "patch-serial/patch/mapping_ids.hh"
#include "patch-serial/patch/midi_def.hh"
#include "patch-serial/patch/patch.hh"
#include "slsexport/meta5/ui.h"
#include <array>
#include <charconv>
#include <string>

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
	static inline lv_style_t panel_large_highlight_style;

	// module selected in patch view
	static inline lv_style_t selected_module_style;

	// Volume or subdir name in Drives panel on PatchSelector
	static inline lv_style_t subdir_panel_item_style;
	static inline lv_style_t subdir_panel_item_sel_style;
	static inline lv_style_t subdir_panel_item_sel_blurred_style;

	static inline lv_style_t mapped_circle_style;
	static inline lv_style_t mapped_jack_circle_label_style;

	static inline lv_style_t dropdown_style;
	static inline lv_style_t dropdown_style_main_checked;
	static inline lv_style_t dropdown_style_selected;

	// General outline for focused objects (FOCUS and FOCUS_KEY)
	static inline lv_style_t focus_style;

	static const lv_color_t orange_highlight;

	// COLORS
	static std::string color_text(std::string_view txt, std::string_view color) {
		return std::string{color} + std::string{txt} + LV_TXT_COLOR_CMD + " ";
	}

	static std::string red_text(std::string_view txt);
	static std::string orange_text(std::string_view txt);
	static std::string yellow_text(std::string_view txt);
	static std::string green_text(std::string_view txt);
	static std::string blue_text(std::string_view txt);
	static std::string grey_text(std::string_view txt);
	static std::string lt_grey_text(std::string_view txt);

	static inline lv_theme_t *theme;
	static inline lv_disp_t *display;

	static const lv_color_t palette[][5];

	static std::array<const lv_color_t, 19> palette_main;

	static lv_color_t get_knob_color(uint16_t panel_id);
	static lv_color_t get_jack_color(uint16_t panel_id);
	static lv_color_t get_buttonexp_color(float value);
	static lv_color_t get_buttonexp_textcolor(float value);
	static lv_color_t get_knob_indicator_color(uint16_t panel_id);

	// Slider Handle Style
	static constexpr lv_style_const_prop_t slider_handle_style_props[9] = {
		LV_STYLE_CONST_BG_OPA(LV_OPA_100),
		LV_STYLE_CONST_BG_COLOR(lv_color_make_rgb565(0x90, 0x90, 0x90)),
		LV_STYLE_CONST_OUTLINE_OPA(LV_OPA_100),
		LV_STYLE_CONST_OUTLINE_COLOR(lv_color_make_rgb565(0xC0, 0xC0, 0xC0)),
		LV_STYLE_CONST_OUTLINE_WIDTH(2),
		LV_STYLE_CONST_BORDER_COLOR(lv_color_make_rgb565(0x20, 0x20, 0x20)),
		LV_STYLE_CONST_BORDER_WIDTH(2),
		LV_STYLE_CONST_BORDER_OPA(LV_OPA_80),
		LV_STYLE_CONST_RADIUS(2),
	};
	static inline auto slider_handle_style = LV_STYLE_CONST_CPP(slider_handle_style_props);

	static lv_color_t mapped_jack_color(unsigned panel_id);

	static std::string color_to_html(lv_color_t color) {
		std::string c = "^000000 ";
		auto printhex = [&c](uint8_t v, size_t pos) {
			if (v < 0x10)
				pos++; //add leading zero
			std::to_chars(c.data() + pos, c.data() + pos + 2, v, 16);
		};
		printhex(color.ch.red << 3, 1);
		printhex(color.ch.green << 2, 3);
		printhex(color.ch.blue << 3, 5);
		return c;
	}

	static void init_lvgl_styles();
};
} // namespace MetaModule
