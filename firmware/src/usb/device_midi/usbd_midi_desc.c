/**
 ******************************************************************************
 * @file    usbd_midi_desc.c
 * @brief   USB device descriptor + string descriptors for MIDI device mode.
 *          Mirrors usbd_video_desc.c; class is defined at the interface level
 *          (bDeviceClass = 0), so the device descriptor itself is class-agnostic.
 ******************************************************************************
 */

#include "usbd_conf.h"
#include "usbd_core.h"
#include "usbd_def.h"

#define USB_SIZ_STRING_SERIAL 0x1A

#define USBD_VID 0x0483
#define USBD_PID 0x5742 /* distinct from CDC/UVC PIDs */
#define USBD_LANGID_STRING 0x409
#define USBD_MANUFACTURER_STRING "4ms Company"
#define USBD_PRODUCT_STRING "MetaModule MIDI"
#define USBD_CONFIGURATION_STRING "MIDI Config"
#define USBD_INTERFACE_STRING "MIDI Streaming"

static uint8_t *MIDI_DeviceDescriptor(USBD_SpeedTypeDef speed, uint16_t *length);
static uint8_t *MIDI_LangIDStrDescriptor(USBD_SpeedTypeDef speed, uint16_t *length);
static uint8_t *MIDI_ManufacturerStrDescriptor(USBD_SpeedTypeDef speed, uint16_t *length);
static uint8_t *MIDI_ProductStrDescriptor(USBD_SpeedTypeDef speed, uint16_t *length);
static uint8_t *MIDI_SerialStrDescriptor(USBD_SpeedTypeDef speed, uint16_t *length);
static uint8_t *MIDI_ConfigStrDescriptor(USBD_SpeedTypeDef speed, uint16_t *length);
static uint8_t *MIDI_InterfaceStrDescriptor(USBD_SpeedTypeDef speed, uint16_t *length);

USBD_DescriptorsTypeDef MIDI_Desc = {
	MIDI_DeviceDescriptor,
	MIDI_LangIDStrDescriptor,
	MIDI_ManufacturerStrDescriptor,
	MIDI_ProductStrDescriptor,
	MIDI_SerialStrDescriptor,
	MIDI_ConfigStrDescriptor,
	MIDI_InterfaceStrDescriptor,
};

__ALIGN_BEGIN static uint8_t USBD_MIDI_DeviceDesc[USB_LEN_DEV_DESC] __ALIGN_END = {
	0x12,                 /* bLength */
	USB_DESC_TYPE_DEVICE, /* bDescriptorType */
	0x00, 0x02,           /* bcdUSB: USB 2.0 */
	0x00,                 /* bDeviceClass: defined at interface level */
	0x00,                 /* bDeviceSubClass */
	0x00,                 /* bDeviceProtocol */
	USB_MAX_EP0_SIZE,     /* bMaxPacketSize0 */
	LOBYTE(USBD_VID), HIBYTE(USBD_VID),
	LOBYTE(USBD_PID), HIBYTE(USBD_PID),
	0x00, 0x02,           /* bcdDevice: 2.00 */
	USBD_IDX_MFC_STR,
	USBD_IDX_PRODUCT_STR,
	USBD_IDX_SERIAL_STR,
	USBD_MAX_NUM_CONFIGURATION,
};

__ALIGN_BEGIN static uint8_t USBD_MIDI_LangIDDesc[USB_LEN_LANGID_STR_DESC] __ALIGN_END = {
	USB_LEN_LANGID_STR_DESC,
	USB_DESC_TYPE_STRING,
	LOBYTE(USBD_LANGID_STRING),
	HIBYTE(USBD_LANGID_STRING),
};

__ALIGN_BEGIN static uint8_t USBD_MIDI_StringSerial[USB_SIZ_STRING_SERIAL] __ALIGN_END = {
	USB_SIZ_STRING_SERIAL,
	USB_DESC_TYPE_STRING,
};

__ALIGN_BEGIN static uint8_t USBD_MIDI_StrDesc[USBD_MAX_STR_DESC_SIZ] __ALIGN_END;

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

static void Get_SerialNum(void) {
	uint32_t deviceserial0 = 5;
	uint32_t deviceserial1 = 6;
	uint32_t deviceserial2 = 7;
	deviceserial0 += deviceserial2;
	if (deviceserial0 != 0) {
		IntToUnicode(deviceserial0, &USBD_MIDI_StringSerial[2], 8);
		IntToUnicode(deviceserial1, &USBD_MIDI_StringSerial[18], 4);
	}
}

static uint8_t *MIDI_DeviceDescriptor(USBD_SpeedTypeDef speed, uint16_t *length) {
	(void)speed;
	*length = sizeof(USBD_MIDI_DeviceDesc);
	return USBD_MIDI_DeviceDesc;
}

static uint8_t *MIDI_LangIDStrDescriptor(USBD_SpeedTypeDef speed, uint16_t *length) {
	(void)speed;
	*length = sizeof(USBD_MIDI_LangIDDesc);
	return USBD_MIDI_LangIDDesc;
}

static uint8_t *MIDI_ManufacturerStrDescriptor(USBD_SpeedTypeDef speed, uint16_t *length) {
	(void)speed;
	USBD_GetString((uint8_t *)USBD_MANUFACTURER_STRING, USBD_MIDI_StrDesc, length);
	return USBD_MIDI_StrDesc;
}

static uint8_t *MIDI_ProductStrDescriptor(USBD_SpeedTypeDef speed, uint16_t *length) {
	(void)speed;
	USBD_GetString((uint8_t *)USBD_PRODUCT_STRING, USBD_MIDI_StrDesc, length);
	return USBD_MIDI_StrDesc;
}

static uint8_t *MIDI_SerialStrDescriptor(USBD_SpeedTypeDef speed, uint16_t *length) {
	(void)speed;
	*length = USB_SIZ_STRING_SERIAL;
	Get_SerialNum();
	return USBD_MIDI_StringSerial;
}

static uint8_t *MIDI_ConfigStrDescriptor(USBD_SpeedTypeDef speed, uint16_t *length) {
	(void)speed;
	USBD_GetString((uint8_t *)USBD_CONFIGURATION_STRING, USBD_MIDI_StrDesc, length);
	return USBD_MIDI_StrDesc;
}

static uint8_t *MIDI_InterfaceStrDescriptor(USBD_SpeedTypeDef speed, uint16_t *length) {
	(void)speed;
	USBD_GetString((uint8_t *)USBD_INTERFACE_STRING, USBD_MIDI_StrDesc, length);
	return USBD_MIDI_StrDesc;
}
