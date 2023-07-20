#pragma once
#include "pages/base.hh"
#include "pages/fonts.hh"
#include "sys/mem_usage.hh"

namespace MetaModule
{

struct PageWidgets {
	static constexpr Color header_fg = Colors::blue.blend(Colors::black, 0.5f);

	static constexpr uint16_t header_ypos = 0;
	static constexpr uint16_t subheader_ypos = 36;
	static constexpr uint16_t list_ypos = 66;

	static constexpr Color subheader_fg = Colors::black;

	static inline const mf_font_s *header_font;
	static inline const mf_font_s *subheader_font;
	static inline const mf_font_s *list_font;

	static constexpr uint16_t list_lineheight = 20;
	static constexpr uint16_t margin_left = 2;

	PageWidgets()
	{
		header_font = mf_find_font("GillSans_Bold32");
		subheader_font = mf_find_font("GillSans_SemiBold24");
		list_font = mf_find_font("GillSans18");
	}

	static void setup_header(ScreenFrameBuffer &screen)
	{
		screen.setFont(header_font);
		screen.setTextColor(header_fg);
		screen.setAlignment(ScreenFrameBuffer::Left);
		screen.setCursor(2, header_ypos);
		screen.setTextWrap(false);
	}

	static void setup_sub_header(ScreenFrameBuffer &screen)
	{
		screen.setFont(subheader_font);
		screen.setTextColor(subheader_fg);
		screen.setAlignment(ScreenFrameBuffer::Left);
		screen.setCursor(2, subheader_ypos);
		screen.setTextWrap(false);
	}

	static void draw_processor_stats(ScreenFrameBuffer &screen, Color color, uint8_t audio_load)
	{
		screen.setTextColor(color.Rgb565());
		screen.setFont(&mf_rlefont_fixed_10x20.font);
		screen.printf_at(200, 223, "%d\%", audio_load);
		screen.setFont(&mf_rlefont_fixed_7x14.font);
		screen.printf_at(120, 226, "%dkb", get_heap_size() / 1024);
		screen.printf_at(160, 226, "%dkb", BigAllocControl::get_memory_usage() / 1024);
	}

	static void print_module_name(ScreenFrameBuffer &screen, PatchPlayer &patch_player, uint32_t module_id)
	{
		screen.print(patch_player.modules[module_id]->get_description());
		auto dup_id = patch_player.get_multiple_module_index(module_id);
		if (dup_id) {
			screen.printf(" #%d", dup_id);
		}
	}

	static void get_module_name(PatchPlayer &patch_player, uint32_t module_id, char *module_name)
	{
		auto dup_id = patch_player.get_multiple_module_index(module_id);
		if (dup_id)
			snprintf(module_name, 255, "%s #%d", patch_player.modules[module_id]->get_description().cstr(), dup_id);
		else
			snprintf(module_name, 255, "%s", patch_player.modules[module_id]->get_description().cstr());
		// module_name = patch_player.modules[module_id]->get_description().cstr();
	}

	static void draw_pot_values(ScreenFrameBuffer &screen, Params &params, Color color, int16_t y_pos = 210)
	{
		screen.setTextColor(color.Rgb565());
		screen.setFont(&mf_rlefont_fixed_7x14.font);
		int y = y_pos;
		const int box_height = 15;
		const int box_width = 30;
		for (unsigned i = 0; i < PanelDef::NumCVIn + PanelDef::NumKnobs; i++) {
			screen.setCursor((i & 0b111) * box_width + 3, y);
			if (i >= PanelDef::NumKnobs)
				screen.print((int16_t)(params.cvjacks[i - PanelDef::NumKnobs] * 100));
			else
				screen.print((int16_t)(params.knobs[i] * 100));
			if (i == 7)
				y += box_height;
		}
	}

	// Todo: pass these as params: text_color, unpat_rect_color, pat_rect_color, notworking_rect_color, alpha
	static void draw_jack_senses(ScreenFrameBuffer &screen, Params &params, uint16_t y_pos = 175)
	{
		const Color text_color = Colors::white;
		const Color unpatched_rect_color = Colors::grey;
		const Color patched_rect_color = Colors::yellow;
		const Color notworking_rect_color = Colors::black;
		const float box_alpha = 0.85f;

		screen.setTextColor(text_color.Rgb565());
		screen.setFont(&mf_rlefont_fixed_7x14.font);

		const uint16_t yoffset = y_pos;
		const uint16_t box_height = 16;

		if constexpr (PanelDef::PanelID == 0) {
			const uint16_t boxes_per_row = 8;
			const uint16_t box_width = MMScreenBufferConf::viewWidth / boxes_per_row;
			const unsigned pin_order[PanelDef::NumJacks] = {0, 1, 2, 3, 6, 7, 8, 9, 10, 11, 12, 13, 4, 5, 14};
			for (unsigned i = 0; i < PanelDef::NumJacks; i++) {
				auto pin = pin_order[i];
				bool plugged = params.jack_senses & (1 << pin);
				bool works = (pin != 4 && pin != 5 && pin != 8 && pin != 9 && pin != 13);
				uint16_t xpos = (i & 0b0111) * box_width;
				uint16_t ypos = i >= boxes_per_row ? yoffset + box_height : yoffset;
				auto color = works ? (plugged ? patched_rect_color : unpatched_rect_color) : notworking_rect_color;
				screen.blendRect(xpos, ypos, box_width, box_height, color.Rgb565(), box_alpha);
				screen.setCursor(xpos + 3, ypos);
				screen.print(PanelDef::ShortJackNames[i]);
			}
		} else if constexpr (PanelDef::PanelID == 1) {
			const uint16_t boxes_per_row = 10;
			const uint16_t box_width = MMScreenBufferConf::viewWidth / boxes_per_row;
			uint16_t xpos = 0;
			uint16_t ypos = yoffset;
			for (unsigned i = 0; i < PanelDef::NumJacks; i++) {
				auto pin = i; //pin_order[i];
				bool plugged = params.jack_senses & (1 << pin);
				auto color = plugged ? patched_rect_color : unpatched_rect_color;
				screen.blendRect(xpos, ypos, box_width, box_height, color.Rgb565(), box_alpha);
				screen.setCursor(xpos + 3, ypos);
				screen.print(PanelDef::ShortJackNames[i]);

				xpos += box_width;
				if (i == boxes_per_row - 1) {
					xpos = 0;
					ypos += box_height;
				}
			}
		}
	}
};

} // namespace MetaModule
