/*
 * xhci_host.c — xHCI host mode for DWC3 (from stm32mp2-baremetal's xhci_baremetal.c)
 *
 * Provides:
 *   - xhci_host_init()   : initialize xHCI after dwc3_baremetal_init(HOST)
 *   - xhci_host_poll()   : poll for port changes and enumerate new devices
 *   - usb_maxpacket()    : USB core shim needed by xhci-ring.c
 *   - USB device table   : non-DM device tracking
 */

#include <common.h>
#include <usb.h>
#include <usb/xhci.h>
#include <xhci_host.h>
#include <linux/delay.h>
#include <string.h>

/* ---- USB device table (non-DM) ---- */

/* MetaModule: entries are freed one at a time (devices behind a hub come and go) */
static struct usb_device usb_dev_table[USB_MAX_DEVICE];
static bool usb_dev_used[USB_MAX_DEVICE];

struct usb_device *usb_get_dev_index(int index)
{
	if (index < 0 || index >= USB_MAX_DEVICE || !usb_dev_used[index])
		return NULL;
	return &usb_dev_table[index];
}

int usb_alloc_new_device(void *controller, struct usb_device **devp)
{
	int i = 0;
	while (i < USB_MAX_DEVICE && usb_dev_used[i])
		i++;
	if (i == USB_MAX_DEVICE) {
		printf("usb_alloc_new_device: too many devices\n");
		return -1;
	}
	struct usb_device *dev = &usb_dev_table[i];
	memset(dev, 0, sizeof(*dev));
	dev->devnum = i + 1; /* USB devnum starts at 1 */
	dev->controller = controller;
	dev->maxpacketsize = PACKET_SIZE_64;
	dev->speed = USB_SPEED_UNKNOWN;
	usb_dev_used[i] = true;
	*devp = dev;
	return 0;
}

static void free_device_entry(struct usb_device *dev)
{
	usb_dev_used[dev->devnum - 1] = false;
}

int usb_maxpacket(struct usb_device *dev, unsigned long pipe)
{
	if (usb_pipein(pipe))
		return dev->epmaxpacketin[usb_pipeendpoint(pipe)];
	else
		return dev->epmaxpacketout[usb_pipeendpoint(pipe)];
}

/* ---- Stub functions declared in usb.h ---- */

int usb_new_device(struct usb_device *dev)
{
	return 0;
}

int usb_update_hub_device(struct usb_device *dev)
{
	return 0;
}

bool usb_device_has_child_on_port(struct usb_device *parent, int port)
{
	return false;
}

int usb_hub_probe(struct usb_device *dev, int ifnum)
{
	return 0;
}

void usb_hub_reset(void)
{
}

void usb_find_usb2_hub_address_port(struct usb_device *udev,
				    uint8_t *hub_address, uint8_t *hub_port)
{
	struct usb_device *hop = udev;
	if (hop->parent) {
		while (hop->parent->parent)
			hop = hop->parent;
		*hub_port = hop->portnr;
		*hub_address = hop->parent->devnum;
	} else {
		*hub_port = 0;
		*hub_address = 0;
	}
}

int usb_control_msg(struct usb_device *dev, unsigned int pipe,
		    unsigned char request, unsigned char requesttype,
		    unsigned short value, unsigned short index,
		    void *data, unsigned short size, int timeout)
{
	struct devrequest setup;
	setup.requesttype = requesttype;
	setup.request = request;
	setup.value = cpu_to_le16(value);
	setup.index = cpu_to_le16(index);
	setup.length = cpu_to_le16(size);

	int ret = submit_control_msg(dev, usb_sndctrlpipe(dev, 0),
				     data, size, &setup);
	if (ret < 0)
		return ret;
	return dev->act_len;
}

int usb_set_interface(struct usb_device *dev, int interface, int alternate)
{
	return usb_control_msg(dev, usb_sndctrlpipe(dev, 0),
			       USB_REQ_SET_INTERFACE, USB_RECIP_INTERFACE,
			       alternate, interface, NULL, 0, USB_CNTL_TIMEOUT);
}

int usb_get_port_status(struct usb_device *dev, int port, void *data)
{
	return usb_control_msg(dev, usb_rcvctrlpipe(dev, 0),
			       USB_REQ_GET_STATUS, USB_DIR_IN | USB_RT_PORT,
			       0, port, data, sizeof(struct usb_port_status),
			       USB_CNTL_TIMEOUT);
}

/* ---- xHCI host init/shutdown/poll ---- */

static struct xhci_ctrl xhci_ctrl_instance;
static struct usb_device *root_hub;
static bool device_connected;
static int max_ports;
static void (*disconnect_callback)(struct usb_device *dev);

static const char *speed_str(enum usb_device_speed speed)
{
	switch (speed) {
	case USB_SPEED_LOW:	return "Low (1.5 Mbps)";
	case USB_SPEED_FULL:	return "Full (12 Mbps)";
	case USB_SPEED_HIGH:	return "High (480 Mbps)";
	case USB_SPEED_SUPER:	return "Super (5 Gbps)";
	default:		return "Unknown";
	}
}

