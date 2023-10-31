#include "conf/screen_buffer_conf.hh"
#include "conf/screen_conf.hh"
#include "drivers/screen_ST77XX.hh"
#include "drivers/timekeeper.hh"
#include "lvgl/lvgl.h"
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

	lv_disp_draw_buf_t disp_buf;
	lv_indev_drv_t indev_drv;
	lv_indev_t *indev;

	// Callbacks
	using flush_cb_t = void(lv_disp_drv_t *, const lv_area_t *, lv_color_t *);
	using indev_cb_t = void(lv_indev_drv_t *indev, lv_indev_data_t *data);
	using wait_cb_t = void(lv_disp_drv_t *);

	// Display driver
	lv_disp_drv_t disp_drv;
	lv_disp_t *display;
	// lv_theme_t *theme;

public:
	LVGLDriver(flush_cb_t flush_cb,
			   indev_cb_t indev_cb,
			   wait_cb_t wait_cb,
			   std::span<lv_color_t> buffer1,
			   std::span<lv_color_t> buffer2) {
		UartLog::log("\n\nLVGLDriver started\n");

		lv_init();
		lv_disp_draw_buf_init(&disp_buf, buffer1.data(), buffer2.data(), buffer1.size());
		lv_disp_drv_init(&disp_drv);
		disp_drv.draw_buf = &disp_buf;
		disp_drv.flush_cb = flush_cb;
		disp_drv.wait_cb = wait_cb;
		disp_drv.hor_res = ScreenWidth;
		disp_drv.ver_res = ScreenHeight;
		display = lv_disp_drv_register(&disp_drv); // NOLINT

		lv_indev_drv_init(&indev_drv);
		indev_drv.type = LV_INDEV_TYPE_ENCODER;
		indev_drv.read_cb = indev_cb;
		indev = lv_indev_drv_register(&indev_drv); // NOLINT
		lv_indev_enable(indev, true);
#if LV_USE_LOG == 1
		lv_log_register_print_cb(log_cb);
#endif
	}

	static void log_cb(const char *buf) {
		UartLog::log("%s", buf);
	}
};

class MMDisplay {
	static inline lv_disp_drv_t *last_used_disp_drv;
	static inline MetaParams *m;
	static constexpr size_t BufferSize = ScreenBufferConf::viewWidth * ScreenBufferConf::viewHeight;

private:
	static inline ScreenFrameWriter _spi_driver;

	static inline std::array<lv_color_t, BufferSize> testbuf;

public:
	static void init(MetaParams &metaparams, std::span<lv_color_t> initial_buf) {
		m = &metaparams;

		_spi_driver.init();
		_spi_driver.register_partial_frame_cb(end_flush);
		_spi_driver.clear_overrun_on_interrupt();
	}

	static inline uint32_t last_transfer_start_time = 0;
	static inline lv_area_t last_area{0, 0, 0, 0};
	static inline uint16_t *last_pixbuf = nullptr;

	static void end_flush() {
		lv_disp_flush_ready(last_used_disp_drv);
	}

	static void flush_to_screen(lv_disp_drv_t *disp_drv, const lv_area_t *area, lv_color_t *color_p) {
		last_used_disp_drv = disp_drv;
		auto pixbuf = reinterpret_cast<uint16_t *>(color_p);
		_spi_driver.transfer_partial_frame(area->x1, area->y1, area->x2, area->y2, pixbuf);

		last_transfer_start_time = HAL_GetTick();
		last_area = *area;
		last_pixbuf = pixbuf;
	}

	static void wait_cb(lv_disp_drv_t *disp_drv) {
		if (disp_drv->draw_buf->flushing) {
			if (_spi_driver.had_transfer_error()) {
				disp_drv->draw_buf->flushing = 0;
			}

			if (_spi_driver.had_fifo_error()) {
				HAL_Delay(1);
			}

			//Timeout
			if (HAL_GetTick() - last_transfer_start_time > 200) {
				disp_drv->draw_buf->flushing = 0;
				// Doesn't seem to matter:
				// _spi_driver.reinit();
				// HAL_Delay(1);
				// Doesn't work at all (screen is still expecting data from previous command):
				// _spi_driver.transfer_partial_frame(last_area.x1, last_area.y1, last_area.x2, last_area.y2, last_pixbuf);
			}
		}
	}

	static void read_input(lv_indev_drv_t *indev, lv_indev_data_t *data) {
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
#endif
	}
};
} // namespace MetaModule
