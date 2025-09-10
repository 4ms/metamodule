#include "conf/screen_buffer_conf.hh"
#include "screen/lvgl_driver.hh"
#include <array>

namespace MetaModule
{

using FrameBufferT = std::array<lv_color_t, MetaModule::ScreenBufferConf::width * MetaModule::ScreenBufferConf::height>;
static inline FrameBufferT framebuf1 alignas(64);
static inline FrameBufferT framebuf2 alignas(64);

FrameBufferT *first_framebuf = &framebuf1;

void init_gui() {
	LVGLDriver gui{MMDisplay::flush_to_screen, MMDisplay::read_input, framebuf1, framebuf2};
}

} // namespace MetaModule
