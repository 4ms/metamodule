#pragma once
#include "pages/page_manager.hh"
#include "pages/page_widgets.hh"

namespace MetaModule
{

struct PatchOverviewPage : DisplayPage {
	static constexpr Color bgcolor = Colors::white;
	static constexpr Color subheader_fg = Colors::black;
	static constexpr uint16_t subheader_ypos = 56;

	static constexpr uint16_t list_ypos = 76;

	static void draw(PageManager *pm)
	{
		auto &screen = pm->screen;
		auto &player = pm->patch_player;
		auto &cur_patch = pm->patch_list.cur_patch();

		screen.fill(bgcolor);
		screen.setTextWrap(true);
		PageWidgets::draw_patch_name(pm, &FreeSansBold18pt7b, pm->patch_fgcolor, 2, 30);

		screen.setFont(&FreeSans9pt7b);
		screen.setTextColor(Colors::grey);
		screen.setCursor(2, 90);
		screen.print("The verbose patch description, etc etc");
		screen.setTextWrap(false);
	}

	static void draw_header_and_setup_subheader(PageManager *pm)
	{
		pm->screen.fill(PatchOverviewPage::bgcolor);
		pm->screen.setTextWrap(false);
		PageWidgets::draw_patch_name(pm, &FreeSansBold18pt7b, pm->patch_fgcolor, 2, 30);
		pm->screen.setFont(&FreeSansBold12pt7b);
		pm->screen.setTextColor(subheader_fg);
		pm->screen.setCursor(2, PatchOverviewPage::subheader_ypos);
	}
};

struct JackMapPage : DisplayPage {
	static void draw(PageManager *pm)
	{
		auto &screen = pm->screen;
		auto &player = pm->patch_player;
		auto &cur_patch = pm->patch_list.cur_patch();

		PatchOverviewPage::draw_header_and_setup_subheader(pm);
		screen.print("Jack layout:");

		screen.setFont(&FreeSans9pt7b);
		const uint16_t line_height = 16;
		int y = PatchOverviewPage::list_ypos;

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

				screen.setTextColor(Colors::black);
				screen.setCursor(2, y);
				y += line_height;
				screen.print(jack_name[i]);
				screen.print(": ");

				screen.setTextColor(Colors::blue.blend(Colors::black, 0.5f));
				if (i < num_ins)
					screen.print(player.modules[jack.module_id]->injack_name(jack.jack_id));
				else
					screen.print(player.modules[jack.module_id]->outjack_name(jack.jack_id));

				screen.setTextColor(Colors::white.blend(Colors::black, 0.75f));
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

		PatchOverviewPage::draw_header_and_setup_subheader(pm);
		screen.print("Knob layout:");

		screen.setFont(&FreeSans9pt7b);
		const uint16_t y_pos = PatchOverviewPage::list_ypos;
		const uint16_t line_height = 16;
		const char knob_name[8][2] = {"A", "B", "C", "D", "a", "b", "c", "d"};

		if (player.is_loaded) {
			for (int i = 0; i < cur_patch.num_mapped_knobs; i++) {
				auto &knob = cur_patch.mapped_knobs[i];

				screen.setTextColor(Colors::black);
				screen.setCursor(2, y_pos + line_height * i);
				screen.print(knob_name[knob.panel_knob_id]);
				screen.print(" = ");

				screen.setTextColor(Colors::white.blend(Colors::black, 0.75f));
				screen.print(player.modules[knob.module_id]->get_description());
				screen.print(" #");
				screen.print(knob.module_id);

				screen.setTextColor(Colors::blue.blend(Colors::black, 0.5f));
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

		PatchOverviewPage::draw_header_and_setup_subheader(pm);
		screen.print("Patch cables:");

		screen.setFont(&FreeSans9pt7b);
		const uint16_t y_pos = PatchOverviewPage::list_ypos;
		const uint16_t line_height = 16;
	}
};

struct ModulesInPatchPage : DisplayPage {
	static void draw(PageManager *pm)
	{
		auto &screen = pm->screen;
		auto &player = pm->patch_player;
		auto &cur_patch = pm->patch_list.cur_patch();

		PatchOverviewPage::draw_header_and_setup_subheader(pm);
		screen.print("Modules in patch:");

		screen.setFont(&FreeSans9pt7b);
		const uint16_t y_pos = PatchOverviewPage::list_ypos;
		const uint16_t line_height = 16;
	}
};

} // namespace MetaModule
