#pragma once
#include <app/RackScrollWidget.hpp>
#include <app/RackWidget.hpp>
#include <app/common.hpp>
#include <widget/OpaqueWidget.hpp>

namespace rack::app
{

struct Scene : widget::OpaqueWidget {
	// Convenience variables for accessing important widgets
	RackScrollWidget *rackScroll{};
	RackWidget *rack{};
	widget::Widget *menuBar{};
	widget::Widget *browser{};

	math::Vec mousePos;

	math::Vec getMousePos() {
		return {};
	}
};

} // namespace rack::app
