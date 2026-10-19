#pragma once

#include <array>
#include <cstdint>

// Pro p1 panel: ER-TFT050-10 (ILI9881C, MIPI DSI), native 720x1280 portrait,
// viewed as 1280x720 landscape. Preview pages at this size with the simulator's
// --screenw/--screenh flags.
// Mounting (observed on the test carrier with a test pattern): the panel's first
// scan line is on the viewer's left, and pixel 0 of each line is at the bottom.
// That is, the panel is mounted rotated 90 degrees counter-clockwise from portrait:
//    hardware (hx, hy) -> view (vx, vy) = (hy, 719 - hx)
//    view (vx, vy) -> hardware (hx, hy) = (719 - vy, vx)
// The LTDC cannot rotate, so the rotation is done when rendering (LVGL now, GPU later).
//
// Hardware line 0 is not visible on the ER-TFT050-10 (tested with isolated single lines:
// line 0 missing, line 2 and the last line visible). That is view column 0 (the leftmost
// column), so the visible view area is x = 1..1279.

namespace MetaModule
{
struct ScreenBufferConf {
	//The width x height as defined by the screen hardware
	static constexpr uint32_t width = 720;
	static constexpr uint32_t height = 1280;

	//The rotation we must to do hardware coordinates to get the view coordinates
	enum Rotation { None, CW90, Flip180, CCW90 };
	static constexpr Rotation rotation = CCW90; // hardware -> view, see the mapping above

	//The width x height as viewed by the User:
	static constexpr uint32_t viewWidth = 1280;
	static constexpr uint32_t viewHeight = 720;
};
} // namespace MetaModule
