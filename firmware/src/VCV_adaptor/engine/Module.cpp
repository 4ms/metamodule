#include "Module.hpp"
#include "jansson.h"
#include "pr_dbg.hh"

namespace rack::engine
{

void Module::initialize_state(std::string_view state_data) {
	if (state_data.size() == 0)
		return;

	json_error_t err;

	json_t *root = json_loadb(state_data.data(), state_data.size(), 0, &err);
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
		return ""; // Do nothing if module has no state to store

	std::string state_str;
	auto sz = json_dumpb(dataJ, nullptr, 0, JSON_COMPACT);
	if (sz > 0) {
		state_str.resize(sz);
		json_dumpb(dataJ, state_str.data(), sz, JSON_COMPACT);
	}

	return state_str;
}

} // namespace rack::engine
