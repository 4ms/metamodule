#pragma once
#include "gui/elements/context.hh"
#include "gui/elements/element_name.hh"
#include "gui/helpers/lv_helpers.hh"
#include "gui/pages/base.hh"
#include "gui/pages/page_list.hh"
#include "gui/slsexport/meta5/ui.h"
#include "gui/styles.hh"
#include "lvgl.h"

namespace MetaModule
{

struct AddMapPopUp {

	AddMapPopUp(PatchModQueue &patch_mod_queue)
		: patch_mod_queue{patch_mod_queue}
		, popup_group(lv_group_create()) {

		lv_group_add_obj(popup_group, ui_CancelAdd);
		lv_group_add_obj(popup_group, ui_OkAdd);
		lv_obj_add_event_cb(ui_CancelAdd, button_cb, LV_EVENT_CLICKED, this);
		lv_obj_add_event_cb(ui_OkAdd, button_cb, LV_EVENT_CLICKED, this);
	}

	void prepare_focus(lv_group_t *group, lv_obj_t *base) {
		base_group = group;
		lv_obj_set_parent(ui_AddMapPopUp, base);
	}

	void show(uint32_t knobset_id, uint16_t param_id, uint16_t module_id, PatchData *patchdata) {
		selected_knob = std::nullopt;
		patch = patchdata;

		lv_show(ui_AddMapPopUp);
		lv_obj_scroll_to_y(ui_AddMapPopUp, 0, LV_ANIM_OFF);

		if (knobset_id == PatchData::MIDIKnobSet) {
			lv_label_set_text(ui_AddMappingTitle, "Add a map: Send MIDI CC");
		} else
			lv_label_set_text(ui_AddMappingTitle, "Add a map: Wiggle a knob");
		lv_label_set_text(ui_MapDetected, "");
		lv_label_set_text(ui_MapExistsLabel, "");

		param_idx = param_id;
		module_idx = module_id;

		set_id = knobset_id;
		visible = true;

		lv_group_activate(popup_group);
		lv_group_focus_obj(ui_OkAdd);
		lv_group_set_editing(popup_group, false);
		lv_group_set_wrap(popup_group, false);
	}

	void hide() {
		visible = false;
		lv_obj_clear_state(ui_CancelAdd, LV_STATE_PRESSED);
		lv_obj_clear_state(ui_OkAdd, LV_STATE_PRESSED);

		lv_hide(ui_AddMapPopUp);

		if (base_group) {
			lv_group_activate(base_group);
			lv_group_set_editing(base_group, false);
		}
	}

	void update(ParamsMidiState &params) {
		if (visible) {
			auto last_selected_knob = selected_knob;

			if (set_id == PatchData::MIDIKnobSet) {
				for (unsigned ccnum = 0; auto &cc : params.midi_ccs) {
					if (cc.did_change()) {
						lv_label_set_text_fmt(ui_MapDetected, "MIDI CC: %d", ccnum);
						selected_knob = MidiCC0 + ccnum;
					}
					ccnum++;
				}
			} else {
				for (unsigned i = 0; auto &knob : params.knobs) {
					if (knob.did_change()) {
						selected_knob = i;
						std::string_view name = PanelDef::get_map_param_name(i);

						lv_label_set_text_fmt(ui_MapDetected, "Knob: %.4s", name.data());
					}
					i++;
				}
			}

			// Print "Already Mapped To..."
			if (patch && last_selected_knob != selected_knob && selected_knob.has_value()) {
				if (auto existingmap = patch->find_mapped_knob(set_id, selected_knob.value())) {
					auto full_name = get_full_element_name(
						existingmap->module_id, existingmap->param_id, ElementType::Param, *patch);

					std::string combined =
						(module_idx == existingmap->module_id) ?
							std::string(full_name.element_name) :
							std::string(full_name.module_name) + "\n" + std::string(full_name.element_name);

					lv_label_set_text_fmt(ui_MapExistsLabel, "Already Mapped To:\n%s", combined.c_str());
				} else
					lv_label_set_text(ui_MapExistsLabel, "");
			}
		}
	}

	static void button_cb(lv_event_t *event) {
		if (!event || !lv_event_get_user_data(event))
			return;
		auto page = static_cast<AddMapPopUp *>(lv_event_get_user_data(event));

		if (lv_event_get_target(event) == ui_OkAdd) {

			if (page->selected_knob.has_value()) {
				auto map = MappedKnob{
					.panel_knob_id = page->selected_knob.value(),
					.module_id = page->module_idx,
					.param_id = page->param_idx,
					.min = 0.f,
					.max = 1.f,
				};
				if (map.is_panel_knob()) {
					// TODO: just have AddMapping type (not AddMidiMap) and use set_id to indicate MidiMap?
					page->patch_mod_queue.put(AddMapping{.map = map, .set_id = page->set_id});

				} else if (map.is_midi_cc()) {
					page->patch_mod_queue.put(AddMidiMap{.map = map});
				}
			}
			page->hide();

		} else if (lv_event_get_target(event) == ui_CancelAdd) {
			page->hide();
		}
	}

	PatchModQueue &patch_mod_queue;
	lv_group_t *base_group = nullptr;
	lv_group_t *popup_group = nullptr;
	PatchData *patch = nullptr;

	uint16_t module_idx = 0;
	uint16_t param_idx = 0;
	uint32_t set_id = 0;
	bool visible = false;
	std::optional<uint16_t> selected_knob{};
};

} // namespace MetaModule
