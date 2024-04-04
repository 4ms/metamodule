#pragma once
#include <ui/MenuEntry.hpp>
#include <ui/common.hpp>
#include <widget/OpaqueWidget.hpp>

namespace rack::ui
{

struct Menu : widget::OpaqueWidget {
	Menu *parentMenu = nullptr;
	Menu *childMenu = nullptr;
	MenuEntry *activeEntry = nullptr;
	BNDcornerFlags cornerFlags = BND_CORNER_NONE;

	void setChildMenu(Menu *menu) {
	}
};

} // namespace rack::ui
