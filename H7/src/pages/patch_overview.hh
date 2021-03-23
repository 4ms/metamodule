#pragma once
#include "pages/page_manager.hh"
#include "pages/page_widgets.hh"

namespace MetaModule
{

struct PatchOverviewPage : DisplayPage {
	static void draw(PageManager *pm)
	{
		auto &screen = pm->screen;
		auto &player = pm->patch_player;
		auto &cur_patch = pm->patch_list.cur_patch();

		screen.fill(pm->bgcolor);
		PageWidgets::draw_patch_name(pm, &FreeSansBold18pt7b, pm->patch_fgcolor, 2, 30);
		// screen.setFont(&FreeSansBold18pt7b);
		// screen.setTextColor(pm->patch_fgcolor.Rgb565());
		// screen.setTextSize(1);
		// screen.setCursor(2, 30);
		// screen.setTextWrap(false);
		// screen.print(cur_patch.patch_name);
	}
};

struct JackMapPage : DisplayPage {
	static void draw(PageManager *pm)
	{
		auto &screen = pm->screen;
		auto &player = pm->patch_player;
		auto &cur_patch = pm->patch_list.cur_patch();

		screen.fill(pm->bgcolor);
		screen.setFont(&FreeSans9pt7b);
		screen.setTextSize(1);
		screen.setTextWrap(false);
		int y = 50;
		const uint16_t line_height = 16;
		const int num_jacks = 8;
		const char jack_name[num_jacks][6] = {"In L", "In R", "CV A", "CV B", "CV C", "CV D", "Out L", "Out R"};

		if (player.is_loaded) {
			int num_ins = player.get_num_panel_inputs();
			for (int i = 0; i < num_jacks; i++) {
				Jack jack;
				if (i < num_ins)
					jack = player.get_panel_input_connection(i);
				else
					jack = player.get_panel_output_connection(i - num_ins);

				if (jack.module_id == 0)
					continue;

				screen.setTextColor(Colors::black.Rgb565());
				screen.setCursor(2, y);
				y += line_height;
				screen.print(jack_name[i]);
				screen.print(": ");

				screen.setTextColor(Colors::blue.blend(Colors::black, 0.5f).Rgb565());
				if (i < num_ins)
					screen.print(player.modules[jack.module_id]->injack_name(jack.jack_id));
				else
					screen.print(player.modules[jack.module_id]->outjack_name(jack.jack_id));

				screen.setTextColor(Colors::white.blend(Colors::black, 0.75f).Rgb565());
				screen.print(" (");
				screen.print(player.modules[jack.module_id]->get_description());
				screen.print(" #");
				screen.print(jack.module_id);
				screen.print(")");
			}
		}
	}
};

struct KnobMapPage : DisplayPage {
	static void draw(PageManager *pm)
	{
		auto &screen = pm->screen;
		auto &player = pm->patch_player;
		auto &cur_patch = pm->patch_list.cur_patch();

		screen.fill(pm->bgcolor);
		screen.setFont(&FreeSans9pt7b);
		screen.setTextSize(1);
		screen.setTextWrap(false);
		const uint16_t line_height = 16;
		const char knob_name[8][2] = {"A", "B", "C", "D", "a", "b", "c", "d"};

		if (player.is_loaded) {
			for (int i = 0; i < cur_patch.num_mapped_knobs; i++) {
				auto &knob = cur_patch.mapped_knobs[i];

				screen.setTextColor(Colors::black.Rgb565());
				screen.setCursor(2, 50 + line_height * i);
				screen.print(knob_name[knob.panel_knob_id]);
				screen.print(" = ");

				screen.setTextColor(Colors::white.blend(Colors::black, 0.75f).Rgb565());
				screen.print(player.modules[knob.module_id]->get_description());
				screen.print(" #");
				screen.print(knob.module_id);

				screen.setTextColor(Colors::blue.blend(Colors::black, 0.5f).Rgb565());
				screen.print(": ");
				screen.print(player.modules[knob.module_id]->knob_name(knob.param_id));
			}
		}
	}
};

struct PatchLayoutPage : DisplayPage {
	static void draw(PageManager *pm)
	{
		auto &screen = pm->screen;
		auto &player = pm->patch_player;
		auto &cur_patch = pm->patch_list.cur_patch();

		screen.fill(Colors::cyan);
	}
};

struct ModulesInPatchPage : DisplayPage {
	static void draw(PageManager *pm)
	{
		auto &screen = pm->screen;
		auto &player = pm->patch_player;
		auto &cur_patch = pm->patch_list.cur_patch();

		screen.fill(Colors::white);
		PageWidgets::draw_patch_name(pm, &FreeSansBold12pt7b, Colors::red, 2, 20);
		screen.setCursor(2, 40);
		screen.print("Modules in patch:");
	}
};

} // namespace MetaModule
