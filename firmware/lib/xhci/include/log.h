#ifndef _LOG_H
#define _LOG_H

#include <stdio.h>

#define pr_debug(fmt, ...)	do {} while (0)
#define pr_info(fmt, ...)	do {} while (0)
#define pr_warn(fmt, ...)	printf("[WRN] " fmt, ##__VA_ARGS__)
#define pr_err(fmt, ...)	printf("[ERR] " fmt, ##__VA_ARGS__)

/* U-Boot's debug() macro — used throughout xHCI/DWC3 code */
#define debug(fmt, ...)		do {} while (0)

#endif /* _LOG_H */
