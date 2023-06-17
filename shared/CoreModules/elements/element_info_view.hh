#pragma once
#include "CoreModules/elements/element_info.hh"

namespace MetaModule
{

struct ElementInfoView {
	std::string_view description{""};
	uint32_t width_hp = 0;
	std::string_view svg_filename{""};
	std::span<const Element> Elements;

	template<Derived<ElementInfoBase> T>
	static constexpr ElementInfoView makeView() {
		return {
			.description = T::description,
			.width_hp = T::width_hp,
			.svg_filename = T::svg_filename,
			.Elements = T::Elements,
		};
	}
};

} // namespace MetaModule
