#pragma once
#include "gui/images/paths.hh"
#include "gui/slsexport/meta5/ui.h"
#include "lvgl.h"
#include "pr_dbg.hh"
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
		return &ui_font_MuseoSansRounded50010;
	else if (name == "Montserrat_10")
		return &lv_font_montserrat_10;
	else if (name == "Default_12")
		return &ui_font_MuseoSansRounded50012;
	else if (name == "Default_14")
		return &ui_font_MuseoSansRounded70014;
	else if (name == "Segment7Standard24")
		return &ui_font_Segment7Standard24;
	else if (name == "Segment32")
		return &ui_font_Segment32;
	else if (name == "Segment14_10")
		return &Segment14_10;
	else if (name == "Segment14_12")
		return &Segment14_12;
	else if (name == "Segment14_14")
		return &Segment14_14;
	else if (name == "Segment14_16")
		return &Segment14_16;
	else if (name == "Segment14_20")
		return &Segment14_20;
	else if (name == "Segment14_24")
		return &Segment14_24;
	else if (name == "Segment14_26")
		return &Segment14_26;
	else {
		pr_dbg("Trying to load font %s (%s)\n", name.data(), ComponentImages::get_comp_path(name).c_str());

		auto font = lv_font_load(ComponentImages::get_comp_path(name).c_str());
		if (font) {
			pr_dbg("Found!\n");
			return font;
		} else {
			pr_dbg("Not found\n");
			return &lv_font_montserrat_12;
		}
	}
}
} // namespace MetaModule
