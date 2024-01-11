#pragma once
#include "audio/auxsignal.hh"
#include "conf/ramdisk_conf.hh"
#include "params/param_block.hh"
#include "patch_file/patch_dir_list.hh"
#include "patch_play/patch_mod_queue.hh"
#include <cstdint>
#include <span>

namespace MetaModule
{
//fwd declare to reduce dependencies
class IntercoreStorageMessage;
class PatchPlayer;
class PatchPlayLoader;
class FileStorageProxy;
class SyncParams;

//TODO: Move this structure to static_buffers.hh and declar static inline ptrs there too
struct SharedMemoryS {
	struct Ptrs {
		DoubleBufParamBlock *param_block;
		DoubleAuxStreamBlock *auxsignal_block;
		RamDrive *ramdrive;
		IntercoreStorageMessage *icc_message;
		std::span<char> *raw_patch_span;
		PatchPlayer *patch_player;
		PatchPlayLoader *patch_playloader;
		const PatchDirList *patch_dir_list;
		FileStorageProxy *patch_storage;
		SyncParams *sync_params;
		PatchModQueue *patch_mod_queue;
	};

	static Ptrs ptrs;
};

} // namespace MetaModule
