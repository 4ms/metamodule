#pragma once
#include "CoreModules/CoreProcessor.hh"
#include <memory>

namespace MetaModule
{

void plugin_module_deinit(std::unique_ptr<CoreProcessor> &module);

}
