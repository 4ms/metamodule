#pragma once

namespace MetaModule
{

// Block-rate parameters
struct MetaParams {
	float eq_switch{};
	float comp_switch{};

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
