#pragma once
#include "conf/panel_conf.hh"
#include "gui/elements/element_name.hh"
#include "gui/elements/panel_name.hh"
#include "gui/helpers/lv_helpers.hh"
#include "gui/slsexport/meta5/ui.h"
#include "gui/slsexport/ui_local.h"
#include "gui/styles.hh"
#include "lvgl.h"
#include "patch.hh"
#include <string_view>

#include "pr_dbg.hh"

namespace MetaModule
{

//TODO: construct MappingPaneList with ptrs to callbacks?
// Or Add/edit callbacks live here and they only use some other class (not ModuleViewMappingPane)
struct MappingPaneList {

	static lv_obj_t *
	create_map_list_item(MappedKnob const &map, std::string_view knobset_name, lv_obj_t *parent, bool is_active) {
		auto obj = ui_MappedKnobsetitem_create(parent);
		auto setname = ui_comp_get_child(obj, UI_COMP_MAPPEDKNOBSETITEM_KNOBSETNAMETEXT);
		auto circle = ui_comp_get_child(obj, UI_COMP_MAPPEDKNOBSETITEM_CIRCLE);
		auto label = ui_comp_get_child(obj, UI_COMP_MAPPEDKNOBSETITEM_CIRCLE_KNOBLETTER);
		lv_label_set_text(setname, knobset_name.data());
		lv_show(circle);
		lv_obj_set_style_text_color(obj, is_active ? lv_color_hex(0xFF8918) : lv_color_white(), LV_STATE_DEFAULT);

		auto name = get_panel_name<PanelDef>(ParamElement{}, map.panel_knob_id);
		lv_label_set_text(label, name.c_str());

		if (map.is_panel_knob())
			format_knob_map_circle(map.panel_knob_id, circle, label);

		else if (map.is_midi_cc())
			format_cc_map_circle(map.cc_num(), circle, label);

		else
			pr_err("Unknown mapping panel_knob_id: %d\n", map.panel_knob_id);

		return obj;
	}

	static lv_obj_t *create_unmapped_list_item(std::string_view knobset_name, lv_obj_t *parent, bool is_active) {
		auto obj = ui_UnmappedSetItem_create(parent);
		auto setname = ui_comp_get_child(obj, UI_COMP_UNMAPPEDSETITEM_KNOBSETNAMETEXT);
		lv_label_set_text(setname, knobset_name.data());
		lv_obj_set_style_text_color(obj, is_active ? lv_color_hex(0xFF8918) : lv_color_white(), LV_STATE_DEFAULT);
		return obj;
	}

	static lv_obj_t *create_panel_incable_item(uint16_t panel_jack_id, lv_obj_t *parent) {
		auto obj = ui_MappedKnobsetitem_create(parent);
		style_panel_incable_item(panel_jack_id, obj);
		return obj;
	}

	static lv_obj_t *create_panel_outcable_item(uint16_t panel_jack_id, lv_obj_t *parent) {
		auto obj = ui_MappedKnobsetitem_create(parent);
		style_panel_outcable_item(panel_jack_id, obj);
		return obj;
	}

	static lv_obj_t *create_cable_item(Jack jack, ElementType dir, PatchData const &patch, lv_obj_t *parent) {
		auto obj = ui_UnmappedSetItem_create(parent);
		style_unmappedcable_item(jack, dir, patch, obj);
		return obj;
	}

	static void style_panel_incable_item(uint16_t panel_jack_id, lv_obj_t *obj) {
		auto circle = ui_comp_get_child(obj, UI_COMP_MAPPEDKNOBSETITEM_CIRCLE);
		auto label = ui_comp_get_child(obj, UI_COMP_MAPPEDKNOBSETITEM_CIRCLE_KNOBLETTER);
		auto setname = ui_comp_get_child(obj, UI_COMP_MAPPEDKNOBSETITEM_KNOBSETNAMETEXT);
		lv_obj_set_flex_flow(obj, LV_FLEX_FLOW_ROW_WRAP_REVERSE);
		lv_obj_set_style_pad_right(obj, 4, LV_STATE_DEFAULT);
		lv_show(circle);

		auto name = get_panel_name<PanelDef>(JackInput{}, panel_jack_id);

		if (panel_jack_id < PanelDef::NumUserFacingInJacks) {
			lv_obj_set_style_border_color(circle, Gui::knob_palette[panel_jack_id], LV_STATE_DEFAULT);
			lv_label_set_text_fmt(setname, "Panel %.16s", name.c_str());
			if (panel_jack_id < 6)
				lv_label_set_text_fmt(label, "%d", panel_jack_id + 1);
			else
				lv_label_set_text_fmt(label, "G%d", panel_jack_id - 5);
			lv_obj_set_style_text_font(label, &ui_font_MuseoSansRounded70016, LV_STATE_DEFAULT);

		} else {
			lv_obj_set_style_border_color(circle, Gui::palette_main[LV_PALETTE_GREY], LV_STATE_DEFAULT);
			lv_label_set_text(setname, name.c_str());
			lv_label_set_text(label, "");
		}

		format_panel_cable_circle(circle);
	}

