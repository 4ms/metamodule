/* Bare-metal shim for U-Boot's <usb.h> (host-mode structures) */
#ifndef _USB_H_
#define _USB_H_

#include <usb_ch9.h>
#include <linux/types.h>
#include <linux/kernel.h>
#include <usb_defs.h>

/* ulong typedef if not already defined */
#ifndef __ULONG_DEFINED
typedef unsigned long ulong;
#define __ULONG_DEFINED
#endif

/* DMA alignment */
#ifndef ARCH_DMA_MINALIGN
#define ARCH_DMA_MINALIGN	64
#endif

#define USB_DMA_MINALIGN	ARCH_DMA_MINALIGN

#define USB_ALTSETTINGALLOC	4
#define USB_MAXALTSETTING	128
#define USB_MAX_DEVICE		32
#define USB_MAXCONFIG		8
#define USB_MAXINTERFACES	8
#define USB_MAXENDPOINTS	16
#define USB_MAXCHILDREN		8
#define USB_MAX_HUB		16

#define USB_CNTL_TIMEOUT	100 /* ms */
#define USB_TIMEOUT_MS(pipe)	(usb_pipebulk(pipe) ? 5000 : 1000)
#define USB_RESUME_TIMEOUT	40 /* ms */

/* Device request (setup) */
struct devrequest {
	__u8	requesttype;
	__u8	request;
	__le16	value;
	__le16	index;
	__le16	length;
} __attribute__ ((packed));

/* Interface */
struct usb_interface {
	struct usb_interface_descriptor desc;
	__u8	no_of_ep;
	__u8	num_altsetting;
	__u8	act_altsetting;
	struct usb_endpoint_descriptor ep_desc[USB_MAXENDPOINTS];
	struct usb_ss_ep_comp_descriptor ss_ep_comp_desc[USB_MAXENDPOINTS];
} __attribute__ ((packed));

/* Configuration */
struct usb_config {
	struct usb_config_descriptor desc;
	__u8	no_of_if;
	struct usb_interface if_desc[USB_MAXINTERFACES];
} __attribute__ ((packed));

enum {
	PACKET_SIZE_8   = 0,
	PACKET_SIZE_16  = 1,
	PACKET_SIZE_32  = 2,
	PACKET_SIZE_64  = 3,
};

/* USB device — non-DM version (CONFIG_IS_ENABLED(DM_USB) = 0) */
struct usb_device {
	int	devnum;
	enum usb_device_speed speed;
	char	mf[32];
	char	prod[32];
	char	serial[32];

	int maxpacketsize;
	unsigned int toggle[2];
	unsigned int halted[2];
	int epmaxpacketin[16];
	int epmaxpacketout[16];

	int configno;
	struct usb_device_descriptor descriptor
		__attribute__((aligned(ARCH_DMA_MINALIGN)));
	struct usb_config config;

	int have_langid;
	int string_langid;
	int (*irq_handle)(struct usb_device *dev);
	unsigned long irq_status;
	int irq_act_len;
	void *privptr;

	unsigned long status;
	unsigned long int_pending;
	int act_len;
	int maxchild;
	int portnr;

	/* non-DM fields */
	struct usb_device *parent;
	struct usb_device *children[USB_MAXCHILDREN];
	void *controller;

	unsigned int slot_id;
};

struct int_queue;

enum usb_init_type {
	USB_INIT_HOST,
	USB_INIT_DEVICE,
	USB_INIT_UNKNOWN,
};

/* Stub declarations — bare-metal doesn't use U-Boot's USB core */
static inline int usb_lowlevel_init(int index, enum usb_init_type init, void **controller) { return 0; }
static inline int usb_lowlevel_stop(int index) { return 0; }

#define usb_reset_root_port(dev)

int submit_bulk_msg(struct usb_device *dev, unsigned long pipe,
		    void *buffer, int transfer_len);
int submit_control_msg(struct usb_device *dev, unsigned long pipe,
		       void *buffer, int transfer_len,
		       struct devrequest *setup);
int submit_int_msg(struct usb_device *dev, unsigned long pipe,
		   void *buffer, int transfer_len, int interval,
		   bool nonblock);

/* Pipe encoding macros */
#define create_pipe(dev, endpoint) \
	(((dev)->devnum << 8) | ((endpoint) << 15) | (dev)->maxpacketsize)
#define default_pipe(dev) ((dev)->speed << 26)

#define usb_sndctrlpipe(dev, endpoint)	((PIPE_CONTROL << 30) | create_pipe(dev, endpoint))
#define usb_rcvctrlpipe(dev, endpoint)	((PIPE_CONTROL << 30) | create_pipe(dev, endpoint) | USB_DIR_IN)
#define usb_sndbulkpipe(dev, endpoint)	((PIPE_BULK << 30) | create_pipe(dev, endpoint))
#define usb_rcvbulkpipe(dev, endpoint)	((PIPE_BULK << 30) | create_pipe(dev, endpoint) | USB_DIR_IN)
#define usb_sndintpipe(dev, endpoint)	((PIPE_INTERRUPT << 30) | create_pipe(dev, endpoint))
#define usb_rcvintpipe(dev, endpoint)	((PIPE_INTERRUPT << 30) | create_pipe(dev, endpoint) | USB_DIR_IN)
#define usb_snddefctrl(dev)		((PIPE_CONTROL << 30) | default_pipe(dev))
#define usb_rcvdefctrl(dev)		((PIPE_CONTROL << 30) | default_pipe(dev) | USB_DIR_IN)
#define usb_sndisocpipe(dev, endpoint)	((PIPE_ISOCHRONOUS << 30) | create_pipe(dev, endpoint))
#define usb_rcvisocpipe(dev, endpoint)	((PIPE_ISOCHRONOUS << 30) | create_pipe(dev, endpoint) | USB_DIR_IN)

