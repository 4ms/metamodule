#pragma once
#include "usbh_core.h"
#include "xhci_host.h"
#include <array>
#include <cstdint>

// The USB host library's low-level driver on lib/xhci (usbh_conf.cc) keeps one of these per library
// handle (as its pData): the lib/xhci device that handle is attached to, and the state of its
// pipes. It stands in for the HAL's host controller handle, which the library's users on MP1 name
// (MSCOps reads Init.dma_enable).
struct HCD_HandleTypeDef {
	struct {
		uint32_t dma_enable = 0;
	} Init;

	usb_device *dev = nullptr; // nullptr: not attached, or the device is gone

	struct Pipe {
		uint8_t ep_addr = 0; // with 0x80 for IN
		uint8_t ep_type = 0; // USBH_EP_CONTROL, ...
		uint16_t mps = 0;

		USBH_URBStateTypeDef urb_state = USBH_URB_IDLE;
		uint32_t xfer_count = 0;

		// Bulk and interrupt transfers
		xhci_xfer xfer{};
		bool busy = false;		   // a transfer is in flight, its result not yet in urb_state
		uint8_t *buf = nullptr;	   // the library's buffer (IN data is copied here)
		uint8_t *dma_buf = nullptr; // xfer's buffer (from xhci_platform_alloc(), kept for next time)
		uint32_t dma_size = 0;
	};
	std::array<Pipe, USBH_MAX_PIPES_NBR> pipes{};

	// The control transfer in progress: lib/xhci does a whole control transfer at once, so it
	// happens at its SETUP stage (no data stage) or its data stage, and the later stages report it.
	std::array<uint8_t, 8> setup{};
	bool data_stage_done = false;
	USBH_URBStateTypeDef ctrl_result = USBH_URB_IDLE;
};
