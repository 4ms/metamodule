#pragma once
#include "VCV_adaptor/events.hh"
#include "VCV_adaptor/widget/Widget.hh"
#include <string>

namespace rack::ui
{

struct Menu : widget::OpaqueWidget {

	virtual Menu *createChildMenu() {
		return nullptr;
	}
};

struct MenuEntry : widget::OpaqueWidget {};

struct MenuSeparator : MenuEntry {};

struct MenuLabel : MenuEntry {
	std::string text;
};

struct MenuItem : MenuEntry {
	std::string text;
	std::string rightText;
	bool disabled = false;
};
} // namespace rack::ui
