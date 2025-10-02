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

inline void update_load_text(MetaParams const &metaparams,
							 PatchPlayLoader &patch_playloader,
							 ModuleDisplaySettings const &settings,
							 lv_obj_t *meter) {

	if (settings.show_samplerate) {
		auto [cur_sr, cur_bs, _] = patch_playloader.get_audio_settings();

		// 68% ^aaaaaa48k/64^
		lv_label_set_text_fmt(meter,
							  "%d%% %s%uk/%u%c",
							  metaparams.audio_load,
							  Gui::grey_color_html.data(),
							  unsigned(cur_sr / 1000u),
							  unsigned(cur_bs),
							  LV_TXT_COLOR_CMD[0]);
	} else {
		lv_label_set_text_fmt(meter, "%d%%", metaparams.audio_load);
	}
	lv_show(meter);
}

} // namespace MetaModule
