#ifndef _DM_DEVICE_COMPAT_H
#define _DM_DEVICE_COMPAT_H

#include <stdio.h>

// #define dev_dbg(dev, fmt, ...) printf("[DWC3 DBG] " fmt, ##__VA_ARGS__)
// #define dev_vdbg(dev, fmt, ...) printf("[DWC3 DVG] " fmt, ##__VA_ARGS__)

#define dev_info(dev, fmt, ...) printf("[DWC3 INF] " fmt, ##__VA_ARGS__)
#define dev_warn(dev, fmt, ...) printf("[DWC3 WRN] " fmt, ##__VA_ARGS__)
#define dev_err(dev, fmt, ...) printf("[DWC3 ERR] " fmt, ##__VA_ARGS__)

#define dev_dbg(dev, fmt, ...)
#define dev_vdbg(dev, fmt, ...)

#endif /* _DM_DEVICE_COMPAT_H */
