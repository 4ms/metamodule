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

#ifndef M_PI
#define M_PI 3.14159f
#endif
#ifndef TWO_PI
static constexpr float TWO_PI = M_PI * 2.f;
#endif

void size(unsigned w, unsigned h);

enum ColorMode { RGB, HSB };
void colorMode(ColorMode mode, float max1, float max2, float max3);
void colorMode(ColorMode mode, float max);
void colorMode(ColorMode mode);

enum CoordMode { CORNER, CORNERS, CENTER, RADIUS };
void rectMode(CoordMode);
void ellipseMode(CoordMode);
void shapeMode(CoordMode);

void noStroke();
void stroke(float comp1, float comp2, float comp3);
void stroke(float grey);
void strokeWeight(float weight);

void background(float color);

void fill(float comp1, float comp2, float comp3);
void fill(float grey);
void noFill();

void rect(int x, int y, int w, int h);
void ellipse(int x, int y, int w, int h);

enum ShapeMode { OPEN, CLOSE };
void beginShape();
void vertex(float x, float y);
void endShape(ShapeMode mode = OPEN);

void pushMatrix();
void popMatrix();
void translate(float x, float y);
void rotate(float angle);
void scale(float s);
void scale(float x, float y);

float noise(float x);
float noise(float x, float y);
float noise(float x, float y, float z);

// clang-format off
inline float map(float x, float in1, float in2, float out1, float out2) { return MathTools::map_value(x, in1, in2, out1, out2); }
inline float constrain(float x, float min, float max) { return std::clamp(x, min, max); }
inline float lerp(float a, float b, float t) { return a + t * (b - a);}  //naive is faster than std::lerp
inline float abs(int x) { return std::abs(x); }
inline float abs(float x) { return std::abs(x); }
inline float cos(float x) { return std::cos(x); }
inline float sin(float x) { return std::sin(x); }
inline float pow(float x, float y) { return std::pow(x, y); }
inline int mod(int t, int m) { return t % m; }
inline float mod(float t, int m) { return fmodf(t, m); }
inline float mod(float t, float m) { return fmodf(t, m); }
// clang-format on

} // namespace Handheld
