#pragma once
#include <Quantity.hpp>
#include <widget/OpaqueWidget.hpp>

namespace rack::ui
{

struct Button : widget::OpaqueWidget {
	std::string text;
	/** Not owned. Tracks the pressed state of the button.*/
	Quantity *quantity = nullptr;
};

} // namespace rack::ui
