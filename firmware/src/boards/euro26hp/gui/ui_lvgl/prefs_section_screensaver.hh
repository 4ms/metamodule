#include "lvgl.h"

namespace MetaModule
{

struct PrefsSectionScreenSaver {
	lv_obj_t *time_dropdown;
	lv_obj_t *knobs_check;

	void create(lv_obj_t *parent);
};

} // namespace MetaModule
