#include "prefs_section_video.hh"
#include "ui_local.h"

namespace MetaModule
{

void PrefsSectionVideo::create(lv_obj_t *parent) {

	create_prefs_section_title(parent, "USB");

	auto role_cont = create_prefs_labeled_dropdown(parent, "USB Mode:", "Auto Host/Device\nForce Host\nForce Device");
	role_dropdown = lv_obj_get_child(role_cont, 1);
	lv_obj_set_width(role_dropdown, 150);

	create_prefs_note(role_cont, "Auto-detect host vs device,\nor force the USB-C port role");

	auto mode_cont = create_prefs_labeled_dropdown(parent, "Device Mode:", "Console\nVideo\nMIDI");
	mode_dropdown = lv_obj_get_child(mode_cont, 1);
	lv_obj_set_width(mode_dropdown, 110);

	create_prefs_note(mode_cont,
					  "When acting as a device:\nConsole: serial console\nVideo: screen as UVC device\nMIDI: USB-MIDI "
					  "port (replaces console)");

	auto mirror_cont = create_prefs_labeled_check(parent, "Mirror X:");
	mirror_check = lv_obj_get_child(mirror_cont, 1);

	create_prefs_note(mirror_cont, "Flip video horizontally");
}

} // namespace MetaModule
