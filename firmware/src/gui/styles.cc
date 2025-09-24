#include <string_view>

#include "styles.hh"

namespace MetaModule
{

namespace Palette
{

// TODO: all colors stem from get_color(id) or get_color_string(id);

std::array<const lv_color_t, 19> palette_main = {
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

static std::array<lv_color_t, 8> knob_palette{
	palette_main[LV_PALETTE_RED],
	palette_main[LV_PALETTE_YELLOW],
	palette_main[LV_PALETTE_CYAN],
	palette_main[LV_PALETTE_PINK],
	palette_main[LV_PALETTE_ORANGE],
	palette_main[LV_PALETTE_GREEN],
	palette_main[LV_PALETTE_GREY],		//?
	palette_main[LV_PALETTE_BLUE_GREY], //?
};

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

std::array<const lv_color_t, 8> cable_palette{
	LV_COLOR_MAKE(0xEF, 0x53, 0x50), //palette[LV_PALETTE_RED][0],
	LV_COLOR_MAKE(0x42, 0xA5, 0xF5), //palette[LV_PALETTE_BLUE][0],
	LV_COLOR_MAKE(0x66, 0xBB, 0x6A), //palette[LV_PALETTE_GREEN][0],
	LV_COLOR_MAKE(0xBD, 0xBD, 0xBD), //palette[LV_PALETTE_GREY][0],
	LV_COLOR_MAKE(0xFF, 0xEE, 0x58), //palette[LV_PALETTE_YELLOW][0],
	LV_COLOR_MAKE(0xFF, 0xA7, 0x26), //palette[LV_PALETTE_ORANGE][0],
	LV_COLOR_MAKE(0xEC, 0x40, 0x7A), //palette[LV_PALETTE_PINK][0],
	LV_COLOR_MAKE(0xAB, 0x47, 0xBC), //palette[LV_PALETTE_PURPLE][0],
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

} // namespace Palette

//// comps

static lv_color_t get_knob_color(uint16_t panel_id) {
	using namespace Palette;

	MappedKnob map{.panel_knob_id = panel_id};

	if (map.is_panel_knob())
		return knob_palette[panel_id % 6];

	if (map.is_button())
		return lv_color_black();

	return knob_palette[panel_id % 6];
}

static lv_color_t get_jack_color(uint16_t panel_id) {
	using namespace Palette;
	return knob_palette[panel_id % 8];
}

static lv_color_t get_buttonexp_color(float value) {
	using namespace Palette;
	auto red = std::clamp<unsigned>(255.f * value, 0, 255);
	return lv_color_make(red, 0, 0);
}

static lv_color_t get_buttonexp_textcolor(float value) {
	using namespace Palette;
	auto grey = std::clamp<unsigned>(255.f * value, 0, 255);
	return (grey > 0xC0) ? lv_color_black() : lv_color_white();
}

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
///////////////////////
// TEXT

const lv_color_t Gui::orange_highlight = lv_color_hex(0xfd8b18);

std::string Gui::red_text(std::string_view txt) {
	return color_text(txt, "^ea1c25 ");
}

std::string Gui::orange_text(std::string_view txt) {
	return color_text(txt, "^fd9b18 ");
}

std::string Gui::yellow_text(std::string_view txt) {
	return color_text(txt, "^d7ff6a ");
}

std::string Gui::green_text(std::string_view txt) {
	return color_text(txt, "^00a551 ");
}

std::string Gui::blue_text(std::string_view txt) {
	return color_text(txt, "^188bfd ");
}

std::string Gui::grey_text(std::string_view txt) {
	return color_text(txt, "^aaaaaa ");
}

std::string Gui::lt_grey_text(std::string_view txt) {
	return color_text(txt, "^cccccc ");
}

const lv_color_t Gui::palette[][5] = {
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

} // namespace MetaModule
