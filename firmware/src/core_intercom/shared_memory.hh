#pragma once
#include "conf/ramdisk_conf.hh"
#include "console/concurrent_buffer.hh"
#include "intercore_modulefs_message.hh"
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
		IntercoreModuleFS::Message *icc_modulefs_message_core0;
		IntercoreModuleFS::Message *icc_modulefs_message_core1;
		ConcurrentBuffer *console_a7_0_buff;
		ConcurrentBuffer *console_a7_1_buff;
		ConcurrentBuffer *console_m4_buff;
		ConcurrentBuffer *console_cdc_buff;
		volatile uint8_t *cdc_arm_flag; // New: A7->M4 arm signal for CDC scan
	};

	static Ptrs ptrs;
};

} // namespace MetaModule
