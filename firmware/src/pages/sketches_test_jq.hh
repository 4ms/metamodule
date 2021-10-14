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
	lv_group_t *group;
	lv_style_t style_highlight;

	SMRTestPage(PatchInfo info)
		: PageBase{info}
	{}

	void init() override
	{
		setup_scr_module_test_small(ui);
		screen = ui->module_test_small;
		init_bg();

		lv_style_init(&style_highlight);

		//Write style state: LV_STATE_DEFAULT for style_module_test_small_btn_1_main
		lv_style_set_radius(&style_highlight, LV_STATE_DEFAULT, 80);
		// lv_style_set_bg_color(&style_highlight, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
		// lv_style_set_bg_grad_color(&style_highlight, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
		// lv_style_set_bg_grad_dir(&style_highlight, LV_STATE_DEFAULT, LV_GRAD_DIR_VER);
		lv_style_set_bg_opa(&style_highlight, LV_STATE_DEFAULT, 0);
		lv_style_set_border_color(&style_highlight, LV_STATE_DEFAULT, lv_color_make(0xff, 0xc3, 0x70));
		lv_style_set_border_width(&style_highlight, LV_STATE_DEFAULT, 2);
		lv_style_set_border_opa(&style_highlight, LV_STATE_DEFAULT, 0);
		lv_style_set_outline_color(&style_highlight, LV_STATE_DEFAULT, lv_color_make(0xff, 0xc3, 0x70));
		lv_style_set_outline_opa(&style_highlight, LV_STATE_DEFAULT, 0);

		group = lv_group_create();
		lv_indev_set_group(lv_indev_get_next(nullptr), group);
		lv_group_add_obj(group, ui->module_test_small_btn_1);
		lv_group_add_obj(group, ui->module_test_small_btn_2);
		lv_group_add_obj(group, ui->module_test_small_btn_3);
		lv_group_add_obj(group, ui->module_test_small_btn_4);
		lv_group_add_obj(group, ui->module_test_small_btn_5);
		lv_group_add_obj(group, ui->module_test_small_btn_6);
		lv_group_add_obj(group, ui->module_test_small_btn_7);
		lv_group_add_obj(group, ui->module_test_small_btn_8);
		lv_group_add_obj(group, ui->module_test_small_btn_9);
		lv_group_add_obj(group, ui->module_test_small_btn_10);
		lv_group_add_obj(group, ui->module_test_small_btn_11);
		lv_group_add_obj(group, ui->module_test_small_btn_12);
		lv_group_add_obj(group, ui->module_test_small_btn_13);
		lv_group_add_obj(group, ui->module_test_small_btn_14);
		lv_group_add_obj(group, ui->module_test_small_btn_15);
		lv_group_add_obj(group, ui->module_test_small_btn_16);
		lv_group_add_obj(group, ui->module_test_small_btn_17);
		lv_group_add_obj(group, ui->module_test_small_btn_18);
		lv_group_add_obj(group, ui->module_test_small_btn_19);
		lv_group_add_obj(group, ui->module_test_small_btn_20);
		lv_group_add_obj(group, ui->module_test_small_btn_21);
		lv_group_add_obj(group, ui->module_test_small_btn_22);
		lv_group_add_obj(group, ui->module_test_small_btn_23);
		lv_group_add_obj(group, ui->module_test_small_btn_24);
		lv_group_add_obj(group, ui->module_test_small_btn_25);
		lv_group_add_obj(group, ui->module_test_small_btn_26);
		lv_group_add_obj(group, ui->module_test_small_btn_27);
		lv_group_add_obj(group, ui->module_test_small_btn_28);
		lv_group_add_obj(group, ui->module_test_small_btn_29);
		lv_group_add_obj(group, ui->module_test_small_btn_30);
		lv_group_add_obj(group, ui->module_test_small_btn_31);
		lv_group_add_obj(group, ui->module_test_small_btn_32);
		lv_group_add_obj(group, ui->module_test_small_btn_33);
		lv_group_add_obj(group, ui->module_test_small_btn_34);
		lv_group_add_obj(group, ui->module_test_small_btn_35);
		lv_group_add_obj(group, ui->module_test_small_btn_36);
		lv_group_add_obj(group, ui->module_test_small_btn_37);
		lv_group_add_obj(group, ui->module_test_small_btn_38);
		lv_group_add_obj(group, ui->module_test_small_btn_39);
		lv_group_add_obj(group, ui->module_test_small_btn_40);
		lv_group_add_obj(group, ui->module_test_small_btn_41);
		lv_group_add_obj(group, ui->module_test_small_btn_42);
		lv_group_add_obj(group, ui->module_test_small_btn_43);
		lv_group_add_obj(group, ui->module_test_small_btn_44);
		lv_group_add_obj(group, ui->module_test_small_btn_45);
		lv_group_add_obj(group, ui->module_test_small_btn_46);
		lv_group_add_obj(group, ui->module_test_small_btn_47);
		lv_group_add_obj(group, ui->module_test_small_btn_48);
		lv_group_add_obj(group, ui->module_test_small_btn_49);
		lv_group_add_obj(group, ui->module_test_small_btn_50);
		lv_group_add_obj(group, ui->module_test_small_btn_51);
		lv_group_add_obj(group, ui->module_test_small_btn_52);
	}

	void update() override {}
};

