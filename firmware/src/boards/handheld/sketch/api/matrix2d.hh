#pragma once
#include <cmath>

namespace ProcessingAPI
{

struct Vertex {
	float x, y;
};

// 2D affine transformation matrix
// | a  c  tx |
// | b  d  ty |
struct Matrix2D {
	float a, b, c, d, tx, ty;

	// Identity matrix
	Matrix2D()
		: a(1)
		, b(0)
		, c(0)
		, d(1)
		, tx(0)
		, ty(0) {
	}

	// Transform a point
	void transform(float &x, float &y) const {
		float x_new = a * x + c * y + tx;
		float y_new = b * x + d * y + ty;
		x = x_new;
		y = y_new;
	}

	// Multiply this matrix by another (this = this * other)
	void multiply(const Matrix2D &other) {
		float new_a = a * other.a + c * other.b;
		float new_b = b * other.a + d * other.b;
		float new_c = a * other.c + c * other.d;
		float new_d = b * other.c + d * other.d;
		float new_tx = a * other.tx + c * other.ty + tx;
		float new_ty = b * other.tx + d * other.ty + ty;

		a = new_a;
		b = new_b;
		c = new_c;
		d = new_d;
		tx = new_tx;
		ty = new_ty;
	}

	// Apply translation
	void translate(float dx, float dy) {
		Matrix2D trans{};
		trans.tx = dx;
		trans.ty = dy;
		multiply(trans);
	}

	// Apply rotation (angle in radians)
	void rotate(float angle) {
		Matrix2D rot{};
		rot.a = std::cos(angle);
		rot.b = std::sin(angle);
		rot.c = -std::sin(angle);
		rot.d = std::cos(angle);
		multiply(rot);
	}

	// Apply scale
	void scale(float sx, float sy) {
		Matrix2D scl{};
		scl.a = sx;
		scl.d = sy;
		multiply(scl);
	}
};

} // namespace ProcessingAPI
