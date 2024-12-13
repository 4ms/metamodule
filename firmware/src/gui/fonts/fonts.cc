#include "gui/images/paths.hh"
#include "gui/slsexport/meta5/ui.h"
#include "lvgl.h"
#include "pr_dbg.hh"
#include <map>
#include <string_view>

LV_FONT_DECLARE(Segment7Standard_14);
LV_FONT_DECLARE(Segment7Standard_20);

namespace MetaModule
{

namespace
{
static std::map<std::string, lv_font_t *> font_cache;
static std::vector<std::string> font_handles;
} // namespace

static lv_font_t const *load_from_cache(std::string_view name) {
	if (font_cache.contains(std::string(name))) {
		return font_cache[std::string(name)];
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

	else if (name == "Montserrat_10")
		return &lv_font_montserrat_10;

	else if (name == "Segment7Standard24" || name == "Segment7Standard_24")
		return &ui_font_Segment7Standard24;
	else if (name == "Segment7Standard_20")
		return &Segment7Standard_20;
	else if (name == "Segment7Standard_14")
		return &Segment7Standard_14;

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

	// Try finding it in the cache:
	else if (auto font = load_from_cache(name)) {
		return font;
	}

	// Try loading it from disk:
	else if (auto font = lv_font_load(ComponentImages::get_comp_path(name).c_str()))
	{
		font_cache.insert({std::string(name), font});
		font_handles.emplace_back(name);
		return font;

		//Use default font:
	} else {
		return &lv_font_montserrat_12;
	}
}

lv_font_t const *get_font_from_handle(int handle) {
	if ((size_t)handle < font_handles.size())
		return load_from_cache(font_handles[handle]);
	else
		return nullptr;
}

int get_handle_from_name(const char *name) {
	auto handle = std::ranges::find(font_handles, std::string{name});
	if (handle != font_handles.end())
		return std::distance(font_handles.begin(), handle);
	else
		return -1;
}

int get_handle_from_font(lv_font_t const *font) {
	for (auto const &f : font_cache) {
		if (f.second == font)
			return get_handle_from_name(f.first.c_str());
	}
	return -1;
}

void free_font(std::string_view filename) {
	std::string name{filename};

	if (font_cache.contains(name)) {
		lv_font_free(font_cache.at(name));
		font_cache.erase(name);
	}
}

} // namespace MetaModule
