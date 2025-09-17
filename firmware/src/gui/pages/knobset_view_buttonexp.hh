#pragma once
#include "gui/elements/element_name.hh"
#include "gui/helpers/lv_helpers.hh"
#include "gui/slsexport/meta5/ui.h"
#include "gui/slsexport/ui_local.h"
#include "gui/styles.hh"
#include "lvgl.h"
#include "metaparams.hh"
#include "patch/patch.hh"
#include "util/countzip.hh"

namespace MetaModule
{

struct ButtonExpanderMapsView {
	ButtonExpanderMapsView(MetaParams const &metaparams)
		: metaparams{metaparams} {

		for (auto [i, but_pane] : enumerate(butexp_panes)) {
			but_pane = create_button_expander_pane(butexp_columns[i / 8]);
			auto cont = create_button_expander_item(but_pane);
			lv_label_set_text(get_button_label(cont), "");
			set_for_button(cont, i);
			lv_disable(cont);
			lv_disable(get_button_circle(cont));
			lv_obj_set_style_bg_opa(get_button_circle(cont), LV_OPA_30, LV_STATE_DISABLED);
		}
	}

	lv_obj_t *create_button_item(unsigned idx, MappedKnob const &map, PatchData *patch) {
		lv_obj_t *cont;

		if (!map.ext_button().has_value())
			return nullptr;
		auto button_id = map.ext_button().value();

		if (lv_obj_get_child_cnt(butexp_panes[button_id]) == 1) {
			cont = lv_obj_get_child(butexp_panes[button_id], 0);
		} else {
			cont = create_button_expander_item(butexp_panes[button_id]);
		}
		lv_enable(cont);
		lv_enable(get_button_circle(cont));

		set_param_item_name(get_button_label(cont), map, patch);
		set_for_button(cont, button_id);

		lv_obj_add_event_cb(cont, focus_cb, LV_EVENT_FOCUSED, this);
		lv_obj_add_event_cb(cont, defocus_cb, LV_EVENT_DEFOCUSED, this);

		// ???
		// num_maps[map.panel_knob_id]++;
		// set_knob_arc<min_arc, max_arc>(map, get_knob(cont), 0);
		// set_for_knob(cont, map.panel_knob_id);
		// arcs[idx] = get_knob(cont);
		// indicators[idx] = get_indicator(cont);

		return cont;
	}

	void add_to_group(lv_group_t *group) {
		for (auto *pane : butexp_panes) {
			if (pane)
				lv_foreach_child(pane, [group](lv_obj_t *cont, int idx) { lv_group_add_obj(group, cont); });
		}
	}

	void hide_unused_columns() {
		for (unsigned i = 0; auto *col : butexp_columns) {
			bool exp_connected = (1 << i) & metaparams.button_exp_connected;
			i++;

			bool has_mappings = false;
			lv_foreach_child(col, [&has_mappings](lv_obj_t *cont, int idx) {
				if ((lv_obj_get_child_cnt(cont) > 0) && !lv_obj_has_state(lv_obj_get_child(cont, 0), LV_STATE_DISABLED))
					has_mappings = true;
			});

			lv_show(col, (exp_connected || has_mappings));
		}
	}

	void blur() {
		// Clear all containers except for the original ones
		for (auto pane : butexp_panes) {
			if (auto num_children = lv_obj_get_child_cnt(pane); num_children > 1) {
				for (auto i = 1u; i < num_children; i++) {
					lv_obj_del_async(lv_obj_get_child(pane, i));
				}
			}
		}
	}

private:
	static void set_for_button(lv_obj_t *cont, unsigned button_id) {
		lv_label_set_text_fmt(get_button_circle_number(cont), "%u", button_id + 1);
		lv_obj_set_style_bg_color(get_button_circle(cont), Gui::knob_palette[button_id % 6], LV_PART_MAIN);
	}

	static lv_obj_t *get_button_label(lv_obj_t *container) {
		if (container && lv_obj_get_child_cnt(container) > 1)
			return lv_obj_get_child(container, 1);
		else
			return nullptr;
	}

	static lv_obj_t *get_button_circle(lv_obj_t *container) {
		return lv_obj_get_child(container, 0);
	}

	static lv_obj_t *get_button_circle_number(lv_obj_t *container) {
		return lv_obj_get_child(get_button_circle(container), 0);
	}

	static void focus_cb(lv_event_t *event) {
		lv_obj_scroll_to_y(ui_KnobSetContainer, 210, LV_ANIM_ON);

		if (auto text_label = get_button_label(event->target)) {
			lv_label_set_long_mode(text_label, LV_LABEL_LONG_SCROLL);
		}
	}

	static void defocus_cb(lv_event_t *event) {
		if (auto text_label = get_button_label(event->target)) {
			lv_label_set_long_mode(text_label, LV_LABEL_LONG_WRAP);
		}
	}

	MetaParams const &metaparams;

	std::array<lv_obj_t *, 4> butexp_columns{
		ui_KnobSetButtonExp1Cont,
		ui_KnobSetButtonExp2Cont,
		ui_KnobSetButtonExp3Cont,
		ui_KnobSetButtonExp4Cont,
	};

	std::array<lv_obj_t *, 32> butexp_panes{};
};

} // namespace MetaModule
