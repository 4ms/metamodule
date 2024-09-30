#pragma once
#include "lvgl.h"
#include <string_view>

namespace MetaModule
{

lv_font_t const *get_font(std::string_view name);
void free_font(std::string_view name);

} // namespace MetaModule
