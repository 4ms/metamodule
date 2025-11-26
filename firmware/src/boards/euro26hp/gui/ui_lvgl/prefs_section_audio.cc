#include "prefs_section_audio.hh"
#include "ui_local.h"

namespace MetaModule
{

void PrefsSectionAudio::create(lv_obj_t *parent) {
	create_prefs_section_title(parent, "AUDIO SETTINGS");

	// Sample Rate:
	auto sr_cont = create_prefs_labeled_dropdown(parent, "Sample Rate:", "24kHz\n32kHz\n48kHz\n96kHz");
	samplerate_dropdown = lv_obj_get_child(sr_cont, 1);
	samplerate_label = lv_obj_get_child(sr_cont, 0);
	lv_obj_set_width(samplerate_dropdown, 90);

	// Current Samplerate Override
	sr_override_cont = create_aligned_text_row(parent, "Patch override:");
	sr_override_label = lv_obj_get_child(sr_override_cont, 1);

	// Samplerate allow override checkbox
	auto sr_override_cont = create_prefs_labeled_check(parent, "Allow patch to override:");
	auto sr_override_label = lv_obj_get_child(sr_override_cont, 0);
	sr_override_check = lv_obj_get_child(sr_override_cont, 1);
	lv_obj_set_style_text_font(sr_override_label, &ui_font_MuseoSansRounded50014, LV_PART_MAIN);

	// Block Size:
	auto bs_cont = create_prefs_labeled_dropdown(parent, "Block Size:", "32\n64\n128\n256\n512");
	blocksize_dropdown = lv_obj_get_child(bs_cont, 1);
	blocksize_label = lv_obj_get_child(bs_cont, 0);
	lv_obj_set_width(blocksize_dropdown, 60);

	// Current Blocksize Override
	bs_override_cont = create_aligned_text_row(parent, "Patch override:");
	bs_override_label = lv_obj_get_child(bs_override_cont, 1);

	// Blocksize allow override checkbox
	auto bs_override_cont = create_prefs_labeled_check(parent, "Allow patch to override:");
	auto bs_override_label = lv_obj_get_child(bs_override_cont, 0);
	bs_override_check = lv_obj_get_child(bs_override_cont, 1);
	lv_obj_set_style_text_font(bs_override_label, &ui_font_MuseoSansRounded50014, LV_PART_MAIN);

	auto audio_retry_cont =
		create_prefs_labeled_dropdown(parent, "Overrun retries:", "None\n4\n8\n16\n32\n64\n128\n256");
	overrun_retries = lv_obj_get_child(audio_retry_cont, 1);
	lv_obj_set_width(overrun_retries, 75);
}

} // namespace MetaModule
