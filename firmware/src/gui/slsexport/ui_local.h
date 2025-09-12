#pragma once

#include "meta5/ui.h"
#include <string_view>

namespace MetaModule
{

lv_obj_t *create_plugin_list_item(lv_obj_t *parent, const char *name);
lv_obj_t *create_plugin_list_version_item(lv_obj_t *parent, const char *name);

enum class JackMapType { Input, Output, MIDI };
lv_obj_t *create_jack_map_item(lv_obj_t *parent, JackMapType type, unsigned panel_jack_id, const char *name);

lv_obj_t *create_automap_item(lv_obj_t *parent, std::string_view name);

lv_obj_t *create_labeled_check_obj(lv_obj_t *parent, const char *name);

lv_obj_t *create_lv_list_button(lv_obj_t *parent, const char *name);

lv_obj_t *create_lv_roller(lv_obj_t *parent);

lv_obj_t *create_lv_labeled_popup(lv_obj_t *parent, const char *label_text);

lv_obj_t *create_button(lv_obj_t *parent, const char *name);

lv_obj_t *create_settings_menu_switch(lv_obj_t *parent, std::string const &onoff_label_text);
lv_obj_t *create_settings_menu_slider(lv_obj_t *parent, std::string const &slider_text);

lv_obj_t *create_settings_menu_title(lv_obj_t *parent, std::string const &title_name);

lv_obj_t *create_file_menu_item(lv_obj_t *parent, std::string_view text);

lv_obj_t *create_midi_map_check(lv_obj_t *parent);
lv_obj_t *create_midi_map_label(lv_obj_t *parent, std::string const &title);
lv_obj_t *create_midi_map_dropdown(lv_obj_t *parent, std::string const &options);

lv_obj_t *create_button_expander_item(lv_obj_t *parent);
lv_obj_t *create_button_expander_pane(lv_obj_t *parent);

} // namespace MetaModule
