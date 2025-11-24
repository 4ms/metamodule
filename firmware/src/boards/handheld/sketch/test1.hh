#pragma once
#include "sketch.hh"

#include "conf/debug_raw.h"

namespace Handheld
{

class Test1 : public Sketch {
public:
	int ctr = 0;

	void setup() {
		colorMode(RGB, 255, 255, 255);
		// rectMode(CENTER);
	}

	void draw() {
		background(0);
		stroke(127, 127, 127);

		strokeWeight(20);
		fill(255, 0, 0); //grey stroked, red filled
		rect(100, 100, 100, 100);

		strokeWeight(0);
		fill(0, 255, 0); //no-stroked, green filled
		rect(100, 200, 100, 100);

		strokeWeight(2);
		fill(0, 0, 255); //thin-stroked, blue filled
		rect(400, 200, 100, 100);

		stroke(200, 200, 200);
		strokeWeight(20.f);
		fill(23, 205, 40);
		rect(30, 60, 100, 200);

		strokeWeight(2.f);
		fill(122, 76, 16);
		rect(630, 60, 200, 100);

		// 		for (int i = 0; i < 100; i++) {
		// 			fill(std::rand() & 0xFF, std::rand() & 0xFF, std::rand() & 0xFF);
		// 			rect(std::rand() % 900, std::rand() % 400, std::rand() % 400, std::rand() % 200);
		// 		}

		// noFill();
		// stroke(0, 255, 0);
		// beginShape();
		// vertex(10 + ctr % width, 10);
		// vertex(50 + ctr % width, 50);
		// vertex(100 + ctr % width, 30);
		// vertex(150 + ctr % width, 70);
		// endShape(OPEN);

		// Draw a concave shape
		// fill(255, 0, 0);
		// stroke(0, 0, 255);
		// strokeWeight(40);
		// pushMatrix();
		// translate(width / 2, height / 2);
		// rotate(90.f / 360.f * TWO_PI);
		// beginShape();
		// vertex(0, -50);
		// vertex(50, 50);
		// vertex(0, 35);
		// vertex(-50, 50);
		// endShape(CLOSE);
		// popMatrix();

		// fill(255, 0, 0);
		// stroke(0, 0, 255);
		// strokeWeight(0);
		// pushMatrix();
		// translate(width / 2 + 100, height / 2);
		// rotate(90.f / 360.f * TWO_PI);
		// beginShape();
		// vertex(0, -50);
		// vertex(50, 50);
		// vertex(0, 35);
		// vertex(-50, 50);
		// endShape(CLOSE);
		// popMatrix();

		// fill(255, 0, 0);
		// stroke(0, 0, 255);
		// strokeWeight(0);
		// pushMatrix();
		// translate(width / 2 - 100, height / 2);
		// scale(1.5f);
		// beginShape();
		// vertex(0, -50);
		// vertex(50, 50);
		// vertex(0, 35);
		// vertex(-50, 50);
		// endShape(CLOSE);
		// popMatrix();

		// ctr += 4;
	}

	void audio() {
	}
};

} // namespace Handheld
