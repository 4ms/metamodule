#pragma once
#include "conf/screen_buffer_conf.hh"
#include "drivers/cache.hh"
#include "lvgl.h"
#include <cstdint>
#include <span>

namespace MetaModule
{

// LVGL display driver for the DSI panel.
//
// LVGL renders in view coordinates (1280x720 landscape) into a partial draw buffer.
// flush() rotates each rendered area into the framebuffer, which is in hardware
// orientation (720x1280 portrait, ARGB8888), then cleans it from the cache so the
// LTDC sees it.
//
// TODO: this writes into the framebuffer the LTDC is scanning out, so fast animation can tear.
class LvglDisplay {
public:
	using HwPixel = uint32_t; // ARGB8888 (ScreenConf.pixel_format)

	static constexpr uint32_t HwWidth = ScreenBufferConf::width;
	static constexpr uint32_t HwHeight = ScreenBufferConf::height;
	static constexpr uint32_t ViewWidth = ScreenBufferConf::viewWidth;
	static constexpr uint32_t ViewHeight = ScreenBufferConf::viewHeight;
	static_assert(ScreenBufferConf::rotation == ScreenBufferConf::CCW90, "flush() only implements CCW90");
	static_assert(HwWidth == ViewHeight && HwHeight == ViewWidth);

	void init(std::span<HwPixel> framebuffer, std::span<lv_color_t> draw_buffer) {
		fb_ = framebuffer.data();

		lv_init();
		lv_disp_draw_buf_init(&draw_buf_, draw_buffer.data(), nullptr, draw_buffer.size());
		lv_disp_drv_init(&disp_drv_);
		disp_drv_.draw_buf = &draw_buf_;
		disp_drv_.flush_cb = flush_cb;
		disp_drv_.hor_res = ViewWidth;
		disp_drv_.ver_res = ViewHeight;
		disp_drv_.user_data = this;
		lv_disp_drv_register(&disp_drv_);
	}

private:
	HwPixel *fb_ = nullptr;
	lv_disp_draw_buf_t draw_buf_{};
	lv_disp_drv_t disp_drv_{};

	static void flush_cb(lv_disp_drv_t *drv, const lv_area_t *area, lv_color_t *pixels) {
		static_cast<LvglDisplay *>(drv->user_data)->flush(area, pixels);
		lv_disp_flush_ready(drv);
	}

	// View (vx, vy) -> hardware (hx, hy) = (HwWidth - 1 - vy, vx), see screen_buffer_conf.hh.
	// Each view column vx is hardware line vx, so the inner loop writes one framebuffer line
	// sequentially (right to left) while reading a column of the draw buffer.
	void flush(const lv_area_t *area, const lv_color_t *pixels) {
		const int32_t area_w = area->x2 - area->x1 + 1;

		for (int32_t vx = area->x1; vx <= area->x2; vx++) {
			HwPixel *hw_line = &fb_[vx * HwWidth];
			const lv_color_t *src = &pixels[vx - area->x1];
			for (int32_t vy = area->y1; vy <= area->y2; vy++) {
				hw_line[HwWidth - 1 - vy] = lv_color_to32(*src);
				src += area_w;
			}
		}

		mdrivlib::SystemCache::clean_dcache_by_range(&fb_[area->x1 * HwWidth], area_w * HwWidth * sizeof(HwPixel));
	}
};

} // namespace MetaModule
