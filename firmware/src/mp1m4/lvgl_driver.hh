#include "lvgl/lvgl.h"

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
} // namespace MetaModule
