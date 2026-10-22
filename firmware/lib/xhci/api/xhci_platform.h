/*
 * xhci_platform.h -- what this library needs from the firmware that uses it
 */
#ifndef XHCI_PLATFORM_H
#define XHCI_PLATFORM_H

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Memory the controller can DMA to and from without cache maintenance (e.g. not cached), at the
 * same address for the CPU and the controller. All of the library's allocations come from here,
 * including the ones the CPU only uses (the U-Boot code frees both kinds with free()). */
void *xhci_platform_alloc(size_t align, size_t size);
void xhci_platform_free(void *ptr);

/* A buffer the controller can DMA len bytes to or from, for the transfer buffer buf: buf itself if
 * it's DMA-safe, or else a bounce buffer (the library copies the data in and out). NULL if len is
 * too big to bounce. Only one transfer is in flight at a time. */
void *xhci_platform_dma_buffer(void *buf, size_t len);

/* Busy-wait delays, and milliseconds since base */
void udelay(unsigned int us);
void mdelay(unsigned int ms);
unsigned long get_timer(unsigned long base);

#ifdef __cplusplus
}
#endif

#endif /* XHCI_PLATFORM_H */
