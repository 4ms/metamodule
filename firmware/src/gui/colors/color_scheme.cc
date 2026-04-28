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

	s.rgb[METACOLOR_RED_HIGHLIGHT] = 0xea1c25;
	s.rgb[METACOLOR_ORANGE_HIGHLIGHT] = 0xfd8b18;
	s.rgb[METACOLOR_ORANGE_BRIGHT] = 0xfdb818;
	s.rgb[METACOLOR_YELLOW_HIGHLIGHT] = 0x8bfd18;
	s.rgb[METACOLOR_GREEN_HIGHLIGHT] = 0x00a551;
	s.rgb[METACOLOR_BLUE_HIGHLIGHT] = 0x188bfd;
	s.rgb[METACOLOR_BLUE_INFO] = 0x2095f6;
	s.rgb[METACOLOR_GREY_HIGHLIGHT] = 0xaaaaaa;
	s.rgb[METACOLOR_GREY_DARKEST] = 0x222222;
	s.rgb[METACOLOR_GREY_DARKER] = 0x333333;
	s.rgb[METACOLOR_GREY_DARK] = 0x555555;
	s.rgb[METACOLOR_GREY_44] = 0x444444;
	s.rgb[METACOLOR_GREY_MEDIUM] = 0x777777;
	s.rgb[METACOLOR_GREY_88] = 0x888888;
	s.rgb[METACOLOR_GREY_BB] = 0xbbbbbb;
	s.rgb[METACOLOR_GREY_BRIGHT] = 0xeeeeee;
	s.rgb[METACOLOR_POPUP_WARNING_BG] = 0xe1e878;
	s.rgb[METACOLOR_KNOB_BODY] = 0x666666;
	s.rgb[METACOLOR_KNOB_DOT] = 0xdddddd;
	s.rgb[METACOLOR_BROWN_HIGHLIGHT] = 0xa26e3e;

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

	return s;
}

constexpr ColorScheme schemes[] = {
	make_default_scheme(),
};

constexpr unsigned kSchemeCount = sizeof(schemes) / sizeof(schemes[0]);

const ColorScheme *active = &schemes[0];

} // namespace

extern "C" uint32_t metacolor_rgb(MetaColorId id) {
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

} // namespace Scheme

} // namespace MetaModule
