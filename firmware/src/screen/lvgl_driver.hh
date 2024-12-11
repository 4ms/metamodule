#pragma once
#include "conf/screen_buffer_conf.hh"
#include "debug.hh"
#include "lvgl.h"
#include "mm_display.hh"
#include "uart_log.hh"
#include <span>

// #define MONKEYROTARY

namespace MetaModule
{
class LVGLDriver {
	static constexpr uint32_t ScreenWidth = ScreenBufferConf::viewWidth;
	static constexpr uint32_t ScreenHeight = ScreenBufferConf::viewHeight;

	lv_display_t *display;
	lv_indev_t *indev;

public:
	LVGLDriver(lv_display_flush_cb_t flush_cb,
			   lv_indev_read_cb_t indev_cb,
			   lv_display_flush_wait_cb_t wait_cb,
			   std::span<lv_color_t> buffer1,
			   std::span<lv_color_t> buffer2) {
		UartLog::log("LVGLDriver started\n");

		// Debug::Pin0::high();
		lv_init();
		display = lv_display_create(ScreenWidth, ScreenHeight); //NOLINT: cannot construct before lv_init
		indev = lv_indev_create();								//NOLINT: cannot construct before lv_init

		lv_display_set_flush_cb(display, flush_cb);
		lv_display_set_buffers(
			display, buffer1.data(), buffer2.data(), buffer1.size_bytes(), LV_DISPLAY_RENDER_MODE_PARTIAL);

		lv_display_set_flush_wait_cb(display, wait_cb);

		lv_indev_set_type(indev, LV_INDEV_TYPE_ENCODER);
		lv_indev_set_read_cb(indev, indev_cb);

		lv_indev_enable(indev, true);
		lv_indev_set_group(indev, nullptr);

#if LV_USE_LOG == 1
		lv_log_register_print_cb(log_cb);
#endif
		// Debug::Pin0::low();
	}

	static void log_cb(lv_log_level_t level, const char *buf) {
		UartLog::log("[%d]: %s", level, buf);
	}
};

} // namespace MetaModule
