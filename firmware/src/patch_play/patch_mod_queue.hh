#pragma once
#include "gui/elements/element_type.hh"
#include "patch/module_type_slug.hh"
#include "patch/patch.hh"
#include "util/lockfree_fifo_spsc.hh"
#include <string>
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

struct ModifyMapping {
	MappedKnob map;
	uint32_t set_id{};
};

struct RemoveMapping {
	MappedKnob map;
	uint32_t set_id{};
};

struct AddMidiMap {
	MappedKnob map;
};

struct AddInternalCable {
	Jack out;
	Jack in;
};

// Removes all mappings and cables
struct DisconnectJack {
	Jack jack;
	ElementType type;
};

struct RemoveJackMappings {
	Jack jack;
	ElementType type;
};

struct AddJackMapping {
	uint16_t panel_jack_id;
	Jack jack;
	ElementType type;
};

struct CalibrationOnOff {
	bool enable;
};

struct SetChanCalibration {
	float slope{1.f};
	float offset{0.f};
	uint16_t channel{};
	bool is_input{};
};

struct SetMidiPolyNum {
	uint32_t poly_num;
};

struct LoadModuleState {
	uint16_t module_id;
	std::string data;
};

struct SetModuleBypass {
	uint16_t module_id;
	bool bypassed;
};

using PatchModRequest = std::variant<SetStaticParam,
									 AddMapping,
									 ModifyMapping,
									 RemoveMapping,
									 AddMidiMap,
									 ChangeKnobSet,
									 AddInternalCable,
									 AddJackMapping,
									 DisconnectJack,
									 RemoveJackMappings,
									 CalibrationOnOff,
									 SetChanCalibration,
									 SetMidiPolyNum,
									 LoadModuleState,
									 SetModuleBypass>;

using PatchModQueue = LockFreeFifoSpsc<PatchModRequest, 128>;

} // namespace MetaModule
