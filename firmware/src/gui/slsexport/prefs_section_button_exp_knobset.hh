#include "lvgl.h"

namespace MetaModule
{

struct PrefsSectionButtonExpKnobSet {
	lv_obj_t *expander_dropdown;
	lv_obj_t *require_back_cont;
	lv_obj_t *require_back_check;

	void create(lv_obj_t *parent);
};

} // namespace MetaModule
