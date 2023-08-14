#include "./meta5/components/ui_comp.h"
#include "lvgl.h"

// Used to force init of this constant, which must happen before
// SLS-exported pages are init
struct SlsComponentInit {
	SlsComponentInit() {
		LV_EVENT_GET_COMP_CHILD = lv_event_register_id();
	}
};
