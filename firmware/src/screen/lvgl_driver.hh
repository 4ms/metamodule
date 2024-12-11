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
	LVGLDriver(std::span<uint8_t> buffer1, std::span<uint8_t> buffer2) {
		UartLog::log("LVGLDriver started\n");

		// Debug::Pin0::high();
		lv_init();

		display = lv_display_create(ScreenWidth, ScreenHeight); //NOLINT: cannot construct before lv_init
		lv_display_set_color_format(display, LV_COLOR_FORMAT_RGB565);
		printf("buffer is %zu bytes\n", buffer1.size_bytes());

		lv_display_set_buffers(
			display, buffer1.data(), buffer2.data(), buffer1.size_bytes(), LV_DISPLAY_RENDER_MODE_PARTIAL);

		lv_display_set_flush_cb(display, MMDisplay::flush_to_screen);
		lv_display_set_flush_wait_cb(display, MMDisplay::wait_cb);

		indev = lv_indev_create(); //NOLINT: cannot construct before lv_init
		lv_indev_set_type(indev, LV_INDEV_TYPE_ENCODER);
		lv_indev_set_read_cb(indev, MMDisplay::read_input);

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
