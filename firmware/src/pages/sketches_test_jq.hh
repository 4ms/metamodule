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
	lv_style_t style_highlight;

	SMRTestPage(PatchInfo info)
		: PageBase{info}
	{}

	void init() override
	{
		//17ms with styles removed. Presumably 24ms with them in
		setup_scr_module_test_small(ui);
		screen = ui->module_test_small;
		init_bg();

		lv_style_init(&style_highlight);

		lv_style_set_radius(&style_highlight, LV_STATE_DEFAULT, 80);
		lv_style_set_bg_opa(&style_highlight, LV_STATE_DEFAULT, 0);
		lv_style_set_border_color(&style_highlight, LV_STATE_DEFAULT, lv_color_make(0xff, 0xc3, 0x70));
		lv_style_set_border_width(&style_highlight, LV_STATE_DEFAULT, 2);
		lv_style_set_border_opa(&style_highlight, LV_STATE_DEFAULT, 0);
		lv_style_set_outline_color(&style_highlight, LV_STATE_DEFAULT, lv_color_make(0xff, 0xc3, 0x70));
		lv_style_set_outline_opa(&style_highlight, LV_STATE_DEFAULT, 0);

		group = lv_group_create();

		lv_group_add_obj(group, ui->module_test_small_param_list);
		lv_group_add_obj(group, ui->module_test_small_freq_nudge1);
		lv_group_add_obj(group, ui->module_test_small_freq_cv1);
		lv_group_add_obj(group, ui->module_test_small_lock1);
		lv_group_add_obj(group, ui->module_test_small_freq_switch1);
		lv_group_add_obj(group, ui->module_test_small_button_lock1);
		lv_group_add_obj(group, ui->module_test_small_button_lock2);
		lv_group_add_obj(group, ui->module_test_small_button_lock3);
		lv_group_add_obj(group, ui->module_test_small_button_lock4);
		lv_group_add_obj(group, ui->module_test_small_button_lock5);
		lv_group_add_obj(group, ui->module_test_small_button_lock6);
		lv_group_add_obj(group, ui->module_test_small_freq_nudge2);
		lv_group_add_obj(group, ui->module_test_small_freq_cv2);
		lv_group_add_obj(group, ui->module_test_small_lock2);
		lv_group_add_obj(group, ui->module_test_small_freq_switch2);
		lv_group_add_obj(group, ui->module_test_small_slider1);
		lv_group_add_obj(group, ui->module_test_small_slider2);
		lv_group_add_obj(group, ui->module_test_small_slider3);
		lv_group_add_obj(group, ui->module_test_small_slider4);
		lv_group_add_obj(group, ui->module_test_small_slider5);
		lv_group_add_obj(group, ui->module_test_small_slider6);
		lv_group_add_obj(group, ui->module_test_small_switch_cv_slew);
		lv_group_add_obj(group, ui->module_test_small_lvl_cv1);
		lv_group_add_obj(group, ui->module_test_small_lvl_cv2);
		lv_group_add_obj(group, ui->module_test_small_lvl_cv3);
		lv_group_add_obj(group, ui->module_test_small_lvl_cv4);
		lv_group_add_obj(group, ui->module_test_small_lvl_cv5);
		lv_group_add_obj(group, ui->module_test_small_lvl_cv6);
		lv_group_add_obj(group, ui->module_test_small_env_out1);
		lv_group_add_obj(group, ui->module_test_small_env_out2);
		lv_group_add_obj(group, ui->module_test_small_env_out3);
		lv_group_add_obj(group, ui->module_test_small_rotate_cv);
		lv_group_add_obj(group, ui->module_test_small_env_out4);
		lv_group_add_obj(group, ui->module_test_small_env_out5);
		lv_group_add_obj(group, ui->module_test_small_env_out6);
		lv_group_add_obj(group, ui->module_test_small_post_pre_switch);
		lv_group_add_obj(group, ui->module_test_small_fast_slow_switch);
		lv_group_add_obj(group, ui->module_test_small_input_odds);
		lv_group_add_obj(group, ui->module_test_small_input_evens);
		lv_group_add_obj(group, ui->module_test_small_rotate_trig_cntr);
		lv_group_add_obj(group, ui->module_test_small_rotate_trig_clkw);
		lv_group_add_obj(group, ui->module_test_small_output_odds);
		lv_group_add_obj(group, ui->module_test_small_output_evens);
		lv_group_add_obj(group, ui->module_test_small_scale_cv);
		lv_group_add_obj(group, ui->module_test_small_res_q_cv);
		lv_group_add_obj(group, ui->module_test_small_rotate_scale);
		lv_group_add_obj(group, ui->module_test_small_morph_cv);
		lv_group_add_obj(group, ui->module_test_small_spread_cv);
		lv_group_add_obj(group, ui->module_test_small_scale_r_switch);
		lv_group_add_obj(group, ui->module_test_small_res_q);
		lv_group_add_obj(group, ui->module_test_small_morph);
		lv_group_add_obj(group, ui->module_test_small_spread);
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
