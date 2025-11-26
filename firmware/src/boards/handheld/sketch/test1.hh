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
		// test_benchmark();

		// test_rect_bounds();
		// test_stroke_align();
		// test_ellipses();

		// test_transformed_rect();
		// test_transformed_ellipses();

		// test_rotated_rects_ellipses();

		// test_rand_rects();

		test_shapes();
	}

	void test_rotated_rects_ellipses() {
		rectMode(CENTER);
		strokeWeight(1);
		stroke(255, 0, 0);

		pushMatrix();
		translate(100, 50);
		fill(0, 0, 255);
		rect(0, 0, 100, 75);
		popMatrix();

		pushMatrix();
		translate(100, 150);
		rotate(1.0 / 360.0 * TWO_PI);
		fill(0, 255, 255);
		rect(0, 0, 100, 75);
		popMatrix();

		pushMatrix();
		//green
		fill(0, 255, 0);
		translate(100, 250);
		rotate(45.0 / 360.0 * TWO_PI);
		rect(0, 0, 100, 75);
		popMatrix();

		pushMatrix();
		fill(0, 255, 0);
		translate(100, 349);
		rotate(90.0 / 360.0 * TWO_PI);
		rect(0, 0, 100, 75);
		popMatrix();

		// ellipses:
		auto draw_ellipses = [this]() {
			pushMatrix();
			translate(100, 50);
			fill(0, 0, 255);
			ellipse(0, 0, 100, 75);
			popMatrix();

			pushMatrix();
			translate(100, 150);
			rotate(1 / 360.0 * TWO_PI);
			fill(0, 255, 255);
			ellipse(0, 0, 100, 75);
			popMatrix();

			pushMatrix();
			fill(0, 255, 0);
			translate(100, 250);
			rotate(ctr / 360.0 * TWO_PI);
			ellipse(0, 0, 100, 75);
			popMatrix();

			pushMatrix();
			fill(0, 255, 0);
			translate(100, 349);
			rotate(90.0 / 360.0 * TWO_PI);
			ellipse(0, 0, 100, 75);
			popMatrix();
		};

		// low res (diamond)
		pushMatrix();
		setTransformResolution(4);
		translate(150, 0);
		draw_ellipses();
		popMatrix();

		// med res
		pushMatrix();
		setTransformResolution(8);
		translate(250, 0);
		draw_ellipses();
		popMatrix();

		pushMatrix();
		setTransformResolution(16);
		translate(350, 0);
		draw_ellipses();
		popMatrix();

		pushMatrix();
		setTransformResolution(32);
		translate(450, 0);
		draw_ellipses();
		popMatrix();

		pushMatrix();
		setTransformResolution(64);
		translate(550, 0);
		draw_ellipses();
		popMatrix();

		pushMatrix();
		setTransformResolution(128);
		translate(650, 0);
		draw_ellipses();
		popMatrix();

		pushMatrix();
		setTransformResolution(128);
		translate(850, 100);
		fill(200, 200, 63);
		noStroke();
		rotate(ctr * 2 / 360.0 * TWO_PI);
		ellipse(0, 0, 100, 75);
		popMatrix();

		pushMatrix();
		setTransformResolution(128);
		translate(850, 200);
		fill(127, 63, 0);
		strokeWeight(1);
		stroke(255);
		rotate(ctr * 2 / 360.0 * TWO_PI);
		ellipse(0, 0, 100, 75);
		popMatrix();

		pushMatrix();
		setTransformResolution(128);
		translate(850, 300);
		noFill();
		strokeWeight(20);
		rotate(ctr * 2 / 360.0 * TWO_PI);
		ellipse(0, 0, 100, 75);
		popMatrix();

		ctr++;
		if (ctr >= 360)
			ctr = 0;
	}

	void test_transformed_rect() {
		rectMode(CORNER);
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

	void test_transformed_ellipses() {
		ellipseMode(CORNER);

		strokeWeight(0);

		// green rect in upper left
		fill(0, 127, 0);
		ellipse(0, 0, 100, 100);

		// yellow square touching green's bottom-right corner
		pushMatrix();
		translate(100, 100);
		fill(127, 127, 0);
		ellipse(0, 0, 100, 100);
		popMatrix();

		// White ellipseangle nested between yellow and green
		// 1px gap between yellow and white
		// no gap between green and white
		pushMatrix();
		scale(2, 1.5);
		fill(127, 127, 127);
		ellipse(50, 33, 50, 33);
		popMatrix();

		// Cyan ellipse continues stair-case pattern
		// 1px gap between cyan and yellow
		// checks translate() then scale()
		pushMatrix();
		translate(101, 50);
		scale(2, 1.5);
		fill(0, 127, 127);
		ellipse(50, 33, 50, 33);
		popMatrix();

		// purple ellipse, meets cyan ellipse like a half-height step.
		// checks scale() then translate()
		pushMatrix();
		scale(2, 1.5);
		translate(101, 50);
		fill(127, 0, 127);
		ellipse(50, 33, 50, 33);
		popMatrix();

		// Blue and gold 50x50 squares in checkerboard
		// checks nested matrices
		pushMatrix();
		fill(0, 0, 127);
		translate(-300, -100);
		ellipse(300, 300, 50, 50);
		pushMatrix();
		translate(50, 50);
		ellipse(300, 300, 50, 50);
		pushMatrix();
		translate(50, 50);
		ellipse(300, 300, 50, 50);
		pushMatrix();
		translate(50, 50);
		ellipse(300, 300, 50, 50);
		fill(60, 60, 0);
		ellipse(400, 300, 50, 50);
		popMatrix();
		ellipse(400, 300, 50, 50);
		popMatrix();
		ellipse(400, 300, 50, 50);
		popMatrix();
		ellipse(400, 300, 50, 50);
		popMatrix();
	}

	void test_benchmark() {
		// Benchmark test:
		// draw and swap:
		// Normal_NonCache, with clear/inval: 1.51ms (looks perfect)
		// Normal_NonCache, no clear/inval: 0.84ms (looks perfect) <<<<<<<<<<<<< best
		// Normal, with clear/inval: 1.97ms (ants)
		// Normal, no clear/inval: 0.96ms (bad streaking)
		// Normal_RW_Shared, with clear/inval: 1.97 (ants)
		// Normal_RW_Shared, no clear/inval: 0.96 (bad streaking)
		// Normal_StronglyOrdered, with clear/inval: 1.7 (bad ants)
		// Normal_StronglyOrdered, no clear/inval: 1.06 (bad ants)
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

		fill(255);
		noStroke();
		ellipseMode(Handheld::CENTER);
		ellipse(10, 10, 9, 9);

		ellipseMode(CENTER);
		fill(255, 0, 0);
		stroke(255);
		strokeWeight(20.f);
		ellipse(480, 150, 100, 50);

		fill(255, 0, 0);
		stroke(255);
		strokeWeight(0.f);
		ellipse(480, 250, 120, 70);

		noFill();
		stroke(255);
		strokeWeight(1.f);
		ellipse(480, 50, 120, 70);

		strokeWeight(20.f);
		fill(255, 0, 0);
		ellipseMode(CORNER);
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
			stroke(std::rand() & 0xFF, std::rand() & 0xFF, std::rand() & 0xFF);
			strokeWeight(std::rand() & 0x1F);
			if (std::rand() & 0b1)
				rect(std::rand() % 900, std::rand() % 400, std::rand() % 400, std::rand() % 200);
			else
				ellipse(std::rand() % 900, std::rand() % 400, std::rand() % 400, std::rand() % 200);
		}
	}

	void test_ellipses() {
		// small ellipse in top corner
		fill(255);
		noStroke();
		ellipseMode(Handheld::CENTER);
		ellipse(10, 10, 9, 9);

		rectMode(CENTER);

		// 50x50 ellipse + 20 stroke => 70x70 outer size
		// is 30x30 inner size, 70x70 outer size

		// centered for reference
		ellipseMode(CENTER);
		fill(255, 0, 0);
		stroke(255);
		strokeWeight(20.f);
		ellipse(480, 150, 100, 50);
		// rect(480, 150, 100, 50);

		fill(255, 0, 0);
		stroke(255);
		strokeWeight(0.f);
		ellipse(480, 250, 120, 70);
		// rect(480, 250, 120, 70);

		noFill();
		stroke(255);
		strokeWeight(1.f);
		ellipse(480, 50, 120, 70);

		//thin stroke
		fill(0, 255, 0);
		stroke(255);
		strokeWeight(1.f);
		ellipse(480, 345, 120, 50);
		// rect(480, 345, 120, 50);

		// reset
		strokeWeight(20.f);
		fill(255, 0, 0);
		ellipseMode(CORNER);
		rectMode(CORNER);

		// left side
		ellipse(-40, 0, 50, 50);
		ellipse(-30, 100, 50, 50);
		ellipse(-20, 200, 50, 50);
		ellipse(-10, 300, 50, 50);

		// right side
		ellipse(950, 0, 50, 50);
		ellipse(940, 100, 50, 50);
		ellipse(930, 200, 50, 50);
		ellipse(920, 300, 50, 50);

		// top side
		ellipse(100, -50, 50, 50); // visible half of stroke
		ellipse(200, -40, 50, 50); // visible all of stroke
		ellipse(300, -30, 50, 50); // visible < half center
		ellipse(600, -20, 50, 50); // visible > half center
		ellipse(700, -10, 50, 50); // visible exactly entire filled portion
		ellipse(800, 0, 50, 50);   // visible all but the top half of stroke

		// bottom side
		ellipse(100, 400, 50, 50);
		ellipse(200, 390, 50, 50);
		ellipse(300, 380, 50, 50);
		ellipse(600, 370, 50, 50);
		ellipse(700, 360, 50, 50);
		ellipse(800, 350, 50, 50);
	}

	void test_shapes() {
		noFill();

		// open shape
		strokeWeight(1);
		stroke(0, 255, 0);
		beginShape();
		vertex(10, 10);
		vertex(50, 50);
		vertex(100, 30);
		vertex(150, 70);
		endShape(OPEN);

		// open shape, thick stroke
		strokeWeight(20);
		stroke(0, 255, 0);
		beginShape();
		vertex(10, 110);
		vertex(50, 150);
		vertex(100, 130);
		vertex(150, 170);
		endShape(OPEN);

		// filled, no stroke concave shape, rotated
		fill(255, 0, 0);
		stroke(0, 0, 255);
		noStroke();
		pushMatrix();
		translate(width / 2.f, height / 2.f);
		rotate(90.f / 360.f * TWO_PI);
		beginShape();
		vertex(0, -50);
		vertex(50, 50);
		vertex(0, 35);
		vertex(-50, 50);
		endShape(CLOSE);
		popMatrix();

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
