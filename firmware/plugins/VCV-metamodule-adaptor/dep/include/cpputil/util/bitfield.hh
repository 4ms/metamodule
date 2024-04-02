#pragma once
#include <cstdint>
#include <initializer_list>
#include <type_traits>

template<typename T>
auto constexpr bitfield(T const val) {
	return static_cast<std::underlying_type_t<T>>(val);
}

template<std::integral T>
auto constexpr bitfield(T const val) {
	return static_cast<T>(val);
}

// bitfield(...) makes sure we only OR together values of the same enum
// It also works on integral types
template<typename... Ts>
auto constexpr bitfield(const Ts... args) {
	return (... | bitfield(args));
}

template<typename Enum>
constexpr std::underlying_type_t<Enum> OR(std::initializer_list<Enum> fields) {
	using UT = std::underlying_type_t<Enum>;
	UT val;
	for (auto el : fields) {
		val |= static_cast<UT>(el);
	}
	return val;
}

template<typename Enum>
constexpr auto val(Enum field) {
	return static_cast<std::underlying_type_t<Enum>>(field);
}
