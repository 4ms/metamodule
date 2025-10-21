#pragma once
#include "CoreModules/elements/elements_index.hh"
#include "gui/elements/element_name.hh"
#include "gui/elements/panel_name.hh"
#include "gui/helpers/lv_helpers.hh"
#include "gui/pages/base.hh"
#include "gui/pages/confirm_popup.hh"
#include "gui/pages/keyboard_entry.hh"
#include "gui/pages/knob_arc.hh"
#include "gui/pages/page_list.hh"
#include "gui/slsexport/meta5/ui.h"
#include "gui/slsexport/ui_local.h"
#include "gui/styles.hh"

namespace MetaModule
{
struct KnobMapPage : PageBase {

	constexpr static unsigned min_arc = 160;
	constexpr static unsigned max_arc = 20;

	KnobMapPage(PatchContext info)
		: PageBase{info, PageId::KnobMap}
		, base{ui_EditMappingPage}
		, patch{patches.get_view_patch()} {

		init_bg(base);
		lv_group_set_editing(group, false);
		lv_obj_add_event_cb(ui_AliasTextArea, edit_text_cb, LV_EVENT_CLICKED, this);
		lv_obj_add_event_cb(ui_MinSlider, slider_cb, LV_EVENT_VALUE_CHANGED, this);
		lv_obj_add_event_cb(ui_MaxSlider, slider_cb, LV_EVENT_VALUE_CHANGED, this);
		lv_obj_add_event_cb(ui_ModuleMapToggleSwitch, slider_cb, LV_EVENT_VALUE_CHANGED, this);

		lv_obj_add_event_cb(ui_ListButton, list_cb, LV_EVENT_RELEASED, this);
		lv_obj_add_event_cb(ui_EditButton, edit_cb, LV_EVENT_RELEASED, this);
		lv_obj_add_event_cb(ui_KnobSetButton, knobset_cb, LV_EVENT_RELEASED, this);
		lv_obj_add_event_cb(ui_TrashButton, trash_cb, LV_EVENT_RELEASED, this);

		ui_EditMapMidiChannelDropdown = create_midi_map_dropdown(
			ui_EditMapMidiChannelCont,
			"All Chan.\nChannel 1\nChannel 2\nChannel 3\nChannel 4\nChannel 5\nChannel 6\nChannel 7\nChannel "
			"8\nChannel 9\nChannel 10\nChannel 11\nChannel 12\nChannel 13\nChannel 14\nChannel 15\nChannel 16");

		lv_obj_set_height(ui_EditMapMidiChannelDropdown, 28);
		lv_obj_set_width(ui_EditMapMidiChannelDropdown, 110);

		lv_obj_add_event_cb(ui_EditMapMidiChannelDropdown, midichan_cb, LV_EVENT_VALUE_CHANGED, this);

		lv_hide(ui_Keyboard);
		lv_hide(ui_EditMapMidiChannelCont);

		del_popup.init(base, group);

		lv_group_remove_all_objs(group);
		lv_group_add_obj(group, ui_MinSlider);
		lv_group_add_obj(group, ui_MaxSlider);
		lv_group_add_obj(group, ui_ModuleMapToggleSwitch);
		lv_group_add_obj(group, ui_AliasTextArea);
		lv_group_add_obj(group, ui_EditMapMidiChannelDropdown);
		lv_group_add_obj(group, ui_ListButton);
		lv_group_add_obj(group, ui_EditButton);
		lv_group_add_obj(group, ui_KnobSetButton);
		lv_group_add_obj(group, ui_TrashButton);
		lv_hide(ui_EditButton);
		lv_group_set_editing(group, false);

		indicator = lv_btn_create(ui_EditMapKnob); //NOLINT
		lv_obj_set_width(indicator, 3);
		lv_obj_set_height(indicator, 10);
		lv_obj_set_x(indicator, 0);
		lv_obj_set_y(indicator, 31);
		lv_obj_set_align(indicator, LV_ALIGN_TOP_MID);
		lv_obj_set_style_bg_color(indicator, lv_color_hex(0x0), LV_PART_MAIN);
		lv_obj_set_style_radius(indicator, 0, LV_PART_MAIN);
		lv_obj_set_style_transform_pivot_x(indicator, 0, LV_PART_MAIN);
		lv_obj_set_style_transform_pivot_y(indicator, 23, LV_PART_MAIN);

		lv_group_set_wrap(group, false);
	}

	void prepare_focus() override {
		keyboard_entry.prepare_focus(ui_EditMappingPage, group);
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
			lv_show(ui_EditMapMidiChannelCont);
		} else {
			lv_show(ui_KnobSetButton);
			lv_hide(ui_EditMapMidiChannelCont);
		}

