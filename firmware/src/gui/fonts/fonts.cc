#include "gui/images/paths.hh"
#include "gui/slsexport/meta5/ui.h"
#include "lvgl.h"
#include "pr_dbg.hh"
#include <cstdio>
#include <map>
#include <string_view>

LV_FONT_DECLARE(Segment7Standard_14);
LV_FONT_DECLARE(Segment7Standard_20);

namespace MetaModule
{

namespace
{
// private:
static std::map<std::string, std::map<lv_coord_t, lv_font_t *>> font_cache;
static std::map<std::string, std::vector<uint8_t>> ttf_cache;

static lv_font_t const *fallback_ttf = nullptr;
} // namespace
static lv_font_t const *get_builtin_font(std::string_view name);
static lv_font_t const *get_font_from_cache(std::string_view name);
static lv_font_t const *get_font_from_disk(std::string_view name, std::string_view path = "");
static lv_font_t const *load_from_cache(std::string_view name, lv_coord_t font_size);
static std::pair<std::string_view, std::string_view> remap_fonts(std::string_view name, std::string_view path);

// public:
lv_font_t const *get_font(std::string_view name, std::string_view path) {
	auto [name_, path_] = remap_fonts(name, path);

	if (auto font = get_builtin_font(name_))
		return font;

	if (auto font = get_font_from_cache(name_))
		return font;

	if (auto font = get_font_from_disk(name_, path_))
		return font;

	// Default fallback:
	return &lv_font_montserrat_12;
}

void free_font(std::string_view fontname) {
	//TODO: lv_tiny_ttf_delete
	// remove file data from ttf_cache

	std::string name{fontname};

	if (font_cache.contains(name)) {
		for (auto &font : font_cache[name]) {
			lv_font_free(font.second);
		}
		font_cache.erase(name);
	}
}

void load_default_fonts() {
	fallback_ttf = get_font("MuseoSansRounded-700", "4ms/fonts/MuseoSansRounded-700.ttf");
	if (!fallback_ttf || fallback_ttf == &lv_font_montserrat_12) {
		pr_err("Could not load MuseoSansRounded-700.ttf\n");
	}
}

////////////////////////////////////////

lv_font_t const *load_from_cache(std::string_view name, lv_coord_t font_size = 0) {
	if (auto font = font_cache.find(std::string(name)); font != font_cache.end()) {
		if (font->second.size()) {
			if (font->second.contains(font_size)) {
				return font->second[font_size];
			}
			if (font_size == 0) { //0: any font size is ok, return the first entry
				return font->second.begin()->second;
			}
		}
	}

	return nullptr;
}

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

lv_font_t const *get_font_from_cache(std::string_view name) {
	// Try finding it in the cache:
	if (auto font = load_from_cache(name))
		return font;
	else
		return nullptr;
}

lv_font_t const *get_font_from_disk(std::string_view name, std::string_view path) {
	// Try loading it from disk:
	if (path == "")
		path = name;

	std::string full_path = ComponentImages::get_comp_path(path);

	if (auto font = lv_font_load(full_path.data())) {
		font->fallback = &lv_font_montserrat_14;

		// Insert a map to a map of font size to font
		font_cache.insert({std::string(name), {{font->line_height, font}}});

		pr_dbg("font %s sz %u loaded into font cache\n", name.data(), font->line_height);

		return font;
	}

	return nullptr;
}

///////////////////////////////
//////////////////// TTF

// Loads the file and stores the data in the ttf cache
// Returns true if a new entry was made
bool load_ttf(std::string_view name, std::string_view path) {
	if (ttf_cache.contains(std::string(name))) {
		pr_dbg("Already a font in the ttf cache with name %s\n", name.data());
		return false;
	}

	auto f = std::fopen(path.data(), "rb");
	if (!f) {
		pr_dbg("Could not load ttf '%s' from '%s'\n", name.data(), path.data());
		return false;
	}

	std::fseek(f, 0, SEEK_END);
	size_t len = std::ftell(f);
	std::fseek(f, 0, SEEK_SET);

	// insert
	auto &data = ttf_cache[std::string(name)];
	data.resize(len);

	auto sz = std::fread(data.data(), 1, len, f);
	if (sz != len) {
		pr_err("Failed to read file %s: expected %zu bytes, read %zu\n", path.data(), len, sz);

		std::fclose(f);

		ttf_cache.erase(std::string(name));
		return false;
	}

	pr_dbg("Loading ttf %s from disk path %s, %zu bytes\n", name.data(), path.data(), len);

	std::fclose(f);

	return true;
}

float adjust_font_size(float fontSize, const void *font) {
	//TODO: get font name from cache
	if (fontSize == 38) //DrumKit Gnome, Sequencer
		return 30;
	else
		return fontSize;
}

lv_font_t const *get_ttf_font(std::string const &name, unsigned font_size) {

	if (auto font = load_from_cache(name, font_size)) {
		return font;
	}

	if (ttf_cache.contains(name)) {
		auto &data = ttf_cache[name];

		if (auto font = lv_tiny_ttf_create_data(data.data(), data.size(), font_size)) {

			font->fallback = fallback_ttf ? fallback_ttf : &lv_font_montserrat_14;

			font_cache.insert({std::string(name), {{font_size, font}}});

			pr_dbg("ttf %s sz %u loaded into font cache\n", name.c_str(), font_size);
			return font;
		}
	}

	pr_err("Error loading ttf, using fallback (%p)\n", fallback_ttf);

	return fallback_ttf;
}

std::pair<std::string_view, std::string_view> remap_fonts(std::string_view name, std::string_view path) {

	if (name == "Segment14") {
		pr_dbg("Request for font %s at %s remapped to Segment7Standard at 4ms/fonts/Segment7Standard.ttf\n",
			   name.data(),
			   path.data());
		return {"Segment7Standard", "4ms/fonts/Segment7Standard.ttf"};
	}

	return {name, path};
}

} // namespace MetaModule
