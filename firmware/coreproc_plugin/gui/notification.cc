#include "internal_interface/plugin_app_interface.hh"

namespace MetaModule::Gui
{

void notify_user(std::string_view message, int duration_ms) {
	PluginAppInterface::notify_user(message, duration_ms);
}

} // namespace MetaModule::Gui
