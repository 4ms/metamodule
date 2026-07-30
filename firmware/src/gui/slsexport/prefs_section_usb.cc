#include "prefs_section_usb.hh"
#include "ui_local.h"

namespace MetaModule
{

void PrefsSectionUSB::create(lv_obj_t *parent) {

	create_prefs_section_title(parent, "USB");

	auto role_cont = create_prefs_labeled_dropdown(parent, "USB Mode:", "Auto\nHost Only\nDevice Only");
	role_dropdown = lv_obj_get_child(role_cont, 1);
	lv_obj_set_width(role_dropdown, 110);

	create_prefs_note(role_cont, "Select if MetaModule can be\n a USB host, device, or both\n");

	auto mode_cont = create_prefs_labeled_dropdown(parent, "Device Mode:", "MIDI\nVideo");
	device_mode_dropdown = lv_obj_get_child(mode_cont, 1);
	lv_obj_set_width(device_mode_dropdown, 90);

	create_prefs_note(mode_cont, "Select USB function when\nconnecting to a computer.");

	auto mirror_cont = create_prefs_labeled_check(parent, "Video Mirror X:");
	mirror_check = lv_obj_get_child(mirror_cont, 1);

	create_prefs_note(mirror_cont, "Flip USB video horizontally");
}

} // namespace MetaModule
