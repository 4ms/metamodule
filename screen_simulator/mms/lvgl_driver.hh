#include "lvgl/lvgl.h"
#include <cstddef>
#include <cstdint>

namespace MetaModule
{

template<size_t ScreenWidth, size_t ScreenHeight>
class LVGLDriver {
	//Buffer
	static constexpr size_t BufferSize = ScreenHeight * ScreenWidth / 10;
	lv_disp_draw_buf_t disp_buf;
	lv_color_t buf_1[BufferSize];
	lv_color_t buf_2[BufferSize];

	//Display driver
	using flush_cb_t = void(lv_disp_drv_t *, const lv_area_t *, lv_color_t *);
	lv_disp_drv_t disp_drv;

public:
	LVGLDriver(flush_cb_t flush_cb)
	{
		lv_init();
		lv_disp_draw_buf_init(&disp_buf, buf_1, buf_2, BufferSize);
		lv_disp_drv_init(&disp_drv);
		disp_drv.draw_buf = &disp_buf;
		disp_drv.flush_cb = flush_cb;
		disp_drv.hor_res = ScreenWidth;
		disp_drv.ver_res = ScreenHeight;

		lv_disp_drv_register(&disp_drv);
	}
};

class MMDisplay {
	static constexpr size_t ScreenWidth = 320;
	static constexpr size_t ScreenHeight = 240;
	//static inline Timekeeper _run_lv_tasks_tmr;
	static inline volatile bool _ready = false;

public:
	static void init()
	{
		//setup timer to run every few ms that sets ready=true
	}

	static void start()
	{
		// _run_lv_tasks_tmr.start();
	}

	static bool is_ready()
	{
		return _ready;
	}

	static void clear_ready()
	{
		_ready = false;
	}

	static inline lv_color_t framebuffer[ScreenWidth][ScreenHeight];
	static void flush_to_screen(lv_disp_drv_t *disp_drv, const lv_area_t *area, lv_color_t *color_p)
	{
		for (int y = area->y1; y <= area->y2; y++) {
			for (int x = area->x1; x <= area->x2; x++) {
				framebuffer[y][x] = *color_p;
				color_p++;
			}
		}
		lv_disp_flush_ready(disp_drv);
	}

private:
	static inline LVGLDriver<ScreenWidth, ScreenHeight> gui{MMDisplay::flush_to_screen};
};
} // namespace MetaModule
