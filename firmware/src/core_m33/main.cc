// MetaModule MP2 ("pro") Cortex-M33 firmware -- bring-up.
//
// Loaded and started by the A35 (see core_a35/main.cc), which has already initialized the
// HSEM and IPCC1 peripherals and published the shared objects (shared_index.hh).
// On MP1 the M4 runs patch storage, controls, USB, and MIDI; on MP2 the M33 takes that role.
//
// So far:
// - controls: the control encoder and Back button, for the GUI (panel_controls.hh).
// - storage: MP1's PatchStorage answers the A35's FileStorageProxy requests (storage_messages.hh).
//   Volumes: SD card, NOR flash, and USB
//   (always unmounted until there's a USB host driver).
// - USB device: MP1's UsbDeviceManager (MIDI + console composite) on the USB3DR (usbd_conf.cc).
//   Device mode only, and always on: no host mode or role detection (FUSB302) yet. The console
//   buffers it sends over USB are empty until the console is buffered, like MP1's.

#include "console.hh"
#include "core_intercom/shared_index.hh"
#include "core_intercom/shared_memory.hh"
#include "drivers/cache.hh"
#include "drivers/stm32xx.h"
#include "fs/fatfs/sd_host.hh"
#include "panel_controls.hh"
#include "storage_messages.hh"
#include "usb/usb_device_manager.hh"
#include "usb_link_stats.hh"
#include "util/lockfree_fifo_spsc.hh"
#include <cstdio>
#include <cstring>

using namespace MetaModule;

// This core's view of MP1's shared-pointer table (see shared_index.hh). Here it's per-core,
// not shared: only the pointers this core uses are set.
MetaModule::SharedMemoryS::Ptrs MetaModule::SharedMemoryS::ptrs{};

namespace
{
// USB host isn't ported yet: a drive that's never present
struct NoDiskOps : DiskOps {
	DSTATUS status() override {
		return STA_NOINIT | STA_NODISK;
	}
	DSTATUS initialize() override {
		return STA_NODISK;
	}
	DRESULT read(uint8_t *, uint32_t, uint32_t) override {
		return RES_NOTRDY;
	}
	DRESULT write(const uint8_t *, uint32_t, uint32_t) override {
		return RES_NOTRDY;
	}
	DRESULT ioctl(uint8_t, uint8_t *) override {
		return RES_NOTRDY;
	}
};

// Not used yet (see conf/ramdisk_conf.hh), but PatchStorage needs one
RamDrive ramdrive;

// What MP1's USB CDC console sends to the host. Nothing writes to them yet.
std::array<ConcurrentBuffer, 3> console_buffers;

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

	//
	// Controls
	//
	static PanelControls controls{*index.param_blocks.get()};
	controls.start();

	//
	// Storage
	//
#ifdef MP2_TEST_CARRIER
	// Drive the common side of the devboard slot's detect switch low before the SD driver reads it
	mdrivlib::Pin sd_detect_common{SDCardDetectCommonPin, mdrivlib::PinMode::Output};
	sd_detect_common.low();
#endif
	SDCardHost sd;

	NoDiskOps usb_ops;
	FatFileIO usb{&usb_ops, Volume::USB};

	// Give the SD card time to mount, so the first patch scan includes it
	for (auto start = HAL_GetTick(); HAL_GetTick() - start < 500;)
		sd.process();
	printf("M33: SD card %s\n", sd.is_mounted() ? "mounted" : "not mounted");

	auto start = HAL_GetTick();
	static StorageMessages storage{usb, sd.get_fileio(), *SharedMemoryS::ptrs.icc_message};
	// The first scan of the volumes can be slow, so do it before the A35 makes requests
	storage.process();
	printf("M33: patch storage ready (%lu ms)\n", (unsigned long)(HAL_GetTick() - start));

	//
	// USB
	//
	static UsbDeviceManager usb_device{{&console_buffers[0], &console_buffers[1], &console_buffers[2]},
									   UsbDeviceMode::MidiConsole,
									   *SharedMemoryS::ptrs.dev_drive_msgs};
	// No MIDI routing yet: print what arrives (the callback runs in the USB interrupt)
	static LockFreeFifoSpsc<uint32_t, 64> midi_in;
	usb_device.midi.set_rx_callback([](std::span<uint8_t> packets) {
		for (auto i = 0u; i + 4 <= packets.size(); i += 4) {
			uint32_t packet;
			std::memcpy(&packet, &packets[i], 4);
			midi_in.put(packet);
		}
	});
	usb_device.start();

	bool sd_was_mounted = sd.is_mounted();

	// USB link activity, once a second while it changes
	UsbLinkStats last_usb_stats{};
	uint8_t last_usb_state = 0xFF;
	uint32_t last_usb_report = 0;

	while (true) {
		sd.process();
		storage.process();
		usb_device.process();

		while (auto packet = midi_in.get())
			printf("M33: USB MIDI in: %08lx\n", (unsigned long)__builtin_bswap32(*packet));

		if (HAL_GetTick() - last_usb_report >= 1000) {
			last_usb_report = HAL_GetTick();
			UsbLinkStats now;
			std::memcpy(&now, (const void *)&usb_link_stats, sizeof now);
			auto state = usb_device.USBD_Device.dev_state;
			if (state != last_usb_state || now.resets != last_usb_stats.resets ||
				now.setups != last_usb_stats.setups || now.disconnects != last_usb_stats.disconnects)
			{
				// DSTS: link state in bits 21:18, frame number (counts SOFs) in bits 16:3
				printf("M33: USB: state %u, irqs %lu, resets %lu, setups %lu, suspends %lu, disconnects %lu, "
					   "speed %s, DSTS %08lx\n",
					   state,
					   (unsigned long)now.irqs,
					   (unsigned long)now.resets,
					   (unsigned long)now.setups,
					   (unsigned long)now.suspends,
					   (unsigned long)now.disconnects,
					   now.speed == PCD_SPEED_HIGH ? "high" : "full",
					   (unsigned long)USB3->DEVREGS.DSTS);
			}
			last_usb_stats = now;
			last_usb_state = state;
		}

		if (sd.is_mounted() != sd_was_mounted) {
			sd_was_mounted = sd.is_mounted();
			printf("M33: SD card %s\n", sd_was_mounted ? "mounted" : "unmounted");
		}
	}
}
