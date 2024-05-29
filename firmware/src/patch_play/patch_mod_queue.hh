#pragma once
#include "CoreModules/module_type_slug.hh"
#include "gui/elements/element_type.hh"
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
	uint32_t set_id{};
};

struct EditMappingMinMax {
	MappedKnob map;
	uint32_t set_id{};
	float cur_val{};
};

struct RemoveMapping {
	MappedKnob map;
	uint32_t set_id{};
};

struct ModifyMapping {
	MappedKnob map;
};

struct AddMidiMap {
	MappedKnob map;
};

struct AddInternalCable {
	Jack out;
	Jack in;
};

struct DisconnectJack {
	Jack jack;
	ElementType type;
};

struct AddJackMapping {
	uint16_t panel_jack_id;
	Jack jack;
	ElementType type;
};

struct AddModule {
	BrandModuleSlug slug{};
};

struct RemoveModule {
	uint16_t module_idx{};
};

using PatchModRequest = std::variant<SetStaticParam,
									 AddMapping,
									 EditMappingMinMax,
									 RemoveMapping,
									 AddMidiMap,
									 ModifyMapping,
									 ChangeKnobSet,
									 AddInternalCable,
									 AddJackMapping,
									 DisconnectJack,
									 AddModule,
									 RemoveModule>;

using PatchModQueue = LockFreeFifoSpsc<PatchModRequest, 128>;

} // namespace MetaModule
