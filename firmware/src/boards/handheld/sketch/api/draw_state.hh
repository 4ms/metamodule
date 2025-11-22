#pragma once
#include "../api.hh"
#include "../sketch.hh"
#include "matrix2d.hh"
#include "util/fixed_vector.hh"
#include <stack>

namespace Handheld
{

using namespace ProcessingAPI;

struct DrawState {
	ColorMode color_mode = RGB;
	float color_range_1 = 255;
	float color_range_2 = 255;
	float color_range_3 = 255;

	Color fill = Colors565::White;
	bool do_fill = true;

	Color stroke = Colors565::White;
	float stroke_width = 0.f;

	Color bg = Colors565::Black;

	CoordMode rect_mode = CORNER;
	CoordMode shape_mode = CORNER;
	CoordMode ellipse_mode = CORNER;

	FixedVector<Vertex, 512> vertices;

	Matrix2D transform_matrix;
	std::stack<Matrix2D> matrix_stack;
};

} // namespace Handheld
