#pragma once
#include "drivers/cache.hh"
#include <cstdint>

// Defined in linker script
extern uint32_t *_params_ptr;

struct SharedMemory {
	SharedMemory() = delete;

	template<typename T>
	static void write_address_of(T *object, uint32_t offset) {
		auto *loc_ptr = reinterpret_cast<uint32_t *>(&_params_ptr);
		*(loc_ptr + offset) = reinterpret_cast<uint32_t>(object);

		auto addr = &_params_ptr + offset * 4;
		mdrivlib::SystemCache::clean_dcache_by_addr(addr);
	}

	template<typename T>
	static T read_address_of(uint32_t offset) {
		auto *loc_ptr = reinterpret_cast<uint32_t *>(&_params_ptr);
		return reinterpret_cast<T>(*(loc_ptr + offset));
	}

	enum : uint32_t {
		ParamsPtrLocation = 0,
		RamDiskLocation,
		AuxSignalBlockLocation,
		PatchPlayerLocation,
	};

	//////////////// TODO: Test this alternative method:
	// enum class Location : uint32_t {
	// 	ParamsPtr = 0,
	// 	RamDisk,
	// 	AuxSignalBlock,
	// 	PatchPlayer,
	// };

	// static inline __attribute__((section(".sharedmemindex"))) uint32_t shared_memory_addrs[4];

	// template<Location Loc, typename T>
	// static void register_address_of(T *object) {
	// 	auto index = static_cast<uint32_t>(Loc);
	// 	shared_memory_addrs[index] = reinterpret_cast<uint32_t>(object);
	// 	mdrivlib::SystemCache::clean_dcache_by_addr(&(shared_memory_addrs[index]));
	// }

	// template<typename T>
	// static T get_shared_obj_ptr(Location loc) {
	// 	auto index = static_cast<uint32_t>(loc);
	// 	return reinterpret_cast<T>(shared_memory_addrs[index]);
	// }
};
