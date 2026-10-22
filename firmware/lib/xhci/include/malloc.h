#ifndef _MALLOC_H
#define _MALLOC_H

#include <stdlib.h>
#include <string.h>
#include <xhci_platform.h>

/* MetaModule: all allocations come from the platform's DMA-safe memory (see xhci_platform.h) */
static inline void *xhci_calloc(size_t n, size_t size)
{
	void *p = xhci_platform_alloc(8, n * size);
	if (p)
		memset(p, 0, n * size);
	return p;
}

#define memalign(align, size)		xhci_platform_alloc((align), (size))
#define malloc(size)			xhci_platform_alloc(8, (size))
#define calloc(n, size)			xhci_calloc((n), (size))
#define free(ptr)			xhci_platform_free(ptr)

#define kmalloc_array(n, size, flags)	calloc((n), (size))

#endif /* _MALLOC_H */
