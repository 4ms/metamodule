#include "lvgl.h"
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <nanovg.h>

#define NANOVG_PIXELBUFFER_IMPLEMENTATION
#include <nanovg_gl.h>
#include <nanovg_gl_utils.h>

namespace MetaModule
{

struct DrawContext {
	lv_obj_t *canvas{};
};

// Share the textures of GLNVGcontext 'otherUptr' if it's non-NULL.
static int renderCreate(void *uptr, void *otherUptr) {
	printf("RenderCreate\n");
	return 1;
}

static int renderCreateTexture(void *uptr, int type, int w, int h, int imageFlags, const unsigned char *data) {
	printf("renderCreateTexture\n");
	return 1;
}

static int renderDeleteTexture(void *uptr, int image) {
	printf("renderDeleteTexture\n");
	return 1;
}

static int renderUpdateTexture(void *uptr, int image, int x, int y, int w, int h, const unsigned char *data) {
	printf("renderUpdateTexture\n");
	return 1;
}
static int renderGetTextureSize(void *uptr, int image, int *w, int *h) {
	printf("renderGetTextureSize\n");
	return 1;
}

static void renderViewport(void *uptr, float width, float height, float devicePixelRatio) {
	printf("renderViewport\n");
}

static void renderCancel(void *uptr) {
	printf("renderCancel\n");
}

static void renderFlush(void *uptr) {
	printf("renderFlush\n");
}

static void renderFill(void *uptr,
					   NVGpaint *paint,
					   NVGcompositeOperationState compositeOperation,
					   NVGscissor *scissor,
					   float fringe,
					   const float *bounds,
					   const NVGpath *paths,
					   int npaths) {
	printf("renderFill %d paths\n", npaths);
}

static void renderStroke(void *uptr,
						 NVGpaint *paint,
						 NVGcompositeOperationState compositeOperation,
						 NVGscissor *scissor,
						 float fringe,
						 float strokeWidth,
						 const NVGpath *paths,
						 int npaths) {

	auto canvas = (lv_obj_t *)uptr;
	// lv_canvas_draw_line(canvas, paths[0].stroke, paths[0].nstroke, )

	printf("renderStroke %d paths\n", npaths);
}

static void renderTriangles(void *uptr,
							NVGpaint *paint,
							NVGcompositeOperationState compositeOperation,
							NVGscissor *scissor,
							const NVGvertex *verts,
							int nverts,
							float fringe) {
	printf("renderTriangles %d verts\n", nverts);
}

static void renderDelete(void *uptr) {
	printf("renderDelete\n");
}

} // namespace MetaModule

NVGcontext *nvgCreatePixelBufferContext(lv_obj_t *canvas) {
	NVGparams params;
	NVGcontext *ctx = nullptr;

	memset(&params, 0, sizeof(params));
	params.renderCreate = MetaModule::renderCreate;
	params.renderCreateTexture = MetaModule::renderCreateTexture;
	params.renderDeleteTexture = MetaModule::renderDeleteTexture;
	params.renderUpdateTexture = MetaModule::renderUpdateTexture;
	params.renderGetTextureSize = MetaModule::renderGetTextureSize;
	params.renderViewport = MetaModule::renderViewport;
	params.renderCancel = MetaModule::renderCancel;
	params.renderFlush = MetaModule::renderFlush;
	params.renderFill = MetaModule::renderFill;
	params.renderStroke = MetaModule::renderStroke;
	params.renderTriangles = MetaModule::renderTriangles;
	params.renderDelete = MetaModule::renderDelete;

	auto draw_ctx = new MetaModule::DrawContext{canvas};
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
