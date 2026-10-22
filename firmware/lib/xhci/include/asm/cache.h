/* Bare-metal shim for asm/cache.h */
#ifndef _ASM_CACHE_H
#define _ASM_CACHE_H

#include <cpu_func.h>

#ifndef ARCH_DMA_MINALIGN
#define ARCH_DMA_MINALIGN	64
#endif

#ifndef CONFIG_SYS_CACHELINE_SIZE
#define CONFIG_SYS_CACHELINE_SIZE	64
#endif

#endif
