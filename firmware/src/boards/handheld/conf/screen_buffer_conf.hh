#pragma once

#include <array>
#include <cstdint>

namespace MetaModule
{
struct ScreenBufferConf {
	//The width x height as defined by the screen hardware
	static constexpr uint32_t width = 960;
	static constexpr uint32_t height = 400;

	//The rotation we must to do hardware coordinates to get the view coordinates
	enum Rotation { None, CW90, Flip180, CCW90 };
	static constexpr Rotation rotation = CW90;

	//The width x height as viewed by the User:
	static constexpr uint32_t viewWidth = 960;
	static constexpr uint32_t viewHeight = 400;
	// static constexpr uint32_t viewWidth = 400;
	// static constexpr uint32_t viewHeight = 960;

	static constexpr uint32_t NumPixels = 960 * 400;
};
} // namespace MetaModule
