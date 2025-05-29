#pragma once
#include "gui/dyn_display.hh"
#include "gui/helpers/lv_helpers.hh"
#include "gui/pages/base.hh"
#include "gui/pages/page_list.hh"
#include "gui/slsexport/meta5/ui.h"

namespace MetaModule
{

struct FullscreenGraphicPage : PageBase {

	FullscreenGraphicPage(PatchContext info)
		: PageBase{info, PageId::FullscreenGraphic}
		, dyn_draw{patch_playloader} {

		screen = lv_obj_create(NULL);
		lv_obj_clear_flag(screen, LV_OBJ_FLAG_SCROLLABLE);
		lv_obj_set_style_opa(screen, LV_OPA_100, LV_PART_MAIN);
		lv_obj_set_style_bg_color(screen, lv_color_black(), LV_PART_MAIN);
		lv_obj_set_size(screen, 320, 240);
		lv_obj_set_style_pad_all(screen, 0, LV_PART_MAIN);
		lv_obj_set_style_border_width(screen, 0, LV_PART_MAIN);
		lv_obj_set_style_outline_width(screen, 0, LV_PART_MAIN);

		init_bg(screen);
	}

	void init(DrawnElement const &el) {
		drawn_el = &el;
		dynamic_elements_prepared = false;
	}

	void prepare_focus() final {
	}

	void update() final {
		if (gui_state.back_button.is_just_released()) {
			page_list.request_last_page();
		}

		prepare_dynamic_elements();
		dyn_draw.draw();
	}

	void blur() final {
		dyn_draw.blur();
	}

private:
	void prepare_dynamic_elements() {
		if (!dynamic_elements_prepared) {
			dyn_draw.prepare_display(*drawn_el, canvas);
			dynamic_elements_prepared = true;
		}
	}

	lv_obj_t *screen;
	lv_obj_t *canvas;
	DynamicDisplay dyn_draw;
	DrawnElement const *drawn_el;

	bool dynamic_elements_prepared = false;
};

} // namespace MetaModule
