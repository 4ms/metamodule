#pragma once
#include "conf/screen_buffer_conf.hh"
#include "pages/base.hh"
#include "pages/bouncing_ball.hh"

namespace MetaModule
{

struct BouncingBallsPage : PageBase {
	BouncingBallsPage(PatchInfo info)
		: PageBase{info}
	{
		ui = &base_ui;
	}

	struct {
		lv_obj_t *screen;
	} base_ui, *ui;
	bool is_init = false;

	static inline BouncingBall balls[4] = {
		{90, {220, 30}, {-1, 1}, {MMScreenBufferConf::height - 1, MMScreenBufferConf::width - 1}},
		{60, {220, 30}, {-1, 2}, {MMScreenBufferConf::height - 1, MMScreenBufferConf::width - 1}},
		{50, {20, 10}, {2, -1}, {MMScreenBufferConf::height - 1, MMScreenBufferConf::width - 1}},
		{40, {10, 220}, {2, 3}, {MMScreenBufferConf::height - 1, MMScreenBufferConf::width - 1}},
	};

	static inline Color ball_colors[4] = {
		Colors::magenta,
		Colors::yellow,
		Colors::cyan,
		Colors::black,
	};

	void init()
	{
		ui->screen = lv_obj_create(nullptr, nullptr);
		is_init = true;
	}
	void focus(PageChangeDirection dir)
	{
		if (!is_init)
			init();

		auto animation_style = dir == PageChangeDirection::Back	   ? LV_SCR_LOAD_ANIM_MOVE_LEFT :
							   dir == PageChangeDirection::Forward ? LV_SCR_LOAD_ANIM_MOVE_RIGHT :
																	   LV_SCR_LOAD_ANIM_FADE_ON;
		lv_scr_load_anim(ui->screen, animation_style, 500, 0, false);
	}

	void blur() {}
	void update()
	{
		// screen.fill(Colors::white);
		// int i = 0;
		// for (auto &ball : balls) {
		// ball.update();
		// auto pos = ball.get_pos();
		// lv_draw_rect({pos.x, pos.y},
		// 	screen.blend64FillCircle(pos.x, pos.y, ball.get_radius(), ball_colors[i].Rgb565(), 0.5f);
		// i++;
		// }
	}
};
} // namespace MetaModule
