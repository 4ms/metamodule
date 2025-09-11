#include "../conf/screen_conf.hh"
#include "conf/screen_buffer_conf.hh"
#include "drivers/screen_ltdc.hh"
#include "drivers/ss7701s_lcd_init.hh"
#include "gui/elements/screensaver.hh"
#include "params/metaparams.hh"
#include "uart_log.hh"
#include "util/colors_rgb565.hh"
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

	// Display driver
	lv_disp_drv_t disp_drv;
	lv_disp_t *display;

public:
	LVGLDriver(flush_cb_t flush_cb, indev_cb_t indev_cb, std::span<lv_color_t> buffer1, std::span<lv_color_t> buffer2) {
		UartLog::log("LVGLDriver started\n");

		lv_init();
		lv_disp_draw_buf_init(&disp_buf, buffer1.data(), buffer2.data(), buffer1.size());
		lv_disp_drv_init(&disp_drv);
		disp_drv.draw_buf = &disp_buf;
		disp_drv.flush_cb = flush_cb;
		disp_drv.hor_res = ScreenWidth;
		disp_drv.ver_res = ScreenHeight;
		display = lv_disp_drv_register(&disp_drv); // NOLINT

		lv_indev_drv_init(&indev_drv);
		indev_drv.type = LV_INDEV_TYPE_ENCODER;
		indev_drv.read_cb = indev_cb;
		indev = lv_indev_drv_register(&indev_drv); // NOLINT
		lv_indev_enable(indev, true);
		lv_indev_set_group(indev, nullptr);

#if LV_USE_LOG == 1
		lv_log_register_print_cb(log_cb);
#endif
	}

	static void log_cb(const char *buf) {
		UartLog::log("%s", buf);
	}
};

void start_pixel_clock();

class MMDisplay {
	static inline MetaParams *m;
	static inline Screensaver *_screensaver;
	static constexpr size_t BufferSize = ScreenBufferConf::viewWidth * ScreenBufferConf::viewHeight;

	static inline ScreenParallelWriter<ScreenConf> ltdc_driver;
	static inline mdrivlib::LTDCSerial9BitSetup<ScreenControlConf> screen_setup{ScreenControlConf::reset};

	static inline std::array<lv_color_t, BufferSize> testbuf;

public:
	static void init(MetaParams &metaparams, Screensaver &screensaver, std::span<lv_color_t> buf) {
		m = &metaparams;
		_screensaver = &screensaver;

		screen_setup.setup_driver_chip(mdrivlib::ST7701S::InitCmds);

		start_pixel_clock();
		HAL_Delay(1);
		ltdc_driver.init(buf.data());

		test_pattern(0, buf);
	}

	static void test_pattern(unsigned id, std::span<lv_color_t> buf) {
		if (buf.size() != 400 * 960)
			printf("WRONG BUFFER SIZE\n");

		// test pattern
		if (id == 0) {
			for (auto y = 0; y < 400; y++) {
				for (auto x = 0; x < 960; x++) {
					unsigned i = x + y * 960;

					if (x >= (480 + 240) && y < 200)
						buf[i].full = Colors565::White;

					else if (x >= 480 && y < 200)
						buf[i].full = Colors565::Red;

					else if (x < 480 && y < 200)
						buf[i].full = Colors565::Grey;

					else if (x < 480 && y >= 200)
						buf[i].full = Colors565::Orange;

					else if (x >= 480 && y >= 200)
						buf[i].full = Colors565::Blue;
				}
			}
		}

		if (id == 1) {
			for (auto y = 0; y < 400; y++) {
				for (auto x = 0; x < 960; x++) {
					unsigned i = x + y * 960;

					if (x >= (480 + 240 + 120) && y < 200)
						buf[i].full = Colors565::White;

					else if (x >= (480 + 240) && y < 200)
						buf[i].full = Colors565::Green;

					else if (x >= 480 && y < 200)
						buf[i].full = Colors565::Red;

					else if (x < 480 && y >= 200)
						buf[i].full = Colors565::Yellow; //never

					else if (x >= (480 + 120) && y >= 200)
						buf[i].full = Colors565::Grey;

					else if (x >= 480 && y >= 200)
						buf[i].full = Colors565::Blue;
				}
			}
		}
		ltdc_driver.set_buffer(buf.data());
	}

	static void flush_to_screen(lv_disp_drv_t *disp_drv, const lv_area_t *area, lv_color_t *color_p) {
		ltdc_driver.set_buffer(color_p);
		lv_disp_flush_ready(disp_drv);
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
