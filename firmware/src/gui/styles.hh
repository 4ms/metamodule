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

	// COLORS
	static inline std::string color_text(std::string_view txt, std::string_view color) {
		return std::string{color} + std::string{txt} + LV_TXT_COLOR_CMD + " ";
	}
	static inline lv_color_t red_highlight = lv_color_hex(0xea1c25);
	static std::string red_text(std::string_view txt) {
		return color_text(txt, "^ea1c25 ");
	}

	static inline lv_color_t orange_highlight = lv_color_hex(0xfd8b18);
	static std::string orange_text(std::string_view txt) {
		return color_text(txt, "^fd9b18 ");
	}

	static inline lv_color_t yellow_highlight = lv_color_hex(0x8bfd18);
	static std::string yellow_text(std::string_view txt) {
		return color_text(txt, "^d7ff6a ");
	}

	static inline lv_color_t green_highlight = lv_color_hex(0x00a551);
	static std::string green_text(std::string_view txt) {
		return color_text(txt, "^00a551 ");
	}

	static std::string blue_text(std::string_view txt) {
		return color_text(txt, "^188bfd ");
	}

	static inline lv_color_t grey_highlight = lv_color_hex(0xaaaaaa);
	static std::string grey_text(std::string_view txt) {
		return color_text(txt, "^aaaaaa ");
	}

	static std::string lt_grey_text(std::string_view txt) {
		return color_text(txt, "^cccccc ");
	}

	static inline const char *brown_highlight_html = "^A26E3E ";

	static inline lv_theme_t *theme;
	static inline lv_disp_t *display;

	static inline const lv_color_t palette[][5] = {
		{LV_COLOR_MAKE(0xEF, 0x53, 0x50),
		 LV_COLOR_MAKE(0xE5, 0x73, 0x73),
		 LV_COLOR_MAKE(0xEF, 0x9A, 0x9A),
		 LV_COLOR_MAKE(0xFF, 0xCD, 0xD2),
		 LV_COLOR_MAKE(0xFF, 0xEB, 0xEE)},
		{LV_COLOR_MAKE(0xEC, 0x40, 0x7A),
		 LV_COLOR_MAKE(0xF0, 0x62, 0x92),
		 LV_COLOR_MAKE(0xF4, 0x8F, 0xB1),
		 LV_COLOR_MAKE(0xF8, 0xBB, 0xD0),
		 LV_COLOR_MAKE(0xFC, 0xE4, 0xEC)},
		{LV_COLOR_MAKE(0xAB, 0x47, 0xBC),
		 LV_COLOR_MAKE(0xBA, 0x68, 0xC8),
		 LV_COLOR_MAKE(0xCE, 0x93, 0xD8),
		 LV_COLOR_MAKE(0xE1, 0xBE, 0xE7),
		 LV_COLOR_MAKE(0xF3, 0xE5, 0xF5)},
		{LV_COLOR_MAKE(0x7E, 0x57, 0xC2),
		 LV_COLOR_MAKE(0x95, 0x75, 0xCD),
		 LV_COLOR_MAKE(0xB3, 0x9D, 0xDB),
		 LV_COLOR_MAKE(0xD1, 0xC4, 0xE9),
		 LV_COLOR_MAKE(0xED, 0xE7, 0xF6)},
		{LV_COLOR_MAKE(0x5C, 0x6B, 0xC0),
		 LV_COLOR_MAKE(0x79, 0x86, 0xCB),
		 LV_COLOR_MAKE(0x9F, 0xA8, 0xDA),
		 LV_COLOR_MAKE(0xC5, 0xCA, 0xE9),
		 LV_COLOR_MAKE(0xE8, 0xEA, 0xF6)},
		{LV_COLOR_MAKE(0x42, 0xA5, 0xF5),
		 LV_COLOR_MAKE(0x64, 0xB5, 0xF6),
		 LV_COLOR_MAKE(0x90, 0xCA, 0xF9),
		 LV_COLOR_MAKE(0xBB, 0xDE, 0xFB),
		 LV_COLOR_MAKE(0xE3, 0xF2, 0xFD)},
		{LV_COLOR_MAKE(0x29, 0xB6, 0xF6),
		 LV_COLOR_MAKE(0x4F, 0xC3, 0xF7),
		 LV_COLOR_MAKE(0x81, 0xD4, 0xFA),
		 LV_COLOR_MAKE(0xB3, 0xE5, 0xFC),
		 LV_COLOR_MAKE(0xE1, 0xF5, 0xFE)},
		{LV_COLOR_MAKE(0x26, 0xC6, 0xDA),
		 LV_COLOR_MAKE(0x4D, 0xD0, 0xE1),
		 LV_COLOR_MAKE(0x80, 0xDE, 0xEA),
		 LV_COLOR_MAKE(0xB2, 0xEB, 0xF2),
		 LV_COLOR_MAKE(0xE0, 0xF7, 0xFA)},
		{LV_COLOR_MAKE(0x26, 0xA6, 0x9A),
		 LV_COLOR_MAKE(0x4D, 0xB6, 0xAC),
		 LV_COLOR_MAKE(0x80, 0xCB, 0xC4),
		 LV_COLOR_MAKE(0xB2, 0xDF, 0xDB),
		 LV_COLOR_MAKE(0xE0, 0xF2, 0xF1)},
		{LV_COLOR_MAKE(0x66, 0xBB, 0x6A),
		 LV_COLOR_MAKE(0x81, 0xC7, 0x84),
		 LV_COLOR_MAKE(0xA5, 0xD6, 0xA7),
		 LV_COLOR_MAKE(0xC8, 0xE6, 0xC9),
		 LV_COLOR_MAKE(0xE8, 0xF5, 0xE9)},
		{LV_COLOR_MAKE(0x9C, 0xCC, 0x65),
		 LV_COLOR_MAKE(0xAE, 0xD5, 0x81),
		 LV_COLOR_MAKE(0xC5, 0xE1, 0xA5),
		 LV_COLOR_MAKE(0xDC, 0xED, 0xC8),
		 LV_COLOR_MAKE(0xF1, 0xF8, 0xE9)},
		{LV_COLOR_MAKE(0xD4, 0xE1, 0x57),
		 LV_COLOR_MAKE(0xDC, 0xE7, 0x75),
		 LV_COLOR_MAKE(0xE6, 0xEE, 0x9C),
		 LV_COLOR_MAKE(0xF0, 0xF4, 0xC3),
		 LV_COLOR_MAKE(0xF9, 0xFB, 0xE7)},
		{LV_COLOR_MAKE(0xFF, 0xEE, 0x58),
		 LV_COLOR_MAKE(0xFF, 0xF1, 0x76),
		 LV_COLOR_MAKE(0xFF, 0xF5, 0x9D),
		 LV_COLOR_MAKE(0xFF, 0xF9, 0xC4),
		 LV_COLOR_MAKE(0xFF, 0xFD, 0xE7)},
		{LV_COLOR_MAKE(0xFF, 0xCA, 0x28),
		 LV_COLOR_MAKE(0xFF, 0xD5, 0x4F),
		 LV_COLOR_MAKE(0xFF, 0xE0, 0x82),
		 LV_COLOR_MAKE(0xFF, 0xEC, 0xB3),
		 LV_COLOR_MAKE(0xFF, 0xF8, 0xE1)},
		{LV_COLOR_MAKE(0xFF, 0xA7, 0x26),
		 LV_COLOR_MAKE(0xFF, 0xB7, 0x4D),
		 LV_COLOR_MAKE(0xFF, 0xCC, 0x80),
		 LV_COLOR_MAKE(0xFF, 0xE0, 0xB2),
		 LV_COLOR_MAKE(0xFF, 0xF3, 0xE0)},
		{LV_COLOR_MAKE(0xFF, 0x70, 0x43),
		 LV_COLOR_MAKE(0xFF, 0x8A, 0x65),
		 LV_COLOR_MAKE(0xFF, 0xAB, 0x91),
		 LV_COLOR_MAKE(0xFF, 0xCC, 0xBC),
		 LV_COLOR_MAKE(0xFB, 0xE9, 0xE7)},
		{LV_COLOR_MAKE(0x8D, 0x6E, 0x63),
		 LV_COLOR_MAKE(0xA1, 0x88, 0x7F),
		 LV_COLOR_MAKE(0xBC, 0xAA, 0xA4),
		 LV_COLOR_MAKE(0xD7, 0xCC, 0xC8),
		 LV_COLOR_MAKE(0xEF, 0xEB, 0xE9)},
		{LV_COLOR_MAKE(0x78, 0x90, 0x9C),
		 LV_COLOR_MAKE(0x90, 0xA4, 0xAE),
		 LV_COLOR_MAKE(0xB0, 0xBE, 0xC5),
		 LV_COLOR_MAKE(0xCF, 0xD8, 0xDC),
		 LV_COLOR_MAKE(0xEC, 0xEF, 0xF1)},
		{LV_COLOR_MAKE(0xBD, 0xBD, 0xBD),
		 LV_COLOR_MAKE(0xE0, 0xE0, 0xE0),
		 LV_COLOR_MAKE(0xEE, 0xEE, 0xEE),
		 LV_COLOR_MAKE(0xF5, 0xF5, 0xF5),
		 LV_COLOR_MAKE(0xFA, 0xFA, 0xFA)},
	};

	static inline std::array<lv_color_t, 8> cable_palette{
		palette[LV_PALETTE_RED][0],
		palette[LV_PALETTE_BLUE][0],
		palette[LV_PALETTE_GREEN][0],
		palette[LV_PALETTE_GREY][0],
		palette[LV_PALETTE_YELLOW][0],
		palette[LV_PALETTE_ORANGE][0],
		palette[LV_PALETTE_PINK][0],
		palette[LV_PALETTE_PURPLE][0],
	};

	static constexpr std::array<lv_color_t, 19> palette_main = {
		lv_color_make_rgb565(0xF4, 0x00, 0x00), // RED
		lv_color_make_rgb565(0xF0, 0x63, 0xB2), // PINK
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

	static lv_color_t get_knob_color(uint16_t panel_id) {
		MappedKnob map{.panel_knob_id = panel_id};

		if (map.is_panel_knob())
			return knob_palette[panel_id % 6];

		if (map.is_button())
			return lv_color_black();

		return knob_palette[panel_id % 6];
	}

	static lv_color_t get_jack_color(uint16_t panel_id) {
		return knob_palette[panel_id % 8];
	}

	static lv_color_t get_buttonexp_color(float value) {
		auto red = std::clamp<unsigned>(255.f * value, 0, 255);
		return lv_color_make(red, 0, 0);
	}

	static lv_color_t get_buttonexp_textcolor(float value) {
		auto grey = std::clamp<unsigned>(255.f * value, 0, 255);
		return (grey > 0xC0) ? lv_color_black() : lv_color_white();
	}

	static inline std::array<lv_color_t, 8> knob_disabled_palette{
		palette_main[LV_PALETTE_RED],
		palette_main[LV_PALETTE_YELLOW],
		palette_main[LV_PALETTE_CYAN],
		palette_main[LV_PALETTE_PINK],
		palette_main[LV_PALETTE_ORANGE],
		palette_main[LV_PALETTE_GREEN],
		palette_main[LV_PALETTE_GREY],		//?
		palette_main[LV_PALETTE_BLUE_GREY], //?
	};

	static inline std::array<lv_color_t, 8> knob_indicator_palette{
		lv_color_black(), //RED
		lv_color_black(), //YELLOW
		lv_color_black(), //CYAN
		lv_color_black(), //PINK
		lv_color_black(), //ORANGE
		lv_color_black(), //GREEN
		lv_color_white(), //black
		lv_color_black(), //white
	};

	static lv_color_t get_knob_indicator_color(uint16_t panel_id) {
		return knob_indicator_palette[panel_id % 6];
	}

	static inline std::array<lv_color_t, 8> jack_palette{
		lv_color_make_rgb565(0xEA, 0x1C, 0x25),
		lv_color_make_rgb565(0xFF, 0xF2, 0x00),
		lv_color_make_rgb565(0x00, 0xAE, 0xEE),
		lv_color_make_rgb565(0xF6, 0x61, 0x94),
		lv_color_make_rgb565(0xFF, 0xA5, 0x29),
		lv_color_make_rgb565(0x00, 0xA5, 0x52),
		lv_color_make_rgb565(0x00, 0x00, 0x00),
		lv_color_make_rgb565(0xFF, 0xFF, 0xFF),
	};

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

	static lv_color_t mapped_jack_color(unsigned panel_id) {
		if (panel_id <= LastPossibleKnob)
			return jack_palette[panel_id % jack_palette.size()];

		else if (panel_id <= MidiNote8Jack)
			return palette_main[0];

		else if (panel_id <= MidiGate8Jack)
			return palette_main[1];

		else if (panel_id <= MidiVel8Jack)
			return palette_main[2];

		else if (panel_id <= MidiAftertouch8Jack)
			return palette_main[3];

		else if (panel_id <= MidiRetrig8Jack)
			return palette_main[4];

		else if (panel_id <= MidiCC127)
			return palette_main[5];

		else if (panel_id <= MidiPitchWheelJack)
			return palette_main[6];

		else if (panel_id <= MidiGateNote127)
			return palette_main[7];

		else if (panel_id <= MidiClockDiv96Jack)
			return palette_main[8];

		else if (panel_id <= MidiContinueJack)
			return palette_main[9];

		else
			return jack_palette[panel_id % jack_palette.size()];
	}

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

	static void init_lvgl_styles() {

		for (auto &color : knob_disabled_palette) {
			auto hsv = lv_color_to_hsv(color);
			color = lv_color_hsv_to_rgb(hsv.h, hsv.s / 2, hsv.v / 2);
		}

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
		lv_style_set_bg_opa(&panel_highlight_style, LV_OPA_40);
		lv_style_set_border_opa(&panel_highlight_style, LV_OPA_70);
		lv_style_set_border_width(&panel_highlight_style, 1);
		lv_style_set_border_color(&panel_highlight_style, orange_highlight);

		// panel_large_highlight_style
		lv_style_init(&panel_large_highlight_style);
		lv_style_set_radius(&panel_large_highlight_style, 4);
		lv_style_set_bg_color(&panel_large_highlight_style, orange_highlight);
		lv_style_set_bg_opa(&panel_large_highlight_style, LV_OPA_10);
		lv_style_set_border_opa(&panel_large_highlight_style, LV_OPA_70);
		lv_style_set_border_width(&panel_large_highlight_style, 2);
		lv_style_set_border_color(&panel_large_highlight_style, orange_highlight);

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

		lv_style_init(&subdir_panel_item_sel_blurred_style);
		lv_style_set_bg_color(&subdir_panel_item_sel_blurred_style, lv_color_hex(0x555555));
		lv_style_set_bg_opa(&subdir_panel_item_sel_blurred_style, LV_OPA_100);
		lv_style_set_outline_width(&subdir_panel_item_sel_blurred_style, 0);
		lv_style_set_border_width(&subdir_panel_item_sel_blurred_style, 0);

		// Dropdown
		lv_style_init(&dropdown_style);
		lv_style_set_bg_color(&dropdown_style, lv_color_hex(0x555555));
		lv_style_set_text_color(&dropdown_style, lv_color_white());
		lv_style_set_text_opa(&dropdown_style, 255);
		lv_style_set_text_font(&dropdown_style, &ui_font_MuseoSansRounded70014);
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
