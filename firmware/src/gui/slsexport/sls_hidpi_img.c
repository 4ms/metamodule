#include "sls_hidpi_img.h"
#include "../ui_scale.h"

#if METAMODULE_UI_SCALE == 100

const void *ui_scaled_img(const void *src) {
	return src;
}

#else

#define MAX_SCALED_IMGS 32

static struct {
	const void *src;
	lv_img_dsc_t *scaled;
} cache[MAX_SCALED_IMGS];
static unsigned num_cached = 0;

typedef struct {
	int32_t r, g, b, a; // premultiplied by alpha
} px_t;

static px_t get_px(const lv_img_dsc_t *img, lv_coord_t x, lv_coord_t y) {
	x = LV_CLAMP(0, x, (lv_coord_t)img->header.w - 1);
	y = LV_CLAMP(0, y, (lv_coord_t)img->header.h - 1);
	const uint8_t *p = img->data + (y * img->header.w + x) * LV_IMG_PX_SIZE_ALPHA_BYTE;
	lv_color_t c;
	lv_memcpy_small(&c, p, sizeof(lv_color_t));
	int32_t a = p[LV_IMG_PX_SIZE_ALPHA_BYTE - 1];
	lv_color32_t c32;
	c32.full = lv_color_to32(c);
	return (px_t){c32.ch.red * a, c32.ch.green * a, c32.ch.blue * a, a};
}

static int32_t lerp(int32_t a, int32_t b, int32_t frac256) {
	return a + (((b - a) * frac256) >> 8);
}

const void *ui_scaled_img(const void *src) {
	if (!src || lv_img_src_get_type(src) != LV_IMG_SRC_VARIABLE)
		return src;

	const lv_img_dsc_t *img = src;
	if (img->header.cf != LV_IMG_CF_TRUE_COLOR_ALPHA)
		return src;

	for (unsigned i = 0; i < num_cached; i++) {
		if (cache[i].src == src)
			return cache[i].scaled;
	}
	if (num_cached >= MAX_SCALED_IMGS)
		return src;

	lv_coord_t w = ui_px(img->header.w);
	lv_coord_t h = ui_px(img->header.h);
	uint32_t data_size = w * h * LV_IMG_PX_SIZE_ALPHA_BYTE;

	lv_img_dsc_t *out = lv_mem_alloc(sizeof(lv_img_dsc_t) + data_size);
	if (!out)
		return src;
	uint8_t *data = (uint8_t *)(out + 1);
	*out = *img;
	out->header.w = w;
	out->header.h = h;
	out->data_size = data_size;
	out->data = data;

	// Bilinear resample, with pixel centers aligned
	for (lv_coord_t y = 0; y < h; y++) {
		int32_t sy = ((2 * y + 1) * (int32_t)img->header.h * 128) / h - 128; // 24.8 fixed point
		lv_coord_t y0 = sy >> 8;
		int32_t fy = sy & 0xFF;
		for (lv_coord_t x = 0; x < w; x++) {
			int32_t sx = ((2 * x + 1) * (int32_t)img->header.w * 128) / w - 128;
			lv_coord_t x0 = sx >> 8;
			int32_t fx = sx & 0xFF;

			px_t p00 = get_px(img, x0, y0);
			px_t p10 = get_px(img, x0 + 1, y0);
			px_t p01 = get_px(img, x0, y0 + 1);
			px_t p11 = get_px(img, x0 + 1, y0 + 1);

			int32_t a = lerp(lerp(p00.a, p10.a, fx), lerp(p01.a, p11.a, fx), fy);
			int32_t r = lerp(lerp(p00.r, p10.r, fx), lerp(p01.r, p11.r, fx), fy);
			int32_t g = lerp(lerp(p00.g, p10.g, fx), lerp(p01.g, p11.g, fx), fy);
			int32_t b = lerp(lerp(p00.b, p10.b, fx), lerp(p01.b, p11.b, fx), fy);

			lv_color_t c =
				a > 0 ? lv_color_make(LV_MIN(r / a, 255), LV_MIN(g / a, 255), LV_MIN(b / a, 255)) : lv_color_black();
			uint8_t *p = data + (y * w + x) * LV_IMG_PX_SIZE_ALPHA_BYTE;
			lv_memcpy_small(p, &c, sizeof(lv_color_t));
			p[LV_IMG_PX_SIZE_ALPHA_BYTE - 1] = LV_CLAMP(0, a, 255);
		}
	}

	cache[num_cached].src = src;
	cache[num_cached].scaled = out;
	num_cached++;
	return out;
}

#endif
