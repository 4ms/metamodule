#pragma once
#include "CoreModules/elements/elements.hh"
#include <cmath>

namespace MetaModule::ElementDrawerImpl
{

constexpr float fix_zoomed_coord(Coords coord_ref, float x, float width, float zoom) {
	if (coord_ref == Coords::TopLeft && zoom < 1.f) {
		// FIXME: why does LVGL add padding around a zoomed obj?
		return x - (width * (1.f - zoom) / 2.f);
	} else if (coord_ref == Coords::Center) {
		//Calculate Top-left from Center
		return x - (width / 2.f);
	}

	return x;
}

} // namespace MetaModule::ElementDrawerImpl
