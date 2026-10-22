/* Bare-metal shim — no watchdog */
#ifndef _WATCHDOG_H
#define _WATCHDOG_H

#define WATCHDOG_RESET()	do {} while (0)
#define schedule()		do {} while (0)

#endif
