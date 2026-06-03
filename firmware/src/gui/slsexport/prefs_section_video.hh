#include "lvgl.h"

namespace MetaModule
{

struct PrefsSectionVideo {
	lv_obj_t *mode_dropdown; // USB device mode: Console / Video / MIDI
	lv_obj_t *mirror_check;	 // Video-only: mirror X

	void create(lv_obj_t *parent);
};

} // namespace MetaModule