static enum usb_device_speed portsc_to_speed(u32 portsc)
{
	switch (portsc & DEV_SPEED_MASK) {
	case XDEV_FS: return USB_SPEED_FULL;
	case XDEV_LS: return USB_SPEED_LOW;
	case XDEV_HS: return USB_SPEED_HIGH;
	case XDEV_SS: return USB_SPEED_SUPER;
	default:      return USB_SPEED_UNKNOWN;
	}
}

/*
 * Get a USB string descriptor and decode it to ASCII.
 */
static int usb_get_string(struct usb_device *dev, int index,
			  char *buf, int buflen)
{
	unsigned char tbuf[256];
	int ret;

	if (index == 0 || buflen < 2)
		return 0;

	/* First get the language ID list (string 0) to get wLANGID[0] */
	ret = usb_control_msg(dev, usb_rcvctrlpipe(dev, 0),
			      USB_REQ_GET_DESCRIPTOR, USB_DIR_IN,
			      (USB_DT_STRING << 8) | 0, 0,
			      tbuf, 4, USB_CNTL_TIMEOUT);
	if (ret < 4)
		return 0;

	u16 langid = tbuf[2] | (tbuf[3] << 8);

	/* Now get the actual string */
	ret = usb_control_msg(dev, usb_rcvctrlpipe(dev, 0),
			      USB_REQ_GET_DESCRIPTOR, USB_DIR_IN,
			      (USB_DT_STRING << 8) | index, langid,
			      tbuf, sizeof(tbuf), USB_CNTL_TIMEOUT);
	if (ret < 2)
		return 0;

	/* Decode UTF-16LE to ASCII */
	int slen = (tbuf[0] - 2) / 2;
	if (slen > buflen - 1)
		slen = buflen - 1;
	for (int i = 0; i < slen; i++)
		buf[i] = tbuf[2 + i * 2]; /* low byte of UTF-16 */
	buf[slen] = '\0';
	return slen;
}

/* Forward declarations */
static int hub_configure(struct usb_device *dev);
static void disable_slot(struct xhci_ctrl *ctrl, struct usb_device *dev);
static void remove_device(struct usb_device *dev);

/*
 * Undo a partially-enumerated device (slot allocated but enumeration failed)
 * so a misbehaving device can't leak xHC slots or device-table entries
 * across repeated connect attempts.
 */
static void enum_failed_cleanup(struct xhci_ctrl *ctrl, struct usb_device *dev)
{
	disable_slot(ctrl, dev);
	free_device_entry(dev);
}

/*
 * Enumerate a newly connected device:
 *   1. Allocate device slot (Enable Slot command)
 *   2. Set Address (Address Device command)
 *   3. Read device descriptor
 *   4. Read config descriptor
 *   5. Set Configuration
 *   6. If hub, configure hub ports
 */
static int xhci_enumerate_device(struct usb_device *parent, int port,
				 enum usb_device_speed speed,
				 struct usb_device **devp)
{
	struct xhci_ctrl *ctrl = &xhci_ctrl_instance;
	struct usb_device *dev;
	int ret;

	/* Allocate a usb_device for this new device */
	ret = usb_alloc_new_device(ctrl, &dev);
	if (ret) {
		printf("  Failed to allocate USB device\n");
		return ret;
	}

	dev->speed = speed;
	dev->portnr = port;
	dev->parent = parent;
	dev->epmaxpacketin[0] = 64;
	dev->epmaxpacketout[0] = 64;

	printf("  Speed: %s\n", speed_str(dev->speed));

	/* Enable Slot — xHCI allocates a slot and virtual device structs */
	ret = usb_alloc_device(dev);
	if (ret) {
		printf("  Enable Slot failed: %d\n", ret);
		free_device_entry(dev);
		return ret;
	}
	printf("  Slot %d assigned\n", dev->slot_id);

	/* Set Address (USB_REQ_SET_ADDRESS) — routed to xhci_address_device */
	ret = usb_control_msg(dev, usb_sndctrlpipe(dev, 0),
			      USB_REQ_SET_ADDRESS, 0,
			      dev->devnum, 0, NULL, 0, USB_CNTL_TIMEOUT);
	if (ret < 0) {
		printf("  Set Address failed: %d\n", ret);
		enum_failed_cleanup(ctrl, dev);
		return ret;
	}
	printf("  Address set\n");

	/* Get Device Descriptor (first 8 bytes to learn bMaxPacketSize0) */
	struct usb_device_descriptor *desc = &dev->descriptor;
	ret = usb_control_msg(dev, usb_rcvctrlpipe(dev, 0),
			      USB_REQ_GET_DESCRIPTOR, USB_DIR_IN,
			      (USB_DT_DEVICE << 8), 0,
			      desc, 8, USB_CNTL_TIMEOUT);
	if (ret < 8) {
		printf("  Get Descriptor (8) failed: %d\n", ret);
		enum_failed_cleanup(ctrl, dev);
		return ret;
	}

	/* Update ep0 max packet size */
	dev->epmaxpacketin[0] = desc->bMaxPacketSize0;
	dev->epmaxpacketout[0] = desc->bMaxPacketSize0;

