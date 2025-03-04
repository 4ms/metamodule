#include "ttf.hh"
#include "fonts.hh"
#include "fs/fatfs/fat_file_io.hh"
#include "lvgl.h"
#include <map>
#include <vector>

namespace MetaModule::Fonts
{

namespace
{

std::map<std::string, std::vector<uint8_t>> ttf_cache;
lv_font_t const *fallback_font = nullptr;
FatFileIO *ramdisk = nullptr;

constexpr std::string_view default_ttf = "MuseoSansRounded-700";

std::pair<std::string_view, std::string_view> remap_fonts(std::string_view name, std::string_view path);

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
	// CountModula
	if (name == "Segment14") {
		return fontSize * 1.3f;
	}

	else if (name == "ShareTechMono-Regular")
	{
		if (fontSize == 12.f)
			fontSize *= 1.2f;

		else if (fontSize < 12.f)
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

			add_font_to_cache(name, font_size, font);

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

void free_ttf(std::string const &filename) {
	auto fontname = filename;
	if (auto pos = filename.find_last_of("."); pos != std::string::npos) {
		fontname = fontname.substr(0, pos);
	}
	if (auto pos = filename.find_last_of("/"); pos != std::string::npos) {
		fontname = fontname.substr(pos + 1);
	}

	// TODO: how do we know another plugin is not using this font?
	pr_dbg("Not erasing cache entry for ttf font %s\n", fontname.c_str());
	// ttf_cache.erase(fontname);
}

namespace
{
std::pair<std::string_view, std::string_view> remap_fonts(std::string_view name, std::string_view path) {

	if (name == "Segment14") {
		pr_dbg("Request for font %s at %s remapped to Segment7Standard at 4ms/fonts/Segment7Standard.ttf\n",
			   name.data(),
			   path.data());
		return {"Segment7Standard", "4ms/fonts/Segment7Standard.ttf"};
	}

	return {name, path};
}

} // namespace

} // namespace MetaModule::Fonts
