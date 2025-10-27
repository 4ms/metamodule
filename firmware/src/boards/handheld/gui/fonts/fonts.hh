#pragma once
#include "src/font/lv_font.h"
#include <string_view>

typedef struct _lv_font_t lv_font_t;

LV_FONT_DECLARE(Segment14_10);
LV_FONT_DECLARE(Segment14_12);
LV_FONT_DECLARE(Segment14_14);
LV_FONT_DECLARE(Segment14_16);
LV_FONT_DECLARE(Segment14_20);
LV_FONT_DECLARE(Segment14_24);
LV_FONT_DECLARE(Segment14_26);
LV_FONT_DECLARE(Segment7Standard_14);
LV_FONT_DECLARE(Segment7Standard_20);
LV_FONT_DECLARE(ui_font_MuseoSansRounded50010);
LV_FONT_DECLARE(ui_font_MuseoSansRounded50012);
LV_FONT_DECLARE(ui_font_MuseoSansRounded50014);
LV_FONT_DECLARE(ui_font_MuseoSansRounded50016);
LV_FONT_DECLARE(ui_font_MuseoSansRounded70014);
LV_FONT_DECLARE(ui_font_MuseoSansRounded70016);
LV_FONT_DECLARE(ui_font_MuseoSansRounded90018);
LV_FONT_DECLARE(ui_font_MuseoSansRounded90040);
LV_FONT_DECLARE(ui_font_Segment32);
LV_FONT_DECLARE(ui_font_Segment7Standard24);

namespace MetaModule::Fonts
{

lv_font_t const *get_font(std::string_view name);
void free_font(std::string_view name);

lv_font_t const *load_from_cache(std::string_view name, unsigned font_size = 0);
void add_font_to_cache(std::string_view name, unsigned font_size, lv_font_t *font);

} // namespace MetaModule::Fonts
