#pragma once
#include "delay.hh"
#include "gui/helpers/lv_helpers.hh"
#include "gui/slsexport/meta5/ui.h"
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
		lv_label_set_text_fmt(meter, "%d%% %uk/%u", metaparams.audio_load, cur_sr / 1000, cur_bs);
	} else {
		lv_label_set_text_fmt(meter, "%d%%", metaparams.audio_load);
	}
	lv_show(meter);
}

} // namespace MetaModule
