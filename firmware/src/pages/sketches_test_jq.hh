#pragma once
#include "pages/base.hh"
#include "pages/gui-guider/custom.h"
#include "pages/gui-guider/gui_guider.h"

namespace MetaModule
{
struct SketchesTestPage : PageBase {
	SketchesTestPage(PatchInfo info)
		: PageBase{info}
	{
		setup_scr_symbol_sketches(ui);
		screen = ui->symbol_sketches;
		init_bg();
	}

	void init() override {}

	void update() override {}
};

struct KnobView1 : PageBase {
	KnobView1(PatchInfo info)
		: PageBase{info}
	{
		setup_scr_Knob_view(ui);
		screen = ui->Knob_view;
		// init_bg();
	}

	void init() override {}

	void update() override {}
};

struct KnobView2 : PageBase {
	KnobView2(PatchInfo info)
		: PageBase{info}
	{
		setup_scr_Knob_view2(ui);
		screen = ui->Knob_view2;
		// init_bg();
	}

	void init() override {}

	void update() override {}
};

struct KnobView3 : PageBase {
	KnobView3(PatchInfo info)
		: PageBase{info}
	{
		setup_scr_Knob_view3(ui);
		screen = ui->Knob_view3;
		// init_bg();
	}

	void init() override {}

	void update() override {}
};
} // namespace MetaModule
