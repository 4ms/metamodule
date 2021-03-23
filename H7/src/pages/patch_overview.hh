#pragma once
#include "page_manager.hh"

namespace MetaModule
{

struct PatchOverviewPage : DisplayPage {
	PatchOverviewPage() = delete;

	static void draw(PageManager *pm)
	{
		pm->screen.fill(pm->bgcolor);
		pm->screen.setFont(&FreeSansBold18pt7b);
		pm->screen.setTextColor(pm->patch_fgcolor.Rgb565());
		pm->screen.setTextSize(1);
		pm->screen.setCursor(2, 30);
		pm->screen.setTextWrap(false);
		pm->screen.print(pm->patch_list.cur_patch().patch_name);
	}
};

} // namespace MetaModule
