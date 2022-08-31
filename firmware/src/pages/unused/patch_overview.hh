#pragma once
#include "pages/base.hh"

namespace MetaModule
{

struct PatchOverviewPage : PageBase {

	PatchOverviewPage(PatchInfo info)
		: PageBase{info}
	{}

	// lv_obj_t *screen1_lmeter_1;
	// lv_style_t style_screen1_lmeter_1_main;
	// lv_obj_t *slider1;
	// int32_t slider_val = 30;

	void init() override
	{
		////Write codes screen1
		//screen = lv_obj_create(nullptr, nullptr);

		////Write codes screen1_lmeter_1
		//screen1_lmeter_1 = lv_linemeter_create(screen, nullptr);

		////Write style LV_LINEMETER_PART_MAIN for screen1_lmeter_1
		//static lv_style_t style_screen1_lmeter_1_main;
		//lv_style_reset(&style_screen1_lmeter_1_main);

		////Write style state: LV_STATE_DEFAULT for style_screen1_lmeter_1_main
		//lv_style_set_radius(&style_screen1_lmeter_1_main, LV_STATE_DEFAULT, 58);
		//lv_style_set_bg_color(&style_screen1_lmeter_1_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
		//lv_style_set_bg_grad_color(&style_screen1_lmeter_1_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
		//lv_style_set_bg_grad_dir(&style_screen1_lmeter_1_main, LV_STATE_DEFAULT, LV_GRAD_DIR_HOR);
		//lv_style_set_bg_opa(&style_screen1_lmeter_1_main, LV_STATE_DEFAULT, 255);
		//lv_style_set_pad_left(&style_screen1_lmeter_1_main, LV_STATE_DEFAULT, 5);
		//lv_style_set_pad_right(&style_screen1_lmeter_1_main, LV_STATE_DEFAULT, 5);
		//lv_style_set_pad_top(&style_screen1_lmeter_1_main, LV_STATE_DEFAULT, 5);
		//lv_style_set_pad_bottom(&style_screen1_lmeter_1_main, LV_STATE_DEFAULT, 5);
		//lv_style_set_line_color(&style_screen1_lmeter_1_main, LV_STATE_DEFAULT, lv_color_make(0x00, 0x59, 0xff));
		//lv_style_set_line_width(&style_screen1_lmeter_1_main, LV_STATE_DEFAULT, 10);
		//lv_style_set_line_opa(&style_screen1_lmeter_1_main, LV_STATE_DEFAULT, 255);
		//lv_style_set_scale_grad_color(&style_screen1_lmeter_1_main, LV_STATE_DEFAULT, lv_color_make(0x00, 0x59, 0xff));
		//lv_style_set_scale_end_color(&style_screen1_lmeter_1_main, LV_STATE_DEFAULT, lv_color_make(0xb5, 0xb5, 0xb5));
		//lv_style_set_scale_width(&style_screen1_lmeter_1_main, LV_STATE_DEFAULT, 6);
		//lv_style_set_scale_end_line_width(&style_screen1_lmeter_1_main, LV_STATE_DEFAULT, 10);
		//lv_obj_add_style(screen1_lmeter_1, LV_LINEMETER_PART_MAIN, &style_screen1_lmeter_1_main);
		//lv_obj_set_pos(screen1_lmeter_1, 211, 4);
		//lv_obj_set_size(screen1_lmeter_1, 97, 97);
		//lv_linemeter_set_scale(screen1_lmeter_1, 300, 100);
		//lv_linemeter_set_range(screen1_lmeter_1, 0, 100);
		//lv_linemeter_set_value(screen1_lmeter_1, 75);
		//lv_linemeter_set_angle_offset(screen1_lmeter_1, 0);

		//slider1 = lv_slider_create(screen, nullptr);
		//slider_val = 30;
		//lv_obj_set_x(slider1, 30);
		//lv_obj_set_y(slider1, 10);
		//lv_obj_set_size(slider1, 15, 100);
		//lv_slider_set_value(slider1, slider_val, LV_ANIM_OFF);

		//init_bg();
	}

