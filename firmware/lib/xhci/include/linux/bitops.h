#ifndef _LINUX_BITOPS_H
#define _LINUX_BITOPS_H

#define BITS_PER_LONG	(8 * __SIZEOF_LONG__)

#define BIT(n)		(1UL << (n))
#define GENMASK(h, l)	(((~0UL) << (l)) & (~0UL >> (BITS_PER_LONG - 1 - (h))))

#endif /* _LINUX_BITOPS_H */
