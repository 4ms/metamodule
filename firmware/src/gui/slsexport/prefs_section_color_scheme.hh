#include "lvgl.h"

namespace MetaModule
{

struct PrefsSectionColorScheme {
	lv_obj_t *scheme_dropdown;

	void create(lv_obj_t *parent);
};

} // namespace MetaModule
