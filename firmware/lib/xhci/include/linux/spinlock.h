#ifndef _LINUX_SPINLOCK_H
#define _LINUX_SPINLOCK_H

#include <stdint.h>

/* Single-core bare-metal: all lock operations are no-ops. */

typedef struct { void * x; } spinlock_t;
typedef struct { void * x; } mutex_t;
typedef uint32_t irqflags_t;

#define spin_lock_init(l)		do { } while (0)
#define spin_lock(l)			do { } while (0)
#define spin_unlock(l)			do { } while (0)
#define spin_lock_irqsave(l, flags)	do { } while (0)
#define spin_unlock_irqrestore(l, f)	do { } while (0)

#define mutex_init(m)			do { } while (0)
#define mutex_lock(m)			do { } while (0)
#define mutex_unlock(m)			do { } while (0)

#endif /* _LINUX_SPINLOCK_H */
