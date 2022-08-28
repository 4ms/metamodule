#pragma once
#include "pages/base.hh"
#include "pages/gui-guider/custom.h"
#include "pages/gui-guider/gui_guider.h"

namespace MetaModule
{
struct ArcTestJQPage : PageBase {
	ArcTestJQPage(PatchInfo info)
		: PageBase{info}
	{}

	void init() override
	{
		setup_scr_Main_Example(ui);
		init_bg(ui->Main_Example);

		lv_arc_set_adjustable(ui->Main_Example_arc_1, true);
		lv_arc_set_adjustable(ui->Main_Example_arc_2, true);
		lv_arc_set_adjustable(ui->Main_Example_arc_3, true);
		lv_arc_set_adjustable(ui->Main_Example_arc_4, true);
		lv_arc_set_adjustable(ui->Main_Example_arc_5, true);
		lv_arc_set_adjustable(ui->Main_Example_arc_6, true);
	}

	void update() override
	{
		// 2 3 6
		// 1 5 4
		lv_arc_set_value(ui->Main_Example_arc_2, params.knobs[0] * 100.f);
		lv_arc_set_value(ui->Main_Example_arc_3, params.knobs[1] * 100.f);
		lv_arc_set_value(ui->Main_Example_arc_6, params.knobs[2] * 100.f);
		lv_arc_set_value(ui->Main_Example_arc_1, params.knobs[3] * 100.f);
		lv_arc_set_value(ui->Main_Example_arc_5, params.knobs[4] * 100.f);
		lv_arc_set_value(ui->Main_Example_arc_4, params.knobs[5] * 100.f);
	}
};
} // namespace MetaModule
