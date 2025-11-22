#pragma once
#include "sketch.hh"
#include <cstdio>

namespace Handheld
{

class Test3 : public Sketch {
public:
	int cols, rows;
	constexpr static float cellSize = 10;

	float time = 0;

	float CV[8]{};

	// Interpolated values
	float zoom = 1.0, targetZoom = 1.0;
	float interpCV1 = 0, interpCV2 = 0, interpCV3 = 0, interpCV4 = 0, interpCV5 = 0, interpCV6 = 0;

	void setup() {
		size(960, 400);
		cols = (int)ceil(width / cellSize);
		rows = (int)ceil(height / cellSize);

		colorMode(RGB, 255);
		noStroke();
	}

	void draw() {
		background(0);

		for (int i = 0; i < 6; i++) {
			CV[i] += 0.01f * i;
			if (CV[i] > 1.f) {
				CV[i] = 0.f;
			}
		}

		// Interpolate all CV values smoothly
		interpCV1 = lerp(interpCV1, CV[0], 0.05); // global speed
		interpCV2 = lerp(interpCV2, CV[1], 0.05); // Perlin amplitude
		interpCV3 = lerp(interpCV3, CV[2], 0.05); // hue
		interpCV4 = lerp(interpCV4, CV[3], 0.05); // zoom
		interpCV5 = lerp(interpCV5, CV[4], 0.05); // ripple frequency
		interpCV6 = lerp(interpCV6, CV[5], 0.05); // ripple amplitude

		// Interpolated zoom
		targetZoom = map(interpCV4, 0, 1, 1.0, 0.5);
		zoom = lerp(zoom, targetZoom, 0.05);

		// Grid dimensions
		cols = ceil(width / cellSize);
		rows = ceil(height / cellSize);
		float gridWidth = cols * cellSize;
		float gridHeight = rows * cellSize;
		float gridCenterX = gridWidth / 2;
		float gridCenterY = gridHeight / 2;
		float offsetX = (width - gridWidth) / 2;
		float offsetY = (height - gridHeight) / 2;

		pushMatrix();
		translate(offsetX + gridCenterX, offsetY + gridCenterY);
		scale(zoom);
		translate(-(offsetX + gridCenterX), -(offsetY + gridCenterY));

		for (int i = 0; i < cols; i++) {
			for (int j = 0; j < rows; j++) {
				float x = i * cellSize + offsetX;
				float y = j * cellSize + offsetY;

				// Distance from center
				float dx = x - (offsetX + gridCenterX);
				float dy = y - (offsetY + gridCenterY);
				float dist = sqrt(dx * dx + dy * dy);

				// Radial sinewave ripple using interpolated frequency & amplitude
				float frequency = map(interpCV5, 0, 1, 0.01, 0.05);
				float amplitude = map(interpCV6, 0, 1, 0, 20);
				float ripple = sin(dist * frequency - time * 2.0) * amplitude;
				y += ripple;

				// Smooth amplitude modulation per cell (interpolated)
				float localAmplitude = noise(i * 0.05, j * 0.05, time * 0.3) * (interpCV2 * 4);

				// Perlin noise for fractal twist
				float n = noise(i * 0.1, j * 0.1, time) * localAmplitude;
				float angle = n * TWO_PI * 4;
				float len = n * cellSize * 2;

				pushMatrix();
				translate(x + cellSize / 2, y + cellSize / 2);
				rotate(angle);

				// RGB color with interpolated hue
				float hueShift = interpCV3 * 255;
				float r = mod(n * 255 + hueShift, 255);
				float g = mod((1 - n) * 200 + hueShift, 255);
				float b = mod((n * 100 + hueShift), 255);

				fill(r, g, b);
				beginShape();
				vertex(-len / 2, -1);
				vertex(len / 2, -1);
				vertex(len / 2, 1);
				vertex(-len / 2, 1);
				endShape(CLOSE);
				// rectMode(CENTER);
				// rect(0, 0, len, 2);
				popMatrix();
			}
		}

		popMatrix();

		// Interpolated global animation speed (CV1)
		float globalSpeed = map(interpCV1, 0, 1, 0, 0.2);
		time += globalSpeed;
	}

	void audio() {
	}
};

} // namespace Handheld
