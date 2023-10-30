#pragma once
#include "CoreModules/elements/element_info.hh"
#include "CoreModules/elements/elements.hh"
#include <cstdio>
#include <vector>

namespace MetaModule::AudibleInstruments
{

inline void fixup_elements(std::vector<MetaModule::Element> &elements) {
	// BraidsDisplay needs to be manually converted to a BraidsDisplay148x56 because Braids.cpp calls addChild()
	// directly on a BraidsDisplay *, and we have no way of getting that type
	// info into the element automatically.
	//
	// Assumptions: BraidsDisplay is the last element, and should have x,y set to 0 by default
	// It also should be a NullElement (variant index 0)

	auto e = base_element(elements.back());
	if (e.x_mm == 0 && e.y_mm == 0 && elements.back().index() == 0) {
		elements.back() =
			BraidsDisplay148x56{ModuleInfoBase::to_mm(14), ModuleInfoBase::to_mm(53), Coords::TopLeft, "", ""};
	}
}

} // namespace MetaModule::AudibleInstruments
