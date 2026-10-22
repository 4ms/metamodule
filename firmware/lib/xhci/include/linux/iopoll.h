/* Bare-metal shim for linux/iopoll.h — register polling macros */
#ifndef _LINUX_IOPOLL_H
#define _LINUX_IOPOLL_H

#include <linux/delay.h>
#include <linux/errno.h>
#include <asm/io.h>

/**
 * read_poll_timeout - Poll a register until condition or timeout
 * @op:         accessor function (e.g. readl)
 * @val:        variable to read the value into
 * @cond:       break condition (usually involving @val)
 * @sleep_us:   sleep between polls (microseconds)
 * @timeout_us: total timeout (microseconds)
 * @sleep_before_read: ignored (Linux-specific)
 * @addr:       address to poll
 */
#define read_poll_timeout(op, val, cond, sleep_us, timeout_us, \
			  sleep_before_read, addr) \
({ \
	unsigned long __timeout_us = (timeout_us); \
	unsigned long __elapsed = 0; \
	int __ret = 0; \
	for (;;) { \
		(val) = op(addr); \
		if (cond) \
			break; \
		if (__elapsed >= __timeout_us) { \
			(val) = op(addr); \
			__ret = (cond) ? 0 : -ETIMEDOUT; \
			break; \
		} \
		if (sleep_us) { \
			udelay(sleep_us); \
			__elapsed += (sleep_us); \
		} else { \
			__elapsed++; \
		} \
	} \
	__ret; \
})

/**
 * readx_poll_sleep_timeout - Poll using a read accessor until condition or timeout
 * @op:         accessor function (e.g. readl, xhci_readl)
 * @addr:       address to poll
 * @val:        variable to read the value into
 * @cond:       break condition (usually involving @val)
 * @sleep_us:   sleep between polls (microseconds)
 * @timeout_us: total timeout (microseconds)
 */
#define readx_poll_sleep_timeout(op, addr, val, cond, sleep_us, timeout_us) \
({ \
	unsigned long __timeout_us = (timeout_us); \
	unsigned long __elapsed = 0; \
	int __ret = 0; \
	for (;;) { \
		(val) = op(addr); \
		if (cond) \
			break; \
		if (__elapsed >= __timeout_us) { \
			(val) = op(addr); \
			__ret = (cond) ? 0 : -ETIMEDOUT; \
			break; \
		} \
		if (sleep_us) { \
			udelay(sleep_us); \
			__elapsed += (sleep_us); \
		} else { \
			__elapsed++; \
		} \
	} \
	__ret; \
})

#endif
