#include "../api.hh"
#include "draw_state.hh"

namespace Handheld
{

extern DrawState state_;

void pushMatrix() {
	state_.matrix_stack.push_back(state_.transform_matrix);
	if (state_.matrix_stack.size() == state_.matrix_stack.max_size()) {
		printf("Error: maximum size of matrix stack exceeded\n");
	}
}

void popMatrix() {
	if (auto m = state_.matrix_stack.pop_back(); m.has_value())
		state_.transform_matrix = m.value();
}

void translate(float x, float y) {
	state_.transform_matrix.translate(x, y);
}

void rotate(float angle) {
	state_.transform_matrix.rotate(angle);
}

void scale(float s) {
	state_.transform_matrix.scale(s, s);
}

void scale(float x, float y) {
	state_.transform_matrix.scale(x, y);
}

void setTransformResolution(unsigned resolution) {
	state_.transform_resolution = resolution;
}

} // namespace Handheld
