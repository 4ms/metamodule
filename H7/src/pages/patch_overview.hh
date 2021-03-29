#pragma once
#include "pages/base.hh"
#include "pages/page_widgets.hh"

namespace MetaModule
{

struct PatchOverviewPage : PageBase {
	PatchOverviewPage(PatchInfo info, ScreenFrameBuffer &screen)
		: PageBase{info, screen}
	{}

	static constexpr Color bgcolor = Colors::white;
	static constexpr Color subheader_fg = Colors::black;
	static constexpr uint16_t subheader_ypos = 56;

	static constexpr uint16_t list_ypos = 76;
	static constexpr uint16_t list_lineheight = 20;

	void draw()
	{
		screen.fill(bgcolor);
		PageWidgets::setup_header(screen);
		screen.setTextWrap(true);
		screen.print(patch_list.cur_patch().patch_name);

		screen.setFont(&FreeSans9pt7b);
		screen.setTextColor(Colors::grey);
		screen.setCursor(2, 90);
		screen.print("The verbose patch description, etc etc");
		screen.setTextWrap(false);
	}
};

struct JackMapPage : PageBase {
	JackMapPage(PatchInfo info, ScreenFrameBuffer &screen)
		: PageBase{info, screen}
	{}

	void draw()
	{
		screen.fill(PatchOverviewPage::bgcolor);
		PageWidgets::setup_header(screen);
		screen.print(patch_list.cur_patch().patch_name);
		PageWidgets::setup_sub_header(screen);
		screen.print("Jack layout:");

		screen.setFont(&FreeSans9pt7b);
		const uint16_t line_height = PatchOverviewPage::list_lineheight;
		int y = PatchOverviewPage::list_ypos;

		const int num_jacks = 8;
		const char jack_name[num_jacks][6] = {"In L", "In R", "CV A", "CV B", "CV C", "CV D", "OutL", "OutR"};

		if (patch_player.is_loaded) {
			int num_ins = patch_player.get_num_panel_inputs();
			for (int i = 0; i < num_jacks; i++) {
				Jack jack;
				if (i < num_ins)
					jack = patch_player.get_panel_input_connection(i);
				else
					jack = patch_player.get_panel_output_connection(i - num_ins);

				if (jack.module_id == 0)
					continue;

				screen.setTextColor(Colors::black);
				screen.setCursor(2, y);
				y += line_height;
				screen.print(jack_name[i]);
				screen.print(": ");

				screen.setTextColor(Colors::blue.blend(Colors::black, 0.5f));
				if (i < num_ins)
					screen.print(patch_player.modules[jack.module_id]->injack_name(jack.jack_id));
				else
					screen.print(patch_player.modules[jack.module_id]->outjack_name(jack.jack_id));

				screen.setTextColor(Colors::white.blend(Colors::black, 0.75f));
				screen.print(" (");
				screen.print(patch_player.modules[jack.module_id]->get_description());
				screen.print(" #");
				screen.print(jack.module_id);
				screen.print(")");
			}
		}
	}
};

struct KnobMapPage : PageBase {
	KnobMapPage(PatchInfo info, ScreenFrameBuffer &screen)
		: PageBase{info, screen}
	{}

	void draw()
	{
		screen.fill(PatchOverviewPage::bgcolor);
		PageWidgets::setup_header(screen);
		screen.print(patch_list.cur_patch().patch_name);
		PageWidgets::setup_sub_header(screen);
		screen.print("Knob layout:");

		screen.setFont(&FreeSans9pt7b);
		const uint16_t y_pos = PatchOverviewPage::list_ypos;
		const uint16_t line_height = PatchOverviewPage::list_lineheight;
		const char knob_name[8][2] = {"A", "B", "C", "D", "a", "b", "c", "d"};

		if (patch_player.is_loaded) {
			for (int i = 0; i < patch_list.cur_patch().num_mapped_knobs; i++) {
				auto &knob = patch_list.cur_patch().mapped_knobs[i];

				screen.setTextColor(Colors::black);
				screen.setCursor(2, y_pos + line_height * i);
				screen.print(knob_name[knob.panel_knob_id]);
				screen.print(" = ");

				screen.setTextColor(Colors::white.blend(Colors::black, 0.75f));
				screen.print(patch_player.modules[knob.module_id]->get_description());
				screen.print(" #");
				screen.print(knob.module_id);

				screen.setTextColor(Colors::blue.blend(Colors::black, 0.5f));
				screen.print(": ");
				screen.print(patch_player.modules[knob.module_id]->knob_name(knob.param_id));
			}
		}
	}
};

struct PatchLayoutPage : PageBase {
	PatchLayoutPage(PatchInfo info, ScreenFrameBuffer &screen)
		: PageBase{info, screen}
	{}

	void draw()
	{
		screen.fill(PatchOverviewPage::bgcolor);
		PageWidgets::setup_header(screen);
		screen.print(patch_list.cur_patch().patch_name);
		PageWidgets::setup_sub_header(screen);
		screen.print("Patch cables:");

		screen.setFont(&FreeSans9pt7b);
		const uint16_t y_pos = PatchOverviewPage::list_ypos;
		const uint16_t line_height = PatchOverviewPage::list_lineheight;
	}
};

struct ModulesInPatchPage : PageBase {
	ModulesInPatchPage(PatchInfo info, ScreenFrameBuffer &screen)
		: PageBase{info, screen}
	{}

	void draw()
	{
		screen.fill(PatchOverviewPage::bgcolor);
		PageWidgets::setup_header(screen);
		screen.print(patch_list.cur_patch().patch_name);
		PageWidgets::setup_sub_header(screen);
		screen.print("Modules in patch:");

		screen.setFont(&FreeSans9pt7b);
		const uint16_t y_pos = PatchOverviewPage::list_ypos;
		const uint16_t line_height = PatchOverviewPage::list_lineheight;
	}
};

} // namespace MetaModule
