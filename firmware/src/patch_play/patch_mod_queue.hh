#pragma once
#include "patch/patch.hh"
#include "util/lockfree_fifo_spsc.hh"
#include "util/overloaded.hh"
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
	uint32_t set_id;
	float cur_val;
};

struct EditMappingMinMax {
	MappedKnob map;
	uint32_t set_id;
	float cur_val;
};

struct RemoveMapping {
	MappedKnob map;
	uint32_t set_id;
};

struct ModifyMapping {
	MappedKnob map;
};

struct AddMidiMap {
	MappedKnob map;
};

using PatchModRequest = std::
	variant<SetStaticParam, AddMapping, EditMappingMinMax, RemoveMapping, AddMidiMap, ModifyMapping, ChangeKnobSet>;

using PatchModQueue = LockFreeFifoSpsc<PatchModRequest, 32>;

} // namespace MetaModule
