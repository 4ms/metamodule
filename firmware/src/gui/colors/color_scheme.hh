#pragma once

#include "gui/colors/color_ids.h"
#include "lvgl.h"
#include <string_view>

namespace MetaModule
{

struct ColorScheme {
	const char *name;
	uint32_t rgb[METACOLOR_COUNT];
};

// Resolve a color id to an lv_color_t under the active scheme.
inline lv_color_t mc(MetaColorId id) {
	return lv_color_hex(metacolor_rgb(id));
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
} // namespace Scheme

} // namespace MetaModule
