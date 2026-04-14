#include "lvgl.h"

namespace MetaModule
{

struct PrefsSectionNotifications {
	lv_obj_t *amount_dropdown;
	lv_obj_t *animation_check;

	void create(lv_obj_t *parent);
};

} // namespace MetaModule
