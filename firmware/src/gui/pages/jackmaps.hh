#pragma once
#include "gui/elements/element_name.hh"
#include "gui/pages/base.hh"
#include "gui/pages/module_view/mapping_pane.hh"
#include "gui/pages/page_list.hh"
#include "gui/slsexport/meta5/ui.h"

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

		unsigned num_inputs = PanelDef::NumUserFacingInJacks;
		unsigned num_outputs = PanelDef::NumUserFacingOutJacks;
		if (Expanders::get_connected().ext_audio_connected) {
			num_inputs += AudioExpander::NumInJacks;
			num_outputs += AudioExpander::NumOutJacks;
		}

		for (unsigned i = 0; i < num_inputs; i++) {
			in_conts[i] = create_jack_map_item(ui_JackMapLeftColumn, JackMapType::Input, i, "");
			lv_group_add_obj(group, in_conts[i]);
		}

		for (unsigned i = 0; i < num_outputs; i++) {
			out_conts[i] = create_jack_map_item(ui_JackMapRightColumn, JackMapType::Output, i, "");
			lv_group_add_obj(group, out_conts[i]);
		}
	}

	void onJackMapClick(unsigned idx, JackMapType type) {
		pr_trace("%s Jack: %d\n", type == JackMapType::Input ? "Input" : "Output", idx);

		if (type == JackMapType::Input) {
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

	template<JackMapType type>
	static void onJackMapClick(lv_event_t *event) {
		if (const auto page = static_cast<JackMapViewPage *>(event->user_data); page) {
			const auto idx = (uintptr_t)lv_obj_get_user_data(event->target);
			page->onJackMapClick(idx, type);
		}
	}

	void prepare_focus() override {
		redraw();
		lv_group_activate(group);

		lv_obj_scroll_to_y(ui_JackMapLeftColumn, 0, LV_ANIM_OFF);
		lv_obj_scroll_to_y(ui_JackMapRightColumn, 0, LV_ANIM_OFF);
	}

	void redraw() {
		patch = patches.get_view_patch();

		// Clear old text
		for (unsigned i = 0; i < PanelDef::NumUserFacingInJacks; i++) {
			if (lv_obj_get_child_cnt(in_conts[i]) > 1)
				lv_label_set_text(lv_obj_get_child(in_conts[i], 1), "");
			lv_obj_remove_event_cb(in_conts[i], NULL);
		}
		for (unsigned i = 0; i < PanelDef::NumUserFacingOutJacks; i++) {
			if (lv_obj_get_child_cnt(out_conts[i]) > 1)
				lv_label_set_text(lv_obj_get_child(out_conts[i], 1), "");
			lv_obj_remove_event_cb(out_conts[i], NULL);
		}

		//Populate new text
		for (auto [i, map] : enumerate(patch->mapped_ins)) {
			for (auto &jack : map.ins) {
				if (map.panel_jack_id < in_conts.size()) {
					if (lv_obj_get_child_cnt(in_conts[map.panel_jack_id]) > 1) {
						lv_obj_set_user_data(in_conts[map.panel_jack_id], (void *)((uintptr_t)i));
						lv_obj_add_event_cb(
							in_conts[map.panel_jack_id], onJackMapClick<JackMapType::Input>, LV_EVENT_CLICKED, this);
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
			if (map.panel_jack_id < out_conts.size()) {
				if (lv_obj_get_child_cnt(in_conts[map.panel_jack_id]) > 1) {
					lv_obj_set_user_data(out_conts[map.panel_jack_id], (void *)((uintptr_t)i));
					lv_obj_add_event_cb(
						out_conts[map.panel_jack_id], onJackMapClick<JackMapType::Output>, LV_EVENT_CLICKED, this);
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
