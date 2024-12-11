#pragma once
#include "conf/screen_buffer_conf.hh"
#include "conf/screen_conf.hh"
#include "debug.hh"
#include "drivers/screen_ST77XX.hh"
#include "drivers/timekeeper.hh"
#include "gui/elements/screensaver.hh"
#include "lvgl.h"
#include "params/metaparams.hh"
#include "params/params.hh"
#include "screen/screen_writer.hh"
#include <atomic>
#include <span>

namespace MetaModule
{

class MMDisplay {
	// static inline lv_display_t *last_used_display = nullptr;
	static inline MetaParams *m = nullptr;
	static inline Screensaver *_screensaver = nullptr;
	static constexpr size_t BufferSize = ScreenBufferConf::viewWidth * ScreenBufferConf::viewHeight;

	static inline ScreenFrameWriter _spi_driver;

	static inline std::array<lv_color_t, BufferSize> testbuf;

public:
	static void register_params(MetaParams &metaparams, Screensaver &screensaver) {
		m = &metaparams;
		_screensaver = &screensaver;
	}

	static void init() {
		_spi_driver.init();
		_spi_driver.register_partial_frame_cb(end_flush);
		_spi_driver.clear_overrun_on_interrupt();

		is_init = true;
	}

	static inline uint32_t last_transfer_start_time = 0;
	// static inline lv_area_t last_area{0, 0, 0, 0};
	// static inline uint16_t *last_pixbuf = nullptr;

	static inline std::atomic<bool> flush_done = false;
	static inline bool is_init = false;

	static void end_flush() {
		Debug::Pin2::high();
		// if (last_used_display) {
		// 	lv_display_flush_ready(last_used_display);
		// }
		flush_done = true;
		Debug::Pin2::low();
	}

	static void flush_to_screen(lv_display_t *display, const lv_area_t *area, uint8_t *color_p) {
		if (!is_init) {
			end_flush();
			return;
		}
		Debug::Pin0::high();
		flush_done = false;
		// last_used_display = display;
		auto pixbuf = reinterpret_cast<uint16_t *>(color_p);
		_spi_driver.transfer_partial_frame(area->x1, area->y1, area->x2, area->y2, pixbuf);

		last_transfer_start_time = HAL_GetTick();
		// last_area = *area;
		// last_pixbuf = pixbuf;
		Debug::Pin0::low();
	}

	static void wait_cb(lv_display_t *display) {
		if (!is_init)
			return;

		while (true) {
			if (_spi_driver.had_transfer_error()) {
				Debug::Pin1::high();
				Debug::Pin1::low();
				return;
			}

			if (_spi_driver.had_fifo_error()) {
				Debug::Pin1::high();
				HAL_Delay(1);
				Debug::Pin1::low();
				return;
			}

			//Timeout
			if (HAL_GetTick() - last_transfer_start_time > 20) {
				Debug::Pin1::high();
				Debug::Pin1::low();
				Debug::Pin1::high();
				Debug::Pin1::low();
				Debug::Pin1::high();
				Debug::Pin1::low();
				return;
			}

			if (flush_done)
				return;
		}
	}

	static void read_input(lv_indev_t *indev, lv_indev_data_t *data) {
		if (!m)
			return;

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
