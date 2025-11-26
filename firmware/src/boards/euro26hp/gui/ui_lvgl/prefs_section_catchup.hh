#include "lvgl.h"

namespace MetaModule
{

struct PrefsSectionCatchupMode {
	lv_obj_t *mode_dropdown;
	lv_obj_t *allowjump_cont;
	lv_obj_t *allowjump_check;

	void create(lv_obj_t *parentTab);
};

} // namespace MetaModule
