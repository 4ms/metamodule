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

		// std::array<char, 32> txt;
		// char *p = txt.begin();

		// auto [new_p, ec] = std::to_chars(p, txt.end(), metaparams.audio_load);
		// p = new_p;

		// *p++ = '%';
		// *p++ = ' ';
		// p = std::copy(Gui::grey_color_html.begin(), Gui::grey_color_html.end(), p);

		// auto [new_p2, ec2] = std::to_chars(p, txt.end(), cur_sr / 1000);
		// p = new_p2;

		// *p++ = 'k';
		// *p++ = '/';

		// auto [new_p3, ec3] = std::to_chars(p, txt.end(), cur_bs);
		// p = new_p3;

		// *p++ = LV_TXT_COLOR_CMD[0];
		// *p++ = '\0';

		// lv_label_set_text(meter, txt.data());

		lv_label_set_text_fmt(meter,
							  "%d%% %s%uk/%u%c",
							  metaparams.audio_load,
							  Gui::grey_color_html.data(),
							  cur_sr / 1000,
							  cur_bs,
							  LV_TXT_COLOR_CMD[0]);
	} else {
		lv_label_set_text_fmt(meter, "%d%%", metaparams.audio_load);
	}
	lv_show(meter);
}

} // namespace MetaModule
