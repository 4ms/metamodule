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

namespace MetaModule
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
static lv_font_t const *get_font_from_cache(std::string_view name);
static lv_font_t const *get_font_from_disk(std::string_view name);
static lv_font_t const *load_from_cache(std::string_view name, lv_coord_t font_size);
static std::pair<std::string_view, std::string_view> remap_fonts(std::string_view name, std::string_view path);
static void free_ttf(std::string const &fontname);

// public:
lv_font_t const *get_font(std::string_view name) {
	if (auto font = get_builtin_font(name))
		return font;

	if (auto font = get_font_from_cache(name))
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

	free_ttf(name);
}

////////////////////////////////////////

// font_size 0 will match any size
lv_font_t const *load_from_cache(std::string_view name, lv_coord_t font_size = 0) {

	auto font = std::ranges::find_if(font_cache, [name, font_size](auto const &entry) {
		return entry.name == name && (font_size == 0 || font_size == entry.font_size);
	});

	if (font != font_cache.end()) {
		return font->font;
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

lv_font_t const *get_font_from_disk(std::string_view name) {
	// Try loading it from disk:
	std::string full_path = ComponentImages::get_comp_path(name);

	if (auto font = lv_font_load(full_path.data())) {
		font->fallback = &lv_font_montserrat_14;

		font_cache.emplace_back(std::string(name), font->line_height, font);

		pr_dbg("font %s sz %u loaded into font cache\n", name.data(), font->line_height);

		return font;
	}

	return nullptr;
}

///////////////////////////////
//////////////////// TTF
namespace
{
static std::map<std::string, std::vector<uint8_t>> ttf_cache;
static lv_font_t const *fallback_font = nullptr;
FatFileIO *ramdisk = nullptr;

static constexpr std::string_view default_ttf = "MuseoSansRounded-700";
} // namespace

// Loads the file and stores the data in the ttf cache
// Returns true if a new entry was made
TTFLoadResult load_ttf(std::string_view name, std::string_view path_) {

	auto [_, path] = remap_fonts(name, path_);

	if (ttf_cache.contains(std::string(name))) {
		pr_dbg("Already a font in the ttf cache with name %s\n", name.data());
		return TTFLoadResult::AlreadyExists;
	}

	if (!ramdisk) {
		pr_err("Fonts not initialized: no ramdisk\n");
		return TTFLoadResult::Error;
	}

	auto len = ramdisk->get_file_size(path);
	if (len == 0) {
		pr_dbg("Could not load ttf '%s' from '%s', using default ttf\n", name.data(), path.data());
		return TTFLoadResult::Error;
	}

	auto &data = ttf_cache[std::string(name)];
	data.resize(len);

	auto sz = ramdisk->read_file(path, std::span{(char *)data.data(), data.size()});

	if (sz != len) {
		pr_err("Failed to read file %s: expected %zu bytes, read %zu\n", path.data(), len, sz);
		ttf_cache.erase(std::string(name));
		return TTFLoadResult::Error;
	}

	pr_dbg("Loading ttf %s from disk path %s, %zu bytes\n", name.data(), path.data(), len);

	return TTFLoadResult::Added;
}

unsigned corrected_ttf_letter_spacing(float fontSize, std::string_view name) {
	if (name == "Segment14") {
		if (fontSize < 16)
			return 1;
		else
			return 3;
	}
	return 0;
}

float corrected_ttf_size(float fontSize, std::string_view name) {
	// CVfunk
	if (name == "DejaVuSansMono") {
		if (fontSize == 16)
			return 18;

		if (fontSize == 10)
			return 12;

		if (fontSize == 14)
			return 15;
	}

	// CountModula
	else if (name == "Segment14")
	{
		return fontSize * 1.3f;
	}

	else if (name == "ShareTechMono-Regular")
	{
		fontSize *= 1.5f;
	}

	if (fontSize == 38) //DrumKit Gnome, Sequencer
		return 30;

	return fontSize;
}

void init_fonts(FatFileIO &ramdiskio) {
	ramdisk = &ramdiskio;

	fallback_font = &lv_font_montserrat_14;

	if (load_ttf(default_ttf, std::string("4ms/fonts/").append(default_ttf).append(".ttf")) != TTFLoadResult::Added) {
		pr_err("Could not load default ttf %s\n", default_ttf.data());
	}
}

std::string_view default_ttf_name() {
	return default_ttf;
}

lv_font_t const *get_ttf_font(std::string const &name, unsigned font_size) {

	if (auto font = load_from_cache(name, font_size)) {
		return font;
	}

	if (ttf_cache.contains(name)) {
		auto &data = ttf_cache[name];

		if (auto font = lv_tiny_ttf_create_data(data.data(), data.size(), font_size)) {

			font->fallback = fallback_font ? fallback_font : &lv_font_montserrat_14;

			font_cache.emplace_back(std::string(name), font_size, font);

			pr_dbg("ttf %s sz %u loaded into font cache\n", name.c_str(), font_size);
			return font;
		} else {
			pr_err("Error creating lvgl font from ttf %s\n", name.c_str());
		}
	} else {
		pr_err("Requested ttf font %s whose file data is not in the cache\n", name.c_str());
	}

	// Recurse to try the default ttf at the requested size
	if (name != default_ttf) {
		pr_err("Using fallback font (%s)\n", default_ttf.data());
		return get_ttf_font(std::string(default_ttf), font_size);
	}

	pr_err("Failed to load default ttf font at size %u, using default non-ttf\n", font_size);
	return fallback_font;
}

void free_ttf(std::string const &fontname) {
	ttf_cache.erase(fontname);
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
