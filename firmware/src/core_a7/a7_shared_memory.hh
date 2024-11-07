#pragma once
#include "conf/ramdisk_conf.hh"
#include "patch_play/patch_mod_queue.hh"

namespace MetaModule
{

class PatchPlayer;
class PatchPlayLoader;
class FileStorageProxy;
class SyncParams;
class OpenPatchManager;

struct A7SharedMemoryS {
	struct Ptrs {
		PatchPlayer *patch_player{};
		PatchPlayLoader *patch_playloader{};
		FileStorageProxy *patch_storage{};
		OpenPatchManager *open_patch_manager{};
		SyncParams *sync_params{};
		PatchModQueue *patch_mod_queue{};
		RamDrive *ramdrive{};
	};

	static Ptrs ptrs;
};

} // namespace MetaModule
