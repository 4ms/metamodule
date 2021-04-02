#pragma once
#include "pages/base.hh"
#include "pages/fonts.hh"
#include "pages/page_widgets.hh"

namespace MetaModule
{

struct PatchSelectorPage : PageBase {
	PatchSelectorPage(PatchInfo info, ScreenFrameBuffer &screen)
		: PageBase{info, screen}
	{}

	void draw()
	{
		screen.fill(Colors::white);
		PageWidgets::setup_header(screen);
		screen.print("Select a patch:");

		for (int i = 0; i < PatchList::NumPatches; i++) {
			screen.setCursor(2, 60 + i * 24);
			if (i == patch_list.cur_patch_index()) {
				screen.setFont(&FreeSansBold12pt7b);
				screen.fillRect(0, 38 + i * 24, 240, 24, Colors::yellow);
				screen.setTextColor(Colors::black);
			} else {
				screen.setFont(&FreeSans12pt7b);
				screen.setTextColor(Colors::black.blend(Colors::green));
			}

			screen.print(patch_list.get_patch(i).patch_name);
		}
	}
};

} // namespace MetaModule
