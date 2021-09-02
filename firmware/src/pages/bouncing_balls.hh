#pragma once
#include "pages/base.hh"
#include "pages/bouncing_ball.hh"

namespace MetaModule
{

struct BouncingBallsPage : PageBase {
	BouncingBallsPage(PatchInfo info, ScreenFrameBuffer &screen)
		: PageBase{info, screen}
	{}

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

	void draw()
	{
		screen.fill(Colors::white);
		int i = 0;
		for (auto &ball : balls) {
			ball.update();
			auto pos = ball.get_pos();
			screen.blend64FillCircle(pos.x, pos.y, ball.get_radius(), ball_colors[i].Rgb565(), 0.5f);
			i++;
		}
	}
};
} // namespace MetaModule
