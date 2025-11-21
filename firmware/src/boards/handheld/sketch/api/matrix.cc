#include "../api.hh"
#include "draw_state.hh"

namespace Handheld
{

extern DrawState state_;

void pushMatrix() {
	state_.matrix_stack.push(state_.transform_matrix);
}

void popMatrix() {
	if (!state_.matrix_stack.empty()) {
		state_.transform_matrix = state_.matrix_stack.top();
		state_.matrix_stack.pop();
	}
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

} // namespace Handheld
