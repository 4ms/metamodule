#include "Module.hpp"
#include "jansson.h"
#include "pr_dbg.hh"

namespace rack::engine
{

void Module::load_state(std::span<const uint8_t> state_data) {
	if (state_data.size() == 0)
		return;

	json_error_t err;

	json_t *root = json_loadb((char *)state_data.data(), state_data.size(), 0, &err);
	if (!root) {
		pr_err("JSON decode error: %d:%d %s\n", err.line, err.column, err.text);
		return;
	}

	this->dataFromJson(root);

	json_decref(root);
}

std::vector<uint8_t> Module::save_state() {
	json_t *dataJ = this->dataToJson();

	if (!dataJ)
		return {};

	std::vector<uint8_t> state_data;
	auto sz = json_dumpb(dataJ, nullptr, 0, JSON_COMPACT);
	if (sz > 0) {
		state_data.resize(sz);
		json_dumpb(dataJ, (char *)state_data.data(), sz, JSON_COMPACT);
	}

	json_decref(dataJ);

	return state_data;
}

} // namespace rack::engine
