#pragma once
#include "conf/panel_conf.hh"
#include "gui/ui_scale.h"
#include "gui/helpers/lv_helpers.hh"
#include "gui/slsexport/meta5/ui.h"
#include "lvgl.h"
#include <array>
#include <type_traits>

namespace MetaModule
{

// The knob set view's panes: the area for each panel knob where its mapping containers go, laid out as
// the knobs are on the panel. If one knob maps to multiple things, then there will be multiple
// containers in that knob's pane.

// MP1: the SquareLine panes. A-F in the middle (big), u-w left and x-z right
struct MediumKnobSetPanes {
	std::array<lv_obj_t *, 12> panes{
		ui_KnobPanelA,
		ui_KnobPanelB,
		ui_KnobPanelC,
		ui_KnobPanelD,
		ui_KnobPanelE,
		ui_KnobPanelF,
		ui_KnobPanelU,
		ui_KnobPanelV,
		ui_KnobPanelW,
		ui_KnobPanelX,
		ui_KnobPanelY,
		ui_KnobPanelZ,
	};

	// These are the first container in each pane. We always keep one here
	// so that a disabled knob shows up as grey-ed out
	std::array<lv_obj_t *, 12> containers{
		ui_KnobContainerA,
		ui_KnobContainerB,
		ui_KnobContainerC,
		ui_KnobContainerD,
		ui_KnobContainerE,
		ui_KnobContainerF,
		ui_KnobContainerU,
		ui_KnobContainerV,
		ui_KnobContainerW,
		ui_KnobContainerX,
		ui_KnobContainerY,
		ui_KnobContainerZ,
	};

	// Another container in a knob's pane
	lv_obj_t *create_container(unsigned panel_knob_id) {
		return (panel_knob_id < 6) ? ui_KnobContainerBig_create(panes[panel_knob_id]) :
									 ui_KnobContainer_create(panes[panel_knob_id]);
	}
};

// Pro: 4 columns of 4 encoders, as on the panel: ENC1-4 (A-D) and ENC5-8 (E-H) left of the screen, and
// ENC9-12 (s-v) and ENC13-16 (w-z) right of it, each column top to bottom.
// They're made here, in place of the SquareLine panes (which are hidden). The knobs are smaller than
// MP1's so that four rows fit.
struct ProKnobSetPanes {
	static constexpr unsigned NumColumns = 4;
	static constexpr unsigned KnobsPerColumn = 4;
	static constexpr unsigned NumKnobs = NumColumns * KnobsPerColumn;

	std::array<lv_obj_t *, NumKnobs> panes{};

	// These are the first container in each pane. We always keep one here
	// so that a disabled knob shows up as grey-ed out
	std::array<lv_obj_t *, NumKnobs> containers{};

	ProKnobSetPanes() {
		lv_hide(ui_KnobSetPanelLeft);
		lv_hide(ui_KnobSetPanelCenter);
		lv_hide(ui_KnobSetPanelRight);

		// Two columns, a gap (the screen), two columns
		unsigned index = 0;
		for (unsigned col = 0; col < NumColumns; col++) {
			if (col == NumColumns / 2) {
				auto gap = lv_obj_create(ui_KnobSetContainer);
				lv_obj_remove_style_all(gap);
				lv_obj_set_height(gap, ui_px(1));
				lv_obj_set_flex_grow(gap, 1);
				lv_obj_clear_flag(gap, LV_OBJ_FLAG_CLICKABLE | LV_OBJ_FLAG_SCROLLABLE);
				lv_obj_move_to_index(gap, index++);
			}

			auto column = create_column();
			lv_obj_move_to_index(column, index++);
			if (col == 0)
				lv_obj_add_flag(column, LV_OBJ_FLAG_FLEX_IN_NEW_TRACK);

			for (unsigned row = 0; row < KnobsPerColumn; row++) {
				auto id = col * KnobsPerColumn + row;
				panes[id] = create_pane(column);
				containers[id] = create_container(id);
			}
		}
	}

