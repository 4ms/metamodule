#pragma once

#include "lvgl.h"
#include "thorvg.h"
#include <cstdio>
#include <span>
#include <vector>

namespace MetaModule::NanoVG
{

struct Texture {
	std::vector<lv_color_t> pix;
	size_t w{};
	size_t h{};

	lv_color_t px(size_t x, size_t y) const {
		return pix[x + y * w];
	}

	lv_color_t &px(size_t x, size_t y) {
		return pix[x + y * w];
	}
	//type?
	//flags?
};

struct TextRenderCacheEntry {
	float x;
	float y;
	int align;
	lv_obj_t *label;
	uint32_t last_drawn_frame;

	bool operator==(const TextRenderCacheEntry &other) const {
		return x == other.x && y == other.y && align == other.align;
	}
};

struct DrawContext {
	lv_obj_t *canvas{};
	lv_draw_label_dsc_t label_dsc{};

	std::vector<Texture> textures;

	std::vector<TextRenderCacheEntry> labels;

	uint32_t draw_frame_ctr{};

	void *parent_ctx{}; // needed for deleting

	unsigned px_per_3U = 240;

	tvg::SwCanvas *tvg_canvas{};

	DrawContext(lv_obj_t *canvas, std::span<uint32_t> buff, uint32_t width)
		: canvas{canvas} {

		lv_draw_label_dsc_init(&label_dsc);

		tvg_canvas = tvg::SwCanvas::gen();
		tvg_canvas->target(buff.data(), width, width, buff.size() / width, tvg::ColorSpace::ARGB8888);
	}

	~DrawContext() {
		delete tvg_canvas;
	}
};

inline DrawContext *get_drawcontext(void *uptr) {
	return (DrawContext *)(uptr);
}

} // namespace MetaModule::NanoVG
