#pragma once
#include <cstdint>

struct Rect;

struct RectC {
	int32_t left;
	int32_t top;
	int32_t right;
	int32_t bottom;

	constexpr int32_t width() const {
		return right - left;
	}
	constexpr int32_t height() const {
		return bottom - top;
	}
	constexpr int32_t center_y() const {
		return (top + bottom) / 2;
	}
	constexpr int32_t center_x() const {
		return (left + right) / 2;
	}

	// operator Rect();

	constexpr bool y_intersects(const RectC &other) const {
		return (top >= other.top && top <= other.bottom) || (other.top >= top && other.top <= bottom);
	}
	constexpr bool x_intersects(const RectC &other) const {
		return (left >= other.left && left <= other.right) || (right <= other.right && right >= other.left);
	}
	constexpr bool is_intersecting(const RectC &other) const {
		return y_intersects(other) && x_intersects(other);
	}
};

struct Rect {
	int32_t left;
	int32_t top;
	int32_t width;
	int32_t height;
	constexpr int32_t right() const {
		return left + width;
	}
	constexpr int32_t bottom() const {
		return top + height;
	}
	constexpr int32_t center_y() const {
		return top + height / 2;
	}
	constexpr int32_t center_x() const {
		return left + width / 2;
	}
	// operator RectC();
};

// RectC::operator Rect()
// {
// 	return Rect{.left = left, .top = top, .width = width(), .height = height()};
// }
// Rect::operator RectC()
// {
// 	return RectC{.left = left, .top = top, .right = right(), .bottom = bottom()};
// }
