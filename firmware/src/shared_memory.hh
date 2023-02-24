#pragma once
// #include "auxsignal.hh"
// #include "conf/ramdisk_conf.hh"
#include "drivers/cache.hh"
// #include "ramdisk.hh"
#include <cstdint>

// Defined in linker script
// extern uint32_t _shared_list[];

// struct SharedMemory {
// 	SharedMemory() = delete;

// 	template<typename T>
// 	static void write_address_of(T *object, uint32_t offset) {
// 		auto *loc_ptr = reinterpret_cast<uint32_t *>(_shared_list);
// 		*(loc_ptr + offset) = reinterpret_cast<uint32_t>(object);

// 		auto addr = _shared_list + offset * 4;
// 		mdrivlib::SystemCache::clean_dcache_by_addr(addr);
// 	}

// 	template<typename T>
// 	static T read_address_of(uint32_t offset) {
// 		auto *loc_ptr = reinterpret_cast<uint32_t *>(_shared_list);
// 		return reinterpret_cast<T>(*(loc_ptr + offset));
// 	}

// 	static void write_value(uint32_t val, uint32_t offset) {
// 		auto *loc_ptr = reinterpret_cast<uint32_t *>(_shared_list);
// 		*(loc_ptr + offset) = val;

// 		auto addr = _shared_list + offset * 4;
// 		mdrivlib::SystemCache::clean_dcache_by_addr(addr);
// 	}

// 	static uint32_t read_value(uint32_t offset) {
// 		auto *loc_ptr = reinterpret_cast<uint32_t *>(_shared_list);
// 		return *(loc_ptr + offset);
// 	}

// 	enum : uint32_t {
// 		ParamsPtrLocation = 0,
// 		AuxSignalBlockLocation,
// 		RamDiskLocation,
// 		PatchPlayerLocation,
// 		InterCoreCommParamsLocation,
// 		PatchListLocation,
// 		PatchDataLocation,
// 	};
// };

//////////////// TODO: Test this alternative method:
#include "auxsignal.hh"
#include "conf/ramdisk_conf.hh"
#include "inter_core_comm.hh"
#include "params.hh"
#include "patch_file.hh"
// #include "patch_player.hh"

#include <span>
namespace MetaModule
{
//fwd declare so that main-m4.cc doesn't have to #include "patch_player.hh"
class PatchPlayer;

struct SharedMemoryS {

	struct SharedMemoryPtrs {
		DoubleBufParamBlock *param_block;			//ParamsPtrLocation
		DoubleAuxStreamBlock *auxsignal_block;		//AuxSignalBlockLocation
		RamDrive *ramdrive;							//RamDiskLocation
		PatchPlayer *patch_player;					//PatchPlayer
		volatile InterCoreCommMessage *icc_message; //InterCoreCommParamsLocation
		std::span<PatchFile> *patch_file_list;		//PatchListLocation
		std::span<char> *raw_patch_span;			//PatchDataLocation
	};

	static inline __attribute__((section(".sharedmemindex"))) SharedMemoryPtrs ptrs;
};

//TODO: Safer yet?
// #include <tuple>
// using shared_data_t = std::tuple<DoubleBufParamBlock *,	 //ParamsPtrLocation
// 								 DoubleAuxStreamBlock *, //AuxSignalBlockLocation
// 								 RamDrive *,			 //RamDiskLocation
// 								 PatchPlayer *,			 //PatchPlayer
// 								 InterCoreCommMessage *, //InterCoreCommParamsLocation
// 								 std::span<PatchFile> *, //PatchListLocation
// 								 std::span<char> *>;	 //PatchDataLocation
// template<size_t ParamID>
// static auto read_address_of() {
// 	auto *loc_ptr = reinterpret_cast<uint32_t *>(_shared_list);
// 	return reinterpret_cast<std::tuple_element<ParamID, shared_data_t>>(*(loc_ptr + ParamID));
// }

} // namespace MetaModule