	/* Get full device descriptor */
	ret = usb_control_msg(dev, usb_rcvctrlpipe(dev, 0),
			      USB_REQ_GET_DESCRIPTOR, USB_DIR_IN,
			      (USB_DT_DEVICE << 8), 0,
			      desc, sizeof(*desc), USB_CNTL_TIMEOUT);
	if (ret < (int)sizeof(*desc)) {
		printf("  Get Descriptor (full) failed: %d\n", ret);
		enum_failed_cleanup(ctrl, dev);
		return ret;
	}

	/* Read manufacturer, product, serial strings */
	usb_get_string(dev, desc->iManufacturer, dev->mf, sizeof(dev->mf));
	usb_get_string(dev, desc->iProduct, dev->prod, sizeof(dev->prod));
	usb_get_string(dev, desc->iSerialNumber, dev->serial, sizeof(dev->serial));

	printf("  Device: %04x:%04x", le16_to_cpu(desc->idVendor),
	       le16_to_cpu(desc->idProduct));
	if (dev->mf[0])
		printf(" %s", dev->mf);
	if (dev->prod[0])
		printf(" %s", dev->prod);
	printf("\n");
	printf("  Class: %02x/%02x/%02x, %d config(s)\n",
	       desc->bDeviceClass, desc->bDeviceSubClass,
	       desc->bDeviceProtocol, desc->bNumConfigurations);

	if (desc->bNumConfigurations == 0) {
		printf("  No configurations!\n");
		enum_failed_cleanup(ctrl, dev);
		return -ENODEV;
	}

	/* Get Config Descriptor (first 9 bytes to learn wTotalLength) */
	struct usb_config_descriptor cfg_hdr;
	ret = usb_control_msg(dev, usb_rcvctrlpipe(dev, 0),
			      USB_REQ_GET_DESCRIPTOR, USB_DIR_IN,
			      (USB_DT_CONFIG << 8), 0,
			      &cfg_hdr, sizeof(cfg_hdr), USB_CNTL_TIMEOUT);
	if (ret < (int)sizeof(cfg_hdr)) {
		printf("  Get Config Descriptor failed: %d\n", ret);
		enum_failed_cleanup(ctrl, dev);
		return ret;
	}

	u16 total_len = le16_to_cpu(cfg_hdr.wTotalLength);
	printf("  Config %d: %d interface(s), total %d bytes\n",
	       cfg_hdr.bConfigurationValue, cfg_hdr.bNumInterfaces, total_len);

	/* Get full config descriptor */
	unsigned char cfg_buf[512];
	if (total_len > sizeof(cfg_buf))
		total_len = sizeof(cfg_buf);
	ret = usb_control_msg(dev, usb_rcvctrlpipe(dev, 0),
			      USB_REQ_GET_DESCRIPTOR, USB_DIR_IN,
			      (USB_DT_CONFIG << 8), 0,
			      cfg_buf, total_len, USB_CNTL_TIMEOUT);
	if (ret < (int)total_len) {
		printf("  Get Config (full) failed: %d (got %d)\n", ret, ret);
		/* Non-fatal, continue with what we got */
	}

	/* Parse config descriptor into udev->config for xhci_set_configuration */
	memset(&dev->config, 0, sizeof(dev->config));
	memcpy(&dev->config.desc, &cfg_hdr, sizeof(cfg_hdr));
	dev->config.no_of_if = cfg_hdr.bNumInterfaces;

	int cur_if = -1;
	int cur_ep_idx = 0;
	int pos = cfg_hdr.bLength;
	while (pos + 2 <= total_len) {
		u8 dlen = cfg_buf[pos];
		u8 dtype = cfg_buf[pos + 1];
		if (dlen < 2)
			break;

		if (dtype == USB_DT_INTERFACE && dlen >= 9) {
			struct usb_interface_descriptor *intf =
				(struct usb_interface_descriptor *)&cfg_buf[pos];
			/* MetaModule: an interface's alternate settings aren't
			 * active after Set Configuration, so don't configure
			 * their endpoints (they'd replace the default's) */
			cur_if = intf->bAlternateSetting == 0 ?
				 intf->bInterfaceNumber : -1;
			if (cur_if >= 0 && cur_if < USB_MAXINTERFACES) {
				memcpy(&dev->config.if_desc[cur_if].desc,
				       intf, sizeof(*intf));
				dev->config.if_desc[cur_if].no_of_ep =
					intf->bNumEndpoints;
				cur_ep_idx = 0;
			}
			printf("    Interface %d: class %02x/%02x/%02x, %d EP(s)\n",
			       intf->bInterfaceNumber,
			       intf->bInterfaceClass,
			       intf->bInterfaceSubClass,
			       intf->bInterfaceProtocol,
			       intf->bNumEndpoints);
		} else if (dtype == USB_DT_ENDPOINT && dlen >= 7 &&
			   cur_if >= 0 && cur_if < USB_MAXINTERFACES) {
			/* Standard endpoint descriptor is 7 bytes on the wire */
			struct usb_endpoint_descriptor *ep =
				&dev->config.if_desc[cur_if].ep_desc[cur_ep_idx];
			memcpy(ep, &cfg_buf[pos], dlen < sizeof(*ep) ? dlen : sizeof(*ep));

			u8 epaddr = ep->bEndpointAddress;
			u8 epnum = epaddr & 0x0f;
			u16 maxpkt = le16_to_cpu(ep->wMaxPacketSize);

			if (epaddr & USB_DIR_IN)
				dev->epmaxpacketin[epnum] = maxpkt;
			else
				dev->epmaxpacketout[epnum] = maxpkt;

			printf("      EP 0x%02x: %s %s, maxpkt %d\n",
			       epaddr,
			       (epaddr & USB_DIR_IN) ? "IN " : "OUT",
			       (ep->bmAttributes & 3) == USB_ENDPOINT_XFER_BULK ? "bulk" :
			       (ep->bmAttributes & 3) == USB_ENDPOINT_XFER_INT  ? "int " :
			       (ep->bmAttributes & 3) == USB_ENDPOINT_XFER_ISOC ? "isoc" :
			       "ctrl",
			       maxpkt);

			cur_ep_idx++;
		}
		pos += dlen;
	}

