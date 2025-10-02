#pragma once
#include "gui/elements/element_name.hh"
#include "gui/pages/base.hh"
#include "gui/pages/page_list.hh"
#include "gui/slsexport/meta5/ui.h"
#include "gui/slsexport/ui_local.h"
#include "params/expanders.hh"

namespace MetaModule
{
struct JackMapViewPage : PageBase {

	constexpr static unsigned min_arc = 160;
	constexpr static unsigned max_arc = 20;

	JackMapViewPage(PatchContext info)
		: PageBase{info, PageId::JackMapView}
		, base{ui_JackMapViewPage}
		, patch{patches.get_view_patch()}
		, group{lv_group_create()} {

		init_bg(base);
		lv_group_set_editing(group, false);

		//TODO:Back button
		// lv_obj_add_event_cb(ui_PreviousKnobSet, prev_knobset_cb, LV_EVENT_CLICKED, this);
	}

	void onJackMapClick(unsigned idx, MapButtonType type) {
		pr_trace("%s Jack: %d\n", type == MapButtonType::Input ? "Input" : "Output", idx);

		if (type == MapButtonType::Input) {
			const auto &i = patch->mapped_ins[idx];
			if (!i.ins.size()) {
				return;
			}
			args.module_id = i.ins[0].module_id;
			args.element_indices = ElementCount::mark_unused_indices(
				{.input_idx = static_cast<uint8_t>(i.ins[0].jack_id)}, {.num_inputs = 1});
		} else {
			const auto &o = patch->mapped_outs[idx];
			args.module_id = o.out.module_id;
			args.element_indices = ElementCount::mark_unused_indices(
				{.output_idx = static_cast<uint8_t>(o.out.jack_id)}, {.num_outputs = 1});
		}

		args.detail_mode = true;
		page_list.request_new_page(PageId::ModuleView, args);
	}

	template<MapButtonType type>
	static void onJackMapClick(lv_event_t *event) {
		if (const auto page = static_cast<JackMapViewPage *>(event->user_data); page) {
			const auto idx = (uintptr_t)lv_obj_get_user_data(event->target);
			page->onJackMapClick(idx, type);
		}
	}

	void prepare_focus() override {
		init_jack_items();

		redraw();
		lv_group_activate(group);

		lv_obj_scroll_to_y(ui_JackMapLeftItems, 0, LV_ANIM_OFF);
		lv_obj_scroll_to_y(ui_JackMapRightItems, 0, LV_ANIM_OFF);
	}

	void redraw() {
		patch = patches.get_view_patch();

		lv_group_remove_all_objs(group);

		// Clear old text
		for (auto *in_cont : in_conts) {
			if (!in_cont)
				continue;
			if (lv_obj_get_child_cnt(in_cont) > 1)
				lv_label_set_text(lv_obj_get_child(in_cont, 1), "");
			lv_obj_remove_event_cb(in_cont, NULL);
		}
		for (auto *out_cont : out_conts) {
			if (!out_cont)
				continue;
			if (lv_obj_get_child_cnt(out_cont) > 1)
				lv_label_set_text(lv_obj_get_child(out_cont, 1), "");
			lv_obj_remove_event_cb(out_cont, NULL);
		}

		//Populate new text
		for (auto [i, map] : enumerate(patch->mapped_ins)) {
			for (auto &jack : map.ins) {
				if (map.panel_jack_id < in_conts.size() && in_conts[map.panel_jack_id]) {
					if (lv_obj_get_child_cnt(in_conts[map.panel_jack_id]) > 1) {
						lv_obj_set_user_data(in_conts[map.panel_jack_id], (void *)((uintptr_t)i));
						lv_obj_add_event_cb(
							in_conts[map.panel_jack_id], onJackMapClick<MapButtonType::Input>, LV_EVENT_CLICKED, this);
						auto label = lv_obj_get_child(in_conts[map.panel_jack_id], 1);
						if (!map.alias_name.size()) {
							auto name = get_full_element_name(jack.module_id, jack.jack_id, ElementType::Input, *patch);
							lv_label_set_text_fmt(label, "%s %s", name.module_name.data(), name.element_name.data());
						} else {
							lv_label_set_text_fmt(label, "%s", map.alias_name.data());
						}
					}
				}
			}
		}

		for (auto [i, map] : enumerate(patch->mapped_outs)) {
			if (map.panel_jack_id < out_conts.size() && out_conts[map.panel_jack_id]) {
				if (lv_obj_get_child_cnt(out_conts[map.panel_jack_id]) > 1) {
					lv_obj_set_user_data(out_conts[map.panel_jack_id], (void *)((uintptr_t)i));
					lv_obj_add_event_cb(
						out_conts[map.panel_jack_id], onJackMapClick<MapButtonType::Output>, LV_EVENT_CLICKED, this);
					auto label = lv_obj_get_child(out_conts[map.panel_jack_id], 1);
					if (!map.alias_name.size()) {
						auto name =
							get_full_element_name(map.out.module_id, map.out.jack_id, ElementType::Output, *patch);
						lv_label_set_text_fmt(label, "%s %s", name.module_name.data(), name.element_name.data());
					} else {
						lv_label_set_text_fmt(label, "%s", map.alias_name.data());
					}
				}
			}
		}

		// Add all populated items to group
		for (auto *cont : in_conts) {
			if (cont && lv_obj_get_child_cnt(cont) > 1) {
				if (lv_label_get_text(lv_obj_get_child(cont, 1))[0] != '\0')
					lv_group_add_obj(group, cont);
			}
		}
		for (auto *cont : out_conts) {
			if (cont && lv_obj_get_child_cnt(cont) > 1) {
				if (lv_label_get_text(lv_obj_get_child(cont, 1))[0] != '\0')
					lv_group_add_obj(group, cont);
			}
		}
	}

	void init_jack_items() {
		// Calculate number of inputs and outputs to display
		unsigned num_inputs = PanelDef::NumUserFacingInJacks;
		unsigned num_outputs = PanelDef::NumUserFacingOutJacks;

		// Show all expander jacks if an expander is connected
		if (Expanders::get_connected().ext_audio_connected) {
			num_inputs += AudioExpander::NumInJacks;
			num_outputs += AudioExpander::NumOutJacks;
		}

		for (unsigned i = 0; i < num_inputs; i++) {
			if (in_conts[i] == nullptr)
				in_conts[i] = create_mapping_circle_item(ui_JackMapLeftItems, MapButtonType::Input, i, "");
		}

		for (unsigned i = 0; i < num_outputs; i++) {
			if (out_conts[i] == nullptr)
				out_conts[i] = create_mapping_circle_item(ui_JackMapRightItems, MapButtonType::Output, i, "");
		}
	}

	void update() override {
		if (gui_state.back_button.is_just_released()) {
			if (page_list.request_last_page()) {
				blur();
			}
		}

		poll_patch_file_changed();
		if (gui_state.view_patch_file_changed) {
			gui_state.view_patch_file_changed = false;
			redraw();
		}
	}

private:
	lv_obj_t *base = nullptr;
	PatchData *patch;
	std::array<lv_obj_t *, PanelDef::NumUserFacingInJacks + AudioExpander::NumInJacks> in_conts{};
	std::array<lv_obj_t *, PanelDef::NumUserFacingOutJacks + AudioExpander::NumOutJacks> out_conts{};
	lv_group_t *group;
};

} // namespace MetaModule
