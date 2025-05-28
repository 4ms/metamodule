#pragma once
#include "CoreModules/CoreProcessor.hh"
#include <memory>

namespace MetaModule
{

void plugin_module_init(std::unique_ptr<CoreProcessor> &module);
void plugin_module_deinit(std::unique_ptr<CoreProcessor> &module);

} // namespace MetaModule
