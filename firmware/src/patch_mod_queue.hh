#pragma once

#include "patch.hh"
#include "util/circular_buffer_opt.hh"
#include <variant>

namespace MetaModule
{

struct SetStaticParam {
	StaticParam param;
};

struct AddMapping {
	MappedKnob map;
};

struct ModifyMapping {
	MappedKnob map;
};

using PatchModRequest = std::variant<SetStaticParam, AddMapping, ModifyMapping>;

using PatchModQueue = CircularBufferOpt<PatchModRequest, 32>;

template<class... Ts>
struct overloaded : Ts... {
	using Ts::operator()...;
};
// Not needed in gcc 11, but needed for clangd 15
template<class... Ts>
overloaded(Ts...) -> overloaded<Ts...>;

} // namespace MetaModule
