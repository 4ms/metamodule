#pragma once
#include "CoreModules/CoreProcessor.hh"
#include "engine/Module.hpp"
#include <memory>
#include <span>

namespace MetaModule
{

rack::engine::Module *as_rack_module(CoreProcessor *module);

void plugin_module_init(std::unique_ptr<CoreProcessor> &module);
void plugin_module_deinit(std::unique_ptr<CoreProcessor> &module);

CoreProcessor::PolyPortBuffer plugin_module_get_poly_output_buffer(std::unique_ptr<CoreProcessor> &module,
																   int output_id);
CoreProcessor::PolyPortBuffer plugin_module_get_poly_input_buffer(std::unique_ptr<CoreProcessor> &module, int input_id);

// Writes the module's text for a param's value (VCV modules: getDisplayValueString() + getUnit()),
// null-terminated. Returns its length, or 0 if the module doesn't provide one.
size_t plugin_module_get_param_value_string(CoreProcessor *module, int param_id, std::span<char> text);

} // namespace MetaModule
