/*
 * xhci_host.h — xHCI host API (from stm32mp2-baremetal's xhci_baremetal.h)
 */

#ifndef XHCI_BAREMETAL_H
#define XHCI_BAREMETAL_H

#include <stdbool.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

struct xhci_ctrl;
struct usb_device;

/*
 * xhci_host_init - Initialize xHCI host controller
 *
 * Call after dwc3_baremetal_init(DWC3_DR_MODE_HOST, ...) has configured
 * the DWC3 in host mode. Powers on ports and allocates the root hub.
 *
 * @dwc3_base: DWC3 MMIO base address (e.g. 0x48300000)
 * Returns 0 on success, negative on error.
 */
int xhci_host_init(uintptr_t dwc3_base);

/*
 * xhci_host_poll - Poll for port changes and enumerate new devices
 *
 * Call periodically from main loop. On new device connection,
 * resets the port, assigns an address, reads descriptors, and
 * sets configuration.
 *
 * Returns pointer to newly enumerated usb_device, or NULL if no change.
 */
struct usb_device *xhci_host_poll(void);

/*
 * xhci_device_connected - Check if a device is currently attached
 */
bool xhci_device_connected(void);

/*
 * xhci_device_is_hub - Check if a device is a USB hub
 */
bool xhci_device_is_hub(struct usb_device *dev);

/*
 * xhci_host_get_ctrl - Get the xHCI controller instance
 */
struct xhci_ctrl *xhci_host_get_ctrl(void);

/*
 * xhci_host_shutdown - Stop and clean up xHCI
 */
void xhci_host_shutdown(void);

/* What an enumerated device says about itself */
struct xhci_host_device_info {
	uint16_t vid;
	uint16_t pid;
	uint8_t device_class;
	uint8_t speed; /* 1 = low, 2 = full, 3 = high, 5 = super */
	uint8_t devnum;
	uint8_t depth; /* 0: on a root port; 1: behind one hub, ... */
	char manufacturer[32];
	char product[32];
};

/*
 * xhci_host_get_device_info - Describe an enumerated device (from xhci_host_poll())
 */
void xhci_host_get_device_info(struct usb_device *dev, struct xhci_host_device_info *info);

/*
 * xhci_host_set_disconnect_callback - Called for each device that's gone (including the devices
 * behind a hub that's gone), from xhci_host_poll(), just before the device is freed
 */
void xhci_host_set_disconnect_callback(void (*callback)(struct usb_device *dev));

/*
 * xhci_host_find_interface - The number of the device's first interface (in its default setting)
 * with this class and subclass, or -1 if it has none
 */
int xhci_host_find_interface(struct usb_device *dev, uint8_t intf_class, uint8_t intf_subclass);

/* The device's speed, as for xhci_host_device_info */
uint8_t xhci_host_device_speed(struct usb_device *dev);

/*
 * xhci_host_device_present - Whether the device is still connected (for when its transfers fail
 * between xhci_host_poll() calls). Asks each hub on the way (blocking).
 */
bool xhci_host_device_present(struct usb_device *dev);

/*
 * xhci_host_control - A control transfer on endpoint 0 (blocking). setup is the 8-byte request; the
 * data stage is its wLength bytes of data. Returns the number of bytes transferred, -EPIPE if the
 * device stalled, or another negative errno.
 */
int xhci_host_control(struct usb_device *dev, const uint8_t setup[8], void *data);

/*
 * Non-blocking bulk and interrupt transfers: one transfer at a time per endpoint, each described by
 * an xhci_xfer that stays valid until it's no longer busy or it's cancelled.
 * xhci_host_process_events() completes them (as do the blocking calls, which process the events
 * that arrive while they wait).
 */
enum xhci_xfer_status {
	XHCI_XFER_IDLE,
	XHCI_XFER_BUSY,
	XHCI_XFER_DONE,
	XHCI_XFER_STALL,
	XHCI_XFER_ERROR,
};

struct xhci_xfer {
	/* Set by the caller */
	struct usb_device *dev;
	uint8_t ep_addr; /* endpoint number, | 0x80 for IN */

	/* Set by the library */
	enum xhci_xfer_status status;
	int actual; /* bytes transferred, when done */

	/* Private */
	int length;
	int slot_id;
	int ep_index;
	uint64_t trb;
	struct xhci_xfer *next;
};

/*
 * xhci_xfer_submit - Start a transfer. buf must be DMA-safe (see xhci_platform.h), and mustn't
 * cross a 64kB boundary. Cancels the xfer's transfer if it's busy, and first recovers the endpoint
 * if a transfer halted it (e.g. stalled). Returns 0 or a negative errno.
 */
int xhci_xfer_submit(struct xhci_xfer *xfer, void *buf, int length);

/*
 * xhci_xfer_cancel - Stop the xfer's transfer, if it's busy. (Its status becomes IDLE.)
 */
void xhci_xfer_cancel(struct xhci_xfer *xfer);

/*
 * xhci_host_process_events - Handle the controller's events (completing transfers). Call often.
 */
void xhci_host_process_events(void);

#ifdef __cplusplus
}
#endif

#endif /* XHCI_BAREMETAL_H */
