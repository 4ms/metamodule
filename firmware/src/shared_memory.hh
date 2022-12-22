#pragma once
#include "conf/ramdisk_conf.hh"
#include "drivers/cache.hh"
#include "ramdisk.hh"
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
};

//////////////// TODO: Test this alternative method:
// #include "auxsignal.hh"
// #include "conf/ramdisk_conf.hh"
// #include "params.hh"
// #include "patch_player.hh"
// #include "ramdisk.hh"

struct SharedMemorySafer {
	enum class Location : uint32_t {
		ParamsPtr = 0,
		RamDiskPtr,
		AuxSignalBlock,
		PatchPlayer,
	};

	static inline __attribute__((section(".sharedmemindex"))) uint32_t shared_memory_addrs[4];

	template<Location Loc, typename T>
	static void register_address_of(T *object) {
		auto index = static_cast<uint32_t>(Loc);
		shared_memory_addrs[index] = reinterpret_cast<uint32_t>(object);
		mdrivlib::SystemCache::clean_dcache_by_addr(&(shared_memory_addrs[index]));
	}

	// template<Location Loc, typename T>
	// static T get_shared_obj_ptr();

	// template<>
	// auto get_shared_obj_ptr<Location::ParamsPtr>() {
	// 	auto index = static_cast<uint32_t>(Location::ParamsPtr);
	// 	return *reinterpret_cast<MetaModule::DoubleBufParamBlock *>(shared_memory_addrs[index]);
	// }

	// template<>
	// auto get_shared_obj_ptr<Location::RamDiskPtr>() {
	// 	auto index = static_cast<uint32_t>(Location::RamDiskPtr);
	// 	return *reinterpret_cast<RamDisk<RamDiskSizeBytes, RamDiskBlockSize> *>(shared_memory_addrs[index]);
	// }

	// template<>
	// auto get_shared_obj_ptr<Location::AuxSignalBlock>() {
	// 	auto index = static_cast<uint32_t>(Location::AuxSignalBlock);
	// 	return *reinterpret_cast<MetaModule::DoubleAuxStreamBlock *>(shared_memory_addrs[index]);
	// }

	// template<>
	// auto get_shared_obj_ptr<Location::PatchPlayer>() {
	// 	auto index = static_cast<uint32_t>(Location::PatchPlayer);
	// 	return *reinterpret_cast<MetaModule::PatchPlayer *>(shared_memory_addrs[index]);
	// }

	template<typename T>
	static T get_shared_obj_ptr(Location loc) {
		auto index = static_cast<uint32_t>(loc);
		return reinterpret_cast<T>(shared_memory_addrs[index]);
	}
};
