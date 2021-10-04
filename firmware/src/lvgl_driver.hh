#include "lvgl/lvgl.h"
#include "screen_writer.hh"
#include "timekeeper.hh"

namespace MetaModule
{
class LVGLDriver {
	static constexpr uint32_t ScreenWidth = MMScreenBufferConf::viewWidth;
	static constexpr uint32_t ScreenHeight = MMScreenBufferConf::viewHeight;
	static constexpr size_t BufferSize = ScreenHeight * ScreenWidth / 10;
	lv_color_t buf_1[BufferSize];
	lv_color_t buf_2[BufferSize];

	lv_disp_draw_buf_t disp_buf;

	//Display driver
	using flush_cb_t = void(lv_disp_drv_t *, const lv_area_t *, lv_color_t *);
	lv_disp_drv_t disp_drv;

	static void round16(lv_disp_drv_t *disp, lv_area_t *area)
	{
		area->y1 = area->y1 & 0x07;
		area->y2 = (area->y2 & 0x07) + 8;

		area->x1 = area->x1 & 0x07;
		area->x2 = (area->x2 & 0x07) + 8;
	}

public:
	LVGLDriver(flush_cb_t flush_cb)
	{
		lv_init();
		lv_disp_draw_buf_init(&disp_buf, buf_1, buf_2, BufferSize);
		lv_disp_drv_init(&disp_drv);
		disp_drv.draw_buf = &disp_buf;
		disp_drv.flush_cb = flush_cb;
		// disp_drv.rounder_cb = round16;
		disp_drv.hor_res = ScreenWidth;
		disp_drv.ver_res = ScreenHeight;

		lv_disp_drv_register(&disp_drv);
	}
};

class MMDisplay {
	static inline ScreenFrameWriter _spi_driver;
	static inline Timekeeper _run_lv_tasks_tmr;
	static inline volatile bool _ready = false;

public:
	static void init()
	{
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

	static inline lv_disp_drv_t *last_used_disp_drv;
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

private:
	static inline LVGLDriver gui{MMDisplay::flush_to_screen};
};
} // namespace MetaModule
