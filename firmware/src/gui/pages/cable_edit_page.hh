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

	CableEditPage(PatchContext info)
		: PageBase{info, PageId::CableEdit}
		, patch{patch_storage.get_view_patch()} {

		init_bg(ui_CableMapPage);
	}

	void prepare_focus() override {
		// blur();

		lv_group_remove_all_objs(group);

		// lv_foreach_child(ui_CableToPanel, [](auto *obj, unsigned) {
		// 	lv_obj_del_async(obj);
		// 	return true;
		// });

		// lv_group_add_obj(group, ui_CableFromEditButton);

		if (!args.module_id || !args.element_counts || !args.element_indices) {
			pr_err("Missing page argument for cable edit page\n");
			return;
		}

		module_id = args.module_id.value();
		counts = args.element_counts.value();
		indices = args.element_indices.value();

		if (counts.num_inputs > 0) {
			find_connections_to_input_jack();
		} else if (counts.num_outputs > 0) {
			find_connections_to_output_jack();
		} else {
			pr_err("Error: no jack specified\n");
			return;
		}

		if (in_jack_objs.size() == 0) {
			show_add_cable();
		} else {
			show_edit_cable();
		}

		lv_group_add_obj(group, ui_CableDeleteButton);
		lv_group_add_obj(group, ui_CableCancel);
	}

	void update() override {
		if (metaparams.meta_buttons[0].is_just_released()) {
			page_list.request_last_page();
		}
	}

	void blur() override {
		for (auto *c : in_jack_objs) {
			lv_obj_del_async(c);
		}
		in_jack_objs.clear();
	}

	// Mapped Panel Output == technically an Input jack, so it's in the "To" section
	void add_panel_output(const MappedOutputJack *mapped_out) {
		if (!mapped_out)
			return;

		printf("Create panel item (Out %u) in CableToPanel\n", (unsigned)mapped_out->panel_jack_id);
		auto button = MappingPaneList::create_panel_outcable_item(mapped_out->panel_jack_id, ui_CableToPanel);

		lv_obj_add_flag(button, LV_OBJ_FLAG_FLEX_IN_NEW_TRACK);
		lv_group_add_obj(group, button);
		in_jack_objs.push_back(button);
	}

	void add_connected_inputs(InternalCable const *int_cable) {
		if (!int_cable)
			return;

		for (auto in : int_cable->ins) {
			add_input_jack(in);
		}
	}

	void add_input_jack(Jack const &in) {
		pr_trace("Create item in CableToPanel\n");
		auto button = MappingPaneList::create_cable_item(in, ElementType::Input, patch, ui_CableToPanel);
		lv_obj_add_flag(button, LV_OBJ_FLAG_FLEX_IN_NEW_TRACK);
		lv_group_add_obj(group, button);
		in_jack_objs.push_back(button);
	}

private:
	PatchData &patch;

	std::vector<lv_obj_t *> in_jack_objs;
	Jack out_jack{};
	// std::array<Jack, 8> in_jacks;

	// The jack that brought us to this page:
	uint16_t module_id = 0;
	ElementCount::Counts counts{};
	ElementCount::Indices indices{};

	void find_connections_to_input_jack() {
		no_from_jack(); //default

		Jack in_jack = {.module_id = module_id, .jack_id = indices.input_idx};
		add_input_jack(in_jack);

		// Look for connected internal cables
		auto *cable = patch.find_internal_cable_with_injack(in_jack);
		if (cable) {
			MappingPaneList::style_mappedcable_item(cable->out, ElementType::Output, patch, ui_CableFromEditButton);
			add_connected_inputs(cable);
		}

		// Look for mapped panel jacks
		auto mapped_cable = patch.find_mapped_injack(in_jack);
		if (mapped_cable) {
			MappingPaneList::style_panel_incable_item(mapped_cable->panel_jack_id, ui_CableFromEditButton);
			InternalCable cable{.out = {}, .ins = mapped_cable->ins};
			add_connected_inputs(&cable);
		}
	}

	void find_connections_to_output_jack() {
		out_jack = {.module_id = module_id, .jack_id = indices.output_idx};
		add_connected_inputs(patch.find_internal_cable_with_outjack(out_jack));

		add_panel_output(patch.find_mapped_outjack(out_jack));
		MappingPaneList::style_mappedcable_item(out_jack, ElementType::Output, patch, ui_CableFromEditButton);
	}

	void no_from_jack() {
		auto cable_outjack_label = ui_comp_get_child(ui_CableFromEditButton, UI_COMP_MAPPEDKNOBSETITEM_KNOBSETNAMETEXT);
		lv_label_set_text(cable_outjack_label, "(Connect to a jack)");

		auto cable_outjack_circle = ui_comp_get_child(ui_CableFromEditButton, UI_COMP_MAPPEDKNOBSETITEM_CIRCLE);
		lv_hide(cable_outjack_circle);
	}

	void show_add_cable() {
		lv_label_set_text(ui_CableMapPageTitle, "Add Cable");
	}

	void show_edit_cable() {
		lv_label_set_text(ui_CableMapPageTitle, "Edit Cable");
	}
};

} // namespace MetaModule
