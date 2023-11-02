#include "gui/slsexport/meta5/ui.h"
#include "lvgl.h"
#include "meta5/components/ui_comp.h"

struct SlsComponentInit {
	SlsComponentInit() {
		ui_init();
		lv_disp_t *dispp = lv_disp_get_default();
		lv_theme_t *theme = lv_theme_default_init(
			dispp, lv_color_hex(0xFD8B18), lv_palette_main(LV_PALETTE_BLUE), LV_THEME_DEFAULT_DARK, LV_FONT_DEFAULT);
		lv_disp_set_theme(dispp, theme);

		// Fixes for SLS not allowing us to set styles for the EDITED state
		// TODO; custom theme?

		// Keyboard buttons:
		lv_obj_set_style_text_color(ui_Keyboard, lv_color_white(), (uint32_t)LV_PART_ITEMS | LV_STATE_EDITED);
		lv_obj_set_style_bg_opa(ui_Keyboard, LV_OPA_0, (uint32_t)LV_PART_ITEMS | LV_STATE_EDITED);

		// Keyboard itself (not outlined when active)
		lv_obj_set_style_outline_opa(ui_Keyboard, LV_OPA_0, LV_STATE_EDITED);

		lv_obj_set_style_outline_color(ui_MinSlider, lv_color_hex(0xFD8B18), LV_STATE_EDITED);
		lv_obj_set_style_outline_opa(ui_MinSlider, 255, LV_STATE_EDITED);
		lv_obj_set_style_outline_width(ui_MinSlider, 2, LV_STATE_EDITED);
		lv_obj_set_style_outline_pad(ui_MinSlider, 1, LV_STATE_EDITED);
		lv_obj_set_style_radius(ui_MinSlider, 20, (uint32_t)LV_PART_INDICATOR | LV_STATE_EDITED);
		lv_obj_set_style_bg_color(ui_MinSlider, lv_color_hex(0xFD8B18), (uint32_t)LV_PART_INDICATOR | LV_STATE_EDITED);
		lv_obj_set_style_bg_opa(ui_MinSlider, 255, (uint32_t)LV_PART_INDICATOR | LV_STATE_EDITED);
		lv_obj_set_style_radius(ui_MinSlider, 15, (uint32_t)LV_PART_KNOB | LV_STATE_EDITED);
		lv_obj_set_style_bg_color(ui_MinSlider, lv_color_hex(0xFD8B18), (uint32_t)LV_PART_KNOB | LV_STATE_EDITED);
		lv_obj_set_style_bg_opa(ui_MinSlider, 255, (uint32_t)LV_PART_KNOB | LV_STATE_EDITED);

		lv_obj_set_style_outline_color(ui_MaxSlider, lv_color_hex(0xFD8B18), LV_STATE_EDITED);
		lv_obj_set_style_outline_opa(ui_MaxSlider, 255, LV_STATE_EDITED);
		lv_obj_set_style_outline_width(ui_MaxSlider, 2, LV_STATE_EDITED);
		lv_obj_set_style_outline_pad(ui_MaxSlider, 1, LV_STATE_EDITED);
		lv_obj_set_style_radius(ui_MaxSlider, 20, (uint32_t)LV_PART_INDICATOR | LV_STATE_EDITED);
		lv_obj_set_style_bg_color(ui_MaxSlider, lv_color_hex(0xFD8B18), (uint32_t)LV_PART_INDICATOR | LV_STATE_EDITED);
		lv_obj_set_style_bg_opa(ui_MaxSlider, 255, (uint32_t)LV_PART_INDICATOR | LV_STATE_EDITED);
		lv_obj_set_style_radius(ui_MaxSlider, 15, (uint32_t)LV_PART_KNOB | LV_STATE_EDITED);
		lv_obj_set_style_bg_color(ui_MaxSlider, lv_color_hex(0xFD8B18), (uint32_t)LV_PART_KNOB | LV_STATE_EDITED);
		lv_obj_set_style_bg_opa(ui_MaxSlider, 255, (uint32_t)LV_PART_KNOB | LV_STATE_EDITED);
	}
};

lv_obj_t *lv_obj_create_copy(lv_obj_t *parent, lv_obj_t *copy) {

	if (copy == nullptr)
		return nullptr;

	lv_obj_t *new_obj = lv_obj_class_create_obj(copy->class_p, parent);

	if (new_obj == nullptr)
		return nullptr;

	new_obj->spec_attr->scroll = copy->spec_attr->scroll;
	new_obj->spec_attr->ext_click_pad = copy->spec_attr->ext_click_pad;
	new_obj->spec_attr->ext_draw_size = copy->spec_attr->ext_draw_size;
	new_obj->spec_attr->scrollbar_mode = copy->spec_attr->scrollbar_mode;
	new_obj->spec_attr->scroll_snap_x = copy->spec_attr->scroll_snap_x;
	new_obj->spec_attr->scroll_snap_y = copy->spec_attr->scroll_snap_y;
	new_obj->spec_attr->scroll_dir = copy->spec_attr->scroll_dir;
	new_obj->spec_attr->event_dsc_cnt = copy->spec_attr->event_dsc_cnt;
	new_obj->spec_attr->layer_type = copy->spec_attr->layer_type;

	// _lv_obj_style_t * styles; //array of style_cnt elements
	for (unsigned i = 0; i < copy->style_cnt; i++) {
		lv_style_t *copy_style = copy->styles[i].style;
		uint32_t copy_selector = copy->styles[i].selector;
		// uint32_t copy_is_local = copy->styles[i].is_local;
		// uint32_t copy_is_trans = copy->styles[i].is_trans;
		lv_obj_add_style(new_obj, copy_style, copy_selector);
	}

	new_obj->coords = copy->coords;
	new_obj->flags = copy->flags;
	new_obj->state = copy->state;
	new_obj->layout_inv = copy->layout_inv;
	new_obj->scr_layout_inv = copy->scr_layout_inv;
	new_obj->skip_trans = copy->skip_trans;
	// new_obj->style_cnt = copy->style_cnt;
	new_obj->h_layout = copy->h_layout;
	new_obj->w_layout = copy->w_layout;
	new_obj->being_deleted = copy->being_deleted;

	for (unsigned i = 0; i < copy->spec_attr->child_cnt; i++) {
		lv_obj_create_copy(new_obj, copy->spec_attr->children[i]);
		// lv_obj_class_create_obj(copy->spec_attr->children[i]->class_p, new_obj);
	}

	//Need to set the group manually
	new_obj->spec_attr->group_p = nullptr;

	//Need to set user_data manually
	new_obj->user_data = nullptr;

	//Need to set events manually
	new_obj->spec_attr->event_dsc = nullptr;

	return new_obj;
}
