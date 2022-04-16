#pragma once
#include "pages/base.hh"
#include "pages/lvgl_mem_helper.hh"
#include "pages/lvgl_string_helper.hh"
#include "pages/styles.hh"
#include "printf.h"

namespace MetaModule
{

struct PatchViewPage : PageBase {
	PatchViewPage(PatchInfo info)
		: PageBase{info}
		, base(lv_obj_create(nullptr)) {
		init_bg(base);

		popup_cont = lv_obj_create(base);
		lv_obj_add_style(popup_cont, &Gui::popup_box_style, LV_PART_MAIN);
		lv_obj_set_flex_flow(popup_cont, LV_FLEX_FLOW_ROW);

		popup_patchname = lv_label_create(popup_cont);
		lv_obj_add_style(popup_patchname, &Gui::header_style, LV_PART_MAIN);
		// lv_obj_set_pos(popup_patchname, 0, 0);
		// lv_obj_set_align(popup_patchname, LV_ALIGN_TOP_MID);
		lv_obj_set_size(popup_patchname, 320, 30);

		popup_desc = lv_label_create(popup_cont);
		lv_obj_add_style(popup_patchname, &Gui::header_style, LV_PART_MAIN);
		lv_label_set_long_mode(popup_desc, LV_LABEL_LONG_DOT);
		lv_obj_set_size(popup_desc, 320, 30);
	}

private:
	lv_obj_t *popup_desc;
	lv_obj_t *popup_patchname;
	lv_obj_t *popup_cont;
	lv_obj_t *base;
};
} // namespace MetaModule
