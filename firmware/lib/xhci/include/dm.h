#ifndef _DM_H
#define _DM_H

#include <linux/types.h>

/* Minimal struct device / struct udevice shim.
 * DWC3 core.h embeds a `struct device *dev` in struct dwc3. */

struct device {
	const char *name;
	void *driver_data;
};

/* U-Boot uses struct udevice; alias it */
//typedef struct device udevice;
#define udevice device

#define dev_set_drvdata(dev, data)	((dev)->driver_data = (data))
#define dev_get_drvdata(dev)		((dev)->driver_data)

/* Opaque types — used as pointers in struct dwc3, never dereferenced */
struct platform_device { int dummy; };
struct dentry { int dummy; };
struct debugfs_regset32 { int dummy; };

#endif /* _DM_H */
