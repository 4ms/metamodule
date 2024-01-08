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
		// display = Display::AddCable;
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
			initial_jack = {module_id, indices.input_idx};
			find_connections_to_input_jack();
		} else if (counts.num_outputs > 0) {
			initial_jack = {module_id, indices.output_idx};
			find_connections_to_output_jack();
		} else {
			initial_jack = {};
			pr_err("Error: no jack specified\n");
			return;
		}

		// if (display == Display::AddCable) {
		// 	show_add_cable();
		// } else {
		show_edit_cable();
		// }
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

private:
	PatchData &patch;

	std::vector<lv_obj_t *> in_jack_objs;
	Jack out_jack{};
	// std::array<Jack, 8> in_jacks;

	// The jack that brought us to this page:
	Jack initial_jack{};
	uint16_t module_id = 0;
	ElementCount::Counts counts{};
	ElementCount::Indices indices{};

	// enum class Display { AddCable, EditCable } display{Display::AddCable};

	void find_connections_to_input_jack() {
		Jack in_jack = {.module_id = module_id, .jack_id = indices.input_idx};

		// Look for connected internal cables
		auto *cable = patch.find_internal_cable_with_injack(in_jack);
		if (cable) {
			MappingPaneList::style_mappedcable_item(cable->out, ElementType::Output, patch, ui_CableFromEditButton);
			add_connected_inputs(cable);
			// display = Display::EditCable;
		}

		// Look for mapped panel jacks
		auto mapped_cable = patch.find_mapped_injack(in_jack);
		if (mapped_cable) {
			MappingPaneList::style_panel_incable_item(mapped_cable->panel_jack_id, ui_CableFromEditButton);
			InternalCable cable{.out = {}, .ins = mapped_cable->ins};
			add_connected_inputs(&cable);
			// display = Display::EditCable;
		}
	}

	void find_connections_to_output_jack() {
		out_jack = {.module_id = module_id, .jack_id = indices.output_idx};

		auto cable = patch.find_internal_cable_with_outjack(out_jack);
		if (cable) {
			add_connected_inputs(cable);
			// display = Display::EditCable;
		}

		auto mapped_out = patch.find_mapped_outjack(out_jack);
		if (mapped_out) {
			add_panel_output(mapped_out);
			// display = Display::EditCable;
		}

		MappingPaneList::style_mappedcable_item(out_jack, ElementType::Output, patch, ui_CableFromEditButton);
	}

	void add_connected_inputs(InternalCable const *int_cable) {
		for (auto in : int_cable->ins) {
			add_input_jack(in);
		}
	}

	lv_obj_t *add_input_jack(Jack const &in) {
		auto obj = MappingPaneList::create_cable_item(in, ElementType::Input, patch, ui_CableToPanel);
		// auto label = ui_comp_get_child(obj, UI_COMP_UNMAPPEDSETITEM_KNOBSETNAMETEXT);
		// lv_obj_set_style_pad_left(label, 0, LV_STATE_DEFAULT);
		lv_obj_add_flag(obj, LV_OBJ_FLAG_FLEX_IN_NEW_TRACK);
		lv_group_add_obj(group, obj);
		in_jack_objs.push_back(obj);
		return obj;
	}

	// void show_add_cable() {
	// 	if (counts.num_inputs > 0) {
	// 		auto obj = add_input_jack({module_id, indices.input_idx});
	// 		lv_group_remove_obj(obj);
	// 		lv_label_set_text(ui_CableFromTitle,
	// 						  "To add a cable, click OK and navigate to the connecting module and jack.");
	// 		lv_label_set_text(ui_CableToTitle, "Input jack:");
	// 		lv_hide(ui_CableFromEditButton);
	// 		lv_show(ui_CableToPanel);
	// 	} else {
	// 		lv_label_set_text(ui_CableFromTitle, "Output jack:");
	// 		lv_label_set_text(ui_CableToTitle,
	// 						  "To add a cable, click OK and navigate to the connecting module and jack.");
	// 		lv_show(ui_CableFromEditButton);
	// 		lv_hide(ui_CableToPanel);
	// 		lv_group_remove_obj(ui_CableFromEditButton);
	// 	}

	// 	lv_label_set_text(ui_CableMapPageTitle, "Add Cable");
	// 	lv_label_set_text(ui_CableCancelLabel, "Cancel");
	// 	lv_label_set_text(ui_CableDeleteIcon, "OK");
	// 	lv_obj_set_style_text_font(ui_CableDeleteIcon, &lv_font_montserrat_14, LV_PART_MAIN);

	// 	remove_all_event_cb(ui_CableDeleteButton);
	// 	lv_obj_add_event_cb(ui_CableDeleteButton, start_new_cable, LV_EVENT_CLICKED, this);
	// 	lv_group_add_obj(group, ui_CableDeleteButton);

	// 	lv_group_add_obj(group, ui_CableCancel);
	// }

	void show_edit_cable() {
		lv_show(ui_CableFromEditButton);
		lv_show(ui_CableToPanel);
		lv_label_set_text(ui_CableMapPageTitle, "Edit Cable");
		lv_label_set_text(ui_CableToTitle, "To:");
		lv_label_set_text(ui_CableFromTitle, "From:");
		lv_label_set_text(ui_CableCancelLabel, "Back");
		lv_label_set_text(ui_CableDeleteIcon, "");
		lv_obj_set_style_text_font(ui_CableDeleteIcon, &lv_font_montserrat_20, LV_PART_MAIN);

		remove_all_event_cb(ui_CableDeleteButton);
		lv_obj_add_event_cb(ui_CableDeleteButton, delete_cable, LV_EVENT_CLICKED, this);
		lv_group_add_obj(group, ui_CableDeleteButton);

		lv_group_add_obj(group, ui_CableCancel);
	}

	static void delete_cable(lv_event_t *event) {
		auto page = static_cast<CableEditPage *>(event->user_data);
		if (!page)
			return;
	}

	// static void start_new_cable(lv_event_t *event) {
	// 	auto page = static_cast<CableEditPage *>(event->user_data);
	// 	if (!page)
	// 		return;

	// 	auto &jack = page->initial_jack;
	// 	auto dir = page->counts.num_inputs > 0 ? ElementType::Input : ElementType::Output;
	// 	auto name = get_full_element_name(jack.module_id, jack.jack_id, dir, page->patch);
	// 	page->gui_state.new_cable_begin_jack = jack;
	// 	page->gui_state.new_cable_begin_type = dir;
	// 	page->notify_queue.put(
	// 		{"Choose a jack to connect to " + std::string(name.module_name) + " " + std::string(name.element_name),
	// 		 Notification::Priority::Status,
	// 		 10000});

	// 	page->page_list.request_new_page(PageId::PatchView, page->args);
	// }
};

} // namespace MetaModule
