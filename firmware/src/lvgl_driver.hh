#include "lvgl/lvgl.h"
#include "lvgl/src/lv_misc/lv_color.h"
#include "params.hh"
#include "printf.h"
#include "screen_writer.hh"
#include "timekeeper.hh"
#include "uart.hh"

namespace MetaModule
{
class LVGLDriver {
	static constexpr uint32_t ScreenWidth = MMScreenBufferConf::viewWidth;
	static constexpr uint32_t ScreenHeight = MMScreenBufferConf::viewHeight;
	static constexpr size_t BufferSize = ScreenHeight * ScreenWidth / 10;
	lv_color_t buf_1[BufferSize];
	lv_color_t buf_2[BufferSize];

	// v8:
	// lv_disp_draw_buf_t disp_buf;
	lv_disp_buf_t disp_buf;
	lv_indev_drv_t indev_drv;
	lv_indev_t *indev;

	//Callbacks
	using flush_cb_t = void(lv_disp_drv_t *, const lv_area_t *, lv_color_t *);
	using indev_cb_t = bool(lv_indev_drv_t *indev, lv_indev_data_t *data);

	//Display driver
	lv_disp_drv_t disp_drv;

#ifdef LV_USE_LOG
	static inline Uart<UART4_BASE> log_uart;
#endif

public:
	//~600us
	LVGLDriver(flush_cb_t flush_cb, indev_cb_t indev_cb)
	{
		printf("LVLDriver started ctor\n\r");

		lv_init();

		// lv_disp_draw_buf_init(&disp_buf, buf_1, buf_2, BufferSize);
		lv_disp_buf_init(&disp_buf, buf_1, buf_2, BufferSize);
		lv_disp_drv_init(&disp_drv);
		// disp_drv.draw_buf = &disp_buf;
		disp_drv.buffer = &disp_buf;
		disp_drv.flush_cb = flush_cb;
		disp_drv.hor_res = ScreenWidth;
		disp_drv.ver_res = ScreenHeight;
		lv_disp_drv_register(&disp_drv);
		// auto disp =
		// lv_disp_set_bg_color(disp, lv_color_make(0x28, 0x28, 0x28));
		// lv_disp_set_bg_opa(disp, LV_OPA_50);

		lv_indev_drv_init(&indev_drv);
		indev_drv.type = LV_INDEV_TYPE_ENCODER;
		indev_drv.read_cb = indev_cb;
		indev = lv_indev_drv_register(&indev_drv);
		lv_indev_enable(indev, true);

		lv_log_register_print_cb(log_cb);
	}

	static void log_cb(lv_log_level_t level, const char *file, uint32_t line, const char *fn_name, const char *dsc)
	{
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
};
#ifdef LV_LOG_PRINTF
extern "C" void _putchar(char character)
{
	// while ((UART4->ISR & UART_FLAG_TXE) == RESET)
	// 	;
	UART4->TDR = character;
	while ((UART4->ISR & USART_ISR_TXFT) == 0)
		;
	// while ((UART4->ISR & UART_FLAG_TC) == RESET)
	// 	;
}

#endif

class MMDisplay {
	static inline ScreenFrameWriter _spi_driver;
	static inline Timekeeper _run_lv_tasks_tmr;
	static inline volatile bool _ready = false;
	static inline lv_disp_drv_t *last_used_disp_drv;
	static inline MetaParams *m;

public:
	static void init(MetaParams &metaparams)
	{
		m = &metaparams;
		_spi_driver.init();
		_spi_driver.register_partial_frame_cb(end_flush);

		_run_lv_tasks_tmr.init(
			{
				.TIMx = TIM5,
				.period_ns = 1000000000 / 333, // =  333Hz = 3ms update lvgl tasks rate
				.priority1 = 2,
				.priority2 = 2,
			},
			[] { _ready = true; });
	}

	static void start()
	{
		_run_lv_tasks_tmr.start();
	}

	static bool is_ready()
	{
		return _ready;
	}

	static void clear_ready()
	{
		_ready = false;
	}

	static void end_flush()
	{
		lv_disp_flush_ready(last_used_disp_drv);
	}

	static void flush_to_screen(lv_disp_drv_t *disp_drv, const lv_area_t *area, lv_color_t *color_p)
	{
		last_used_disp_drv = disp_drv;
		_spi_driver.transfer_partial_frame(
			area->x1, area->y1, area->x2, area->y2, reinterpret_cast<uint16_t *>(color_p));
	}

	static bool read_input(lv_indev_drv_t *indev, lv_indev_data_t *data)
	{
		data->enc_diff = m->rotary.use_motion();
		data->state = m->rotary_button.is_pressed() ? LV_INDEV_STATE_PR : LV_INDEV_STATE_REL;

		bool have_more_data_to_send = false;
		return have_more_data_to_send;
	}
};
} // namespace MetaModule
