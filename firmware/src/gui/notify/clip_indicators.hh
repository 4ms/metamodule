#pragma once
#include "CoreModules/hub/audio_expander_defs.hh"
#include "conf/panel_conf.hh"
#include "gui/helpers/lv_helpers.hh"
#include "gui/notify/clip_hold.hh"
#include "gui/slsexport/meta5/ui.h"
#include "lvgl.h"
#include "params/expanders.hh"
#include <array>

namespace MetaModule
{

// Row of red numbered pills at the top of the screen, one per output that is clipping.
// They sit at the bottom of the top layer: above every page, but below notifications,
// dialogs, and anything on the sys layer (OVER, screensaver)
class ClipIndicators {
	static constexpr unsigned MaxOutputs = PanelDef::NumAudioOut + AudioExpander::NumOutJacks;
	static constexpr unsigned SlotsPerRow = 8;
	static constexpr int SlotX0 = 4;
	static constexpr int SlotPitch = 27;
	static constexpr int SlotWidth = 23;

	ClipHold<MaxOutputs> hold;
	std::array<lv_obj_t *, MaxOutputs> pills{};
	unsigned num_outputs = 0;

public:
	void update(uint32_t mask, uint32_t now_ms, bool enabled) {
		if (num_outputs == 0)
			create();

		hold.update(mask, now_ms);

		for (unsigned i = 0; i < num_outputs; i++)
			lv_show(pills[i], enabled && hold.is_lit(i, now_ms));
	}

private:
	void create() {
		num_outputs = PanelDef::NumAudioOut;
		if (Expanders::get_connected().ext_audio_connected)
			num_outputs += AudioExpander::NumOutJacks;

		bool compact = num_outputs > SlotsPerRow;
		int height = compact ? 12 : 16;
		auto font = compact ? &ui_font_MuseoSansRounded50010 : &ui_font_MuseoSansRounded50012;

		for (unsigned i = 0; i < num_outputs; i++) {
			int row = i / SlotsPerRow;
			int col = i % SlotsPerRow;
			int y = compact ? 2 + row * 14 : 3;

			auto pill = lv_label_create(lv_layer_top());
			lv_obj_move_background(pill);
			lv_obj_set_size(pill, SlotWidth, height);
			lv_obj_set_pos(pill, SlotX0 + col * SlotPitch, y);
			lv_label_set_text_fmt(pill, "%u", i + 1);
			lv_obj_set_style_text_font(pill, font, LV_PART_MAIN);
			lv_obj_set_style_text_color(pill, lv_color_hex(0xFFFFFF), LV_PART_MAIN);
			lv_obj_set_style_text_align(pill, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN);
			lv_obj_set_style_bg_color(pill, lv_color_hex(0xFF0000), LV_PART_MAIN);
			lv_obj_set_style_bg_opa(pill, 192, LV_PART_MAIN);
			lv_obj_set_style_radius(pill, 3, LV_PART_MAIN);
			lv_obj_set_style_pad_all(pill, 0, LV_PART_MAIN);
			lv_obj_set_style_pad_top(pill, compact ? 0 : 1, LV_PART_MAIN);
			lv_obj_clear_flag(pill, LV_OBJ_FLAG_CLICKABLE | LV_OBJ_FLAG_SCROLLABLE);
			lv_hide(pill);
			pills[i] = pill;
		}
	}
};

} // namespace MetaModule
