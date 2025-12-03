#pragma once
#include "concurrent_buffer.hh"
#include "conf/ramdisk_conf.hh"

namespace MetaModule
{

class PatchPlayer;
class PatchPlayLoader;
class FileStorageProxy;
class OpenPatchManager;

struct A7SharedMemoryS {
	struct Ptrs {
		FileStorageProxy *patch_storage{};
		RamDrive *ramdrive{};
		ConcurrentBuffer *console_buffer{};
	};

	static Ptrs ptrs;
};

} // namespace MetaModule
