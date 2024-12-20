#include "CoreModules/elements/units.hh"
#include "gui/fonts/fonts.hh"
#include "lvgl.h"
#include "nanovg_pixbuf_drawctx.hh"
#include "nanovg_pixbuf_util.hh"
#include <algorithm>
#include <cmath>
#include <cstdlib>
#include <cstring>
#include <nanovg.h>
#include <span>
#include <string>
#include <vector>

#include "console/pr_dbg.hh"
#include "medium/debug_raw.h"

namespace MetaModule::NanoVG
{

void renderFill(void *uptr,
				NVGpaint *paint,
				NVGcompositeOperationState compositeOperation,
				NVGscissor *scissor,
				float fringe,
				const float *bounds,
				const NVGpath *paths,
				int npaths) {

	if (npaths < 0 || npaths > 1024) {
		pr_dbg("Invalid number of paths in RenderFill: %d\n", npaths);
		return;
	}
	if (paths[0].fill[0].x > 10000.f || paths[0].fill[0].y > 10000.f) {
		pr_dbg("Invalid point in renderFill (point [0] is %f, %f)\n", paths[0].fill[0].x, paths[0].fill[0].y);
		return;
	}

	auto context = get_drawcontext(uptr);

	context->line_dsc.color = to_lv_color(paint->innerColor);
	context->line_dsc.opa = to_lv_opa(paint->innerColor);

	context->rect_dsc.bg_opa = to_lv_opa(paint->innerColor);
	context->rect_dsc.bg_color = to_lv_color(paint->innerColor);

	for (auto &path : std::span{paths, (size_t)npaths}) {
		std::vector<lv_point_t> points;

		std::ranges::transform(std::span{path.fill, (size_t)path.nfill}, std::back_inserter(points), to_lv_point);

		if (is_poly_concave(points)) {
			// LVGL lv_canvas_draw_polygon goes into an infinite loop if polygon is concave.
			// Fall back to drawing polygon outline (unfilled) if it's concave
			lv_canvas_draw_line(context->canvas, points.data(), points.size(), &context->line_dsc);
		} else {
			lv_canvas_draw_polygon(context->canvas, points.data(), points.size(), &context->rect_dsc);
		}
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
		pr_dbg("Invalid number of paths in RenderFill: %d\n", npaths);
		return;
	}
	if (paths[0].stroke[0].x > 10000.f || paths[0].stroke[0].y > 10000.f) {
		pr_dbg("Invalid point in renderStroke (point [0] is %f, %f)\n", paths[0].stroke[0].x, paths[0].stroke[0].y);
		return;
	}

	context->line_dsc.color = to_lv_color(paint->innerColor);
	context->line_dsc.opa = to_lv_opa(paint->innerColor);

	for (auto &path : std::span{paths, (size_t)npaths}) {
		std::vector<lv_point_t> points;

		std::ranges::transform(std::span{path.stroke, (size_t)path.nstroke}, std::back_inserter(points), to_lv_point);

		lv_canvas_draw_line(context->canvas, points.data(), points.size(), &context->line_dsc);
	}
}

float renderText(
	void *uptr, float x, float y, float max_w, const char *text, const char *textend, struct NVGFontState *fs) {
	auto context = get_drawcontext(uptr);
	auto canvas = context->canvas;

	DebugPin1High(); // really debug 0

	// Move to position
	auto lv_x = to_lv_coord(x + fs->xform[4]);
	auto lv_y = to_lv_coord(y + fs->xform[5]);

	auto lv_font_size = to_lv_coord(corrected_ttf_size(fs->fontSize, fs->fontName));
	auto font = get_ttf_font(std::string(fs->fontName), lv_font_size);
	if (!font)
		return 0;

	// Create or find existing label (match on X,Y pos)
	lv_obj_t *label{};
	auto found = std::ranges::find_if(context->labels, [=](TextRenderCacheEntry const &cached) {
		return cached.x == lv_x && cached.y == lv_y && cached.align == fs->textAlign;
	});

	if (found != context->labels.end()) {
		label = found->label;
	} else {

		auto align = fs->textAlign & NVG_ALIGN_LEFT	  ? LV_TEXT_ALIGN_LEFT :
					 fs->textAlign & NVG_ALIGN_RIGHT  ? LV_TEXT_ALIGN_RIGHT :
					 fs->textAlign & NVG_ALIGN_CENTER ? LV_TEXT_ALIGN_CENTER :
														LV_TEXT_ALIGN_LEFT;

		// Align vertically
		auto align_lv_y = lv_y - (fs->textAlign & NVG_ALIGN_BASELINE ? lv_font_size * 0.8f :
								  fs->textAlign & NVG_ALIGN_BOTTOM	 ? lv_font_size * 1.2f :
								  fs->textAlign & NVG_ALIGN_MIDDLE	 ? lv_font_size * 0.5f :
								  fs->textAlign & NVG_ALIGN_TOP		 ? 0 :
																	   lv_font_size * 1.0f);

		label = lv_label_create(canvas);
		lv_obj_set_pos(label, lv_x, align_lv_y);
		lv_obj_set_size(label, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
		lv_obj_set_style_text_font(label, font, LV_PART_MAIN);
		lv_obj_set_style_text_opa(label, to_lv_opa(fs->paint->innerColor), LV_PART_MAIN);
		lv_obj_set_style_text_align(label, align, LV_PART_MAIN);

		lv_obj_set_style_text_line_space(label, 0, LV_PART_MAIN);
		auto letter_space = corrected_ttf_letter_spacing(fs->fontSize, fs->fontName);
		lv_obj_set_style_text_letter_space(label, letter_space, LV_PART_MAIN);

		// lv_obj_set_style_border_color(label, lv_color_hex(0xFF0000), LV_PART_MAIN);
		// lv_obj_set_style_border_opa(label, LV_OPA_50, LV_PART_MAIN);
		// lv_obj_set_style_border_width(label, 1, LV_PART_MAIN);

		pr_dbg("Creating label at %d,%d align %d (sz %f)\n", lv_x, lv_y, fs->textAlign, fs->fontSize);
		pr_dbg("Canvas is %d,%d\n", lv_obj_get_width(canvas), lv_obj_get_height(canvas), fs->textAlign, fs->fontSize);
		context->labels.emplace_back(lv_x, lv_y, fs->textAlign, label);
	}

	if (text == nullptr)
		text = "";

	// Handle case were text doesn't have a null terminator (which LVGL needs)
	std::string text_copy;
	if (textend && *textend != '\0') {
		text_copy.append(text, textend - text);
		text = text_copy.c_str();
	}

	if (fs->textAlign & NVG_ALIGN_CENTER) {
		auto width = text ? lv_txt_get_width(text, strlen(text), font, 0, 0) : 0;
		lv_obj_set_x(label, lv_x - width / 2);
	}
	if (fs->textAlign & NVG_ALIGN_RIGHT) {
		auto width = text ? lv_txt_get_width(text, strlen(text), font, 0, 0) : 0;
		lv_obj_set_x(label, lv_x - width);
	}

	lv_obj_set_style_text_color(label, to_lv_text_color(fs->paint->innerColor), LV_PART_MAIN);
	lv_label_set_text(label, text);

	DebugPin1Low(); //really debug 0

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
		auto d_tl = to_lv_point(verts[i]);
		auto d_br = to_lv_point(verts[i + 1]);

		// source rect:
		auto tx_width = context->textures[paint->image].w;
		auto tx_height = context->textures[paint->image].h;
		auto s_tl = lv_point_t{to_lv_coord(tx_width * verts[i].u), to_lv_coord(tx_height * verts[i].v)};
		auto s_br = lv_point_t{to_lv_coord(tx_width * verts[i + 1].u), to_lv_coord(tx_height * verts[i + 1].v)};

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
	// pr_dbg("renderDelete\n");
	if (uptr) {
		if (auto context = get_drawcontext(uptr))
			delete context;
	}
}

// Share the textures of GLNVGcontext 'otherUptr' if it's non-NULL.
int renderCreate(void *uptr, void *otherUptr) {
	// pr_dbg("RenderCreate\n");
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
	pr_dbg("renderViewport %f x %f, %f\n", width, height, devicePixelRatio);
}

void renderCancel(void *uptr) {
	// printf("renderCancel\n");
}

void renderFlush(void *uptr) {
	// printf("renderFlush\n");
}

} // namespace MetaModule::NanoVG

NVGcontext *nvgCreatePixelBufferContext(void *canvas) {
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

	auto draw_ctx = new DrawContext{(lv_obj_t *)canvas};
	params.userPtr = draw_ctx;

	params.edgeAntiAlias = 0;

	ctx = nvgCreateInternal(&params, nullptr);

	if (ctx) {
		draw_ctx->parent_ctx = ctx;
		return ctx;
	} else {
		delete draw_ctx;
		return nullptr;
	}
}

void nvgDeletePixelBufferContext(NVGcontext *ctx) {
	// pr_dbg("nvgDeletePixelBufferContext\n");
	if (ctx)
		nvgDeleteInternal(ctx);
}

void nvgluDeleteFramebuffer(NVGcontext *ctx) {
	// keep track of them?
}
