#pragma once
#include <cmath>

namespace MetaModule
{

// Block-rate parameters
struct MetaParams {
	unsigned eq_switch{};
	unsigned comp_switch{};

	bool low_sel{};
	bool mid_sel{};
	bool high_sel{};

	bool inL_plugged{};
	bool inR_plugged{};
	bool outL_plugged{};
	bool outR_plugged{};
	bool cv_plugged{};

	void clear() {
		*this = MetaParams{};
	}
};

} // namespace MetaModule
