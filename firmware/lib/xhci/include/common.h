#ifndef _COMMON_H
#define _COMMON_H

/* Umbrella header — in U-Boot this pulls in most basic types and utilities. */

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <string.h>

#include <linux/types.h>
#include <linux/compiler.h>
#include <linux/kernel.h>
#include <linux/err.h>
#include <linux/bug.h>
#include <linux/spinlock.h>
#include <linux/slab.h>
#include <linux/interrupt.h>
#include <log.h>

/* errno values used by the driver */
#include <errno.h>

/* U-Boot's CONFIG_IS_ENABLED — always 0 for bare-metal.
 * This disables PHY-bulk, DM_USB, device-tree parsing, etc. */
#define CONFIG_IS_ENABLED(x)	0

/* MODULE_* macros — no-op */
#define MODULE_ALIAS(x)
#define MODULE_AUTHOR(x)
#define MODULE_LICENSE(x)
#define MODULE_DESCRIPTION(x)

/* roundup — used in ep0.c */
#define roundup(x, y)	((((x) + ((y) - 1)) / (y)) * (y))

#endif /* _COMMON_H */
