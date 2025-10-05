#include "prefs_section_fs.hh"
#include "ui_local.h"

namespace MetaModule
{

void PrefsSectionFilesystem::create(lv_obj_t *parent) {

	// Title
	create_prefs_section_title(parent, "Patch Files");

	// Startup Patch
	auto startup_cont = create_prefs_labeled_check(parent, "Startup Patch:");
	startup_patch_check = lv_obj_get_child(startup_cont, 1);

	// Statup patch name label:
	startup_patch_label = create_prefs_note(startup_cont, "");

	// Max Open Patches:
	auto max_cont =
		create_prefs_labeled_dropdown(parent, "Max Open Patches:", "2\n3\n4\n5\n6\n7\n8\n9\n10\n15\n20\n25");

	max_patches_dropdown = lv_obj_get_child(max_cont, 1);
	lv_obj_set_width(max_patches_dropdown, 50);

	create_prefs_note(max_cont, "Takes effect after restart");
}

} // namespace MetaModule
