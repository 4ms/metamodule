#pragma once
#include "gui/elements/element_name.hh"
#include "gui/elements/panel_name.hh"
#include "gui/helpers/lv_helpers.hh"
#include "gui/pages/add_map_popup.hh"
#include "gui/pages/base.hh"
#include "gui/pages/confirm_popup.hh"
#include "gui/pages/knob_arc.hh"
#include "gui/pages/page_list.hh"
#include "gui/slsexport/meta5/ui.h"
#include "gui/styles.hh"

namespace MetaModule
{
struct KnobMapPage : PageBase {

	constexpr static unsigned min_arc = 160;
	constexpr static unsigned max_arc = 20;

	KnobMapPage(PatchContext info)
		: PageBase{info, PageId::KnobMap}
		, base{ui_EditMappingPage}
		, patch{patches.get_view_patch()} // , add_map_popup{patch_mod_queue}
	{

		init_bg(base);
		lv_group_set_editing(group, false);
		lv_obj_add_event_cb(ui_AliasTextArea, edit_text_cb, LV_EVENT_PRESSED, this);
		lv_obj_add_event_cb(ui_AliasTextArea, edit_text_cb, LV_EVENT_RELEASED, this);
		lv_obj_add_event_cb(ui_MinSlider, slider_cb, LV_EVENT_VALUE_CHANGED, this);
		lv_obj_add_event_cb(ui_MaxSlider, slider_cb, LV_EVENT_VALUE_CHANGED, this);

		lv_obj_add_event_cb(ui_ListButton, list_cb, LV_EVENT_RELEASED, this);
		lv_obj_add_event_cb(ui_EditButton, edit_cb, LV_EVENT_RELEASED, this);
		lv_obj_add_event_cb(ui_KnobSetButton, knobset_cb, LV_EVENT_RELEASED, this);
		lv_obj_add_event_cb(ui_TrashButton, trash_cb, LV_EVENT_RELEASED, this);

		lv_hide(ui_Keyboard);

		del_popup.init(base, group);

		lv_group_remove_all_objs(group);
		lv_group_add_obj(group, ui_MinSlider);
		lv_group_add_obj(group, ui_MaxSlider);
		lv_group_add_obj(group, ui_AliasTextArea);
		lv_group_add_obj(group, ui_ListButton);
		lv_group_add_obj(group, ui_EditButton);
		lv_group_add_obj(group, ui_KnobSetButton);
		lv_group_add_obj(group, ui_TrashButton);
		lv_hide(ui_EditButton);
		lv_group_set_editing(group, false);
	}