	void update() override
	{
		//slider_val = 100.f * params.knobs[0];
		// slider_val++;
		// if (slider_val > 100)
		// 	slider_val = 0;
		// lv_slider_set_value(slider1, slider_val, LV_ANIM_OFF);

		// float knob = params.knobs[1];
		// int slider_val2 = knob * 100.f;
		// lv_linemeter_set_value(screen1_lmeter_1, slider_val2);

		// screen.fill(bgcolor);
		// PageWidgets::setup_header(screen);
		// screen.setTextWrap(true);
		// screen.print(patch_player.get_patch_name());
	}
};
/*

// Todo: this should display User-set names for jacks:
// Instead of "Drum#3:Out", should be "Kick Out"
struct JackMapPage : PageBase {
	JackMapPage(PatchInfo info)
		: PageBase{info}
	{
		ui = &base_ui;
	}

	struct {
		lv_obj_t *screen;
	} base_ui, *ui;

	bool is_init = false;

	void init()
	{
		//Write codes screen
		ui->screen = lv_obj_create(nullptr, nullptr);

		is_init = true;
	}

	void blur() {}

	void update()
	{
		// screen.fill(PatchOverviewPage::bgcolor);
		// PageWidgets::setup_header(screen);
		// screen.print(patch_player.get_patch_name());
		// PageWidgets::setup_sub_header(screen);
		// screen.print("Jack layout:");

		// screen.setFont(PageWidgets::list_font);
		// const uint16_t line_height = PageWidgets::list_lineheight;
		// int y = PageWidgets::list_ypos;

		// if (patch_player.is_loaded) {
		// 	int num_ins = PanelDef::NumUserFacingInJacks;
		// 	int num_outs = PanelDef::NumUserFacingOutJacks;

		// 	for (int i = 0; i < (num_ins + num_outs); i++) {
		// 		Jack jack;
		// 		if (i < num_ins)
		// 			jack = patch_player.get_panel_input_connection(i);
		// 		else
		// 			jack = patch_player.get_panel_output_connection(i - num_ins);

		// 		if (jack.module_id == 0)
		// 			continue;

		// 		screen.setTextColor(Colors::black);
		// 		screen.setCursor(2, y);
		// 		y += line_height;
		// 		if (i < num_ins)
		// 			screen.print(patch_player.modules[0]->outjack_name(i));
		// 		else
		// 			screen.print(patch_player.modules[0]->injack_name(i - num_ins));
		// 		screen.print(": ");

		// 		screen.setTextColor(Colors::blue.blend(Colors::black, 0.5f));
		// 		if (i < num_ins)
		// 			screen.print(patch_player.modules[jack.module_id]->injack_name(jack.jack_id));
		// 		else
		// 			screen.print(patch_player.modules[jack.module_id]->outjack_name(jack.jack_id));

		// 		screen.setTextColor(Colors::white.blend(Colors::black, 0.75f));
		// 		screen.print(" (");
		// 		PageWidgets::print_module_name(screen, patch_player, jack.module_id);
		// 		screen.print(")");
		// 	}
		// }
	}
};

struct KnobMapPage : PageBase {
	KnobMapPage(PatchInfo info)
		: PageBase{info}
	{}

	void draw()
	{
		// screen.fill(PatchOverviewPage::bgcolor);
		// PageWidgets::setup_header(screen);
		// screen.print(patch_player.get_patch_name());
		// PageWidgets::setup_sub_header(screen);
		// screen.print("Knob layout:");

		// screen.setFont(PageWidgets::list_font);
		// const uint16_t y_pos = PageWidgets::list_ypos;
		// const uint16_t line_height = PageWidgets::list_lineheight;

		// if (patch_player.is_loaded) {
		// 	int i = 0;
		// 	for (auto &knob_conn : patch_player.knob_conns) {
		// 		if (!knob_conn.size())
		// 			continue;

		// 		screen.setTextColor(Colors::black);
		// 		screen.setCursor(2, y_pos + line_height * i);
		// 		screen.print(patch_player.modules[0]->knob_name(knob_conn[0].panel_knob_id));
		// 		screen.print("= ");

		// 		for (auto &knob : knob_conn) {
		// 			screen.setTextColor(Colors::white.blend(Colors::black, 0.75f));
		// 			PageWidgets::print_module_name(screen, patch_player, knob.module_id);

		// 			screen.setTextColor(Colors::blue.blend(Colors::black, 0.5f));
		// 			screen.print(": ");
		// 			screen.print(patch_player.modules[knob.module_id]->knob_name(knob.param_id));
		// 			screen.print(" ");
		// 		}
		// 		i++;
		// 	}

		// 	// for (int i = 0; i < patch_player.get_num_mapped_knobs(); i++) {
		// 	// 	auto &knob = patch_player.mapped_knobs[i];

		// 	// 	screen.setTextColor(Colors::black);
		// 	// 	screen.setCursor(2, y_pos + line_height * i);
		// 	// 	screen.print(knob_name[knob.panel_knob_id]);
		// 	// 	screen.print(" = ");

		// 	// 	screen.setTextColor(Colors::white.blend(Colors::black, 0.75f));
		// 	// 	PageWidgets::print_module_name(screen, patch_player, knob.module_id);

		// 	// 	screen.setTextColor(Colors::blue.blend(Colors::black, 0.5f));
		// 	// 	screen.print(": ");
		// 	// 	screen.print(patch_player.modules[knob.module_id]->knob_name(knob.param_id));
		// 	// }
		// }
	}
};

struct PatchLayoutPage : PageBase{
	// using ScrollBoxT = ScrollBox<PatchLayoutPage>;
	// static constexpr RectC box{
	// 	.left = 0,
	// 	.top = PageWidgets::list_ypos,
	// 	.right = MMScreenBufferConf::viewWidth,
	// 	.bottom = MMScreenBufferConf::viewHeight,
	// };

	PatchLayoutPage(PatchInfo info)
		: PageBase{info}
	// , ScrollBoxT{
	// 			 {
	// 				 .bounding_box = box,
	// 				 .show_scrollbar = false,
	// 				 .scroll_method = ScrollMethod::ByScreen,
	// 				 .loop = false,
	// 				 .highlight = Colors::white, //none?
	// 				 .lineheight = PageWidgets::list_lineheight,
	// 				 .num_animation_steps = 6,
	// 			 }}
	{}

	void focus()
	{
		// ScrollBoxT::set_num_items(patch_player.get_num_int_cables());
		// ScrollBoxT::focus();
		// ScrollBoxT::set_selection(0);
	}

	void draw()
	{
		// auto rotary = metaparams.rotary.use_motion();
		// if (rotary > 0)
		// 	ScrollBoxT::scroll_screen_down();
		// if (rotary < 0)
		// 	ScrollBoxT::scroll_screen_up();

		// screen.fill(PatchOverviewPage::bgcolor);
		// PageWidgets::setup_header(screen);
		// screen.print(patch_player.get_patch_name());
		// PageWidgets::setup_sub_header(screen);
		// screen.print("Internal cables:");

		// ScrollBoxT::draw_scroll_box();
	}

	void draw_scrollbox_element(int32_t i)
	{
		//screen.setTextColor(Colors::black);
		//screen.setFont(PageWidgets::list_font);
		//screen.print("X");
		//auto &cable = patch_player.int_cables[i];
		//PageWidgets::print_module_name(screen, patch_player, cable.out.module_id);
		//screen.print(": ");
		//screen.setTextColor(Colors::blue.blend(Colors::black, 0.25f));
		//screen.print(patch_player.modules[cable.out.module_id]->outjack_name(cable.out.jack_id));

		//for (int j = 1; j < MAX_CONNECTIONS_PER_NODE - 1; j++) {
		//	auto &input_jack = cable.ins[j];
		//	if (input_jack.jack_id < 0 || input_jack.module_id < 0)
		//		break;
		//	//newline?
		//	screen.setTextColor(Colors::grey);
		//	screen.print(" =>");
		//	screen.setTextColor(Colors::black);
		//	PageWidgets::print_module_name(screen, patch_player, input_jack.module_id);
		//	screen.print(": ");
		//	screen.setTextColor(Colors::blue.blend(Colors::black, 0.25f));
		//	screen.print(patch_player.modules[input_jack.module_id]->injack_name(input_jack.jack_id));
		//}
	}
};

struct ModulesInPatchPage : PageBase {
	ModulesInPatchPage(PatchInfo info)
		: PageBase{info}
	{}

	void draw()
	{
		// screen.fill(PatchOverviewPage::bgcolor);
		// PageWidgets::setup_header(screen);
		// screen.print(patch_player.get_patch_name());
		// PageWidgets::setup_sub_header(screen);
		// screen.print("Modules in patch:");

		// screen.setFont(PageWidgets::list_font);
		// uint16_t y_pos = PageWidgets::list_ypos;
		// if (patch_player.is_loaded) {
		// 	for (int i = 0; i < patch_player.get_num_modules(); i++) {
		// 		if (i == 0)
		// 			continue; // skip PANEL
		// 		screen.setCursor(PageWidgets::margin_left, y_pos);
		// 		screen.setTextColor(Colors::white.blend(Colors::black, 0.75f));
		// 		PageWidgets::print_module_name(screen, patch_player, i);
		// 		y_pos += PageWidgets::list_lineheight;
		// 	}
		// }
	}
};
*/
} // namespace MetaModule
