#pragma once
#include "CoreModules/info/module_info_base.hh"
#include "lvgl/src/core/lv_obj_pos.h"
#include "pages/base.hh"
#include "pages/draw_helpers.hh"
#include "pages/images/image_list.hh"
#include "pages/page_list.hh"
#include "pages/styles.hh"
#include <string>

LV_IMG_DECLARE(knob_large_x);

namespace MetaModule
{
struct KnobEditPage : PageBase {

	KnobEditPage(PatchInfo info)
		: PageBase{info}
		, base(lv_obj_create(nullptr)) {
		PageList::register_page(this, PageId::KnobEdit);

		init_bg(base);

		knob_name = lv_label_create(base);
		lv_obj_add_style(knob_name, &Gui::header_style, LV_PART_MAIN);
		lv_obj_set_width(knob_name, 248);
		lv_obj_set_height(knob_name, 28);

		// lv_group_add_obj(group, roller);
		// lv_obj_add_event_cb(roller, roller_cb, LV_EVENT_KEY, this);
	}

	void prepare_focus() override {
		this_module_id = PageList::get_selected_module_id();

		if (!read_slug()) {
			mbox.append_message("Knob Edit page cannot read module slug.\n");
			return;
		}

		lv_label_set_text(knob_name, "Test Knobs");
		// printf("ModuleViewPage module %s\n", slug.data());

		// auto moduleinfo = ModuleFactory::getModuleInfo(slug);
		// if (moduleinfo.width_hp == 0) {
		// 	mbox.append_message("Module View page got empty module slug.\r\n");
		// 	return;
		// }

		// reset_module_page();
	}

	void update() override {
		if (metaparams.meta_buttons[0].is_just_released()) {
			if (PageList::request_last_page()) {
				blur();
			}
		}
	}

private:
	void reset_page() {
	}

	bool read_slug() {
		auto module_id = PageList::get_selected_module_id();
		auto patch_id = PageList::get_selected_patch_id();
		const PatchData &patch = patch_list.get_patch(patch_id);
		if (patch.patch_name.length() == 0)
			return false;
		if (module_id >= patch.module_slugs.size())
			return false;

		slug = patch.module_slugs[module_id];
		return true;
	}

	uint16_t this_module_id;
	uint16_t this_param_id;
	ModuleTypeSlug slug;

	lv_obj_t *base = nullptr;
	lv_obj_t *knob_name;
};

} // namespace MetaModule
