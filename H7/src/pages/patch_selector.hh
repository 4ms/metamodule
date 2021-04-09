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

	void start()
	{
		hi_patch_index = patch_list.cur_patch_index();
		cur_hi_top_pos = hi_patch_index * 24 + 42;
		animation_ctr = 0;
	}

	void draw()
	{
		const uint32_t lineheight = 24;

		if (hi_patch_index != patch_list.cur_patch_index()) {
			animation_dir = patch_list.cur_patch_index() - hi_patch_index;
			animation_ctr = lineheight;
			hi_patch_index = patch_list.cur_patch_index();
		}
		screen.fill(Colors::white);
		PageWidgets::setup_header(screen);
		screen.print("Select a patch:");

		screen.setFont(PageWidgets::subheader_font);
		if (animation_ctr) {
			animation_ctr -= 4;
			cur_hi_top_pos += 4 * animation_dir;
		}
		screen.blendRect(0, cur_hi_top_pos, 240, 24, Colors::cyan.Rgb565(), 0.6f);
		screen.setTextColor(Colors::black);
		int16_t y_pos = 40;
		for (unsigned i = 0; i < PatchList::NumPatches; i++) {
			screen.setCursor(2, y_pos);
			screen.print(patch_list.get_patch(i).patch_name);
			y_pos += 24;
		}
	}

	void stop_page() {}

	uint8_t hi_patch_index;
	int32_t animation_ctr;
	int32_t animation_dir;
	int16_t cur_hi_top_pos;
};

} // namespace MetaModule
