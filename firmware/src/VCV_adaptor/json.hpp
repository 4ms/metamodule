#pragma once
#include <string>
#include <string_view>

namespace rack
{

struct json_t {};

inline json_t *json_object() {
	return nullptr;
}

inline json_t *json_boolean(bool) {
	return nullptr;
}

inline json_t *json_integer(int) {
	return nullptr;
}

inline json_t *json_array() {
	return nullptr;
}

inline json_t *json_string(const char *) {
	return nullptr;
}

inline json_t *json_object_get(json_t *, std::string_view) {
	return nullptr;
}

inline bool json_boolean_value(json_t *) {
	return false;
}

inline int json_integer_value(json_t *) {
	return 0;
}

inline std::string json_string_value(json_t *) {
	return "";
}

inline json_t *json_array_get(json_t *, int) {
	return nullptr;
}

inline void json_object_set_new(json_t *, std::string_view, json_t *) {
}

inline void json_array_insert_new(json_t *, int, json_t *) {
}

inline void json_array_append_new(json_t *, json_t *) {
}

} // namespace rack
