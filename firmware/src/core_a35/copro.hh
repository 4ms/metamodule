#pragma once
#include "console.hh"
#include "console/uart_log.hh"
#include "core_intercom/shared_index.hh"
#include "drivers/copro_control.hh"
#include "drivers/hsem.hh"
#include "drivers/ipcc.hh"
#include "drivers/risaf.hh"
#include "drivers/usb3dr.hh"
#include "ld.h"
#include "static_buffers.hh"
#include <cstdio>

extern "C" const uint8_t m33_firmware[];	 // m33_firmware.S
extern "C" const uint8_t m33_firmware_end[]; // m33_firmware.S

namespace MetaModule
{

// Loads the M33 firmware (embedded in ours) and starts it, after giving it the memory and the
// peripherals it shares with us.
inline void start_m33() {
	// Park the M33 before (re)initializing the peripherals it uses
	mdrivlib::CoproController::reset();
	mdrivlib::HWSemaphoreGlobalBase::init_peripheral();
	mdrivlib::IPCC_<1>::init_peripheral();
	A35Console::use_hsem_lock();

	// USB runs on the M33: its DMA uses the M33's compartment ID (CID2), so it can reach the
	// M33's memory
	mdrivlib::Usb3DR::init_rif(2);

	// Shared memory: open it to the M33 in the DDR firewall, create the shared objects in
	// .sharedmem, and publish pointers to them in the index the M33 reads
	using namespace mdrivlib::RISAF;
	constexpr unsigned SharedMemRegionIndex = 10;
	if (!add_ddr_region(
			SharedMemRegionIndex, SHAREDMEM, SHAREDMEM + SHAREDMEM_SZ - 1, CID_A35 | CID_M33, CID_A35 | CID_M33, true))
		printf("Shared memory: RISAF4 is locked, can't open it to the M33!\n");

	StaticBuffers::storage_message = {};
	StaticBuffers::dev_drive_block.reset();

	auto &index = shared_index();
	index.storage_message = &StaticBuffers::storage_message;
	index.param_blocks = &StaticBuffers::param_blocks;
	index.dev_drive_msgs = &StaticBuffers::dev_drive_block;
	index.device_settings_message = &StaticBuffers::icc_device_settings_message;
	index.usb_connection_status = &StaticBuffers::usb_connection_status;
	index.console_buffers = StaticBuffers::console_buffers.data();
	index.magic = SharedIndex::ValidMagic;

	if (M33_REGION >= mdrivlib::RISAF::DDRBase) {
		// TF-A's DDR region only allows CID0/CID1: open the M33's region to it (CID2)
		constexpr unsigned M33RegionIndex = 11;
		if (!add_ddr_region(M33RegionIndex, M33_REGION, M33_REGION_END - 1, CID_A35 | CID_M33, CID_A35 | CID_M33, true))
			printf("M33: RISAF4 is locked, can't open DDR to the M33!\n");
	}

	auto size = size_t(m33_firmware_end - m33_firmware);
	printf("M33: loading %zu bytes to 0x%08x and starting\n", size, unsigned(M33_REGION));
	mdrivlib::CoproController::load_and_start({m33_firmware, size}, M33_REGION);

	using mdrivlib::CoproController;
	auto reset_us = CoproController::wait_for_breadcrumb(M33_REGION, 0, CoproController::BreadcrumbResetRan, 100);
	auto main_us = CoproController::wait_for_breadcrumb(M33_REGION, 1, CoproController::BreadcrumbReachedMain, 1000);
	if (reset_us < 0)
		printf("M33: reset handler DID NOT RUN\n");
	else if (main_us < 0)
		printf("M33: reset handler ran, main() NOT REACHED\n");
	else {
		// The M33 sends the console buffers on (to the UART, or the USB console). If it's not
		// running, keep writing to the UART.
		UartLog::use_buffer(&StaticBuffers::console_buffers[0]);
	}
}

} // namespace MetaModule
