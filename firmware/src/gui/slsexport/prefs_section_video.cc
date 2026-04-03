#include "prefs_section_video.hh"
#include "ui_local.h"

namespace MetaModule
{

void PrefsSectionVideo::create(lv_obj_t *parent) {

	create_prefs_section_title(parent, "Video");

	auto video_cont = create_prefs_labeled_check(parent, "USB Video Output:");
	enabled_check = lv_obj_get_child(video_cont, 1);

	create_prefs_note(video_cont, "Stream screen over USB\nas a UVC video device");

	auto mirror_cont = create_prefs_labeled_check(parent, "Mirror X:");
	mirror_check = lv_obj_get_child(mirror_cont, 1);

	create_prefs_note(mirror_cont, "Flip video horizontally");
}

} // namespace MetaModule
