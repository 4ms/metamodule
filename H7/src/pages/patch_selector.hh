#pragma once
#include "pages/base.hh"
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

		screen.setFont(&FreeSans12pt7b);
		screen.setTextColor(Colors::black.blend(Colors::green));
		for (int i = 0; i < PatchList::NumPatches; i++) {
			screen.setCursor(2, 60 + i * 24);
			screen.print(patch_list.get_patch(i).patch_name);
		}
	}
};

} // namespace MetaModule
