#pragma once
#include "pages/base.hh"
#include "pages/gui-guider/custom.h"
#include "pages/gui-guider/gui_guider.h"

namespace MetaModule
{
struct SketchesTestPage : PageBase {
	SketchesTestPage(PatchInfo info)
		: PageBase{info} {
	}

	void init() override {
		setup_scr_symbol_sketches(ui);
		init_bg(ui->symbol_sketches);
	}

	void update() override {
	}
};

struct DropDownOnlyPage : PageBase {
	DropDownOnlyPage(PatchInfo info)
		: PageBase{info} {
	}

	void init() override {
		// setup_scr_Dropdown_only(ui);
		// init_bg(ui->Dropdown_only);

		// lv_dropdown_clear_options(ui->Dropdown_only_patch_dropdown);
		// for (int i = 0; i < patch_list.NumPatches; i++)
		// 	lv_dropdown_add_option(ui->Dropdown_only_patch_dropdown, patch_list.get_patch_name(i), i);

		// lv_group_add_obj(group, ui->Dropdown_only_patch_dropdown);
	}

	void update() override {
	}
};
struct AudioCVInsPage : PageBase {
	AudioCVInsPage(PatchInfo info)
		: PageBase{info} {
	}

	void init() override {
		setup_scr_AudioCV_Ins(ui);
		init_bg(ui->AudioCV_Ins);
	}

