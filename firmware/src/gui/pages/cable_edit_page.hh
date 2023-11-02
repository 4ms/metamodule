
#pragma once
#include "gui/elements/element_name.hh"
#include "gui/elements/helpers.hh"
#include "gui/pages/base.hh"
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
		lv_group_remove_all_objs(group);

		num_inputs = 0;
		auto num_tos = lv_obj_get_child_cnt(ui_CableToPanel);
		for (unsigned i = 0; i < num_tos; i++) {
			auto child = lv_obj_get_child(ui_CableToPanel, i);
			lv_obj_del_async(child);
		}

		lv_label_set_text(ui_CableFromLabel, "");
		lv_group_add_obj(group, ui_CableFromEditButton);

		module_id = (uint16_t)PageList::get_selected_module_id();
		counts = PageList::get_selected_element_counts();
		indices = PageList::get_selected_element_indices();

		if (counts.num_inputs > 0) {
			printf("Node with input jack %d on module %d\n", indices.input_idx, module_id);
			Jack in_jack = {.module_id = module_id, .jack_id = indices.input_idx};
			auto *cable = patch.find_internal_cable_with_injack(in_jack);

			if (cable) {
				auto outname =
					get_full_element_name(cable->out.module_id, cable->out.jack_id, ElementType::Output, patch);
				lv_label_set_text_fmt(
					ui_CableFromLabel, "%s %s", outname.module_name.data(), outname.element_name.data());
				add_connected_inputs(cable);
			}

			add_mapped_in(patch.find_mapped_injack(in_jack));

			lv_label_set_text(ui_CableMapPageTitle, num_inputs ? "Edit Connections" : "Add Cable");

		} else if (counts.num_outputs > 0) {
			// We know the output jack, scan int_cables and mapped_outs
			out_jack = {.module_id = module_id, .jack_id = indices.output_idx};
			num_inputs = 0;

			add_connected_inputs(patch.find_internal_cable_with_outjack(out_jack));

			add_mapped_out(patch.find_mapped_outjack(out_jack));

			auto outname = get_full_element_name(module_id, indices.output_idx, ElementType::Output, patch);
			lv_label_set_text_fmt(ui_CableFromLabel, "%s %s", outname.module_name.data(), outname.element_name.data());
			lv_label_set_text(ui_CableMapPageTitle, num_inputs ? "Edit Connections" : "Add Cable");

		} else
			return; //not an input or output

		lv_group_add_obj(group, ui_CableDeleteButton);
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
			lv_obj_del(c);
		}
		in_jack_objs.clear();
	}

	void add_mapped_in(const MappedInputJack *mapped_in) {
		if (!mapped_in)
			return;

		if (mapped_in->alias_name.size()) {
			lv_label_set_text_fmt(ui_CableFromLabel, "Panel %s", mapped_in->alias_name.c_str());
		} else {
			auto name = get_panel_name<PanelDef>(JackInput{}, mapped_in->panel_jack_id);
			lv_label_set_text_fmt(ui_CableFromLabel, "Panel %s", name.c_str());
		}

		InternalCable cable{.out = {}, .ins = mapped_in->ins};
		add_connected_inputs(&cable);
	}

	void add_mapped_out(const MappedOutputJack *mapped_out) {
		if (!mapped_out)
			return;

		auto button = ui_CableToEditButton_create(ui_CableToPanel);
		auto label = ui_comp_get_child(button, UI_COMP_CABLETOEDITBUTTON_CABLETOLABEL);
		lv_group_add_obj(group, button);
		in_jack_objs.push_back(button);

		if (mapped_out->alias_name.size()) {
			lv_label_set_text_fmt(label, "Panel %s", mapped_out->alias_name.c_str());
		} else {
			auto name = get_panel_name<PanelDef>(JackOutput{}, mapped_out->panel_jack_id);
			lv_label_set_text_fmt(label, "Panel %s", name.c_str());
		}
	}

	void add_connected_inputs(InternalCable const *int_cable) {
		if (!int_cable)
			return;

		for (auto in : int_cable->ins) {
			auto button = ui_CableToEditButton_create(ui_CableToPanel);
			auto label = ui_comp_get_child(button, UI_COMP_CABLETOEDITBUTTON_CABLETOLABEL);
			lv_group_add_obj(group, button);
			in_jack_objs.push_back(button);

			auto inname = get_full_element_name(in.module_id, in.jack_id, ElementType::Input, patch);
			lv_label_set_text_fmt(label, "%s %s", inname.module_name.data(), inname.element_name.data());
		}
	}

private:
	PatchData &patch;

	std::vector<lv_obj_t *> in_jack_objs;
	Jack out_jack;
	// std::array<Jack, 8> in_jacks;
	size_t num_inputs = 0;

	// The jack that brought us to this page:
	uint16_t module_id = 0;
	ElementCount::Counts counts{};
	ElementCount::Indices indices{};
};

} // namespace MetaModule
