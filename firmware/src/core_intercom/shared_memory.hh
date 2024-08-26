#pragma once
#include "audio/auxsignal.hh"
#include "conf/ramdisk_conf.hh"
#include "core_intercom/intercore_modulefs_message.hh"
#include "params/param_block.hh"

namespace MetaModule
{
//fwd declare to reduce dependencies
class IntercoreStorageMessage;

//TODO: Move this structure to static_buffers.hh and declare static inline ptrs there too
struct SharedMemoryS {
	struct Ptrs {
		DoubleBufParamBlock *param_block;
		DoubleAuxStreamBlock *auxsignal_block;
		RamDrive *ramdrive;
		IntercoreStorageMessage *icc_message;
		IntercoreModuleFS::Message *icc_modulefs_message_core0;
		IntercoreModuleFS::Message *icc_modulefs_message_core1;
	};

	static Ptrs ptrs;
};

} // namespace MetaModule
