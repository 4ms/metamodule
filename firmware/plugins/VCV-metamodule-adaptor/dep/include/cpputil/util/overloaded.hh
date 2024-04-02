#pragma once

template<class... Ts>
struct overloaded : Ts... {
	using Ts::operator()...;
};
// Not needed in gcc 11, but needed for clangd 15
template<class... Ts>
overloaded(Ts...) -> overloaded<Ts...>;
