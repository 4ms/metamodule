#pragma once
#include "CoreModules/elements/element_counter.hh"
#include "CoreModules/elements/element_info.hh"
#include <util/base_concepts.hh>
#include <array>
#include <cstdint>
#include <span>

namespace MetaModule
{

struct ModuleInfoView {
	std::string_view description{""};
	uint32_t width_hp = 0;
	std::span<const Element> elements;
	std::span<const ElementCount::Indices> indices;

	template<Derived<ModuleInfoBase> T>
	static ModuleInfoView makeView() {
		static std::array<ElementCount::Indices, T::Elements.size()> s_indices = ElementCount::get_indices<T>();
		return {
			.description = T::description,
			.width_hp = T::width_hp,
			.elements = T::Elements,
			.indices = s_indices,
		};
	}
};

} // namespace MetaModule
