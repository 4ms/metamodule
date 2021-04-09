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

		screen.setFont(PageWidgets::subheader_font);
		screen.setTextColor(Colors::black);
		int16_t y_pos = 40;
		for (unsigned i = 0; i < PatchList::NumPatches; i++) {
			screen.setCursor(2, y_pos);
			if (i == patch_list.cur_patch_index())
				screen.fillRect(0, y_pos, 240, 24, Colors::yellow);

			screen.print(patch_list.get_patch(i).patch_name);
			y_pos += 24;
		}
	}
};

} // namespace MetaModule
