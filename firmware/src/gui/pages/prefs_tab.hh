#pragma once
#include "gui/pages/system_menu_tab_base.hh"
#include "gui/slsexport/meta5/ui.h"

namespace MetaModule
{

struct PrefsTab : SystemMenuTab {

	void prepare_focus(lv_group_t *group) override {
		this->group = group;
	}

private:
	lv_group_t *group = nullptr;
};

} // namespace MetaModule
