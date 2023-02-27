#pragma once
#include "auxsignal.hh"
#include "conf/ramdisk_conf.hh"
#include "inter_core_comm_msg.hh"
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
		DoubleBufParamBlock *param_block;
		DoubleAuxStreamBlock *auxsignal_block;
		RamDrive *ramdrive;
		PatchPlayer *patch_player;
		volatile InterCoreCommMessage *icc_message;
		PatchFileList *patch_file_list;
		std::span<char> *raw_patch_span;
	};

	static Ptrs ptrs;
};

} // namespace MetaModule
