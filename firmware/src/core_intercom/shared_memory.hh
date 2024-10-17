#pragma once
#include "conf/ramdisk_conf.hh"
#include "params/param_block.hh"

namespace MetaModule
{
//fwd declare to reduce dependencies
class IntercoreStorageMessage;

//TODO: Move this structure to static_buffers.hh and declare static inline ptrs there too
struct SharedMemoryS {
	struct Ptrs {
		DoubleBufParamBlock *param_block;
		RamDrive *ramdrive;
		IntercoreStorageMessage *icc_message;
	};

	static Ptrs ptrs;
};

} // namespace MetaModule
