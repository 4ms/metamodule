#pragma once

#include <array>
#include <cstdint>

// PROVISIONAL -- the final panel and resolution are not chosen yet (LTDC
// parallel-RGB vs MIPI DSI is an open hardware decision). 1280x720 is the
// working assumption for GUI layout work; preview pages at this size with the
// simulator's --screenw/--screenh flags.

namespace MetaModule
{
struct ScreenBufferConf {
	//The width x height as defined by the screen hardware
	static constexpr uint32_t width = 1280; // TBD: final panel resolution
	static constexpr uint32_t height = 720; // TBD: final panel resolution

	//The rotation we must to do hardware coordinates to get the view coordinates
	// (LTDC scans out in view orientation, unlike the MP1 SPI panel's CW90)
	enum Rotation { None, CW90, Flip180, CCW90 };
	static constexpr Rotation rotation = None;

	//The width x height as viewed by the User:
	static constexpr uint32_t viewWidth = 1280;
	static constexpr uint32_t viewHeight = 720;
};
} // namespace MetaModule
