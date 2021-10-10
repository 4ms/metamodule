#pragma once
#include "lvgl/lvgl.h"
#include "params.hh"
#include <cstddef>
#include <cstdint>

namespace MetaModule
{

class LVGLDriver {
	static constexpr uint32_t ScreenWidth = 320;  //MMScreenBufferConf::viewWidth;
	static constexpr uint32_t ScreenHeight = 240; //MMScreenBufferConf::viewHeight;
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

public:
	LVGLDriver(flush_cb_t flush_cb, indev_cb_t indev_cb)
	{
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
	}
};

class MMDisplay {
	static constexpr size_t ScreenWidth = 320;
	static constexpr size_t ScreenHeight = 240;
	static inline volatile bool _ready = false;
	static inline MetaParams *m;

public:
	static void init(MetaModule::MetaParams &metaparams)
	{
		m = &metaparams;
	}

	static void start() {}

	static inline lv_color_t framebuffer[ScreenWidth][ScreenHeight];
	static void flush_to_screen(lv_disp_drv_t *disp_drv, const lv_area_t *area, lv_color_t *color_p)
	{
		for (int x = area->x1; x <= area->x2; x++) {
			for (int y = area->y1; y <= area->y2; y++) {
				framebuffer[x][y] = *color_p;
				color_p++;
			}
		}
		lv_disp_flush_ready(disp_drv);
	}

	static bool read_input(lv_indev_drv_t *indev, lv_indev_data_t *data)
	{
		data->enc_diff = m->rotary.use_motion();
		data->state = m->rotary_button.is_pressed() ? LV_INDEV_STATE_PR : LV_INDEV_STATE_REL;

		bool have_more_data_to_send = false;
		return have_more_data_to_send;
	}

private:
	static inline LVGLDriver gui{flush_to_screen, read_input};
};
} // namespace MetaModule
