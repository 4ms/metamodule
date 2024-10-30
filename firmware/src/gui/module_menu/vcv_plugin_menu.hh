#pragma once
#include "console/pr_dbg.hh"
#include "gui/module_menu/base_plugin_menu.hh"
#include "gui/styles.hh"
#include <app/ModuleWidget.hpp>
#include <ui/MenuItem.hpp>

namespace MetaModule
{

struct RackModuleMenu : BasePluginModuleMenu {
	RackModuleMenu(std::shared_ptr<rack::app::ModuleWidget> module_widget)
		: module_widget{module_widget} {
	}

	std::vector<std::string> get_items() override {
		std::vector<std::string> item_strings;

		if (!rack_menu) {
			// Initialize
			rack_menu = std::make_shared<rack::ui::Menu>();
			current_menu = rack_menu.get();
			rack_menu->parentMenu = nullptr;

			if (auto mw = module_widget.lock()) {
				mw->appendContextMenu(rack_menu.get());
			}

			exited = false;
		}

		if (current_menu) {
			add_menu_items(current_menu->children, item_strings);
		}

		return item_strings;
	}

	void back_event() override {
		if (current_menu && current_menu->parentMenu) {
			current_menu = current_menu->parentMenu;
		} else {
			rack_menu.reset();
			current_menu = nullptr;
			exited = true;
		}
	}

	bool is_done() override {
		return exited;
	}

	void click_item(unsigned idx) override {
		if (!current_menu)
			return;

		unsigned i = 0;
		for (auto child : current_menu->children) {
			if (auto rack_item = dynamic_cast<rack::ui::MenuItem *>(child)) {
				if (i == idx) {
					// Perform its action
					rack_item->doAction();

					// Remove any existing submenu (from a previous click)
					if (current_menu->childMenu) {
						current_menu->childMenu->parent->removeChild(current_menu->childMenu);
						delete current_menu->childMenu;
						current_menu->childMenu = nullptr;
					}

					// Enter the submenu if it has one
					auto submenu = rack_item->createChildMenu();
					if (submenu) {
						// Add the submenu widget so we can delete it later
						current_menu->childMenu = submenu;
						current_menu->addChild(submenu);

						// point child to parent so we can traverse back
						submenu->parentMenu = current_menu;

						// Make the submenu our current menu
						current_menu = submenu;
					}
					break;
				}
				i++;
			}
		}
	}

private:
	void add_menu_items(std::list<rack::widget::Widget *> children, std::vector<std::string> &menu) {
		for (auto child : children) {
			if (auto rack_item = dynamic_cast<rack::ui::MenuItem *>(child)) {
				child->step();

				auto &item = menu.emplace_back();
				// Checkmarks go on left side
				if (rack_item->rightText.ends_with(CHECKMARK_STRING))
					item = Gui::yellow_text(CHECKMARK_STRING);

				item += rack_item->text;

				if (rack_item->rightText.length() && !rack_item->rightText.ends_with(CHECKMARK_STRING))
					item += " " + Gui::yellow_text(rack_item->rightText);
			}
		}
	}

	std::weak_ptr<rack::app::ModuleWidget> module_widget{};
	std::shared_ptr<rack::ui::Menu> rack_menu;

	rack::ui::Menu *current_menu{}; //can't use smart pointer because must point to a raw pointer in rack API

	bool exited = false;
};

} // namespace MetaModule
