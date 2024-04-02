#pragma once
#include <app/ParamWidget.hpp>

namespace rack::app
{

struct Knob : ParamWidget {
	bool horizontal = false;
	bool smooth = true;
	bool snap = false;
	float speed = 1.f;
	bool forceLinear = false;
	float minAngle = -M_PI;
	float maxAngle = M_PI;
};

} // namespace rack::app
