#include "conf/screen_buffer_conf.hh"
#include "conf/screen_ltdc_conf.hh"
#include "drivers/screen_ltdc.hh"
#include "drivers/screen_ltdc_st77XX_setup.hh"
#include "lvgl/lvgl.h"
#include "lvgl/src/lv_misc/lv_color.h"
#include "params.hh"
#include "printf.h"
#include "timekeeper.hh"
#include "uart.hh"
#include <span>

namespace MetaModule
{
class LVGLDriver {
	static constexpr uint32_t ScreenWidth = ScreenBufferConf::viewWidth;
	static constexpr uint32_t ScreenHeight = ScreenBufferConf::viewHeight;

	// v8:
	// lv_disp_draw_buf_t disp_buf;
	lv_disp_buf_t disp_buf;
	lv_indev_drv_t indev_drv;
	lv_indev_t *indev;

	// Callbacks
	using flush_cb_t = void(lv_disp_drv_t *, const lv_area_t *, lv_color_t *);
	using indev_cb_t = bool(lv_indev_drv_t *indev, lv_indev_data_t *data);

	// Display driver
	lv_disp_drv_t disp_drv;

#ifdef LV_USE_LOG
	static inline mdrivlib::Uart<UART4_BASE> log_uart;
#endif

public:
	//~600us
	LVGLDriver(flush_cb_t flush_cb, indev_cb_t indev_cb, std::span<lv_color_t> buffer1, std::span<lv_color_t> buffer2) {
		printf("\n\rLVLDriver started\n\r");

		lv_init();

		// lv_disp_draw_buf_init(&disp_buf, buf_1, buf_2, BufferSize);

		lv_disp_buf_init(&disp_buf, buffer1.data(), buffer2.data(), buffer1.size());
		lv_disp_drv_init(&disp_drv);
		// disp_drv.draw_buf = &disp_buf;
		disp_drv.buffer = &disp_buf;
		disp_drv.flush_cb = flush_cb;
		disp_drv.hor_res = ScreenWidth;
		disp_drv.ver_res = ScreenHeight;
		lv_disp_drv_register(&disp_drv);

		lv_indev_drv_init(&indev_drv);
		indev_drv.type = LV_INDEV_TYPE_ENCODER;
		indev_drv.read_cb = indev_cb;
		indev = lv_indev_drv_register(&indev_drv);
		lv_indev_enable(indev, true);

#ifdef LV_USE_LOG
		lv_log_register_print_cb(log_cb);
#endif
	}

#ifdef LV_USE_LOG
	static void log_cb(lv_log_level_t level, const char *file, uint32_t line, const char *fn_name, const char *dsc) {
		if (level == LV_LOG_LEVEL_ERROR)
			log_uart.write("ERROR: ");
		if (level == LV_LOG_LEVEL_WARN)
			log_uart.write("WARNING: ");
		if (level == LV_LOG_LEVEL_INFO)
			log_uart.write("INFO: ");
		if (level == LV_LOG_LEVEL_TRACE)
			log_uart.write("TRACE: ");

		log_uart.write("File: ");
		log_uart.write(file);

		log_uart.write("#");
		log_uart.write(line);

		log_uart.write(": ");
		log_uart.write(fn_name);
		log_uart.write(": ");
		log_uart.write(dsc);
		log_uart.write("\n\r");
	}
#endif
};

extern "C" void _putchar(char character) {
	UART4->TDR = character;
	while ((UART4->ISR & USART_ISR_TXFT) == 0)
		;
}

class MMDisplay {
	static inline mdrivlib::Timekeeper _run_lv_tasks_tmr;
	static inline volatile bool _ready = false;
	static inline lv_disp_drv_t *last_used_disp_drv;
	static inline MetaParams *m;
	static constexpr size_t BufferSize = ScreenBufferConf::viewWidth * ScreenBufferConf::viewHeight;

private:
	static inline ScreenParallelWriter<ScreenConf> _ltdc_driver;
	static inline mdrivlib::ST77XXParallelSetup<ScreenControlConf> _screen_configure;

public:
	static void init(MetaParams &metaparams, std::span<lv_color_t, BufferSize> buf) {
		m = &metaparams;

		_screen_configure.setup_driver_chip<ScreenConf>();
		_ltdc_driver.init(buf.data());

		// for (int i = 0; i < 16; i++) {
		// 	for (auto &px : buf)
		// 		px.full = (1 << i);
		// 	_ltdc_driver.set_buffer(buf.data());
		// 	__BKPT();
		// }

		_run_lv_tasks_tmr.init(
			{
				.TIMx = TIM5,
				.period_ns = 1000000000 / 333, // =  333Hz = 3ms update lvgl tasks rate
				.priority1 = 2,
				.priority2 = 2,
			},
			[] { _ready = true; });
	}

	static void start() {
		_run_lv_tasks_tmr.start();
	}

	static bool is_ready() {
		return _ready;
	}

	static void clear_ready() {
		_ready = false;
	}

	static void flush_to_screen(lv_disp_drv_t *disp_drv, const lv_area_t *area, lv_color_t *color_p) {
		_ltdc_driver.set_buffer((void *)color_p);
		lv_disp_flush_ready(disp_drv);
	}

	static inline bool should_send_button_release = false;

	static bool read_input(lv_indev_drv_t *indev, lv_indev_data_t *data) {
		if (should_send_button_release) {
			data->state = LV_INDEV_STATE_REL;
			should_send_button_release = false;
			return false;
		}

		bool have_more_data_to_send = false;

		data->enc_diff = m->rotary.use_motion();
		auto just_released = m->rotary_button.is_just_released();
		if (just_released) {
			data->state = LV_INDEV_STATE_PR;
			should_send_button_release = true;
			have_more_data_to_send = true;
		}
		return have_more_data_to_send;
	}
};
} // namespace MetaModule
