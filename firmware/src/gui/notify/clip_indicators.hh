#pragma once
#include "CoreModules/hub/audio_expander_defs.hh"
#include "conf/screen_buffer_conf.hh"
#include "gui/helpers/lv_helpers.hh"
#include "gui/notify/clip_hold.hh"
#include "gui/slsexport/meta5/ui.h"
#include "lvgl.h"
#include "params/expanders.hh"
#include "params/params_state.hh"
#include <array>

namespace MetaModule
{

// Row of red numbered pills along the bottom of the screen, one per output that is clipping.
// They sit at the bottom of the top layer: above every page, but below notifications,
// dialogs, and anything on the sys layer (OVER, screensaver)
class ClipIndicators {
public:
	static constexpr unsigned MaxOutputs = PanelDef::NumAudioOut + AudioExpander::NumOutJacks;

private:
	static constexpr int ScreenWidth = ScreenBufferConf::viewWidth;
	static constexpr int ScreenHeight = ScreenBufferConf::viewHeight;

	// Spread across the full width of the screen
	static constexpr unsigned SlotsPerRow = 8;
	static constexpr int SlotPitch = ScreenWidth / SlotsPerRow;
	static constexpr int SlotGap = 2;
	static constexpr int SlotWidth = SlotPitch - SlotGap;
	static constexpr int SlotX0 = SlotGap / 2;

	// One row: 8 outputs. Two rows (Audio Expander): shorter pills, smaller font
	static constexpr int OneRowHeight = 16;
	static constexpr int OneRowPadTop = 1; // centers the numeral vertically
	static constexpr int TwoRowHeight = 12;
	static constexpr int RowGap = 2;

	ClipHold<MaxOutputs> hold;
	std::array<lv_obj_t *, MaxOutputs> pills{};
	unsigned num_outputs = 0;
	uint32_t lit = 0; // bit n: pill n is showing

public:
	// A pill only lights if its jack's bit (jack_senses bit order) in jack_enabled is set.
	// Pass jack_senses to show only patched outputs, ~0u to show all, 0 to show none
	void update(uint32_t mask, uint32_t now_ms, uint32_t jack_enabled) {
		if (num_outputs == 0)
			create();

		hold.update(mask, now_ms);

		uint32_t now_lit = 0;
		for (unsigned i = 0; i < num_outputs; i++) {
			bool enabled = jack_enabled & (1u << ParamsState::output_bit(i));
			if (enabled && hold.is_lit(i, now_ms))
				now_lit |= 1u << i;
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
		unsigned num_rows = two_rows ? 2 : 1;

		for (unsigned i = 0; i < num_outputs; i++) {
			int row = i / SlotsPerRow;
			int col = i % SlotsPerRow;
			// Last row sits flush with the bottom of the screen
			int y = ScreenHeight - height - int(num_rows - 1 - row) * (height + RowGap);

			auto pill = lv_label_create(lv_layer_top());
			lv_obj_move_background(pill);
			lv_obj_set_size(pill, SlotWidth, height);
			lv_obj_set_pos(pill, SlotX0 + col * SlotPitch, y);
			lv_label_set_text_fmt(pill, "%u", i + 1);
			lv_obj_set_style_text_font(pill, font, LV_PART_MAIN);
			lv_obj_set_style_text_color(pill, lv_color_hex(0xFFFFFF), LV_PART_MAIN);
			lv_obj_set_style_text_align(pill, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN);
			lv_obj_set_style_bg_color(pill, lv_color_hex(0xFF0000), LV_PART_MAIN);
			lv_obj_set_style_bg_opa(pill, LV_OPA_COVER, LV_PART_MAIN);
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
