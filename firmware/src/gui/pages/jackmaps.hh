#pragma once
#include "gui/elements/element_name.hh"
#include "gui/pages/base.hh"
#include "gui/pages/helpers.hh"
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

	// Clicking a jack-mapping row jumps to that jack's module in the Module View.
	static void follow_jack_cb(lv_event_t *event) {
		auto page = static_cast<JackMapViewPage *>(event->user_data);
		if (!page || !event->target)
			return;

		auto userdata = lv_obj_get_user_data(event->target);
		if (!userdata)
			return;

		auto endpoint = CableEndpointUserData{userdata};
		page->args.module_id = endpoint.module_id;
		page->args.element_indices = endpoint.idx;
		page->args.detail_mode = true;
		page->page_list.request_new_page(PageId::ModuleView, page->args);
	}

	void prepare_focus() override {
		redraw();
		lv_group_activate(group);

		lv_obj_scroll_to_y(ui_JackMapLeftItems, 0, LV_ANIM_OFF);
		lv_obj_scroll_to_y(ui_JackMapRightItems, 0, LV_ANIM_OFF);
	}

	void redraw() {
		patch = patches.get_view_patch();

		lv_obj_clean(ui_JackMapLeftItems);
		lv_obj_clean(ui_JackMapRightItems);
		lv_group_remove_all_objs(group);

		// Number of panel jacks to display (plus expander jacks if connected)
		unsigned num_inputs = PanelDef::NumUserFacingInJacks;
		unsigned num_outputs = PanelDef::NumUserFacingOutJacks;
		if (Expanders::get_connected().ext_audio_connected) {
			num_inputs += AudioExpander::NumInJacks;
			num_outputs += AudioExpander::NumOutJacks;
		}

		// Inputs (left column). A panel input jack may be summed from several
		// module input jacks: show one selectable row per jack, with the
		// circle+number only on the first row and the following rows' text
		// aligned beneath it.
		for (unsigned pj = 0; pj < num_inputs; pj++) {
			auto *mapped = patch->find_mapped_injack((uint16_t)pj);
			if (!mapped || mapped->ins.empty()) {
				create_mapping_circle_item(ui_JackMapLeftItems, MapButtonType::Input, pj, "");
				continue;
			}

			// If the panel jack has an alias, show it as a header carrying the
			// circle+number; the jack rows then align beneath the alias text.
			bool has_alias = mapped->alias_name.size() > 0;
			if (has_alias)
				add_alias_header(ui_JackMapLeftItems, MapButtonType::Input, pj, mapped->alias_name.data());

			for (auto [k, jack] : enumerate(mapped->ins)) {
				auto name = get_full_element_name(jack.module_id, jack.jack_id, ElementType::Input, *patch);
				add_jack_row(
					ui_JackMapLeftItems,
					MapButtonType::Input,
					pj,
					!has_alias && k == 0,
					name,
					(uint16_t)jack.module_id,
					ElementCount::mark_unused_indices({.input_idx = (uint8_t)jack.jack_id}, {.num_inputs = 1}));
			}
		}

		// Outputs (right column). A panel output jack may be driven from several
		// module output jacks (across map entries sharing a panel_jack_id).
		for (unsigned pj = 0; pj < num_outputs; pj++) {
			// Entries sharing a panel_jack_id carry the same alias; find it and
			// whether anything is mapped to this panel jack.
			const char *alias = nullptr;
			bool any = false;
			for (auto &map : patch->mapped_outs) {
				if (map.panel_jack_id != pj)
					continue;
				any = true;
				if (map.alias_name.size())
					alias = map.alias_name.data();
			}

			if (!any) {
				create_mapping_circle_item(ui_JackMapRightItems, MapButtonType::Output, pj, "");
				continue;
			}

			if (alias)
				add_alias_header(ui_JackMapRightItems, MapButtonType::Output, pj, alias);

			bool first = true;
			for (auto &map : patch->mapped_outs) {
				if (map.panel_jack_id != pj)
					continue;

				auto name = get_full_element_name(map.out.module_id, map.out.jack_id, ElementType::Output, *patch);
				add_jack_row(
					ui_JackMapRightItems,
					MapButtonType::Output,
					pj,
					!alias && first,
					name,
					(uint16_t)map.out.module_id,
					ElementCount::mark_unused_indices({.output_idx = (uint8_t)map.out.jack_id}, {.num_outputs = 1}));
				first = false;
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
	// Create a selectable row for one module jack connected to a panel jack.
	// `show_circle` draws the panel jack circle+number (first row of a panel
	// jack); otherwise the circle's space is kept but hidden so the text lines
	// up under the first row.
	void add_jack_row(lv_obj_t *parent,
					  MapButtonType type,
					  unsigned panel_jack_id,
					  bool show_circle,
					  FullElementName const &name,
					  uint16_t module_id,
					  ElementCount::Indices idx) {

		std::string text = name.module_name;
		if (!name.element_name.empty()) {
			if (!text.empty())
				text += " ";
			text += name.element_name;
		}

		auto row = create_mapping_circle_item(parent, type, panel_jack_id, text.c_str());

		if (!show_circle)
			hide_circle(row);

		lv_obj_set_user_data(row, CableEndpointUserData{module_id, idx});
		lv_obj_add_event_cb(row, follow_jack_cb, LV_EVENT_CLICKED, this);
		lv_group_add_obj(group, row);
	}

	// Show the panel jack's alias as a non-selectable header line. The circle+
	// number sits on this line, and the (circle-less) jack rows below align
	// under the alias text.
	void add_alias_header(lv_obj_t *parent, MapButtonType type, unsigned panel_jack_id, const char *alias) {
		auto header = create_mapping_circle_item(parent, type, panel_jack_id, alias);
		auto label = lv_obj_get_child(header, 1);
		lv_obj_set_style_text_color(label, Gui::orange_highlight, LV_PART_MAIN);
		lv_obj_clear_flag(header, LV_OBJ_FLAG_CLICK_FOCUSABLE | LV_OBJ_FLAG_CLICKABLE);
	}

	// Make the panel jack circle invisible while keeping its layout footprint,
	// so a continuation row's text aligns with the first row's text.
	static void hide_circle(lv_obj_t *row) {
		if (lv_obj_get_child_cnt(row) == 0)
			return;
		auto circle = lv_obj_get_child(row, 0);
		lv_obj_set_style_bg_opa(circle, LV_OPA_TRANSP, LV_PART_MAIN);
		lv_obj_set_style_border_opa(circle, LV_OPA_TRANSP, LV_PART_MAIN);
		if (lv_obj_get_child_cnt(circle) > 0)
			lv_label_set_text(lv_obj_get_child(circle, 0), "");
	}

	lv_obj_t *base = nullptr;
	PatchData *patch;
	lv_group_t *group;
};

} // namespace MetaModule