	void update() override {
	}
};

// struct SMRTestPage : PageBase {
// 	static inline lv_style_t style_highlight;
// 	static inline int32_t cur_selected = -1;
// 	static inline lv_obj_t *button[51];

// 	SMRTestPage(PatchInfo info)
// 		: PageBase{info} {
// 	}

// 	static void roller_cb(lv_obj_t *obj, lv_event_t event) {
// 		if (obj != ui->module_test_small_roller_2)
// 			return;

// 		if (event == LV_EVENT_KEY) {
// 			// Turn off old button
// 			if (cur_selected >= 0) {
// 				lv_obj_remove_style(button[cur_selected], LV_BTN_PART_MAIN, &style_highlight);
// 				lv_event_send_refresh(button[cur_selected]);
// 			}

// 			// Get the new button
// 			cur_selected = lv_roller_get_selected(obj);
// 			printf("cur_selected: %d\r\n", cur_selected);

// 			// Turn on new button
// 			lv_obj_add_style(button[cur_selected], LV_BTN_PART_MAIN, &style_highlight);
// 			lv_event_send_refresh(button[cur_selected]);
// 		}
// 	}

// 	void init() override {
// 		setup_scr_module_test_small(ui);
// 		init_bg(ui->module_test_small);

// 		// Event and group for roller
// 		// group = lv_group_create();
// 		lv_group_add_obj(group, ui->module_test_small_roller_2);
// 		lv_obj_set_event_cb(ui->module_test_small_roller_2, roller_cb);

// 		// Highlight for buttons
// 		lv_style_init(&style_highlight);
// 		lv_style_set_radius(&style_highlight, LV_STATE_DEFAULT, 120);
// 		lv_style_set_outline_color(&style_highlight, LV_STATE_DEFAULT, lv_color_make(0xff, 0xc3, 0x70));
// 		lv_style_set_outline_width(&style_highlight, LV_STATE_DEFAULT, 4);
// 		lv_style_set_outline_opa(&style_highlight, LV_STATE_DEFAULT, 200);

// 		// Fix roller style
// 		static lv_style_t style_roller_tweak;
// 		lv_style_reset(&style_roller_tweak);
// 		lv_style_set_pad_hor(&style_roller_tweak, LV_STATE_DEFAULT, 2);
// 		lv_style_set_pad_ver(&style_roller_tweak, LV_STATE_DEFAULT, 10);
// 		lv_style_set_pad_inner(&style_roller_tweak, LV_STATE_DEFAULT, 0);
// 		lv_style_set_text_line_space(&style_roller_tweak, LV_STATE_DEFAULT, 7);
// 		lv_obj_add_style(ui->module_test_small_roller_2, LV_ROLLER_PART_BG, &style_roller_tweak);
// 		lv_obj_add_style(ui->module_test_small_roller_2, LV_ROLLER_PART_SELECTED, &style_roller_tweak);

// 		lv_roller_set_align(ui->module_test_small_roller_2, LV_ALIGN_CENTER);
// 		lv_roller_set_options(ui->module_test_small_roller_2,
// 							  "Freq Odds\n"
// 							  "Freq CV-O\n"
// 							  "Lock Gate-O\n"
// 							  "Lock 1/135\n"
// 							  "Lock Ch.1\n"
// 							  "Lock Ch.2\n"
// 							  "Lock Ch.3\n"
// 							  "Lock Ch.4\n"
// 							  "Lock Ch.5\n"
// 							  "Lock Ch.6\n"
// 							  "Freq Evens\n"
// 							  "Freq CV-E\n"
// 							  "Lock Gate-E\n"
// 							  "Lock 2/246\n"
// 							  "Level Ch.1\n"
// 							  "Level Ch.2\n"
// 							  "Level Ch.3\n"
// 							  "Level Ch.4\n"
// 							  "Level Ch.5\n"
// 							  "Level Ch.6\n"
// 							  "Slew\n"
// 							  "Lvl CV Ch.1\n"
// 							  "Lvl CV Ch.2\n"
// 							  "Lvl CV Ch.3\n"
// 							  "Lvl CV Ch.4\n"
// 							  "Lvl CV Ch.5\n"
// 							  "Lvl CV Ch.6\n"
// 							  "Env Out Ch.1\n"
// 							  "Env Out Ch.2\n"
// 							  "Env Out Ch.3\n"
// 							  "Rotate CV\n"
// 							  "Env Out Ch.4\n"
// 							  "Env Out Ch.5\n"
// 							  "Env Out Ch.6\n"
// 							  "Pre/Post\n"
// 							  "Fast/Trig/Slow\n"
// 							  "Input Odds\n"
// 							  "Input Evens\n"
// 							  "Rotate <-\n"
// 							  "Rotate ->\n"
// 							  "Output Odds\n"
// 							  "Output Evens\n"
// 							  "Scale CV\n"
// 							  "Res CV\n"
// 							  "Rotate Scale\n"
// 							  "Morph CV\n"
// 							  "Spread CV\n"
// 							  "ROTATE|SCALE\n"
// 							  "Res (Q)\n"
// 							  "Morph\n"
// 							  "Spread",
// 							  LV_ROLLER_MODE_INIFINITE);

// 		int i = 0;
// 		button[i++] = (ui->module_test_small_freq_nudge1);
// 		button[i++] = (ui->module_test_small_freq_cv1);
// 		button[i++] = (ui->module_test_small_lock1);
// 		button[i++] = (ui->module_test_small_freq_switch1);
// 		button[i++] = (ui->module_test_small_button_lock1);
// 		button[i++] = (ui->module_test_small_button_lock2);
// 		button[i++] = (ui->module_test_small_button_lock3);
// 		button[i++] = (ui->module_test_small_button_lock4);
// 		button[i++] = (ui->module_test_small_button_lock5);
// 		button[i++] = (ui->module_test_small_button_lock6);
// 		button[i++] = (ui->module_test_small_freq_nudge2);
// 		button[i++] = (ui->module_test_small_freq_cv2);
// 		button[i++] = (ui->module_test_small_lock2);
// 		button[i++] = (ui->module_test_small_freq_switch2);
// 		button[i++] = (ui->module_test_small_slider1);
// 		button[i++] = (ui->module_test_small_slider2);
// 		button[i++] = (ui->module_test_small_slider3);
// 		button[i++] = (ui->module_test_small_slider4);
// 		button[i++] = (ui->module_test_small_slider5);
// 		button[i++] = (ui->module_test_small_slider6);
// 		button[i++] = (ui->module_test_small_switch_cv_slew);
// 		button[i++] = (ui->module_test_small_lvl_cv1);
// 		button[i++] = (ui->module_test_small_lvl_cv2);
// 		button[i++] = (ui->module_test_small_lvl_cv3);
// 		button[i++] = (ui->module_test_small_lvl_cv4);
// 		button[i++] = (ui->module_test_small_lvl_cv5);
// 		button[i++] = (ui->module_test_small_lvl_cv6);
// 		button[i++] = (ui->module_test_small_env_out1);
// 		button[i++] = (ui->module_test_small_env_out2);
// 		button[i++] = (ui->module_test_small_env_out3);
// 		button[i++] = (ui->module_test_small_rotate_cv);
// 		button[i++] = (ui->module_test_small_env_out4);
// 		button[i++] = (ui->module_test_small_env_out5);
// 		button[i++] = (ui->module_test_small_env_out6);
// 		button[i++] = (ui->module_test_small_post_pre_switch);
// 		button[i++] = (ui->module_test_small_fast_slow_switch);
// 		button[i++] = (ui->module_test_small_input_odds);
// 		button[i++] = (ui->module_test_small_input_evens);
// 		button[i++] = (ui->module_test_small_rotate_trig_cntr);
// 		button[i++] = (ui->module_test_small_rotate_trig_clkw);
// 		button[i++] = (ui->module_test_small_output_odds);
// 		button[i++] = (ui->module_test_small_output_evens);
// 		button[i++] = (ui->module_test_small_scale_cv);
// 		button[i++] = (ui->module_test_small_res_q_cv);
// 		button[i++] = (ui->module_test_small_rotate_scale);
// 		button[i++] = (ui->module_test_small_morph_cv);
// 		button[i++] = (ui->module_test_small_spread_cv);
// 		button[i++] = (ui->module_test_small_scale_r_switch);
// 		button[i++] = (ui->module_test_small_res_q);
// 		button[i++] = (ui->module_test_small_morph);
// 		button[i++] = (ui->module_test_small_spread);
// 	}

// 	void update() override {
// 	}
// };

struct GroupArcSketchesPage1 : PageBase {
	GroupArcSketchesPage1(PatchInfo info)
		: PageBase{info} {
	}

