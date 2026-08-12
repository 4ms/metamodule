/**
 ******************************************************************************
 * @file    usbd_composite_desc.c
 * @brief   Device and string descriptors for the composite (MIDI + Console)
 *          device mode.
 *
 *          bDeviceClass is Miscellaneous / Common Class / Interface Association
 *          Descriptor, which is what tells a host to read the IADs in the
 *          configuration descriptor and group the four interfaces into two
 *          functions. A CDC-class device descriptor (as the console-only mode
 *          used) would make Windows bind the whole device to the CDC driver.
 ******************************************************************************
 */

#include "usbd_conf.h"
#include "usbd_core.h"
#include "usbd_def.h"

#define USB_SIZ_STRING_SERIAL 0x1A

#define USBD_VID 0x0483
/* Distinct from the single-class PIDs (CDC 0x5740, UVC 0x5741, MIDI 0x5742):
 * hosts cache descriptors per VID/PID, so a device that enumerates differently
 * must not reuse one. */
#define USBD_PID 0x5743
#define USBD_LANGID_STRING 0x409
#define USBD_MANUFACTURER_STRING "4ms Company"
#define USBD_PRODUCT_STRING "MetaModule"
#define USBD_CONFIGURATION_STRING "MetaModule Config"
#define USBD_INTERFACE_STRING "MetaModule Interface"

/* Per-function names, referenced by iFunction/iInterface in the composite
 * configuration descriptor (see CMPSIT_STR_IDX_* in usbd_composite.c). These
 * are what a host shows for the serial port and the MIDI port. */
#define USBD_CDC_FUNCTION_STRING "MetaModule Console"
#define USBD_MIDI_FUNCTION_STRING "MetaModule MIDI"
#define CMPSIT_STR_IDX_CDC 0x06U
#define CMPSIT_STR_IDX_MIDI 0x07U

static uint8_t *CMPSIT_DeviceDescriptor(USBD_SpeedTypeDef speed, uint16_t *length);
static uint8_t *CMPSIT_LangIDStrDescriptor(USBD_SpeedTypeDef speed, uint16_t *length);
static uint8_t *CMPSIT_ManufacturerStrDescriptor(USBD_SpeedTypeDef speed, uint16_t *length);
static uint8_t *CMPSIT_ProductStrDescriptor(USBD_SpeedTypeDef speed, uint16_t *length);
static uint8_t *CMPSIT_SerialStrDescriptor(USBD_SpeedTypeDef speed, uint16_t *length);
static uint8_t *CMPSIT_ConfigStrDescriptor(USBD_SpeedTypeDef speed, uint16_t *length);
static uint8_t *CMPSIT_InterfaceStrDescriptor(USBD_SpeedTypeDef speed, uint16_t *length);
static uint8_t *CMPSIT_UserStrDescriptor(USBD_SpeedTypeDef speed, uint8_t idx, uint16_t *length);

USBD_DescriptorsTypeDef CMPSIT_Desc = {
	CMPSIT_DeviceDescriptor,
	CMPSIT_LangIDStrDescriptor,
	CMPSIT_ManufacturerStrDescriptor,
	CMPSIT_ProductStrDescriptor,
	CMPSIT_SerialStrDescriptor,
	CMPSIT_ConfigStrDescriptor,
	CMPSIT_InterfaceStrDescriptor,
#if (USBD_CLASS_USER_STRING_DESC == 1)
	CMPSIT_UserStrDescriptor,
#endif
};

__ALIGN_BEGIN static uint8_t USBD_CMPSIT_DeviceDesc[USB_LEN_DEV_DESC] __ALIGN_END = {
	0x12,				  /* bLength */
	USB_DESC_TYPE_DEVICE, /* bDescriptorType */
	0x00, 0x02,			  /* bcdUSB: USB 2.0 */
	0xEF,				  /* bDeviceClass: Miscellaneous */
	0x02,				  /* bDeviceSubClass: Common Class */
	0x01,				  /* bDeviceProtocol: Interface Association Descriptor */
	USB_MAX_EP0_SIZE,	  /* bMaxPacketSize0 */
	LOBYTE(USBD_VID), HIBYTE(USBD_VID),
	LOBYTE(USBD_PID), HIBYTE(USBD_PID),
	0x00, 0x02, /* bcdDevice: 2.00 */
	USBD_IDX_MFC_STR,
	USBD_IDX_PRODUCT_STR,
	USBD_IDX_SERIAL_STR,
	USBD_MAX_NUM_CONFIGURATION,
};

__ALIGN_BEGIN static uint8_t USBD_CMPSIT_LangIDDesc[USB_LEN_LANGID_STR_DESC] __ALIGN_END = {
	USB_LEN_LANGID_STR_DESC,
	USB_DESC_TYPE_STRING,
	LOBYTE(USBD_LANGID_STRING),
	HIBYTE(USBD_LANGID_STRING),
};

