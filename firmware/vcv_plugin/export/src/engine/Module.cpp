#include "engine/Module.hpp"
#include "console/pr_dbg.hh"
#include "jansson.h"

namespace rack::engine
{

Module::Module() {
	onReset();
}

Module::~Module() {
}

void Module::load_state(std::string_view state_data) {
	if (state_data.size() == 0) {
		onReset();
		return;
	}

	json_error_t err;

	json_t *root = json_loadb((char *)state_data.data(), state_data.size(), 0, &err);
	if (!root) {
		pr_err("JSON decode error: %d:%d %s\n", err.line, err.column, err.text);
		return;
	}

	this->dataFromJson(root);

	json_decref(root);
}

std::string Module::save_state() {
	json_t *dataJ = this->dataToJson();

	if (!dataJ)
		return {};

	std::string state_data;
	auto sz = json_dumpb(dataJ, nullptr, 0, JSON_COMPACT);
	if (sz > 0) {
		state_data.resize(sz);
		json_dumpb(dataJ, (char *)state_data.data(), sz, JSON_COMPACT);
	}

	json_decref(dataJ);

	return state_data;
}

void Module::config(int num_params, int num_inputs, int num_outputs, int num_lights) {
	params.resize(num_params);
	for (auto &x : params)
		x.value = 0;

	inputs.resize(num_inputs);
	for (auto &x : inputs)
		x.setVoltage(0.f);

	outputs.resize(num_outputs);
	for (auto &x : outputs)
		x.setVoltage(0.f);

	lights.resize(num_lights);
	for (auto &x : lights)
		x.value = 0;

	paramQuantities.resize(num_params);

	inputInfos.resize(num_inputs);

	outputInfos.resize(num_outputs);

	lightInfos.resize(num_lights);
}

} // namespace rack::engine
