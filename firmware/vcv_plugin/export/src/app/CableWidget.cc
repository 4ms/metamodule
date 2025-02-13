#include <app/CableWidget.hpp>

namespace rack::app
{

CableWidget::~CableWidget() {
	if (cable)
		delete cable;
}

bool CableWidget::isComplete() {
	return false;
}

void CableWidget::updateCable() {
}

void CableWidget::setCable(engine::Cable *cable) {
	this->cable = cable;
}

engine::Cable *CableWidget::getCable() {
	return cable;
}

math::Vec CableWidget::getInputPos() {
	return {};
}

math::Vec CableWidget::getOutputPos() {
	return {};
}

void CableWidget::mergeJson(json_t *rootJ) {
}

void CableWidget::fromJson(json_t *rootJ) {
}

engine::Cable *CableWidget::releaseCable() {
	auto t = cable;
	cable = nullptr;
	return t;
}

void CableWidget::step() {
}
void CableWidget::draw(const DrawArgs &args) {
}
void CableWidget::drawLayer(const DrawArgs &args, int layer) {
}

} // namespace rack::app
