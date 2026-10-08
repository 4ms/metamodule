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

	// One row: 8 outputs. Two rows (Audio Expander): shorter pills, smaller font
	static constexpr int OneRowY = 3;
	static constexpr int OneRowHeight = 16;
	static constexpr int OneRowPadTop = 1; // centers the numeral vertically
	static constexpr int TwoRowY = 2;
	static constexpr int TwoRowHeight = 12;
	static constexpr int TwoRowPitch = 14;

	ClipHold<MaxOutputs> hold;
	std::array<lv_obj_t *, MaxOutputs> pills{};
	unsigned num_outputs = 0;
	uint32_t lit = 0; // bit n: pill n is showing

public:
	void update(uint32_t mask, uint32_t now_ms, bool enabled) {
		if (num_outputs == 0)
			create();

		hold.update(mask, now_ms);

		uint32_t now_lit = 0;
		if (enabled) {
			for (unsigned i = 0; i < num_outputs; i++) {
				if (hold.is_lit(i, now_ms))
					now_lit |= 1u << i;
			}
		}

		// Showing or hiding an LVGL object invalidates it, so only touch pills whose state changed
		if (auto changed = now_lit ^ lit) {
			for (unsigned i = 0; i < num_outputs; i++) {
				if (changed & (1u << i))
					lv_show(pills[i], now_lit & (1u << i));
			}
			lit = now_lit;
		}
	}

private:
	void create() {
		num_outputs = PanelDef::NumAudioOut;
		if (Expanders::get_connected().ext_audio_connected)
			num_outputs += AudioExpander::NumOutJacks;

		bool two_rows = num_outputs > SlotsPerRow;
		int height = two_rows ? TwoRowHeight : OneRowHeight;
		auto font = two_rows ? &ui_font_MuseoSansRounded50010 : &ui_font_MuseoSansRounded50012;

		for (unsigned i = 0; i < num_outputs; i++) {
			int row = i / SlotsPerRow;
			int col = i % SlotsPerRow;
			int y = two_rows ? TwoRowY + row * TwoRowPitch : OneRowY;

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
			lv_obj_set_style_pad_top(pill, two_rows ? 0 : OneRowPadTop, LV_PART_MAIN);
			lv_obj_clear_flag(pill, LV_OBJ_FLAG_CLICKABLE | LV_OBJ_FLAG_SCROLLABLE);
			lv_hide(pill);
			pills[i] = pill;
		}
	}
};

} // namespace MetaModule
