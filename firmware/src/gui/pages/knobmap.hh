#pragma once
#include "gui/pages/base.hh"
#include "gui/pages/page_list.hh"
#include "gui/slsexport/meta5/ui.h"
#include "gui/styles.hh"

namespace MetaModule
{
struct KnobMapPage : PageBase {

	KnobMapPage(PatchInfo info)
		: PageBase{info}
		, base{ui_EditMappingPage}
		, patch{patch_storage.get_view_patch()} {
		PageList::register_page(this, PageId::KnobMap);
		init_bg(base);
		lv_group_set_editing(group, false);
	}

	void prepare_focus() override {

		lv_group_set_editing(group, false);
	}

	void update() override {
		if (metaparams.meta_buttons[0].is_just_released()) {
			if (PageList::request_last_page()) {
				blur();
			}
		}
	}

	void blur() final {
	}

private:
	lv_obj_t *base = nullptr;
	PatchData &patch;
};

} // namespace MetaModule
