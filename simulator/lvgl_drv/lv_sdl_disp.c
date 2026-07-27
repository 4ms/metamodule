//SPDX-License-Identifier: MIT

#include "lv_port_disp.h"
#include "lvgl.h"
#include <SDL2/SDL.h>
#include <assert.h>

static void *fb1, *fb2;
SDL_Window *window = NULL;
SDL_Renderer *renderer = NULL;
SDL_Texture *texture = NULL;
static lv_disp_drv_t disp_drv;
static lv_disp_draw_buf_t draw_buf;
static int DISPLAY_WIDTH;
static int DISPLAY_HEIGHT;
// Most recently flushed framebuffer (full_refresh=1, so it holds the whole screen)
static lv_color_t *last_fb = NULL;
#ifndef WINDOW_NAME
#define WINDOW_NAME "MetaModule"
#endif

static void disp_flush(lv_disp_drv_t *disp_drv, const lv_area_t *area, lv_color_t *color_p) {
	SDL_Rect r;
	r.x = area->x1;
	r.y = area->y1;
	r.w = area->x2 - area->x1 + 1;
	r.h = area->y2 - area->y1 + 1;
	SDL_UpdateTexture(texture, &r, color_p, r.w * ((LV_COLOR_DEPTH + 7) / 8));
	SDL_RenderCopy(renderer, texture, NULL, NULL);
	SDL_RenderPresent(renderer);
	last_fb = color_p;
	lv_disp_flush_ready(disp_drv);
}

// Save the current screen contents to a BMP file. Returns 0 on success.
int lv_port_disp_capture(const char *path) {
	if (!last_fb)
		return -1;

	Uint32 fmt = (LV_COLOR_DEPTH == 32) ? SDL_PIXELFORMAT_ARGB8888 : SDL_PIXELFORMAT_RGB565;
	int pitch = DISPLAY_WIDTH * ((LV_COLOR_DEPTH + 7) / 8);

	SDL_Surface *surf = SDL_CreateRGBSurfaceWithFormatFrom(
		last_fb, DISPLAY_WIDTH, DISPLAY_HEIGHT, LV_COLOR_DEPTH, pitch, fmt);
	if (!surf)
		return -1;

	int ret = SDL_SaveBMP(surf, path);
	SDL_FreeSurface(surf);
	return ret;
}

void lv_port_disp_init(int width, int height, int zoom) {
	assert(LV_COLOR_DEPTH == 16 || LV_COLOR_DEPTH == 32);
	DISPLAY_WIDTH = width;
	DISPLAY_HEIGHT = height;
	SDL_InitSubSystem(SDL_INIT_VIDEO | SDL_INIT_AUDIO);

	window = SDL_CreateWindow(WINDOW_NAME,
							  SDL_WINDOWPOS_UNDEFINED,
							  SDL_WINDOWPOS_UNDEFINED,
							  DISPLAY_WIDTH * zoom / 100,
							  DISPLAY_HEIGHT * zoom / 100,
							  SDL_WINDOW_RESIZABLE);

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_SOFTWARE);

	texture = SDL_CreateTexture(renderer,
								(LV_COLOR_DEPTH == 32) ? (SDL_PIXELFORMAT_ARGB8888) : (SDL_PIXELFORMAT_RGB565),
								SDL_TEXTUREACCESS_STREAMING,
								DISPLAY_WIDTH,
								DISPLAY_HEIGHT);

	fb1 = malloc(DISPLAY_WIDTH * DISPLAY_HEIGHT * ((LV_COLOR_DEPTH + 7) / 8));
	fb2 = malloc(DISPLAY_WIDTH * DISPLAY_HEIGHT * ((LV_COLOR_DEPTH + 7) / 8));

	lv_disp_draw_buf_init(&draw_buf, fb1, fb2, DISPLAY_WIDTH * DISPLAY_HEIGHT);
	lv_disp_drv_init(&disp_drv);

	disp_drv.hor_res = DISPLAY_WIDTH;
	disp_drv.ver_res = DISPLAY_HEIGHT;
	disp_drv.flush_cb = disp_flush;
	disp_drv.draw_buf = &draw_buf;
	disp_drv.full_refresh = 1;
	lv_disp_drv_register(&disp_drv);
}

void lv_port_disp_deinit() {
	free(fb1);
	free(fb2);
	SDL_DestroyTexture(texture);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_QuitSubSystem(SDL_INIT_VIDEO);
}
