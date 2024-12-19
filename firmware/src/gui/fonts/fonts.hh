#pragma once
#include <string_view>

typedef struct _lv_font_t lv_font_t;

namespace MetaModule
{

lv_font_t const *get_font(std::string_view name, std::string_view path = "");

void free_font(std::string_view name);

///////////////// TTF

void load_default_fonts();
bool load_ttf(std::string_view name, std::string_view path);
float corrected_ttf_size(float fontSize, const void *font);
lv_font_t const *get_ttf_font(std::string const &name, unsigned font_size);

} // namespace MetaModule
