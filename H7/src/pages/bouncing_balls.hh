#pragma once
#include "bouncing_ball.hh"
#include "page_manager.hh"

namespace MetaModule
{

struct BouncingBallsPage : DisplayPage {
	BouncingBallsPage() = delete;

	static inline BouncingBall balls[4] = {
		{90, {220, 30}, {-1, 1}, {239, 239}},
		{60, {220, 30}, {-1, 2}, {239, 239}},
		{50, {20, 10}, {2, -1}, {239, 239}},
		{40, {10, 220}, {2, 3}, {239, 239}},
	};

	static inline Color ball_colors[4] = {
		Colors::magenta,
		Colors::yellow,
		Colors::cyan,
		Colors::black,
	};

	static void draw(PageManager *pm)
	{
		pm->screen.fill(Colors::white);
		int i = 0;
		for (auto &ball : balls) {
			ball.update();
			auto pos = ball.get_pos();
			pm->screen.blend64FillCircle(pos.x, pos.y, ball.get_radius(), ball_colors[i].Rgb565(), 0.5f);
			// pm->screen.fillCircle(pos.x, pos.y, ball.get_radius(), ball_colors[i].Rgb565());
			i++;
		}
	}
};
} // namespace MetaModule
