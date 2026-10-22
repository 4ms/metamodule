/* Bare-metal shim — identity address mapping (1:1 VA=PA) */
#ifndef _PHYS2BUS_H
#define _PHYS2BUS_H

#include <linux/types.h>

static inline unsigned long virt_to_phys(void *vaddr)
{
	return (unsigned long)vaddr;
}

static inline void *phys_to_virt(unsigned long paddr)
{
	return (void *)paddr;
}

static inline unsigned long phys_to_bus(unsigned long phys)
{
	return phys;
}

static inline unsigned long bus_to_phys(unsigned long bus)
{
	return bus;
}

/* Device-model aware variants — identity for bare-metal */
static inline unsigned long dev_phys_to_bus(void *dev, unsigned long phys)
{
	(void)dev;
	return phys;
}

static inline unsigned long dev_bus_to_phys(void *dev, unsigned long bus)
{
	(void)dev;
	return bus;
}

#endif
