#pragma once
#include "CoreModules/elements/elements.hh"

namespace MetaModule
{

inline void set_pos(BaseElement &el, float x, float y, Coords coords) {
	el.x_mm = x;
	el.y_mm = y;
	el.coords = coords;
}

inline void set_pos(Element &element, float x, float y, Coords coords) {
	std::visit([=](auto &el) { set_pos(el, x, y, coords); }, element);
}

inline void set_short_name(BaseElement &el, std::string_view short_name) {
	el.short_name = short_name;
}

inline void set_short_name(Element &element, std::string_view short_name) {
	std::visit([&](auto &el) { set_short_name(el, short_name); }, element);
}

} // namespace MetaModule
