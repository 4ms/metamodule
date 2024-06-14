#pragma once
#include "lvgl.h"

namespace MetaModule
{

struct SystemMenuTab {

	virtual void prepare_focus(lv_group_t *group) {
	}

	// Returns true if this pages uses the back event
	virtual bool consume_back_event() {
		return false;
	}

	virtual void update() {
	}
};

} // namespace MetaModule