	/* Set Configuration — xhci_set_configuration reads udev->config */
	ret = usb_control_msg(dev, usb_sndctrlpipe(dev, 0),
			      USB_REQ_SET_CONFIGURATION, 0,
			      cfg_hdr.bConfigurationValue, 0,
			      NULL, 0, USB_CNTL_TIMEOUT);
	if (ret < 0) {
		printf("  Set Configuration failed: %d\n", ret);
		enum_failed_cleanup(ctrl, dev);
		return ret;
	}
	printf("  Configured (config %d)\n", cfg_hdr.bConfigurationValue);

	dev->configno = cfg_hdr.bConfigurationValue;
	device_connected = true;
	*devp = dev;

	/* If this device is a hub, configure it */
	if (desc->bDeviceClass == USB_CLASS_HUB) {
		ret = hub_configure(dev);
		if (ret)
			printf("  Hub configuration failed: %d\n", ret);
	}

	return 0;
}

/* ---- Hub support ---- */

#define MAX_HUBS 4

struct hub_info {
	struct usb_device *dev;
	struct usb_hub_descriptor desc;
	int num_ports;
};

static struct hub_info hubs[MAX_HUBS];
static int num_hubs;

/*
 * Read hub descriptor, update xHCI slot context with DEV_HUB,
 * power on all downstream ports.
 */
static int hub_configure(struct usb_device *dev)
{
	struct xhci_ctrl *ctrl = &xhci_ctrl_instance;
	int ret;

	if (num_hubs >= MAX_HUBS) {
		printf("  Too many hubs\n");
		return -ENOMEM;
	}

	struct hub_info *hub = &hubs[num_hubs];
	memset(hub, 0, sizeof(*hub));
	hub->dev = dev;

	/* Read hub descriptor */
	u8 dt = (dev->speed >= USB_SPEED_SUPER) ? USB_DT_SS_HUB : USB_DT_HUB;
	ret = usb_control_msg(dev, usb_rcvctrlpipe(dev, 0),
			      USB_REQ_GET_DESCRIPTOR,
			      USB_DIR_IN | USB_RT_HUB,
			      (dt << 8), 0,
			      &hub->desc, sizeof(hub->desc),
			      USB_CNTL_TIMEOUT);
	if (ret < 7) {
		printf("  Get Hub Descriptor failed: %d\n", ret);
		return ret < 0 ? ret : -EIO;
	}

	hub->num_ports = hub->desc.bNbrPorts;
	if (hub->num_ports > USB_MAXCHILDREN)
		hub->num_ports = USB_MAXCHILDREN;

	dev->maxchild = hub->num_ports;
	printf("  Hub: %d port(s)\n", hub->num_ports);

	/* Update xHCI slot context: set DEV_HUB and number of ports */
	struct xhci_virt_device *virt_dev = ctrl->devs[dev->slot_id];
	struct xhci_input_control_ctx *ctrl_ctx =
		xhci_get_input_control_ctx(virt_dev->in_ctx);
	struct xhci_slot_ctx *slot_ctx =
		xhci_get_slot_ctx(ctrl, virt_dev->in_ctx);

	ctrl_ctx->add_flags = cpu_to_le32(SLOT_FLAG);
	ctrl_ctx->drop_flags = 0;

	/* Copy current slot context then modify */
	xhci_inval_cache((uintptr_t)virt_dev->out_ctx->bytes,
			 virt_dev->out_ctx->size);
	xhci_slot_copy(ctrl, virt_dev->in_ctx, virt_dev->out_ctx);

	slot_ctx->dev_info |= cpu_to_le32(DEV_HUB);
	slot_ctx->dev_info2 |= cpu_to_le32(XHCI_MAX_PORTS(hub->num_ports));

	/* Set TT think time for HS hubs */
	if (dev->speed == USB_SPEED_HIGH) {
		u16 char_bits = le16_to_cpu(hub->desc.wHubCharacteristics);
		u32 think_time = (char_bits & HUB_CHAR_TTTT) >> 5;
		slot_ctx->tt_info |= cpu_to_le32(TT_THINK_TIME(think_time));
	}

	/* Issue Evaluate Context to update the slot */
	ret = xhci_configure_endpoints(dev, true);
	if (ret) {
		printf("  Hub Evaluate Context failed: %d\n", ret);
		return ret;
	}

	num_hubs++;

	/* Power on each downstream port */
	for (int p = 1; p <= hub->num_ports; p++) {
		usb_control_msg(dev, usb_sndctrlpipe(dev, 0),
				USB_REQ_SET_FEATURE, USB_RT_PORT,
				USB_PORT_FEAT_POWER, p,
				NULL, 0, USB_CNTL_TIMEOUT);
	}

	/* Wait for power good (bPwrOn2PwrGood * 2 ms) */
	int delay = hub->desc.bPwrOn2PwrGood * 2;
	if (delay < 100)
		delay = 100;
	mdelay(delay);

	printf("  Hub ports powered\n");
	return 0;
}

