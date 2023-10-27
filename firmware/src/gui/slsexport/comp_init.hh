#include "gui/slsexport/meta5/ui.h"
#include "lvgl.h"
#include "meta5/components/ui_comp.h"

struct SlsComponentInit {
	SlsComponentInit() {
		ui_init();
		lv_disp_t *dispp = lv_disp_get_default();
		lv_theme_t *theme = lv_theme_default_init(dispp,
												  lv_palette_main(LV_PALETTE_ORANGE),
												  lv_palette_main(LV_PALETTE_BLUE),
												  LV_THEME_DEFAULT_DARK,
												  LV_FONT_DEFAULT);
		lv_disp_set_theme(dispp, theme);

		lv_obj_set_style_text_color(ui_Keyboard, lv_color_white(), LV_PART_ITEMS | LV_STATE_EDITED);
		lv_obj_set_style_bg_opa(ui_Keyboard, LV_OPA_0, LV_PART_ITEMS | LV_STATE_EDITED);
		lv_obj_set_style_outline_opa(ui_Keyboard, LV_OPA_0, LV_STATE_EDITED);
	}
};
