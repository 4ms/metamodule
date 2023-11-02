
#pragma once
#include "gui/elements/element_name.hh"
#include "gui/elements/helpers.hh"
#include "gui/pages/base.hh"
#include "gui/pages/page_list.hh"
#include "gui/slsexport/ui_local.h"
#include "gui/styles.hh"
#include "pr_dbg.hh"

lv_obj_t *lv_obj_create_copy(lv_obj_t *parent, lv_obj_t *copy) {

	if (copy == nullptr)
		return nullptr;

	lv_obj_t *new_obj = lv_obj_class_create_obj(copy->class_p, parent);

	if (new_obj == nullptr)
		return nullptr;

	new_obj->spec_attr->scroll = copy->spec_attr->scroll;
	new_obj->spec_attr->ext_click_pad = copy->spec_attr->ext_click_pad;
	new_obj->spec_attr->ext_draw_size = copy->spec_attr->ext_draw_size;
	new_obj->spec_attr->scrollbar_mode = copy->spec_attr->scrollbar_mode;
	new_obj->spec_attr->scroll_snap_x = copy->spec_attr->scroll_snap_x;
	new_obj->spec_attr->scroll_snap_y = copy->spec_attr->scroll_snap_y;
	new_obj->spec_attr->scroll_dir = copy->spec_attr->scroll_dir;
	new_obj->spec_attr->event_dsc_cnt = copy->spec_attr->event_dsc_cnt;
	new_obj->spec_attr->layer_type = copy->spec_attr->layer_type;

	// _lv_obj_style_t * styles; //array of style_cnt elements
	for (unsigned i = 0; i < copy->style_cnt; i++) {
		lv_style_t *copy_style = copy->styles[i].style;
		uint32_t copy_selector = copy->styles[i].selector;
		// uint32_t copy_is_local = copy->styles[i].is_local;
		// uint32_t copy_is_trans = copy->styles[i].is_trans;
		lv_obj_add_style(new_obj, copy_style, copy_selector);
	}

	new_obj->coords = copy->coords;
	new_obj->flags = copy->flags;
	new_obj->state = copy->state;
	new_obj->layout_inv = copy->layout_inv;
	new_obj->scr_layout_inv = copy->scr_layout_inv;
	new_obj->skip_trans = copy->skip_trans;
	// new_obj->style_cnt = copy->style_cnt;
	new_obj->h_layout = copy->h_layout;
	new_obj->w_layout = copy->w_layout;
	new_obj->being_deleted = copy->being_deleted;

	for (unsigned i = 0; i < copy->spec_attr->child_cnt; i++) {
		lv_obj_create_copy(new_obj, copy->spec_attr->children[i]);
		// lv_obj_class_create_obj(copy->spec_attr->children[i]->class_p, new_obj);
	}

	//Need to set the group manually
	new_obj->spec_attr->group_p = nullptr;

	//Need to set user_data manually
	new_obj->user_data = nullptr;

	//Need to set events manually
	new_obj->spec_attr->event_dsc = nullptr;

	return new_obj;
}

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

		auto button = lv_obj_create_copy(ui_CableToPanel, ui_CableToEditButton1);
		auto label = lv_obj_get_child(button, 0);
		// auto button = ui_CableToEditButton_create(ui_CableToPanel);
		// auto label = ui_comp_get_child(button, UI_COMP_CABLETOEDITBUTTON_CABLETOLABEL);
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
			auto button = lv_obj_create_copy(ui_CableToPanel, ui_CableToEditButton1);
			auto label = lv_obj_get_child(button, 0);
			// auto button = ui_CableToEditButton_create(ui_CableToPanel);
			// auto label = ui_comp_get_child(button, UI_COMP_CABLETOEDITBUTTON_CABLETOLABEL);
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
