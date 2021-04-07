#include "screen_buffer.hh"

// Wrapper for C-style printf library
// Todo: convert mpaland/printf to a C++ class, and use CRTP to provide _putchar
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
