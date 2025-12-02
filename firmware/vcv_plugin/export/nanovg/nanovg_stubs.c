// Stubs for nanovg (for headless operation)

#include "nanovg.h"
#include <memory.h>

NVGcontext *nvgCreateInternal(NVGparams *params, NVGcontext *other) {
	return NULL;
}

NVGparams *nvgInternalParams(NVGcontext *ctx) {
	return NULL;
}

void nvgDeleteInternal(NVGcontext *ctx) {
}

void nvgBeginFrame(NVGcontext *ctx, float windowWidth, float windowHeight, float devicePixelRatio) {
}

void nvgCancelFrame(NVGcontext *ctx) {
}

void nvgEndFrame(NVGcontext *ctx) {
}

NVGcolor nvgRGB(unsigned char r, unsigned char g, unsigned char b) {
	NVGcolor c;
	return c;
}

NVGcolor nvgRGBf(float r, float g, float b) {
	NVGcolor c;
	return c;
}

NVGcolor nvgRGBA(unsigned char r, unsigned char g, unsigned char b, unsigned char a) {
	NVGcolor c;
	return c;
}

NVGcolor nvgRGBAf(float r, float g, float b, float a) {
	NVGcolor c;
	return c;
}

NVGcolor nvgTransRGBA(NVGcolor c, unsigned char a) {
	return c;
}

NVGcolor nvgTransRGBAf(NVGcolor c, float a) {
	return c;
}

NVGcolor nvgLerpRGBA(NVGcolor c0, NVGcolor c1, float u) {
	NVGcolor c;
	return c;
}

NVGcolor nvgHSL(float h, float s, float l) {
	NVGcolor c;
	return c;
}

NVGcolor nvgHSLA(float h, float s, float l, unsigned char a) {
	NVGcolor c;
	return c;
}

void nvgTransformIdentity(float *t) {
}

void nvgTransformTranslate(float *t, float tx, float ty) {
}

void nvgTransformScale(float *t, float sx, float sy) {
}

void nvgTransformRotate(float *t, float a) {
}

void nvgTransformSkewX(float *t, float a) {
}

void nvgTransformSkewY(float *t, float a) {
}

void nvgTransformMultiply(float *t, const float *s) {
}

void nvgTransformPremultiply(float *t, const float *s) {
}

int nvgTransformInverse(float *inv, const float *t) {
	return 0;
}

void nvgTransformPoint(float *dx, float *dy, const float *t, float sx, float sy) {
}

float nvgDegToRad(float deg) {
	return deg / 180.0f * NVG_PI;
}

float nvgRadToDeg(float rad) {
	return rad / NVG_PI * 180.0f;
}

// State handling
void nvgSave(NVGcontext *ctx) {
}

void nvgRestore(NVGcontext *ctx) {
}

void nvgReset(NVGcontext *ctx) {
}

// State setting
void nvgShapeAntiAlias(NVGcontext *ctx, int enabled) {
}

void nvgStrokeWidth(NVGcontext *ctx, float width) {
}

void nvgMiterLimit(NVGcontext *ctx, float limit) {
}

void nvgLineCap(NVGcontext *ctx, int cap) {
}

void nvgLineJoin(NVGcontext *ctx, int join) {
}

void nvgGlobalAlpha(NVGcontext *ctx, float alpha) {
}

void nvgGlobalTint(NVGcontext *ctx, NVGcolor tint) {
}

NVGcolor nvgGetGlobalTint(NVGcontext *ctx) {
	NVGcolor c;
	return c;
}

void nvgAlpha(NVGcontext *ctx, float alpha) {
}

void nvgTint(NVGcontext *ctx, NVGcolor tint) {
}

void nvgTransform(NVGcontext *ctx, float a, float b, float c, float d, float e, float f) {
}

void nvgResetTransform(NVGcontext *ctx) {
}

void nvgTranslate(NVGcontext *ctx, float x, float y) {
}

void nvgRotate(NVGcontext *ctx, float angle) {
}

void nvgSkewX(NVGcontext *ctx, float angle) {
}

void nvgSkewY(NVGcontext *ctx, float angle) {
}

void nvgScale(NVGcontext *ctx, float x, float y) {
}

void nvgCurrentTransform(NVGcontext *ctx, float *xform) {
}

void nvgStrokeColor(NVGcontext *ctx, NVGcolor color) {
}

void nvgStrokePaint(NVGcontext *ctx, NVGpaint paint) {
}

void nvgFillColor(NVGcontext *ctx, NVGcolor color) {
}

void nvgFillPaint(NVGcontext *ctx, NVGpaint paint) {
}

int nvgCreateImageRGBA(NVGcontext *ctx, int w, int h, int imageFlags, const unsigned char *data) {
	return -1;
}

void nvgUpdateImage(NVGcontext *ctx, int image, const unsigned char *data) {
}

void nvgImageSize(NVGcontext *ctx, int image, int *w, int *h) {
}

void nvgDeleteImage(NVGcontext *ctx, int image) {
}

NVGpaint nvgLinearGradient(NVGcontext *ctx, float sx, float sy, float ex, float ey, NVGcolor icol, NVGcolor ocol) {
	NVGpaint p;
	return p;
}

NVGpaint nvgRadialGradient(NVGcontext *ctx, float cx, float cy, float inr, float outr, NVGcolor icol, NVGcolor ocol) {
	NVGpaint p;
	return p;
}

NVGpaint
nvgBoxGradient(NVGcontext *ctx, float x, float y, float w, float h, float r, float f, NVGcolor icol, NVGcolor ocol) {
	NVGpaint p;
	return p;
}

