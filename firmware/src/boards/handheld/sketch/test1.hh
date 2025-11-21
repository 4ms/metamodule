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
		noStroke();
		fill(0, 0, 0);
		rect(0, 0, width, height);

		fill(0, 0, 200);
		stroke(200, 0, 0);
		strokeWeight(4.f);
		ellipse((30 + ctr) % width, (60 + ctr * 2) % height, 50, 150);

		fill(200, 0, 200);
		noStroke();
		ellipse((30 + ctr) % width, (60 + ctr * 2) % height, 150, 50);

		stroke(200, 200, 200);
		strokeWeight(20.f);
		fill(23, 205, 40);
		rect(30, 60, 100, 200);

		strokeWeight(2.f);
		fill(122, 76, 16);
		rect(630, 60, 200, 100);

		ctr++;
	}

	void audio() {
	}
};

} // namespace Handheld
