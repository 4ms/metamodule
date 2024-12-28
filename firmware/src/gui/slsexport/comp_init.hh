#pragma once
#include "gui/helpers/lv_helpers.hh"
#include "lvgl.h"
#include "ui_local.h"
#include <array>

namespace MetaModule
{

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

		// Sliders
		for (auto slider : {ui_MinSlider,
							ui_MaxSlider,
							ui_PVCablesTranspSlider,
							ui_PVJackMapTranspSlider,
							ui_PVControlMapTranspSlider,
							ui_MVCablesTranspSlider,
							ui_MVJackMapTranspSlider,
							ui_MVControlMapTranspSlider})
		{
			style_slider(slider);
		}

		lv_obj_set_parent(ui_MessagePanel, lv_layer_top());
		lv_obj_set_y(ui_MessagePanel, -80);

		lv_obj_set_parent(ui_OverloadMsgLabel, lv_layer_top());
		lv_hide(ui_OverloadMsgLabel);
	}

	static void style_slider(lv_obj_t *slider) {
		lv_obj_set_style_outline_color(slider, lv_color_hex(0xFD8B18), LV_STATE_EDITED);
		lv_obj_set_style_outline_opa(slider, 255, LV_STATE_EDITED);
		lv_obj_set_style_outline_width(slider, 2, LV_STATE_EDITED);
		lv_obj_set_style_outline_pad(slider, 1, LV_STATE_EDITED);
		lv_obj_set_style_radius(slider, 20, (uint32_t)LV_PART_INDICATOR | LV_STATE_EDITED);
		lv_obj_set_style_bg_color(slider, lv_color_hex(0xFD8B18), (uint32_t)LV_PART_INDICATOR | LV_STATE_EDITED);
		lv_obj_set_style_bg_opa(slider, 255, (uint32_t)LV_PART_INDICATOR | LV_STATE_EDITED);
		lv_obj_set_style_radius(slider, 15, (uint32_t)LV_PART_KNOB | LV_STATE_EDITED);
		lv_obj_set_style_bg_color(slider, lv_color_hex(0xFD8B18), (uint32_t)LV_PART_KNOB | LV_STATE_EDITED);
		lv_obj_set_style_bg_opa(slider, 255, (uint32_t)LV_PART_KNOB | LV_STATE_EDITED);
	}
};

} // namespace MetaModule
