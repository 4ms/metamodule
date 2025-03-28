#pragma once

#include "meta5/ui.h"
#include <string_view>

namespace MetaModule
{

lv_obj_t *create_plugin_list_item(lv_obj_t *parent, const char *name);

enum class JackMapType { Input, Output };
lv_obj_t *create_jack_map_item(lv_obj_t *parent, JackMapType type, unsigned panel_jack_id, const char *name);

lv_obj_t *create_automap_item(lv_obj_t *parent, std::string_view name);

lv_obj_t *create_labeled_check_obj(lv_obj_t *parent, const char *name);

lv_obj_t *create_lv_list_button(lv_obj_t *parent, const char *name);

lv_obj_t *create_lv_roller(lv_obj_t *parent);

lv_obj_t *create_lv_labeled_popup(lv_obj_t *parent, const char *label_text);

lv_obj_t *create_button(lv_obj_t *parent, const char *name);

} // namespace MetaModule
