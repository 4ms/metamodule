#pragma once
#include "CoreModules/elements/element_counter.hh"
#include "console/pr_dbg.hh"
#include "gui/elements/element_type.hh"
#include <cstdint>

namespace MetaModule
{

// Store module/param ids in lvgl object userdata
struct ModuleParamUserData {
	uint16_t module_id;
	uint16_t param_id;

	static ModuleParamUserData unpack(void *user_data) {
		// Caller must check if user_data is nullptr
		auto user_data_num = reinterpret_cast<uintptr_t>(user_data) - 1;
		return ModuleParamUserData{uint16_t(user_data_num >> 16), uint16_t(user_data_num & 0x0000FFFF)};
	}

	operator void *() {
		uintptr_t packed = (module_id << 16) | param_id;
		if (param_id == 0xFFFF) {
			pr_err("Error: param id of 0xFFFF is not supported by KnobSetView\n");
			packed--;
		}
		return reinterpret_cast<void *>(packed + 1);
	}
};

// Store and retreive module/jack index and type (in/out) in lvgl object userdata
struct CableEndpointUserData {
	uint16_t module_id;
	ElementCount::Indices idx;

	CableEndpointUserData(uint16_t module_id, ElementCount::Indices idx)
		: module_id{module_id}
		, idx{idx} {
	}

	CableEndpointUserData(void *userdata) {
		auto raw = reinterpret_cast<uintptr_t>(userdata);

		module_id = (raw & 0xFFFF0000) >> 16;

		idx = ElementCount::NoElementIndices;
		if (raw & 0x8000)
			idx.input_idx = raw & 0x7FFF;
		else
			idx.output_idx = raw & 0x7FFF;
	}

	operator void *() {
		uint16_t jack_id = 0;

		//Top bit is set for input jacks
		if (idx.input_idx != ElementCount::Indices::NoElementMarker)
			jack_id = idx.input_idx | 0x8000;
		else if (idx.output_idx != ElementCount::Indices::NoElementMarker)
			jack_id = idx.output_idx;
		else
			pr_err("Error: MapCableUserData without a valid input or output jack\n");

		uintptr_t packed = (module_id << 16) | jack_id;
		return reinterpret_cast<void *>(packed);
	}
};

// Store and retreive panel jack id and type (in/out) in the gui object's user_data field
struct PanelJackMapUserData {
	uint32_t panel_jack_id;
	bool is_input;
	bool is_valid = true;

	PanelJackMapUserData(uint32_t panel_jack_id, ElementType type)
		: panel_jack_id{panel_jack_id}
		, is_input{type == ElementType::Input}
		, is_valid{true} {
	}

	PanelJackMapUserData(void *userdata) {
		auto raw = reinterpret_cast<uintptr_t>(userdata);
		is_input = raw & (1 << 31);
		panel_jack_id = raw & ~(1 << 31);

		is_valid = (panel_jack_id > 0);
		panel_jack_id = panel_jack_id - 1;
	}

	operator void *() {
		uintptr_t packed = (panel_jack_id + 1) | (is_input << 31);
		return reinterpret_cast<void *>(packed);
	}
};
} // namespace MetaModule
