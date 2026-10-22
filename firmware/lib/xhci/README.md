# xhci

An xHCI USB host controller driver, for the STM32MP25's USB3DR (Synopsys DWC3) in host mode.

## Where it's from

- `src/xhci.c`, `src/xhci-mem.c`, `src/xhci-ring.c`, `include/usb/xhci.h`, `include/usb_defs.h`:
  U-Boot's xHCI driver (`drivers/usb/host/xhci*.c`), as ported to bare metal (non-driver-model)
  in [stm32mp2-baremetal](https://github.com/danngreen/stm32mp2-baremetal) `usb-drd/xhci`.
  **License: GPL-2.0+** (see the SPDX headers, and `gpl-2.0.txt`), which allows MetaModule to use
  them under GPL-3.0.
- `src/xhci_host.c`, `api/xhci_host.h`: stm32mp2-baremetal's `xhci_baremetal.c/h`: host init,
  port polling, enumeration, and hubs.
- `include/` (other than the two U-Boot headers above): stm32mp2-baremetal's stand-ins for the
  U-Boot and Linux headers the driver includes, and `include/usb_ch9.h`, written for MetaModule
  in place of `<linux/usb/ch9.h>` (which is GPL-2.0 only).

## MetaModule changes

- Runs on a 32-bit core (the Cortex-M33): `u32` is `unsigned int` as in Linux, `BITS_PER_LONG`
  follows the target, and `xhci_readl()`/`xhci_writel()` take `void *` (the register structs mix
  `uint32_t` and `__le32`, which differ on 32-bit Arm).
- Memory: every allocation comes from the platform (`api/xhci_platform.h`), which gives memory
  the controller can DMA without cache maintenance, so the cache functions are no-ops. Transfer
  buffers that aren't DMA-safe go through the platform's bounce buffer (`xhci_ctrl_tx()` and
  `xhci_bulk_tx()` in `xhci-ring.c`).
- `BUG()`/`BUG_ON()` log instead of halting, and errno values are the C library's.
- Non-blocking bulk and interrupt transfers (`xhci_xfer_*()`, `xhci_host_process_events()`, at
  the end of `xhci-ring.c`). They share the event ring with the blocking transfers and commands:
  while a blocking call waits, `xhci_wait_for_event()` passes the other transfers' events to them.
  A transfer that halts its endpoint (e.g. a stall) is cleared when the next one is submitted.
- Devices come and go one at a time: the device table frees entries, a device unplugged from a hub
  (or a hub, with the devices behind it) is removed and reported
  (`xhci_host_set_disconnect_callback()`), and a reconnect on a port replaces what was there.
- Only an interface's default setting's endpoints are configured (the others' would replace them).
- `xhci_host_get_device_info()`, `xhci_host_find_interface()`, `xhci_host_control()`,
  `xhci_host_device_present()`.

## Using it

The firmware provides the functions in `api/xhci_platform.h`, sets up the DWC3 core in host mode,
and calls the functions in `api/xhci_host.h`. The headers in `include/` are private to the
library (they shadow names like `malloc.h` and `usb.h`). See `src/core_m33/usb/` for MetaModule's.
