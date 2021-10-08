#pragma once
#include "pages/base.hh"
#include "pages/gui-guider/custom.h"
#include "pages/gui-guider/gui_guider.h"

namespace MetaModule
{
// Todo: this should display User-set names for jacks:
// Instead of "Drum#3:Out", should be "Kick Out"
struct ArcTestJQPage : PageBase {
	lv_ui base_ui, *ui;
	bool is_init = false;

	ArcTestJQPage(PatchInfo info)
		: PageBase{info}
	{
		ui = &base_ui;
	}

	void init()
	{
		setup_scr_Main_Example(ui);
		custom_init(ui);

		//Added by DG:
		// lv_arc_set_adjustable(ui->Main_Example_arc_1, true);
		// lv_arc_set_adjustable(ui->Main_Example_arc_2, true);
		// lv_arc_set_adjustable(ui->Main_Example_arc_3, true);
		// lv_arc_set_adjustable(ui->Main_Example_arc_4, true);
		// lv_arc_set_adjustable(ui->Main_Example_arc_5, true);
		// lv_arc_set_adjustable(ui->Main_Example_arc_6, true);

		is_init = true;
	}

	void focus(PageChangeDirection dir)
	{
		if (!is_init)
			init();

		auto animation_style = dir == PageChangeDirection::Back	   ? LV_SCR_LOAD_ANIM_MOVE_LEFT :
							   dir == PageChangeDirection::Forward ? LV_SCR_LOAD_ANIM_MOVE_RIGHT :
																	   LV_SCR_LOAD_ANIM_FADE_ON;
		lv_scr_load_anim(ui->Main_Example, animation_style, 500, 0, false);
	}

	void blur() {}

	void update()
	{
		// lv_arc_set_value(ui->Main_Example_arc_1, params.knobs[0] * 100.f);
		// lv_arc_set_value(ui->Main_Example_arc_2, params.knobs[1] * 100.f);
		// lv_arc_set_value(ui->Main_Example_arc_3, params.knobs[2] * 100.f);
		// lv_arc_set_value(ui->Main_Example_arc_4, params.knobs[3] * 100.f);
		// lv_arc_set_value(ui->Main_Example_arc_5, params.knobs[4] * 100.f);
		// lv_arc_set_value(ui->Main_Example_arc_6, params.knobs[5] * 100.f);
	}
};
} // namespace MetaModule
