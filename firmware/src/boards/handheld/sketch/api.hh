#pragma once

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

void noStroke();

void background(float color);

void fill(float comp1, float comp2, float comp3);

void rect(int x, int y, unsigned w, unsigned h);
void ellipse(int x, int y, unsigned w, unsigned h);

} // namespace Handheld
