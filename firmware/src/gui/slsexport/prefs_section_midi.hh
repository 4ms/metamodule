#include "lvgl.h"

namespace MetaModule
{

struct PrefsSectionMidi {
	lv_obj_t *feedback_check;

	void create(lv_obj_t *parent);
};

} // namespace MetaModule
