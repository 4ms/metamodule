#ifndef _ASM_IO_H
#define _ASM_IO_H

#include <linux/compiler.h>
#include <linux/types.h>

// static inline u32 readl(const volatile void __iomem *addr)
// {
// 	u32 val;
// 	__asm__ volatile("ldr %w0, [%1]" : "=r"(val) : "r"(addr) : "memory");
// 	return val;
// }

// static inline void writel(u32 val, volatile void __iomem *addr)
// {
// 	__asm__ volatile("str %w0, [%1]" : : "r"(val), "r"(addr) : "memory");
// }

// #define readl_relaxed(addr) readl(addr)
// #define writel_relaxed(val, addr) writel(val, addr)

// From u-boot:
#define __iormb()	asm("dmb sy")
#define __iowmb()	asm("dmb sy")
#define __arch_getl(a)			(*(volatile unsigned int *)(a))
#define __arch_putl(v,a)		(*(volatile unsigned int *)(a) = (v))
#define readl(c)	({ u32 __v = __arch_getl(c); __iormb(); __v; })
#define writel(v,c)	({ u32 __v = v; __iowmb(); __arch_putl(__v,c); __v; })

#endif /* _ASM_IO_H */
