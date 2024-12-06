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

DrawContext draw_ctx;

} // namespace MetaModule

// Share the textures of GLNVGcontext 'otherUptr' if it's non-NULL.
static int glnvg__renderCreate(void *uptr, void *otherUptr) {
	printf("RenderCreate\n");
	return 1;
}

static int glnvg__renderCreateTexture(void *uptr, int type, int w, int h, int imageFlags, const unsigned char *data) {
	printf("renderCreateTexture\n");
	return 1;
}

static int glnvg__renderDeleteTexture(void *uptr, int image) {
	printf("renderDeleteTexture\n");
	return 1;
}

static int glnvg__renderUpdateTexture(void *uptr, int image, int x, int y, int w, int h, const unsigned char *data) {
	printf("renderUpdateTexture\n");
	return 1;
}
static int glnvg__renderGetTextureSize(void *uptr, int image, int *w, int *h) {
	printf("renderGetTextureSize\n");
	return 1;
}

static void glnvg__renderViewport(void *uptr, float width, float height, float devicePixelRatio) {
	printf("renderViewport\n");
}

static void glnvg__renderCancel(void *uptr) {
	printf("renderCancel\n");
}

static void glnvg__renderFlush(void *uptr) {
	printf("renderFlush\n");
}

static void glnvg__renderFill(void *uptr,
							  NVGpaint *paint,
							  NVGcompositeOperationState compositeOperation,
							  NVGscissor *scissor,
							  float fringe,
							  const float *bounds,
							  const NVGpath *paths,
							  int npaths) {
	printf("renderFill %d paths\n", npaths);
}

static void glnvg__renderStroke(void *uptr,
								NVGpaint *paint,
								NVGcompositeOperationState compositeOperation,
								NVGscissor *scissor,
								float fringe,
								float strokeWidth,
								const NVGpath *paths,
								int npaths) {
	printf("renderStroke %d paths\n", npaths);
}

static void glnvg__renderTriangles(void *uptr,
								   NVGpaint *paint,
								   NVGcompositeOperationState compositeOperation,
								   NVGscissor *scissor,
								   const NVGvertex *verts,
								   int nverts,
								   float fringe) {
	printf("renderTriangles %d verts\n", nverts);
}

static void glnvg__renderDelete(void *uptr) {
	printf("renderDelete\n");
}

NVGcontext *nvgCreatePixelBufferContext() {
	NVGparams params;
	NVGcontext *ctx = nullptr;

	memset(&params, 0, sizeof(params));
	params.renderCreate = glnvg__renderCreate;
	params.renderCreateTexture = glnvg__renderCreateTexture;
	params.renderDeleteTexture = glnvg__renderDeleteTexture;
	params.renderUpdateTexture = glnvg__renderUpdateTexture;
	params.renderGetTextureSize = glnvg__renderGetTextureSize;
	params.renderViewport = glnvg__renderViewport;
	params.renderCancel = glnvg__renderCancel;
	params.renderFlush = glnvg__renderFlush;
	params.renderFill = glnvg__renderFill;
	params.renderStroke = glnvg__renderStroke;
	params.renderTriangles = glnvg__renderTriangles;
	params.renderDelete = glnvg__renderDelete;

	auto draw_ctx = new MetaModule::DrawContext;
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

void nvgluBindFramebuffer(NVGLUframebuffer *) {
}

NVGLUframebuffer *nvgluCreateFramebuffer(NVGcontext *ctx, int w, int h, int imageFlags) {

	NVGLUframebuffer *fb = nullptr;

	fb = (NVGLUframebuffer *)malloc(sizeof(NVGLUframebuffer));
	if (fb == nullptr)
		return nullptr;

	memset(fb, 0, sizeof(NVGLUframebuffer));

	// fb->image = nvgCreateImageRGBA(ctx, w, h, imageFlags | NVG_IMAGE_FLIPY | NVG_IMAGE_PREMULTIPLIED, NULL);
	// fb->texture = nvglImageHandleGL2(ctx, fb->image);
	fb->ctx = ctx;

	return fb;
}

void nvgluDeleteFramebuffer(NVGLUframebuffer *fb) {
	if (fb == nullptr)
		return;
	// if (fb->fbo != 0)
	// 	glDeleteFramebuffers(1, &fb->fbo);
	// if (fb->rbo != 0)
	// 	glDeleteRenderbuffers(1, &fb->rbo);
	// if (fb->image >= 0)
	// 	nvgDeleteImage(fb->ctx, fb->image);
	fb->ctx = nullptr;
	fb->fbo = 0;
	fb->rbo = 0;
	fb->texture = 0;
	fb->image = -1;
	free(fb);
}

void nvgBindFrameBuffer(NVGcontext *ctx, lv_obj_t *canvas) {
	if (ctx) {
		MetaModule::draw_ctx.canvas = canvas;
	}
}
