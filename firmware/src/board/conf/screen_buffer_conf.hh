#pragma once

#include <cstdint>

namespace Mousai
{

struct ScreenBufferConf {
	//The width x height as defined by the screen hardware
	static constexpr uint32_t width = 128;
	static constexpr uint32_t height = 64;

	//The rotation we must to do hardware coordinates to get the view coordinates
	enum Rotation { None, CW90, Flip180, CCW90 };
	static constexpr Rotation rotation = None;

	//The width x height as viewed by the User:
	static constexpr uint32_t viewWidth = 128;
	static constexpr uint32_t viewHeight = 64;
};
} // namespace Mousai
