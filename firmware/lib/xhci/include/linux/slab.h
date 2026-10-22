#ifndef _LINUX_SLAB_H
#define _LINUX_SLAB_H

#include <malloc.h>

/* GFP flags — ignored in bare-metal */
#define GFP_KERNEL	0
#define GFP_ATOMIC	0

#define kzalloc(size, flags)	calloc(1, size)
#define kmalloc(size, flags)	malloc(size)
#define kfree(ptr)		free(ptr)

#endif /* _LINUX_SLAB_H */
