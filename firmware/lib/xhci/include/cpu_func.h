#ifndef _CPU_FUNC_H
#define _CPU_FUNC_H

#include <stdint.h>

#define CONFIG_SYS_CACHELINE_SIZE	64

/* MetaModule: everything the controller reads or writes is in memory the platform keeps out of
 * the data cache (xhci_platform_alloc(), and the bounce buffers in xhci_ctrl_tx()/xhci_bulk_tx()),
 * so there's nothing to clean or invalidate. */

static inline void flush_dcache_range(uintptr_t start, uintptr_t end)
{
	(void)start;
	(void)end;
}

static inline void invalidate_dcache_range(uintptr_t start, uintptr_t end)
{
	(void)start;
	(void)end;
}

#endif /* _CPU_FUNC_H */
