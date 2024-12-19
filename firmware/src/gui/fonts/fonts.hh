#pragma once
#include <string_view>

typedef struct _lv_font_t lv_font_t;

namespace MetaModule
{

lv_font_t const *get_font(std::string_view name);
void free_font(std::string_view name);

///////////////// TTF

void load_default_ttf_fonts();
std::string_view default_ttf_name();

// Load raw ttf file data into the font cache
enum class TTFLoadResult { Error, AlreadyExists, Added };
TTFLoadResult load_ttf(std::string_view name, std::string_view path);

// Given a name of a ttf font that's already loaded, return an LVGL font at the given size
lv_font_t const *get_ttf_font(std::string const &name, unsigned font_size);

// Tweak the ttf font size so it looks better on the MM screen
float corrected_ttf_size(float fontSize, std::string_view name);
unsigned corrected_ttf_letter_spacing(float fontSize, std::string_view name);

} // namespace MetaModule
