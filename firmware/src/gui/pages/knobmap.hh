#pragma once
#include "gui/elements/helpers.hh"
#include "gui/elements/update.hh"
#include "gui/helpers/lv_helpers.hh"
#include "gui/pages/base.hh"
#include "gui/pages/knob_arc.hh"
#include "gui/pages/page_list.hh"
#include "gui/slsexport/meta5/ui.h"
#include "gui/styles.hh"

namespace MetaModule
{
struct KnobMapPage : PageBase {

	constexpr static unsigned min_arc = 160;
	constexpr static unsigned max_arc = 20;

	KnobMapPage(PatchInfo info)
		: PageBase{info}
		, base{ui_EditMappingPage}
		, patch{patch_storage.get_view_patch()} {
		PageList::register_page(this, PageId::KnobMap);
		init_bg(base);
		lv_group_set_editing(group, false);
		lv_obj_add_event_cb(ui_AliasTextArea, edit_text_cb, LV_EVENT_PRESSED, this);
		lv_obj_add_event_cb(ui_Keyboard, keyboard_cb, LV_EVENT_READY, this);
		lv_obj_add_event_cb(ui_Keyboard, keyboard_cb, LV_EVENT_CANCEL, this);
		lv_obj_add_event_cb(ui_MinSlider, slider_cb, LV_EVENT_VALUE_CHANGED, this);
		lv_obj_add_event_cb(ui_MaxSlider, slider_cb, LV_EVENT_VALUE_CHANGED, this);
		lv_hide(ui_Keyboard);
	}

	void prepare_focus() override {
		lv_group_remove_all_objs(group);
		lv_group_set_editing(group, false);

		patch = patch_storage.get_view_patch();

		view_set_idx = PageList::get_viewing_knobset();
		map_idx = PageList::get_selected_mappedknob_id();
		if (view_set_idx >= patch.knob_sets.size())
			return;

		map = patch.knob_sets[view_set_idx].set[map_idx];

		lv_group_add_obj(group, ui_MinSlider);
		lv_group_add_obj(group, ui_MaxSlider);
		lv_group_add_obj(group, ui_AliasTextArea);
		lv_group_add_obj(group, ui_ListButton);
		lv_group_add_obj(group, ui_EditButton);
		lv_group_add_obj(group, ui_TrashButton);
		lv_group_set_editing(group, false);

		if (!map.is_panel_knob())
			return;

		auto fullname = get_full_element_name(map.module_id, map.param_id, ElementType::Param, patch);
		lv_label_set_text(ui_ModuleMapName, fullname.module_name.data());
		lv_label_set_text(ui_KnobMapName, fullname.element_name.data());

		if (map.alias_name.length()) {
			lv_textarea_set_text(ui_AliasTextArea, map.alias_name.data());
		} else {
			char name[64]{};
			snprintf_(name, 64, "%s %s", fullname.module_name.data(), fullname.element_name.data());
			lv_textarea_set_text(ui_AliasTextArea, name);
		}

		auto panel_name = PanelDef::get_map_param_name(map.panel_knob_id);
		lv_label_set_text_fmt(
			ui_MappedName, "Knob %s in '%s'", panel_name.data(), patch.valid_knob_set_name(view_set_idx));

		float val = params.knobs[map.panel_knob_id];
		set_knob_arc<min_arc, max_arc>(map, ui_EditMappingArc, val);

		auto color = Gui::knob_palette[map.panel_knob_id % 6];
		lv_obj_set_style_arc_color(ui_EditMappingArc, color, LV_PART_INDICATOR);
		lv_obj_set_style_bg_color(ui_EditMappingCircle, color, LV_STATE_DEFAULT);
		lv_label_set_text(ui_EditMappingLetter, panel_name.data());

		lv_group_set_editing(group, false);
	}

	void update() override {
		if (metaparams.meta_buttons[0].is_just_released()) {
			if (kb_visible) {
				hide_keyboard();
			} else if (PageList::request_last_page()) {
				blur();
			}
		}

		bool is_patch_playing = PageList::get_selected_patch_location() == patch_playloader.cur_patch_location();
		if (is_patch_playing) {
			// TODO also call set_knob_arc if max/min changed
			if (auto val = ElementUpdate::get_mapped_param_value(params, map.panel_knob_id); val.has_value()) {
				set_knob_arc<min_arc, max_arc>(map, ui_EditMappingArc, val.value());
			}
		}
	}

	void blur() final {
	}

	static void slider_cb(lv_event_t *event) {
		if (!event || !event->user_data)
			return;
		auto page = static_cast<KnobMapPage *>(event->user_data);
		auto obj = event->current_target;
		if (obj != ui_MinSlider && obj != ui_MaxSlider)
			return;

		auto val = lv_slider_get_value(obj);
		(obj == ui_MinSlider ? page->map.min : page->map.max) = val / 100.f;
	}

	static void edit_text_cb(lv_event_t *event) {
		printf_("Pressed\n");
		if (!event || !event->user_data)
			return;
		auto page = static_cast<KnobMapPage *>(event->user_data);

		auto kb_hidden = lv_obj_has_flag(ui_Keyboard, LV_OBJ_FLAG_HIDDEN);
		if (kb_hidden) {
			printf_("showing keyboard\n");
			lv_show(ui_Keyboard);
			page->kb_visible = true;
			lv_group_add_obj(page->group, ui_Keyboard);
			lv_group_focus_obj(ui_Keyboard);
		} else {
			printf_("hiding keyboard\n");
			page->hide_keyboard();
		}
	}

	static void keyboard_cb(lv_event_t *event) {
		if (!event || !event->user_data)
			return;

		auto page = static_cast<KnobMapPage *>(event->user_data);
		if (event->code == LV_EVENT_READY) {
			printf_("Ready\n");
			page->hide_keyboard();
		}
		if (event->code == LV_EVENT_CANCEL) {
			printf_("Cancel\n");
			page->hide_keyboard();
		}
	}

	void hide_keyboard() {
		lv_group_remove_obj(ui_Keyboard);
		lv_hide(ui_Keyboard);
		kb_visible = false;
	}

private:
	lv_obj_t *base = nullptr;
	PatchData &patch;
	MappedKnob &map{null_map};
	MappedKnob null_map;

	bool kb_visible = false;

	unsigned map_idx = 0;
	unsigned view_set_idx = 0;
};

} // namespace MetaModule
