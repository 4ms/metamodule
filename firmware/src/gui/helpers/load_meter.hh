#pragma once
#include "delay.hh"
#include "gui/helpers/lv_helpers.hh"
#include "lvgl.h"
#include "metaparams.hh"

namespace MetaModule
{

inline void update_load_text(MetaParams const &metaparams, lv_obj_t *meter) {
	if (metaparams.audio_overruns > 0) {
		lv_obj_set_style_bg_color(meter, lv_color_hex(0xFF0000), LV_PART_MAIN);
		lv_obj_set_style_bg_opa(meter, LV_OPA_100, LV_PART_MAIN);

		lv_obj_set_style_text_color(meter, lv_color_white(), LV_PART_MAIN);

		lv_label_set_text(meter, "OVER");

	} else {
		lv_label_set_text_fmt(meter, "%d%%", metaparams.audio_load);
		lv_obj_set_style_text_color(meter, lv_color_hex(0xFD8B18), LV_PART_MAIN);
		lv_obj_set_style_outline_opa(meter, LV_OPA_0, LV_PART_MAIN);
		lv_obj_set_style_bg_opa(meter, LV_OPA_0, LV_PART_MAIN);
	}
	lv_show(meter);
}

} // namespace MetaModule
