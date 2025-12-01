#include "../api.hh"
#include "draw_state.hh"

namespace Handheld
{

extern DrawState state_;

void colorMode(ColorMode mode, float max1, float max2, float max3) {
	state_.color_mode = mode;
	state_.color_range_1 = max1;
	state_.color_range_2 = max2;
	state_.color_range_3 = max3;
}

void colorMode(ColorMode mode, float max) {
	state_.color_mode = mode;
	state_.color_range_1 = max;
	state_.color_range_2 = max;
	state_.color_range_3 = max;
}

void colorMode(ColorMode mode) {
	state_.color_mode = mode;
}

} // namespace Handheld
