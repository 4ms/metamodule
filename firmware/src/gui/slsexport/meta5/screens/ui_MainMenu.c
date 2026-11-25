#include "../ui.h"

void ui_MainMenu_screen_init(void)
{
ui_MainMenu = lv_obj_create(NULL);
lv_obj_clear_flag( ui_MainMenu, LV_OBJ_FLAG_SCROLLABLE );    /// Flags
lv_obj_set_style_bg_color(ui_MainMenu, lv_color_hex(0x111111), LV_PART_MAIN | LV_STATE_DEFAULT );
lv_obj_set_style_bg_opa(ui_MainMenu, 255, LV_PART_MAIN| LV_STATE_DEFAULT);

ui_MainMenuStatusBar = lv_obj_create(ui_MainMenu);
lv_obj_remove_style_all(ui_MainMenuStatusBar);
lv_obj_set_width( ui_MainMenuStatusBar, lv_pct(100));
lv_obj_set_height( ui_MainMenuStatusBar, LV_SIZE_CONTENT);   /// 1
lv_obj_set_align( ui_MainMenuStatusBar, LV_ALIGN_TOP_MID );
lv_obj_set_flex_flow(ui_MainMenuStatusBar,LV_FLEX_FLOW_COLUMN);
lv_obj_set_flex_align(ui_MainMenuStatusBar, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_START);
lv_obj_clear_flag( ui_MainMenuStatusBar, LV_OBJ_FLAG_CLICKABLE | LV_OBJ_FLAG_SCROLLABLE );    /// Flags
lv_obj_set_style_pad_left(ui_MainMenuStatusBar, ui_px(2), LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_pad_right(ui_MainMenuStatusBar, ui_px(2), LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_pad_top(ui_MainMenuStatusBar, ui_px(2), LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_pad_bottom(ui_MainMenuStatusBar, ui_px(2), LV_PART_MAIN| LV_STATE_DEFAULT);

ui_MainMenuNowPlayingPanel = lv_obj_create(ui_MainMenuStatusBar);
lv_obj_set_width( ui_MainMenuNowPlayingPanel, lv_pct(100));
lv_obj_set_height( ui_MainMenuNowPlayingPanel, ui_px(24));
lv_obj_set_x( ui_MainMenuNowPlayingPanel, 0 );
lv_obj_set_y( ui_MainMenuNowPlayingPanel, ui_px(3) );
lv_obj_set_align( ui_MainMenuNowPlayingPanel, LV_ALIGN_CENTER );
lv_obj_set_flex_flow(ui_MainMenuNowPlayingPanel,LV_FLEX_FLOW_ROW);
lv_obj_set_flex_align(ui_MainMenuNowPlayingPanel, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_SPACE_BETWEEN);
lv_obj_clear_flag( ui_MainMenuNowPlayingPanel, LV_OBJ_FLAG_PRESS_LOCK | LV_OBJ_FLAG_CLICK_FOCUSABLE | LV_OBJ_FLAG_GESTURE_BUBBLE | LV_OBJ_FLAG_SNAPPABLE | LV_OBJ_FLAG_SCROLLABLE | LV_OBJ_FLAG_SCROLL_ELASTIC | LV_OBJ_FLAG_SCROLL_MOMENTUM | LV_OBJ_FLAG_SCROLL_CHAIN );    /// Flags
lv_obj_set_scrollbar_mode(ui_MainMenuNowPlayingPanel, LV_SCROLLBAR_MODE_OFF);
lv_obj_set_style_radius(ui_MainMenuNowPlayingPanel, 0, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_bg_color(ui_MainMenuNowPlayingPanel, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT );
lv_obj_set_style_bg_opa(ui_MainMenuNowPlayingPanel, 0, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_border_color(ui_MainMenuNowPlayingPanel, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT );
lv_obj_set_style_border_opa(ui_MainMenuNowPlayingPanel, 255, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_border_width(ui_MainMenuNowPlayingPanel, 0, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_pad_left(ui_MainMenuNowPlayingPanel, ui_px(4), LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_pad_right(ui_MainMenuNowPlayingPanel, ui_px(2), LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_pad_top(ui_MainMenuNowPlayingPanel, 0, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_pad_bottom(ui_MainMenuNowPlayingPanel, 0, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_pad_row(ui_MainMenuNowPlayingPanel, 0, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_pad_column(ui_MainMenuNowPlayingPanel, 0, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_outline_color(ui_MainMenuNowPlayingPanel, lv_color_hex(0xFD8B18), LV_PART_MAIN | LV_STATE_FOCUSED );
lv_obj_set_style_outline_opa(ui_MainMenuNowPlayingPanel, 255, LV_PART_MAIN| LV_STATE_FOCUSED);
lv_obj_set_style_outline_width(ui_MainMenuNowPlayingPanel, ui_px(2), LV_PART_MAIN| LV_STATE_FOCUSED);
lv_obj_set_style_outline_pad(ui_MainMenuNowPlayingPanel, ui_px(1), LV_PART_MAIN| LV_STATE_FOCUSED);
lv_obj_set_style_outline_color(ui_MainMenuNowPlayingPanel, lv_color_hex(0xFD8B18), LV_PART_MAIN | LV_STATE_FOCUS_KEY );
lv_obj_set_style_outline_opa(ui_MainMenuNowPlayingPanel, 255, LV_PART_MAIN| LV_STATE_FOCUS_KEY);
lv_obj_set_style_outline_width(ui_MainMenuNowPlayingPanel, ui_px(2), LV_PART_MAIN| LV_STATE_FOCUS_KEY);
lv_obj_set_style_outline_pad(ui_MainMenuNowPlayingPanel, ui_px(1), LV_PART_MAIN| LV_STATE_FOCUS_KEY);

ui_MainMenuNowPlaying = lv_label_create(ui_MainMenuNowPlayingPanel);
lv_obj_set_height( ui_MainMenuNowPlaying, ui_px(20));
lv_obj_set_width( ui_MainMenuNowPlaying, LV_SIZE_CONTENT);  /// 1
lv_obj_set_x( ui_MainMenuNowPlaying, ui_px(2) );
lv_obj_set_y( ui_MainMenuNowPlaying, ui_px(8) );
lv_obj_set_align( ui_MainMenuNowPlaying, LV_ALIGN_CENTER );
lv_label_set_text(ui_MainMenuNowPlaying,"Playing:");
lv_obj_clear_flag( ui_MainMenuNowPlaying, LV_OBJ_FLAG_CLICK_FOCUSABLE | LV_OBJ_FLAG_GESTURE_BUBBLE | LV_OBJ_FLAG_SCROLLABLE | LV_OBJ_FLAG_SCROLL_ELASTIC | LV_OBJ_FLAG_SCROLL_MOMENTUM | LV_OBJ_FLAG_SCROLL_CHAIN );    /// Flags
lv_obj_set_scrollbar_mode(ui_MainMenuNowPlaying, LV_SCROLLBAR_MODE_OFF);
lv_obj_set_style_text_color(ui_MainMenuNowPlaying, lv_color_hex(0xFD8B18), LV_PART_MAIN | LV_STATE_DEFAULT );
lv_obj_set_style_text_opa(ui_MainMenuNowPlaying, 255, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_text_letter_space(ui_MainMenuNowPlaying, 0, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_text_line_space(ui_MainMenuNowPlaying, 0, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_text_font(ui_MainMenuNowPlaying, &ui_font_med_large_bold, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_radius(ui_MainMenuNowPlaying, 0, LV_PART_MAIN| LV_STATE_DEFAULT);

ui_MainMenuNowPlayingName = lv_label_create(ui_MainMenuNowPlayingPanel);
lv_obj_set_height( ui_MainMenuNowPlayingName, ui_px(20));
lv_obj_set_flex_grow( ui_MainMenuNowPlayingName, 1);
lv_obj_set_x( ui_MainMenuNowPlayingName, ui_px(2) );
lv_obj_set_y( ui_MainMenuNowPlayingName, ui_px(8) );
lv_obj_set_align( ui_MainMenuNowPlayingName, LV_ALIGN_CENTER );
lv_label_set_long_mode(ui_MainMenuNowPlayingName,LV_LABEL_LONG_SCROLL_CIRCULAR);
lv_label_set_text(ui_MainMenuNowPlayingName,"MOtS Patch - EnOsc & Looping");
lv_obj_clear_flag( ui_MainMenuNowPlayingName, LV_OBJ_FLAG_CLICK_FOCUSABLE | LV_OBJ_FLAG_GESTURE_BUBBLE | LV_OBJ_FLAG_SCROLLABLE | LV_OBJ_FLAG_SCROLL_ELASTIC | LV_OBJ_FLAG_SCROLL_MOMENTUM | LV_OBJ_FLAG_SCROLL_CHAIN );    /// Flags
lv_obj_set_scrollbar_mode(ui_MainMenuNowPlayingName, LV_SCROLLBAR_MODE_OFF);
lv_obj_set_scroll_dir(ui_MainMenuNowPlayingName, LV_DIR_LEFT);
lv_obj_set_style_text_color(ui_MainMenuNowPlayingName, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT );
lv_obj_set_style_text_opa(ui_MainMenuNowPlayingName, 255, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_text_align(ui_MainMenuNowPlayingName, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_text_decor(ui_MainMenuNowPlayingName, LV_TEXT_DECOR_NONE, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_text_font(ui_MainMenuNowPlayingName, &ui_font_med_large_bold, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_radius(ui_MainMenuNowPlayingName, 0, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_pad_left(ui_MainMenuNowPlayingName, ui_px(4), LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_pad_right(ui_MainMenuNowPlayingName, ui_px(4), LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_pad_top(ui_MainMenuNowPlayingName, 0, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_pad_bottom(ui_MainMenuNowPlayingName, 0, LV_PART_MAIN| LV_STATE_DEFAULT);

ui_MainMenuLastViewedPanel = lv_obj_create(ui_MainMenuStatusBar);
lv_obj_set_width(ui_MainMenuLastViewedPanel, lv_pct(100));
lv_obj_set_height( ui_MainMenuLastViewedPanel, ui_px(24));
lv_obj_set_x( ui_MainMenuLastViewedPanel, 0 );
lv_obj_set_y( ui_MainMenuLastViewedPanel, ui_px(26) );
lv_obj_set_align( ui_MainMenuLastViewedPanel, LV_ALIGN_TOP_MID );
lv_obj_set_flex_flow(ui_MainMenuLastViewedPanel,LV_FLEX_FLOW_ROW);
lv_obj_set_flex_align(ui_MainMenuLastViewedPanel, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_SPACE_BETWEEN);
lv_obj_add_flag( ui_MainMenuLastViewedPanel, LV_OBJ_FLAG_OVERFLOW_VISIBLE );   /// Flags
lv_obj_clear_flag( ui_MainMenuLastViewedPanel, LV_OBJ_FLAG_PRESS_LOCK | LV_OBJ_FLAG_CLICK_FOCUSABLE | LV_OBJ_FLAG_GESTURE_BUBBLE | LV_OBJ_FLAG_SNAPPABLE | LV_OBJ_FLAG_SCROLLABLE | LV_OBJ_FLAG_SCROLL_ELASTIC | LV_OBJ_FLAG_SCROLL_MOMENTUM | LV_OBJ_FLAG_SCROLL_CHAIN );    /// Flags
lv_obj_set_scrollbar_mode(ui_MainMenuLastViewedPanel, LV_SCROLLBAR_MODE_OFF);
lv_obj_set_style_radius(ui_MainMenuLastViewedPanel, 0, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_bg_color(ui_MainMenuLastViewedPanel, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT );
lv_obj_set_style_bg_opa(ui_MainMenuLastViewedPanel, 0, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_border_color(ui_MainMenuLastViewedPanel, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT );
lv_obj_set_style_border_opa(ui_MainMenuLastViewedPanel, 255, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_border_width(ui_MainMenuLastViewedPanel, 0, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_pad_left(ui_MainMenuLastViewedPanel, ui_px(4), LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_pad_right(ui_MainMenuLastViewedPanel, ui_px(4), LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_pad_top(ui_MainMenuLastViewedPanel, 0, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_pad_bottom(ui_MainMenuLastViewedPanel, 0, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_pad_row(ui_MainMenuLastViewedPanel, 0, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_pad_column(ui_MainMenuLastViewedPanel, 0, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_outline_color(ui_MainMenuLastViewedPanel, lv_color_hex(0xFD8B18), LV_PART_MAIN | LV_STATE_FOCUSED );
lv_obj_set_style_outline_opa(ui_MainMenuLastViewedPanel, 255, LV_PART_MAIN| LV_STATE_FOCUSED);
lv_obj_set_style_outline_width(ui_MainMenuLastViewedPanel, ui_px(2), LV_PART_MAIN| LV_STATE_FOCUSED);
lv_obj_set_style_outline_pad(ui_MainMenuLastViewedPanel, ui_px(1), LV_PART_MAIN| LV_STATE_FOCUSED);
lv_obj_set_style_outline_color(ui_MainMenuLastViewedPanel, lv_color_hex(0xFD8B18), LV_PART_MAIN | LV_STATE_FOCUS_KEY );
lv_obj_set_style_outline_opa(ui_MainMenuLastViewedPanel, 255, LV_PART_MAIN| LV_STATE_FOCUS_KEY);
lv_obj_set_style_outline_width(ui_MainMenuLastViewedPanel, ui_px(2), LV_PART_MAIN| LV_STATE_FOCUS_KEY);
lv_obj_set_style_outline_pad(ui_MainMenuLastViewedPanel, ui_px(1), LV_PART_MAIN| LV_STATE_FOCUS_KEY);

ui_MainMenuLastViewed = lv_label_create(ui_MainMenuLastViewedPanel);
lv_obj_set_height( ui_MainMenuLastViewed, ui_px(20));
lv_obj_set_width( ui_MainMenuLastViewed, LV_SIZE_CONTENT);  /// 1
lv_obj_set_x( ui_MainMenuLastViewed, ui_px(2) );
lv_obj_set_y( ui_MainMenuLastViewed, ui_px(8) );
lv_obj_set_align( ui_MainMenuLastViewed, LV_ALIGN_CENTER );
lv_label_set_text(ui_MainMenuLastViewed,"Last Viewed:");
lv_obj_add_flag( ui_MainMenuLastViewed, LV_OBJ_FLAG_CLICKABLE );   /// Flags
lv_obj_clear_flag( ui_MainMenuLastViewed, LV_OBJ_FLAG_CLICK_FOCUSABLE | LV_OBJ_FLAG_GESTURE_BUBBLE | LV_OBJ_FLAG_SCROLLABLE | LV_OBJ_FLAG_SCROLL_ELASTIC | LV_OBJ_FLAG_SCROLL_MOMENTUM | LV_OBJ_FLAG_SCROLL_CHAIN );    /// Flags
lv_obj_set_scrollbar_mode(ui_MainMenuLastViewed, LV_SCROLLBAR_MODE_OFF);
lv_obj_set_style_text_color(ui_MainMenuLastViewed, lv_color_hex(0xFD8B18), LV_PART_MAIN | LV_STATE_DEFAULT );
lv_obj_set_style_text_opa(ui_MainMenuLastViewed, 255, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_text_letter_space(ui_MainMenuLastViewed, 0, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_text_line_space(ui_MainMenuLastViewed, 0, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_text_font(ui_MainMenuLastViewed, &ui_font_med_large_bold, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_radius(ui_MainMenuLastViewed, 0, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_pad_left(ui_MainMenuLastViewed, 0, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_pad_right(ui_MainMenuLastViewed, 0, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_pad_top(ui_MainMenuLastViewed, 0, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_pad_bottom(ui_MainMenuLastViewed, 0, LV_PART_MAIN| LV_STATE_DEFAULT);

ui_MainMenuLastViewedName = lv_label_create(ui_MainMenuLastViewedPanel);
lv_obj_set_height( ui_MainMenuLastViewedName, ui_px(20));
lv_obj_set_flex_grow( ui_MainMenuLastViewedName, 1);
lv_obj_set_x( ui_MainMenuLastViewedName, ui_px(2) );
lv_obj_set_y( ui_MainMenuLastViewedName, ui_px(8) );
lv_obj_set_align( ui_MainMenuLastViewedName, LV_ALIGN_CENTER );
lv_label_set_long_mode(ui_MainMenuLastViewedName,LV_LABEL_LONG_SCROLL_CIRCULAR);
lv_label_set_text(ui_MainMenuLastViewedName,"MOtS Patch - EnOsc & Looping");
lv_obj_clear_flag( ui_MainMenuLastViewedName, LV_OBJ_FLAG_CLICK_FOCUSABLE | LV_OBJ_FLAG_GESTURE_BUBBLE | LV_OBJ_FLAG_SCROLLABLE | LV_OBJ_FLAG_SCROLL_ELASTIC | LV_OBJ_FLAG_SCROLL_MOMENTUM | LV_OBJ_FLAG_SCROLL_CHAIN );    /// Flags
lv_obj_set_scrollbar_mode(ui_MainMenuLastViewedName, LV_SCROLLBAR_MODE_OFF);
lv_obj_set_scroll_dir(ui_MainMenuLastViewedName, LV_DIR_LEFT);
lv_obj_set_style_text_color(ui_MainMenuLastViewedName, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT );
lv_obj_set_style_text_opa(ui_MainMenuLastViewedName, 255, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_text_align(ui_MainMenuLastViewedName, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_text_decor(ui_MainMenuLastViewedName, LV_TEXT_DECOR_NONE, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_text_font(ui_MainMenuLastViewedName, &ui_font_med_large_bold, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_radius(ui_MainMenuLastViewedName, 0, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_pad_left(ui_MainMenuLastViewedName, ui_px(4), LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_pad_right(ui_MainMenuLastViewedName, ui_px(4), LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_pad_top(ui_MainMenuLastViewedName, 0, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_pad_bottom(ui_MainMenuLastViewedName, 0, LV_PART_MAIN| LV_STATE_DEFAULT);

ui_MainMenuPanel = lv_obj_create(ui_MainMenu);
lv_obj_set_height( ui_MainMenuPanel, ui_px(131));
lv_obj_set_width( ui_MainMenuPanel, lv_pct(100));
lv_obj_set_align( ui_MainMenuPanel, LV_ALIGN_CENTER );
lv_obj_set_flex_flow(ui_MainMenuPanel,LV_FLEX_FLOW_ROW);
lv_obj_set_flex_align(ui_MainMenuPanel, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_START);
lv_obj_clear_flag( ui_MainMenuPanel, LV_OBJ_FLAG_SCROLL_ELASTIC | LV_OBJ_FLAG_SCROLL_MOMENTUM | LV_OBJ_FLAG_SCROLL_CHAIN );    /// Flags
lv_obj_set_style_radius(ui_MainMenuPanel, 0, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_bg_color(ui_MainMenuPanel, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT );
lv_obj_set_style_bg_opa(ui_MainMenuPanel, 0, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_border_color(ui_MainMenuPanel, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT );
lv_obj_set_style_border_opa(ui_MainMenuPanel, 0, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_pad_left(ui_MainMenuPanel, ui_px(12), LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_pad_right(ui_MainMenuPanel, ui_px(12), LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_pad_top(ui_MainMenuPanel, ui_px(8), LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_pad_bottom(ui_MainMenuPanel, ui_px(8), LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_pad_row(ui_MainMenuPanel, 0, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_pad_column(ui_MainMenuPanel, ui_px(14), LV_PART_MAIN| LV_STATE_DEFAULT);

lv_obj_set_style_bg_color(ui_MainMenuPanel, lv_color_hex(0xFF8918), LV_PART_SCROLLBAR | LV_STATE_DEFAULT );
lv_obj_set_style_bg_opa(ui_MainMenuPanel, 255, LV_PART_SCROLLBAR| LV_STATE_DEFAULT);
lv_obj_set_style_pad_left(ui_MainMenuPanel, 0, LV_PART_SCROLLBAR| LV_STATE_DEFAULT);
lv_obj_set_style_pad_right(ui_MainMenuPanel, 0, LV_PART_SCROLLBAR| LV_STATE_DEFAULT);
lv_obj_set_style_pad_top(ui_MainMenuPanel, 0, LV_PART_SCROLLBAR| LV_STATE_DEFAULT);
lv_obj_set_style_pad_bottom(ui_MainMenuPanel, 0, LV_PART_SCROLLBAR| LV_STATE_DEFAULT);

ui_MenuPanelPatches = lv_btn_create(ui_MainMenuPanel);
lv_obj_set_flex_grow(ui_MenuPanelPatches, 1);
lv_obj_set_height( ui_MenuPanelPatches, lv_pct(100));
lv_obj_set_align( ui_MenuPanelPatches, LV_ALIGN_CENTER );
lv_obj_set_flex_flow(ui_MenuPanelPatches,LV_FLEX_FLOW_COLUMN);
lv_obj_set_flex_align(ui_MenuPanelPatches, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER);
lv_obj_add_flag( ui_MenuPanelPatches, LV_OBJ_FLAG_SCROLL_ON_FOCUS );   /// Flags
lv_obj_clear_flag( ui_MenuPanelPatches, LV_OBJ_FLAG_PRESS_LOCK | LV_OBJ_FLAG_GESTURE_BUBBLE | LV_OBJ_FLAG_SCROLLABLE | LV_OBJ_FLAG_SCROLL_ELASTIC | LV_OBJ_FLAG_SCROLL_MOMENTUM | LV_OBJ_FLAG_SCROLL_CHAIN );    /// Flags
lv_obj_set_style_bg_color(ui_MenuPanelPatches, lv_color_hex(0x333333), LV_PART_MAIN | LV_STATE_DEFAULT );
lv_obj_set_style_bg_opa(ui_MenuPanelPatches, 255, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_pad_left(ui_MenuPanelPatches, 0, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_pad_right(ui_MenuPanelPatches, 0, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_pad_top(ui_MenuPanelPatches, ui_px(13), LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_pad_bottom(ui_MenuPanelPatches, ui_px(13), LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_pad_row(ui_MenuPanelPatches, ui_px(8), LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_pad_column(ui_MenuPanelPatches, 0, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_outline_color(ui_MenuPanelPatches, lv_color_hex(0xFD8B18), LV_PART_MAIN | LV_STATE_FOCUS_KEY );
lv_obj_set_style_outline_opa(ui_MenuPanelPatches, 255, LV_PART_MAIN| LV_STATE_FOCUS_KEY);

ui_MenuImagePatches = lv_img_create(ui_MenuPanelPatches);
lv_img_set_src(ui_MenuImagePatches, LV_SYMBOL_PLAY);
lv_obj_set_style_text_font(ui_MenuImagePatches, &ui_font_icons, LV_PART_MAIN | LV_STATE_DEFAULT);
lv_obj_set_style_text_color(ui_MenuImagePatches, lv_color_hex(0xE6E6E6), LV_PART_MAIN | LV_STATE_DEFAULT);
lv_obj_set_width(ui_MenuImagePatches, LV_SIZE_CONTENT);
lv_obj_set_height(ui_MenuImagePatches, LV_SIZE_CONTENT);
lv_obj_set_align( ui_MenuImagePatches, LV_ALIGN_CENTER );
lv_obj_add_flag( ui_MenuImagePatches, LV_OBJ_FLAG_ADV_HITTEST );   /// Flags
lv_obj_clear_flag( ui_MenuImagePatches, LV_OBJ_FLAG_SCROLLABLE );    /// Flags

ui_MenuLabelPatches = lv_label_create(ui_MenuPanelPatches);
lv_obj_set_width( ui_MenuLabelPatches, LV_SIZE_CONTENT);  /// 100
lv_obj_set_height( ui_MenuLabelPatches, LV_SIZE_CONTENT);   /// 1
lv_obj_set_align( ui_MenuLabelPatches, LV_ALIGN_CENTER );
lv_label_set_text(ui_MenuLabelPatches,"Load\nPatch");
lv_obj_set_style_text_align(ui_MenuLabelPatches, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_text_font(ui_MenuLabelPatches, &ui_font_large, LV_PART_MAIN| LV_STATE_DEFAULT);

ui_MenuPanelSave = lv_btn_create(ui_MainMenuPanel);
lv_obj_set_flex_grow(ui_MenuPanelSave, 1);
lv_obj_set_height( ui_MenuPanelSave, lv_pct(100));
lv_obj_set_align( ui_MenuPanelSave, LV_ALIGN_CENTER );
lv_obj_set_flex_flow(ui_MenuPanelSave,LV_FLEX_FLOW_COLUMN);
lv_obj_set_flex_align(ui_MenuPanelSave, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER);
lv_obj_add_flag( ui_MenuPanelSave, LV_OBJ_FLAG_SCROLL_ON_FOCUS );   /// Flags
lv_obj_clear_flag( ui_MenuPanelSave, LV_OBJ_FLAG_PRESS_LOCK | LV_OBJ_FLAG_GESTURE_BUBBLE | LV_OBJ_FLAG_SCROLLABLE | LV_OBJ_FLAG_SCROLL_ELASTIC | LV_OBJ_FLAG_SCROLL_MOMENTUM | LV_OBJ_FLAG_SCROLL_CHAIN );    /// Flags
lv_obj_set_style_bg_color(ui_MenuPanelSave, lv_color_hex(0x333333), LV_PART_MAIN | LV_STATE_DEFAULT );
lv_obj_set_style_bg_opa(ui_MenuPanelSave, 255, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_pad_left(ui_MenuPanelSave, 0, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_pad_right(ui_MenuPanelSave, 0, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_pad_top(ui_MenuPanelSave, ui_px(13), LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_pad_bottom(ui_MenuPanelSave, ui_px(13), LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_pad_row(ui_MenuPanelSave, ui_px(8), LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_pad_column(ui_MenuPanelSave, 0, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_outline_color(ui_MenuPanelSave, lv_color_hex(0xFD8B18), LV_PART_MAIN | LV_STATE_FOCUS_KEY );
lv_obj_set_style_outline_opa(ui_MenuPanelSave, 255, LV_PART_MAIN| LV_STATE_FOCUS_KEY);

ui_MenuImageSave = lv_img_create(ui_MenuPanelSave);
lv_img_set_src(ui_MenuImageSave, LV_SYMBOL_PLUS);
lv_obj_set_style_text_font(ui_MenuImageSave, &ui_font_icons, LV_PART_MAIN | LV_STATE_DEFAULT);
lv_obj_set_style_text_color(ui_MenuImageSave, lv_color_hex(0xE6E6E6), LV_PART_MAIN | LV_STATE_DEFAULT);
lv_obj_set_width(ui_MenuImageSave, LV_SIZE_CONTENT);
lv_obj_set_height(ui_MenuImageSave, LV_SIZE_CONTENT);
lv_obj_set_align( ui_MenuImageSave, LV_ALIGN_CENTER );
lv_obj_add_flag( ui_MenuImageSave, LV_OBJ_FLAG_ADV_HITTEST );   /// Flags
lv_obj_clear_flag( ui_MenuImageSave, LV_OBJ_FLAG_SCROLLABLE );    /// Flags

ui_MenuLabelSave = lv_label_create(ui_MenuPanelSave);
lv_obj_set_width( ui_MenuLabelSave, LV_SIZE_CONTENT);  /// 100
lv_obj_set_height( ui_MenuLabelSave, LV_SIZE_CONTENT);   /// 1
lv_obj_set_align( ui_MenuLabelSave, LV_ALIGN_CENTER );
lv_label_set_text(ui_MenuLabelSave,"New\nPatch");
lv_obj_set_style_text_align(ui_MenuLabelSave, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_text_font(ui_MenuLabelSave, &ui_font_large, LV_PART_MAIN| LV_STATE_DEFAULT);

ui_MenuPanelSettings = lv_btn_create(ui_MainMenuPanel);
lv_obj_set_flex_grow(ui_MenuPanelSettings, 1);
lv_obj_set_height( ui_MenuPanelSettings, lv_pct(100));
lv_obj_set_align( ui_MenuPanelSettings, LV_ALIGN_CENTER );
lv_obj_set_flex_flow(ui_MenuPanelSettings,LV_FLEX_FLOW_COLUMN);
lv_obj_set_flex_align(ui_MenuPanelSettings, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER);
lv_obj_add_flag( ui_MenuPanelSettings, LV_OBJ_FLAG_SCROLL_ON_FOCUS );   /// Flags
lv_obj_clear_flag( ui_MenuPanelSettings, LV_OBJ_FLAG_PRESS_LOCK | LV_OBJ_FLAG_GESTURE_BUBBLE | LV_OBJ_FLAG_SCROLLABLE | LV_OBJ_FLAG_SCROLL_ELASTIC | LV_OBJ_FLAG_SCROLL_MOMENTUM | LV_OBJ_FLAG_SCROLL_CHAIN );    /// Flags
lv_obj_set_style_bg_color(ui_MenuPanelSettings, lv_color_hex(0x333333), LV_PART_MAIN | LV_STATE_DEFAULT );
lv_obj_set_style_bg_opa(ui_MenuPanelSettings, 255, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_pad_left(ui_MenuPanelSettings, 0, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_pad_right(ui_MenuPanelSettings, 0, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_pad_top(ui_MenuPanelSettings, ui_px(13), LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_pad_bottom(ui_MenuPanelSettings, ui_px(13), LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_pad_row(ui_MenuPanelSettings, ui_px(8), LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_pad_column(ui_MenuPanelSettings, 0, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_outline_color(ui_MenuPanelSettings, lv_color_hex(0xFD8B18), LV_PART_MAIN | LV_STATE_FOCUS_KEY );
lv_obj_set_style_outline_opa(ui_MenuPanelSettings, 255, LV_PART_MAIN| LV_STATE_FOCUS_KEY);

ui_MenuImageSettings = lv_img_create(ui_MenuPanelSettings);
lv_img_set_src(ui_MenuImageSettings, LV_SYMBOL_SETTINGS);
lv_obj_set_style_text_font(ui_MenuImageSettings, &ui_font_icons, LV_PART_MAIN | LV_STATE_DEFAULT);
lv_obj_set_style_text_color(ui_MenuImageSettings, lv_color_hex(0xE6E6E6), LV_PART_MAIN | LV_STATE_DEFAULT);
lv_obj_set_width(ui_MenuImageSettings, LV_SIZE_CONTENT);
lv_obj_set_height(ui_MenuImageSettings, LV_SIZE_CONTENT);
lv_obj_set_align( ui_MenuImageSettings, LV_ALIGN_CENTER );
lv_obj_add_flag( ui_MenuImageSettings, LV_OBJ_FLAG_ADV_HITTEST );   /// Flags
lv_obj_clear_flag( ui_MenuImageSettings, LV_OBJ_FLAG_SCROLLABLE );    /// Flags

ui_MenuLabelSettings = lv_label_create(ui_MenuPanelSettings);
lv_obj_set_width( ui_MenuLabelSettings, LV_SIZE_CONTENT);  /// 100
lv_obj_set_height( ui_MenuLabelSettings, LV_SIZE_CONTENT);   /// 1
lv_obj_set_align( ui_MenuLabelSettings, LV_ALIGN_CENTER );
lv_label_set_text(ui_MenuLabelSettings,"Settings");
lv_obj_set_style_text_font(ui_MenuLabelSettings, &ui_font_large, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_pad_left(ui_MenuLabelSettings, 0, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_pad_right(ui_MenuLabelSettings, 0, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_pad_top(ui_MenuLabelSettings, ui_px(12), LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_pad_bottom(ui_MenuLabelSettings, 0, LV_PART_MAIN| LV_STATE_DEFAULT);

}
