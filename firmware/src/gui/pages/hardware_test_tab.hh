#pragma once
#include "gui/helpers/lv_helpers.hh"
#include "gui/pages/base.hh"
#include "gui/pages/page_list.hh"
#include "gui/slsexport/meta5/ui.h"
#include "gui/styles.hh"

namespace MetaModule
{

struct HardwareTestTab {

	void prepare_focus(lv_group_t *group) {
		this->group = group;
	}

	void update() {
	}

private:
	lv_group_t *group = nullptr;
};
} // namespace MetaModule
