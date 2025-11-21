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
		rectMode(CENTER);
	}

	void draw() {
		background(0);

		// Test stroke width is centered:
		stroke(0, 0, 255); //blue
		fill(85);

		strokeWeight(20);
		fill(255, 0, 0); //red
		ellipse(100, 100, 100, 100);

		strokeWeight(0);
		fill(0, 255, 0); //green
		ellipse(100, 200, 100, 100);

		// noStroke();
		// fill(0, 0, 0);
		// rect(0, 0, width, height);

		// fill(0, 0, 200);
		// stroke(200, 0, 0);
		// strokeWeight(4.f);
		// ellipse((30 + ctr) % width, (60 + ctr * 2) % height, 50, 150);

		// fill(200, 0, 200);
		// noStroke();
		// ellipse((30 + ctr) % width, (60 + ctr * 2) % height, 150, 50);

		// stroke(200, 200, 200);
		// strokeWeight(20.f);
		// fill(23, 205, 40);
		// rect(30, 60, 100, 200);

		// strokeWeight(2.f);
		// fill(122, 76, 16);
		// pushMatrix();
		// rect(630, 60, 200, 100);
		// rotate(((ctr % 20) / 20.f) * 2.f * 3.1416f);
		// translate(ctr % width, 0);
		// popMatrix();

		// noFill();
		// stroke(0, 255, 0);
		// beginShape();
		// vertex(10 + ctr % width, 10);
		// vertex(50 + ctr % width, 50);
		// vertex(100 + ctr % width, 30);
		// vertex(150 + ctr % width, 70);
		// endShape(OPEN);

		// Draw a concave shape
		fill(255, 0, 0);
		stroke(0, 0, 255);
		strokeWeight(40);
		pushMatrix();
		translate(width / 2, height / 2);
		rotate(90.f / 360.f * TWO_PI);
		beginShape();
		vertex(0, -50);
		vertex(50, 50);
		vertex(0, 35);
		vertex(-50, 50);
		endShape(CLOSE);
		popMatrix();

		fill(255, 0, 0);
		stroke(0, 0, 255);
		strokeWeight(0);
		pushMatrix();
		translate(width / 2 + 100, height / 2);
		rotate(90.f / 360.f * TWO_PI);
		beginShape();
		vertex(0, -50);
		vertex(50, 50);
		vertex(0, 35);
		vertex(-50, 50);
		endShape(CLOSE);
		popMatrix();

		// ctr += 4;
	}

	void audio() {
	}
};

} // namespace Handheld
