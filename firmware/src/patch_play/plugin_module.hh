#pragma once
#include "CoreModules/CoreProcessor.hh"
#include "engine/Module.hpp"
#include <memory>
#include <string_view>

namespace MetaModule
{

rack::engine::Module *as_rack_module(CoreProcessor *module);

void plugin_module_set_model(std::unique_ptr<CoreProcessor> &module, std::string_view combined_slug);
void plugin_module_init(std::unique_ptr<CoreProcessor> &module);
void plugin_module_deinit(std::unique_ptr<CoreProcessor> &module);

CoreProcessor::PolyPortBuffer plugin_module_get_poly_output_buffer(std::unique_ptr<CoreProcessor> &module,
																   int output_id);
CoreProcessor::PolyPortBuffer plugin_module_get_poly_input_buffer(std::unique_ptr<CoreProcessor> &module, int input_id);

} // namespace MetaModule
