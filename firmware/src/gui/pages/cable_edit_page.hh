
#pragma once
#include "gui/pages/base.hh"
#include "gui/pages/page_list.hh"
#include "gui/slsexport/meta5/ui.h"
#include "gui/styles.hh"
#include "pr_dbg.hh"

namespace MetaModule
{

struct CableEditPage : PageBase {
	CableEditPage(PatchInfo info)
		: PageBase{info} {
		PageList::register_page(this, PageId::PatchSel);

		init_bg(ui_CableMapPage);
	}

	void prepare_focus() override {
		lv_group_add_obj(group, ui_CableFromEditButton);
		lv_group_add_obj(group, ui_CableToEditButton1);
		lv_group_add_obj(group, ui_CableToEditButton2);
		lv_group_add_obj(group, ui_CableDeleteButton);
	}

	void update() override {
	}

	void blur() override {
	}

private:
};

} // namespace MetaModule
