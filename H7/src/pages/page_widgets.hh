#pragma once
#include "pages/base.hh"
#include "sys/mem_usage.hh"

namespace MetaModule
{

struct PageWidgets {
	static constexpr Color header_fg = Colors::blue.blend(Colors::black, 0.5f);
	static constexpr uint16_t header_ypos = 30;
	static constexpr Color subheader_fg = Colors::black;
	static constexpr uint16_t subheader_ypos = 56;

	static void setup_header(ScreenFrameBuffer &screen)
	{
		screen.setFont(&FreeSansBold18pt7b);
		screen.setTextColor(header_fg);
		screen.setTextSize(1);
		screen.setCursor(2, header_ypos);
		screen.setTextWrap(false);
	}

	static void setup_sub_header(ScreenFrameBuffer &screen)
	{
		screen.setFont(&FreeSansBold12pt7b);
		screen.setTextColor(subheader_fg);
		screen.setTextSize(1);
		screen.setCursor(2, subheader_ypos);
		screen.setTextWrap(false);
	}

	static void draw_processor_stats(ScreenFrameBuffer &screen, Color color, uint8_t audio_load)
	{
		screen.setTextColor(color.Rgb565());
		screen.setTextSize(2);
		screen.setFont(NULL);
		screen.setCursor(200, 225);
		screen.print(audio_load, 10);
		screen.print("% ");
		screen.setTextSize(1);
		screen.setCursor(160, 224);
		screen.print(get_heap_size() / 1024, 10);
		screen.print("kb ");
		screen.setCursor(160, 232);
		screen.print(BigAlloc<PageWidgets>::get_memory_usage() / 1024, 10);
		screen.print("kb   ");
	}

	static void print_module_name(ScreenFrameBuffer &screen, PatchPlayer &patch_player, uint32_t module_id)
	{
		screen.print(patch_player.modules[module_id]->get_description());
		auto dup_id = patch_player.get_multiple_module_index(module_id);
		if (dup_id) {
			screen.print(" #");
			screen.print(dup_id);
		}
	}

	static void draw_pot_values(ScreenFrameBuffer &screen, Params &params, Color color, int16_t y_pos = 214)
	{
		screen.setTextColor(color.Rgb565());
		screen.setTextSize(1);
		screen.setFont(NULL);
		int y = y_pos;
		const int box_height = 15;
		const int box_width = 30;
		for (int i = 0; i < 12; i++) {
			screen.setCursor((i & 0b111) * box_width + 3, y);
			if (i >= 8)
				screen.print((int16_t)(params.cvjacks[i - 8] * 100));
			else
				screen.print((int16_t)(params.knobs[i] * 100));
			screen.print(" ");
			if (i == 7)
				y += box_height;
		}
	}

	// Todo: pass these as params: text_color, unpat_rect_color, pat_rect_color, notworking_rect_color, alpha
	static void draw_jack_senses(ScreenFrameBuffer &screen, Params &params, uint16_t y_pos = 180)
	{
		const Color text_color = Colors::white;
		const Color unpatched_rect_color = Colors::grey;
		const Color patched_rect_color = Colors::yellow;
		const Color notworking_rect_color = Colors::black;
		const float box_alpha = 0.85f;

		screen.setTextColor(text_color.Rgb565());
		screen.setTextSize(1);
		screen.setFont(NULL);

		const uint16_t yoffset = y_pos;
		const uint16_t box_height = 15;
		const uint16_t box_width = 240 / 8;

		const unsigned pin_order[15] = {0, 1, 2, 3, 6, 7, 8, 9, 10, 11, 12, 13, 4, 5, 14};
		const char names[15][5] = {"CVA",
								   "CVB",
								   "CVC",
								   "CVD",
								   "Lin",
								   "Rin",
								   "Lout",
								   "Rout",
								   "Gt1",
								   "Gt2",
								   "CkIn",
								   "CkO",
								   "CVO1",
								   "CVO2",
								   "Pat"};
		for (unsigned i = 0; i < 15; i++) {
			auto pin = pin_order[i];
			bool plugged = params.jack_senses & (1 << pin);
			bool works = (pin != 4 && pin != 5 && pin != 8 && pin != 9 && pin != 13);
			uint16_t xpos = (i & 0b0111) * box_width;
			uint16_t ypos = i > 7 ? yoffset + box_height : yoffset;
			auto color = works ? (plugged ? patched_rect_color : unpatched_rect_color) : notworking_rect_color;
			screen.blendRect(xpos, ypos, box_width, box_height, color.Rgb565(), box_alpha);
			screen.setCursor(xpos + 3, ypos + 4);
			screen.print(names[i]);
		}
	}
};

} // namespace MetaModule
