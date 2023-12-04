#pragma once
#include "gui/pages/base.hh"
#include "gui/pages/page_list.hh"
#include "gui/slsexport/meta5/ui.h"

namespace MetaModule
{

struct MainMenuPage : PageBase {
	MainMenuPage(PatchInfo info)
		: PageBase{info, PageId::MainMenu} {
		init_bg(ui_MainMenu);
		lv_group_remove_all_objs(group);
		lv_group_add_obj(group, ui_MenuPanelPatches);
		lv_group_add_obj(group, ui_MenuPanelSave);
		lv_group_add_obj(group, ui_MenuPanelSettings);
		lv_group_focus_obj(ui_MenuPanelPatches);
	}

	void prepare_focus() final {
		;
	}

	void update() final {
		;
	}

	void blur() final {
		;
	}
};

} // namespace MetaModule
