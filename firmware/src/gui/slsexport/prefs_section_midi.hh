#include "../lib/cpputil/util/callable.hh"
#include "gui/pages/roller_popup.hh"
#include "lvgl.h"
#include "user_settings/midi_pc_settings.hh"
#include <vector>

namespace MetaModule
{

struct PrefsSectionMidi {
	lv_obj_t *feedback_check;
	lv_obj_t *midi_14bit_check;
	lv_obj_t *pc_patch_load_check;
	lv_obj_t *knobset_control_check;
	lv_obj_t *knobset_cc_dropdown;
	lv_obj_t *knobset_channel_dropdown;

	lv_obj_t *show_pc_table_button;

	MidiPCPatchLoadSettings *settings;

	void create(lv_obj_t *parent);

	void init_popup(lv_obj_t *parent, lv_group_t *group, MidiPCPatchLoadSettings &settings);
	bool close_popup();

	RollerPopup pc_roller{"MIDI PC LOAD PATCH:"};

	Function<void(std::string_view path)> on_patch_clicked;
	std::vector<MidiPCPatchLoadSettings::Entry> sorted_entries;

	static void show_pc_table(lv_event_t *event);
};

} // namespace MetaModule
