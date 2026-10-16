#pragma once

#include <array>
#include <cstdint>

// Pro p1 panel: ER-TFT050-10 (ILI9881C, MIPI DSI), native 720x1280 portrait,
// viewed as 1280x720 landscape. Preview pages at this size with the simulator's
// --screenw/--screenh flags.
// TODO: confirm the mounting direction on hardware (CW90 vs CCW90). The LTDC cannot
// rotate, so the rotation is done when rendering (LVGL now, GPU later).

namespace MetaModule
{
struct ScreenBufferConf {
	//The width x height as defined by the screen hardware
	static constexpr uint32_t width = 720;
	static constexpr uint32_t height = 1280;

	//The rotation we must to do hardware coordinates to get the view coordinates
	enum Rotation { None, CW90, Flip180, CCW90 };
	static constexpr Rotation rotation = CW90; // TODO: verify on hardware

	//The width x height as viewed by the User:
	static constexpr uint32_t viewWidth = 1280;
	static constexpr uint32_t viewHeight = 720;
};
} // namespace MetaModule
