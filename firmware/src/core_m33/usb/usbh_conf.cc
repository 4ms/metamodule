// The USB host library's low-level driver (USBH_LL_*), on lib/xhci: MP2's version of MP1's
// src/usb/usbh_conf.cc.
//
// lib/xhci enumerates the devices (including through hubs). UsbHostManager attaches a library
// handle to one of them (its HCD_HandleTypeDef's dev: see hcd_xhci.hh) and tells the library it's
// connected. The library then enumerates it again through these functions, as if it were alone on
// the bus: its control requests go to the device's endpoint 0 (except Set Address and Set
// Configuration, which lib/xhci did already), and its bulk and interrupt transfers are lib/xhci's
// non-blocking transfers.
//
// Nothing here runs in an interrupt (lib/xhci is polled), so GetURBState() handles the controller's
// events: the library's blocking calls (e.g. USBH_MSC_Read()) poll it.

#include "drivers/stm32xx.h"
#include "hcd_xhci.hh"
#include "usbh_core.h"
#include "usbh_msc.h"
#include "xhci_platform.h"
#include <algorithm>
#include <bit>
#include <cerrno>
#include <cstring>

namespace
{

using Pipe = HCD_HandleTypeDef::Pipe;

HCD_HandleTypeDef &hcd(USBH_HandleTypeDef *phost) {
	return *static_cast<HCD_HandleTypeDef *>(phost->pData);
}

// The library's Timer counts frames (ms)
void update_timer(USBH_HandleTypeDef *phost) {
	USBH_LL_SetTimer(phost, HAL_GetTick());
}

//
// Control transfers
//

USBH_URBStateTypeDef do_control(HCD_HandleTypeDef &h, uint8_t *data, uint32_t &count) {
	count = 0;
	if (!h.dev)
		return USBH_URB_ERROR;

	// lib/xhci did these when it enumerated the device
	constexpr uint8_t StandardDeviceOut = 0x00;
	if (h.setup[0] == StandardDeviceOut &&
		(h.setup[1] == USB_REQ_SET_ADDRESS || h.setup[1] == USB_REQ_SET_CONFIGURATION))
		return USBH_URB_DONE;

	int ret = xhci_host_control(h.dev, h.setup.data(), data);
	if (ret == -EPIPE)
		return USBH_URB_STALL;
	if (ret < 0)
		return USBH_URB_ERROR;
	count = ret;
	return USBH_URB_DONE;
}

void submit_control(HCD_HandleTypeDef &h, Pipe &pipe, uint8_t token, uint8_t *buf, uint16_t length) {
	if (token == USBH_PID_SETUP) {
		std::copy_n(buf, h.setup.size(), h.setup.begin());
		h.data_stage_done = false;
		uint16_t wLength = h.setup[6] | (h.setup[7] << 8);
		uint32_t count = 0;
		h.ctrl_result = wLength ? USBH_URB_DONE : do_control(h, nullptr, count);
		// A stall is the status stage's (the library looks for it there)
		pipe.urb_state = h.ctrl_result == USBH_URB_ERROR ? USBH_URB_ERROR : USBH_URB_DONE;
		pipe.xfer_count = h.setup.size();

	} else if (length > 0 && !h.data_stage_done) {
		h.data_stage_done = true;
		h.ctrl_result = do_control(h, buf, pipe.xfer_count);
		pipe.urb_state = h.ctrl_result;

	} else {
		// Status stage
		pipe.urb_state = h.ctrl_result;
		pipe.xfer_count = 0;
	}
}

//
// Bulk and interrupt transfers
//

// The pipe's DMA buffer, big enough for length bytes
bool reserve_dma_buf(Pipe &pipe, uint32_t length) {
	if (pipe.dma_buf && pipe.dma_size >= length)
		return true;

	// The transfer is one TRB, which can't cross a 64kB boundary: aligning the buffer to its size
	// makes sure
	constexpr uint32_t MaxSize = 64 * 1024;
	auto size = std::max<uint32_t>(std::bit_ceil(length), 1024);
	if (size > MaxSize) {
		printf("USB host: %u-byte transfer is too big\n", (unsigned)length);
		return false;
	}

	xhci_xfer_cancel(&pipe.xfer);
	xhci_platform_free(pipe.dma_buf);
	pipe.dma_buf = static_cast<uint8_t *>(xhci_platform_alloc(size, size));
	pipe.dma_size = pipe.dma_buf ? size : 0;
	return pipe.dma_buf;
}

void submit_xfer(HCD_HandleTypeDef &h, Pipe &pipe, uint8_t *buf, uint16_t length) {
	pipe.busy = false;
	pipe.xfer_count = 0;
	pipe.urb_state = USBH_URB_ERROR;

	if (!h.dev || !reserve_dma_buf(pipe, length))
		return;

	bool is_in = pipe.ep_addr & 0x80;
	if (!is_in && length)
		std::memcpy(pipe.dma_buf, buf, length);
	pipe.buf = buf;

	pipe.xfer.dev = h.dev;
	pipe.xfer.ep_addr = pipe.ep_addr;
	if (xhci_xfer_submit(&pipe.xfer, pipe.dma_buf, length) == 0) {
		pipe.busy = true;
		pipe.urb_state = USBH_URB_IDLE;
	}
}

void finish_xfer(USBH_HandleTypeDef *phost, Pipe &pipe) {
	switch (pipe.xfer.status) {
		case XHCI_XFER_BUSY:
			return;
		case XHCI_XFER_DONE:
			pipe.urb_state = USBH_URB_DONE;
			break;
		case XHCI_XFER_STALL:
			pipe.urb_state = USBH_URB_STALL;
			break;
		default:
			pipe.urb_state = USBH_URB_ERROR;
			break;
	}
	pipe.busy = false;
	pipe.xfer_count = pipe.xfer.actual;

	bool is_in = pipe.ep_addr & 0x80;
	if (is_in && pipe.urb_state == USBH_URB_DONE && pipe.xfer_count)
		std::memcpy(pipe.buf, pipe.dma_buf, pipe.xfer_count);

	// If the device is gone, say so now: the library's blocking calls (e.g. USBH_MSC_Read()) wait
	// for that, not for errors, and the main loop's xhci_host_poll() won't run till they're done
	auto &h = hcd(phost);
	if (pipe.urb_state == USBH_URB_ERROR && h.dev && !xhci_host_device_present(h.dev)) {
		h.dev = nullptr;
		USBH_LL_Disconnect(phost);
	}
}

void cancel_xfer(Pipe &pipe) {
	if (pipe.busy) {
		xhci_xfer_cancel(&pipe.xfer);
		pipe.busy = false;
	}
}

} // namespace

