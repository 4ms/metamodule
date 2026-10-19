// MetaModule MP2 ("pro") Cortex-M33 firmware -- bring-up.
//
// Loaded and started by the A35 (see core_a35/main.cc), which has already initialized the
// HSEM and IPCC1 peripherals and published the shared objects (shared_index.hh).
// On MP1 the M4 runs patch storage, controls, USB, and MIDI; on MP2 the M33 takes that role.
//
// So far:
// - storage: MP1's PatchStorage answers the A35's FileStorageProxy requests (storage_messages.hh).
//   Volumes: SD card, NOR flash (a RAM-backed stub until there's an OSPI driver), and USB
//   (always unmounted until there's a USB host driver).
// - bring-up test: respond to the A35's ping messages, woken by the IPCC1 RX-occupied interrupt

#include "console.hh"
#include "core_intercom/shared_memory.hh"
#include "drivers/cache.hh"
#include "drivers/inter_core_comm.hh"
#include "drivers/ipcc.hh"
#include "drivers/stm32xx.h"
#include "fs/fatfs/sd_host.hh"
#include "core_intercom/shared_index.hh"
#include "storage_messages.hh"
#include <cstdio>

using namespace MetaModule;

// This core's view of MP1's shared-pointer table (see shared_index.hh). Here it's per-core,
// not shared: only the pointers this core uses are set.
MetaModule::SharedMemoryS::Ptrs MetaModule::SharedMemoryS::ptrs{};

namespace
{
using IPC = mdrivlib::InterCoreComm<mdrivlib::ICCRoleType::Responder, BringupIPC::Message, BringupIPC::Channel>;
using IPCChan = mdrivlib::IPCC_<2>::HalfDuplexMode<BringupIPC::Channel>;

volatile bool request_pending = false;

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
	// Bring-up IPC test
	//
	static IPC ipc{*index.bringup_message};

	// The A35's request holds the channel's RX-occupied flag high until we reply, so the ISR
	// masks the channel; the main loop unmasks it again after replying.
	IPCChan::enable_chan_isr(1, 0, [] {
		IPCChan::disable_chan_isr();
		request_pending = true;
	});

	uint32_t num_requests = 0;
	uint32_t last_print = HAL_GetTick();
	bool sd_was_mounted = sd.is_mounted();

	while (true) {
		sd.process();
		storage.process();

		if (sd.is_mounted() != sd_was_mounted) {
			sd_was_mounted = sd.is_mounted();
			printf("M33: SD card %s\n", sd_was_mounted ? "mounted" : "unmounted");
		}

		if (request_pending) {
			request_pending = false;

			auto msg = ipc.get_new_message();
			if (msg.seq) {
				num_requests++;
				if (!ipc.send_message({.seq = msg.seq, .value = msg.seq * 2}))
					printf("M33: reply FAILED (not my turn)\n");
			}
			IPCChan::enable_chan_isr();
		}

		auto now = HAL_GetTick();
		if (now - last_print >= 10000) {
			last_print = now;
			printf("M33: uptime %lu s, answered %lu pings\n", (unsigned long)(now / 1000), (unsigned long)num_requests);
		}
	}
}
