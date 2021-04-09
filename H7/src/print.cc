#include "screen_buffer.hh"

// Wrapper for C-style printf library
// Todo: convert mcufont to C++ classes, and use CRTP to provide callbacks
// -- OR -- use std::bind to call class functions
static ScreenFrameBuffer *default_screen;
static bool screen_is_registered = false;
void register_printf_destination(ScreenFrameBuffer &screen)
{
	default_screen = &screen;
	screen_is_registered = true;
}

extern "C" void _draw_text_pixel_callback(int16_t x, int16_t y, uint8_t count, uint8_t alpha, void *state)
{
	if (!screen_is_registered)
		return;
	default_screen->blendHLineText(x, y, count, alpha);
}

extern "C" uint8_t _char_cursor_callback(int16_t x0, int16_t y0, mf_char character, void *state)
{
	if (!screen_is_registered)
		return 0;
	auto x_inc = mf_render_character(default_screen->_font, x0, y0, character, &_draw_text_pixel_callback, state);
	if (default_screen->_alignment == MF_ALIGN_LEFT)
		default_screen->cursor_x += x_inc;
	else
		default_screen->cursor_x -= x_inc;
	return x_inc;
}
