#pragma once
#include "CoreModules/elements/element_info.hh"
#include "gui/elements/element_name.hh"
#include "gui/elements/map_ring_animate.hh"
#include "gui/elements/module_drawer.hh"
#include "gui/pages/base.hh"
#include "gui/pages/knob_arc.hh"
#include "gui/pages/module_view_mapping_pane.hh"
#include "gui/pages/page_list.hh"
#include "gui/slsexport/meta5/ui.h"
#include "gui/styles.hh"
#include "src/core/lv_obj_tree.h"

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

	void prepare_focus() override {
		patch = patches.get_view_patch();

		// Clear old text
		for (unsigned i = 0; i < PanelDef::NumUserFacingInJacks; i++) {
			if (lv_obj_get_child_cnt(in_conts[i]) > 1)
				lv_label_set_text(lv_obj_get_child(in_conts[i], 1), "");
		}
		for (unsigned i = 0; i < PanelDef::NumUserFacingOutJacks; i++) {
			if (lv_obj_get_child_cnt(out_conts[i]) > 1)
				lv_label_set_text(lv_obj_get_child(out_conts[i], 1), "");
		}

		//Populate new text
		for (auto map : patch->mapped_ins) {
			for (auto &jack : map.ins) {
				if (map.panel_jack_id < in_conts.size()) {
					if (lv_obj_get_child_cnt(in_conts[map.panel_jack_id]) > 1) {
						auto name = get_full_element_name(jack.module_id, jack.jack_id, ElementType::Input, *patch);
						auto label = lv_obj_get_child(in_conts[map.panel_jack_id], 1);
						lv_label_set_text_fmt(label, "%s %s", name.module_name.data(), name.element_name.data());
					}
				}
			}
		}

		for (auto map : patch->mapped_outs) {
			if (map.panel_jack_id < out_conts.size()) {
				if (lv_obj_get_child_cnt(in_conts[map.panel_jack_id]) > 1) {
					auto name = get_full_element_name(map.out.module_id, map.out.jack_id, ElementType::Output, *patch);
					auto label = lv_obj_get_child(out_conts[map.panel_jack_id], 1);
					lv_label_set_text_fmt(label, "%s %s", name.module_name.data(), name.element_name.data());
				}
			}
		}

		lv_group_activate(group);
	}

	void update() override {
		if (gui_state.back_button.is_just_released()) {
			if (page_list.request_last_page()) {
				blur();
			}
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
