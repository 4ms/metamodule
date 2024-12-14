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

static std::map<std::string, lv_font_t *> font_cache;
static std::map<std::string, std::vector<uint8_t>> ttf_cache;

} // namespace

// private:
static lv_font_t const *get_builtin_font(std::string_view name);
static lv_font_t const *get_font_from_cache(std::string_view name);
static lv_font_t const *get_font_from_disk(std::string_view name, std::string_view path = "");
static lv_font_t const *load_from_cache(std::string_view name);

// public:

lv_font_t const *get_font(std::string_view name, std::string_view path) {
	if (auto font = get_builtin_font(name))
		return font;

	if (auto font = get_font_from_cache(name))
		return font;

	if (auto font = get_font_from_disk(name, path))
		return font;

	// Default fallback:
	return &lv_font_montserrat_12;
}

void free_font(std::string_view filename) {
	//TODO: lv_tiny_ttf_delete
	std::string name{filename};

	if (font_cache.contains(name)) {
		lv_font_free(font_cache.at(name));
		font_cache.erase(name);
	}
}

////////////////////////////////////////

lv_font_t const *load_from_cache(std::string_view name) {
	if (auto font = font_cache.find(std::string(name)); font != font_cache.end())
		return font->second;
	else
		return nullptr;
}

// get_font(name)
//
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

lv_font_t const *get_ttf_font_from_disk(std::string_view name, std::string_view path) {
	pr_dbg("Loading ttf from disk path %s\n", path.data());

	auto f = std::fopen(path.data(), "rb");
	if (!f)
		return nullptr;

	std::fseek(f, 0, SEEK_END);
	size_t len = std::ftell(f);
	std::fseek(f, 0, SEEK_SET);

	std::vector<uint8_t> data;
	data.resize(len);

	std::fread(data.data(), 1, len, f);
	std::fclose(f);

	if (auto font = lv_tiny_ttf_create_data(data.data(), data.size(), 12)) {
		font_cache.insert({std::string(name), font});
		pr_dbg("Font found\n");
		return font;
	}

	pr_err("Could not load ttf font %s\n", name.data());

	return nullptr;
}

lv_font_t const *get_font_from_disk(std::string_view name, std::string_view path) {
	// Try loading it from disk:
	if (path == "")
		path = name;

	if (path.ends_with(".ttf")) {
		return get_ttf_font_from_disk(name, path);
	}

	std::string full_path = ComponentImages::get_comp_path(path);

	if (auto font = lv_font_load(full_path.data())) {
		font_cache.insert({std::string(name), font});
		return font;
	}

	return nullptr;
}

} // namespace MetaModule
