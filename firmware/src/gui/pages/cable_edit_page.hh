
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
		: PageBase{info}
		, patch{patch_storage.get_view_patch()} {
		PageList::register_page(this, PageId::PatchSel);

		init_bg(ui_CableMapPage);
	}

	void prepare_focus() override {
		module_id = (uint16_t)PageList::get_selected_module_id();
		counts = PageList::get_selected_element_counts();
		indices = PageList::get_selected_element_indices();

		// std::vector<Jack> in_jacks;

		InternalCable cable;

		if (counts.num_inputs > 0) {
			// base_jack.jack_id = indices.input_idx;

		} else if (counts.num_outputs > 0) {
			// We know the output jack, scan int_cables and mapped_outs
			Jack out_jack{.module_id = module_id, .jack_id = indices.output_idx};

			bool found = false;
			for (auto &c : patch_storage.get_view_patch().int_cables) {
				if (c.out == out_jack) {
					cable = c;
					found = true;
					break;
				}
			}
			if (!found) {
				// Handle add cable from out_jack
			}

		} else
			return; //not an input or output

		lv_group_remove_all_objs(group);
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
	PatchData &patch;
	uint16_t module_id = 0;
	ElementCount::Counts counts{};
	ElementCount::Indices indices{};
};

} // namespace MetaModule
