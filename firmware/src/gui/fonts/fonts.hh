#pragma once
// #include "lvgl.h"
#include <string_view>

typedef struct _lv_font_t lv_font_t;

namespace MetaModule
{

lv_font_t const *get_font(std::string_view name);
lv_font_t const *get_font_from_handle(int handle);

int get_handle_from_name(const char *name);
int get_handle_from_font(lv_font_t const *font);

void free_font(std::string_view name);

} // namespace MetaModule
