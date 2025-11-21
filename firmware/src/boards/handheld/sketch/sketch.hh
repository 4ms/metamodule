#pragma once
#include "api.hh"
#include "util/colors_rgb565.hh"

namespace Handheld
{

using Color = RGB565;

class Sketch {
public:
	virtual void setup() = 0;
	virtual void draw() = 0;
	virtual void audio() = 0;

	virtual ~Sketch() {};
};

} // namespace Handheld
