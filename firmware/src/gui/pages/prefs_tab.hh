#pragma once
#include "dynload/plugin_loader.hh"
#include "gui/helpers/lv_helpers.hh"
#include "gui/pages/base.hh"
#include "gui/pages/page_list.hh"
#include "gui/slsexport/meta5/ui.h"
#include "gui/styles.hh"

namespace MetaModule
{

struct PrefsTab {

	PrefsTab() = default;

	void prepare_focus(lv_group_t *group) {
		this->group = group;
	}

	// Returns true if this pages uses the back event
	bool consume_back_event() {
		return false;
	}

	void update() {
	}

private:
	lv_group_t *group = nullptr;
};

} // namespace MetaModule