__ALIGN_BEGIN static uint8_t USBD_CMPSIT_StringSerial[USB_SIZ_STRING_SERIAL] __ALIGN_END = {
	USB_SIZ_STRING_SERIAL,
	USB_DESC_TYPE_STRING,
};

__ALIGN_BEGIN static uint8_t USBD_CMPSIT_StrDesc[USBD_MAX_STR_DESC_SIZ] __ALIGN_END;

static void IntToUnicode(uint32_t value, uint8_t *pbuf, uint8_t len) {
	for (uint8_t idx = 0; idx < len; idx++) {
		if (((value >> 28)) < 0xA)
			pbuf[2 * idx] = (value >> 28) + '0';
		else
			pbuf[2 * idx] = (value >> 28) + 'A' - 10;
		value = value << 4;
		pbuf[2 * idx + 1] = 0;
	}
}

/* TODO: derive from the MPU unique ID. A fixed serial is tolerable for CDC and
 * MIDI but Windows keys removable-media handling off it, so this needs to be
 * real before the developer-mode MSC drive ships. Kept identical to the
 * single-class modes for now. */
static void Get_SerialNum(void) {
	uint32_t deviceserial0 = 5;
	uint32_t deviceserial1 = 6;
	uint32_t deviceserial2 = 7;
	deviceserial0 += deviceserial2;
	if (deviceserial0 != 0) {
		IntToUnicode(deviceserial0, &USBD_CMPSIT_StringSerial[2], 8);
		IntToUnicode(deviceserial1, &USBD_CMPSIT_StringSerial[18], 4);
	}
}

static uint8_t *CMPSIT_DeviceDescriptor(USBD_SpeedTypeDef speed, uint16_t *length) {
	(void)speed;
	*length = sizeof(USBD_CMPSIT_DeviceDesc);
	return USBD_CMPSIT_DeviceDesc;
}

static uint8_t *CMPSIT_LangIDStrDescriptor(USBD_SpeedTypeDef speed, uint16_t *length) {
	(void)speed;
	*length = sizeof(USBD_CMPSIT_LangIDDesc);
	return USBD_CMPSIT_LangIDDesc;
}

static uint8_t *CMPSIT_ManufacturerStrDescriptor(USBD_SpeedTypeDef speed, uint16_t *length) {
	(void)speed;
	USBD_GetString((uint8_t *)USBD_MANUFACTURER_STRING, USBD_CMPSIT_StrDesc, length);
	return USBD_CMPSIT_StrDesc;
}

static uint8_t *CMPSIT_ProductStrDescriptor(USBD_SpeedTypeDef speed, uint16_t *length) {
	(void)speed;
	USBD_GetString((uint8_t *)USBD_PRODUCT_STRING, USBD_CMPSIT_StrDesc, length);
	return USBD_CMPSIT_StrDesc;
}

static uint8_t *CMPSIT_SerialStrDescriptor(USBD_SpeedTypeDef speed, uint16_t *length) {
	(void)speed;
	*length = USB_SIZ_STRING_SERIAL;
	Get_SerialNum();
	return USBD_CMPSIT_StringSerial;
}

static uint8_t *CMPSIT_ConfigStrDescriptor(USBD_SpeedTypeDef speed, uint16_t *length) {
	(void)speed;
	USBD_GetString((uint8_t *)USBD_CONFIGURATION_STRING, USBD_CMPSIT_StrDesc, length);
	return USBD_CMPSIT_StrDesc;
}

static uint8_t *CMPSIT_InterfaceStrDescriptor(USBD_SpeedTypeDef speed, uint16_t *length) {
	(void)speed;
	USBD_GetString((uint8_t *)USBD_INTERFACE_STRING, USBD_CMPSIT_StrDesc, length);
	return USBD_CMPSIT_StrDesc;
}

static uint8_t *CMPSIT_UserStrDescriptor(USBD_SpeedTypeDef speed, uint8_t idx, uint16_t *length) {
	(void)speed;

	switch (idx) {
		case CMPSIT_STR_IDX_CDC:
			USBD_GetString((uint8_t *)USBD_CDC_FUNCTION_STRING, USBD_CMPSIT_StrDesc, length);
			return USBD_CMPSIT_StrDesc;

		case CMPSIT_STR_IDX_MIDI:
			USBD_GetString((uint8_t *)USBD_MIDI_FUNCTION_STRING, USBD_CMPSIT_StrDesc, length);
			return USBD_CMPSIT_StrDesc;

		default:
			*length = 0;
			return NULL;
	}
}
