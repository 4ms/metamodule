#pragma once
#include <app/RackWidget.hpp>
#include <app/common.hpp>
#include <ui/ScrollWidget.hpp>
#include <widget/ZoomWidget.hpp>

namespace rack::app
{

struct RackScrollWidget : ui::ScrollWidget {
	widget::ZoomWidget *zoomWidget{};
	RackWidget *rackWidget{};

	void reset() {
	}
	math::Vec getGridOffset() {
		return {};
	}
	void setGridOffset(math::Vec gridOffset) {
	}
	float getZoom() {
		return {};
	}
	void setZoom(float zoom) {
	}
	void setZoom(float zoom, math::Vec pivot) {
	}
};

} // namespace rack::app
