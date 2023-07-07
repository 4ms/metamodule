#pragma once
#include "CoreModules/elements/element_info.hh"
#include "util/base_concepts.hh"
#include <cstdint>
#include <span>

namespace MetaModule
{

struct ModuleInfoView {
	std::string_view description{""};
	uint32_t width_hp = 0;
	bool uses_center_coords = false;
	std::span<const Element> elements;

	template<Derived<ModuleInfoBase> T>
	static constexpr ModuleInfoView makeView() {
		return {
			.description = T::description,
			.width_hp = T::width_hp,
			.uses_center_coords = T::uses_center_coords,
			.elements = T::Elements,
		};
	}
};

} // namespace MetaModule
