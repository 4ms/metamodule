#pragma once
#include "delay.hh"
#include "gui/helpers/lv_helpers.hh"
#include "gui/slsexport/meta5/ui.h"
#include "gui/styles.hh"
#include "lvgl.h"
#include "metaparams.hh"
#include "patch_play/patch_playloader.hh"

namespace MetaModule
{

inline void update_audio_meter(bool is_patch_playloaded,
							   MetaParams const &metaparams,
							   PatchPlayLoader &patch_playloader,
							   ModuleDisplaySettings const &settings,
							   lv_obj_t *meter) {

	auto [cur_sr, cur_bs, _] = patch_playloader.get_audio_settings();

	if (metaparams.audio_load > 0 && is_patch_playloaded && !patch_playloader.is_audio_muted()) {
		// Playing: show load regardless of other settings
		lv_show(meter);
		if (settings.show_samplerate) {
			lv_label_set_text_fmt(meter,
								  "%s%uk/%u%c %d%%",
								  Gui::grey_color_html.data(),
								  unsigned(cur_sr / 1000u),
								  unsigned(cur_bs),
								  LV_TXT_COLOR_CMD[0],
								  metaparams.audio_load);

		} else {
			lv_label_set_text_fmt(meter, "%d%%", metaparams.audio_load);
		}

	} else if (settings.show_samplerate) {
		// Not playing, but show_samplerate is enabled: hide load but show samplerate/blocksize
		lv_show(meter);
		lv_label_set_text_fmt(meter,
							  "%s%uk/%u%c",
							  Gui::grey_color_html.data(),
							  unsigned(cur_sr / 1000u),
							  unsigned(cur_bs),
							  LV_TXT_COLOR_CMD[0]);

	} else {
		// Not playing and not showing samplerate: hide meter
		lv_hide(meter);
	}
}

inline void style_load_meter(ModuleDisplaySettings const &settings, lv_obj_t *meter, lv_obj_t *default_parent) {
	if (settings.float_loadmeter) {
		lv_obj_set_parent(meter, lv_layer_sys());
		lv_obj_move_foreground(ui_OverloadMsgLabel);
		lv_obj_set_style_bg_opa(meter, LV_OPA_80, 0);
	} else {
		lv_obj_set_parent(meter, default_parent);
		lv_obj_move_to_index(meter, 2);
		lv_obj_set_style_bg_opa(meter, LV_OPA_0, 0);
	}
}

} // namespace MetaModule
