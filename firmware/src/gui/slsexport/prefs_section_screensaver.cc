#include "prefs_section_screensaver.hh"
#include "ui_local.h"

namespace MetaModule
{

void PrefsSectionScreenSaver::create(lv_obj_t *parent) {

	create_prefs_section_title(parent, "SCREENSAVER");

	auto screensaver_cont = create_prefs_labeled_dropdown(
		parent, "Timeout:", "Never\n30 Sec\n1 Min\n5 Min\n10 Min\n30 Min\n1 Hour\n4 Hours");

	time_dropdown = lv_obj_get_child(screensaver_cont, 1);
	lv_obj_set_width(time_dropdown, 90);

	auto ss_knobs_cont = create_prefs_labeled_check(parent, "Wake with knob");
	knobs_check = lv_obj_get_child(ss_knobs_cont, 1);
}

} // namespace MetaModule
