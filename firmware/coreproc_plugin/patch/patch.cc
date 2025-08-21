#include "internal_interface/plugin_app_interface.hh"
#include "util/static_string.hh"

namespace MetaModule::Patch
{

void mark_patch_modified() {
	PluginAppInterface::mark_patch_modified();
}

StaticString<7> get_volume() {
	return PluginAppInterface::get_volume();
}

std::string get_path() {
	return PluginAppInterface::get_path();
}

std::string get_dir() {
	return PluginAppInterface::get_dir();
}

} // namespace MetaModule::Patch
