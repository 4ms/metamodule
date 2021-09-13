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
		//metaparams.rotary.use_motion(); //?? why?

		//Disable scrolling if the number of lines fits on the screen
		if ((int32_t)patch_list.NumPatches <= (box.height() / lineheight))
			scroll_offset_px = 0;

		//Check if scroll_offset_px puts current selection hightlight bar off-screen:
		else if (scroll_offset_px > (box.bottom - lineheight - cur_sel_patch_top_y)) {
			scroll_offset_px = box.bottom - lineheight - cur_sel_patch_top_y;
		} else if (scroll_offset_px < box.top - cur_sel_patch_top_y) {
			scroll_offset_px = box.top - cur_sel_patch_top_y;
		}
	}

	int32_t idx_to_top_y(int32_t idx)
	{
		return idx * lineheight + box.top;
	}

	void start()
	{
		active_patch_idx = patch_list.cur_patch_index();
		if (selected_patch_idx < 0 || selected_patch_idx >= patch_list.NumPatches)
			selected_patch_idx = active_patch_idx;

		cur_sel_patch_top_y = idx_to_top_y(selected_patch_idx);
		dst_sel_patch_top_y = cur_sel_patch_top_y;
		animation_ctr = 0;
		scroll_offset_px = 0;
		calc_scroll_offset();
	}

	void handle_changing_patch(uint32_t new_patch_index)
	{
		if (!mbox.loading_new_patch && (new_patch_index != patch_list.cur_patch_index())) {
			mbox.new_patch_index = new_patch_index;
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

			active_patch_idx = patch_list.cur_patch_index();
			mbox.loading_new_patch = false;
		}
	}

	void check_rotary()
	{
		auto rotary = metaparams.rotary.use_motion();
		if (rotary > 0)
			selected_patch_idx = selected_patch_idx == patch_list.NumPatches - 1 ? 0 : selected_patch_idx + 1;
		if (rotary < 0)
			selected_patch_idx = selected_patch_idx == 0 ? patch_list.NumPatches - 1 : selected_patch_idx - 1;
		if (rotary) {
			dst_sel_patch_top_y = idx_to_top_y(selected_patch_idx);
			animation_step_size = (dst_sel_patch_top_y - cur_sel_patch_top_y) / NumAnimationSteps;
			animation_ctr = NumAnimationSteps;
		}
	}

	void draw()
	{
		check_rotary();

		screen.fill(Colors::white);
		PageWidgets::setup_header(screen);
		screen.print("Select a patch:");
		screen.setFont(PageWidgets::subheader_font);
		screen.drawHLine(0, box.top, box.width(), Colors::grey.Rgb565());

		//Print scroll bar up/down arrows
		if (scroll_offset_px < 0)
			screen.printf_at(box.right - 10, box.top, "^");
		if (patch_list.NumPatches * lineheight + scroll_offset_px > box.height())
			screen.printf_at(box.right - 10, 210, "v");

		// Step animation
		if (animation_ctr) {
			animation_ctr--;
			cur_sel_patch_top_y += animation_step_size;
		} else
			cur_sel_patch_top_y = dst_sel_patch_top_y;

		calc_scroll_offset();

		screen.set_clip_rect(box);

		//Selection Highlight bar
		screen.blendRect(
			0, cur_sel_patch_top_y + scroll_offset_px + 2, box.width(), lineheight, Colors::cyan.Rgb565(), 0.6f);

		//Active Highlight bar
		auto active_patch_top_y = idx_to_top_y(active_patch_idx) + scroll_offset_px + 2;
		if (active_patch_top_y >= box.top && (active_patch_top_y + lineheight) <= box.bottom) {
			screen.blendRect(0, active_patch_top_y, box.width(), lineheight, Colors::green.Rgb565(), 0.4f);
		}

		//Names of patches
		screen.setTextColor(Colors::black);
		int16_t y_pos = box.top + scroll_offset_px;
		for (unsigned i = 0; i < PatchList::NumPatches; i++) {
			if ((y_pos + lineheight) < box.top) {
				y_pos += lineheight;
				continue;
			}
			if (y_pos > box.bottom)
				break;
			screen.setCursor(2, y_pos);
			screen.print(patch_list.get_patch_name(i));
			y_pos += lineheight;
		}

		screen.clear_clip_rect();
	}

	void stop_page() {}

	int32_t selected_patch_idx{};
	int32_t active_patch_idx{};

	int32_t animation_ctr;
	int32_t animation_step_size;
	int16_t cur_sel_patch_top_y;
	int16_t dst_sel_patch_top_y;
	int16_t scroll_offset_px;

	static constexpr int32_t NumAnimationSteps = 6;
	const int32_t lineheight = 24;

	static constexpr RectC box{
		.left = 0, .top = 44, .right = MMScreenBufferConf::viewWidth, .bottom = MMScreenBufferConf::viewHeight};
};

///////////////////////////////////////////
// WIP: Generic ScrollBox class:
//

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
