#ifndef _LINUX_DELAY_H
#define _LINUX_DELAY_H

#ifdef __cplusplus
extern "C" {
#endif

/* Provided by the platform: see xhci_platform.h */
void udelay(unsigned int us);
void mdelay(unsigned int ms);
unsigned long get_timer(unsigned long base);

#ifdef __cplusplus
}
#endif

#endif /* _LINUX_DELAY_H */
