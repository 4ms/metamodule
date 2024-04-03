#include "engine/Module.hpp"
#include "console/pr_dbg.hh"
#include "jansson.h"

namespace rack::engine
{

Module::Module() = default;

Module::~Module() {
}

void Module::initialize_state(std::string_view state_string) {
	json_error_t err;
	json_t *root = json_loadb(state_string.data(), state_string.size(), 0, &err);
	if (!root) {
		pr_err("JSON decode error: %d:%d %s\n", err.line, err.column, err.text);
		return;
	}

	json_t *data = json_object_get(root, "data");
	if (data)
		this->dataFromJson(data);

	json_decref(root);
}

void Module::config(int num_params, int num_inputs, int num_outputs, int num_lights) {
	params.resize(num_params);
	for (auto &x : params)
		x.value = 0;

	inputs.resize(num_inputs);
	for (auto &x : inputs)
		x.voltage = 0;

	outputs.resize(num_outputs);
	for (auto &x : outputs)
		x.voltage = 0;

	lights.resize(num_lights);
	for (auto &x : lights)
		x.value = 0;

	paramQuantities.resize(num_params);

	inputInfos.resize(num_inputs);

	outputInfos.resize(num_outputs);

	lightInfos.resize(num_lights);
}

} // namespace rack::engine
