#include "CoreModules/elements/units.hh"
#include "lvgl.h"
#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <nanovg.h>
#include <span>
#include <vector>

#define NANOVG_PIXELBUFFER_IMPLEMENTATION
#include <nanovg_gl.h>
#include <nanovg_gl_utils.h>

namespace MetaModule
{

struct DrawContext {
	lv_obj_t *canvas{};
};

namespace NanoVG
{

constexpr lv_coord_t lv_coord(float x) {
	return std::round(mm_to_px(to_mm(x), 240));
}

constexpr lv_point_t to_lv_point(NVGvertex vertex) {
	return lv_point_t(lv_coord(vertex.x), lv_coord(vertex.y));
}

lv_obj_t *get_canvas_from_context(void *uptr) {
	auto ctx = (MetaModule::DrawContext *)(uptr);
	return ctx->canvas;
}

lv_color_t to_lv_color(NVGcolor color) {
	return lv_color_make(color.r * 255.f, color.g * 255.f, color.b * 255.f);
}

constexpr uint8_t to_lv_opa(NVGcolor color) {
	return std::round(color.a * float(LV_OPA_100));
}

void renderFill(void *uptr,
				NVGpaint *paint,
				NVGcompositeOperationState compositeOperation,
				NVGscissor *scissor,
				float fringe,
				const float *bounds,
				const NVGpath *paths,
				int npaths) {
	auto canvas = get_canvas_from_context(uptr);

	lv_draw_rect_dsc_t rect_dsc;
	lv_draw_rect_dsc_init(&rect_dsc);
	rect_dsc.bg_opa = to_lv_opa(paint->innerColor);
	rect_dsc.bg_color = to_lv_color(paint->innerColor);
	rect_dsc.radius = 0;

	lv_draw_line_dsc_t line_dsc;
	lv_draw_line_dsc_init(&line_dsc);
	line_dsc.color = to_lv_color(paint->innerColor);
	line_dsc.opa = to_lv_opa(paint->innerColor);
	line_dsc.width = 1;

	int16_t line_mask_id_1 = 0;
	int16_t line_mask_id_2 = 0;
	int16_t line_mask_id_3 = 0;
	int16_t line_mask_id_4 = 0;
	lv_draw_mask_line_param_t line_mask_param;
	if (scissor->extent[0] > 0) {

		auto w = lv_coord(scissor->extent[0] * 2);
		auto h = lv_coord(scissor->extent[1] * 2);
		auto x = lv_coord(scissor->xform[4] - scissor->extent[0]);
		auto y = lv_coord(scissor->xform[5] - scissor->extent[1]);
		lv_draw_mask_line_points_init(&line_mask_param, x, y, x + w, y, LV_DRAW_MASK_LINE_SIDE_BOTTOM);
		line_mask_id_1 = lv_draw_mask_add(&line_mask_param, nullptr);
		lv_draw_mask_line_points_init(&line_mask_param, x, y + h, x + w, y + h, LV_DRAW_MASK_LINE_SIDE_TOP);
		line_mask_id_2 = lv_draw_mask_add(&line_mask_param, nullptr);
		// lv_draw_mask_line_points_init(&line_mask_param, x, y, x, y + h, LV_DRAW_MASK_LINE_SIDE_LEFT);
		// line_mask_id_3 = lv_draw_mask_add(&line_mask_param, nullptr);
		// lv_draw_mask_line_points_init(&line_mask_param, x + w, y, x + w, y + h, LV_DRAW_MASK_LINE_SIDE_RIGHT);
		// line_mask_id_4 = lv_draw_mask_add(&line_mask_param, nullptr);
	}
	for (auto &path : std::span{paths, (size_t)npaths}) {
		std::vector<lv_point_t> points;

		std::ranges::transform(std::span{path.fill, (size_t)path.nfill}, std::back_inserter(points), to_lv_point);
		// [](NVGvertex v) { return to_lv_point(v); });

		// lv_canvas_draw_polygon(canvas, points.data(), points.size(), &rect_dsc);
		lv_canvas_draw_line(canvas, points.data(), points.size(), &line_dsc);

		// printf("Fill poly: ");
		// for (auto &p : points)
		// 	printf("%d,%d -> ", (int)p.x, (int)p.y);
		// printf("\n");
	}

	if (scissor->extent[0] > 0) {
		lv_draw_mask_remove_id(line_mask_id_1);
		lv_draw_mask_remove_id(line_mask_id_2);
		// lv_draw_mask_remove_id(line_mask_id_3);
		// lv_draw_mask_remove_id(line_mask_id_4);
		lv_draw_mask_free_param(&line_mask_param);
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

	auto canvas = get_canvas_from_context(uptr);

	lv_draw_line_dsc_t line_dsc;
	lv_draw_line_dsc_init(&line_dsc);
	line_dsc.color = to_lv_color(paint->innerColor);
	line_dsc.opa = to_lv_opa(paint->innerColor);
	line_dsc.width = 1;

	for (auto &path : std::span{paths, (size_t)npaths}) {
		std::vector<lv_point_t> points;

		std::ranges::transform(std::span{path.stroke, (size_t)path.nstroke}, std::back_inserter(points), to_lv_point);
		// [](NVGvertex v) { return to_lv_point(v); });

		lv_canvas_draw_line(canvas, points.data(), points.size(), &line_dsc);

		// printf("Draw line: ");
		// for (auto &p : points)
		// 	printf("%d,%d -> ", (int)p.x, (int)p.y);
		// printf("\n");
	}
}

void renderTriangles(void *uptr,
					 NVGpaint *paint,
					 NVGcompositeOperationState compositeOperation,
					 NVGscissor *scissor,
					 const NVGvertex *verts,
					 int nverts,
					 float fringe) {
	// printf("renderTriangles %d verts\n", nverts);
}

void renderDelete(void *uptr) {
	// printf("renderDelete\n");
}

// Share the textures of GLNVGcontext 'otherUptr' if it's non-NULL.
int renderCreate(void *uptr, void *otherUptr) {
	// printf("RenderCreate (canvas = %p)\n", get_canvas_from_context(uptr));
	return 1;
}

int renderCreateTexture(void *uptr, int type, int w, int h, int imageFlags, const unsigned char *data) {
	// printf("renderCreateTexture (canvas=%p): %d x %d (%p)\n", get_canvas_from_context(uptr), w, h, data);
	if (data) {
		// for (auto i = 0; auto c : std::span{data, size_t(w * h)}) {
		//TODO: copy pixels to canvas

		// 		printf("%02x ", c);
		// 		if (++i == w)
		// 			printf("\n");
		// }
		// 	printf("\n");
	}
	return 1;
}

int renderDeleteTexture(void *uptr, int image) {
	// printf("renderDeleteTexture\n");
	return 1;
}

int renderUpdateTexture(void *uptr, int image, int x, int y, int w, int h, const unsigned char *data) {
	// printf("renderUpdateTexture\n");
	return 1;
}
int renderGetTextureSize(void *uptr, int image, int *w, int *h) {
	// printf("renderGetTextureSize\n");
	return 1;
}

void renderViewport(void *uptr, float width, float height, float devicePixelRatio) {
	// printf("renderViewport\n");
}

void renderCancel(void *uptr) {
	// printf("renderCancel\n");
}

void renderFlush(void *uptr) {
	// printf("renderFlush\n");
}

} // namespace NanoVG

} // namespace MetaModule

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

