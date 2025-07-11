#include "internal_interface/plugin_interface.hh"

namespace MetaModule::Patch
{

void mark_patch_modified() {
	PluginAppInterface::mark_patch_modified();
}

} // namespace MetaModule::Patch
