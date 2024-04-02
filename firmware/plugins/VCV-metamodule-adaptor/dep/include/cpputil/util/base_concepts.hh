#pragma once
#include <concepts>

template<class T, class U>
concept Derived = std::is_base_of<U, T>::value;

// template<class T>
// concept SignedNumber = std::is_signed_v<T>;

// template<class T>
// concept Numeric = std::integral<T> || std::is_floating_point_v<T>;
