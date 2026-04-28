#pragma once

#include "gui/colors/color_ids.h"
#include "lvgl.h"
#include <string_view>

namespace MetaModule
{

struct ColorScheme {
	const char *name;
	uint32_t rgb[METACOLOR_COUNT];

	// LVGL color palette used by Gui::palette_main / mapped_jack_color.
	// Layout matches LV_PALETTE_* indices (0..18).
	uint32_t palette_main[19];

	// Per-jack accent palette (Gui::jack_palette).
	uint32_t jack_palette[8];
};

// Resolve a color id to an lv_color_t under the active scheme.
inline lv_color_t mc(MetaColorId id) {
	return lv_color_hex(scheme_color_rgb(id));
}

namespace Scheme
{
// Switch the active scheme. Updates atomic ColorStyles and reports a global
// style change. Does NOT call Gui::init_lvgl_styles() — caller must do that
// to refresh the composite styles defined in styles.hh.
void set(unsigned idx);

unsigned current();
unsigned count();
std::string_view name(unsigned idx);

// Returns a pointer to the active scheme. Used by Gui::init_lvgl_styles()
// to refresh palette_main / jack_palette arrays from the scheme.
const ColorScheme *active_scheme();
} // namespace Scheme

} // namespace MetaModule
