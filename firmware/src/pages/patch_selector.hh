#pragma once
#include "pages/base.hh"
#include "pages/fonts.hh"
#include "pages/page_widgets.hh"
#include "pages/scroll_box.hh"

namespace MetaModule
{

struct PatchSelectorPage : PageBase, public ScrollBox<PatchSelectorPage> {
	using ScrollBoxT = ScrollBox<PatchSelectorPage>;

	PatchSelectorPage(PatchInfo info, ScreenFrameBuffer &screen)
		: PageBase{info, screen}
		, ScrollBoxT{screen,
					 {
						 .bounding_box = box,
						 .show_scrollbar = true,
						 .scroll_method = ScrollMethod::BySelection,
						 .highlight = Colors::cyan,
						 .lineheight = lineheight,
						 .num_animation_steps = 6,
					 }}
	{}

	void focus()
	{
		active_patch_idx = patch_list.cur_patch_index();
		ScrollBoxT::set_num_items(patch_list.NumPatches);
		ScrollBoxT::focus();
		ScrollBoxT::set_selection(active_patch_idx);
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
		auto active_patch_top_y = get_item_top(active_patch_idx);
		if (active_patch_top_y >= box.top && (active_patch_top_y + lineheight) <= box.bottom) {
			screen.blendRect(0, active_patch_top_y, box.width(), lineheight, Colors::green.Rgb565(), 0.4f);
		}

		ScrollBoxT::draw_scroll_box();
	}

	void check_rotary()
	{
		auto rotary = metaparams.rotary.use_motion();
		if (rotary > 0)
			ScrollBoxT::animate_next();
		if (rotary < 0)
			ScrollBoxT::animate_prev();

		if (metaparams.rotary_button.is_just_released())
			start_changing_patch(ScrollBoxT::get_selection());

		handle_changing_patch();
	}

	void draw_scrollbox_element(int32_t i)
	{
		screen.setTextColor(Colors::black);
		screen.print(patch_list.get_patch_name(i));
	}

	void start_changing_patch(int32_t new_patch_index)
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

	void blur() {}

	int32_t active_patch_idx = 0;
	static constexpr int32_t lineheight = 24;
	static constexpr RectC box{
		.left = 0, .top = 44, .right = MMScreenBufferConf::viewWidth, .bottom = MMScreenBufferConf::viewHeight};
};

} // namespace MetaModule
