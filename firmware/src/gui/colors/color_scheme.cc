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
	s.rgb[METACOLOR_YELLOW_HIGHLIGHT] = 0x8bfd18;
	s.rgb[METACOLOR_GREEN_HIGHLIGHT] = 0x00a551;
	s.rgb[METACOLOR_BLUE_HIGHLIGHT] = 0x188bfd;
	s.rgb[METACOLOR_GREY_HIGHLIGHT] = 0xaaaaaa;
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

namespace Colors
{

void set_scheme(unsigned idx) {
	if (idx >= kSchemeCount)
		return;
	active = &schemes[idx];
	ColorStyles::reapply_scheme();
}

unsigned current_scheme() {
	return static_cast<unsigned>(active - &schemes[0]);
}

unsigned scheme_count() {
	return kSchemeCount;
}

std::string_view scheme_name(unsigned idx) {
	if (idx >= kSchemeCount)
		return {};
	return schemes[idx].name;
}

} // namespace Colors

} // namespace MetaModule