#define usb_gettoggle(dev, ep, out)	(((dev)->toggle[out] >> ep) & 1)
#define usb_dotoggle(dev, ep, out)	((dev)->toggle[out] ^= (1 << ep))
#define usb_settoggle(dev, ep, out, bit) \
	((dev)->toggle[out] = ((dev)->toggle[out] & ~(1 << ep)) | ((bit) << ep))

#define usb_endpoint_out(ep_dir)	(((ep_dir >> 7) & 1) ^ 1)
#define usb_endpoint_halt(dev, ep, out)		((dev)->halted[out] |= (1 << (ep)))
#define usb_endpoint_running(dev, ep, out)	((dev)->halted[out] &= ~(1 << (ep)))
#define usb_endpoint_halted(dev, ep, out)	((dev)->halted[out] & (1 << (ep)))

#define usb_packetid(pipe)	(((pipe) & USB_DIR_IN) ? USB_PID_IN : USB_PID_OUT)

#define usb_pipeout(pipe)	((((pipe) >> 7) & 1) ^ 1)
#define usb_pipein(pipe)	(((pipe) >> 7) & 1)
#define usb_pipedevice(pipe)	(((pipe) >> 8) & 0x7f)
#define usb_pipe_endpdev(pipe)	(((pipe) >> 8) & 0x7ff)
#define usb_pipeendpoint(pipe)	(((pipe) >> 15) & 0xf)
#define usb_pipedata(pipe)	(((pipe) >> 19) & 1)
#define usb_pipetype(pipe)	(((pipe) >> 30) & 3)
#define usb_pipeisoc(pipe)	(usb_pipetype((pipe)) == PIPE_ISOCHRONOUS)
#define usb_pipeint(pipe)	(usb_pipetype((pipe)) == PIPE_INTERRUPT)
#define usb_pipecontrol(pipe)	(usb_pipetype((pipe)) == PIPE_CONTROL)
#define usb_pipebulk(pipe)	(usb_pipetype((pipe)) == PIPE_BULK)

#define usb_pipe_ep_index(pipe)	\
	usb_pipecontrol(pipe) ? (usb_pipeendpoint(pipe) * 2) : \
		((usb_pipeendpoint(pipe) * 2) - (usb_pipein(pipe) ? 0 : 1))

/* Swap macros — little-endian ARM needs no swap */
#define swap_16(x) (x)
#define swap_32(x) (x)

/* Hub structures */
struct usb_port_status {
	unsigned short wPortStatus;
	unsigned short wPortChange;
} __attribute__ ((packed));

struct usb_hub_status {
	unsigned short wHubStatus;
	unsigned short wHubChange;
} __attribute__ ((packed));

#define USB_HUB_PR_FS		0
#define USB_HUB_PR_HS_NO_TT	0
#define USB_HUB_PR_HS_SINGLE_TT 1
#define USB_HUB_PR_HS_MULTI_TT	2
#define USB_HUB_PR_SS		3

#define HUB_TTTT_8_BITS		0x00
#define HUB_TTTT_16_BITS	0x20
#define HUB_TTTT_24_BITS	0x40
#define HUB_TTTT_32_BITS	0x60

struct usb_hub_descriptor {
	unsigned char  bLength;
	unsigned char  bDescriptorType;
	unsigned char  bNbrPorts;
	unsigned short wHubCharacteristics;
	unsigned char  bPwrOn2PwrGood;
	unsigned char  bHubContrCurrent;
	union {
		struct {
			__u8 DeviceRemovable[(USB_MAXCHILDREN + 1 + 7) / 8];
			__u8 PortPowerCtrlMask[(USB_MAXCHILDREN + 1 + 7) / 8];
		} __attribute__ ((packed)) hs;
		struct {
			__u8 bHubHdrDecLat;
			__le16 wHubDelay;
			__le16 DeviceRemovable;
		} __attribute__ ((packed)) ss;
	} u;
} __attribute__ ((packed));

struct usb_hub_device {
	struct usb_device *pusb_dev;
	struct usb_hub_descriptor desc;
	ulong connect_timeout;
	ulong query_delay;
	int overcurrent_count[USB_MAXCHILDREN];
	int hub_depth;
	struct usb_tt tt;
};

/* Non-DM function declarations used by xHCI */
struct usb_device *usb_get_dev_index(int index);
int usb_alloc_new_device(void *controller, struct usb_device **devp);
int usb_new_device(struct usb_device *dev);
int usb_alloc_device(struct usb_device *dev);
int usb_update_hub_device(struct usb_device *dev);
int usb_get_max_xfer_size(struct usb_device *dev, size_t *size);
bool usb_device_has_child_on_port(struct usb_device *parent, int port);
int usb_hub_probe(struct usb_device *dev, int ifnum);
void usb_hub_reset(void);
void usb_find_usb2_hub_address_port(struct usb_device *udev,
				    uint8_t *hub_address, uint8_t *hub_port);
int usb_control_msg(struct usb_device *dev, unsigned int pipe,
		    unsigned char request, unsigned char requesttype,
		    unsigned short value, unsigned short index,
		    void *data, unsigned short size, int timeout);
int usb_maxpacket(struct usb_device *dev, unsigned long pipe);
int usb_set_interface(struct usb_device *dev, int interface, int alternate);
int usb_get_port_status(struct usb_device *dev, int port, void *data);

#endif /* _USB_H_ */
