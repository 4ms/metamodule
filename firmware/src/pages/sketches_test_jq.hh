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
		init_bg();
	}

	void update() override {}
};

struct AudioCVInsPage : PageBase {
	AudioCVInsPage(PatchInfo info)
		: PageBase{info}
	{}

	void init() override
	{
		setup_scr_AudioCV_Ins(ui);
		screen = ui->AudioCV_Ins;
		init_bg();
	}

	void update() override {}
};

struct SMRTestPage : PageBase {
	SMRTestPage(PatchInfo info)
		: PageBase{info}
	{}

	void init() override
	{
		setup_scr_module_test_small(ui);
		screen = ui->module_test_small;
		init_bg();
	}

	void update() override {}
};
struct SMRTestLargePage : PageBase {
	SMRTestLargePage(PatchInfo info)
		: PageBase{info}
	{}

	void init() override
	{
		setup_scr_module_test_large(ui);
		screen = ui->module_test_large;
		init_bg();
	}

	void update() override {}
};

} // namespace MetaModule
