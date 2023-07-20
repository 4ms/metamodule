#pragma once
#include "pages/base.hh"
#include "pages/page_widgets.hh"

namespace MetaModule
{

struct DebugInfoPage : PageBase {
	DebugInfoPage(PatchInfo info, ScreenFrameBuffer &screen)
		: PageBase{info, screen}
	{}

	void draw()
	{
		screen.fill(Colors::pink);
		PageWidgets::setup_header(screen);
		screen.print(patch_player.get_patch_name());
		PageWidgets::draw_jack_senses(screen, params, 180);
		PageWidgets::draw_pot_values(screen, params, Colors::black, 214);
		PageWidgets::draw_processor_stats(screen, Colors::blue, metaparams.audio_load);

		screen.setFont(mf_find_font("fixed_5x8"));
		uint16_t y_pos = 40;
		for (int i = 0; i < patch_player.get_num_modules(); i++) {
			screen.setCursor(0, y_pos);
			screen.printf("%d: %s (%s) #%d",
						  i,
						  patch_player.modules[i]->get_description().cstr(),
						  patch_player.get_module_name(i).cstr(),
						  patch_player.get_multiple_module_index(i));
			y_pos += 10;
		}
		screen.setTextColor(Colors::black);
		for (int i = 0; i < PanelDef::NumUserFacingOutJacks; i++) {
			screen.setCursor(0, y_pos);
			screen.printf("OUT %d: {%d, %d}",
						  i,
						  patch_player.get_panel_output_connection(i).module_id,
						  patch_player.get_panel_output_connection(i).jack_id);
			y_pos += 8;
		}
		y_pos = 40;
		for (int i = 0; i < PanelDef::NumUserFacingInJacks; i++) {
			screen.setCursor(160, y_pos);
			screen.printf("IN %d: {%d, %d}",
						  i,
						  patch_player.get_panel_input_connection(i).module_id,
						  patch_player.get_panel_input_connection(i).jack_id);
			y_pos += 10;
		}
	}

	static void test_justification(ScreenFrameBuffer &screen)
	{
		// Test justifications
		screen.setFont(PageWidgets::list_font);
		screen.setTextColor(Colors::grey);
		screen.setCursor(0, 60);
		screen.setAlignment(ScreenFrameBuffer::Left);
		screen.print("Left Justified.");
		screen.print("More");

		screen.setTextColor(Colors::red);
		screen.setCursor(239, 90);
		screen.setAlignment(ScreenFrameBuffer::Right);
		screen.print("Right Justified.");
		screen.print("More");

		screen.setTextColor(Colors::green.blend(Colors::black, 0.25f));
		screen.setCursor(120, 120);
		screen.setAlignment(ScreenFrameBuffer::Center);
		screen.print("Center Justified.");
		screen.print("More");
	}

	static void draw_test_squares(ScreenFrameBuffer &screen)
	{
		// Should see a 1-pixel border around the 4-square, and a 1-pixel gap between squares
		screen.fillRect(0, 0, 44, 44, Colors::purple.Rgb565());
		screen.fillRect(1, 1, 20, 20, Colors::red.Rgb565());
		screen.fillRect(1, 23, 20, 20, Colors::green.Rgb565());
		screen.fillRect(23, 1, 20, 20, Colors::orange.Rgb565());
		screen.fillRect(23, 23, 20, 20, Colors::grey.Rgb565());

		screen.fillRect(196, 196, 44, 44, Colors::white.Rgb565());
		screen.fillRect(219, 219, 20, 20, Colors::yellow.Rgb565());
		screen.fillRect(197, 219, 20, 20, Colors::purple.Rgb565());
		screen.fillRect(197, 197, 20, 20, Colors::pink.Rgb565());
		screen.fillRect(219, 197, 20, 20, Colors::cyan.Rgb565());
	}
};

} // namespace MetaModule
