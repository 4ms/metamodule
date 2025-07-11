#include "internal_interface/plugin_interface.hh"

namespace MetaModule::Audio
{

uint32_t get_block_size() {
	return PluginAppInterface::get_block_size();
}

} // namespace MetaModule::Audio
