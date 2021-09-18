#pragma once
#include "pages/base.hh"
#include "pages/fonts.hh"
#include "pages/page_widgets.hh"
#include "pages/scroll_box.hh"

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
		screen.print(patch_player.get_patch_name());
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
		screen.print(patch_player.get_patch_name());
		PageWidgets::setup_sub_header(screen);
		screen.print("Jack layout:");

		screen.setFont(PageWidgets::list_font);
		const uint16_t line_height = PageWidgets::list_lineheight;
		int y = PageWidgets::list_ypos;

		if (patch_player.is_loaded) {
			int num_ins = PanelDef::NumUserFacingInJacks;
			int num_outs = PanelDef::NumUserFacingOutJacks;

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
		screen.print(patch_player.get_patch_name());
		PageWidgets::setup_sub_header(screen);
		screen.print("Knob layout:");

		screen.setFont(PageWidgets::list_font);
		const uint16_t y_pos = PageWidgets::list_ypos;
		const uint16_t line_height = PageWidgets::list_lineheight;

		if (patch_player.is_loaded) {
			int i = 0;
			for (auto &knob_conn : patch_player.knob_conns) {
				if (!knob_conn.size())
					continue;

				screen.setTextColor(Colors::black);
				screen.setCursor(2, y_pos + line_height * i);
				screen.print(patch_player.modules[0]->knob_name(knob_conn[0].panel_knob_id));
				screen.print("= ");

				for (auto &knob : knob_conn) {
					screen.setTextColor(Colors::white.blend(Colors::black, 0.75f));
					PageWidgets::print_module_name(screen, patch_player, knob.module_id);

					screen.setTextColor(Colors::blue.blend(Colors::black, 0.5f));
					screen.print(": ");
					screen.print(patch_player.modules[knob.module_id]->knob_name(knob.param_id));
					screen.print(" ");
				}
				i++;
			}

			// for (int i = 0; i < patch_player.get_num_mapped_knobs(); i++) {
			// 	auto &knob = patch_player.mapped_knobs[i];

			// 	screen.setTextColor(Colors::black);
			// 	screen.setCursor(2, y_pos + line_height * i);
			// 	screen.print(knob_name[knob.panel_knob_id]);
			// 	screen.print(" = ");

			// 	screen.setTextColor(Colors::white.blend(Colors::black, 0.75f));
			// 	PageWidgets::print_module_name(screen, patch_player, knob.module_id);

			// 	screen.setTextColor(Colors::blue.blend(Colors::black, 0.5f));
			// 	screen.print(": ");
			// 	screen.print(patch_player.modules[knob.module_id]->knob_name(knob.param_id));
			// }
		}
	}
};

struct PatchLayoutPage : PageBase, ScrollBox<PatchLayoutPage> {
	using ScrollBoxT = ScrollBox<PatchLayoutPage>;
	static constexpr RectC box{
		.left = 0,
		.top = PageWidgets::list_ypos,
		.right = MMScreenBufferConf::viewWidth,
		.bottom = MMScreenBufferConf::viewHeight,
	};

	PatchLayoutPage(PatchInfo info, ScreenFrameBuffer &screen)
		: PageBase{info, screen}
		, ScrollBoxT{screen,
					 {
						 .bounding_box = box,
						 .show_scrollbar = false,
						 .scroll_method = ScrollMethod::ByScreen,
						 .highlight = Colors::white, //none?
						 .lineheight = PageWidgets::list_lineheight,
						 .num_animation_steps = 6,
					 }}
	{}

	void focus()
	{
		ScrollBoxT::set_num_items(patch_player.get_num_int_cables());
		ScrollBoxT::focus();
		ScrollBoxT::set_selection(0);
	}

	void draw()
	{
		auto rotary = metaparams.rotary.use_motion();
		if (rotary > 0)
			ScrollBoxT::scroll_screen_down();
		if (rotary < 0)
			ScrollBoxT::scroll_screen_up();

		screen.fill(PatchOverviewPage::bgcolor);
		PageWidgets::setup_header(screen);
		screen.print(patch_player.get_patch_name());
		PageWidgets::setup_sub_header(screen);
		screen.print("Internal cables:");

		ScrollBoxT::draw_scroll_box();
	}

	void draw_scrollbox_element(int32_t i)
	{
		screen.setTextColor(Colors::black);
		screen.setFont(PageWidgets::list_font);
		screen.print("X");
		auto &cable = patch_player.int_cables[i];
		PageWidgets::print_module_name(screen, patch_player, cable.out.module_id);
		screen.print(": ");
		screen.setTextColor(Colors::blue.blend(Colors::black, 0.25f));
		screen.print(patch_player.modules[cable.out.module_id]->outjack_name(cable.out.jack_id));

		for (int j = 1; j < MAX_CONNECTIONS_PER_NODE - 1; j++) {
			auto &input_jack = cable.ins[j];
			if (input_jack.jack_id < 0 || input_jack.module_id < 0)
				break;
			//newline?
			screen.setTextColor(Colors::grey);
			screen.print(" =>");
			screen.setTextColor(Colors::black);
			PageWidgets::print_module_name(screen, patch_player, input_jack.module_id);
			screen.print(": ");
			screen.setTextColor(Colors::blue.blend(Colors::black, 0.25f));
			screen.print(patch_player.modules[input_jack.module_id]->injack_name(input_jack.jack_id));
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
		screen.print(patch_player.get_patch_name());
		PageWidgets::setup_sub_header(screen);
		screen.print("Modules in patch:");

		screen.setFont(PageWidgets::list_font);
		uint16_t y_pos = PageWidgets::list_ypos;
		if (patch_player.is_loaded) {
			for (int i = 0; i < patch_player.get_num_modules(); i++) {
				if (i == 0)
					continue; // skip PANEL
				screen.setCursor(PageWidgets::margin_left, y_pos);
				screen.setTextColor(Colors::white.blend(Colors::black, 0.75f));
				PageWidgets::print_module_name(screen, patch_player, i);
				y_pos += PageWidgets::list_lineheight;
			}
		}
	}
};

} // namespace MetaModule
