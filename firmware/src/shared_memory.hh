#pragma once
#include "auxsignal.hh"
#include "conf/ramdisk_conf.hh"
#include "inter_core_comm.hh"
#include "params.hh"
#include "patch_file.hh"
// #include "patch_player.hh"
#include <cstdint>
#include <span>

namespace MetaModule
{
//fwd declare so that main-m4.cc doesn't have to #include "patch_player.hh"
class PatchPlayer;

//TODO: Move this structure to static_buffers.hh and declar static inline ptrs there too
struct SharedMemoryS {
	struct Ptrs {
		DoubleBufParamBlock *param_block;			//ParamsPtrLocation
		DoubleAuxStreamBlock *auxsignal_block;		//AuxSignalBlockLocation
		RamDrive *ramdrive;							//RamDiskLocation
		PatchPlayer *patch_player;					//PatchPlayer
		volatile InterCoreCommMessage *icc_message; //InterCoreCommParamsLocation
		std::span<PatchFile> *patch_file_list;		//PatchListLocation
		std::span<char> *raw_patch_span;			//PatchDataLocation
	};

	static Ptrs ptrs;
};

} // namespace MetaModule
