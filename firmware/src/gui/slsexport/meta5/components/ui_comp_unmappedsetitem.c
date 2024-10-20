// This file was generated by SquareLine Studio
// SquareLine Studio version: SquareLine Studio 1.4.2
// LVGL version: 8.3.6
// Project name: Main

#include "../ui.h"


// COMPONENT UnmappedSetItem

lv_obj_t *ui_UnmappedSetItem_create(lv_obj_t *comp_parent) {

lv_obj_t *cui_UnmappedSetItem;
cui_UnmappedSetItem = lv_obj_create(comp_parent);
lv_obj_set_height( cui_UnmappedSetItem, 28);
lv_obj_set_width( cui_UnmappedSetItem, lv_pct(100));
lv_obj_set_align( cui_UnmappedSetItem, LV_ALIGN_LEFT_MID );
lv_obj_add_flag( cui_UnmappedSetItem, LV_OBJ_FLAG_OVERFLOW_VISIBLE | LV_OBJ_FLAG_SCROLL_ON_FOCUS );   /// Flags
lv_obj_clear_flag( cui_UnmappedSetItem, LV_OBJ_FLAG_PRESS_LOCK | LV_OBJ_FLAG_GESTURE_BUBBLE | LV_OBJ_FLAG_SNAPPABLE | LV_OBJ_FLAG_SCROLLABLE | LV_OBJ_FLAG_SCROLL_ELASTIC | LV_OBJ_FLAG_SCROLL_MOMENTUM | LV_OBJ_FLAG_SCROLL_CHAIN );    /// Flags
lv_obj_set_style_radius(cui_UnmappedSetItem, 0, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_bg_color(cui_UnmappedSetItem, lv_color_hex(0xFF8918), LV_PART_MAIN | LV_STATE_DEFAULT );
lv_obj_set_style_bg_opa(cui_UnmappedSetItem, 0, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_border_width(cui_UnmappedSetItem, 0, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_pad_left(cui_UnmappedSetItem, 0, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_pad_right(cui_UnmappedSetItem, 0, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_pad_top(cui_UnmappedSetItem, 2, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_pad_bottom(cui_UnmappedSetItem, 3, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_pad_row(cui_UnmappedSetItem, 0, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_pad_column(cui_UnmappedSetItem, 0, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_text_color(cui_UnmappedSetItem, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT );
lv_obj_set_style_text_opa(cui_UnmappedSetItem, 255, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_outline_color(cui_UnmappedSetItem, lv_color_hex(0xFF8918), LV_PART_MAIN | LV_STATE_FOCUSED );
lv_obj_set_style_outline_opa(cui_UnmappedSetItem, 255, LV_PART_MAIN| LV_STATE_FOCUSED);
lv_obj_set_style_outline_width(cui_UnmappedSetItem, 2, LV_PART_MAIN| LV_STATE_FOCUSED);
lv_obj_set_style_outline_pad(cui_UnmappedSetItem, -1, LV_PART_MAIN| LV_STATE_FOCUSED);
lv_obj_set_style_text_color(cui_UnmappedSetItem, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_FOCUSED );
lv_obj_set_style_text_opa(cui_UnmappedSetItem, 255, LV_PART_MAIN| LV_STATE_FOCUSED);
lv_obj_set_style_outline_color(cui_UnmappedSetItem, lv_color_hex(0xFF8918), LV_PART_MAIN | LV_STATE_FOCUS_KEY );
lv_obj_set_style_outline_opa(cui_UnmappedSetItem, 255, LV_PART_MAIN| LV_STATE_FOCUS_KEY);
lv_obj_set_style_outline_width(cui_UnmappedSetItem, 2, LV_PART_MAIN| LV_STATE_FOCUS_KEY);
lv_obj_set_style_outline_pad(cui_UnmappedSetItem, -1, LV_PART_MAIN| LV_STATE_FOCUS_KEY);

lv_obj_t *cui_KnobSetNameText;
cui_KnobSetNameText = lv_label_create(cui_UnmappedSetItem);
lv_obj_set_width( cui_KnobSetNameText, LV_SIZE_CONTENT);  /// 1
lv_obj_set_height( cui_KnobSetNameText, LV_SIZE_CONTENT);   /// 15
lv_obj_set_align( cui_KnobSetNameText, LV_ALIGN_LEFT_MID );
lv_label_set_text(cui_KnobSetNameText,"Default");
lv_obj_clear_flag( cui_KnobSetNameText, LV_OBJ_FLAG_PRESS_LOCK | LV_OBJ_FLAG_CLICK_FOCUSABLE | LV_OBJ_FLAG_GESTURE_BUBBLE | LV_OBJ_FLAG_SNAPPABLE | LV_OBJ_FLAG_SCROLLABLE | LV_OBJ_FLAG_SCROLL_ELASTIC | LV_OBJ_FLAG_SCROLL_MOMENTUM | LV_OBJ_FLAG_SCROLL_CHAIN );    /// Flags
lv_obj_set_style_text_font(cui_KnobSetNameText, &ui_font_MuseoSansRounded70014, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_pad_left(cui_KnobSetNameText, 31, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_pad_right(cui_KnobSetNameText, 0, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_pad_top(cui_KnobSetNameText, 0, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_pad_bottom(cui_KnobSetNameText, 0, LV_PART_MAIN| LV_STATE_DEFAULT);

lv_obj_t ** children = lv_mem_alloc(sizeof(lv_obj_t *) * _UI_COMP_UNMAPPEDSETITEM_NUM);
children[UI_COMP_UNMAPPEDSETITEM_UNMAPPEDSETITEM] = cui_UnmappedSetItem;
children[UI_COMP_UNMAPPEDSETITEM_KNOBSETNAMETEXT] = cui_KnobSetNameText;
lv_obj_add_event_cb(cui_UnmappedSetItem, get_component_child_event_cb, LV_EVENT_GET_COMP_CHILD, children);
lv_obj_add_event_cb(cui_UnmappedSetItem, del_component_child_event_cb, LV_EVENT_DELETE, children);
ui_comp_UnmappedSetItem_create_hook(cui_UnmappedSetItem);
return cui_UnmappedSetItem; 
}