		auto param_id = args.mappedknob_id;
		auto module_id = args.module_id;
		if (!param_id.has_value() || !module_id.has_value()) {
			pr_err("KnobMapPage: No mapped module/param in page args (set %d)\n", view_set_idx);
			return;
		}
		if (auto it = std::ranges::find_if(knobset,
										   [mid = *module_id, pid = *param_id](MappedKnob const &m) {
											   return (m.module_id == mid && m.param_id == pid);
										   });
			it != knobset.end())
		{
			map = *it;
		} else {
			pr_err("KnobMapPage: Panel knob %u not found in knob set %d\n", param_id.value(), view_set_idx);
			return;
		}

		// Title
		auto fullname = get_full_element_name(map.module_id, map.param_id, ElementType::Param, *patch);
		lv_label_set_text(ui_ModuleMapName, fullname.module_name.data());
		lv_label_set_text(ui_KnobMapName, fullname.element_name.data());

		update_alias_text_area();

		auto panel_name = get_panel_name(ParamElement{}, map.panel_knob_id);
		lv_label_set_text_fmt(
			ui_MappedName, "Knob %s in '%s'", panel_name.c_str(), patch->valid_knob_set_name(view_set_idx));

		// Min/Max sliders
		int intmin = std::round(map.min * 100.f);
		int intmax = std::round(map.max * 100.f);
		lv_label_set_text_fmt(ui_MinValue, "%d%%", intmin);
		lv_label_set_text_fmt(ui_MaxValue, "%d%%", intmax);
		lv_slider_set_value(ui_MinSlider, intmin, LV_ANIM_OFF);
		lv_slider_set_value(ui_MaxSlider, intmax, LV_ANIM_OFF);

		if (map.is_midi_notegate() || map.is_button()) {
			lv_show(ui_ModuleMapToggleSwitchCont);
			lv_check(ui_ModuleMapToggleSwitch, map.curve_type == MappedKnob::CurveType::Toggle);
			lv_label_set_text(ui_ModuleMapToggleSwitchLabel, "Button Behavior: Toggle");

		} else {
			lv_hide(ui_ModuleMapToggleSwitchCont);
			lv_check(ui_ModuleMapToggleSwitch, false);
		}
		lv_dropdown_set_selected(ui_EditMapMidiChannelDropdown, map.midi_chan);

		// Knob arc

		float knob_val = static_param ? map.unmap_val(static_param->value) : 0;
		set_knob_arc<min_arc, max_arc>(map, ui_EditMappingArc, knob_val);

		lv_obj_set_style_opa(ui_EditMappingArc, is_actively_playing ? LV_OPA_100 : LV_OPA_50, LV_PART_KNOB);

		auto color = Gui::get_knob_color(map.panel_knob_id);

		lv_obj_set_style_arc_color(ui_EditMappingArc, color, LV_PART_INDICATOR);
		lv_obj_set_style_bg_color(ui_EditMappingCircle, color, LV_STATE_DEFAULT);
		lv_label_set_text(ui_EditMappingLetter, panel_name.c_str());

		if (map.is_midi() || map.is_button() || panel_name.size() > 3)
			lv_obj_set_style_text_font(ui_EditMappingLetter, &ui_font_MuseoSansRounded90018, LV_PART_MAIN);
		else
			lv_obj_set_style_text_font(ui_EditMappingLetter, &ui_font_MuseoSansRounded90040, LV_PART_MAIN);

		if (map.is_button())
			lv_obj_set_style_text_color(ui_EditMappingLetter, lv_color_white(), LV_PART_MAIN);
		else
			lv_obj_set_style_text_color(ui_EditMappingLetter, lv_color_black(), LV_PART_MAIN);

		lv_obj_set_style_bg_color(indicator, Gui::get_knob_indicator_color(map.panel_knob_id), LV_STATE_DEFAULT);
		lv_obj_set_style_bg_opa(indicator, LV_OPA_100, LV_STATE_DEFAULT);

		update_active_status();

		lv_group_set_editing(group, false);
	}

