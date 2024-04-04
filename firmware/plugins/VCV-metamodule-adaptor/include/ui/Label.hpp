#pragma once
#include <widget/Widget.hpp>

namespace rack::ui
{

struct Label : widget::Widget {
	enum Alignment {
		LEFT_ALIGNMENT,
		CENTER_ALIGNMENT,
		RIGHT_ALIGNMENT,
	};

	std::string text;
	float fontSize;
	float lineHeight;
	NVGcolor color;
	Alignment alignment = LEFT_ALIGNMENT;
};

} // namespace rack::ui
