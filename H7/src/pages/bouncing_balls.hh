#pragma once
#include "bouncing_ball.hh"
#include "page_manager.hh"

namespace MetaModule
{

struct BouncingBallsPage : DisplayPage {
	BouncingBallsPage() = delete;

	static inline BouncingBall balls[3] = {
		{60, {220, 30}, {-1, 1}, {239, 239}},
		{50, {20, 10}, {2, -1}, {239, 239}},
		{40, {10, 220}, {2, 3}, {239, 239}},
	};

	static inline Color ball_colors[3] = {
		Colors::red,
		Colors::black,
		Colors::orange,
	};

	static void draw(PageManager *pm)
	{
		pm->screen.fill(pm->bgcolor);
		int i = 0;
		for (auto &ball : balls) {
			ball.update();
			auto pos = ball.get_pos();
			pm->screen.fillCircle(pos.x, pos.y, ball.get_radius(), ball_colors[i].Rgb565());
			i++;
		}
	}
};
} // namespace MetaModule
