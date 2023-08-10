#pragma once

#include "patch/patch.hh"
#include "util/lockfree_fifo_spsc.hh"
#include <variant>

namespace MetaModule
{

struct ChangeKnobSet {
	unsigned knobset_num;
};

struct SetStaticParam {
	StaticParam param;
};

struct AddMapping {
	MappedKnob map;
};

struct ModifyMapping {
	MappedKnob map;
};

using PatchModRequest = std::variant<SetStaticParam, AddMapping, ModifyMapping, ChangeKnobSet>;
static_assert(sizeof(PatchModRequest) == 36);

using PatchModQueue = LockFreeFifoSpsc<PatchModRequest, 32>;

template<class... Ts>
struct overloaded : Ts... {
	using Ts::operator()...;
};
// Not needed in gcc 11, but needed for clangd 15
template<class... Ts>
overloaded(Ts...) -> overloaded<Ts...>;

} // namespace MetaModule
