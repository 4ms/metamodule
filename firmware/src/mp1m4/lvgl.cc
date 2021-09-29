#include "lvgl/lvgl.h"

template<size_t HOR_RES>
class LVGLDriver {
	lv_disp_draw_buf_t disp_buf;
	lv_color_t buf_1[HOR_RES * 10];
	//lv_color_t buf_2[MY_DISP_HOR_RES * 10];

	/*Initialize `disp_buf` with the buffer(s). With only one buffer use NULL instead buf_2 */
	LVGLDriver()
	{
		lv_disp_draw_buf_init(&disp_buf, buf_1, NULL, HOR_RES * 10);
	}
};
