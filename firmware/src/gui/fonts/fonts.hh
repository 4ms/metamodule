#pragma once
#include <span>
#include <string_view>

typedef struct _lv_font_t lv_font_t;

namespace MetaModule
{

lv_font_t const *get_font(std::string_view name, std::string_view path = "");
void load_default_fonts();
float adjust_font_size(float fontSize, const void *font);

void free_font(std::string_view name);

} // namespace MetaModule
