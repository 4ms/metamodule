#include "lvgl.h"

namespace MetaModule
{

struct PrefsSectionMidi {
	lv_obj_t *feedback_check;
	lv_obj_t *knobset_control_check;
	lv_obj_t *knobset_cc_dropdown;
	lv_obj_t *knobset_channel_dropdown;

	void create(lv_obj_t *parent);
};

} // namespace MetaModule
