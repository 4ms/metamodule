#pragma once
#include <string_view>

namespace rack
{

struct json_t {};

json_t *json_object() {
	return nullptr;
}

json_t *json_boolean(bool) {
	return nullptr;
}

json_t *json_object_get(json_t *, std::string_view) {
	return nullptr;
}

bool json_boolean_value(json_t *) {
	return false;
}

void json_object_set_new(json_t *, std::string_view, json_t *) {
}

} // namespace rack