/*
 * Convert USB port status wPortStatus to device speed.
 */
static enum usb_device_speed hub_port_speed(u16 portstatus)
{
	u16 spd = portstatus & USB_PORT_STAT_SPEED_MASK;
	if (spd == USB_PORT_STAT_SUPER_SPEED)
		return USB_SPEED_SUPER;
	if (spd == USB_PORT_STAT_HIGH_SPEED)
		return USB_SPEED_HIGH;
	if (spd == USB_PORT_STAT_LOW_SPEED)
		return USB_SPEED_LOW;
	return USB_SPEED_FULL;
}

/*
 * MetaModule: a hub port's connection changed. Whatever was on it is gone (a
 * reconnect is a new device); if a device is there now, reset the port and
 * enumerate it. Returns the new device, or NULL.
 */
static struct usb_device *hub_port_changed(struct usb_device *hubdev, int p,
					   u16 status)
{
	struct usb_port_status ps;
	int ret;

	if (hubdev->children[p - 1]) {
		printf("Hub port %d: device disconnected\n", p);
		remove_device(hubdev->children[p - 1]);
	}

	if (!(status & USB_PORT_STAT_CONNECTION))
		return NULL;

	printf("Hub port %d: device connected\n", p);

	/* Reset the port */
	usb_control_msg(hubdev, usb_sndctrlpipe(hubdev, 0),
			USB_REQ_SET_FEATURE, USB_RT_PORT,
			USB_PORT_FEAT_RESET, p,
			NULL, 0, USB_CNTL_TIMEOUT);
	mdelay(50);

	/* Clear reset change */
	usb_control_msg(hubdev, usb_sndctrlpipe(hubdev, 0),
			USB_REQ_CLEAR_FEATURE, USB_RT_PORT,
			USB_PORT_FEAT_C_RESET, p,
			NULL, 0, USB_CNTL_TIMEOUT);

	/* Re-read status for speed */
	ret = usb_get_port_status(hubdev, p, &ps);
	if (ret < 0)
		return NULL;
	status = le16_to_cpu(ps.wPortStatus);

	if (!(status & USB_PORT_STAT_ENABLE)) {
		printf("Hub port %d: not enabled after reset\n", p);
		return NULL;
	}

	struct usb_device *newdev;
	ret = xhci_enumerate_device(hubdev, p, hub_port_speed(status), &newdev);
	if (ret) {
		printf("Hub port %d: enumeration failed: %d\n", p, ret);
		return NULL;
	}
	hubdev->children[p - 1] = newdev;
	return newdev;
}

/*
 * Poll all registered hubs for port status changes.
 * Handles connect/disconnect on hub ports.
 * Returns a newly enumerated device, or NULL.
 */
static struct usb_device *hub_poll(void)
{
	for (int h = 0; h < num_hubs; h++) {
		struct hub_info *hub = &hubs[h];
		struct usb_device *hubdev = hub->dev;

		for (int p = 1; p <= hub->num_ports; p++) {
			struct usb_port_status ps;
			int ret = usb_get_port_status(hubdev, p, &ps);
			if (ret < 0)
				continue;

			u16 status = le16_to_cpu(ps.wPortStatus);
			u16 change = le16_to_cpu(ps.wPortChange);

			if (!(change & USB_PORT_STAT_C_CONNECTION))
				continue;

			/* Clear the connection change bit */
			usb_control_msg(hubdev, usb_sndctrlpipe(hubdev, 0),
					USB_REQ_CLEAR_FEATURE, USB_RT_PORT,
					USB_PORT_FEAT_C_CONNECTION, p,
					NULL, 0, USB_CNTL_TIMEOUT);

			/* MetaModule: one change per poll, since removing a
			 * device can remove hubs */
			return hub_port_changed(hubdev, p, status);
		}
	}
	return NULL;
}

/*
 * Free a single virtual device's resources (rings, contexts).
 * Mirrors xhci_free_virt_devices() but for one slot only.
 */
