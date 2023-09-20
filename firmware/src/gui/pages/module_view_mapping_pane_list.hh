#pragma once
#include "gui/elements/helpers.hh"
#include "gui/helpers/lv_helpers.hh"
#include "gui/slsexport/meta5/ui.h"
#include "gui/styles.hh"
#include "lvgl.h"
#include "patch.hh"
#include <string_view>

namespace MetaModule
{

//TODO: construct MappingPaneList with ptrs to callbacks?
// Or Add/edit callbacks live here and they only use some other clasS (not ModuleViewMappingPane)
struct MappingPaneList {

	lv_obj_t *create_map_list_item(std::string_view name, std::string_view knobset_name, unsigned color_id) {
		auto obj = ui_MappedKnobSetItem_create(ui_MapList);
		auto circle = ui_comp_get_child(obj, UI_COMP_MAPPEDKNOBSETITEM_CIRCLE);
		auto label = ui_comp_get_child(obj, UI_COMP_MAPPEDKNOBSETITEM_CIRCLE_KNOBLETTER);
		auto setname = ui_comp_get_child(obj, UI_COMP_MAPPEDKNOBSETITEM_KNOBSETNAMETEXT);
		lv_obj_set_style_bg_color(circle, Gui::knob_palette[color_id], LV_STATE_DEFAULT);
		lv_label_set_text(label, name.data());
		lv_label_set_text(setname, knobset_name.data());
		return obj;
	}

	lv_obj_t *create_unmapped_list_item(std::string_view knobset_name) {
		auto obj = ui_UnmappedSetItem_create(ui_MapList);
		auto setname = ui_comp_get_child(obj, UI_COMP_UNMAPPEDSETITEM_KNOBSETNAMETEXT);
		lv_label_set_text(setname, knobset_name.data());
		return obj;
	}

	lv_obj_t *create_panelcable_item(std::string_view panel_jack_name, unsigned color_id) {
		auto obj = ui_MappedKnobSetItem_create(ui_MapList);
		auto circle = ui_comp_get_child(obj, UI_COMP_MAPPEDKNOBSETITEM_CIRCLE);
		auto label = ui_comp_get_child(obj, UI_COMP_MAPPEDKNOBSETITEM_CIRCLE_KNOBLETTER);
		auto setname = ui_comp_get_child(obj, UI_COMP_MAPPEDKNOBSETITEM_KNOBSETNAMETEXT);
		lv_obj_set_flex_flow(obj, LV_FLEX_FLOW_ROW_WRAP_REVERSE);
		lv_obj_set_style_bg_color(circle, Gui::knob_palette[color_id], LV_STATE_DEFAULT);
		lv_label_set_text(label, "");
		lv_label_set_text_fmt(setname, "Panel %.16s", panel_jack_name.data());
		return obj;
	}

	lv_obj_t *create_cable_item(Jack jack, JackDir dir, PatchData const &patch) {
		auto obj = ui_UnmappedSetItem_create(ui_MapList);
		auto label = ui_comp_get_child(obj, UI_COMP_UNMAPPEDSETITEM_KNOBSETNAMETEXT);
		lv_obj_set_style_pad_left(label, 0, LV_STATE_DEFAULT);
		lv_obj_set_style_text_color(label, lv_color_white(), LV_STATE_DEFAULT);
		auto name = get_full_jack_name(jack, dir, patch);
		lv_label_set_text_fmt(
			label, "%s %.16s %.16s", dir == JackDir::In ? "->" : "<-", name.module_name.data(), name.jack_name.data());

		return obj;
	}
};
} // namespace MetaModule
