#pragma once
#include <context.hpp>
#include <ui/Menu.hpp>
#include <ui/MenuEntry.hpp>
#include <ui/common.hpp>

namespace rack::ui
{

struct MenuItem : MenuEntry {
	std::string text;
	std::string rightText;
	bool disabled = false;

	void doAction(bool consume = true) {
	}
	virtual Menu *createChildMenu() {
		return nullptr;
	}
};

} // namespace rack::ui
