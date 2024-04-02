#pragma once
#include <cstddef>
#include <string>
#include <string_view>

// A null-terminated string with fixed compile-time capacity
template<size_t CAPACITY>
struct StaticString {
	char _data[CAPACITY + 1];

	static constexpr size_t capacity = CAPACITY;

	constexpr StaticString() {
		_data[0] = '\0';
	}

	constexpr StaticString(std::string_view s) {
		copy(s);
	}

	constexpr StaticString(const char *s) {
		copy(s);
	}

	constexpr void copy(const char *s) {
		size_t i = 0;
		while (*s && i < CAPACITY) {
			_data[i] = *s;
			i++;
			s++;
		}
		_data[i] = '\0';
	}

	constexpr void copy(std::string_view s) {
		size_t i = 0;
		for (auto c : s) {
			_data[i++] = c;
			if (i >= CAPACITY)
				break;
		}
		_data[i] = '\0';
	}

	const char *c_str() const {
		return _data;
	}

	const char *data() const {
		return _data;
	}

	size_t length() const {
		return std::string_view{_data}.length();
	}

	size_t size() const {
		return length();
	}

	template<size_t CAP2>
	bool operator==(const StaticString<CAP2> &rhs) const {
		return std::string_view{_data} == std::string_view{rhs};
	}

	bool is_equal(const char *rhs) const {
		return std::string_view{_data} == std::string_view{rhs};
	}

	operator const char *() const {
		return _data;
	}

	operator std::string() const {
		return _data;
	}

	operator std::string_view() const {
		return _data;
	}

	// volatile combinations:
	// clang-format off
  constexpr void copy(const char *s) volatile { const_cast<StaticString<CAPACITY>*>(this)->copy(s); }

  template <size_t OTHER_CAP>
  constexpr void copy(StaticString<OTHER_CAP> const &other) { copy(other.data()); }

  template <size_t OTHER_CAP>
  constexpr void copy(StaticString<OTHER_CAP> volatile const &other) volatile { copy(const_cast<StaticString<OTHER_CAP> const &>(other).data()); }

  template <size_t OTHER_CAP>
  constexpr void copy(StaticString<OTHER_CAP> const &other) volatile { copy(other.data()); }
	// clang-format on
};
