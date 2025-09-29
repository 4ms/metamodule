#pragma once
#include "console/pr_dbg.hh"
#include <cstdint>
#include <utility>

namespace MetaModule
{

inline void *pack_user_data_from_module_param(uint16_t module_id, uint16_t param_id) {
	uintptr_t packed = (module_id << 16) | param_id;
	if (param_id == 0xFFFF) {
		pr_err("Error: param id of 0xFFFF is not supported by KnobSetView\n");
		packed--;
	}
	return reinterpret_cast<void *>(packed + 1);
}

inline std::pair<uint16_t, uint16_t> unpack_user_data_to_module_param(void *user_data) {
	// Caller must check if user_data is nullptr
	auto user_data_num = reinterpret_cast<uintptr_t>(user_data) - 1;
	return {user_data_num >> 16, user_data_num & 0x0000FFFF};
}

} // namespace MetaModule
