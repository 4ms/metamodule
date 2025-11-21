#pragma once

#include "util/math.hh"
#include <cmath>

namespace Handheld
{

extern unsigned width;
extern unsigned height;

extern int mouseX;
extern int mouseY;

extern float accelX;
extern float accelY;
extern float accelZ;

void size(unsigned w, unsigned h);

enum ColorMode { RGB, HSB };
void colorMode(ColorMode mode, float comp1, float comp2, float comp3);

enum CoordMode { CORNER, CORNERS, CENTER, RADIUS };
void rectMode(CoordMode);
void ellipseMode(CoordMode);
void shapeMode(CoordMode);

void noStroke();
void stroke(float comp1, float comp2, float comp3);
void strokeWeight(float weight);

void background(float color);

void fill(float comp1, float comp2, float comp3);
void noFill();

void rect(int x, int y, unsigned w, unsigned h);
void ellipse(int x, int y, unsigned w, unsigned h);

enum ShapeMode { OPEN, CLOSE };
void beginShape();
void vertex(float x, float y);
void endShape(ShapeMode mode = OPEN);

void pushMatrix();
void popMatrix();
void translate(float x, float y);
void rotate(float angle);

inline float map(float x, float in1, float in2, float out1, float out2) {
	return MathTools::map_value(x, in1, in2, out1, out2);
}

inline float constrain(float x, float min, float max) {
	return std::clamp(x, min, max);
}

inline float lerp(float in1, float in2, float phase) {
	return std::lerp(in1, in2, phase);
}

} // namespace Handheld
