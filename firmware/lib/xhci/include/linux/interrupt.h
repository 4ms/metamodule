#ifndef _LINUX_INTERRUPT_H
#define _LINUX_INTERRUPT_H

typedef enum {
	IRQ_NONE = 0,
	IRQ_HANDLED = 1,
	IRQ_WAKE_THREAD = 2,
} irqreturn_t;

#endif /* _LINUX_INTERRUPT_H */
