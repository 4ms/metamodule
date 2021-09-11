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

	void calc_scroll_offset()
	{
		metaparams.rotary.use_motion();
		if ((int32_t)patch_list.NumPatches <= (MMScreenBufferConf::viewHeight - y_offset) / lineheight)
			scroll_offset_px = 0;
		else if ((cur_hi_top_pos + scroll_offset_px) > ((int32_t)MMScreenBufferConf::viewHeight - lineheight)) {
			scroll_offset_px = MMScreenBufferConf::viewHeight - lineheight - cur_hi_top_pos;
		} else if ((cur_hi_top_pos + scroll_offset_px) < (y_offset)) {
			scroll_offset_px = y_offset - cur_hi_top_pos;
		}
	}

	void start()
	{
		hi_patch_index = patch_list.cur_patch_index();
		cur_hi_top_pos = hi_patch_index * lineheight + y_offset;
		dest_hi_top_pos = cur_hi_top_pos;
		animation_ctr = 0;
		scroll_offset_px = 0;
		calc_scroll_offset();
	}

	uint32_t last_changed_page_tm;

	void change_patch()
	{
		//Start changing patch
		auto rotary = metaparams.rotary.use_motion();
		if (rotary) {
			if (auto now_tm = HAL_GetTick(); (now_tm - last_changed_page_tm) > 100) {
				last_changed_page_tm = now_tm;
				if (rotary < 0)
					mbox.new_patch_index = patch_list.prev_patch();
				else
					mbox.new_patch_index = patch_list.next_patch();
				mbox.loading_new_patch = true;
			}
		}

		if (mbox.loading_new_patch && mbox.audio_is_muted) {
			auto orig_patch = patch_list.cur_patch();
			patch_player.unload_patch();
			patch_list.set_cur_patch_index(mbox.new_patch_index);
			bool ok = patch_player.load_patch(patch_list.cur_patch());
			if (!ok) {
				mbox.set_message("Can't load patch");
				patch_player.unload_patch();
				patch_player.load_patch(orig_patch);
			} else
				mbox.clear_message();

			mbox.loading_new_patch = false;
		}
	}

	void draw()
	{
		if (hi_patch_index != patch_list.cur_patch_index()) {
			hi_patch_index = patch_list.cur_patch_index();
			dest_hi_top_pos = patch_list.cur_patch_index() * lineheight + y_offset;
			animation_step_size = (dest_hi_top_pos - cur_hi_top_pos) / num_animation_steps;
			animation_ctr = num_animation_steps;
		}

		screen.fill(Colors::white);
		PageWidgets::setup_header(screen);
		screen.print("Select a patch:");
		screen.setFont(PageWidgets::subheader_font);
		screen.drawHLine(0, y_offset, MMScreenBufferConf::viewWidth, Colors::grey.Rgb565());
		if (scroll_offset_px < 0)
			screen.printf_at(MMScreenBufferConf::viewWidth - 10, y_offset, "^");
		if (patch_list.NumPatches * lineheight + scroll_offset_px >
			((int32_t)MMScreenBufferConf::viewHeight - y_offset))
			screen.printf_at(MMScreenBufferConf::viewWidth - 10, 210, "v");

		if (animation_ctr) {
			animation_ctr--;
			cur_hi_top_pos += animation_step_size;
		} else
			cur_hi_top_pos = dest_hi_top_pos;

		calc_scroll_offset();

		//Highlight bar
		screen.blendRect(0,
						 cur_hi_top_pos + scroll_offset_px + 2,
						 MMScreenBufferConf::viewWidth,
						 lineheight,
						 Colors::cyan.Rgb565(),
						 0.6f);

		//Names of patches
		screen.setTextColor(Colors::black);
		int16_t y_pos = y_offset + scroll_offset_px;
		for (unsigned i = 0; i < PatchList::NumPatches; i++) {
			if (y_pos < y_offset) {
				y_pos += lineheight;
				continue;
			}
			screen.setCursor(2, y_pos);
			screen.print(patch_list.get_patch_name(i));
			y_pos += lineheight;
		}
	}

	void stop_page() {}

	uint8_t hi_patch_index;
	int32_t animation_ctr;
	int32_t animation_step_size;
	int16_t cur_hi_top_pos;
	int16_t dest_hi_top_pos;
	int16_t scroll_offset_px;

	const int32_t num_animation_steps = 6;
	const int32_t lineheight = 24;
	const int32_t y_offset = 48;
};

} // namespace MetaModule
