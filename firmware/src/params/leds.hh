#pragma once
#include <array>

namespace MetaModule
{

struct LedStates {
	std::array<bool, 4> low{};
	std::array<bool, 6> mid{};
	std::array<bool, 5> high{};
	bool eq_clip{};
	bool comp_clip{};
	std::array<float, 9> graph{};
};

} // namespace MetaModule
