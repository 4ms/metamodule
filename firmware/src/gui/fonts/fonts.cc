#include "gui/images/paths.hh"
#include "gui/slsexport/meta5/ui.h"
#include "lvgl.h"
#include "pr_dbg.hh"
#include <list>
#include <string_view>

LV_FONT_DECLARE(Segment7Standard_14);
LV_FONT_DECLARE(Segment7Standard_20);

namespace MetaModule
{

namespace
{
static std::list<lv_font_t *> font_cache;
}

// convert filename to hash and cast as void* so we can store in lvgl user_data field
static void *hash(std::string_view name) {
	auto h = std::hash<std::string_view>{}(name);
	return reinterpret_cast<void *>(h);
}

static lv_font_t const *load_from_cache(std::string_view name) {
	if (auto f = std::find_if(
			font_cache.begin(), font_cache.end(), [&](lv_font_t const *font) { return font->user_data == hash(name); });
		f != font_cache.end())
	{
		return *f;
	} else
		return nullptr;
}

lv_font_t const *get_font(std::string_view name) {

	if (name == "Default_10")
		return &ui_font_MuseoSansRounded50010;
	else if (name == "Default_12")
		return &ui_font_MuseoSansRounded50012;
	else if (name == "Default_14")
		return &ui_font_MuseoSansRounded70014;
	//
	else if (name == "Montserrat_10")
		return &lv_font_montserrat_10;
	//
	else if (name == "Segment7Standard24" || name == "Segment7Standard_24")
		return &ui_font_Segment7Standard24;
	else if (name == "Segment7Standard_20")
		return &Segment7Standard_20;
	else if (name == "Segment7Standard_14")
		return &Segment7Standard_14;
	//
	else if (name == "Segment32")
		return &ui_font_Segment32;
	//
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

	// Try finding it in the cache:
	else if (auto font = load_from_cache(name)) {
		return font;
	}

	// Try loading it into the cache:
	else if (auto font = lv_font_load(ComponentImages::get_comp_path(name).c_str()))
	{
		font->user_data = hash(name);
		font_cache.push_back(font);
		return font;

	} else { //Use default font:
		return &lv_font_montserrat_12;
	}
}

void free_font(std::string_view filename) {
	font_cache.remove_if([&](lv_font_t *font) {
		if (font->user_data == hash(filename)) {
			// Free the lvgl memory
			lv_font_free(font);
			return true;
		}
		return false;
	});
}

} // namespace MetaModule