	void update() override {
		if (gui_state.back_button.is_just_released()) {

			if (keyboard_entry.is_visible()) {
				keyboard_entry.back();

			} else if (del_popup.is_visible()) {
				del_popup.hide();

			} else if (lv_dropdown_is_open(ui_EditMapMidiChannelDropdown)) {
				lv_dropdown_close(ui_EditMapMidiChannelDropdown);
				lv_group_set_editing(group, false);

			} else {
				page_list.request_last_page();
			}
		}

		update_active_status();

		if (is_actively_playing) {
			auto is_tracking = map.is_midi() || patch_playloader.is_param_tracking(map.module_id, map.param_id);

			if (is_tracking) {
				lv_hide(indicator);
				lv_obj_set_style_bg_color(ui_EditMappingArc, lv_color_hex(0xFFFFFF), LV_PART_KNOB);
			} else {
				lv_show(indicator);
				lv_obj_set_style_bg_color(ui_EditMappingArc, lv_color_hex(0xAAAAAA), LV_PART_KNOB);

				if (map.panel_knob_id < params.knobs.size()) {
					auto phys_val = params.knobs[map.panel_knob_id].val;
					auto mapped_phys_val = map.get_mapped_val(phys_val);
					lv_obj_set_style_transform_angle(indicator, mapped_phys_val * 2500.f - 1250.f, LV_PART_MAIN);
				}
			}

			auto value = patch_playloader.param_value(map.module_id, map.param_id);
			auto arc_val = map.unmap_val(value);
			set_knob_arc<min_arc, max_arc>(map, ui_EditMappingArc, arc_val);
		}

		poll_patch_file_changed();

		if (gui_state.view_patch_file_changed) {
			gui_state.view_patch_file_changed = false;
			prepare_focus();
		}
	}

	void update_active_status() {
		is_patch_playing = patch_is_playing(args.patch_loc_hash);

		auto is_active_knobset = map.is_midi() || args.view_knobset_id.value_or(999) == page_list.get_active_knobset();
		if (is_patch_playing && is_active_knobset) {
			if (!is_actively_playing) {
				lv_obj_set_style_opa(ui_EditMappingArc, LV_OPA_100, LV_PART_KNOB);
			}
			is_actively_playing = true;
		} else {
			if (is_actively_playing) {
				lv_obj_set_style_opa(ui_EditMappingArc, LV_OPA_50, LV_PART_KNOB);
			}
			is_actively_playing = false;
		}
	}

	void blur() final {
	}

private:
	static void slider_cb(lv_event_t *event) {
		if (!event || !event->user_data)
			return;

		auto page = static_cast<KnobMapPage *>(event->user_data);
		if (!page)
			return;

		auto obj = event->current_target;
		if (obj != ui_MinSlider && obj != ui_MaxSlider && obj != ui_ModuleMapToggleSwitch) {
			return;
		}

		if (obj == ui_MinSlider) {
			auto val = lv_slider_get_value(obj);
			page->map.min = val / 100.f;
			lv_label_set_text_fmt(ui_MinValue, "%d%%", (int)val);

		} else if (obj == ui_MaxSlider) {
			auto val = lv_slider_get_value(obj);
			page->map.max = val / 100.f;
			lv_label_set_text_fmt(ui_MaxValue, "%d%%", (int)val);

		} else {
			auto checked = lv_obj_has_state(ui_ModuleMapToggleSwitch, LV_STATE_CHECKED);
			page->map.curve_type = checked ? MappedKnob::CurveType::Toggle : MappedKnob::CurveType::Normal;
		}

		set_knob_arc<min_arc, max_arc>(page->map, ui_EditMappingArc, {});
		page->patch_mod_queue.put(ModifyMapping{.map = page->map, .set_id = page->view_set_idx});
		page->patch->add_update_mapped_knob(page->view_set_idx, page->map);
		page->patches.mark_view_patch_modified();
	}

	static void edit_text_cb(lv_event_t *event) {
		if (!event || !event->user_data)
			return;
		auto page = static_cast<KnobMapPage *>(event->user_data);

		if (!lv_obj_has_flag(ui_Keyboard, LV_OBJ_FLAG_HIDDEN))
			return;

		page->show_keyboard();
	}

	void show_keyboard() {
		keyboard_entry.show_keyboard(ui_AliasTextArea, [this](std::string_view text) {
			map.alias_name = lv_textarea_get_text(ui_AliasTextArea);
			patch->add_update_mapped_knob(view_set_idx, map);
			patches.mark_view_patch_modified();
		});
		kb_visible = true;
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
		page->args.element_indices = ElementIndex::set_index(ParamElement{}, page->map.param_id);
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

	static void midichan_cb(lv_event_t *event) {
		if (!event || !event->user_data)
			return;
		auto page = static_cast<KnobMapPage *>(event->user_data);
		if (!page)
			return;

		page->map.midi_chan = lv_dropdown_get_selected(ui_EditMapMidiChannelDropdown);
		page->patch_mod_queue.put(ModifyMapping{.map = page->map, .set_id = PatchData::MIDIKnobSet});
		page->patch->add_update_midi_map(page->map);
		page->patches.mark_view_patch_modified();
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
	lv_obj_t *indicator = nullptr;
	PatchData *patch;
	MappedKnob map{};
	const StaticParam *static_param = nullptr;

	ConfirmPopup del_popup;

	bool kb_visible = false;

	uint32_t view_set_idx = 0;

	bool is_actively_playing = false;
	bool is_patch_playing = false;

	KeyboardEntry keyboard_entry;
};

} // namespace MetaModule
