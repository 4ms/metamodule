#pragma once
#include "lvgl.h"
#include <string_view>

namespace MetaModule
{

inline lv_font_t const *get_font(std::string_view name) {
	// TODO: lazy load fonts from filesystem, store them here
	// lv_font_t *my_font;
	// my_font = lv_font_load(X / path / to / my_font.bin);
	// Free fonts when plugin is unloaded
	// lv_font_free(my_font);

	if (name == "Default_10")
		return &lv_font_montserrat_10;
	else if (name == "Default_12")
		return &ui_font_MuseoSansRounded50012;
	else if (name == "Default_14")
		return &ui_font_MuseoSansRounded70014;
	else
		return &lv_font_montserrat_12;
}
} // namespace MetaModule
