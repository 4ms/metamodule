#pragma once

class BouncingBall {

	struct XYVec {
		int x;
		int y;
	};

	int radius;
	XYVec pos;
	XYVec velocity;
	const XYVec bounds;

public:
	BouncingBall(int radius, XYVec initial_pos, XYVec initial_velocity, XYVec bounds)
		: radius{radius}
		, pos{initial_pos}
		, velocity{initial_velocity}
		, bounds{bounds}
	{}

	void update()
	{
		XYVec new_pos{pos.x + velocity.x, pos.y + velocity.y};

		if (new_pos.x - radius <= 0) { // left window edge
			velocity.x *= -1;
			new_pos.x = 0 + radius;
		} else if (new_pos.x + radius >= bounds.x) { // right window edge
			velocity.x *= -1;
			new_pos.x = bounds.x - radius;
		} else if (new_pos.y - radius <= 0) { // top of window
			velocity.y *= -1;
			new_pos.y = 0 + radius;
		} else if (new_pos.y + radius >= bounds.y) { // bottom of window
			velocity.y *= -1;
			new_pos.y = bounds.y - radius;
		}
		pos = new_pos;
	}

	XYVec get_pos()
	{
		return pos;
	}

	float get_radius()
	{
		return radius;
	}
};