struct GroupArcSketchesPage1 : PageBase {
	GroupArcSketchesPage1(PatchInfo info)
		: PageBase{info}
	{}

	void init() override
	{
		setup_scr_group_arc_sketches(ui);
		screen = ui->group_arc_sketches;
		init_bg();
		lv_arc_set_adjustable(ui->group_arc_sketches_arc_1, true);
		lv_arc_set_adjustable(ui->group_arc_sketches_arc_2, true);
		lv_arc_set_adjustable(ui->group_arc_sketches_arc_3, true);
		lv_arc_set_adjustable(ui->group_arc_sketches_arc_4, true);
		lv_arc_set_adjustable(ui->group_arc_sketches_arc_5, true); //crashes!
		lv_arc_set_adjustable(ui->group_arc_sketches_arc_6, true);
		lv_arc_set_adjustable(ui->group_arc_sketches_arc_7, true);
		lv_arc_set_adjustable(ui->group_arc_sketches_arc_8, true);
		lv_arc_set_adjustable(ui->group_arc_sketches_arc_9, true);
		lv_arc_set_adjustable(ui->group_arc_sketches_arc_10, true);
		lv_arc_set_adjustable(ui->group_arc_sketches_arc_11, true);
		lv_arc_set_adjustable(ui->group_arc_sketches_arc_12, true);
	}

	void update() override
	{
		lv_arc_set_value(ui->group_arc_sketches_arc_1, params.knobs[0] * 100.f);
		lv_arc_set_value(ui->group_arc_sketches_arc_2, params.knobs[1] * 100.f);
		lv_arc_set_value(ui->group_arc_sketches_arc_3, params.knobs[2] * 100.f);
		lv_arc_set_value(ui->group_arc_sketches_arc_4, params.knobs[3] * 100.f);
		lv_arc_set_value(ui->group_arc_sketches_arc_5, params.knobs[4] * 100.f);
		lv_arc_set_value(ui->group_arc_sketches_arc_6, params.knobs[5] * 100.f);
		lv_arc_set_value(ui->group_arc_sketches_arc_7, params.knobs[6] * 100.f);
		lv_arc_set_value(ui->group_arc_sketches_arc_8, params.knobs[7] * 100.f);
		lv_arc_set_value(ui->group_arc_sketches_arc_9, params.knobs[8] * 100.f);
		lv_arc_set_value(ui->group_arc_sketches_arc_10, params.knobs[9] * 100.f);
		lv_arc_set_value(ui->group_arc_sketches_arc_11, params.knobs[10] * 100.f);
		lv_arc_set_value(ui->group_arc_sketches_arc_12, params.knobs[11] * 100.f);
	}
};

struct GroupArcSketchesPage2 : PageBase {
	GroupArcSketchesPage2(PatchInfo info)
		: PageBase{info}
	{}

