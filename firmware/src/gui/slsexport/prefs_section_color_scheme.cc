#include "prefs_section_color_scheme.hh"
#include "ui_local.h"

namespace MetaModule
{

void PrefsSectionColorScheme::create(lv_obj_t *parent) {

	create_prefs_section_title(parent, "COLOR SCHEME");

	auto cont = create_prefs_labeled_dropdown(parent, "Theme:");
	scheme_dropdown = lv_obj_get_child(cont, 1);
	lv_obj_set_width(scheme_dropdown, 120);
}

} // namespace MetaModule
