//
// Copyright (c) 2013 Mikko Mononen memon@inside.org
//
// This software is provided 'as-is', without any express or implied
// warranty.  In no event will the authors be held liable for any damages
// arising from the use of this software.
// Permission is granted to anyone to use this software for any purpose,
// including commercial applications, and to alter it and redistribute it
// freely, subject to the following restrictions:
// 1. The origin of this software must not be misrepresented; you must not
//    claim that you wrote the original software. If you use this software
//    in a product, an acknowledgment in the product documentation would be
//    appreciated but is not required.
// 2. Altered source versions must be plainly marked as such, and must not be
//    misrepresented as being the original software.
// 3. This notice may not be removed or altered from any source distribution.
//
//
// Modified by Dan Green 2024 for use with MetaModule

#pragma once

struct NVGcolor {
	union {
		float rgba[4];
		struct {
			float r, g, b, a;
		};
	};
};

struct NVGpaint {
	float xform[6];
	float extent[2];
	float radius;
	float feather;
	NVGcolor innerColor;
	NVGcolor outerColor;
	int image;
};

using NVGpaint = struct NVGpaint;

enum NVGwinding {
	NVG_CCW = 1, // Winding for solid shapes
	NVG_CW = 2,	 // Winding for holes
};

enum NVGsolidity {
	NVG_SOLID = 1, // CCW
	NVG_HOLE = 2,  // CW
};

enum NVGlineCap {
	NVG_BUTT,
	NVG_ROUND,
	NVG_SQUARE,
	NVG_BEVEL,
	NVG_MITER,
};

enum NVGalign {
	// Horizontal align
	NVG_ALIGN_LEFT = 1 << 0,   // Default, align text horizontally to left.
	NVG_ALIGN_CENTER = 1 << 1, // Align text horizontally to center.
	NVG_ALIGN_RIGHT = 1 << 2,  // Align text horizontally to right.
	// Vertical align
	NVG_ALIGN_TOP = 1 << 3,		 // Align text vertically to top.
	NVG_ALIGN_MIDDLE = 1 << 4,	 // Align text vertically to middle.
	NVG_ALIGN_BOTTOM = 1 << 5,	 // Align text vertically to bottom.
	NVG_ALIGN_BASELINE = 1 << 6, // Default, align text vertically to baseline.
};

enum NVGblendFactor {
	NVG_ZERO = 1 << 0,
	NVG_ONE = 1 << 1,
	NVG_SRC_COLOR = 1 << 2,
	NVG_ONE_MINUS_SRC_COLOR = 1 << 3,
	NVG_DST_COLOR = 1 << 4,
	NVG_ONE_MINUS_DST_COLOR = 1 << 5,
	NVG_SRC_ALPHA = 1 << 6,
	NVG_ONE_MINUS_SRC_ALPHA = 1 << 7,
	NVG_DST_ALPHA = 1 << 8,
	NVG_ONE_MINUS_DST_ALPHA = 1 << 9,
	NVG_SRC_ALPHA_SATURATE = 1 << 10,
};

enum NVGcompositeOperation {
	NVG_SOURCE_OVER,
	NVG_SOURCE_IN,
	NVG_SOURCE_OUT,
	NVG_ATOP,
	NVG_DESTINATION_OVER,
	NVG_DESTINATION_IN,
	NVG_DESTINATION_OUT,
	NVG_DESTINATION_ATOP,
	NVG_LIGHTER,
	NVG_COPY,
	NVG_XOR,
};

struct NVGcompositeOperationState {
	int srcRGB;
	int dstRGB;
	int srcAlpha;
	int dstAlpha;
};

struct NVGglyphPosition {
	const char *str;  // Position of the glyph in the input string.
	float x;		  // The x-coordinate of the logical glyph position.
	float minx, maxx; // The bounds of the glyph shape.
};

struct NVGtextRow {
	const char *start; // Pointer to the input text where the row starts.
	const char *end;   // Pointer to the input text where the row ends (one past the last character).
	const char *next;  // Pointer to the beginning of the next row.
	float width;	   // Logical width of the row.
	float minx,
		maxx; // Actual bounds of the row. Logical with and bounds can differ because of kerning and some parts over extending.
};

enum NVGimageFlags {
	NVG_IMAGE_GENERATE_MIPMAPS = 1 << 0, // Generate mipmaps during creation of the image.
	NVG_IMAGE_REPEATX = 1 << 1,			 // Repeat image in X direction.
	NVG_IMAGE_REPEATY = 1 << 2,			 // Repeat image in Y direction.
	NVG_IMAGE_FLIPY = 1 << 3,			 // Flips (inverses) image in Y direction when rendered.
	NVG_IMAGE_PREMULTIPLIED = 1 << 4,	 // Image data has premultiplied alpha.
	NVG_IMAGE_NEAREST = 1 << 5,			 // Image interpolation is Nearest instead Linear
};

struct NVGcontext {};
struct NVGLUframebuffer {};