	void init() override
	{
		setup_scr_group_arc_sketches2(ui);
		screen = ui->group_arc_sketches2;
		init_bg();
	}

	void update() override
	{
		lv_arc_set_value(ui->group_arc_sketches2_arc_1, params.knobs[0] * 100.f);
		lv_arc_set_value(ui->group_arc_sketches2_arc_2, params.knobs[1] * 100.f);
		lv_arc_set_value(ui->group_arc_sketches2_arc_3, params.knobs[2] * 100.f);
		lv_arc_set_value(ui->group_arc_sketches2_arc_4, params.knobs[3] * 100.f);
		lv_arc_set_value(ui->group_arc_sketches2_arc_5, params.knobs[4] * 100.f);
		lv_arc_set_value(ui->group_arc_sketches2_arc_6, params.knobs[5] * 100.f);
	}
};

struct GroupArcSketchesPage3 : PageBase {
	GroupArcSketchesPage3(PatchInfo info)
		: PageBase{info}
	{}

	void init() override
	{
		setup_scr_group_arc_sketches3(ui);
		screen = ui->group_arc_sketches3;
		init_bg();
	}

	void update() override
	{
		lv_arc_set_value(ui->group_arc_sketches3_arc_1, params.knobs[0] * 100.f);
		lv_arc_set_value(ui->group_arc_sketches3_arc_2, params.knobs[1] * 100.f);
		lv_arc_set_value(ui->group_arc_sketches3_arc_3, params.knobs[2] * 100.f);
		lv_arc_set_value(ui->group_arc_sketches3_arc_4, params.knobs[3] * 100.f);
		lv_arc_set_value(ui->group_arc_sketches3_arc_5, params.knobs[4] * 100.f);
		lv_arc_set_value(ui->group_arc_sketches3_arc_6, params.knobs[5] * 100.f);
		lv_arc_set_value(ui->group_arc_sketches3_arc_7, params.knobs[6] * 100.f);
		lv_arc_set_value(ui->group_arc_sketches3_arc_8, params.knobs[7] * 100.f);
		lv_arc_set_value(ui->group_arc_sketches3_arc_9, params.knobs[8] * 100.f);
		lv_arc_set_value(ui->group_arc_sketches3_arc_10, params.knobs[9] * 100.f);
		lv_arc_set_value(ui->group_arc_sketches3_arc_11, params.knobs[10] * 100.f);
		lv_arc_set_value(ui->group_arc_sketches3_arc_12, params.knobs[11] * 100.f);
	}
};

struct GroupArcSketchesPage4 : PageBase {
	GroupArcSketchesPage4(PatchInfo info)
		: PageBase{info}
	{}

	void init() override
	{
		setup_scr_group_arc_sketches4(ui);
		screen = ui->group_arc_sketches4;
		init_bg();
	}

	void update() override
	{
		// lv_arc_set_value(ui->group_arc_sketches4_arc_1, params.knobs[0] * 100.f);
		// lv_arc_set_value(ui->group_arc_sketches4_arc_2, params.knobs[1] * 100.f);
		// lv_arc_set_value(ui->group_arc_sketches4_arc_3, params.knobs[2] * 100.f);
		// lv_arc_set_value(ui->group_arc_sketches4_arc_4, params.knobs[3] * 100.f);
		// lv_arc_set_value(ui->group_arc_sketches4_arc_5, params.knobs[4] * 100.f);
		// lv_arc_set_value(ui->group_arc_sketches4_arc_6, params.knobs[5] * 100.f);
		// lv_arc_set_value(ui->group_arc_sketches4_arc_8, params.knobs[7] * 100.f);
		// lv_arc_set_value(ui->group_arc_sketches4_arc_9, params.knobs[8] * 100.f);
		// lv_arc_set_value(ui->group_arc_sketches4_arc_10, params.knobs[9] * 100.f);
		// lv_arc_set_value(ui->group_arc_sketches4_arc_11, params.knobs[10] * 100.f);
		// lv_arc_set_value(ui->group_arc_sketches4_arc_12, params.knobs[11] * 100.f);
	}
};

} // namespace MetaModule
