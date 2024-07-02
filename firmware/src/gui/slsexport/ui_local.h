#pragma once
#include "meta5/ui.h"
#include <string_view>

namespace MetaModule
{

lv_obj_t *create_plugin_list_item(lv_obj_t *parent, const char *name);

enum class JackMapType { Input, Output };
lv_obj_t *create_jack_map_item(lv_obj_t *parent, JackMapType type, unsigned panel_jack_id, const char *name);

lv_obj_t *create_automap_item(lv_obj_t *parent, std::string_view name);

} // namespace MetaModule
