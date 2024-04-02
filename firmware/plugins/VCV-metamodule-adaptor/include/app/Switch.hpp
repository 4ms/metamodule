#pragma once
#include <app/ParamWidget.hpp>

namespace rack::app
{

/** A ParamWidget that represents an integer.
Increases by 1 each time it is clicked.
When maxValue is reached, the next click resets to minValue.
In momentary mode, the value is instead set to maxValue when the mouse is held and minValue when released.
*/
struct Switch : ParamWidget {
	// Instead of incrementing values on each click, sets maxValue on press and minValue on release.
	bool momentary = false;
};

} // namespace rack::app
