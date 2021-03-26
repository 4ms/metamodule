#pragma once
#include "pages/page_manager.hh"
#include "pages/page_widgets.hh"

namespace MetaModule
{

struct PatchSelectorPage : DisplayPage {
	static void draw(PageManager *pm)
	{
		auto &screen = pm->screen;
		auto &player = pm->patch_player;
		auto &cur_patch = pm->patch_list.cur_patch();

		screen.fill(pm->bgcolor);
		screen.setFont(&FreeSansBold12pt7b);
		screen.setTextColor(Colors::black);
		screen.setCursor(2, 20);
		screen.print("Select a patch:");

		screen.setFont(&FreeSans12pt7b);
		screen.setTextColor(Colors::black.blend(Colors::green));
		for (int i = 0; i < PatchList::NumPatches; i++) {
			screen.setCursor(2, 40 + i * 24);
			screen.print(pm->patch_list.get_patch(i).patch_name);
		}
	}
};

} // namespace MetaModule