	auto draw_ctx = new MetaModule::DrawContext{(lv_obj_t *)canvas};
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

void nvgluDeleteFramebuffer(NVGcontext *ctx) {
	// keep track of them?
}

// void nvgluBindFramebuffer(NVGLUframebuffer *) {
// }

// NVGLUframebuffer *nvgluCreateFramebuffer(NVGcontext *ctx, int w, int h, int imageFlags) {

// 	NVGLUframebuffer *fb = nullptr;

// 	fb = (NVGLUframebuffer *)malloc(sizeof(NVGLUframebuffer));
// 	if (fb == nullptr)
// 		return nullptr;

// 	memset(fb, 0, sizeof(NVGLUframebuffer));

// 	// fb->image = nvgCreateImageRGBA(ctx, w, h, imageFlags | NVG_IMAGE_FLIPY | NVG_IMAGE_PREMULTIPLIED, NULL);
// 	// fb->texture = nvglImageHandleGL2(ctx, fb->image);
// 	fb->ctx = ctx;

// 	return fb;
// }

// void nvgluDeleteFramebuffer(NVGLUframebuffer *fb) {
// 	if (fb == nullptr)
// 		return;
// 	// if (fb->fbo != 0)
// 	// 	glDeleteFramebuffers(1, &fb->fbo);
// 	// if (fb->rbo != 0)
// 	// 	glDeleteRenderbuffers(1, &fb->rbo);
// 	// if (fb->image >= 0)
// 	// 	nvgDeleteImage(fb->ctx, fb->image);
// 	fb->ctx = nullptr;
// 	fb->fbo = 0;
// 	fb->rbo = 0;
// 	fb->texture = 0;
// 	fb->image = -1;
// 	free(fb);
// }

// void nvgBindFrameBuffer(NVGcontext *ctx, lv_obj_t *canvas) {
// 	if (ctx) {
// 		MetaModule::draw_ctx.canvas = canvas;
// 	}
// }
