#pragma once
#include "core_intercom/intercore_devicesettings_message.hh"
#include "core_intercom/intercore_types.hh"
#include "param_block.hh"
#include "usb/usb_connection_status_block.hh"
#include <cstddef>
#include <cstdint>

// Objects shared between the A35 and the M33.
//
// The A35 creates them in .sharedmem (DDR, non-cacheable on both cores) and publishes pointers
// to them in SharedIndex, at the start of the shared region, before starting the M33. This is
// MP2's version of MP1's SharedMemoryS::ptrs, which holds raw pointers and so can't cross a
// 64-bit/32-bit core boundary. Each core can fill in its own SharedMemoryS::ptrs from this.

namespace MetaModule
{

struct IntercoreStorageMessage;
struct DevDriveBlock;

// Crosses the core boundary: no raw pointers (8 bytes on the A35, 4 on the M33).
// Both cores see shared DDR at the same addresses, so InterCoreSharedRegion::base stays 0.
struct SharedIndex {
	static constexpr uint32_t ValidMagic = 0x5EA4ED01;
	uint32_t magic; // set by the A35 once the pointers below are valid

	InterCorePtr32<IntercoreStorageMessage> storage_message; // FileStorageProxy (A35) <-> PatchStorage (M33)
	InterCorePtr32<DoubleBufParamBlock> param_blocks;		 // Controls (M33) -> audio (A35)
	InterCorePtr32<DevDriveBlock> dev_drive_msgs;			 // USB device (M33) <-> developer drive (A35)
	InterCorePtr32<DeviceSettingsMessage> device_settings_message;		// USB settings: GUI (A35) -> M33
	InterCorePtr32<UsbConnectionStatusBlock> usb_connection_status; // USB status: M33 -> GUI (A35)

	// Frames of each param block the audio stream uses (0 until it's running): A35 -> M33. The
	// M33 fills in only these frames' MIDI (see core_m33/panel_controls.hh).
	volatile uint32_t audio_block_size;
};
static_assert(sizeof(SharedIndex) == 28);

// Both cores use these directly, so they must have the same layout on the A35 and the M33
static_assert(sizeof(DeviceSettingsMessage) == 12);
static_assert(sizeof(UsbConnectionStatusBlock) == 1360);

// Both cores use ParamBlock directly, so it must have the same layout on the 64-bit A35 and the
// 32-bit M33 (no pointers, size_t, or long). If these fail after a change to Params or MetaParams,
// check that both cores agree before updating the numbers.
static_assert(sizeof(Params) == PanelDef::NumPot * sizeof(float) + 12);
static_assert(sizeof(MetaParams) == 76);
static_assert(offsetof(ParamBlock, metaparams) == sizeof(Params) * StreamConf::Audio::MaxBlockSize);
static_assert(alignof(ParamBlock) == 64);

// At the start of the shared region (SHAREDMEM_ADDR), where both cores see it.
// Deliberately not a defined object: InterCorePtr32 has a default member initializer, so
// a defined object would get a static constructor on *each* core, and the M33's would wipe
// the pointers the A35 published. The A35 sets every field explicitly before starting the M33.
inline SharedIndex &shared_index() {
	return *reinterpret_cast<SharedIndex *>(SHAREDMEM_ADDR);
}

} // namespace MetaModule
