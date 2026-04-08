#include "prefs_section_button_exp_knobset.hh"
#include "lvgl.h"
#include "ui_local.h"

namespace MetaModule
{

void PrefsSectionButtonExpKnobSet::create(lv_obj_t *parent) {

	create_prefs_section_title(parent, "BUTTON EXP. KNOB SET SELECT");

	auto cont = create_prefs_labeled_dropdown(parent, "Button Expander #:", "Disabled\n1\n2\n3\n4");
	expander_dropdown = lv_obj_get_child(cont, 1);
	lv_obj_set_width(expander_dropdown, 110);

	require_back_cont = create_prefs_labeled_check(parent, "With Back button\npressed:");
	require_back_check = lv_obj_get_child(require_back_cont, 1);
}

} // namespace MetaModule
