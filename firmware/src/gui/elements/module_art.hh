#pragma once
#include "conf/screen_buffer_conf.hh"

namespace MetaModule
{

// Module artwork (faceplates and component images) is made for a module drawn this many
// pixels high. Modules drawn at any other height are scaled from this.
// This is not the screen height, though they are the same on MP1.
inline constexpr unsigned ModuleArtHeightPx = 240;

// A module drawn at the full height of the screen (as in ModuleView)
inline constexpr unsigned ModuleFullHeightPx = ScreenBufferConf::viewHeight;

} // namespace MetaModule
