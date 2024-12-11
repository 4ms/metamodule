//SPDX-License-Identifier: MIT

#include "lv_port_disp.h"
#include "lvgl.h"
#include <SDL2/SDL.h>
#include <assert.h>

static void *fb1, *fb2;
SDL_Window *window = NULL;
SDL_Renderer *renderer = NULL;
SDL_Texture *texture = NULL;
static lv_display_t *display;
static int DISPLAY_WIDTH;
static int DISPLAY_HEIGHT;

#ifndef WINDOW_NAME
#define WINDOW_NAME "MetaModule"
#endif

static void disp_flush(lv_display_t *display, const lv_area_t *area, unsigned char *color_p) {
	SDL_Rect r;
	r.x = area->x1;
	r.y = area->y1;
	r.w = area->x2 - area->x1 + 1;
	r.h = area->y2 - area->y1 + 1;
	SDL_UpdateTexture(texture, &r, color_p, r.w * ((LV_COLOR_DEPTH + 7) / 8));
	SDL_RenderCopy(renderer, texture, NULL, NULL);
	SDL_RenderPresent(renderer);
	lv_disp_flush_ready(display);
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

	const size_t buffersize = DISPLAY_WIDTH * DISPLAY_HEIGHT * ((LV_COLOR_DEPTH + 7) / 8);
	fb1 = malloc(buffersize);
	fb2 = malloc(buffersize);

	display = lv_display_create(DISPLAY_WIDTH, DISPLAY_HEIGHT);
	lv_display_set_buffers(display, fb1, fb2, buffersize, LV_DISPLAY_RENDER_MODE_FULL);

	lv_display_set_flush_cb(display, disp_flush);
	lv_display_set_color_format(display, (LV_COLOR_DEPTH == 32) ? LV_COLOR_FORMAT_ARGB8888 : LV_COLOR_FORMAT_RGB565);
}

void lv_port_disp_deinit() {
	free(fb1);
	free(fb2);
	SDL_DestroyTexture(texture);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_QuitSubSystem(SDL_INIT_VIDEO);
}
