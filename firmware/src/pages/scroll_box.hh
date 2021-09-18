#include "pages/geometry.hh"
#include "screen_buffer.hh"
#include "util/colors.hh"

namespace MetaModule
{

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
		if (selected_item_idx < 0 || selected_item_idx >= opts.num_items)
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
		if (item_top(opts.num_items) <= box.height())
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
		if (item_top(opts.num_items) + scroll_offset_px > box.height())
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

		int16_t y_pos = box.top + scroll_offset_px;
		for (int i = 0; i < opts.num_items; i++) {
			if ((y_pos + item_line_height(i)) < box.top) {
				y_pos += item_line_height(i);
				continue;
			}
			if (y_pos > box.bottom)
				break;
			_screen.setCursor(LeftMargin, y_pos);
			static_cast<ParentWidget *>(this)->draw_scrollbox_element(i);
			y_pos += item_line_height(i);
		}
		_screen.clear_clip_rect();
	}

	void animate_next()
	{
		selected_item_idx = selected_item_idx == opts.num_items - 1 ? 0 : selected_item_idx + 1;
		_animate_to_selection();
	}

	void animate_prev()
	{
		selected_item_idx = selected_item_idx == 0 ? opts.num_items - 1 : selected_item_idx - 1;
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

} // namespace MetaModule