NVGpaint nvgImagePattern(NVGcontext *ctx, float cx, float cy, float w, float h, float angle, int image, float alpha) {
	NVGpaint p;
	return p;
}

// Scissoring
void nvgScissor(NVGcontext *ctx, float x, float y, float w, float h) {
}

void nvgIntersectScissor(NVGcontext *ctx, float x, float y, float w, float h) {
}

void nvgResetScissor(NVGcontext *ctx) {
}

// Global composite operation.
void nvgGlobalCompositeOperation(NVGcontext *ctx, int op) {
}

void nvgGlobalCompositeBlendFunc(NVGcontext *ctx, int sfactor, int dfactor) {
}

void nvgGlobalCompositeBlendFuncSeparate(NVGcontext *ctx, int srcRGB, int dstRGB, int srcAlpha, int dstAlpha) {
}

// Draw
void nvgBeginPath(NVGcontext *ctx) {
}

void nvgMoveTo(NVGcontext *ctx, float x, float y) {
}

void nvgLineTo(NVGcontext *ctx, float x, float y) {
}

void nvgBezierTo(NVGcontext *ctx, float c1x, float c1y, float c2x, float c2y, float x, float y) {
}

void nvgQuadTo(NVGcontext *ctx, float cx, float cy, float x, float y) {
}

void nvgArcTo(NVGcontext *ctx, float x1, float y1, float x2, float y2, float radius) {
}

void nvgClosePath(NVGcontext *ctx) {
}

void nvgPathWinding(NVGcontext *ctx, int dir) {
}

void nvgArc(NVGcontext *ctx, float cx, float cy, float r, float a0, float a1, int dir) {
}

void nvgRect(NVGcontext *ctx, float x, float y, float w, float h) {
}

void nvgRoundedRect(NVGcontext *ctx, float x, float y, float w, float h, float r) {
}

void nvgRoundedRectVarying(NVGcontext *ctx,
						   float x,
						   float y,
						   float w,
						   float h,
						   float radTopLeft,
						   float radTopRight,
						   float radBottomRight,
						   float radBottomLeft) {
}

void nvgEllipse(NVGcontext *ctx, float cx, float cy, float rx, float ry) {
}

void nvgCircle(NVGcontext *ctx, float cx, float cy, float r) {
}

void nvgDebugDumpPathCache(NVGcontext *ctx) {
}

void nvgFill(NVGcontext *ctx) {
}

void nvgStroke(NVGcontext *ctx) {
}

// Add fonts
int nvgCreateFont(NVGcontext *ctx, const char *name, const char *filename) {
	return -1;
}

int nvgCreateFontAtIndex(NVGcontext *ctx, const char *name, const char *filename, const int fontIndex) {
	return -1;
}

int nvgCreateFontMem(NVGcontext *ctx, const char *name, unsigned char *data, int ndata, int freeData) {
	return -1;
}

int nvgCreateFontMemAtIndex(
	NVGcontext *ctx, const char *name, unsigned char *data, int ndata, int freeData, const int fontIndex) {
	return -1;
}

int nvgFindFont(NVGcontext *ctx, const char *name) {
	return -1;
}

int nvgAddFallbackFontId(NVGcontext *ctx, int baseFont, int fallbackFont) {
	return -1;
}

int nvgAddFallbackFont(NVGcontext *ctx, const char *baseFont, const char *fallbackFont) {
	return nvgAddFallbackFontId(ctx, nvgFindFont(ctx, baseFont), nvgFindFont(ctx, fallbackFont));
}

void nvgResetFallbackFontsId(NVGcontext *ctx, int baseFont) {
}

void nvgResetFallbackFonts(NVGcontext *ctx, const char *baseFont) {
}

// State setting
void nvgFontSize(NVGcontext *ctx, float size) {
}

void nvgFontBlur(NVGcontext *ctx, float blur) {
}

void nvgTextLetterSpacing(NVGcontext *ctx, float spacing) {
}

void nvgTextLineHeight(NVGcontext *ctx, float lineHeight) {
}

void nvgTextAlign(NVGcontext *ctx, int align) {
}

void nvgFontFaceId(NVGcontext *ctx, int font) {
}

void nvgFontFace(NVGcontext *ctx, const char *font) {
}

float nvgText(NVGcontext *ctx, float x, float y, const char *string, const char *end) {
	return 0;
}

void nvgTextBox(NVGcontext *ctx, float x, float y, float breakRowWidth, const char *string, const char *end) {
}

int nvgTextGlyphPositions(NVGcontext *ctx,
						  float x,
						  float y,
						  const char *string,
						  const char *end,
						  NVGglyphPosition *positions,
						  int maxPositions) {
	return 0;
}

int nvgTextBreakLines(
	NVGcontext *ctx, const char *string, const char *end, float breakRowWidth, NVGtextRow *rows, int maxRows) {
	return 0;
}

float nvgTextBounds(NVGcontext *ctx, float x, float y, const char *string, const char *end, float *bounds) {
	return 0;
}

void nvgTextBoxBounds(
	NVGcontext *ctx, float x, float y, float breakRowWidth, const char *string, const char *end, float *bounds) {
}

void nvgTextMetrics(NVGcontext *ctx, float *ascender, float *descender, float *lineh) {
}

int nvgCreateImage(NVGcontext *ctx, const char *filename, int imageFlags) {
	return -1;
}

int nvgCreateImageMem(NVGcontext *ctx, int imageFlags, unsigned char *data, int ndata) {
	return -1;
}
