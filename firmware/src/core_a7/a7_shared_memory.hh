#pragma once
#include "concurrent_buffer.hh"

namespace MetaModule
{

class PatchPlayer;
class PatchPlayLoader;
class FileStorageProxy;
class OpenPatchManager;

struct A7SharedMemoryS {
	struct Ptrs {
		ConcurrentBuffer *console_buffer{};
	};

	static Ptrs ptrs;
};

} // namespace MetaModule
