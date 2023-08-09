#pragma once
#include "CoreModules/elements/element_info.hh"
#include "cpputil/util/base_concepts.hh"
#include <cstdint>
#include <span>

namespace MetaModule
{

struct ModuleInfoView {
	std::string_view description{""};
	uint32_t width_hp = 0;
	std::span<const Element> elements;

	template<Derived<ModuleInfoBase> T>
	static constexpr ModuleInfoView makeView() {
		return {
			.description = T::description,
			.width_hp = T::width_hp,
			.elements = T::Elements,
		};
	}
};

} // namespace MetaModule
