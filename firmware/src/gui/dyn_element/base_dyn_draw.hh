#pragma once
#include "gui/styles.hh"
#include "lvgl.h"
#include "pr_dbg.hh"
#include <span>

namespace MetaModule
{

struct BaseDynDraw {
	virtual ~BaseDynDraw() = default;
	virtual void draw() = 0;
	virtual void prepare(lv_obj_t *module_canvas, unsigned height) = 0;
	virtual void blur() = 0;

	bool copy_buffer(std::span<char> lv_buffer, std::span<uint32_t> fullcolor_buffer) {
		if ((fullcolor_buffer.size() * 3) > lv_buffer.size()) {
			pr_err("DynDraw buffer size error\n");
			return false;
		}

		unsigned buf_pos = 0;
		bool diff = false;
		for (auto pixel : fullcolor_buffer) {

			auto col = lv_color_make_rgb565(pixel >> 16, pixel >> 8, pixel);
			uint8_t alpha = (pixel >> 24) & 0xFF;

			if (lv_buffer[buf_pos] != (col.full & 0xFF)) {
				diff = true;
				lv_buffer[buf_pos] = col.full & 0xFF;
			}
			if (lv_buffer[buf_pos + 1] != (col.full >> 8)) {
				diff = true;
				lv_buffer[buf_pos + 1] = col.full >> 8;
			}
			if (lv_buffer[buf_pos + 2] != alpha) {
				diff = true;
				lv_buffer[buf_pos + 2] = alpha;
			}

			buf_pos += 3;
		}
		return diff;
	}
};

} // namespace MetaModule
