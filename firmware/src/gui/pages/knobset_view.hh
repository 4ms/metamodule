#pragma once
#include "CoreModules/elements/element_info.hh"
#include "gui/elements/element_name.hh"
#include "gui/elements/map_ring_animate.hh"
#include "gui/elements/module_drawer.hh"
#include "gui/elements/module_param.hh"
#include "gui/elements/update.hh"
#include "gui/images/faceplate_images.hh"
#include "gui/pages/base.hh"
#include "gui/pages/module_view_mapping_pane.hh"
#include "gui/pages/page_list.hh"
#include "gui/slsexport/meta5/ui.h"
#include "gui/styles.hh"

namespace MetaModule
{
struct KnobSetViewPage : PageBase {

	KnobSetViewPage(PatchInfo info)
		: PageBase{info}
		, base{ui_KnobSetViewPage} {
		PageList::register_page(this, PageId::KnobSetView);
		init_bg(base);
	}

	void prepare_focus() override {
	}

	void update() override {
		if (metaparams.meta_buttons[0].is_just_released()) {
			if (PageList::request_last_page()) {
				blur();
			}
		}
	}

	void blur() final {
		// drawn_elements.clear(); // doing this might lead to fragmentation?
	}

private:
	lv_obj_t *base = nullptr;
};

} // namespace MetaModule
