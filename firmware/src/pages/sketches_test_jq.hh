#pragma once
#include "pages/base.hh"
#include "pages/gui-guider/custom.h"
#include "pages/gui-guider/gui_guider.h"

namespace MetaModule
{
struct SketchesTestPage : PageBase {
	SketchesTestPage(PatchInfo info)
		: PageBase{info}
	{}

	void init() override
	{
		setup_scr_symbol_sketches(ui);
		screen = ui->symbol_sketches;
		//init_bg();
	}

	void update() override {}
};
} // namespace MetaModule
