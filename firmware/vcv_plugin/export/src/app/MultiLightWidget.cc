#include <app/MultiLightWidget.hpp>

namespace rack::app
{

int MultiLightWidget::getNumColors() const {
	return baseColors.size();
}

void MultiLightWidget::addBaseColor(NVGcolor baseColor) {
	baseColors.push_back(baseColor);
}

void MultiLightWidget::setBrightnesses(const std::vector<float> &brightnesses) {
	//TODO
}

} // namespace rack::app
