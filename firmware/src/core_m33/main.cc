// MetaModule MP2 ("pro") Cortex-M33 firmware -- bring-up.
//
// Loaded and started by the A35 (see core_a35/main.cc), which has already initialized the
// HSEM and IPCC1 peripherals and published the shared objects (shared_index.hh).
// On MP1 the M4 runs patch storage, controls, USB, and MIDI; on MP2 the M33 takes that role.
//
// So far:
// - controls: the nav encoder and Back button, for the GUI, and USB MIDI (host or device) and DIN5
//   MIDI to and from the patch (panel_controls.hh). The other controls are read, and reported on the console.
// - storage: MP1's PatchStorage answers the A35's FileStorageProxy requests (storage_messages.hh).
//   Volumes: SD card, NOR flash, and USB drive.
// - USB: MP1's UsbManager, with the FUSB302 deciding the role. Takes the USB settings from the
//   GUI, and publishes the connection status for it. As a device: MIDI + console
//   composite on the USB3DR (usbd_conf.cc). As a host: MIDI devices and USB drives, including
//   through a hub (usb/usb_host_manager.hh).
// - console: as on MP1, all cores write their console output to buffers, which we send to the
//   UART (console_drain.hh), or to the USB console when a computer connects to it.

#include "console.hh"
#include "console/uart_log.hh"
#include "console_drain.hh"
#include "core_intercom/shared_i2c_lock.hh"
#include "core_intercom/shared_index.hh"
#include "core_intercom/shared_memory.hh"
#include "drivers/cache.hh"
#include "drivers/stm32xx.h"
#include "fs/fatfs/sd_host.hh"
#include "panel_controls.hh"
#include "storage_messages.hh"
#include "usb/device_settings_messages.hh"
#include "usb/usb_manager.hh"
#include <cstdio>

using namespace MetaModule;

// This core's view of MP1's shared-pointer table (see shared_index.hh). Here it's per-core,
// not shared: only the pointers this core uses are set.
MetaModule::SharedMemoryS::Ptrs MetaModule::SharedMemoryS::ptrs{};

namespace
{
// Not used yet (see conf/ramdisk_conf.hh), but PatchStorage needs one
RamDrive ramdrive;

} // namespace

int main() {
	// The MPU is already set up (system_init.cc): DCACHE caches the M33's own memory, not shared memory.
	// It speeds up code and data in DDR ~20-30x.
	bool dcache_ok = mdrivlib::SystemCache::enable_dcache();

	// Line-buffered, so lines from the two cores don't interleave (see write.cc)
	setvbuf(stdout, nullptr, _IOLBF, 256);

	printf("M33: started. DCACHE %s\n", dcache_ok ? "on" : "enable FAILED");

	// The A35 publishes the shared objects before starting us
	auto &index = shared_index();
	if (index.magic != SharedIndex::ValidMagic) {
		printf("M33: shared memory index not valid! magic = %08lx\n", (unsigned long)index.magic);
		while (true)
			;
	}
	SharedMemoryS::ptrs.ramdrive = &ramdrive;
	SharedMemoryS::ptrs.icc_message = index.storage_message.get();
	SharedMemoryS::ptrs.dev_drive_msgs = index.dev_drive_msgs.get();
	SharedMemoryS::ptrs.icc_device_settings_message = index.device_settings_message.get();
	SharedMemoryS::ptrs.usb_connection_status = index.usb_connection_status.get();

	//
	// Console: every core's printf() goes into its buffer (the A35's, once we're running), and we
	// send them on to the UART, or USB (UsbSerialDevice)
	//
	auto *console_buffers = index.console_buffers.get();
	std::array<ConcurrentBuffer *, NumConsoleBuffers> console_buffer_ptrs{
		&console_buffers[0], &console_buffers[1], &console_buffers[2]};
	UartLog::use_buffer(console_buffer_ptrs[2]);
	static ConsoleDrain console_drain{console_buffer_ptrs};

	//
	// Controls
	//
	static PanelControls controls{*index.param_blocks.get()};
	controls.start();

	//
	// USB
	//
	// The FUSB302 is on I2C4, which the A35 also uses (codec): hold the bus whenever UsbManager may
	// use it. (Constructing it initializes the I2C peripheral.)
	auto &usb = [&]() -> UsbManager & {
		SharedI2CGuard i2c;
		static UsbManager usb{console_buffer_ptrs, *SharedMemoryS::ptrs.dev_drive_msgs};
		usb.start();
		return usb;
	}();
	// USB MIDI <-> the patch
	controls.start_midi(usb.get_midi_host(), usb.get_midi_device());

	//
	// Storage
	//
#ifdef MP2_TEST_CARRIER
	// Drive the common side of the devboard slot's detect switch low before the SD driver reads it
	mdrivlib::Pin sd_detect_common{SDCardDetectCommonPin, mdrivlib::PinMode::Output};
	sd_detect_common.low();
#endif
	SDCardHost sd;

	// Give the SD card time to mount, so the first patch scan includes it
	for (auto start = HAL_GetTick(); HAL_GetTick() - start < 500;) {
		sd.process();
		console_drain.process();
	}
	printf("M33: SD card %s\n", sd.is_mounted() ? "mounted" : "not mounted");

	auto start = HAL_GetTick();
	static StorageMessages storage{usb.get_msc_fileio(), sd.get_fileio(), *SharedMemoryS::ptrs.icc_message};
	// The first scan of the volumes can be slow, so do it before the A35 makes requests
	storage.process();
	printf("M33: patch storage ready (%lu ms)\n", (unsigned long)(HAL_GetTick() - start));

	// USB settings from the GUI, and the connection status for it (same as MP1's M4 main loop)
	static DeviceSettingsMessages device_settings{SharedMemoryS::ptrs.icc_device_settings_message};
	UsbConnection last_published_conn = UsbConnection::None;
	uint32_t last_published_info_seq = usb.get_device_info_seq();

	bool sd_was_mounted = sd.is_mounted();

	while (true) {
		console_drain.process();
		controls.process();
		sd.process();
		storage.process();
		{
			SharedI2CGuard i2c;
			usb.process();
			controls.update_jack_sense(usb.i2c());

			auto ds_result = device_settings.process();
			if (ds_result.has_mode_change)
				usb.set_device_mode(ds_result.mode);
			if (ds_result.has_role_change)
				usb.set_role_mode(ds_result.role);
		}
		// The USB host's work doesn't use the I2C bus (see UsbHostManager::process())
		UsbHostManager::run();

		auto conn = usb.get_connection_status();
		controls.set_usb_connection(conn);
		auto info_seq = usb.get_device_info_seq();
		if (conn != last_published_conn || info_seq != last_published_info_seq) {
			last_published_conn = conn;
			last_published_info_seq = info_seq;
			SharedMemoryS::ptrs.usb_connection_status->publish(usb.get_status());
		}

		if (sd.is_mounted() != sd_was_mounted) {
			sd_was_mounted = sd.is_mounted();
			printf("M33: SD card %s\n", sd_was_mounted ? "mounted" : "unmounted");
		}
	}
}
