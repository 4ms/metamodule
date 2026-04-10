#include "prefs_section_notifications.hh"
#include "ui_local.h"

namespace MetaModule
{

void PrefsSectionNotifications::create(lv_obj_t *parent) {

	create_prefs_section_title(parent, "NOTIFICATIONS");

	auto amount_cont = create_prefs_labeled_dropdown(parent, "Show:", "All\nFewer\nOnly Critical");
	amount_dropdown = lv_obj_get_child(amount_cont, 1);
	lv_obj_set_width(amount_dropdown, 110);

	auto anim_cont = create_prefs_labeled_check(parent, "Animations:");
	animation_check = lv_obj_get_child(anim_cont, 1);
}

} // namespace MetaModule