	void prepare_focus() override {
		// remove all callbacks
		while (lv_obj_remove_event_cb(ui_Keyboard, nullptr))
			;
		lv_obj_add_event_cb(ui_Keyboard, lv_keyboard_def_event_cb, LV_EVENT_VALUE_CHANGED, nullptr);
		lv_obj_add_event_cb(ui_Keyboard, keyboard_cb, LV_EVENT_READY, this);
		lv_obj_add_event_cb(ui_Keyboard, keyboard_cb, LV_EVENT_CANCEL, this);

		lv_obj_set_parent(ui_Keyboard, ui_EditMappingPage);
		lv_obj_set_y(ui_Keyboard, 1);

		patch = patches.get_view_patch();

		view_set_idx = args.view_knobset_id.value_or(view_set_idx);
		if (view_set_idx != PatchData::MIDIKnobSet && view_set_idx >= patch->knob_sets.size()) {
			return;
		}

		auto &knobset =
			(view_set_idx == PatchData::MIDIKnobSet) ? patch->midi_maps.set : patch->knob_sets[view_set_idx].set;

		if (view_set_idx == PatchData::MIDIKnobSet) {
			lv_hide(ui_KnobSetButton);
		} else {
			lv_show(ui_KnobSetButton);
		}

		//mappedknob_id is the index of the MappedKnob in the MappedKnobSet::set vector
		auto map_idx = args.mappedknob_id;
		if (!map_idx.has_value() || map_idx.value() >= knobset.size()) {
			pr_err("Mapping not found for set %d, panel_knob_id %d\n", view_set_idx, map_idx);
			return;
		}
		map = knobset[map_idx.value()];

		// Title
		auto fullname = get_full_element_name(map.module_id, map.param_id, ElementType::Param, *patch);
		lv_label_set_text(ui_ModuleMapName, fullname.module_name.data());
		lv_label_set_text(ui_KnobMapName, fullname.element_name.data());

		update_alias_text_area();

		auto panel_name = get_panel_name<PanelDef>(ParamElement{}, map.panel_knob_id);
		lv_label_set_text_fmt(
			ui_MappedName, "Knob %s in '%s'", panel_name.c_str(), patch->valid_knob_set_name(view_set_idx));

		// Min/Max sliders
		lv_label_set_text_fmt(ui_MinValue, "%d%%", unsigned(map.min * 100));
		lv_label_set_text_fmt(ui_MaxValue, "%d%%", unsigned(map.max * 100));
		lv_slider_set_value(ui_MinSlider, map.min * 100.f, LV_ANIM_OFF);
		lv_slider_set_value(ui_MaxSlider, map.max * 100.f, LV_ANIM_OFF);

		// Knob arc

		static_param = patch->find_static_knob(map.module_id, map.param_id);
		float knob_val = static_param ? map.unmap_val(static_param->value) : 0;
		set_knob_arc<min_arc, max_arc>(map, ui_EditMappingArc, knob_val);
		lv_obj_set_style_opa(ui_EditMappingArc, is_actively_playing ? LV_OPA_100 : LV_OPA_50, LV_PART_KNOB);

		auto color = Gui::knob_palette[map.panel_knob_id % 6];
		lv_obj_set_style_arc_color(ui_EditMappingArc, color, LV_PART_INDICATOR);
		lv_obj_set_style_bg_color(ui_EditMappingCircle, color, LV_STATE_DEFAULT);
		lv_label_set_text(ui_EditMappingLetter, panel_name.c_str());
		if (panel_name.size() > 3)
			lv_obj_set_style_text_font(ui_EditMappingLetter, &ui_font_MuseoSansRounded90018, LV_PART_MAIN);
		else
			lv_obj_set_style_text_font(ui_EditMappingLetter, &ui_font_MuseoSansRounded90040, LV_PART_MAIN);

		update_active_status();

		lv_group_set_editing(group, false);

		// add_map_popup.prepare_focus(group, ui_EditMappingPage);
		// add_map_popup.hide();
	}

	void update() override {
		if (gui_state.back_button.is_just_released()) {
			if (kb_visible) {
				del_popup.show([this](bool ok) { save_knob_alias(ok); }, "Do you want to save your edits?", "Save");
			} else if (del_popup.is_visible()) {
				del_popup.hide();
			} else {
				page_list.request_last_page();
			}
		}

		update_active_status();

		if (is_actively_playing && static_param) {
			float s_val = map.unmap_val(static_param->value);
			set_knob_arc<min_arc, max_arc>(map, ui_EditMappingArc, s_val);
		}

		// add_map_popup.update(params);
	}

	void update_active_status() {
		is_patch_playing = patch_is_playing(args.patch_loc_hash);

		if (is_patch_playing && args.view_knobset_id.value_or(999) == page_list.get_active_knobset()) {
			if (!is_actively_playing)
				lv_obj_set_style_opa(ui_EditMappingArc, LV_OPA_100, LV_PART_KNOB);
			is_actively_playing = true;
		} else {
			if (is_actively_playing)
				lv_obj_set_style_opa(ui_EditMappingArc, LV_OPA_50, LV_PART_KNOB);
			is_actively_playing = false;
		}
	}

	void blur() final {
	}

	static void slider_cb(lv_event_t *event) {
		if (!event || !event->user_data)
			return;

		auto page = static_cast<KnobMapPage *>(event->user_data);
		if (!page)
			return;

		auto obj = event->current_target;
		if (obj != ui_MinSlider && obj != ui_MaxSlider)
			return;

		auto val = lv_slider_get_value(obj);
		if (obj == ui_MinSlider) {
			page->map.min = val / 100.f;
			lv_label_set_text_fmt(ui_MinValue, "%d%%", (int)val);
		} else {
			page->map.max = val / 100.f;
			lv_label_set_text_fmt(ui_MaxValue, "%d%%", (int)val);
		}

		set_knob_arc<min_arc, max_arc>(page->map, ui_EditMappingArc, {});
		page->patch_mod_queue.put(
			EditMappingMinMax{.map = page->map, .set_id = page->view_set_idx, .cur_val = val / 100.f});
		page->patch->add_update_mapped_knob(page->view_set_idx, page->map);
		page->patches.mark_view_patch_modified();
	}

