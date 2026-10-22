#ifndef _LINUX_KERNEL_H
#define _LINUX_KERNEL_H

#include <stddef.h>
#include <linux/compiler.h>
#include <linux/types.h>

#define ALIGN(x, a)		(((x) + ((a) - 1)) & ~((a) - 1))
#define IS_ALIGNED(x, a)	(((x) & ((a) - 1)) == 0)

#define ARRAY_SIZE(arr)		(sizeof(arr) / sizeof((arr)[0]))

#define DIV_ROUND_UP(n, d)	(((n) + (d) - 1) / (d))
#define ROUND(a, b)		(((a) + (b) - 1) & ~((b) - 1))

#define min(a, b)		((a) < (b) ? (a) : (b))
#define max(a, b)		((a) > (b) ? (a) : (b))
#define min_t(type, a, b)	((type)(a) < (type)(b) ? (type)(a) : (type)(b))
#define max_t(type, a, b)	((type)(a) > (type)(b) ? (type)(a) : (type)(b))
#define clamp(val, lo, hi)	min_t(__typeof__(val), max_t(__typeof__(val), val, lo), hi)
#define clamp_val(val, lo, hi)	clamp(val, lo, hi)

#define U32_MAX		0xFFFFFFFFU

/* fls is provided by newlib's <strings.h> */
#include <strings.h>

#define container_of(ptr, type, member) \
	((type *)((char *)(ptr) - offsetof(type, member)))

#define upper_32_bits(n)	((u32)(((n) >> 16) >> 16))
#define lower_32_bits(n)	((u32)(n))

/* Pointer alignment */
#define PTR_ALIGN(p, a)		((typeof(p))ALIGN((unsigned long)(p), (a)))

/* IS_ENABLED — evaluates Kconfig-style symbols.
 * For bare-metal, define the symbols we want enabled. */
#define __ARG_PLACEHOLDER_1	0,
#define __take_second_arg(__ignored, val, ...)	val
#define __is_defined(x)		___is_defined(x)
#define ___is_defined(val)	____is_defined(__ARG_PLACEHOLDER_##val)
#define ____is_defined(arg1_or_junk)	__take_second_arg(arg1_or_junk 1, 0, 0)
#define IS_ENABLED(option)	__is_defined(option)

/* Define which features we want active for bare-metal DRD */
#define CONFIG_USB_DWC3_GADGET	1
#define CONFIG_USB_HOST		1

/* printk — used by WARN_ON etc. */
#include <stdio.h>
#define printk	printf

#endif /* _LINUX_KERNEL_H */
