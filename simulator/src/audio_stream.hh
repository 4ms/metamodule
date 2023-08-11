#pragma once
#include "frame.hh"
#include <span>

class Player {
	//

public:
	void play(std::span<Frame> buffer) {
		static float x = 0;
		static float y = 0;
		for (auto &sample : buffer) {
			sample.l = x;
			sample.r = y;
			x += 0.0011;
			y += 0.0030;
			if (x > 0.25f)
				x = -0.25f;
			if (y > 0.25f)
				y = -0.25f;
		}
	}
};