static void xhci_free_virt_device(struct xhci_ctrl *ctrl, int slot_id)
{
	struct xhci_virt_device *virt_dev = ctrl->devs[slot_id];
	if (!virt_dev)
		return;

	ctrl->dcbaa->dev_context_ptrs[slot_id] = 0;

	for (int i = 0; i < 31; i++)
		if (virt_dev->eps[i].ring)
			xhci_ring_free(virt_dev->eps[i].ring);

	if (virt_dev->in_ctx)
		xhci_free_container_ctx(virt_dev->in_ctx);
	if (virt_dev->out_ctx)
		xhci_free_container_ctx(virt_dev->out_ctx);

	free(virt_dev);
	ctrl->devs[slot_id] = NULL;
}

/* Disable the device's xHCI slot (if it has one) and free its resources */
static void disable_slot(struct xhci_ctrl *ctrl, struct usb_device *dev)
{
	if (!dev->slot_id)
		return;

	xhci_queue_command(ctrl, NULL, dev->slot_id, 0, TRB_DISABLE_SLOT);
	union xhci_trb *event = xhci_wait_for_event(ctrl, TRB_COMPLETION);
	if (event) {
		u32 comp = GET_COMP_CODE(le32_to_cpu(event->event_cmd.status));
		if (comp != COMP_SUCCESS)
			printf("Disable Slot %d: comp code %d\n",
			       dev->slot_id, comp);
		xhci_acknowledge_event(ctrl);
	}

	xhci_free_virt_device(ctrl, dev->slot_id);
	dev->slot_id = 0;
}

/*
 * MetaModule: a device is gone (unplugged, or behind a hub that is). Removes
 * the devices behind it first, tells the disconnect callback, then frees it.
 */
static void remove_device(struct usb_device *dev)
{
	struct xhci_ctrl *ctrl = &xhci_ctrl_instance;

	for (int p = 0; p < USB_MAXCHILDREN; p++) {
		if (dev->children[p])
			remove_device(dev->children[p]);
	}

	for (int h = 0; h < num_hubs; h++) {
		if (hubs[h].dev == dev) {
			hubs[h] = hubs[--num_hubs];
			break;
		}
	}

	if (dev->parent) {
		for (int p = 0; p < USB_MAXCHILDREN; p++) {
			if (dev->parent->children[p] == dev)
				dev->parent->children[p] = NULL;
		}
	}

	if (disconnect_callback)
		disconnect_callback(dev);

	xhci_xfer_forget_device(dev);
	disable_slot(ctrl, dev);
	free_device_entry(dev);

	device_connected = false;
	for (int i = 0; i < USB_MAX_DEVICE; i++) {
		if (usb_dev_used[i] && &usb_dev_table[i] != root_hub)
			device_connected = true;
	}
}

/*
 * Wait for a root port to stop changing state, clearing change bits as they
 * appear. Self-powered/dual-role devices can bounce the bus for a second or
 * two after attach — e.g. USB-PD sinks issue hard resets when we never send
 * Source Capabilities, then settle down as plain 5V devices. Enumerating
 * during the bouncing wedges commands mid-transaction.
 * Returns the final PORTSC value.
 */
static u32 wait_port_stable(volatile uint32_t *portsc_reg, int settle_ms,
			    int max_ms)
{
	u32 portsc = xhci_readl(portsc_reg);
	int stable = 0;

	while (stable < settle_ms && max_ms > 0) {
		mdelay(10);
		stable += 10;
		max_ms -= 10;
		portsc = xhci_readl(portsc_reg);
		u32 changes = portsc & (PORT_CSC | PORT_PEC | PORT_RC |
					PORT_PLC | PORT_WRC | PORT_OCC |
					PORT_CEC);
		if (changes) {
			u32 val = portsc & (XHCI_PORT_RO | XHCI_PORT_RWS);
			xhci_writel(portsc_reg, val | changes);
			stable = 0;
		}
	}
	return portsc;
}

/*
 * Reset a root port and wait for it to come back enabled.
 * Returns true if the port is enabled after the reset. On success *out_portsc
 * receives the validated post-reset PORTSC value, whose Port Speed field is
 * valid; callers should decode the device speed from this rather than issuing a
 * fresh read, which can race with the port's follow-on link-state change and
 * momentarily report an undefined speed.
 */
static bool reset_root_port(volatile uint32_t *portsc_reg, int portnum,
			    u32 *out_portsc)
{
	u32 val = xhci_readl(portsc_reg);
	val &= XHCI_PORT_RO | XHCI_PORT_RWS;
	val |= PORT_RESET;
	xhci_writel(portsc_reg, val);

	/* Wait for reset to complete */
	u32 portsc = 0;
	int timeout = 500;
	while (timeout-- > 0) {
		mdelay(1);
		portsc = xhci_readl(portsc_reg);
		if (portsc & PORT_RC)
			break;
	}
	if (!(portsc & PORT_RC)) {
		printf("Port %d reset timeout!\n", portnum);
		return false;
	}

	/* Clear RC bit */
	val = portsc & (XHCI_PORT_RO | XHCI_PORT_RWS);
	xhci_writel(portsc_reg, val | PORT_RC);

	portsc = xhci_readl(portsc_reg);
	printf("Post-reset PORTSC=0x%08x\n", portsc);

	if (!(portsc & PORT_PE)) {
		printf("Port %d not enabled after reset\n", portnum);
		return false;
	}
	if (out_portsc)
		*out_portsc = portsc;
	return true;
}

