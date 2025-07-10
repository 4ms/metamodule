#include "internal_interface/plugin_interface.hh"

namespace MetaModule
{

void mark_patch_modified() {
	if (PluginInterface::instance) {
		PluginInterface::instance->mark_patch_modified();
	}
}

} // namespace MetaModule
