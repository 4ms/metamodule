#pragma once
#include <string_view>

typedef struct _lv_font_t lv_font_t;

namespace MetaModule::Fonts
{

lv_font_t const *get_font(std::string_view name);
void free_font(std::string_view name);

lv_font_t const *load_from_cache(std::string_view name, unsigned font_size = 0);
void add_font_to_cache(std::string_view name, unsigned font_size, lv_font_t *font);

} // namespace MetaModule::Fonts
