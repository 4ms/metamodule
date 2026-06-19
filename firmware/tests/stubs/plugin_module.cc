#include "CoreModules/CoreProcessor.hh"
#include "test_poly_module.hh"
#include <memory>

namespace MetaModule
{

void plugin_module_init(std::unique_ptr<CoreProcessor> &module) {
}
void plugin_module_deinit(std::unique_ptr<CoreProcessor> &module) {
}

CoreProcessor::PolyPortBuffer plugin_module_get_poly_output_buffer(std::unique_ptr<CoreProcessor> &module,
																   int output_id) {
	if (auto m = dynamic_cast<TestPolyModule *>(module.get())) {
		if ((unsigned)output_id < TestPolyModule::NumOutputs)
			return {m->output_poly[output_id].data(), &m->output_channels[output_id]};
	}

	return {nullptr, nullptr};
}

CoreProcessor::PolyPortBuffer plugin_module_get_poly_input_buffer(std::unique_ptr<CoreProcessor> &module,
																  int input_id) {
	if (auto m = dynamic_cast<TestPolyModule *>(module.get())) {
		if ((unsigned)input_id < TestPolyModule::NumInputs)
			return {m->input_poly[input_id].data(), &m->input_channels[input_id]};
	}
	return {nullptr, nullptr};
}

} // namespace MetaModule
