#pragma once
#include "conf/panel_conf.hh"
#include "gui/elements/element_name.hh"
#include "gui/elements/panel_name.hh"
#include "gui/helpers/lv_helpers.hh"
#include "gui/slsexport/meta5/ui.h"
#include "gui/slsexport/ui_local.h"
#include "gui/styles.hh"
#include "lvgl.h"
#include "patch/patch.hh"
#include <string_view>

#include "pr_dbg.hh"

namespace MetaModule
{

//TODO: construct MappingPaneList with ptrs to callbacks?
// Or Add/edit callbacks live here and they only use some other class (not ModuleViewMappingPane)
struct MappingPaneList {

	static lv_obj_t *
	create_param_map_list_item(MappedKnob const &map, std::string_view knobset_name, lv_obj_t *parent, bool is_active) {
		auto obj = ui_MappedKnobsetitem_create(parent, false);

		if (lv_obj_get_child_cnt(obj) < 2) {
			pr_err("create_param_map_list_item(): object is corrupted\n");
			return nullptr;
		}
		auto circle = lv_obj_get_child(obj, 0);
		if (lv_obj_get_child_cnt(circle) == 0) {
			pr_err("create_param_map_list_item(): object circle is corrupted\n");
			return nullptr;
		}
		auto label = lv_obj_get_child(circle, 0);
		auto setname = lv_obj_get_child(obj, 1);

		if (lv_obj_has_class(setname, &lv_label_class))
			lv_label_set_text(setname, knobset_name.data());
		lv_show(circle);
		lv_obj_set_style_text_color(obj, is_active ? lv_color_hex(0xFF8918) : lv_color_white(), LV_STATE_DEFAULT);

		auto name = get_panel_name(ParamElement{}, map.panel_knob_id);
		lv_label_set_text(label, name.c_str());

		if (map.is_panel_knob())
			format_knob_map_circle(map.panel_knob_id, circle, label);

		else if (map.is_button())
			format_button_map_circle(map.panel_knob_id, circle, label);

		else if (map.is_midi_cc())
			format_mapping_circle(circle, MapButtonType::MIDIParam, map.panel_knob_id);

		else if (map.is_midi_notegate())
			format_mapping_circle(circle, MapButtonType::MIDIParam, map.panel_knob_id);

		else
			pr_err("Unknown mapping panel_knob_id: %d\n", map.panel_knob_id);

		return obj;
	}

	static lv_obj_t *create_unmapped_list_item(std::string_view knobset_name, lv_obj_t *parent, bool is_active) {
		auto obj = ui_UnmappedSetItem_create(parent);
		lv_obj_set_style_pad_left(obj, 32, LV_PART_MAIN | LV_STATE_DEFAULT);

		if (lv_obj_get_child_cnt(obj) == 0)
			return nullptr;
		auto setname = lv_obj_get_child(obj, 0);

		lv_label_set_text(setname, knobset_name.data());
		lv_obj_set_style_text_color(obj, is_active ? lv_color_hex(0xFF8918) : lv_color_white(), LV_STATE_DEFAULT);
		return obj;
	}

	static lv_obj_t *create_panel_in_item(uint16_t panel_jack_id, lv_obj_t *parent, std::string_view alias_name) {
		if (Midi::is_midi_panel_id(panel_jack_id)) {
			auto obj = create_mapping_circle_item(parent, MapButtonType::MIDIJack, panel_jack_id, alias_name.data());
			if (!alias_name.length()) {
				auto name = get_panel_name(JackInput{}, panel_jack_id);
				lv_label_set_text_fmt(lv_obj_get_child(obj, 1), "%s", name.c_str());
			}
			lv_obj_set_style_pad_hor(obj, 1, LV_PART_MAIN);
			lv_obj_set_style_pad_ver(obj, 1, LV_PART_MAIN);
			lv_obj_set_width(obj, lv_pct(100));
			return obj;

		} else {
			// TODO: create item with textarea/label
			auto obj = ui_MappedKnobsetitem_create(parent, true);
			style_panel_incable_item(panel_jack_id, obj, alias_name);
			return obj;
		}
	}

	static lv_obj_t *create_panel_out_item(uint16_t panel_jack_id, lv_obj_t *parent, std::string_view name) {
		// TODO: create item with textarea/label
		auto obj = ui_MappedKnobsetitem_create(parent, true);
		style_panel_outcable_item(panel_jack_id, obj, name);
		return obj;
	}

