#include "screen_buffer.hh"

// Wrapper for C-style printf library
// Todo: convert printf and mcufont to C++ classes, and use CRTP to provide _putchar and/or _draw_text_pixel_callback
static ScreenFrameBuffer *default_screen;
static bool screen_is_registered = false;
void register_printf_destination(ScreenFrameBuffer &screen)
{
	default_screen = &screen;
	screen_is_registered = true;
}

extern "C" void _putchar(char character)
{
	if (!screen_is_registered)
		return;
	default_screen->write(character);
}

extern "C" void _draw_text_pixel_callback(int16_t x, int16_t y, uint8_t count, uint8_t alpha, void *state)
{
	if (!screen_is_registered)
		return;
	default_screen->blendHLineText(x, y, count, alpha);
}

extern "C" uint8_t _char_callback(int16_t x0, int16_t y0, mf_char character, void *state)
{
	if (!screen_is_registered)
		return 0;
	return mf_render_character(default_screen->_font, x0, y0, character, &_draw_text_pixel_callback, state);
}

extern "C" uint8_t _char_cursor_callback(int16_t x0, int16_t y0, mf_char character, void *state)
{
	if (!screen_is_registered)
		return 0;
	auto x_inc = mf_render_character(default_screen->_font, x0, y0, character, &_draw_text_pixel_callback, state);
	default_screen->cursor_x += x_inc;
	return x_inc;
}
