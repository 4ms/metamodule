#pragma once
#include "meta5/ui.h"

namespace MetaModule
{

lv_obj_t *create_plugin_list_item(lv_obj_t *parent, const char *name);

enum class JackMapType { Input, Output };
lv_obj_t *create_jack_map_item(lv_obj_t *parent, JackMapType type, unsigned panel_jack_id, const char *name);

} // namespace MetaModule
