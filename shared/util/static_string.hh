#pragma once
#include <cstddef>
#include <cstring>
#include <string>

// A null-terminated string with fixed compile-time capacity
template<size_t CAPACITY>
struct StaticString {
	char data[CAPACITY + 1];

	static constexpr size_t capacity = CAPACITY;

	constexpr StaticString() {
		data[0] = '\0';
	}

	constexpr StaticString(std::string_view s) {
		size_t i = 0;
		for (auto c : s) {
			data[i++] = c;
			if (i >= CAPACITY)
				break;
		}
		data[i] = '\0';
	}

	constexpr StaticString(const char *s) {
		size_t i = 0;
		while (*s && i < CAPACITY) {
			data[i] = *s;
			i++;
			s++;
		}
		data[i] = '\0';
	}

	const char *cstr() const {
		return data;
	}

	const char *c_str() const {
		return data;
	}

	template<size_t CAP2>
	bool operator==(const StaticString<CAP2> &rhs) const {
		return (strcmp(data, rhs.data) == 0);
	}

	bool is_equal(const char *rhs) const {
		return (strcmp(data, rhs) == 0);
	}

	operator const char *() const {
		return data;
	}
};
