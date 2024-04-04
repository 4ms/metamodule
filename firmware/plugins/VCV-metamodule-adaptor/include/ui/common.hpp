#pragma once
#include <blendish.h>
#include <nanovg.h>

#include <color.hpp>
#include <common.hpp>

/** Useful for menu items with a "true" boolean state */
#define CHECKMARK_STRING "✔"
#define CHECKMARK(_cond) ((_cond) ? CHECKMARK_STRING : "")

/** Useful for menu items that open a sub-menu */
#define RIGHT_ARROW "▸"

namespace rack::ui
{

inline void setTheme(NVGcolor bg, NVGcolor fg) {
}
inline void refreshTheme() {
}

} // namespace rack::ui
