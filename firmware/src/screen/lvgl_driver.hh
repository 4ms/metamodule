#include "conf/screen_buffer_conf.hh"
#include "conf/screen_conf.hh"
#include "drivers/screen_ST77XX.hh"
//#include "drivers/screen_ILI9341.hh"
//#include "drivers/screen_ltdc.hh"
//#include "drivers/screen_ltdc_setup.hh"
#include "drivers/timekeeper.hh"
#include "lvgl/lvgl.h"
#include "params/metaparams.hh"
#include "params/params.hh"
#include "screen/screen_writer.hh"
#include "uart_log.hh"
#include <span>

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
	// lv_theme_t *theme;

public:
	LVGLDriver(flush_cb_t flush_cb, indev_cb_t indev_cb, std::span<lv_color_t> buffer1, std::span<lv_color_t> buffer2) {
		UartLog::log("\n\nLVGLDriver started\n");

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
	// static inline ScreenParallelWriter<ScreenConf> _ltdc_driver;
	// static inline mdrivlib::LTDCParallelSetup<ScreenControlConf> _screen_configure;

	static inline std::array<lv_color_t, BufferSize> testbuf;

public:
	static void init(MetaParams &metaparams, std::span<lv_color_t> initial_buf) {
		m = &metaparams;

		_spi_driver.init();
		_spi_driver.register_partial_frame_cb(end_flush);
		_spi_driver.clear_overrun_on_interrupt();

		// LTDC mode:
		// _screen_configure.setup_driver_chip(mdrivlib::ST77XX::ST7789InitLTDC<ScreenConf>::cmds);
		// _ltdc_driver.init(buf.data());

		// for (int i = 0; i < 16; i++) {
		// 	for (auto &px : testbuf)
		// 		px.full = (1 << i);
		// 	// _ltdc_driver.set_buffer(buf.data());
		// 	_spi_driver.transfer_partial_frame(0, 0, 320, 240, reinterpret_cast<uint16_t *>(testbuf.data()));
		// 	__BKPT();
		// }
		// for (auto &px : testbuf)
		// 	px.full = (1 << 10);
	}

	static void end_flush() {
		lv_disp_flush_ready(last_used_disp_drv);
	}

	static void flush_to_screen(lv_disp_drv_t *disp_drv, const lv_area_t *area, lv_color_t *color_p) {
		last_used_disp_drv = disp_drv;
		auto pixbuf = reinterpret_cast<uint16_t *>(color_p);
		_spi_driver.transfer_partial_frame(area->x1, area->y1, area->x2, area->y2, pixbuf);
		// LTDC mode:
		// _ltdc_driver.set_buffer((void *)color_p);
		// lv_disp_flush_ready(disp_drv);
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
		data->enc_diff = m->rotary.use_motion();
	}
};
} // namespace MetaModule
