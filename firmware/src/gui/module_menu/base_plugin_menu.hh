#pragma once
#include <string>
#include <vector>

namespace MetaModule
{

struct BasePluginModuleMenu {
	virtual ~BasePluginModuleMenu() = default;

	virtual std::vector<std::string> get_items() = 0;
	virtual void back_event() = 0;
	virtual void click_item(unsigned idx) = 0;
	virtual bool is_done() = 0;
};

} // namespace MetaModule
