#include "Module.hpp"
#include "jansson.h"
#include "pr_dbg.hh"

namespace rack::engine
{

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

} // namespace rack::engine
