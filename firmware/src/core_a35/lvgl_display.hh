#pragma once
#include "conf/screen_buffer_conf.hh"
#include "drivers/cache.hh"
#include "gui/elements/screensaver.hh"
#include "lvgl.h"
#include "params/metaparams.hh"
#include <cstdint>
#include <span>

namespace MetaModule
{

// LVGL display and input drivers for the DSI panel. MP2's version of MP1's MMDisplay + LVGLDriver
// (screen/lvgl_driver.hh).
//
// LVGL renders the GUI at viewWidth x viewHeight (MP1's 320x240) into a partial draw buffer.
// flush() scales each rendered area up by viewScale into the middle of the panel view (1280x720
// landscape), and rotates it into the framebuffer, which is in hardware orientation (720x1280
// portrait, ARGB8888). Then it cleans the framebuffer from the cache so the LTDC sees it.
//
// Input is an LVGL encoder fed from MetaParams (the rotary encoder and its button), as on MP1.
//
// TODO: this writes into the framebuffer the LTDC is scanning out, so fast animation can tear.
class LvglDisplay {
public:
	using HwPixel = uint32_t; // ARGB8888 (ScreenConf.pixel_format)

	static constexpr uint32_t HwWidth = ScreenBufferConf::width;
	static constexpr uint32_t HwHeight = ScreenBufferConf::height;
	static constexpr uint32_t ViewWidth = ScreenBufferConf::viewWidth;
	static constexpr uint32_t ViewHeight = ScreenBufferConf::viewHeight;
	static constexpr uint32_t Scale = ScreenBufferConf::viewScale;
	static constexpr uint32_t OffsetX = ScreenBufferConf::viewOffsetX;
	static constexpr uint32_t OffsetY = ScreenBufferConf::viewOffsetY;
	static_assert(ScreenBufferConf::rotation == ScreenBufferConf::CCW90, "flush() only implements CCW90");
	static_assert(HwWidth == ScreenBufferConf::panelViewHeight && HwHeight == ScreenBufferConf::panelViewWidth);

	void init(std::span<HwPixel> framebuffer, std::span<lv_color_t> draw_buffer) {
		fb_ = framebuffer.data();

		lv_init();
		lv_disp_draw_buf_init(&draw_buf_, draw_buffer.data(), nullptr, draw_buffer.size());
		lv_disp_drv_init(&disp_drv_);
		disp_drv_.draw_buf = &draw_buf_;
		disp_drv_.flush_cb = flush_cb;
		disp_drv_.hor_res = ViewWidth;
		disp_drv_.ver_res = ViewHeight;
		disp_drv_.user_data = this;
		lv_disp_drv_register(&disp_drv_);

		lv_indev_drv_init(&indev_drv_);
		indev_drv_.type = LV_INDEV_TYPE_ENCODER;
		indev_drv_.read_cb = read_input_cb;
		indev_drv_.user_data = this;
		auto indev = lv_indev_drv_register(&indev_drv_);
		lv_indev_enable(indev, true);
		lv_indev_set_group(indev, nullptr);
	}

	// The input reads the encoder from these (owned by the Ui, which is created after LVGL is started)
	void connect_input(MetaParams &metaparams, Screensaver &screensaver) {
		metaparams_ = &metaparams;
		screensaver_ = &screensaver;
	}

private:
	HwPixel *fb_ = nullptr;
	MetaParams *metaparams_ = nullptr;
	Screensaver *screensaver_ = nullptr;
	lv_disp_draw_buf_t draw_buf_{};
	lv_disp_drv_t disp_drv_{};
	lv_indev_drv_t indev_drv_{};

	static void flush_cb(lv_disp_drv_t *drv, const lv_area_t *area, lv_color_t *pixels) {
		static_cast<LvglDisplay *>(drv->user_data)->flush(area, pixels);
		lv_disp_flush_ready(drv);
	}

	// GUI (gx, gy) -> panel view (vx, vy) = (OffsetX + gx * Scale + i, OffsetY + gy * Scale + j), i,j < Scale
	// Panel view (vx, vy) -> hardware (hx, hy) = (HwWidth - 1 - vy, vx), see screen_buffer_conf.hh.
	// Each view column vx is hardware line vx, so the inner loop writes one framebuffer line
	// sequentially (right to left) while reading a column of the draw buffer.
	void flush(const lv_area_t *area, const lv_color_t *pixels) {
		const int32_t area_w = area->x2 - area->x1 + 1;

		for (int32_t gx = area->x1; gx <= area->x2; gx++) {
			for (uint32_t i = 0; i < Scale; i++) {
				auto vx = OffsetX + gx * Scale + i;
				HwPixel *hw_line = &fb_[vx * HwWidth];
				const lv_color_t *src = &pixels[gx - area->x1];

				for (int32_t gy = area->y1; gy <= area->y2; gy++) {
					auto color = lv_color_to32(*src);
					auto vy = OffsetY + gy * Scale;
					for (uint32_t j = 0; j < Scale; j++)
						hw_line[HwWidth - 1 - (vy + j)] = color;
					src += area_w;
				}
			}
		}

		auto first_line = OffsetX + area->x1 * Scale;
		mdrivlib::SystemCache::clean_dcache_by_range(&fb_[first_line * HwWidth],
													 area_w * Scale * HwWidth * sizeof(HwPixel));
	}

	static void read_input_cb(lv_indev_drv_t *drv, lv_indev_data_t *data) {
		static_cast<LvglDisplay *>(drv->user_data)->read_input(data);
	}

	// Same as MP1's MMDisplay::read_input()
	void read_input(lv_indev_data_t *data) {
		auto m = metaparams_;
		data->continue_reading = false;

		if (!m || !screensaver_) {
			data->state = LV_INDEV_STATE_RELEASED;
			data->enc_diff = 0;
			return;
		}

		if (m->meta_buttons[0].is_pressed()) {
			if (m->rotary.motion != 0) {
				m->ignore_metabutton_release = true;
				m->rotary_with_metabutton.transfer_motion(m->rotary);
			}
		}

		data->state = m->rotary_button.is_pressed() ? LV_INDEV_STATE_PRESSED : LV_INDEV_STATE_RELEASED;
		data->enc_diff = m->rotary.use_motion();

		// Wake screensaver on any motion, clearing events from the GUI
		if (screensaver_->is_active()) {
			if (m->rotary_button.is_just_released() || data->enc_diff || m->meta_buttons[0].is_just_released()) {
				screensaver_->wake();
			}
			m->meta_buttons[0].clear_events();
			m->rotary_button.clear_events();
			data->enc_diff = 0;
			data->state = LV_INDEV_STATE_RELEASED;
		}
	}
};

} // namespace MetaModule
