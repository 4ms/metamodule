#include "prefs_section_catchup.hh"
#include "lvgl.h"
#include "ui_local.h"

namespace MetaModule
{

void PrefsSectionCatchupMode::create(lv_obj_t *parent) {

	create_prefs_section_title(parent, "KNOB CATCHUP MODE");

	auto cont = create_prefs_labeled_dropdown(parent, "Default Catchup Mode:");
	mode_dropdown = lv_obj_get_child(cont, 1);
	lv_obj_set_width(mode_dropdown, 185);

	prefs_cont_justify_multiline(cont);

	allowjump_cont = create_prefs_labeled_check(parent, "Allow jumping\nout-of-range params:");
	allowjump_check = lv_obj_get_child(allowjump_cont, 1);
}

} // namespace MetaModule
