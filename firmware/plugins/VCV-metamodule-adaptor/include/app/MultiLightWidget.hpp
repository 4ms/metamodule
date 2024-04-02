#pragma once
#include <app/LightWidget.hpp>

namespace rack::app
{

struct MultiLightWidget : LightWidget {
	std::vector<NVGcolor> baseColors;

	int getNumColors() const {
		return baseColors.size();
	}

	void addBaseColor(NVGcolor baseColor) {
		baseColors.push_back(baseColor);
	}

	void setBrightnesses(const std::vector<float> &brightnesses) {
		//TODO
	}
};

} // namespace rack::app
