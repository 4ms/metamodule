#pragma once
#include "VCV-adaptor/app/RackWidget.hpp"
#include "VCV-adaptor/widgets.hh"
namespace rack::app
{

struct RackScrollWidget {};

struct Scene : widget::OpaqueWidget {
	RackScrollWidget *rackScroll;
	RackWidget *rack;
	widget::Widget *menuBar;
	widget::Widget *browser;

	math::Vec mousePos;
	math::Vec getMousePos() {
		return mousePos;
	}
};
} // namespace rack::app
