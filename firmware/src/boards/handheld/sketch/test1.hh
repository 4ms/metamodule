#pragma once
#include "sketch.hh"

namespace Handheld
{

class Test1 : public Sketch {
public:
	int ctr = 0;

	void setup() {
		colorMode(RGB, 255, 255, 255);
		noStroke();
		background(0);
	}

	void draw() {
		fill(0, 0, 0);
		rect(0, 0, width, height);

		fill(255, 0, 0);
		rect((30 + ctr) % width, (60 + ctr * 2) % height, 100, 100);

		fill(23, 205, 40);
		rect(30, 60, 100, 200);

		fill(122, 76, 16);
		rect(630, 60, 200, 100);

		ctr++;
	}

	void audio() {
	}
};

} // namespace Handheld
