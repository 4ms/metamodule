#include "fonts.hh"
#include "fs/fatfs/fat_file_io.hh"
#include "gui/images/paths.hh"
#include "gui/slsexport/meta5/ui.h"
#include "lvgl.h"
#include "pr_dbg.hh"
#include <cstdio>
#include <map>
#include <string_view>

LV_FONT_DECLARE(Segment7Standard_14);
LV_FONT_DECLARE(Segment7Standard_20);

namespace MetaModule::Fonts
{

// private:
namespace
{

struct FontEntry {
	std::string name;
	lv_coord_t font_size;
	lv_font_t *font;
};

static std::vector<FontEntry> font_cache;

} // namespace

static lv_font_t const *get_builtin_font(std::string_view name);
static lv_font_t const *get_font_from_disk(std::string_view name);

// public:
lv_font_t const *get_font(std::string_view name) {
	if (auto font = get_builtin_font(name))
		return font;

	if (auto font = load_from_cache(name, 0))
		return font;

	if (auto font = get_font_from_disk(name))
		return font;

	// Default fallback:
	return &lv_font_montserrat_12;
}

void free_font(std::string_view fontname) {
	std::string name{fontname};

	auto match_name = [fontname](FontEntry const &entry) {
		return entry.name == fontname;
	};

	for (auto &entry : font_cache) {
		if (match_name(entry))
			lv_font_free(entry.font);
	}

	auto num_erased = std::erase_if(font_cache, match_name);
	pr_dbg("Erased %zu fonts matching name %s", num_erased, name.c_str());
}

// font_size 0 will match any size
lv_font_t const *load_from_cache(std::string_view name, unsigned font_size) {

	auto font = std::ranges::find_if(font_cache, [name, font_size](auto const &entry) {
		return entry.name == name && (font_size == 0 || font_size == (unsigned)entry.font_size);
	});

	if (font != font_cache.end()) {
		return font->font;
	}

	return nullptr;
}

void add_font_to_cache(std::string_view name, unsigned font_size, lv_font_t *font) {
	font_cache.push_back({std::string(name), (lv_coord_t)font_size, font});
}

////////////////////////////////////////

lv_font_t const *get_builtin_font(std::string_view name) {
	// Look for built-in fonts first
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

	else
		return nullptr;
}

lv_font_t const *get_font_from_disk(std::string_view name) {
	// Try loading it from disk:
	std::string full_path = ComponentImages::get_comp_path(name);

	if (auto font = lv_font_load(full_path.data())) {
		font->fallback = &lv_font_montserrat_14;

		font_cache.push_back({std::string(name), font->line_height, font});

		pr_dbg("font %s sz %u loaded into font cache\n", name.data(), font->line_height);

		return font;
	}

	return nullptr;
}

} // namespace MetaModule::Fonts
