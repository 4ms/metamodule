#pragma once
#include "VCV_adaptor/events.hh"

namespace rack::ui
{
struct Menu {
	void addChild(Menu *) {
	}
	virtual Menu *createChildMenu() {
		return nullptr;
	}
	virtual void onAction(const event::Action &e) {
	}
};

struct MenuSeparator : Menu {};

struct MenuLabel : Menu {};
struct MenuItem : Menu {};
} // namespace rack::ui
