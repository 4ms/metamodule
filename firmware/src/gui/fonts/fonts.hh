#pragma once
#include <span>
#include <string_view>

typedef struct _lv_font_t lv_font_t;

namespace MetaModule
{

lv_font_t const *get_font(std::string_view name, std::string_view path = "");

lv_font_t const *load_ttf_from_memory(std::string_view name, std::span<uint8_t> data);

void free_font(std::string_view name);

} // namespace MetaModule