	static lv_obj_t *create_cable_item(Jack jack, ElementType dir, PatchData const &patch, lv_obj_t *parent) {
		auto obj = ui_UnmappedSetItem_create(parent);
		style_unmappedcable_item(jack, dir, patch, obj);
		return obj;
	}

	static void style_panel_incable_item(uint16_t panel_jack_id, lv_obj_t *obj, std::string_view alias_name) {
		if (lv_obj_get_child_cnt(obj) < 2) {
			pr_err("style_panel_outcable_item(): object is corrupted\n");
			return;
		}
		auto circle = lv_obj_get_child(obj, 0);
		if (lv_obj_get_child_cnt(circle) == 0) {
			pr_err("style_panel_outcable_item(): object circle is corrupted\n");
			return;
		}
		auto label = lv_obj_get_child(circle, 0);
		auto setname = lv_obj_get_child(obj, 1);

		lv_show(circle);

		lv_obj_set_style_border_color(circle, Gui::get_jack_color(panel_jack_id), LV_STATE_DEFAULT);

		std::string text =
			alias_name.length() ? std::string(alias_name) : "Panel " + get_panel_name(JackInput{}, panel_jack_id);

		if (lv_obj_has_class(setname, &lv_textarea_class))
			lv_textarea_set_text(setname, text.c_str());
		else
			lv_label_set_text(setname, text.c_str());

		lv_label_set_text(label, get_panel_brief_name(JackInput{}, panel_jack_id).c_str());

		lv_obj_set_style_text_font(label, &ui_font_MuseoSansRounded70016, LV_STATE_DEFAULT);

		format_panel_cable_circle(circle);
	}

	static void style_panel_outcable_item(uint16_t panel_jack_id, lv_obj_t *obj, std::string_view alias_name) {
		if (lv_obj_get_child_cnt(obj) < 2) {
			pr_err("style_panel_outcable_item(): object is corrupted\n");
			return;
		}
		auto circle = lv_obj_get_child(obj, 0);
		if (lv_obj_get_child_cnt(circle) == 0) {
			pr_err("style_panel_outcable_item(): object circle is corrupted\n");
			return;
		}
		auto label = lv_obj_get_child(circle, 0);
		auto setname = lv_obj_get_child(obj, 1);

		lv_show(circle);

		lv_obj_set_style_border_color(circle, Gui::get_jack_color(panel_jack_id), LV_STATE_DEFAULT);

		std::string text =
			alias_name.length() ? std::string(alias_name) : "Panel " + get_panel_name(JackOutput{}, panel_jack_id);

		if (lv_obj_has_class(setname, &lv_textarea_class))
			lv_textarea_set_text(setname, text.c_str());
		else
			lv_label_set_text(setname, text.c_str());

		lv_label_set_text_fmt(label, "%d", panel_jack_id + 1);
		lv_obj_set_style_text_font(label, &ui_font_MuseoSansRounded70016, LV_STATE_DEFAULT);

		format_panel_cable_circle(circle);
	}

	static void style_unmappedcable_item(Jack jack, ElementType dir, PatchData const &patch, lv_obj_t *obj) {
		if (lv_obj_get_child_cnt(obj) == 0)
			return;
		auto label = lv_obj_get_child(obj, 0);
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
		if (panel_knob_id >= 6 && panel_knob_id < 12)
			lv_obj_set_style_pad_bottom(label, 3, LV_STATE_DEFAULT);

		format_label(label, 0, &ui_font_MuseoSansRounded90018);
		format_circle(circle, Gui::get_knob_color(panel_knob_id), 22);
	}

	static void format_button_map_circle(uint16_t panel_knob_id, lv_obj_t *circle, lv_obj_t *label) {
		format_label(label, 0, &ui_font_MuseoSansRounded70014);
		lv_obj_set_style_text_color(label, lv_color_white(), LV_STATE_DEFAULT);
		format_circle(circle, Gui::get_knob_color(panel_knob_id), 22);
	}

	static void format_circle(lv_obj_t *circle, lv_color_t bg_color, lv_coord_t bg_radius) {
		lv_obj_set_style_bg_color(circle, bg_color, LV_STATE_DEFAULT);
		lv_obj_set_style_radius(circle, bg_radius, LV_STATE_DEFAULT);
	}

	static void format_label(lv_obj_t *label, lv_coord_t line_spacing, const lv_font_t *font) {
		lv_obj_set_style_text_font(label, font, LV_STATE_DEFAULT);
		lv_obj_set_style_text_line_space(label, line_spacing, LV_STATE_DEFAULT);
		lv_obj_set_style_text_color(label, lv_color_black(), LV_STATE_DEFAULT);
	}
};
} // namespace MetaModule