	static void style_panel_outcable_item(uint16_t panel_jack_id, lv_obj_t *obj) {
		auto circle = ui_comp_get_child(obj, UI_COMP_MAPPEDKNOBSETITEM_CIRCLE);
		auto label = ui_comp_get_child(obj, UI_COMP_MAPPEDKNOBSETITEM_CIRCLE_KNOBLETTER);
		auto setname = ui_comp_get_child(obj, UI_COMP_MAPPEDKNOBSETITEM_KNOBSETNAMETEXT);
		lv_obj_set_flex_flow(obj, LV_FLEX_FLOW_ROW_WRAP_REVERSE);
		lv_obj_set_style_pad_right(obj, 4, LV_STATE_DEFAULT);
		lv_show(circle);

		auto name = get_panel_name<PanelDef>(JackOutput{}, panel_jack_id);

		if (panel_jack_id < Gui::knob_palette.size())
			lv_obj_set_style_border_color(circle, Gui::knob_palette[panel_jack_id], LV_STATE_DEFAULT);

		lv_label_set_text_fmt(setname, "Panel %.16s", name.c_str());
		lv_label_set_text_fmt(label, "%d", panel_jack_id + 1);
		lv_obj_set_style_text_font(label, &ui_font_MuseoSansRounded70016, LV_STATE_DEFAULT);

		format_panel_cable_circle(circle);
	}

	static void style_mappedcable_item(Jack jack, ElementType dir, PatchData const &patch, lv_obj_t *obj) {
		auto label = ui_comp_get_child(obj, UI_COMP_MAPPEDKNOBSETITEM_KNOBSETNAMETEXT);
		auto circle = ui_comp_get_child(obj, UI_COMP_MAPPEDKNOBSETITEM_CIRCLE);
		lv_hide(circle);
		lv_obj_set_style_pad_left(label, 9, LV_STATE_DEFAULT);
		lv_obj_set_style_text_color(label, lv_color_white(), LV_STATE_DEFAULT);
		auto name = get_full_element_name(jack.module_id, jack.jack_id, dir, patch);
		lv_label_set_text_fmt(label, "%.16s %.16s", name.module_name.data(), name.element_name.data());
	}

	static void style_unmappedcable_item(Jack jack, ElementType dir, PatchData const &patch, lv_obj_t *obj) {
		auto label = ui_comp_get_child(obj, UI_COMP_UNMAPPEDSETITEM_KNOBSETNAMETEXT);
		lv_obj_set_style_pad_left(label, 9, LV_STATE_DEFAULT);
		lv_obj_set_style_text_color(label, lv_color_white(), LV_STATE_DEFAULT);
		auto name = get_full_element_name(jack.module_id, jack.jack_id, dir, patch);
		lv_label_set_text_fmt(label, "%.16s %.16s", name.module_name.data(), name.element_name.data());
	}

private:
	static void format_panel_cable_circle(lv_obj_t *circle) {
		lv_obj_set_style_border_width(circle, 3, LV_STATE_DEFAULT);
		lv_obj_set_style_bg_color(circle, lv_color_hex(0xbbbbbb), LV_STATE_DEFAULT);
		lv_obj_set_style_bg_opa(circle, LV_OPA_100, LV_STATE_DEFAULT);
	}

	static void format_knob_map_circle(uint16_t panel_knob_id, lv_obj_t *circle, lv_obj_t *label) {
		//workaround for lowercase letter positions off-center
		if (panel_knob_id >= 6)
			lv_obj_set_style_pad_bottom(label, 3, LV_STATE_DEFAULT);
		format_label(label, 0, &ui_font_MuseoSansRounded90018);
		format_circle(circle, Gui::knob_palette[panel_knob_id % 6], 22);
	}

	static void format_cc_map_circle(uint16_t cc_num, lv_obj_t *circle, lv_obj_t *label) {
		//Workaround to make two lines
		std::string name{lv_label_get_text(label)};
		if (name.size() > 2 && name[0] == 'C' && name[1] == 'C') {
			name.insert(2, "\n");
			lv_label_set_text(label, name.c_str());
		}
		format_label(label, -2, &ui_font_MuseoSansRounded50012);
		format_circle(circle, Gui::palette_main[LV_PALETTE_GREY], 2);
	}

	static void format_circle(lv_obj_t *circle, lv_color_t bg_color, lv_coord_t bg_radius) {
		lv_obj_set_style_bg_color(circle, bg_color, LV_STATE_DEFAULT);
		lv_obj_set_style_radius(circle, bg_radius, LV_STATE_DEFAULT);
	}

	static void format_label(lv_obj_t *label, lv_coord_t line_spacing, const lv_font_t *font) {
		lv_obj_set_style_text_font(label, font, LV_STATE_DEFAULT);
		lv_obj_set_style_text_line_space(label, line_spacing, LV_STATE_DEFAULT);
	}
};
} // namespace MetaModule
