/* Bare-metal shim for linux/compat.h — minimal subset needed by xHCI */
#ifndef _LINUX_COMPAT_H_
#define _LINUX_COMPAT_H_

#include <stdlib.h>
#include <string.h>
#include <linux/types.h>
#include <linux/kernel.h>

/* GFP flags (GFP_KERNEL etc. are in linux/slab.h) */
#include <linux/slab.h>
#define __GFP_ZERO	((__force gfp_t)0x8000u)

#define PAGE_SIZE	4096

/* Timer / scheduling stubs */
#ifndef schedule
#define schedule()	do {} while (0)
#endif

#endif
