#pragma once
#include "CoreModules/elements/elements.hh"
#include "units.hh"
#include <array>
#include <cstdint>
#include <string_view>

namespace MetaModule
{

struct ModuleInfoBase {
	static constexpr std::string_view slug{""};
	static constexpr std::string_view description{""};
	static constexpr uint32_t width_hp = 0;
	static constexpr std::array<Element, 0> Elements{};
	static constexpr std::string_view svg_filename{""};
	static constexpr std::string_view png_filename{""};
};

} // namespace MetaModule
