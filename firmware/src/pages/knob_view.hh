#pragma once
#include "pages/base.hh"
#include "pages/gui-guider/custom.h"
#include "pages/gui-guider/gui_guider.h"

namespace MetaModule
{
struct KnobView3 : PageBase {
	KnobView3(PatchInfo info)
		: PageBase{info}
	{}

	void init() override
	{
		setup_scr_Knob_view3(ui);
		screen = ui->Knob_view3;
		init_bg();

		lv_arc_set_adjustable(ui->Knob_view3_arc_1, true);
		lv_arc_set_adjustable(ui->Knob_view3_arc_2, true);
		lv_arc_set_adjustable(ui->Knob_view3_arc_3, true);
		lv_arc_set_adjustable(ui->Knob_view3_arc_4, true);
		lv_arc_set_adjustable(ui->Knob_view3_arc_5, true);
		lv_arc_set_adjustable(ui->Knob_view3_arc_6, true);
		lv_arc_set_adjustable(ui->Knob_view3_arc_7, true);
		lv_arc_set_adjustable(ui->Knob_view3_arc_8, true);
		lv_arc_set_adjustable(ui->Knob_view3_arc_9, true);
		lv_arc_set_adjustable(ui->Knob_view3_arc_10, true);
		lv_arc_set_adjustable(ui->Knob_view3_arc_11, true);
		lv_arc_set_adjustable(ui->Knob_view3_arc_12, true);
	}

	void update() override
	{

		//2 6 5
		//3 1 4
		lv_arc_set_value(ui->Knob_view3_arc_2, params.knobs[0] * 100.f);
		lv_arc_set_value(ui->Knob_view3_arc_3, params.knobs[1] * 100.f);
		lv_arc_set_value(ui->Knob_view3_arc_6, params.knobs[2] * 100.f);
		lv_arc_set_value(ui->Knob_view3_arc_1, params.knobs[3] * 100.f);
		lv_arc_set_value(ui->Knob_view3_arc_5, params.knobs[4] * 100.f);
		lv_arc_set_value(ui->Knob_view3_arc_4, params.knobs[5] * 100.f);

		//7 11 8 9 10 12
		//7 12 8 11 9 10
		//7 12 8 9 10 11
		lv_arc_set_value(ui->Knob_view3_arc_7, params.knobs[6] * 100.f);
		lv_arc_set_value(ui->Knob_view3_arc_12, params.knobs[7] * 100.f);
		lv_arc_set_value(ui->Knob_view3_arc_8, params.knobs[8] * 100.f);
		lv_arc_set_value(ui->Knob_view3_arc_10, params.knobs[9] * 100.f); //PotL
		lv_arc_set_value(ui->Knob_view3_arc_11, params.knobs[10] * 100.f);
		lv_arc_set_value(ui->Knob_view3_arc_9, params.knobs[11] * 100.f); //PotQ
	}
};
} // namespace MetaModule