/*******************************************************************************
					   LL Driver Interface (USB Host Library --> HCD)
*******************************************************************************/

USBH_StatusTypeDef USBH_LL_Init(USBH_HandleTypeDef *phost) {
	update_timer(phost);
	return USBH_OK;
}

USBH_StatusTypeDef USBH_LL_DeInit(USBH_HandleTypeDef *phost) {
	return USBH_OK;
}

// UsbHostManager starts and stops the controller
USBH_StatusTypeDef USBH_LL_Start(USBH_HandleTypeDef *phost) {
	return USBH_OK;
}

USBH_StatusTypeDef USBH_LL_Stop(USBH_HandleTypeDef *phost) {
	return USBH_OK;
}

USBH_SpeedTypeDef USBH_LL_GetSpeed(USBH_HandleTypeDef *phost) {
	auto *dev = hcd(phost).dev;
	switch (dev ? xhci_host_device_speed(dev) : 0) {
		case 1:
			return USBH_SPEED_LOW;
		case 2:
			return USBH_SPEED_FULL;
		default:
			return USBH_SPEED_HIGH;
	}
}

// lib/xhci reset the port (and enumerated the device) already
USBH_StatusTypeDef USBH_LL_ResetPort(USBH_HandleTypeDef *phost) {
	USBH_LL_PortEnabled(phost);
	return USBH_OK;
}

uint32_t USBH_LL_GetLastXferSize(USBH_HandleTypeDef *phost, uint8_t pipe) {
	return hcd(phost).pipes[pipe].xfer_count;
}

// The library opens a pipe again to change it (e.g. the control pipes' max packet size)
USBH_StatusTypeDef USBH_LL_OpenPipe(USBH_HandleTypeDef *phost,
									uint8_t pipe_num,
									uint8_t epnum,
									uint8_t dev_address,
									uint8_t speed,
									uint8_t ep_type,
									uint16_t mps) {
	auto &pipe = hcd(phost).pipes[pipe_num];
	cancel_xfer(pipe);
	pipe.ep_addr = epnum;
	pipe.ep_type = ep_type;
	pipe.mps = mps;
	pipe.urb_state = USBH_URB_IDLE;
	pipe.xfer_count = 0;
	return USBH_OK;
}

USBH_StatusTypeDef USBH_LL_ClosePipe(USBH_HandleTypeDef *phost, uint8_t pipe_num) {
	cancel_xfer(hcd(phost).pipes[pipe_num]);
	return USBH_OK;
}

USBH_StatusTypeDef USBH_LL_SubmitURB(USBH_HandleTypeDef *phost,
									 uint8_t pipe_num,
									 uint8_t direction,
									 uint8_t ep_type,
									 uint8_t token,
									 uint8_t *pbuff,
									 uint16_t length,
									 uint8_t do_ping) {
	update_timer(phost);
	auto &h = hcd(phost);
	auto &pipe = h.pipes[pipe_num];

	if (ep_type == USBH_EP_CONTROL)
		submit_control(h, pipe, token, pbuff, length);
	else if (ep_type == USBH_EP_BULK || ep_type == USBH_EP_INTERRUPT)
		submit_xfer(h, pipe, pbuff, length);
	else
		pipe.urb_state = USBH_URB_ERROR; // no isochronous transfers

	return USBH_OK;
}

USBH_URBStateTypeDef USBH_LL_GetURBState(USBH_HandleTypeDef *phost, uint8_t pipe_num) {
	update_timer(phost);
	auto &pipe = hcd(phost).pipes[pipe_num];
	if (pipe.busy) {
		xhci_host_process_events();
		finish_xfer(phost, pipe);
	}
	return pipe.urb_state;
}

// UsbHostManager drives VBUS
USBH_StatusTypeDef USBH_LL_DriverVBUS(USBH_HandleTypeDef *phost, uint8_t state) {
	return USBH_OK;
}

// The controller keeps the data toggles
USBH_StatusTypeDef USBH_LL_SetToggle(USBH_HandleTypeDef *phost, uint8_t pipe, uint8_t toggle) {
	return USBH_OK;
}

uint8_t USBH_LL_GetToggle(USBH_HandleTypeDef *phost, uint8_t pipe) {
	return 0;
}

void USBH_Delay(uint32_t Delay) {
	HAL_Delay(Delay);
}

// Same as MP1's
void *msc_malloc(size_t sz) {
	static MSC_HandleTypeDef hmsc;
	if (sz == sizeof(MSC_HandleTypeDef))
		return &hmsc;
	else
		return nullptr;
}

void msc_free(void *) {
}
