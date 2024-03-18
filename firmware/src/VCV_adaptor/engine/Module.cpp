#include "Module.hpp"
#include "jansson.h"
#include "patch_convert/ryml/ryml_serial.hh"
#include "pr_dbg.hh"

namespace rack::engine
{

void Module::initialize_state(std::string_view state_yml) {
	// Deserialize yaml
	ryml::Tree tree = ryml::parse_in_arena(ryml::csubstr(state_yml.data(), state_yml.size()));

	if (tree.num_children(0) > 0) {
		ryml::ConstNodeRef yml_root = tree.rootref();

		// Re-serialize as json
		auto json_string = ryml::emitrs_json<std::string>(yml_root);

		// Pass json to VCV-native module's dataFromJson
		json_error_t err;
		json_t *root = json_loadb(json_string.data(), json_string.size(), 0, &err);
		if (!root) {
			pr_err("JSON decode error: %d:%d %s\n", err.line, err.column, err.text);
			return;
		}

		if (json_t *data = json_object_get(root, "data"); data)
			this->dataFromJson(data);

		json_decref(root);
	}
}

std::string Module::save_state() {
	//TODO: serialize result of this->dataToJson() as json, then convert to yml
	return "";
}

} // namespace rack::engine
