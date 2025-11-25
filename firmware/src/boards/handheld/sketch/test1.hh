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
	}

	void draw() {
		background(0);
		// test_rect_bounds();
		// test_stroke_align();
		// test_transformed_rect();

		test_ellipses();
	}

	void test_transformed_rect() {
		strokeWeight(0);

		// green rect in upper left
		fill(0, 255, 0);
		rect(0, 0, 100, 100);

		// yellow square touching green's bottom-right corner
		pushMatrix();
		translate(100, 100);
		fill(255, 255, 0);
		rect(0, 0, 100, 100);
		popMatrix();

		// White rectangle nested between yellow and green
		// 1px gap between yellow and white
		// no gap between green and white
		pushMatrix();
		scale(2, 1.5);
		fill(255, 255, 255);
		rect(50, 33, 50, 33);
		popMatrix();

		// Cyan rect continues stair-case pattern
		// 1px gap between cyan and yellow
		// checks translate() then scale()
		pushMatrix();
		translate(101, 50);
		scale(2, 1.5);
		fill(0, 255, 255);
		rect(50, 33, 50, 33);
		popMatrix();

		// purple rect, meets cyan rect like a half-height step.
		// checks scale() then translate()
		pushMatrix();
		scale(2, 1.5);
		translate(101, 50);
		fill(127, 0, 255);
		rect(50, 33, 50, 33);
		popMatrix();

		// Blue and gold 50x50 squares in checkerboard
		// checks nested matrices
		pushMatrix();
		fill(0, 0, 255);
		translate(-300, -100);
		rect(300, 300, 50, 50);
		pushMatrix();
		translate(50, 50);
		rect(300, 300, 50, 50);
		pushMatrix();
		translate(50, 50);
		rect(300, 300, 50, 50);
		pushMatrix();
		translate(50, 50);
		rect(300, 300, 50, 50);
		fill(127, 127, 0);
		rect(400, 300, 50, 50);
		popMatrix();
		rect(400, 300, 50, 50);
		popMatrix();
		rect(400, 300, 50, 50);
		popMatrix();
		rect(400, 300, 50, 50);
		popMatrix();
	}

	void test_benchmark() {
		// Benchmark test:
		stroke(127, 127, 127);

		strokeWeight(20);
		fill(255, 0, 0); //grey stroked, red filled
		rect(100, 100, 100, 100);

		strokeWeight(0);
		fill(0, 255, 0); //no-stroked, green filled
		rect(100, 200, 100, 100);

		strokeWeight(1);
		fill(0, 0, 255); //thin-stroked, blue filled
		rect(400, 200, 100, 100);

		stroke(200, 200, 200);
		strokeWeight(20.f);
		fill(23, 205, 40);
		rect(30, 60, 100, 200);

		strokeWeight(2.f);
		fill(122, 76, 16);
		rect(630, 60, 200, 100);
	}

	void test_rect_bounds() {
		// rect bounds tests

		stroke(255);
		strokeWeight(20.f);
		// 50x50 rect + 20 stroke => 70x70 outer size
		// is 30x30 inner size, 70x70 outer size
		fill(255, 0, 0);

		// centered for reference
		rectMode(CENTER);
		rect(480, 150, 50, 50);

		strokeWeight(0.f);
		rect(480, 250, 70, 70);

		strokeWeight(20.f);
		rectMode(CORNER);

		// left side
		rect(-40, 0, 50, 50);
		rect(-30, 100, 50, 50);
		rect(-20, 200, 50, 50);
		rect(-10, 300, 50, 50);

		// right side
		rect(950, 0, 50, 50);
		rect(940, 100, 50, 50);
		rect(930, 200, 50, 50);
		rect(920, 300, 50, 50);

		// top side
		rect(100, -50, 50, 50);
		rect(200, -40, 50, 50);
		rect(300, -30, 50, 50);
		rect(400, -20, 50, 50);
		rect(500, -10, 50, 50);
		rect(600, 0, 50, 50);

		// bottom side
		rect(100, 400, 50, 50);
		rect(200, 390, 50, 50);
		rect(300, 380, 50, 50);
		rect(400, 370, 50, 50);
		rect(500, 360, 50, 50);
		rect(600, 350, 50, 50);
	}

	void test_stroke_align() {

		// Stroke alignment test:
		// Two pairs of squares:

		// Pair 1:
		// Left sides should be aligned
		// Right side of stroked rect should be 1px to the right of right side of unstroked rect
		strokeWeight(0);
		fill(0, 255, 0);
		rect(200, 200, 100, 100);

		strokeWeight(1);
		stroke(255);
		fill(0, 0, 255);
		rect(200, 250, 100, 100);

		// Pair 2:
		// Top sides should be aligned
		// Bottom side of stroked rect should be 1px below the bottom of unstroked rect
		strokeWeight(0);
		fill(0, 255, 0);
		rect(400, 200, 100, 100);

		strokeWeight(1);
		stroke(255);
		fill(0, 0, 255);
		rect(450, 200, 100, 100);
	}

	void test_rand_rects() {
		for (int i = 0; i < 100; i++) {
			fill(std::rand() & 0xFF, std::rand() & 0xFF, std::rand() & 0xFF);
			rect(std::rand() % 900, std::rand() % 400, std::rand() % 400, std::rand() % 200);
		}
	}

	void test_ellipses() {
		// 50x50 ellipse + 20 stroke => 70x70 outer size
		// is 30x30 inner size, 70x70 outer size
		fill(255, 0, 0);
		stroke(255);
		strokeWeight(20.f);

		// centered for reference
		ellipseMode(CENTER);
		ellipse(480, 150, 100, 50);

		strokeWeight(0.f);
		ellipse(480, 250, 120, 70);

		strokeWeight(20.f);
		ellipseMode(CORNER);

		// left side
		ellipse(-40, 0, 50, 50);
		ellipse(-30, 100, 50, 50);
		ellipse(-20, 200, 50, 50);
		ellipse(-10, 300, 50, 50);

		// // right side
		// ellipse(950, 0, 50, 50);
		// ellipse(940, 100, 50, 50);
		// ellipse(930, 200, 50, 50);
		// ellipse(920, 300, 50, 50);

		// // top side
		// ellipse(100, -50, 50, 50);
		// ellipse(200, -40, 50, 50);
		// ellipse(300, -30, 50, 50);
		// ellipse(400, -20, 50, 50);
		// ellipse(500, -10, 50, 50);
		// ellipse(600, 0, 50, 50);

		// // bottom side
		// ellipse(100, 400, 50, 50);
		// ellipse(200, 390, 50, 50);
		// ellipse(300, 380, 50, 50);
		// ellipse(400, 370, 50, 50);
		// ellipse(500, 360, 50, 50);
		// ellipse(600, 350, 50, 50);
	}

	void test_shapes() {
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
