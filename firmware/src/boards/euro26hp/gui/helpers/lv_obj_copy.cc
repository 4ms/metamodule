#include "lvgl.h"

lv_obj_t *lv_obj_create_copy(lv_obj_t *parent, lv_obj_t *copy) {

	if (copy == nullptr)
		return nullptr;

	lv_obj_t *new_obj = lv_obj_class_create_obj(copy->class_p, parent);

	if (new_obj == nullptr)
		return nullptr;

	lv_obj_class_init_obj(new_obj);

	lv_obj_allocate_spec_attr(new_obj);

	new_obj->spec_attr->scroll = copy->spec_attr->scroll;
	new_obj->spec_attr->ext_click_pad = copy->spec_attr->ext_click_pad;
	new_obj->spec_attr->ext_draw_size = copy->spec_attr->ext_draw_size;
	new_obj->spec_attr->scrollbar_mode = copy->spec_attr->scrollbar_mode;
	new_obj->spec_attr->scroll_snap_x = copy->spec_attr->scroll_snap_x;
	new_obj->spec_attr->scroll_snap_y = copy->spec_attr->scroll_snap_y;
	new_obj->spec_attr->scroll_dir = copy->spec_attr->scroll_dir;
	new_obj->spec_attr->event_dsc_cnt = 0; //events must be added manually
	new_obj->spec_attr->layer_type = copy->spec_attr->layer_type;

	new_obj->style_cnt = 0;
	for (unsigned i = 0; i < copy->style_cnt; i++) {
		lv_style_t *copy_style = copy->styles[i].style;
		lv_style_selector_t copy_selector = copy->styles[i].selector;

		//copy style props and values
		if (copy_style->prop_cnt > 0) {
			uint8_t *tmp = copy_style->v_p.values_and_props + copy_style->prop_cnt * sizeof(lv_style_value_t);
			auto *props = (uint16_t *)tmp;
			for (uint32_t propi = 0; propi < copy_style->prop_cnt; propi++) {
				auto *values = (lv_style_value_t *)copy_style->v_p.values_and_props;
				lv_style_value_t value = values[propi];
				auto prop = static_cast<lv_style_prop_t>(props[propi]);
				lv_obj_set_local_style_prop(new_obj, prop, value, copy_selector);
			}
		}
	}

	new_obj->coords = copy->coords;

	// TODO: better if we call lv_obj_add_flag(new_obj, flag_bit)?
	new_obj->flags = copy->flags;

	new_obj->state = copy->state;
	new_obj->layout_inv = 1;				//"dirty", needs redrawing
	new_obj->scr_layout_inv = 0;			//seems to only apply to screens?
	new_obj->skip_trans = copy->skip_trans; //??
	new_obj->h_layout = copy->h_layout;		//1 if height is set by layout (flex, grid)
	new_obj->w_layout = copy->w_layout;		//1 if width is set by layout
	new_obj->being_deleted = 0;

	for (unsigned i = 0; i < copy->spec_attr->child_cnt; i++) {
		lv_obj_create_copy(new_obj, copy->spec_attr->children[i]);
	}

	//Need to set the group manually
	new_obj->spec_attr->group_p = nullptr;

	//Need to set user_data manually
	new_obj->user_data = nullptr;

	//Need to set events manually
	new_obj->spec_attr->event_dsc = nullptr;

	return new_obj;
}