	static void edit_text_cb(lv_event_t *event) {
		if (!event || !event->user_data)
			return;
		auto page = static_cast<KnobMapPage *>(event->user_data);

		auto kb_hidden = lv_obj_has_flag(ui_Keyboard, LV_OBJ_FLAG_HIDDEN);
		if (kb_hidden) {
			lv_show(ui_Keyboard);
			lv_keyboard_set_textarea(ui_Keyboard, ui_AliasTextArea);
			page->kb_visible = true;
			lv_obj_add_state(ui_AliasTextArea, LV_STATE_USER_1);
			lv_group_add_obj(page->group, ui_Keyboard);
			lv_group_focus_obj(ui_Keyboard);
		}
	}

	static void keyboard_cb(lv_event_t *event) {
		if (!event || !event->user_data)
			return;

		auto page = static_cast<KnobMapPage *>(event->user_data);
		if (event->code == LV_EVENT_READY || event->code == LV_EVENT_CANCEL) {
			page->save_knob_alias(event->code == LV_EVENT_READY || event->code == LV_EVENT_CANCEL);
		}
	}

	static void edit_cb(lv_event_t *event) {
		if (!event || !event->user_data)
			return;
		auto page = static_cast<KnobMapPage *>(event->user_data);
		if (!page)
			return;

		// TODO: header says "Change Map", not "Add a map"
		// page->add_map_popup.show(page->view_set_idx, page->map.param_id, page->map.module_id);
		page->notify_queue.put({"Not implemented yet :("});
	}

	static void knobset_cb(lv_event_t *event) {
		if (!event || !event->user_data)
			return;
		auto page = static_cast<KnobMapPage *>(event->user_data);
		if (!page)
			return;

		// Note: we keep args.mappedknob_id the same as it was when this page was loaded
		page->args.view_knobset_id = page->view_set_idx;
		page->page_list.request_new_page(PageId::KnobSetView, page->args);
	}

	static void list_cb(lv_event_t *event) {
		if (!event || !event->user_data)
			return;
		auto page = static_cast<KnobMapPage *>(event->user_data);
		if (!page)
			return;

		page->args.module_id = page->map.module_id;
		page->args.element_indices =
			ElementCount::mark_unused_indices({.param_idx = (uint8_t)page->map.param_id}, {.num_params = 1});
		page->args.detail_mode = true;
		page->page_list.request_new_page(PageId::ModuleView, page->args);
	}

	static void trash_cb(lv_event_t *event) {
		if (!event || !event->user_data)
			return;
		auto page = static_cast<KnobMapPage *>(event->user_data);
		if (!page)
			return;

		page->del_popup.show(
			[page](bool ok) {
				if (!ok)
					return;

				page->patch_mod_queue.put(RemoveMapping{.map = page->map, .set_id = page->view_set_idx});
				page->patches.mark_view_patch_modified();

				if (!page->patch->remove_mapping(page->view_set_idx, page->map))
					pr_err("Could not delete mapping\n");
				else
					page->page_list.request_last_page();
			},
			"Are you sure you want to delete this mapping?",
			"Trash");
	}

	void save_knob_alias(bool save) {
		lv_obj_clear_state(ui_AliasTextArea, LV_STATE_USER_1);
		lv_group_focus_obj(ui_AliasTextArea);
		lv_group_remove_obj(ui_Keyboard);
		lv_hide(ui_Keyboard);
		kb_visible = false;

		if (save) {
			map.alias_name = lv_textarea_get_text(ui_AliasTextArea);
			patch->add_update_mapped_knob(view_set_idx, map);
		}

		update_alias_text_area();
	}

	void update_alias_text_area() {
		const auto fullname = get_full_element_name(map.module_id, map.param_id, ElementType::Param, *patch);
		if (map.alias_name.length()) {
			lv_textarea_set_text(ui_AliasTextArea, map.alias_name.data());
		} else {
			char name[64]{};
			snprintf(name, 64, "%s %s", fullname.module_name.data(), fullname.element_name.data());
			lv_textarea_set_text(ui_AliasTextArea, "");
			lv_textarea_set_placeholder_text(ui_AliasTextArea, name);
		}
	}

private:
	lv_obj_t *base = nullptr;
	PatchData *patch;
	MappedKnob map{};
	const StaticParam *static_param = nullptr;

	ConfirmPopup del_popup;

	// AddMapPopUp add_map_popup;

	bool kb_visible = false;

	uint32_t view_set_idx = 0;

	bool is_actively_playing = false;
	bool is_patch_playing = false;
};

} // namespace MetaModule
