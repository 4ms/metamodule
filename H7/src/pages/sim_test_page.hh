#pragma once
#include "pages/base.hh"

namespace MetaModule
{

struct SimulationTestPage : PageBase {
	SimulationTestPage(PatchInfo info, ScreenFrameBuffer &screen)
		: PageBase{info, screen}
	{}

	void draw()
	{
		screen.drawPixel(50, 50, Colors::red.Rgb565());
		screen.drawPixel(150, 50, Colors::green.Rgb565());
		screen.drawPixel(50, 150, Colors::blue.Rgb565());
		// screen.fill(Colors::white);
		// screen.fillRect(120, 120, 120, 120, Colors::blue);
		// screen.fillRect(0, 0, 120, 120, Colors::red);
	}
};

} // namespace MetaModule
