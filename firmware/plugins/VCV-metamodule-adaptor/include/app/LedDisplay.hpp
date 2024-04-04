#pragma once
#include <app/common.hpp>
#include <ui/TextField.hpp>
#include <widget/OpaqueWidget.hpp>
#include <widget/Widget.hpp>

namespace rack::app
{

struct LedDisplay : widget::Widget {};

struct LedDisplaySeparator : widget::Widget {};

struct LedDisplayChoice : widget::OpaqueWidget {
	std::string text;
	std::string fontPath;
	math::Vec textOffset;
	NVGcolor color;
	NVGcolor bgColor;
};

struct LedDisplayTextField : ui::TextField {
	std::string fontPath;
	math::Vec textOffset;
	NVGcolor color;
	NVGcolor bgColor;
};

} // namespace rack::app
