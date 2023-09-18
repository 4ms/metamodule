#pragma once
#include "audio/auxsignal.hh"
#include "conf/ramdisk_conf.hh"
#include "core_intercom/patch_icc_message.hh"
#include "param_block.hh"
#include "params/sync_params.hh"
#include "patch_file/patch_file.hh"
#include "patch_play/patch_mod_queue.hh"
#include "patch_play/patch_playloader.hh"
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
		volatile PatchICCMessage *icc_message;
		PatchFileList *patch_file_list;
		std::span<char> *raw_patch_span;
		PatchPlayer *patch_player;
		PatchPlayLoader *patch_playloader;
		PatchStorageProxy *patch_storage;
		SyncParams *sync_params;
		PatchModQueue *patch_mod_queue;
	};

	static Ptrs ptrs;
};

} // namespace MetaModule
