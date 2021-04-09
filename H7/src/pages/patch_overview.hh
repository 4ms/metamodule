#pragma once
#include "pages/base.hh"
#include "pages/fonts.hh"
#include "pages/page_widgets.hh"

namespace MetaModule
{

struct PatchOverviewPage : PageBase {
	PatchOverviewPage(PatchInfo info, ScreenFrameBuffer &screen)
		: PageBase{info, screen}
	{}

	static constexpr Color bgcolor = Colors::white;
	static constexpr Color subheader_fg = Colors::black;

	void draw()
	{
		screen.fill(bgcolor);
		PageWidgets::setup_header(screen);
		screen.setTextWrap(true);
		screen.print(patch_list.cur_patch().patch_name);

		screen.setFont(PageWidgets::list_font);
		screen.setTextColor(Colors::grey);
		screen.setCursor(2, 90);
		screen.print("Here is the verbose patch description, etc etc. Todo, fix word-wrap to only wrap on a space");
		screen.setTextWrap(false);
	}
};

// Todo: this should display User-set names for jacks:
// Instead of "Drum#3:Out", should be "Kick Out"
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

		screen.setFont(PageWidgets::list_font);
		const uint16_t line_height = PageWidgets::list_lineheight;
		int y = PageWidgets::list_ypos;

		if (patch_player.is_loaded) {
			int num_ins = Panel::NumUserFacingInJacks;
			int num_outs = Panel::NumUserFacingOutJacks;

			for (int i = 0; i < (num_ins + num_outs); i++) {
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
				if (i < num_ins)
					screen.print(patch_player.modules[0]->outjack_name(i));
				else
					screen.print(patch_player.modules[0]->injack_name(i - num_ins));
				screen.print(": ");

				screen.setTextColor(Colors::blue.blend(Colors::black, 0.5f));
				if (i < num_ins)
					screen.print(patch_player.modules[jack.module_id]->injack_name(jack.jack_id));
				else
					screen.print(patch_player.modules[jack.module_id]->outjack_name(jack.jack_id));

				screen.setTextColor(Colors::white.blend(Colors::black, 0.75f));
				screen.print(" (");
				PageWidgets::print_module_name(screen, patch_player, jack.module_id);
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

		screen.setFont(PageWidgets::list_font);
		const uint16_t y_pos = PageWidgets::list_ypos;
		const uint16_t line_height = PageWidgets::list_lineheight;
		const char knob_name[8][2] = {"A", "B", "C", "D", "a", "b", "c", "d"};

		if (patch_player.is_loaded) {
			for (int i = 0; i < patch_list.cur_patch().num_mapped_knobs; i++) {
				auto &knob = patch_list.cur_patch().mapped_knobs[i];

				screen.setTextColor(Colors::black);
				screen.setCursor(2, y_pos + line_height * i);
				screen.print(knob_name[knob.panel_knob_id]);
				screen.print(" = ");

				screen.setTextColor(Colors::white.blend(Colors::black, 0.75f));
				PageWidgets::print_module_name(screen, patch_player, knob.module_id);

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
		screen.print("Internal cables:");

		screen.setFont(PageWidgets::list_font);
		uint16_t y_pos = PageWidgets::list_ypos;
		if (patch_player.is_loaded) {
			screen.setCursor(2, y_pos);
			for (int i = 0; i < patch_list.cur_patch().num_nets; i++) {
				auto &net = patch_list.cur_patch().nets[i];
				if (net.num_jacks < 2 || net.jacks[0].module_id == 0 || net.jacks[1].module_id == 0)
					continue;

				auto output_jack = net.jacks[0];
				screen.setTextColor(Colors::black);
				PageWidgets::print_module_name(screen, patch_player, output_jack.module_id);
				screen.print(": ");
				screen.setTextColor(Colors::blue.blend(Colors::black, 0.5f));
				screen.print(patch_player.modules[output_jack.module_id]->outjack_name(output_jack.jack_id));

				for (int j = 1; j < net.num_jacks; j++) {
					auto input_jack = net.jacks[j];
					y_pos += PageWidgets::list_lineheight;
					screen.setCursor(2, y_pos);
					screen.print("  => ");
					screen.setTextColor(Colors::black);
					PageWidgets::print_module_name(screen, patch_player, input_jack.module_id);
					screen.print(": ");
					screen.setTextColor(Colors::blue.blend(Colors::black, 0.5f));
					screen.print(patch_player.modules[input_jack.module_id]->injack_name(input_jack.jack_id));
				}
				y_pos += PageWidgets::list_lineheight;
			}
		}
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

		screen.setFont(PageWidgets::list_font);
		uint16_t y_pos = PageWidgets::list_ypos;
		if (patch_player.is_loaded) {
			for (int i = 0; i < patch_list.cur_patch().num_modules; i++) {
				if (i == 0)
					continue; // skip PANEL
				screen.setCursor(PageWidgets::margin_left, y_pos);
				screen.setTextColor(Colors::white.blend(Colors::black, 0.75f));
				screen.print(i);
				screen.print(": ");
				PageWidgets::print_module_name(screen, patch_player, i);
				y_pos += PageWidgets::list_lineheight;
			}
		}
	}
};

} // namespace MetaModule
