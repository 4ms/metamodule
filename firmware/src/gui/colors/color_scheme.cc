#include "gui/colors/color_scheme.hh"
#include "gui/colors/color_styles.hh"

namespace MetaModule
{

namespace
{

// Build a scheme via a constexpr function so we can use the symbolic
// MetaColorId names as array indices (C++ has no designated array initializers).
constexpr ColorScheme make_default_scheme() {
	ColorScheme s{};
	s.name = "Default";

	s.rgb[METACOLOR_PRIMARY_HIGHLIGHT] = 0xfd8b18;

	s.rgb[METACOLOR_GREY_DARKEST] = 0x222222;
	s.rgb[METACOLOR_GREY_DARKER] = 0x333333;
	s.rgb[METACOLOR_GREY_MEDDARK] = 0x444444;
	s.rgb[METACOLOR_GREY_DARK] = 0x555555;
	s.rgb[METACOLOR_GREY_MEDIUM] = 0x777777;
	s.rgb[METACOLOR_GREY_MED_LIGHT] = 0x888888;
	s.rgb[METACOLOR_GREY_BRIGHT] = 0xaaaaaa;
	s.rgb[METACOLOR_GREY_BRIGHTER] = 0xbbbbbb;
	s.rgb[METACOLOR_GREY_BRIGHTEST] = 0xeeeeee;

	s.rgb[METACOLOR_MODULE_SELECTED_BORDER] = 0xffb74d;

	s.rgb[METACOLOR_NOTIFICATION_BG] = 0xe1e878;

	s.rgb[METACOLOR_BUTTON_CONFIRM] = 0x2095f6;
	s.rgb[METACOLOR_BUTTON_CAUTION] = 0xea1c25;

	s.rgb[METACOLOR_KNOB_BODY] = 0x666666;
	s.rgb[METACOLOR_KNOB_DOT] = 0xdddddd;
	s.rgb[METACOLOR_KNOB_DISABLED] = 0xb4b2b4;

	s.rgb[METACOLOR_CHECKBOX] = 0x4067d3;
	s.rgb[METACOLOR_TEXT_DARK] = 0x111111;

	s.rgb[METACOLOR_RED_TEXT] = 0xea1c25;
	s.rgb[METACOLOR_ORANGE_TEXT] = 0xfd9b18;
	s.rgb[METACOLOR_YELLOW_TEXT] = 0xd7ff6a;
	s.rgb[METACOLOR_GREEN_TEXT] = 0x00a551;
	s.rgb[METACOLOR_BLUE_TEXT] = 0x188bfd;
	s.rgb[METACOLOR_GREY_TEXT] = 0xaaaaaa;
	s.rgb[METACOLOR_LT_GREY_TEXT] = 0xcccccc;

	s.rgb[METACOLOR_BLACK] = 0x000000;
	s.rgb[METACOLOR_WHITE] = 0xffffff;
	s.rgb[METACOLOR_DEBUG_BORDER] = 0xff0000;

	s.rgb[METACOLOR_ORANGE_DARK] = 0xf19300;
	s.rgb[METACOLOR_GREEN_DARK] = 0x23973c;
	s.rgb[METACOLOR_BLUE_DEEP] = 0x4040ff;
	s.rgb[METACOLOR_SCROLLBAR_ORANGE] = 0xdf7d1a;

	s.rgb[METACOLOR_LV_GREY] = 0x9e9e9e;
	s.rgb[METACOLOR_LV_ORANGE] = 0xff9800;
	s.rgb[METACOLOR_LV_GREEN_LIGHT] = 0x66bb6a;
	s.rgb[METACOLOR_LV_RED_LIGHT] = 0xef5350;

	// LV_PALETTE_* indices. Layout: RED, PINK, PURPLE, DEEP_PURPLE, INDIGO,
	// BLUE, LIGHT_BLUE, CYAN, TEAL, GREEN, LIGHT_GREEN, LIME, YELLOW, AMBER,
	// ORANGE, DEEP_ORANGE, BROWN, BLUE_GREY, GREY.
	s.palette_main[0] = 0xf40000;  // RED
	s.palette_main[1] = 0xf063b2;  // PINK
	s.palette_main[2] = 0x9c27b0;  // PURPLE
	s.palette_main[3] = 0x673ab7;  // DEEP_PURPLE
	s.palette_main[4] = 0x3f51b5;  // INDIGO
	s.palette_main[5] = 0x42a5f5;  // BLUE
	s.palette_main[6] = 0xbbdefb;  // LIGHT_BLUE
	s.palette_main[7] = 0x26c6da;  // CYAN
	s.palette_main[8] = 0x009688;  // TEAL
	s.palette_main[9] = 0x00a551;  // GREEN
	s.palette_main[10] = 0x8bc34a; // LIGHT_GREEN
	s.palette_main[11] = 0xcddc39; // LIME
	s.palette_main[12] = 0xfff100; // YELLOW
	s.palette_main[13] = 0xffc107; // AMBER
	s.palette_main[14] = 0xfaa629; // ORANGE
	s.palette_main[15] = 0xff5722; // DEEP_ORANGE
	s.palette_main[16] = 0x896558; // BROWN
	s.palette_main[17] = 0x607d8b; // BLUE_GREY
	s.palette_main[18] = 0x9e9e9e; // GREY

	s.jack_palette[0] = 0xea1c25;
	s.jack_palette[1] = 0xfff200;
	s.jack_palette[2] = 0x00aeee;
	s.jack_palette[3] = 0xf66194;
	s.jack_palette[4] = 0xffa529;
	s.jack_palette[5] = 0x00a552;
	s.jack_palette[6] = 0x000000;
	s.jack_palette[7] = 0xffffff;

	return s;
}

// High-contrast scheme for accessibility. Pure-white text, fully saturated
// accents, dark-but-distinguishable panel backgrounds. Goal: every meaningful
// fg/bg pair has a luminance ratio well above 4.5:1.
constexpr ColorScheme make_high_contrast_scheme() {
	ColorScheme s{};
	s.name = "High Contrast";

	// Highlights — pure / max-saturation versions of the Default hues.
	s.rgb[METACOLOR_BUTTON_CAUTION] = 0xff0000;
	s.rgb[METACOLOR_PRIMARY_HIGHLIGHT] = 0xffa000;
	s.rgb[METACOLOR_BUTTON_CONFIRM] = 0x00bfff;

	// Greys — collapse low-contrast mid-greys toward black or white. Keep two
	// distinct dark steps for panel layering on the black screen background.
	s.rgb[METACOLOR_GREY_BRIGHT] = 0xffffff; // was a low-contrast text grey
	s.rgb[METACOLOR_GREY_DARKEST] = 0x000000;
	s.rgb[METACOLOR_GREY_DARKER] = 0x111111;
	s.rgb[METACOLOR_GREY_DARK] = 0x222222;
	s.rgb[METACOLOR_GREY_MEDDARK] = 0x222222;
	s.rgb[METACOLOR_GREY_MEDIUM] = 0x666666;
	s.rgb[METACOLOR_GREY_MED_LIGHT] = 0xaaaaaa;
	s.rgb[METACOLOR_GREY_BRIGHTER] = 0xdddddd;
	s.rgb[METACOLOR_GREY_BRIGHTEST] = 0xffffff;

	// Popup warning — keep yellow but make it pure for max attention.
	s.rgb[METACOLOR_NOTIFICATION_BG] = 0xffff00;

	s.rgb[METACOLOR_KNOB_BODY] = 0x444444;
	s.rgb[METACOLOR_KNOB_DOT] = 0xffffff;
	s.rgb[METACOLOR_KNOB_DISABLED] = 0x666666;

	s.rgb[METACOLOR_MODULE_SELECTED_BORDER] = 0xffcc66;

	s.rgb[METACOLOR_CHECKBOX] = 0x4080ff;
	s.rgb[METACOLOR_TEXT_DARK] = 0x000000;

	// Rich-text colors used in HTML escape sequences — pull these toward
	// near-white tints of their hue so they still read on black.
	s.rgb[METACOLOR_RED_TEXT] = 0xff8080;
	s.rgb[METACOLOR_ORANGE_TEXT] = 0xffcc66;
	s.rgb[METACOLOR_YELLOW_TEXT] = 0xffff80;
	s.rgb[METACOLOR_GREEN_TEXT] = 0x80ff80;
	s.rgb[METACOLOR_BLUE_TEXT] = 0x80c8ff;
	s.rgb[METACOLOR_GREY_TEXT] = 0xffffff;
	s.rgb[METACOLOR_LT_GREY_TEXT] = 0xffffff;

	s.rgb[METACOLOR_BLACK] = 0x000000;
	s.rgb[METACOLOR_WHITE] = 0xffffff;
	s.rgb[METACOLOR_DEBUG_BORDER] = 0xff0000;

	s.rgb[METACOLOR_ORANGE_DARK] = 0xffa000;
	s.rgb[METACOLOR_GREEN_DARK] = 0x00ff00;
	s.rgb[METACOLOR_BLUE_DEEP] = 0x6080ff;
	s.rgb[METACOLOR_SCROLLBAR_ORANGE] = 0xffa000;

	s.rgb[METACOLOR_LV_GREY] = 0xcccccc;
	s.rgb[METACOLOR_LV_ORANGE] = 0xffa000;
	s.rgb[METACOLOR_LV_GREEN_LIGHT] = 0x80ff80;
	s.rgb[METACOLOR_LV_RED_LIGHT] = 0xff8080;

	// Palette indices — saturated/luminous versions for a black background.
	s.palette_main[0] = 0xff0000;  // RED
	s.palette_main[1] = 0xff80c0;  // PINK
	s.palette_main[2] = 0xc040ff;  // PURPLE
	s.palette_main[3] = 0x9060ff;  // DEEP_PURPLE
	s.palette_main[4] = 0x6080ff;  // INDIGO
	s.palette_main[5] = 0x40c0ff;  // BLUE
	s.palette_main[6] = 0xc0e0ff;  // LIGHT_BLUE
	s.palette_main[7] = 0x00ffff;  // CYAN
	s.palette_main[8] = 0x00ffcc;  // TEAL
	s.palette_main[9] = 0x00ff00;  // GREEN
	s.palette_main[10] = 0xc0ff60; // LIGHT_GREEN
	s.palette_main[11] = 0xccff00; // LIME
	s.palette_main[12] = 0xffff00; // YELLOW
	s.palette_main[13] = 0xffd000; // AMBER
	s.palette_main[14] = 0xffa000; // ORANGE
	s.palette_main[15] = 0xff6020; // DEEP_ORANGE
	s.palette_main[16] = 0xc08060; // BROWN
	s.palette_main[17] = 0xa0c0d0; // BLUE_GREY
	s.palette_main[18] = 0xcccccc; // GREY

	s.jack_palette[0] = 0xff0000;
	s.jack_palette[1] = 0xffff00;
	s.jack_palette[2] = 0x00ffff;
	s.jack_palette[3] = 0xff80c0;
	s.jack_palette[4] = 0xffa000;
	s.jack_palette[5] = 0x00ff00;
	s.jack_palette[6] = 0x000000;
	s.jack_palette[7] = 0xffffff;

	return s;
}

constexpr ColorScheme schemes[] = {
	make_default_scheme(),
	make_high_contrast_scheme(),
};

constexpr unsigned kSchemeCount = sizeof(schemes) / sizeof(schemes[0]);

const ColorScheme *active = &schemes[0];

} // namespace

extern "C" uint32_t scheme_color_rgb(MetaColorId id) {
	return active->rgb[id];
}

namespace Scheme
{

void set(unsigned idx) {
	if (idx >= kSchemeCount)
		return;
	active = &schemes[idx];
	ColorStyles::reapply_scheme();
}

unsigned current() {
	return static_cast<unsigned>(active - &schemes[0]);
}

unsigned count() {
	return kSchemeCount;
}

std::string_view name(unsigned idx) {
	if (idx >= kSchemeCount)
		return {};
	return schemes[idx].name;
}

const ColorScheme *active_scheme() {
	return active;
}

} // namespace Scheme

} // namespace MetaModule
