#pragma once
#include "pages/page_manager.hh"
#include "pages/page_widgets.hh"

namespace MetaModule
{

struct DebugInfoPage : DisplayPage {
	static void draw(PageManager *pm)
	{
		pm->screen.fill(pm->bgcolor);
		PageWidgets::draw_patch_name(pm, &FreeSansBold12pt7b, pm->patch_fgcolor, 2, 30);
		PageWidgets::draw_jack_senses(pm->screen, pm->params, 180);
		PageWidgets::draw_pot_values(pm->screen, pm->params, Colors::black, 214);
		PageWidgets::draw_processor_stats(pm->screen, Colors::blue, pm->patch_list.audio_load);
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
