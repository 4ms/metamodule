#pragma once
#include "concurrent_buffer.hh"
#include "conf/ramdisk_conf.hh"

namespace MetaModule
{

class PatchPlayer;
class PatchPlayLoader;
class FileStorageProxy;
class SyncParams;
class OpenPatchManager;

struct A7SharedMemoryS {
	struct Ptrs {
		FileStorageProxy *patch_storage{};
		SyncParams *sync_params{};
		RamDrive *ramdrive{};
		ConcurrentBuffer *console_buffer{};
	};

	static Ptrs ptrs;
};

} // namespace MetaModule
