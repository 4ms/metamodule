#include "lvgl.h"

namespace MetaModule
{

struct PrefsSectionVideo {
	lv_obj_t *enabled_check;

	void create(lv_obj_t *parent);
};

} // namespace MetaModule
