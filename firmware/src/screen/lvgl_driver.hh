#include "conf/screen_buffer_conf.hh"
#include "conf/screen_conf.hh"
#include "drivers/screen_ST77XX.hh"
#include "drivers/timekeeper.hh"
#include "gui/elements/screensaver.hh"
#include "lvgl.h"
#include "params/metaparams.hh"
#include "params/params.hh"
#include "screen/screen_writer.hh"
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
	}

	static void log_cb(lv_log_level_t level, const char *buf) {
		UartLog::log("[%d]: %s", level, buf);
	}
};

class MMDisplay {
	static inline lv_display_t *last_used_display;
	static inline MetaParams *m;
	static inline Screensaver *_screensaver;
	static constexpr size_t BufferSize = ScreenBufferConf::viewWidth * ScreenBufferConf::viewHeight;

	static inline ScreenFrameWriter _spi_driver;

	static inline std::array<lv_color_t, BufferSize> testbuf;

public:
	static void init(MetaParams &metaparams, Screensaver &screensaver) {
		m = &metaparams;
		_screensaver = &screensaver;

		_spi_driver.init();
		_spi_driver.register_partial_frame_cb(end_flush);
		_spi_driver.clear_overrun_on_interrupt();
	}

	static inline uint32_t last_transfer_start_time = 0;
	static inline lv_area_t last_area{0, 0, 0, 0};
	static inline uint16_t *last_pixbuf = nullptr;

	static inline std::atomic<bool> flush_done = false;

	static void end_flush() {
		lv_display_flush_ready(last_used_display);
		Debug::Pin0::low();
		flush_done = true;
	}

	static void flush_to_screen(lv_display_t *display, const lv_area_t *area, uint8_t *color_p) {
		Debug::Pin0::high();
		flush_done = false;
		last_used_display = display;
		auto pixbuf = reinterpret_cast<uint16_t *>(color_p);
		_spi_driver.transfer_partial_frame(area->x1, area->y1, area->x2, area->y2, pixbuf);

		last_transfer_start_time = HAL_GetTick();
		last_area = *area;
		last_pixbuf = pixbuf;
	}

	static void wait_cb(lv_display_t *display) {
		// if (display->draw_buf->flushing) {
		while (true) {
			if (_spi_driver.had_transfer_error()) {
				return;
			}

			if (_spi_driver.had_fifo_error()) {
				HAL_Delay(1);
				return;
			}

			//Timeout
			if (HAL_GetTick() - last_transfer_start_time > 20) {
				return;
			}

			if (flush_done)
				return;
		}
	}

	static void read_input(lv_indev_t *indev, lv_indev_data_t *data) {
		data->continue_reading = false;

#ifdef LONG_PRESS_MANUALLY_PARSED
		static inline bool should_send_button_release = false;
		if (should_send_button_release) {
			data->state = LV_INDEV_STATE_REL;
			should_send_button_release = false;
			return;
		}

		// Handle rotary button press/release while still allowing for rotary push+turn.
		// LVGL does not support rotary push+turn, instead it interprets the release at the end
		// of a push+turn event as a normal rotary release.
		// Here we use is_just_released() which only is true if we had a push and a release
		// without any turning. In this case, we send a press event immediately followed by
		// a release event.
		// Push+turn events are ignored by LVGL in this setup.
		auto just_released = m->rotary_button.is_just_released();
		if (just_released) {
			data->state = LV_INDEV_STATE_PR;
			should_send_button_release = true;
			data->continue_reading = true;
		}
#else
		if (_screensaver->is_active()) {
			if (m->rotary_button.is_just_released() || m->rotary.use_motion())
				_screensaver->wake();
			return;
		} else
			m->rotary_button.clear_events();

		if (m->meta_buttons[0].is_pressed()) {
			if (m->rotary.motion != 0) {
				m->ignore_metabutton_release = true;
				m->rotary_with_metabutton.transfer_motion(m->rotary);
				_screensaver->wake();
			}
		} else
			data->state = m->rotary_button.is_pressed() ? LV_INDEV_STATE_PR : LV_INDEV_STATE_REL;
#endif

#ifdef MONKEYROTARY
		static uint32_t last_tm = 0;
		static uint32_t count = 100;
		if (HAL_GetTick() - last_tm >= count) {
			data->enc_diff = HAL_GetTick() & 0b01 ? 1 : -1;
			last_tm = HAL_GetTick();
			count = HAL_GetTick() % count + 100;
		} else
			data->enc_diff = m->rotary.use_motion();
#else
		data->enc_diff = m->rotary.use_motion();

		if (data->state || data->enc_diff)
			_screensaver->wake();
#endif
	}
};
} // namespace MetaModule
