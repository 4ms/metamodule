#include "CoreModules/elements/units.hh"
#include "gui/fonts/ttf.hh"
#include "lvgl.h"
#include "nanovg_pixbuf_drawctx.hh"
#include "nanovg_pixbuf_util.hh"
#include "thorvg.h"
#include <algorithm>
#include <cmath>
#include <cstdlib>
#include <cstring>
#include <nanovg.h>
#include <span>
#include <string>
#include <vector>

#include "console/pr_dbg.hh"
// #include "medium/debug_raw.h"

namespace MetaModule::NanoVG
{

// #define dump_draw printf
#define dump_draw(...)

void renderFill(void *uptr,
				NVGpaint *paint,
				NVGcompositeOperationState compositeOperation,
				NVGscissor *scissor,
				float fringe,
				const float *bounds,
				const NVGpath *paths,
				int npaths) {

	if (npaths < 0 || npaths > 1024) {
		// pr_dbg("Invalid number of paths in RenderFill: %d\n", npaths);
		return;
	}
	if (paths[0].fill[0].x > 10000.f || paths[0].fill[0].y > 10000.f) {
		// pr_dbg("Invalid point in renderFill (point [0] is %f, %f)\n", paths[0].fill[0].x, paths[0].fill[0].y);
		return;
	}

	auto context = get_drawcontext(uptr);

	// Scale by ratio of 1 Rack pixel to 1 MM pixel
	auto scaling = mm_to_px(to_mm(1.), context->px_per_3U);

	for (auto &path : std::span{paths, (size_t)npaths}) {
		dump_draw("Fill path: #fill %d = count:%d\n", path.nfill, path.count);
		if (path.count < 3)
			continue;

		auto poly = tvg::Shape::gen();

		poly->moveTo(path.fill[0].x, path.fill[0].y);
		for (auto pt : std::span{path.fill + 1, (size_t)(path.count - 1)}) {
			poly->lineTo(pt.x, pt.y);
		}
		poly->close();

		auto [r, g, b, a] = to_tvg_color(paint->innerColor);
		poly->fill(r, g, b, a);

		// Clip/Scissor
		if (scissor->extent[0] >= 0 && scissor->extent[1] >= 0) {
			auto clip_region = tvg::Shape::gen();
			auto x = scissor->xform[4] - scissor->extent[0];
			auto y = scissor->xform[5] - scissor->extent[1];
			auto w = 2 * scissor->extent[0];
			auto h = 2 * scissor->extent[1];
			clip_region->appendRect(x, y, w, h);
			poly->clip(clip_region);
		}

		// Scene is required for clipping (at least in ThorVG 1.0-pre)
		auto scene = tvg::Scene::gen();
		scene->push(poly);
		scene->scale(scaling);

		context->tvg_canvas->push(scene);
		context->tvg_canvas->draw();
		context->tvg_canvas->sync();
		context->tvg_canvas->remove();
	}
}

void renderStroke(void *uptr,
				  NVGpaint *paint,
				  NVGcompositeOperationState compositeOperation,
				  NVGscissor *scissor,
				  float fringe,
				  float strokeWidth,
				  const NVGpath *paths,
				  int npaths) {

	auto context = get_drawcontext(uptr);

	if (npaths < 0 || npaths > 1024) {
		// pr_dbg("Invalid number of paths in renderStroke: %d\n", npaths);
		return;
	}
	if (paths[0].stroke[0].x > 10000.f || paths[0].stroke[0].y > 10000.f) {
		// pr_dbg("Invalid point in renderStroke (point [0] is %f, %f)\n", paths[0].stroke[0].x, paths[0].stroke[0].y);
		return;
	}

	// Scale by ratio of 1 Rack pixel to 1 MM pixel
	auto scaling = mm_to_px(to_mm(1.), context->px_per_3U);

	for (auto &path : std::span{paths, (size_t)npaths}) {
		dump_draw("Stroke path: #strokes %d = count:%d + closed:%d\n", path.nstroke, path.count, path.closed);
		if (path.count < 2)
			continue;

		auto poly = tvg::Shape::gen();

		poly->moveTo(path.stroke[0].x, path.stroke[0].y);
		for (auto pt : std::span{path.stroke + 1, (size_t)(path.nstroke - 1)}) {
			poly->lineTo(pt.x, pt.y);
		}

		auto [r, g, b, a] = to_tvg_color(paint->innerColor);
		poly->strokeFill(r, g, b, a);

		auto stroke_width = std::round(to_lv_coord(strokeWidth, context->px_per_3U));

		constexpr float MinStroke = 1.3f;
		poly->strokeWidth(std::max<lv_coord_t>(stroke_width, MinStroke / scaling));

		// Clip/Scissor
		if (scissor->extent[0] >= 0 && scissor->extent[1] >= 0) {
			auto clip_region = tvg::Shape::gen();
			auto x = scissor->xform[4] - scissor->extent[0];
			auto y = scissor->xform[5] - scissor->extent[1];
			auto w = 2 * scissor->extent[0];
			auto h = 2 * scissor->extent[1];
			clip_region->appendRect(x, y, w, h);
			poly->clip(clip_region);
		}

		// Scene is required for clipping (at least in ThorVG 1.0-pre)
		auto scene = tvg::Scene::gen();
		scene->push(poly);
		scene->scale(scaling);

		context->tvg_canvas->push(scene);
		context->tvg_canvas->draw();
		context->tvg_canvas->sync();
		context->tvg_canvas->remove();
	}
}

float renderText(
	void *uptr, float x, float y, float max_w, const char *text, const char *textend, struct NVGFontState *fs) {
	auto context = get_drawcontext(uptr);
	auto canvas = context->canvas;

	// Move to position
	auto lv_x = to_lv_coord(x, context->px_per_3U);
	auto lv_y = to_lv_coord(y, context->px_per_3U);

	if (fs->xform && (fs->xform[4] != 0 || fs->xform[5] != 0)) {
		lv_x += to_lv_coord(fs->xform[4], context->px_per_3U);
		lv_y += to_lv_coord(fs->xform[5], context->px_per_3U);
	}

	auto lv_font_size = to_lv_coord(Fonts::corrected_ttf_size(fs->fontSize, fs->fontName), context->px_per_3U);
	auto font = Fonts::get_ttf_font(std::string(fs->fontName), lv_font_size);
	if (!font)
		return 0;

	// Create or find existing label (match on X,Y pos and alignment)
	lv_obj_t *label{};
	auto found = std::ranges::find_if(context->labels, [=](TextRenderCacheEntry const &cached) {
		return cached.x == lv_x && cached.y == lv_y && cached.align == fs->textAlign;
	});

	if (found != context->labels.end()) {
		label = found->label;
		found->last_drawn_frame = context->draw_frame_ctr;
	} else {

		auto align = fs->textAlign & NVG_ALIGN_LEFT	  ? LV_TEXT_ALIGN_LEFT :
					 fs->textAlign & NVG_ALIGN_RIGHT  ? LV_TEXT_ALIGN_RIGHT :
					 fs->textAlign & NVG_ALIGN_CENTER ? LV_TEXT_ALIGN_CENTER :
														LV_TEXT_ALIGN_LEFT;

		// Align vertically
		auto align_lv_y = lv_y - (fs->textAlign & NVG_ALIGN_BASELINE ? lv_font_size * 1.0f :
								  fs->textAlign & NVG_ALIGN_BOTTOM	 ? lv_font_size * 1.2f :
								  fs->textAlign & NVG_ALIGN_MIDDLE	 ? lv_font_size * 0.5f :
								  fs->textAlign & NVG_ALIGN_TOP		 ? 0 :
																	   lv_font_size * 1.0f);

		align_lv_y += Fonts::corrected_ttf_ypos_shift(fs->fontSize, fs->fontName);

		if (fs->xform && (fs->xform[4] != 0 || fs->xform[5] != 0)) {
			pr_dbg("Text xform %f, %f\n", fs->xform[4], fs->xform[5]);
		}

		if (!(fs->textAlign & NVG_ALIGN_TOP))
			lv_obj_add_flag(canvas, LV_OBJ_FLAG_OVERFLOW_VISIBLE);

		label = lv_label_create(canvas);
		lv_obj_set_pos(label, lv_x, align_lv_y);
		lv_obj_set_size(label, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
		lv_obj_set_style_text_font(label, font, LV_PART_MAIN);
		// Ignore text opacity
		// lv_obj_set_style_text_opa(label, to_lv_opa(fs->paint->innerColor), LV_PART_MAIN);
		lv_obj_set_style_text_opa(label, LV_OPA_100, LV_PART_MAIN);
		lv_obj_set_style_text_align(label, align, LV_PART_MAIN);

		lv_obj_set_style_text_line_space(label, 0, LV_PART_MAIN);
		auto letter_space = to_lv_coord(fs->letterSpacing, context->px_per_3U);
		lv_obj_set_style_text_letter_space(label, letter_space, LV_PART_MAIN);

		lv_obj_add_flag(canvas, LV_OBJ_FLAG_OVERFLOW_VISIBLE);

		// Debug positions with red borders around labels
		// lv_obj_set_style_border_color(label, lv_color_hex(0xFF0000), LV_PART_MAIN);
		// lv_obj_set_style_border_opa(label, LV_OPA_50, LV_PART_MAIN);
		// lv_obj_set_style_border_width(label, 1, LV_PART_MAIN);

		pr_trace("Creating label at %d,%d a:0x%x sz:%g sp:%d\n", lv_x, lv_y, fs->textAlign, fs->fontSize, letter_space);
		context->labels.push_back({(float)lv_x, (float)lv_y, fs->textAlign, label, context->draw_frame_ctr});
	}

	if (text == nullptr)
		text = "";

	// Handle case were text doesn't have a null terminator (which LVGL needs)
	std::string text_copy;
	if (textend && *textend != '\0') {
		text_copy.append(text, textend - text);
		text = text_copy.c_str();
	}

	auto cur_x = lv_obj_get_x(label);
	auto new_x = cur_x;
	if (fs->textAlign & NVG_ALIGN_CENTER) {
		auto width = text ? lv_txt_get_width(text, strlen(text), font, 0, 0) : 0;
		new_x = lv_x - width / 2;
	} else if (fs->textAlign & NVG_ALIGN_RIGHT) {
		auto width = text ? lv_txt_get_width(text, strlen(text), font, 0, 0) : 0;
		new_x = lv_x - width;
	}
	if (new_x != cur_x) {
		lv_obj_set_x(label, new_x);
	}

	auto cur_col = lv_obj_get_style_text_color(label, LV_PART_MAIN);
	auto new_col = to_lv_text_color(fs->paint->innerColor);
	if (cur_col.full != new_col.full) {
		lv_obj_set_style_text_color(label, to_lv_text_color(fs->paint->innerColor), LV_PART_MAIN);
	}

	auto cur_text = lv_label_get_text(label);
	if (strcmp(cur_text, text) != 0) {
		lv_label_set_text(label, text);
	}

	return 1;
}

void renderTriangles(void *uptr,
					 NVGpaint *paint,
					 NVGcompositeOperationState compositeOperation,
					 NVGscissor *scissor,
					 const NVGvertex *verts,
					 int nverts,
					 float fringe) {
	auto context = get_drawcontext(uptr);

	if (auto rem = nverts % 6; rem != 0)
		nverts -= rem;

	for (auto i = 0; i < nverts; i += 6) {
		// dest rect
		auto d_tl = to_lv_point(verts[i], context->px_per_3U);
		auto d_br = to_lv_point(verts[i + 1], context->px_per_3U);

		// source rect:
		auto tx_width = context->textures[paint->image].w;
		auto tx_height = context->textures[paint->image].h;
		auto s_tl = lv_point_t{to_lv_coord(tx_width * verts[i].u, context->px_per_3U),
							   to_lv_coord(tx_height * verts[i].v, context->px_per_3U)};
		auto s_br = lv_point_t{to_lv_coord(tx_width * verts[i + 1].u, context->px_per_3U),
							   to_lv_coord(tx_height * verts[i + 1].v, context->px_per_3U)};

		(void)d_tl;
		(void)d_br;
		(void)s_tl;
		(void)s_br;

		// now copy with scaling
		// from context->textures[paint->image].pix[s_tl...s_br]
		// to lv_canvas buffer

		//ignore i+2, i+3, i+4, i+5
	}
}

void renderDelete(void *uptr) {
	if (uptr) {
		if (auto context = get_drawcontext(uptr)) {
			// printf("nanovg_pixbuf: renderDelete(): Delete DrawContext %p\n", context);
			delete context;
		}
	}
}

// Share the textures of GLNVGcontext 'otherUptr' if it's non-NULL.
int renderCreate(void *uptr, void *otherUptr) {
	return 1;
}

int renderCreateTexture(void *uptr, int type, int w, int h, int imageFlags, const unsigned char *data) {
	pr_dbg("renderCreateTexture: %d x %d, type %d, flags %d\n", w, h, type, imageFlags);

	auto context = get_drawcontext(uptr);

	Texture tx;
	tx.w = w;
	tx.h = h;
	tx.pix.resize(w * h);

	if (data) {
		// for (auto i = 0; auto c : std::span{data, size_t(w * h)}) {
		// tx.pix[i] = c; //what format is the data in?
		// }
	}

	context->textures.emplace_back(tx);
	return context->textures.size() - 1;
}

int renderDeleteTexture(void *uptr, int image) {
	pr_dbg("renderDeleteTexture\n");
	return 1;
}

int renderUpdateTexture(void *uptr, int image, int x, int y, int w, int h, const unsigned char *data) {
	pr_dbg("renderUpdateTexture (image=%d) %d x %d @ %d,%d\n", image, w, h, x, y);
	auto context = get_drawcontext(uptr);

	if (image < (int)context->textures.size()) {
		//copy data to context->textures[image]
	}

	return 1;
}
int renderGetTextureSize(void *uptr, int image, int *w, int *h) {
	pr_dbg("renderGetTextureSize\n");
	auto context = get_drawcontext(uptr);

	if (image < (int)context->textures.size()) {
		*w = context->textures[image].w;
		*h = context->textures[image].h;
		return 1;
	}

	return 0;
}

void renderViewport(void *uptr, float width, float height, float devicePixelRatio) {
	auto context = get_drawcontext(uptr);
	context->draw_frame_ctr++;
}

void renderCancel(void *uptr) {
	// printf("renderCancel\n");
}

void renderFlush(void *uptr) {
	auto context = get_drawcontext(uptr);

	// Hide all labels that were not re-drawn since the last renderViewport() (via nvgBeginFrame())
	for (auto &label : context->labels) {
		if (label.last_drawn_frame < context->draw_frame_ctr) {
			lv_label_set_text(label.label, "");
		}
	}
}

} // namespace MetaModule::NanoVG

NVGcontext *
nvgCreatePixelBufferContext(void *canvas, std::span<uint32_t> buffer, uint32_t buffer_width, uint32_t px_per_3U) {
	NVGparams params;
	NVGcontext *ctx = nullptr;

	using namespace MetaModule::NanoVG;

	memset(&params, 0, sizeof(params));
	params.renderCreate = renderCreate;
	params.renderCreateTexture = renderCreateTexture;
	params.renderDeleteTexture = renderDeleteTexture;
	params.renderUpdateTexture = renderUpdateTexture;
	params.renderGetTextureSize = renderGetTextureSize;
	params.renderViewport = renderViewport;
	params.renderCancel = renderCancel;
	params.renderFlush = renderFlush;
	params.renderFill = renderFill;
	params.renderStroke = renderStroke;
	params.renderTriangles = renderTriangles;
	params.renderDelete = renderDelete;
	params.renderText = renderText;

	auto draw_ctx = new DrawContext{(lv_obj_t *)canvas, buffer, buffer_width};
	dump_draw("Create new DrawContext %p with px_per_3U %u\n", draw_ctx, px_per_3U);
	draw_ctx->px_per_3U = px_per_3U;
	params.userPtr = draw_ctx;

	params.edgeAntiAlias = 0;

	ctx = nvgCreateInternal(&params, nullptr);

	if (ctx) {
		return ctx;
	} else {
		delete draw_ctx;
		return nullptr;
	}
}

void nvgDeletePixelBufferContext(NVGcontext *ctx) {
	dump_draw("Delete NVGcontext %p\n", ctx);
	if (ctx)
		nvgDeleteInternal(ctx);
}

void nvgluDeleteFramebuffer(NVGcontext *ctx) {
	// keep track of them?
}
