#pragma once
#include "sketch.hh"

namespace Handheld
{

class Test2 : public Sketch {
public:
	int numLines = 10;

	float baseSize = 40;

	float hueEven = 0;
	float hueOdd = 180;

	float CV1In = 0;
	float CV2In = 0;

	void setup() {
		size(960, 400);
		rectMode(CENTER);
		ellipseMode(CENTER);
		colorMode(HSB, 360, 100, 100);
	}

	void draw() {
		background(0);

		CV1In += 0.01;
		if (CV1In > 0.5) {
			CV1In = -0.5;
			CV2In += 0.01;
			if (CV2In > 0.5)
				CV2In = -0.5;
		}

		float centerX = width / 2;
		float centerY = height / 2;

		// Tunnel expansion driven ONLY by CV1In magnitude
		float audioMag = std::abs(CV1In);
		float tunnelSpeed = map(audioMag, 0.f, 0.5f, 0.f, 0.2f);

		// DIRECT ROTATION CONTROL (NEW)
		float angleFromCV1In = map(CV1In, -0.5f, 0.5f, -M_PI, M_PI); // layer2 rotation
		float angleFromCV2In = map(CV2In, -0.5f, 0.5f, -M_PI, M_PI); // layer1 rotation

		// Morphing sources
		float morphFromCV1In = std::clamp(map(CV1In, -0.5f, 0.5f, 0.f, 2.f), 0.f, 2.f);
		float morphFromCV2In = std::clamp(map(CV2In, -0.5f, 0.5f, 0.f, 2.f), 0.f, 2.f);

		// Color shift
		float hueShift = map(CV2In, -0.5f, 0.5f, -2.f, 2.f);

		for (int i = 0; i < numLines; i++) {

			// Expansion
			float size = baseSize + i * (20 + tunnelSpeed * 200);
			if (tunnelSpeed == 0)
				size = baseSize + i * 20;

			// Rotation (DIRECT CONTROL)
			float angle = (i % 2 == 0) ? angleFromCV2In // even layers rotate from CV2In
										 :
										 angleFromCV1In; // odd layers rotate from CV1In

			// Color logic
			float h;
			if (i % 2 == 0) {
				hueEven = std::fmod(hueEven + hueShift, 360);
				h = std::fmod(hueEven + i * 3, 360);
			} else {
				hueOdd = std::fmod(hueOdd - hueShift, 360);
				h = std::fmod(hueOdd + i * 3, 360);
			}

			// Morph per layer
			float morph = (i % 2 == 0) ? morphFromCV2In // even from CV2In
										 :
										 morphFromCV1In; // odd from CV1In

			pushMatrix();
			translate(centerX, centerY);
			rotate(angle);
			stroke(h, 90, 100);
			noFill();
			strokeWeight(1.2);

			drawMorphShape(size, morph);
			popMatrix();
		}
	}

	void drawMorphShape(float size, float morph) {
		beginShape();

		int steps = 80;
		float r = size / 2.0;

		for (int i = 0; i < steps; i++) {
			float t = map(i, 0, steps, 0, 2.f * M_PI);

			// Circle
			float cx = r * std::cos(t);
			float cy = r * std::sin(t);

			// Square
			float exponentSquare = 20;
			float sx = r * std::pow(std::abs(std::cos(t)), exponentSquare / 2) * sgn(std::cos(t));
			float sy = r * std::pow(std::abs(std::sin(t)), exponentSquare / 2) * sgn(std::sin(t));

			// Triangle
			float triAngle = (2.f * M_PI / 3.f);
			float angleMod = (fmod(t, triAngle));
			float k = std::cos(angleMod) / std::cos(triAngle / 2);
			float tx = r * k * std::cos(t);
			float ty = r * k * std::sin(t);

			float x, y;
			if (morph < 1) {
				x = lerp(tx, sx, morph);
				y = lerp(ty, sy, morph);
			} else {
				x = lerp(sx, cx, morph - 1);
				y = lerp(sy, cy, morph - 1);
			}

			vertex(x, y);
		}

		endShape(CLOSE);
	}

	float sgn(float v) {
		return (v < 0) ? -1 : 1;
	}

	void audio() {
	}
};

} // namespace Handheld
