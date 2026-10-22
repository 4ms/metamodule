/*
 * usb_ch9.h -- the USB standard descriptors and helpers this library uses (USB 2.0 spec chapter 9,
 * USB 3.2 spec 9.6.7). Written for MetaModule in place of Linux/U-Boot's <linux/usb/ch9.h>; the
 * other chapter 9 constants are in usb_defs.h.
 */
#ifndef USB_CH9_H
#define USB_CH9_H

#include <linux/compiler.h>
#include <linux/types.h>
#include <usb_defs.h>

/* Ordered by speed: the code compares them */
enum usb_device_speed {
	USB_SPEED_UNKNOWN = 0,
	USB_SPEED_LOW,
	USB_SPEED_FULL,
	USB_SPEED_HIGH,
	USB_SPEED_WIRELESS,
	USB_SPEED_SUPER,
	USB_SPEED_SUPER_PLUS,
};

#define USB_TYPE_MASK		(0x03 << 5)

/* bmAttributes of an endpoint descriptor: bits 12:11 of wMaxPacketSize are extra transactions */
#define USB_ENDPOINT_MAXP_MASK	0x07ff
#define USB_EP_MAXP_MULT_SHIFT	11
#define USB_EP_MAXP_MULT_MASK	(3 << USB_EP_MAXP_MULT_SHIFT)

struct usb_device_descriptor {
	__u8 bLength;
	__u8 bDescriptorType;
	__le16 bcdUSB;
	__u8 bDeviceClass;
	__u8 bDeviceSubClass;
	__u8 bDeviceProtocol;
	__u8 bMaxPacketSize0;
	__le16 idVendor;
	__le16 idProduct;
	__le16 bcdDevice;
	__u8 iManufacturer;
	__u8 iProduct;
	__u8 iSerialNumber;
	__u8 bNumConfigurations;
} __attribute__((packed));

struct usb_config_descriptor {
	__u8 bLength;
	__u8 bDescriptorType;
	__le16 wTotalLength;
	__u8 bNumInterfaces;
	__u8 bConfigurationValue;
	__u8 iConfiguration;
	__u8 bmAttributes;
	__u8 bMaxPower;
} __attribute__((packed));

struct usb_interface_descriptor {
	__u8 bLength;
	__u8 bDescriptorType;
	__u8 bInterfaceNumber;
	__u8 bAlternateSetting;
	__u8 bNumEndpoints;
	__u8 bInterfaceClass;
	__u8 bInterfaceSubClass;
	__u8 bInterfaceProtocol;
	__u8 iInterface;
} __attribute__((packed));

/* 7 bytes on the wire; audio-class endpoints add bRefresh and bSynchAddress */
struct usb_endpoint_descriptor {
	__u8 bLength;
	__u8 bDescriptorType;
	__u8 bEndpointAddress;
	__u8 bmAttributes;
	__le16 wMaxPacketSize;
	__u8 bInterval;
	__u8 bRefresh;
	__u8 bSynchAddress;
} __attribute__((packed));

/* SuperSpeed endpoint companion */
struct usb_ss_ep_comp_descriptor {
	__u8 bLength;
	__u8 bDescriptorType;
	__u8 bMaxBurst;
	__u8 bmAttributes;
	__le16 wBytesPerInterval;
} __attribute__((packed));

static inline int usb_endpoint_num(const struct usb_endpoint_descriptor *epd)
{
	return epd->bEndpointAddress & USB_ENDPOINT_NUMBER_MASK;
}

static inline int usb_endpoint_type(const struct usb_endpoint_descriptor *epd)
{
	return epd->bmAttributes & USB_ENDPOINT_XFERTYPE_MASK;
}

static inline int usb_endpoint_dir_in(const struct usb_endpoint_descriptor *epd)
{
	return (epd->bEndpointAddress & USB_ENDPOINT_DIR_MASK) == USB_DIR_IN;
}

static inline int usb_endpoint_dir_out(const struct usb_endpoint_descriptor *epd)
{
	return (epd->bEndpointAddress & USB_ENDPOINT_DIR_MASK) == USB_DIR_OUT;
}

static inline int usb_endpoint_xfer_control(const struct usb_endpoint_descriptor *epd)
{
	return usb_endpoint_type(epd) == USB_ENDPOINT_XFER_CONTROL;
}

static inline int usb_endpoint_xfer_bulk(const struct usb_endpoint_descriptor *epd)
{
	return usb_endpoint_type(epd) == USB_ENDPOINT_XFER_BULK;
}

static inline int usb_endpoint_xfer_int(const struct usb_endpoint_descriptor *epd)
{
	return usb_endpoint_type(epd) == USB_ENDPOINT_XFER_INT;
}

static inline int usb_endpoint_xfer_isoc(const struct usb_endpoint_descriptor *epd)
{
	return usb_endpoint_type(epd) == USB_ENDPOINT_XFER_ISOC;
}

/* Max packet size, without the high-bandwidth bits */
static inline int usb_endpoint_maxp(const struct usb_endpoint_descriptor *epd)
{
	return le16_to_cpu(epd->wMaxPacketSize) & USB_ENDPOINT_MAXP_MASK;
}

/* Transactions per microframe (1 to 3), for high-bandwidth endpoints */
static inline int usb_endpoint_maxp_mult(const struct usb_endpoint_descriptor *epd)
{
	return ((le16_to_cpu(epd->wMaxPacketSize) & USB_EP_MAXP_MULT_MASK) >> USB_EP_MAXP_MULT_SHIFT) + 1;
}

#endif /* USB_CH9_H */
