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
		screen.print(patch_list.cur_patch().patch_name);
		PageWidgets::draw_jack_senses(screen, params, 180);
		PageWidgets::draw_pot_values(screen, params, Colors::black, 214);
		PageWidgets::draw_processor_stats(screen, Colors::blue, patch_list.audio_load);

		screen.setCursor(0, 40);
		for (int i = 0; i < patch_list.cur_patch().num_modules; i++) {
			screen.print(i);
			screen.print(": ");
			screen.print(patch_player.modules[i]->get_description());
			screen.print(": ");
			screen.print(patch_list.cur_patch().modules_used[i]);
			screen.print(": ");
			screen.print(patch_player.get_multiple_module_index(i));
			screen.print("\n");
		}
		screen.setTextColor(Colors::black);
		for (int i = 0; i < Panel::NumUserFacingOutJacks; i++) {
			screen.print(i);
			screen.print(": {");
			screen.print(patch_player.get_panel_output_connection(i).module_id);
			screen.print(",");
			screen.print(patch_player.get_panel_output_connection(i).jack_id);
			screen.print("}");
			screen.print("\n");
		}
		for (int i = 0; i < Panel::NumUserFacingInJacks; i++) {
			screen.print(i);
			screen.print(": {");
			screen.print(patch_player.get_panel_input_connection(i).module_id);
			screen.print(",");
			screen.print(patch_player.get_panel_input_connection(i).jack_id);
			screen.print("}");
			screen.print("\n");
		}
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