/*
 * xhci_host_poll — check port status and handle connect/disconnect.
 *
 * Call this periodically from your main loop.
 * Returns the newly enumerated usb_device on connect, NULL otherwise.
 */
struct usb_device *xhci_host_poll(void)
{
	struct xhci_ctrl *ctrl = &xhci_ctrl_instance;
	struct xhci_hcor *hcor = ctrl->hcor;
	bool any_root_change = false;

	/* Check all root hub ports for status changes */
	for (int port_idx = 0; port_idx < max_ports; port_idx++) {
		volatile uint32_t *portsc_reg =
			&hcor->portregs[port_idx].or_portsc;
		u32 portsc = xhci_readl(portsc_reg);

		if (!(portsc & (PORT_CSC | PORT_PEC | PORT_RC)))
			continue;

		any_root_change = true;

		printf("Port %d status change: PORTSC=0x%08x", port_idx + 1,
		       portsc);
		if (portsc & PORT_CSC)
			printf(" [connect]");
		if (portsc & PORT_PEC)
			printf(" [enable]");
		if (portsc & PORT_RC)
			printf(" [reset]");
		printf("\n");

		/* Clear change bits (W1C) while preserving RWS bits */
		u32 clear = portsc;
		clear &= XHCI_PORT_RO | XHCI_PORT_RWS;
		clear |= portsc & (PORT_CSC | PORT_PEC | PORT_RC | PORT_WRC |
				   PORT_OCC | PORT_PLC | PORT_CEC);
		xhci_writel(portsc_reg, clear);

		/* Connection Status Change */
		if (portsc & PORT_CSC) {
			/* MetaModule: whatever was on the port is gone (a
			 * reconnect is a new device) */
			if (root_hub->children[port_idx]) {
				printf("Device disconnected on port %d\n",
				       port_idx + 1);
				remove_device(root_hub->children[port_idx]);
			}

			if (portsc & PORT_CONNECT) {
				printf("Device connected on port %d\n",
				       port_idx + 1);

				/* Let the device settle before resetting it
				 * (PD-capable devices bounce the bus first) */
				portsc = wait_port_stable(portsc_reg, 200, 2500);
				if (!(portsc & PORT_CONNECT)) {
					printf("Device left before enumeration\n");
					continue;
				}

				for (int attempt = 1; attempt <= 3; attempt++) {
					u32 rst_portsc = 0;
					if (!reset_root_port(portsc_reg,
							     port_idx + 1,
							     &rst_portsc))
						break;

					/* Decode speed from the value the reset
					 * validated. A fresh read here can race
					 * with the port's link-state change and
					 * report an undefined speed, which would
					 * later BUG() in the xHC device setup. */
					enum usb_device_speed speed =
						portsc_to_speed(rst_portsc);
					if (speed == USB_SPEED_UNKNOWN) {
						/* Speed field not latched yet:
						 * retry, then assume High so a
						 * transient can't crash enum. */
						for (int i = 0; i < 10 &&
						     speed == USB_SPEED_UNKNOWN;
						     i++) {
							mdelay(1);
							speed = portsc_to_speed(
								xhci_readl(portsc_reg));
						}
						if (speed == USB_SPEED_UNKNOWN) {
							printf("  Speed field unreadable; assuming High\n");
							speed = USB_SPEED_HIGH;
						}
					}

					/* Enumerate — port number is 1-based */
					struct usb_device *newdev;
					int ret = xhci_enumerate_device(
						root_hub, port_idx + 1, speed,
						&newdev);
					if (!ret) {
						root_hub->children[port_idx] = newdev;
						return newdev;
					}

					printf("Enumeration attempt %d failed: %d\n",
					       attempt, ret);

					portsc = wait_port_stable(portsc_reg,
								  200, 2500);
					if (!(portsc & PORT_CONNECT)) {
						printf("Device left, giving up\n");
						break;
					}
				}

			}
		}
	}

	/* No root hub changes — poll downstream hubs */
	if (!any_root_change && num_hubs > 0) {
		struct usb_device *newdev = hub_poll();
		if (newdev)
			return newdev;
	}

	return NULL;
}

