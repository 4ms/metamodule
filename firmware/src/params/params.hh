#pragma once
#include <array>

namespace MetaModule
{

// Sample-rate parameters
struct Params {
	std::array<float, 8> knobs{};
	float width_cv{};

	void clear() {
		*this = Params{};
	}
};

static constexpr auto Params_Size = sizeof(Params);

} // namespace MetaModule
