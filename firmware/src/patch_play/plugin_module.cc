#include "plugin_module.hh"
#include "CoreModules/CoreProcessor.hh"
#include "engine/Module.hpp"
#include "vcv_plugin/internal/rack_model_lookup.hh"

namespace MetaModule
{

static rack::engine::Module *get_rack_plugin_module(std::unique_ptr<CoreProcessor> &module) {
	return dynamic_cast<rack::engine::Module *>(module.get());
}

static CoreProcessorPoly *get_coreprocpoly_plugin_module(std::unique_ptr<CoreProcessor> &module) {
	return dynamic_cast<CoreProcessorPoly *>(module.get());
}

rack::engine::Module *as_rack_module(CoreProcessor *module) {
	return dynamic_cast<rack::engine::Module *>(module);
}

void plugin_module_set_model(std::unique_ptr<CoreProcessor> &module, std::string_view combined_slug) {
	if (auto rack_module = get_rack_plugin_module(module)) {
		if (!rack_module->model)
			rack_module->model = RackModelLookup::find(combined_slug);
	}
}

void plugin_module_init(std::unique_ptr<CoreProcessor> &module) {
	if (auto rack_module = get_rack_plugin_module(module)) {
		rack::engine::Module::AddEvent a{};
		rack_module->onAdd(a);
	}
}

void plugin_module_deinit(std::unique_ptr<CoreProcessor> &module) {
	if (auto rack_module = get_rack_plugin_module(module)) {
		rack::engine::Module::RemoveEvent rm{};
		rack_module->onRemove(rm);
	}
}

CoreProcessor::PolyPortBuffer plugin_module_get_poly_output_buffer(std::unique_ptr<CoreProcessor> &module,
																   int output_id) {
	if (auto rack_module = get_rack_plugin_module(module)) {
		if (output_id < (int)rack_module->outputs.size())
			return {rack_module->outputs[output_id].voltages.begin(), &rack_module->outputs[output_id].channels};
	} else if (auto corepoly_module = get_coreprocpoly_plugin_module(module)) {
		return corepoly_module->get_poly_output_buffer(output_id);
	}

	return {nullptr, nullptr};
}

CoreProcessor::PolyPortBuffer plugin_module_get_poly_input_buffer(std::unique_ptr<CoreProcessor> &module,
																  int input_id) {
	if (auto rack_module = get_rack_plugin_module(module)) {
		if (input_id < (int)rack_module->inputs.size())
			return {rack_module->inputs[input_id].voltages.begin(), &rack_module->inputs[input_id].channels};
	} else if (auto corepoly_module = get_coreprocpoly_plugin_module(module)) {
		return corepoly_module->get_poly_input_buffer(input_id);
	}

	return {nullptr, nullptr};
}

} // namespace MetaModule
