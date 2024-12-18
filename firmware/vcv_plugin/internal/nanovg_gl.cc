#include "CoreModules/elements/units.hh"
#include "gui/fonts/fonts.hh"
#include "lvgl.h"
#include <algorithm>
#include <cmath>
#include <cstdlib>
#include <cstring>
#include <nanovg.h>
#include <span>
#include <string>
#include <vector>

#define NANOVG_PIXELBUFFER_IMPLEMENTATION
#include <nanovg_gl.h>
#include <nanovg_gl_utils.h>

#include "console/pr_dbg.hh"
#include "medium/debug_raw.h"

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

	bool operator==(const TextRenderCacheEntry &other) const {
		return x == other.x && y == other.y && align == other.align;
	}
};

struct DrawContext {
	lv_obj_t *canvas{};
	lv_draw_line_dsc_t line_dsc{};
	lv_draw_rect_dsc_t rect_dsc{};
	lv_draw_label_dsc_t label_dsc{};

	std::vector<Texture> textures;

	std::vector<TextRenderCacheEntry> labels;

	void *parent_ctx{}; // needed for deleting

	DrawContext(lv_obj_t *canvas)
		: canvas{canvas} {
		lv_draw_line_dsc_init(&line_dsc);
		line_dsc.width = 1;

		lv_draw_rect_dsc_init(&rect_dsc);
		rect_dsc.radius = 0;

		lv_draw_label_dsc_init(&label_dsc);
	}
};

constexpr lv_coord_t to_lv_coord(float x) {
	return std::round(mm_to_px(to_mm(x), 240));
}
// 10px in rack dimensions => 6.325px in MM dimensions
// static_assert(mm_to_px(to_mm(10.f), 240) == 6.325291928f);

constexpr lv_point_t to_lv_point(NVGvertex vertex) {
	return lv_point_t(to_lv_coord(vertex.x), to_lv_coord(vertex.y));
}

DrawContext *get_drawcontext(void *uptr) {
	return (DrawContext *)(uptr);
}

lv_color_t to_lv_color(NVGcolor color) {
	return lv_color_make(color.r * 255.f, color.g * 255.f, color.b * 255.f);
}

constexpr uint8_t to_lv_opa(NVGcolor color) {
	return std::round(color.a * float(LV_OPA_100));
}

constexpr bool is_poly_concave(std::span<lv_point_t> points) {
	auto n = points.size();
	if (n < 3)
		return false;

	auto X_prod = [](lv_point_t O, lv_point_t A, lv_point_t B) {
		return (A.x - O.x) * (B.y - O.y) - (A.y - O.y) * (B.x - O.x);
	};

	int sign = 0;
	for (auto i = 0u; i < points.size(); i++) {
		auto O = points[i];
		auto A = points[(i + 1) % n];
		auto B = points[(i + 2) % n];
		auto cross = X_prod(O, A, B);
		if (cross == 0)
			continue;

		if (sign == 0)
			sign = cross;

		if ((sign > 0 && cross < 0) || (sign < 0 && cross > 0))
			return true;
	}
	return false;
}

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

lv_coord_t manual_font_tweaks(float fontSize, const void *font) {
	if (fontSize == 38) //DrumKit Gnome, Sequencer
		return 20;
	else
		return to_lv_coord(fontSize);
}

float renderText(
	void *uptr, float x, float y, float max_w, const char *text, const char *textend, struct NVGFontState *fs) {
	auto context = get_drawcontext(uptr);
	auto canvas = context->canvas;

	DebugPin1High();

	// Move to position
	auto lv_x = to_lv_coord(x + fs->xform[4]);
	auto lv_y = to_lv_coord(y + fs->xform[5]);

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

		auto font = (lv_font_t *)fs->fontPtr;
		auto lv_font_size = manual_font_tweaks(fs->fontSize, fs->fontPtr);

		// Align vertically
		lv_y -= fs->textAlign & NVG_ALIGN_BASELINE ? lv_font_size :
				fs->textAlign & NVG_ALIGN_BOTTOM   ? lv_font_size * 1.2f :
				fs->textAlign & NVG_ALIGN_MIDDLE   ? lv_font_size * 0.5f :
													 0;

		label = lv_label_create(canvas);
		lv_obj_set_pos(label, lv_x, lv_y);
		lv_obj_set_size(label, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
		lv_tiny_ttf_set_size(font, lv_font_size);
		lv_obj_set_style_text_font(label, font, LV_PART_MAIN);
		lv_obj_set_style_text_color(label, to_lv_color(fs->paint->innerColor), LV_PART_MAIN);
		lv_obj_set_style_text_opa(label, to_lv_opa(fs->paint->innerColor), LV_PART_MAIN);
		lv_obj_set_style_text_align(label, align, LV_PART_MAIN);

		lv_obj_set_style_text_line_space(label, 0, LV_PART_MAIN);
		lv_obj_set_style_text_letter_space(label, 0, LV_PART_MAIN);
		lv_obj_set_style_border_color(label, lv_color_hex(0xFF0000), LV_PART_MAIN);
		lv_obj_set_style_border_width(label, 1, LV_PART_MAIN);

		// Use original x,y for cache
		context->labels.emplace_back(lv_x, lv_y, fs->textAlign, label);
		pr_dbg("Creating label at %d,%d (sz %d)\n", lv_x, lv_y, lv_font_size);
	}

	// Handle case were text doesn't have a null terminator (which LVGL needs)
	std::string text_copy;
	if (textend && *textend != '\0') {
		// pr_dbg("String not null terminated\n");
		text_copy.append(text, textend - text);
		text = text_copy.c_str();
	}

	if (fs->textAlign & NVG_ALIGN_CENTER) {
		auto width = lv_txt_get_width(text, strlen(text), (lv_font_t *)fs->fontPtr, 0, 0);
		lv_obj_set_x(label, lv_x - width / 2);
	}

	lv_label_set_text(label, text);

	DebugPin1Low();

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
