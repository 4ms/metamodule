#include "prefs_section_missing_plugins.hh"
#include "ui_local.h"

namespace MetaModule
{

void PrefsSectionMissingPlugins::create(lv_obj_t *parent) {
	create_prefs_section_title(parent, "MISSING PLUGINS");

	auto cont = create_prefs_labeled_dropdown(parent, "Search for missing plugins:", "Ask\nAlways\nNever");

	dropdown = lv_obj_get_child(cont, 1);
	lv_obj_set_width(dropdown, 95);

	prefs_cont_justify_multiline(cont);
}

} // namespace MetaModule
