#include "api.hh"
#include "conf/screen_buffer_conf.hh"
#include "sketch/sketch.hh"
#include <algorithm>
#include <cmath>
#include <cstring>
#include <span>

#include "api/color_convert.hh"
#include "api/draw_state.hh"
#include "api/framebuffer.hh"

namespace Handheld
{

using namespace ProcessingAPI;

//
// Globals (requried for Processing API)
//

unsigned width = MetaModule::ScreenBufferConf::viewWidth;
unsigned height = MetaModule::ScreenBufferConf::viewHeight;

int mouseX = 0;
int mouseY = 0;

//
// Private internal state
//

DrawState state_{};

//
// API
//

void size(unsigned w, unsigned h) {
	//? Scale to fit?
}

} // namespace Handheld
