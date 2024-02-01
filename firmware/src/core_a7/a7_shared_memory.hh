#pragma once
#include "patch_play/patch_mod_queue.hh"

namespace MetaModule
{

class PatchPlayer;
class PatchPlayLoader;
class FileStorageProxy;
class SyncParams;

struct A7SharedMemoryS {
	struct Ptrs {
		PatchPlayer *patch_player{};
		PatchPlayLoader *patch_playloader{};
		FileStorageProxy *patch_storage{};
		SyncParams *sync_params{};
		PatchModQueue *patch_mod_queue{};
	};

	static Ptrs ptrs;
};

} // namespace MetaModule