	void init() override {
		setup_scr_group_arc_sketches(ui);
		init_bg(ui->group_arc_sketches);
		lv_arc_set_adjustable(ui->group_arc_sketches_arc_1, true);
		lv_arc_set_adjustable(ui->group_arc_sketches_arc_2, true);
		lv_arc_set_adjustable(ui->group_arc_sketches_arc_3, true);
		lv_arc_set_adjustable(ui->group_arc_sketches_arc_4, true);
		lv_arc_set_adjustable(ui->group_arc_sketches_arc_5, true);
		lv_arc_set_adjustable(ui->group_arc_sketches_arc_6, true);
		lv_arc_set_adjustable(ui->group_arc_sketches_arc_7, true);
		lv_arc_set_adjustable(ui->group_arc_sketches_arc_8, true);
		lv_arc_set_adjustable(ui->group_arc_sketches_arc_9, true);
		lv_arc_set_adjustable(ui->group_arc_sketches_arc_10, true);
		lv_arc_set_adjustable(ui->group_arc_sketches_arc_11, true);
		lv_arc_set_adjustable(ui->group_arc_sketches_arc_12, true);
	}

	void update() override {
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
		: PageBase{info} {
	}

	void init() override {
		setup_scr_group_arc_sketches2(ui);
		init_bg(ui->group_arc_sketches2);
	}

	void update() override {
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
		: PageBase{info} {
	}

	void init() override {
		setup_scr_group_arc_sketches3(ui);
		init_bg(ui->group_arc_sketches3);
	}

	void update() override {
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
		: PageBase{info} {
	}

	void init() override {
		setup_scr_group_arc_sketches4(ui);
		screen = ui->group_arc_sketches4;
		init_bg(ui->group_arc_sketches4);
	}

	void update() override {
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
