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
		active_patch_idx = patch_list.cur_patch_index();
		if (selected_patch_idx < 0 || selected_patch_idx >= patch_list.NumPatches)
			selected_patch_idx = active_patch_idx;

		cur_sel_patch_top_y = idx_to_top_y(selected_patch_idx);
		dst_sel_patch_top_y = cur_sel_patch_top_y;
		animation_ctr = 0;
		scroll_offset_px = 0;
		calc_scroll_offset();
	}

	void draw()
	{
		check_rotary();

		screen.fill(Colors::white);
		PageWidgets::setup_header(screen);
		screen.print("Select a patch:");
		screen.setFont(PageWidgets::subheader_font);
		screen.drawHLine(0, box.top, box.width(), Colors::grey.Rgb565());

		screen.set_clip_rect(box);

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

		//Selection Highlight bar
		screen.blendRect(
			0, cur_sel_patch_top_y + scroll_offset_px + 2, box.width(), lineheight, Colors::cyan.Rgb565(), 0.6f);

		//Active Patch Highlight bar
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

	void start_changing_patch(uint32_t new_patch_index)
	{
		if (!mbox.loading_new_patch && (new_patch_index != patch_list.cur_patch_index())) {
			mbox.new_patch_index = new_patch_index;
			mbox.loading_new_patch = true;
		}
	}

	void handle_changing_patch()
	{
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

		if (metaparams.rotary_button.is_just_released()) {
			start_changing_patch(selected_patch_idx);
		}
		handle_changing_patch();
	}

	void calc_scroll_offset()
	{
		//Clear any pending motion //don't need this anymore, right?
		// metaparams.rotary.use_motion();

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

template<typename ParentWidget>
class ScrollBox {
public:
	struct Options {
		RectC bounding_box;
		int32_t num_items;
		bool show_scrollbar;
		Color highlight;
		int32_t lineheight;
		int32_t num_animation_steps;
	};

	ScrollBox(ScreenFrameBuffer &screen, Options options)
		: _screen{screen}
		, box{options.bounding_box}
		, opts{options} {};

	void set_selection(int32_t idx)
	{
		selected_item_idx = idx;
	}

	int32_t get_selection()
	{
		return selected_item_idx;
	}

	void focus()
	{
		if (selected_item_idx < 0 || selected_item_idx >= num_items)
			selected_item_idx = 0;

		cur_selected_item_top_y = item_abs_top(selected_item_idx);
		dst_selected_item_top_y = cur_selected_item_top_y;
		animation_ctr = 0;
		scroll_offset_px = 0;
		calc_scroll_offset();
	}

	void blur() {}

	int32_t item_line_height(int itemnum)
	{
		return opts.lineheight;
		//return line_heights[itemnum];
	}

	int32_t item_top(int itemnum)
	{
		return opts.lineheight * itemnum;
		//return line_abs_pos[itemnum]; //make sure last element is bottom of last item
	}

	int32_t item_abs_top(int32_t idx)
	{
		return item_top(idx) + box.top;
	}

	int32_t get_item_top(int32_t idx)
	{
		return item_abs_top(idx) + scroll_offset_px + ItemTopMargin;
	}

	void calc_scroll_offset()
	{
		auto cur_selected_item_bottom_y = cur_selected_item_top_y + item_line_height(selected_item_idx);
		//Disable scrolling if all items fit on the screen
		if (item_top(num_items) <= box.height())
			scroll_offset_px = 0;

		//Scroll up or down if scroll_offset_px puts cur_selected_item off-screen:
		else if ((scroll_offset_px + cur_selected_item_bottom_y) > box.bottom) {
			scroll_offset_px = box.bottom - cur_selected_item_bottom_y;
		} else if ((scroll_offset_px + cur_selected_item_top_y) < box.top) {
			scroll_offset_px = box.top - cur_selected_item_top_y;
		}
	}

	void draw_scroll_box()
	{
		_screen.set_clip_rect(box);

		//Print scroll bar up/down arrows
		if (scroll_offset_px < 0)
			_screen.printf_at(box.right - 10, box.top, "^");
		if (item_top(num_items) + scroll_offset_px > box.height())
			_screen.printf_at(box.right - 10, 210, "v");

		// Step animation
		if (animation_ctr) {
			animation_ctr--;
			cur_selected_item_top_y += animation_step_size;
		} else
			cur_selected_item_top_y = dst_selected_item_top_y;

		calc_scroll_offset();

		//Selection Highlight bar
		_screen.blendRect(0,
						  cur_selected_item_top_y + scroll_offset_px + ItemTopMargin,
						  box.width(),
						  item_line_height(selected_item_idx),
						  opts.highlight.Rgb565(),
						  0.6f);

		//Names of patches
		_screen.setTextColor(Colors::black);
		int16_t y_pos = box.top + scroll_offset_px;
		for (unsigned i = 0; i < num_items; i++) {
			if ((y_pos + item_line_height(i)) < box.top) {
				y_pos += item_line_height(i);
				continue;
			}
			if (y_pos > box.bottom)
				break;
			_screen.setCursor(LeftMargin, y_pos);
			static_cast<ParentWidget &>(*this).draw_scrollbox_element(i);
			y_pos += item_line_height(i);
		}
		_screen.clear_clip_rect();
	}

	void animate_next()
	{
		selected_item_idx = selected_item_idx == num_items - 1 ? 0 : selected_item_idx + 1;
		_animate_to_selection();
	}

	void animate_prev()
	{
		selected_item_idx = selected_item_idx == 0 ? num_items - 1 : selected_item_idx - 1;
		_animate_to_selection();
	}

private:
	void _animate_to_selection()
	{
		dst_selected_item_top_y = item_abs_top(selected_item_idx);
		animation_step_size = (dst_selected_item_top_y - cur_selected_item_top_y) / opts.num_animation_steps;
		animation_ctr = opts.num_animation_steps;
	}

private:
	ScreenFrameBuffer &_screen;
	RectC box;
	Options opts;
	int32_t num_items = 0;
	int32_t scroll_offset_px;
	int32_t selected_item_idx = 0;
	int32_t cur_selected_item_top_y;
	int32_t dst_selected_item_top_y;
	int32_t animation_ctr = 0;
	int32_t animation_step_size;

	static constexpr int32_t LeftMargin = 2;
	static constexpr int32_t ItemTopMargin = 2;

	// int32_t line_heights[MaxItems];
	// int32_t line_abs_pos[MaxItems];
};

struct PatchScrollPage : public ScrollBox<PatchScrollPage>, PageBase {
	PatchScrollPage(PatchInfo info, ScreenFrameBuffer &screen)
		: PageBase{info, screen}
		, ScrollBox<PatchScrollPage>{screen,
									 {
										 .bounding_box = box,
										 .num_items = patch_list.NumPatches,
										 .show_scrollbar = true,
										 .highlight = Colors::cyan,
										 .lineheight = 24,
										 .num_animation_steps = 6,
									 }}
	{}

	void start()
	{
		active_patch_idx = patch_list.cur_patch_index();
		ScrollBox<PatchScrollPage>::focus();
		ScrollBox<PatchScrollPage>::set_selection(active_patch_idx);
	}

	void draw()
	{
		check_rotary();

		screen.fill(Colors::white);
		PageWidgets::setup_header(screen);
		screen.print("Select a patch:");
		screen.setFont(PageWidgets::subheader_font);
		screen.drawHLine(0, box.top, box.width(), Colors::grey.Rgb565());

		//Active Patch Highlight bar
		// auto active_patch_top_y = idx_to_top_y(active_patch_idx) + scroll_offset_px + 2;
		auto active_patch_top_y = get_item_top(active_patch_idx);
		if (active_patch_top_y >= box.top && (active_patch_top_y + lineheight) <= box.bottom) {
			screen.blendRect(0, active_patch_top_y, box.width(), lineheight, Colors::green.Rgb565(), 0.4f);
		}

		ScrollBox<PatchScrollPage>::draw_scroll_box();
	}

	void draw_scrollbox_element(int32_t i)
	{
		screen.setTextColor(Colors::black);
		screen.print(patch_list.get_patch_name(i));
	}

	void start_changing_patch(uint32_t new_patch_index)
	{
		if (!mbox.loading_new_patch && (new_patch_index != patch_list.cur_patch_index())) {
			mbox.new_patch_index = new_patch_index;
			mbox.loading_new_patch = true;
		}
	}

	void handle_changing_patch()
	{
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
			ScrollBox<PatchScrollPage>::animate_next();
		if (rotary < 0)
			ScrollBox<PatchScrollPage>::animate_prev();

		if (metaparams.rotary_button.is_just_released())
			start_changing_patch(ScrollBox<PatchScrollPage>::get_selection());

		handle_changing_patch();
	}

	int32_t idx_to_top_y(int32_t idx)
	{
		return idx * lineheight + box.top;
	}

	void stop_page() {}

	int32_t active_patch_idx = 0;

	const int32_t lineheight = 24;

	static constexpr RectC box{
		.left = 0, .top = 44, .right = MMScreenBufferConf::viewWidth, .bottom = MMScreenBufferConf::viewHeight};
};

} // namespace MetaModule
