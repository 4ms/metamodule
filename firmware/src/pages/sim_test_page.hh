#pragma once
#include "pages/base.hh"
// #include "pages/page_widgets.hh"

namespace MetaModule
{

struct SimulationTestPage : PageBase {
	SimulationTestPage(PatchInfo info)
		: PageBase{info}
	{}

	void init() override {}

	void update() override
	{
		// screen.fill(Colors::white);
		// screen.fillRect(120, 120, 120, 120, Colors::blue);
		// screen.fillRect(10, 10, 10, 10, Colors::red);
		// screen.fillRect(20, 10, 10, 10, Colors::blue);
		// screen.fillRect(40, 10, 10, 10, Colors::green);
		// screen.fillRect(80, 10, 10, 10, Colors::green);
		// screen.fillRect(100, 10, 10, 10, Colors::blue);

		// screen.fillRect(10, 20, 101, 10, Colors::blue);
		// screen.fillRect(120, 20, 64, 16, Colors::red);
		// PageWidgets::setup_header(screen);
		// screen.print("Select a patch:");
	}
};

} // namespace MetaModule
