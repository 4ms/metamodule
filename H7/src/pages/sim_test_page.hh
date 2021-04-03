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
		// screen.fill(Colors::white);
		// screen.fillRect(120, 120, 120, 120, Colors::blue);
		screen.fillRect(0, 0, 120, 120, Colors::red);
	}
};

} // namespace MetaModule
