#include "graphics/waveform_display.hh"

namespace MetaModule
{

struct StreamingWaveformDisplay::Internal {};

StreamingWaveformDisplay::StreamingWaveformDisplay(float display_width_mm, float display_height_mm)
	: display_width{0}
	, display_height{0}
	, wave_height{0} {
}

StreamingWaveformDisplay::~StreamingWaveformDisplay() = default;

void StreamingWaveformDisplay::set_cursor_position(float pos) {
}

void StreamingWaveformDisplay::draw_sample(float sample) {
}

void StreamingWaveformDisplay::sync() {
}

void StreamingWaveformDisplay::set_x_zoom(float zoom) {
}

void StreamingWaveformDisplay::set_wave_color(uint8_t r, uint8_t g, uint8_t b) {
}

void StreamingWaveformDisplay::set_wave_color(std::span<const float, 3> rgb) {
}

void StreamingWaveformDisplay::set_bar_bg_color(uint8_t r, uint8_t g, uint8_t b) {
}

void StreamingWaveformDisplay::set_bar_bg_color(std::span<const float, 3> rgb) {
}

void StreamingWaveformDisplay::set_bar_fg_color(uint8_t r, uint8_t g, uint8_t b) {
}

void StreamingWaveformDisplay::set_bar_fg_color(std::span<const float, 3> rgb) {
}

void StreamingWaveformDisplay::set_cursor_width(unsigned width) {
}

void StreamingWaveformDisplay::set_bar_begin_end(float begin, float end) {
}

void StreamingWaveformDisplay::show_graphic_display(std::span<uint32_t> pix_buffer,
													unsigned width,
													lv_obj_t *lvgl_canvas) {
}

bool StreamingWaveformDisplay::draw_graphic_display() {
	return false;
}

void StreamingWaveformDisplay::hide_graphic_display() {
}

} // namespace MetaModule
