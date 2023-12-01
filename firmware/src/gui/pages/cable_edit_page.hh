#pragma once
#include "gui/elements/element_name.hh"
#include "gui/helpers/lv_helpers.hh"
#include "gui/pages/base.hh"
#include "gui/pages/module_view_mapping_pane_list.hh"
#include "gui/pages/page_list.hh"
#include "gui/slsexport/ui_local.h"
#include "gui/styles.hh"
#include "pr_dbg.hh"

namespace MetaModule
{

struct CableEditPage : PageBase {
	CableEditPage(PatchInfo info)
		: PageBase{info}
		, patch{patch_storage.get_view_patch()} {
		PageList::register_page(this, PageId::CableEdit);

		init_bg(ui_CableMapPage);
	}

	void prepare_focus() override {
		auto cable_from_label = ui_comp_get_child(ui_CableFromEditButton, UI_COMP_MAPPEDKNOBSETITEM_KNOBSETNAMETEXT);
		lv_label_set_text(cable_from_label, "(Add connection)");

		lv_group_remove_all_objs(group);

		auto num_tos = lv_obj_get_child_cnt(ui_CableToPanel);
		for (unsigned i = 0; i < num_tos; i++) {
			auto child = lv_obj_get_child(ui_CableToPanel, i);
			lv_obj_del_async(child);
		}

		lv_group_add_obj(group, ui_CableFromEditButton);

		module_id = (uint16_t)PageList::get_selected_module_id();
		counts = PageList::get_selected_element_counts();
		indices = PageList::get_selected_element_indices();

		if (counts.num_inputs > 0) {
			Jack in_jack = {.module_id = module_id, .jack_id = indices.input_idx};
			auto *cable = patch.find_internal_cable_with_injack(in_jack);

			if (cable) {
				MappingPaneList::style_mappedcable_item(cable->out, ElementType::Output, patch, ui_CableFromEditButton);
				add_connected_inputs(cable);
			}

			add_mapped_in(patch.find_mapped_injack(in_jack));

		} else if (counts.num_outputs > 0) {
			out_jack = {.module_id = module_id, .jack_id = indices.output_idx};
			add_connected_inputs(patch.find_internal_cable_with_outjack(out_jack));

			add_mapped_out(patch.find_mapped_outjack(out_jack));
			MappingPaneList::style_mappedcable_item(out_jack, ElementType::Output, patch, ui_CableFromEditButton);

		} else
			return; //not an input or output

		lv_label_set_text(ui_CableMapPageTitle, in_jack_objs.size() > 0 ? "Edit Connections" : "Add Cable");

		lv_group_add_obj(group, ui_CableDeleteButton);
		lv_group_add_obj(group, ui_CableUndo);
	}

	void update() override {
		if (metaparams.meta_buttons[0].is_just_released()) {
			if (PageList::request_last_page()) {
				blur();
			}
		}
	}

	void blur() override {
		for (auto *c : in_jack_objs) {
			lv_obj_del_async(c);
		}
		in_jack_objs.clear();
	}

	void add_mapped_in(const MappedInputJack *mapped_in) {
		if (!mapped_in)
			return;

		MappingPaneList::style_panel_incable_item(mapped_in->panel_jack_id, ui_CableFromEditButton);

		InternalCable cable{.out = {}, .ins = mapped_in->ins};
		add_connected_inputs(&cable);
	}

	void add_mapped_out(const MappedOutputJack *mapped_out) {
		if (!mapped_out)
			return;

		printf("Create panel item (Out %ld) in CableToPanel\n", mapped_out->panel_jack_id);
		auto button = MappingPaneList::create_panel_outcable_item(mapped_out->panel_jack_id, ui_CableToPanel);

		lv_obj_add_flag(button, LV_OBJ_FLAG_FLEX_IN_NEW_TRACK);
		lv_group_add_obj(group, button);
		in_jack_objs.push_back(button);
	}

	void add_connected_inputs(InternalCable const *int_cable) {
		if (!int_cable)
			return;

		for (auto in : int_cable->ins) {
			printf("Create item in CableToPanel\n");
			auto button = MappingPaneList::create_cable_item(in, ElementType::Input, patch, ui_CableToPanel);
			lv_obj_add_flag(button, LV_OBJ_FLAG_FLEX_IN_NEW_TRACK);
			lv_group_add_obj(group, button);
			in_jack_objs.push_back(button);
		}
	}

private:
	PatchData &patch;

	std::vector<lv_obj_t *> in_jack_objs;
	Jack out_jack;
	// std::array<Jack, 8> in_jacks;

	// The jack that brought us to this page:
	uint16_t module_id = 0;
	ElementCount::Counts counts{};
	ElementCount::Indices indices{};
};

} // namespace MetaModule