	// Another container in a knob's pane: MP1's small knob, made smaller
	lv_obj_t *create_container(unsigned panel_knob_id) {
		auto cont = ui_KnobContainer_create(panes[panel_knob_id]);
		lv_obj_set_height(cont, KnobHeight);
		lv_obj_set_style_pad_top(cont, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

		// The arc, and the circle with the knob's letter and the indicator, centered in it
		lv_obj_set_size(lv_obj_get_child(cont, 0), ArcSize, ArcSize);
		auto circle = lv_obj_get_child(cont, 1);
		lv_obj_set_size(circle, CircleSize, CircleSize);
		lv_obj_set_y(circle, (ArcSize - CircleSize) / 2);
		lv_obj_set_y(lv_obj_get_child(cont, 3), ArcSize / 2 - IndicatorPivot);

		// The label, just below the arc's ends
		auto label = lv_obj_get_child(cont, 2);
		lv_obj_set_y(label, LabelY);
		lv_obj_set_height(label, KnobHeight - LabelY);

		return cont;
	}

private:
	static constexpr lv_coord_t ColumnWidth = ui_px(50);
	static constexpr lv_coord_t PaneWidth = ui_px(52);
	// Room below the knob for the pane's scrollbar (when a knob has more than one mapping)
	static constexpr lv_coord_t PaneHeight = ui_px(52);

	// MP1's small knob is 64 high: 44 arc, 22 circle, label at 31 (two lines)
	static constexpr lv_coord_t KnobHeight = ui_px(50);
	static constexpr lv_coord_t ArcSize = ui_px(36);
	static constexpr lv_coord_t CircleSize = ui_px(20);
	static constexpr lv_coord_t LabelY = ui_px(25);
	static constexpr lv_coord_t IndicatorPivot = ui_px(10); // the indicator's transform_pivot_y

	// Like the SquareLine page's ui_KnobSetPanelLeft
	static lv_obj_t *create_column() {
		auto column = lv_obj_create(ui_KnobSetContainer);
		lv_obj_set_width(column, ColumnWidth);
		lv_obj_set_height(column, PaneHeight * KnobsPerColumn);
		lv_obj_set_flex_flow(column, LV_FLEX_FLOW_COLUMN);
		lv_obj_set_flex_align(column, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER);
		lv_obj_add_flag(column, LV_OBJ_FLAG_OVERFLOW_VISIBLE | LV_OBJ_FLAG_SCROLL_ON_FOCUS);
		lv_obj_clear_flag(column,
						  LV_OBJ_FLAG_PRESS_LOCK | LV_OBJ_FLAG_GESTURE_BUBBLE | LV_OBJ_FLAG_SNAPPABLE |
							  LV_OBJ_FLAG_SCROLLABLE | LV_OBJ_FLAG_SCROLL_ELASTIC | LV_OBJ_FLAG_SCROLL_MOMENTUM |
							  LV_OBJ_FLAG_SCROLL_CHAIN);
		lv_obj_set_scrollbar_mode(column, LV_SCROLLBAR_MODE_OFF);
		lv_obj_set_style_radius(column, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
		lv_obj_set_style_bg_opa(column, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
		lv_obj_set_style_border_width(column, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
		lv_obj_set_style_pad_all(column, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
		lv_obj_set_style_pad_row(column, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
		lv_obj_set_style_pad_column(column, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
		return column;
	}

	// Like the SquareLine page's ui_KnobPanelU
	static lv_obj_t *create_pane(lv_obj_t *column) {
		auto pane = lv_obj_create(column);
		lv_obj_set_width(pane, PaneWidth);
		lv_obj_set_height(pane, PaneHeight);
		lv_obj_set_flex_flow(pane, LV_FLEX_FLOW_ROW);
		lv_obj_set_flex_align(pane, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_START);
		lv_obj_clear_flag(pane,
						  LV_OBJ_FLAG_CLICKABLE | LV_OBJ_FLAG_PRESS_LOCK | LV_OBJ_FLAG_CLICK_FOCUSABLE |
							  LV_OBJ_FLAG_GESTURE_BUBBLE | LV_OBJ_FLAG_SNAPPABLE | LV_OBJ_FLAG_SCROLL_ELASTIC |
							  LV_OBJ_FLAG_SCROLL_MOMENTUM | LV_OBJ_FLAG_SCROLL_CHAIN);
		lv_obj_set_scroll_dir(pane, LV_DIR_HOR);
		lv_obj_set_style_bg_opa(pane, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
		lv_obj_set_style_border_side(pane, LV_BORDER_SIDE_NONE, LV_PART_MAIN | LV_STATE_DEFAULT);
		lv_obj_set_style_pad_all(pane, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
		lv_obj_set_style_pad_row(pane, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
		lv_obj_set_style_pad_column(pane, ui_px(8), LV_PART_MAIN | LV_STATE_DEFAULT);

		lv_obj_set_style_radius(pane, 0, LV_PART_SCROLLBAR | LV_STATE_DEFAULT);
		lv_obj_set_style_bg_color(pane, lv_color_hex(0xFD8B18), LV_PART_SCROLLBAR | LV_STATE_DEFAULT);
		lv_obj_set_style_bg_opa(pane, 255, LV_PART_SCROLLBAR | LV_STATE_DEFAULT);
		lv_obj_set_style_outline_width(pane, 0, LV_PART_SCROLLBAR | LV_STATE_DEFAULT);
		lv_obj_set_style_pad_left(pane, ui_px(2), LV_PART_SCROLLBAR | LV_STATE_DEFAULT);
		lv_obj_set_style_pad_right(pane, ui_px(2), LV_PART_SCROLLBAR | LV_STATE_DEFAULT);
		lv_obj_set_style_pad_top(pane, 0, LV_PART_SCROLLBAR | LV_STATE_DEFAULT);
		lv_obj_set_style_pad_bottom(pane, ui_px(-1), LV_PART_SCROLLBAR | LV_STATE_DEFAULT);
		return pane;
	}
};

using KnobSetPanes =
	std::conditional_t<PanelDef::NumKnobs == ProKnobSetPanes::NumKnobs, ProKnobSetPanes, MediumKnobSetPanes>;

} // namespace MetaModule
