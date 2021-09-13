#pragma once
#include <cstdint>

struct RectC {
	int32_t left;
	int32_t top;
	int32_t right;
	int32_t bottom;

	[[nodiscard]] constexpr int32_t width() const
	{
		return right - left;
	}
	[[nodiscard]] constexpr int32_t height() const
	{
		return bottom - top;
	}
	[[nodiscard]] constexpr int32_t center_y() const
	{
		return (top + bottom) / 2;
	}
	[[nodiscard]] constexpr int32_t center_x() const
	{
		return (left + right) / 2;
	}
};

struct Rect {
	int32_t left;
	int32_t top;
	int32_t width;
	int32_t height;
	[[nodiscard]] constexpr int32_t right() const
	{
		return left + width;
	}
	[[nodiscard]] constexpr int32_t bottom() const
	{
		return top + height;
	}
	[[nodiscard]] constexpr int32_t center_y() const
	{
		return top + height / 2;
	}
	[[nodiscard]] constexpr int32_t center_x() const
	{
		return left + width / 2;
	}
};
