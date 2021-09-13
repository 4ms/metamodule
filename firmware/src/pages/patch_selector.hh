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
		metaparams.rotary.use_motion(); //?? why?

		if ((int32_t)patch_list.NumPatches <= (MMScreenBufferConf::viewHeight - y_offset) / lineheight)
			scroll_offset_px = 0;
		else if (scroll_offset_px > ((int32_t)MMScreenBufferConf::viewHeight - lineheight - cur_sel_patch_top_y)) {
			scroll_offset_px = MMScreenBufferConf::viewHeight - lineheight - cur_sel_patch_top_y;
		} else if (scroll_offset_px < y_offset - cur_sel_patch_top_y) {
			scroll_offset_px = y_offset - cur_sel_patch_top_y;
		}
	}

	int32_t idx_to_top_y(int32_t idx)
	{
		return idx * lineheight + y_offset;
	}

	void start()
	{
		selected_patch_idx = patch_list.cur_patch_index();
		active_patch_idx = selected_patch_idx;

		cur_sel_patch_top_y = idx_to_top_y(selected_patch_idx);
		dst_sel_patch_top_y = cur_sel_patch_top_y;
		animation_ctr = 0;
		scroll_offset_px = 0;
		calc_scroll_offset();
	}

	void change_patch()
	{
		//Start changing patch
		auto rotary = metaparams.rotary.use_motion();
		if (rotary) {
			if (rotary < 0)
				mbox.new_patch_index = patch_list.prev_patch();
			else
				mbox.new_patch_index = patch_list.next_patch();
			mbox.loading_new_patch = true;
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

	void check_rotary()
	{
		auto rotary = metaparams.rotary.use_motion();
	}

	void draw()
	{
		check_rotary();

		if (selected_patch_idx != patch_list.cur_patch_index()) {
			selected_patch_idx = patch_list.cur_patch_index();
			dst_sel_patch_top_y = patch_list.cur_patch_index() * lineheight + y_offset;
			animation_step_size = (dst_sel_patch_top_y - cur_sel_patch_top_y) / num_animation_steps;
			animation_ctr = num_animation_steps;
		}

		screen.fill(Colors::white);
		PageWidgets::setup_header(screen);
		screen.print("Select a patch:");
		screen.setFont(PageWidgets::subheader_font);
		screen.drawHLine(0, y_offset, MMScreenBufferConf::viewWidth, Colors::grey.Rgb565());

		//Print scroll bar up/down arrows
		if (scroll_offset_px < 0)
			screen.printf_at(MMScreenBufferConf::viewWidth - 10, y_offset, "^");
		if (patch_list.NumPatches * lineheight + scroll_offset_px >
			((int32_t)MMScreenBufferConf::viewHeight - y_offset))
			screen.printf_at(MMScreenBufferConf::viewWidth - 10, 210, "v");

		if (animation_ctr) {
			animation_ctr--;
			cur_sel_patch_top_y += animation_step_size;
		} else
			cur_sel_patch_top_y = dst_sel_patch_top_y;

		calc_scroll_offset();

		//Highlight bar
		screen.blendRect(0,
						 cur_sel_patch_top_y + scroll_offset_px + 2,
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
			if (y_pos > MMScreenBufferConf::viewHeight)
				break;
			screen.setCursor(2, y_pos);
			screen.print(patch_list.get_patch_name(i));
			y_pos += lineheight;
		}
	}

	void stop_page() {}

	uint8_t selected_patch_idx;
	uint8_t active_patch_idx;

	int32_t animation_ctr;
	int32_t animation_step_size;
	int16_t cur_sel_patch_top_y;
	int16_t dst_sel_patch_top_y;
	int16_t scroll_offset_px;

	const int32_t num_animation_steps = 6;
	const int32_t lineheight = 24;
	static constexpr int32_t y_offset = 44;
	static constexpr int32_t scrollbox_size = MMScreenBufferConf::viewHeight - y_offset;
};

class Rect {
	int32_t x;
	int32_t y;
	int32_t width;
	int32_t height;
};

template<size_t MaxItems>
class ScrollBox {
public:
	struct Options {
		bool show_scrollbar;
		Color highlight;
	};
	ScrollBox(Rect bounding_box, Options options);
	void add_text_item(std::string str);
	void add_text_item(const char *str);
	void add_graphic_item();

	int32_t get_num_items();

private:
	Rect box;
	Options opts;
	int32_t num_items;
	int32_t lineheights[MaxItems];
};

} // namespace MetaModule