// clang-format off
inline void nvgBeginFrame(NVGcontext* ctx, float windowWidth, float windowHeight, float devicePixelRatio) {}
inline void nvgCancelFrame(NVGcontext* ctx) {}
inline void nvgEndFrame(NVGcontext* ctx) {}
inline void nvgGlobalCompositeOperation(NVGcontext* ctx, int op) {}
inline void nvgGlobalCompositeBlendFunc(NVGcontext* ctx, int sfactor, int dfactor) {}
inline void nvgGlobalCompositeBlendFuncSeparate(NVGcontext* ctx, int srcRGB, int dstRGB, int srcAlpha, int dstAlpha) {}
inline NVGcolor nvgRGB(unsigned char r, unsigned char g, unsigned char b) { 
	return {.r = r / 255.0f, .g = g / 255.0f, .b = b / 255.0f, .a = 1.f};
}
inline NVGcolor nvgRGBf(float r, float g, float b) { 
	return {{{r, g, b, 1.f}}};
}
inline NVGcolor nvgRGBA(unsigned char r, unsigned char g, unsigned char b, unsigned char a) {
	return {.r = r / 255.0f, .g = g / 255.0f, .b = b / 255.0f, .a = a / 255.f};
}
inline NVGcolor nvgRGBAf(float r, float g, float b, float a) {
	return {{{r, g, b, a}}};
}

