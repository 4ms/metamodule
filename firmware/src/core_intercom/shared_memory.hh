#pragma once
#include "conf/ramdisk_conf.hh"
#include "console/concurrent_buffer.hh"
#include "intercore_modulefs_message.hh"
#include "usb/dev_drive_block.hh"
#include "usb/usb_connection_status_block.hh"
#include <array>

namespace MetaModule
{
//fwd declare to reduce dependencies
struct IntercoreStorageMessage;
struct DeviceSettingsMessage;
struct ParamBlock; // params/param_block.hh: depends on the panel's conf
using DoubleBufParamBlock = std::array<ParamBlock, 2>;

//TODO: Move this structure to static_buffers.hh and declare static inline ptrs there too
struct SharedMemoryS {
	struct Ptrs {
		DoubleBufParamBlock *param_block;
		RamDrive *ramdrive;
		IntercoreStorageMessage *icc_message;
		IntercoreModuleFS::IccMessage *icc_modulefs_message_core0;
		IntercoreModuleFS::IccMessage *icc_modulefs_message_core1;
		ConcurrentBuffer *console_a7_0_buff;
		ConcurrentBuffer *console_a7_1_buff;
		ConcurrentBuffer *console_m4_buff;
		uint8_t *uvc_framebuffer;
		DeviceSettingsMessage *icc_device_settings_message;
		UsbConnectionStatusBlock *usb_connection_status;
		DevDriveBlock *dev_drive_msgs;
	};

	static Ptrs ptrs;
};

} // namespace MetaModule
