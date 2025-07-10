#include "internal_interface/plugin_interface.hh"

namespace MetaModule
{

uint32_t get_block_size() {
	if (PluginInterface::instance) {
		return PluginInterface::instance->get_block_size();
	} else
		return 32; //reasonable default, but should never happen
}

} // namespace MetaModule
