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
		, base(lv_obj_create(nullptr))
		, knob_name(lv_label_create(base))
		, mapped_info(lv_label_create(base))
		, manual_knob(lv_arc_create(base)) {
		PageList::register_page(this, PageId::KnobEdit);

		init_bg(base);
		lv_obj_set_flex_flow(base, LV_FLEX_FLOW_ROW_WRAP);
		lv_obj_set_flex_align(base, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_END, LV_FLEX_ALIGN_START);

		lv_obj_add_style(knob_name, &Gui::header_style, LV_PART_MAIN);
		lv_obj_set_width(knob_name, 320);
		lv_obj_set_height(knob_name, 28);

		lv_obj_add_style(mapped_info, &Gui::text_block_style, LV_PART_MAIN);
		lv_obj_set_width(mapped_info, 320);
		lv_obj_set_height(mapped_info, 20);

		// lv_arc_set_adjustable(manual_knob, true);
		lv_obj_set_size(manual_knob, 50, 50);
		lv_arc_set_rotation(manual_knob, 135);
		lv_arc_set_bg_angles(manual_knob, 0, 270);
		lv_arc_set_value(manual_knob, 40);
	}

	void prepare_focus() override {
		// Get relevant data: module, patch, param info:

		this_module_id = PageList::get_selected_module_id();
		auto patch_id = PageList::get_selected_patch_id();
		const auto &patch = patch_list.get_patch(patch_id);
		if (patch.patch_name.length() == 0) {
			msg_queue.append_message("Patch name empty\n");
			return;
		}
		if (this_module_id >= patch.module_slugs.size()) {
			msg_queue.append_message("Module has invalid ID\n");
			return;
		}
		slug = patch.module_slugs[this_module_id];

		if (!slug.length()) {
			msg_queue.append_message("Module has invalid slug\n");
			return;
		}

		auto moduleinfo = ModuleFactory::getModuleInfo(slug);
		if (moduleinfo.width_hp == 0) {
			msg_queue.append_message("Knob Edit page got empty module slug.\n");
			return;
		}

		// Knob name label
		auto this_param = PageList::get_selected_param();
		std::string nm;
		nm.reserve(40);
		nm.append(slug.c_str());
		nm.append(" knob: ");
		nm.append(moduleinfo.Knobs[this_param.id].long_name);
		lv_label_set_text(knob_name, nm.c_str());

		nm.clear();

		// Mapped/unmapped label
		auto mappedknob = patch.find_mapped_knob(PageList::get_selected_module_id(), this_param.id);
		if (mappedknob && mappedknob->panel_knob_id < PanelDef::NumKnobs) {
			nm.append("Mapped to Knob ");
			nm.append(PanelDef::KnobNames[mappedknob->panel_knob_id]);
			//nm.append(" in Set __");
			//edit button
		} else {
			nm.append("Not mapped");
			//add mapping button
		}
		lv_label_set_text(mapped_info, nm.c_str());

		//patch.mapped_knobs[
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

		return true;
	}

	uint16_t this_module_id;
	// uint16_t this_param_id;
	ModuleTypeSlug slug;

	lv_obj_t *base = nullptr;
	lv_obj_t *knob_name;
	lv_obj_t *mapped_info;
	lv_obj_t *manual_knob;
};

} // namespace MetaModule