int xhci_host_init(uintptr_t dwc3_base)
{
	struct xhci_hccr *hccr;
	struct xhci_hcor *hcor;

	memset(&xhci_ctrl_instance, 0, sizeof(xhci_ctrl_instance));
	memset(usb_dev_used, 0, sizeof(usb_dev_used));
	device_connected = false;
	num_hubs = 0;

	hccr = (struct xhci_hccr *)dwc3_base;
	hcor = (struct xhci_hcor *)(dwc3_base +
		HC_LENGTH(xhci_readl(&hccr->cr_capbase)));

	printf("xHCI: cap_length=%u, hci_version=0x%04x\n",
	       HC_LENGTH(xhci_readl(&hccr->cr_capbase)),
	       HC_VERSION(xhci_readl(&hccr->cr_capbase)));

	int ret = xhci_register_bare(&xhci_ctrl_instance, hccr, hcor);
	if (ret) {
		printf("xhci_register_bare failed: %d\n", ret);
		return ret;
	}

	max_ports = HCS_MAX_PORTS(xhci_readl(&hccr->cr_hcsparams1));
	if (max_ports > USB_MAXCHILDREN) /* root_hub->children[] */
		max_ports = USB_MAXCHILDREN;
	printf("xHCI: initialized, %d port(s)\n", max_ports);

	/* Allocate root hub as device 0 */
	ret = usb_alloc_new_device(&xhci_ctrl_instance, &root_hub);
	if (ret)
		return ret;
	root_hub->speed = USB_SPEED_HIGH;

	/* Tell xHCI this is the root hub (Enable Slot is skipped for rootdev==0) */
	ret = usb_alloc_device(root_hub);
	if (ret) {
		printf("Root hub alloc failed: %d\n", ret);
		return ret;
	}

	/* Set rootdev directly so control transfers to real devices
	 * don't get routed to the root hub handler. */
	xhci_ctrl_instance.rootdev = root_hub->devnum;

	/* Power on port(s) */
	for (int i = 0; i < max_ports; i++) {
		volatile uint32_t *ps = &hcor->portregs[i].or_portsc;
		u32 val = xhci_readl(ps);
		if (!(val & PORT_POWER)) {
			val &= XHCI_PORT_RO | XHCI_PORT_RWS;
			val |= PORT_POWER;
			xhci_writel(ps, val);
			mdelay(20);
		}
		printf("  Port %d: PORTSC=0x%08x\n", i + 1, xhci_readl(ps));
	}

	return 0;
}

bool xhci_device_connected(void)
{
	return device_connected;
}

bool xhci_device_is_hub(struct usb_device *dev)
{
	return dev && dev->descriptor.bDeviceClass == USB_CLASS_HUB;
}

struct xhci_ctrl *xhci_host_get_ctrl(void)
{
	return &xhci_ctrl_instance;
}

void xhci_host_shutdown(void)
{
	xhci_xfer_forget_device(NULL);
	xhci_deregister_bare(&xhci_ctrl_instance);
}

void xhci_host_get_device_info(struct usb_device *dev, struct xhci_host_device_info *info)
{
	memset(info, 0, sizeof(*info));
	if (!dev)
		return;

	info->vid = le16_to_cpu(dev->descriptor.idVendor);
	info->pid = le16_to_cpu(dev->descriptor.idProduct);
	info->device_class = dev->descriptor.bDeviceClass;
	info->speed = dev->speed;
	info->devnum = dev->devnum;
	for (struct usb_device *p = dev->parent; p && p->parent; p = p->parent)
		info->depth++;
	memcpy(info->manufacturer, dev->mf, sizeof(info->manufacturer) - 1);
	memcpy(info->product, dev->prod, sizeof(info->product) - 1);
}

void xhci_host_set_disconnect_callback(void (*callback)(struct usb_device *dev))
{
	disconnect_callback = callback;
}

int xhci_host_find_interface(struct usb_device *dev, uint8_t intf_class, uint8_t intf_subclass)
{
	for (int i = 0; i < dev->config.no_of_if && i < USB_MAXINTERFACES; i++) {
		struct usb_interface_descriptor *desc = &dev->config.if_desc[i].desc;
		if (desc->bLength && desc->bInterfaceClass == intf_class &&
		    desc->bInterfaceSubClass == intf_subclass)
			return desc->bInterfaceNumber;
	}
	return -1;
}

uint8_t xhci_host_device_speed(struct usb_device *dev)
{
	return dev->speed;
}

int xhci_host_control(struct usb_device *dev, const uint8_t setup[8], void *data)
{
	struct devrequest req;
	unsigned long pipe;
	int ret;

	memcpy(&req, setup, sizeof(req));
	pipe = (req.requesttype & USB_DIR_IN) ? usb_rcvctrlpipe(dev, 0) :
						usb_sndctrlpipe(dev, 0);

	ret = xhci_ctrl_tx(dev, pipe, &req, le16_to_cpu(req.length), data);
	if (ret < 0)
		return ret;
	if (dev->status == USB_ST_STALLED)
		return -EPIPE;
	return dev->act_len;
}

bool xhci_host_device_present(struct usb_device *dev)
{
	for (; dev->parent && dev->parent != root_hub; dev = dev->parent) {
		struct usb_port_status ps;
		if (usb_get_port_status(dev->parent, dev->portnr, &ps) < 0)
			return false;
		if (!(le16_to_cpu(ps.wPortStatus) & USB_PORT_STAT_CONNECTION))
			return false;
	}

	if (dev->portnr < 1 || dev->portnr > max_ports)
		return false;
	return xhci_readl(&xhci_ctrl_instance.hcor->portregs[dev->portnr - 1].or_portsc) & PORT_CONNECT;
}