inline NVGcolor nvgLerpRGBA(NVGcolor c0, NVGcolor c1, float u) { return {}; }
inline NVGcolor nvgTransRGBA(NVGcolor c0, unsigned char a) { return {}; }
inline NVGcolor nvgTransRGBAf(NVGcolor c0, float a) { return {}; }
inline NVGcolor nvgHSL(float h, float s, float l) { return {}; }
inline NVGcolor nvgHSLA(float h, float s, float l, unsigned char a) { return {}; }
inline void nvgSave(NVGcontext *ctx) {}
inline void nvgRestore(NVGcontext *ctx) {}
inline void nvgReset(NVGcontext *ctx) {}
inline void nvgShapeAntiAlias(NVGcontext *ctx, int enabled) {}
inline void nvgStrokeColor(NVGcontext *ctx, NVGcolor color) {}
inline void nvgStrokePaint(NVGcontext *ctx, NVGpaint paint) {}
inline void nvgFillColor(NVGcontext *ctx, NVGcolor color) {}
inline void nvgFillPaint(NVGcontext *ctx, NVGpaint paint) {}
inline void nvgMiterLimit(NVGcontext *ctx, float limit) {}
inline void nvgStrokeWidth(NVGcontext *ctx, float size) {}
inline void nvgLineCap(NVGcontext *ctx, int cap) {}
inline void nvgLineJoin(NVGcontext *ctx, int join) {}
inline void nvgGlobalAlpha(NVGcontext *ctx, float alpha) {}
inline void nvgGlobalTint(NVGcontext *ctx, NVGcolor tint) {}
inline NVGcolor nvgGetGlobalTint(NVGcontext *ctx) { return {}; }
inline void nvgAlpha(NVGcontext *ctx, float alpha) {}
inline void nvgTint(NVGcontext *ctx, NVGcolor tint) {}
inline void nvgResetTransform(NVGcontext *ctx) {}
inline void nvgTransform(NVGcontext *ctx, float a, float b, float c, float d, float e, float f) {}
inline void nvgTranslate(NVGcontext *ctx, float x, float y) {}
inline void nvgRotate(NVGcontext *ctx, float angle) {}
inline void nvgSkewX(NVGcontext *ctx, float angle) {}
inline void nvgSkewY(NVGcontext *ctx, float angle) {}
inline void nvgScale(NVGcontext *ctx, float x, float y) {}
inline void nvgCurrentTransform(NVGcontext *ctx, float *xform) {}
inline void nvgTransformIdentity(float *dst) {}
inline void nvgTransformTranslate(float *dst, float tx, float ty) {}
inline void nvgTransformScale(float *dst, float sx, float sy) {}
inline void nvgTransformRotate(float *dst, float a) {}
inline void nvgTransformSkewX(float *dst, float a) {}
inline void nvgTransformSkewY(float *dst, float a) {}
inline void nvgTransformMultiply(float *dst, const float *src) {}
inline void nvgTransformPremultiply(float *dst, const float *src) {}
inline int nvgTransformInverse(float *dst, const float *src) { return {}; }
inline void nvgTransformPoint(float *dstx, float *dsty, const float *xform, float srcx, float srcy) {}
inline float nvgDegToRad(float deg) { return {}; }
inline float nvgRadToDeg(float rad) { return {}; }
inline int nvgCreateImage(NVGcontext *ctx, const char *filename, int imageFlags) { return {}; }
inline int nvgCreateImageMem(NVGcontext *ctx, int imageFlags, unsigned char *data, int ndata) { return {}; }
inline int nvgCreateImageRGBA(NVGcontext *ctx, int w, int h, int imageFlags, const unsigned char *data) { return {}; }
inline void nvgUpdateImage(NVGcontext *ctx, int image, const unsigned char *data) {}
inline void nvgImageSize(NVGcontext *ctx, int image, int *w, int *h) {}
inline void nvgDeleteImage(NVGcontext *ctx, int image) {}
inline NVGpaint nvgLinearGradient(NVGcontext *ctx, float sx, float sy, float ex, float ey, NVGcolor icol, NVGcolor ocol) { return {}; }
inline NVGpaint nvgBoxGradient(NVGcontext *ctx, float x, float y, float w, float h, float r, float f, NVGcolor icol, NVGcolor ocol) { return {}; }
inline NVGpaint nvgRadialGradient(NVGcontext *ctx, float cx, float cy, float inr, float outr, NVGcolor icol, NVGcolor ocol) { return {}; }
inline NVGpaint nvgImagePattern(NVGcontext *ctx, float ox, float oy, float ex, float ey, float angle, int image, float alpha) { return {}; }
inline void nvgScissor(NVGcontext *ctx, float x, float y, float w, float h) {}
inline void nvgIntersectScissor(NVGcontext *ctx, float x, float y, float w, float h) {}
inline void nvgResetScissor(NVGcontext *ctx) {}
inline void nvgBeginPath(NVGcontext *ctx) {}
inline void nvgMoveTo(NVGcontext *ctx, float x, float y) {}
inline void nvgLineTo(NVGcontext *ctx, float x, float y) {}
inline void nvgBezierTo(NVGcontext *ctx, float c1x, float c1y, float c2x, float c2y, float x, float y) {}
inline void nvgQuadTo(NVGcontext *ctx, float cx, float cy, float x, float y) {}
inline void nvgArcTo(NVGcontext *ctx, float x1, float y1, float x2, float y2, float radius) {}
inline void nvgClosePath(NVGcontext *ctx) {}
inline void nvgPathWinding(NVGcontext *ctx, int dir) {}
inline void nvgArc(NVGcontext *ctx, float cx, float cy, float r, float a0, float a1, int dir) {}
inline void nvgRect(NVGcontext *ctx, float x, float y, float w, float h) {}
inline void nvgRoundedRect(NVGcontext *ctx, float x, float y, float w, float h, float r) {}
inline void nvgRoundedRectVarying(NVGcontext *ctx, float, float, float, float, float, float, float, float) {}
inline void nvgEllipse(NVGcontext *ctx, float cx, float cy, float rx, float ry) {}
inline void nvgCircle(NVGcontext *ctx, float cx, float cy, float r) {}
inline void nvgFill(NVGcontext *ctx) {}
inline void nvgStroke(NVGcontext *ctx) {}
inline int nvgCreateFont(NVGcontext *ctx, const char *name, const char *filename) { return {}; }
inline int nvgCreateFontAtIndex(NVGcontext *ctx, const char *name, const char *filename, const int fontIndex) { return {}; }
inline int nvgCreateFontMem(NVGcontext *ctx, const char *name, unsigned char *data, int ndata, int freeData) { return {}; }
inline int nvgCreateFontMemAtIndex( NVGcontext *ctx, const char *name, unsigned char *data, int ndata, int freeData, const int fontIndex) { return {}; }
inline int nvgFindFont(NVGcontext *ctx, const char *name) { return {}; }
inline int nvgAddFallbackFontId(NVGcontext *ctx, int baseFont, int fallbackFont) { return {}; }
inline int nvgAddFallbackFont(NVGcontext *ctx, const char *baseFont, const char *fallbackFont) { return {}; }
inline void nvgResetFallbackFontsId(NVGcontext *ctx, int baseFont) {}
inline void nvgResetFallbackFonts(NVGcontext *ctx, const char *baseFont) {}
inline void nvgFontSize(NVGcontext *ctx, float size) {}
inline void nvgFontBlur(NVGcontext *ctx, float blur) {}
inline void nvgTextLetterSpacing(NVGcontext *ctx, float spacing) {}
inline void nvgTextLineHeight(NVGcontext *ctx, float lineHeight) {}
inline void nvgTextAlign(NVGcontext *ctx, int align) {}
inline void nvgFontFaceId(NVGcontext *ctx, int font) {}
inline void nvgFontFace(NVGcontext *ctx, const char *font) {}
inline float nvgText(NVGcontext *ctx, float x, float y, const char *string, const char *end) { return {}; }
inline void nvgTextBox(NVGcontext *ctx, float x, float y, float breakRowWidth, const char *string, const char *end) {}
inline float nvgTextBounds(NVGcontext *ctx, float x, float y, const char *string, const char *end, float *bounds) { return {}; }
inline void nvgTextBoxBounds( NVGcontext *ctx, float x, float y, float breakRowWidth, const char *string, const char *end, float *bounds) {}
inline int nvgTextGlyphPositions(NVGcontext *, float, float, const char *, const char *, NVGglyphPosition *, int) { return {}; }
inline void nvgTextMetrics(NVGcontext *ctx, float *ascender, float *descender, float *lineh) {}
inline int nvgTextBreakLines( NVGcontext *ctx, const char *string, const char *end, float breakRowWidth, NVGtextRow *rows, int maxRows) { return {}; }
// clang-format on
