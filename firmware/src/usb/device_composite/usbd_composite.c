/**
 ******************************************************************************
 * @file    usbd_composite.c
 * @brief   Composite configuration descriptor (CDC ACM + USB-MIDI) and the
 *          USBD_CMPSIT hooks the device core calls in composite builds.
 *          See usbd_composite_builder.h for why ST's builder is not used.
 ******************************************************************************
 */

#include "usbd_composite_builder.h"
#include "device_midi/usbd_midi.h"
#include "usbd_cdc.h"
#include "usbd_conf.h"
#include "usbd_core.h"
#include "usbd_ctlreq.h"
#include "usbd_msc.h"
#include "usbd_video.h"

/* 9 config + [8 IAD + 35 CDC comm + 23 CDC data] + [8 IAD + 18 MIDI AC + 74 MIDI MS] */
#define CMPSIT_CONFIG_DESC_SIZ 175U

/* ... plus [9 MSC interface + 7 + 7 endpoints] when the developer drive is on.
   The MSC descriptors sit at the end of the array so one set of bytes serves
   both configurations: with the drive off we report the shorter length. */
#define CMPSIT_MSC_DESC_SIZ 23U
#define CMPSIT_CONFIG_DESC_SIZ_WITH_DRIVE (CMPSIT_CONFIG_DESC_SIZ + CMPSIT_MSC_DESC_SIZ)

#if (USBD_SELF_POWERED == 1U)
#define CMPSIT_BMATTRIBUTES 0xC0U
#else
#define CMPSIT_BMATTRIBUTES 0x80U
#endif

/* String descriptor indices. 0..5 are reserved by the library (LangID,
 * manufacturer, product, serial, configuration, interface), so our per-function
 * names start at 6 and are served by the GetUserStrDescriptor callback in
 * usbd_composite_desc.c. */
#define CMPSIT_STR_IDX_CDC 0x06U
#define CMPSIT_STR_IDX_MIDI 0x07U
#define CMPSIT_STR_IDX_MSC 0x08U

static UsbCompositeProfile s_profile = UsbCompositeProfile_MidiConsole;
static USBD_HandleTypeDef *s_pdev;

uint8_t CMPSIT_CDC_EpAdd[3] = {CMPSIT_CDC_IN_EP, CMPSIT_CDC_OUT_EP, CMPSIT_CDC_CMD_EP};
uint8_t CMPSIT_MIDI_EpAdd[2] = {CMPSIT_MIDI_IN_EP, CMPSIT_MIDI_OUT_EP};
uint8_t CMPSIT_MSC_EpAdd[2] = {CMPSIT_MSC_IN_EP, CMPSIT_MSC_OUT_EP};
uint8_t CMPSIT_VIDEO_EpAdd[1] = {UVC_IN_EP};

static uint8_t s_drive_enabled;

/* Initialised at full-speed packet sizes; the bulk endpoints and the CDC
 * notification interval are patched in place for high speed, the way ST's own
 * class drivers do it (see USBD_CDC_GetHSCfgDesc). */
__ALIGN_BEGIN static uint8_t USBD_CMPSIT_CfgDesc[] __ALIGN_END = {
	/* ---------------- Configuration descriptor ---------------- */
	0x09,							   /* bLength */
	USB_DESC_TYPE_CONFIGURATION,	   /* bDescriptorType */
	LOBYTE(CMPSIT_CONFIG_DESC_SIZ),	   /* wTotalLength */
	HIBYTE(CMPSIT_CONFIG_DESC_SIZ),	   /**/
	0x04,							   /* bNumInterfaces: CDC(2) + MIDI(2) */
	0x01,							   /* bConfigurationValue */
	0x00,							   /* iConfiguration */
	CMPSIT_BMATTRIBUTES,			   /* bmAttributes */
	USBD_MAX_POWER,					   /* bMaxPower */

	/* ================= Function 1: CDC ACM (console) ================= */
	/* Interface Association Descriptor. Without this a host sees four unrelated
	 * interfaces; Windows in particular needs the IAD to bind usbccgp and hand
	 * IF0+IF1 to the CDC driver as one function. */
	0x08,							   /* bLength */
	USB_DESC_TYPE_IAD,				   /* bDescriptorType: IAD */
	CMPSIT_IF_CDC_COMM,				   /* bFirstInterface */
	0x02,							   /* bInterfaceCount */
	0x02,							   /* bFunctionClass: Communications */
	0x02,							   /* bFunctionSubClass: Abstract Control Model */
	0x01,							   /* bFunctionProtocol: AT commands */
	CMPSIT_STR_IDX_CDC,				   /* iFunction */

	/* Communication interface */
	0x09,							   /* bLength */
	USB_DESC_TYPE_INTERFACE,		   /* bDescriptorType */
	CMPSIT_IF_CDC_COMM,				   /* bInterfaceNumber */
	0x00,							   /* bAlternateSetting */
	0x01,							   /* bNumEndpoints */
	0x02,							   /* bInterfaceClass: Communications */
	0x02,							   /* bInterfaceSubClass: ACM */
	0x01,							   /* bInterfaceProtocol: AT commands */
	CMPSIT_STR_IDX_CDC,				   /* iInterface */

	/* Header Functional Descriptor */
	0x05, 0x24, 0x00, 0x10, 0x01,
	/* Call Management Functional Descriptor: no call mgmt, data on IF1 */
	0x05, 0x24, 0x01, 0x00, CMPSIT_IF_CDC_DATA,
	/* ACM Functional Descriptor: supports line coding + serial state */
	0x04, 0x24, 0x02, 0x02,
	/* Union Functional Descriptor: master IF0, slave IF1 */
	0x05, 0x24, 0x06, CMPSIT_IF_CDC_COMM, CMPSIT_IF_CDC_DATA,

	/* Notification endpoint */
	0x07,							   /* bLength */
	USB_DESC_TYPE_ENDPOINT,			   /* bDescriptorType */
	CMPSIT_CDC_CMD_EP,				   /* bEndpointAddress */
	0x03,							   /* bmAttributes: interrupt */
	LOBYTE(CDC_CMD_PACKET_SIZE),	   /* wMaxPacketSize */
	HIBYTE(CDC_CMD_PACKET_SIZE),	   /**/
	CDC_FS_BINTERVAL,				   /* bInterval (patched for HS) */

	/* Data interface */
	0x09,							   /* bLength */
	USB_DESC_TYPE_INTERFACE,		   /* bDescriptorType */
	CMPSIT_IF_CDC_DATA,				   /* bInterfaceNumber */
	0x00,							   /* bAlternateSetting */
	0x02,							   /* bNumEndpoints */
	0x0A,							   /* bInterfaceClass: CDC Data */
	0x00,							   /* bInterfaceSubClass */
	0x00,							   /* bInterfaceProtocol */
	0x00,							   /* iInterface */

	/* Bulk OUT */
	0x07, USB_DESC_TYPE_ENDPOINT, CMPSIT_CDC_OUT_EP, 0x02,
	LOBYTE(CDC_DATA_FS_MAX_PACKET_SIZE), HIBYTE(CDC_DATA_FS_MAX_PACKET_SIZE), 0x00,
	/* Bulk IN */
	0x07, USB_DESC_TYPE_ENDPOINT, CMPSIT_CDC_IN_EP, 0x02,
	LOBYTE(CDC_DATA_FS_MAX_PACKET_SIZE), HIBYTE(CDC_DATA_FS_MAX_PACKET_SIZE), 0x00,

	/* ================= Function 2: USB-MIDI 1.0 ================= */
	/* Topology (1 cable), same as the standalone MIDI descriptor:
	 *   Bulk OUT -> Embedded MIDI IN  Jack (1) -> External MIDI OUT Jack (4)
	 *   Bulk IN  <- Embedded MIDI OUT Jack (3) <- External MIDI IN  Jack (2) */
	0x08,							   /* bLength */
	USB_DESC_TYPE_IAD,				   /* bDescriptorType: IAD */
	CMPSIT_IF_MIDI_AC,				   /* bFirstInterface */
	0x02,							   /* bInterfaceCount */
	0x01,							   /* bFunctionClass: Audio */
	0x01,							   /* bFunctionSubClass: AudioControl */
	0x00,							   /* bFunctionProtocol */
	CMPSIT_STR_IDX_MIDI,			   /* iFunction */

	/* Standard AudioControl interface (no endpoints) */
	0x09, USB_DESC_TYPE_INTERFACE, CMPSIT_IF_MIDI_AC, 0x00, 0x00, 0x01, 0x01, 0x00, CMPSIT_STR_IDX_MIDI,
	/* Class-specific AC header: bcdADC 1.00, wTotalLength 9, 1 streaming iface */
	0x09, 0x24, 0x01, 0x00, 0x01, 0x09, 0x00, 0x01, CMPSIT_IF_MIDI_MS,

	/* Standard MIDIStreaming interface */
	0x09, USB_DESC_TYPE_INTERFACE, CMPSIT_IF_MIDI_MS, 0x00, 0x02, 0x01, 0x03, 0x00, CMPSIT_STR_IDX_MIDI,
	/* Class-specific MS header (wTotalLength = 7 + jacks = 0x25) */
	0x07, 0x24, 0x01, 0x00, 0x01, 0x25, 0x00,
	/* MIDI IN Jack (Embedded, ID 1) */
	0x06, 0x24, 0x02, 0x01, 0x01, 0x00,
	/* MIDI IN Jack (External, ID 2) */
	0x06, 0x24, 0x02, 0x02, 0x02, 0x00,
	/* MIDI OUT Jack (Embedded, ID 3) <- External IN jack (ID 2) */
	0x09, 0x24, 0x03, 0x01, 0x03, 0x01, 0x02, 0x01, 0x00,
	/* MIDI OUT Jack (External, ID 4) <- Embedded IN jack (ID 1) */
	0x09, 0x24, 0x03, 0x02, 0x04, 0x01, 0x01, 0x01, 0x00,

	/* Standard bulk OUT endpoint. USB-Audio v1.0 endpoint descriptors are 9
	 * bytes (bRefresh + bSynchAddress), not the usual 7. */
	0x09, USB_DESC_TYPE_ENDPOINT, CMPSIT_MIDI_OUT_EP, 0x02,
	LOBYTE(MIDI_DATA_FS_MAX_PACKET_SIZE), HIBYTE(MIDI_DATA_FS_MAX_PACKET_SIZE), 0x00, 0x00, 0x00,
	/* Class-specific MS bulk OUT endpoint: feeds Embedded IN jack 1 */
	0x05, 0x25, 0x01, 0x01, 0x01,
	/* Standard bulk IN endpoint */
	0x09, USB_DESC_TYPE_ENDPOINT, CMPSIT_MIDI_IN_EP, 0x02,
	LOBYTE(MIDI_DATA_FS_MAX_PACKET_SIZE), HIBYTE(MIDI_DATA_FS_MAX_PACKET_SIZE), 0x00, 0x00, 0x00,
	/* Class-specific MS bulk IN endpoint: fed by Embedded OUT jack 3 */
	0x05, 0x25, 0x01, 0x01, 0x03,

	/* ========= Function 3: MSC (developer-mode drive), optional =========
	 * Everything from here on is only reported when the drive is enabled; a
	 * single interface, so no IAD is needed. */
	0x09,					 /* bLength */
	USB_DESC_TYPE_INTERFACE, /* bDescriptorType */
	CMPSIT_IF_MSC,			 /* bInterfaceNumber */
	0x00,					 /* bAlternateSetting */
	0x02,					 /* bNumEndpoints */
	0x08,					 /* bInterfaceClass: Mass Storage */
	0x06,					 /* bInterfaceSubClass: SCSI transparent */
	0x50,					 /* bInterfaceProtocol: Bulk-Only Transport */
	CMPSIT_STR_IDX_MSC,		 /* iInterface */

	/* Bulk IN */
	0x07, USB_DESC_TYPE_ENDPOINT, CMPSIT_MSC_IN_EP, 0x02,
	LOBYTE(MSC_MAX_FS_PACKET), HIBYTE(MSC_MAX_FS_PACKET), 0x00,
	/* Bulk OUT */
	0x07, USB_DESC_TYPE_ENDPOINT, CMPSIT_MSC_OUT_EP, 0x02,
	LOBYTE(MSC_MAX_FS_PACKET), HIBYTE(MSC_MAX_FS_PACKET), 0x00,
};

_Static_assert(sizeof(USBD_CMPSIT_CfgDesc) == CMPSIT_CONFIG_DESC_SIZ_WITH_DRIVE,
			   "composite config descriptor size does not match wTotalLength");

/* USB Standard Device Qualifier Descriptor (high-speed capable) */
__ALIGN_BEGIN static uint8_t USBD_CMPSIT_DeviceQualifierDesc[USB_LEN_DEV_QUALIFIER_DESC] __ALIGN_END = {
	USB_LEN_DEV_QUALIFIER_DESC,
	USB_DESC_TYPE_DEVICE_QUALIFIER,
	0x00,
	0x02,
	0x00,
	0x00,
	0x00,
	0x40,
	0x01,
	0x00,
};

void USBD_CMPSIT_SetDriveEnabled(uint8_t enabled) {
	s_drive_enabled = enabled;
}

uint8_t USBD_CMPSIT_IsDriveEnabled(void) {
	return s_drive_enabled;
}

void USBD_CMPSIT_SelectProfile(UsbCompositeProfile profile) {
	s_profile = profile;
}

UsbCompositeProfile USBD_CMPSIT_GetProfile(void) {
	return s_profile;
}

/* ------------------------------------------------------------------------- */

static void set_ep(USBD_CompositeElementTypeDef *e, uint32_t idx, uint8_t addr, uint8_t type) {
	e->Eps[idx].add = addr;
	e->Eps[idx].type = type;
	e->Eps[idx].is_used = 1U;
	/* .size is a uint8_t and cannot hold a high-speed packet size; nothing in
	 * the core reads it (USBD_CoreGetEPAdd matches on add/type/is_used). */
	e->Eps[idx].size = 0U;
}

uint8_t USBD_CMPSIT_AddClass(USBD_HandleTypeDef *pdev,
							 USBD_ClassTypeDef *pclass,
							 USBD_CompositeClassTypeDef classtype,
							 uint8_t cfgidx) {
	(void)pclass;
	(void)cfgidx;

	if (pdev->classId >= USBD_MAX_SUPPORTED_CLASS)
		return (uint8_t)USBD_FAIL;

	s_pdev = pdev;

	USBD_CompositeElementTypeDef *e = &pdev->tclasslist[pdev->classId];
	e->ClassType = classtype;
	e->ClassId = pdev->classId;
	e->Active = 1U;
	e->CurrPcktSze = 0U;

	switch ((uint32_t)classtype) {
		case CLASS_TYPE_CDC:
			e->NumIf = 2U;
			e->Ifs[0] = CMPSIT_IF_CDC_COMM;
			e->Ifs[1] = CMPSIT_IF_CDC_DATA;
			e->NumEps = 3U;
			set_ep(e, 0U, e->EpAdd[0], USBD_EP_TYPE_BULK); /* data IN  */
			set_ep(e, 1U, e->EpAdd[1], USBD_EP_TYPE_BULK); /* data OUT */
			set_ep(e, 2U, e->EpAdd[2], USBD_EP_TYPE_INTR); /* notifications */
			break;

		case CLASS_TYPE_MIDI:
			e->NumIf = 2U;
			e->Ifs[0] = CMPSIT_IF_MIDI_AC;
			e->Ifs[1] = CMPSIT_IF_MIDI_MS;
			e->NumEps = 2U;
			set_ep(e, 0U, e->EpAdd[0], USBD_EP_TYPE_BULK); /* IN  */
			set_ep(e, 1U, e->EpAdd[1], USBD_EP_TYPE_BULK); /* OUT */
			break;

		case CLASS_TYPE_MSC:
			e->NumIf = 1U;
			e->Ifs[0] = CMPSIT_IF_MSC;
			e->NumEps = 2U;
			set_ep(e, 0U, e->EpAdd[0], USBD_EP_TYPE_BULK); /* IN  */
			set_ep(e, 1U, e->EpAdd[1], USBD_EP_TYPE_BULK); /* OUT */
			break;

		case CLASS_TYPE_VIDEO:
			e->NumIf = 2U;
			e->Ifs[0] = UVC_VC_IF_NUM;
			e->Ifs[1] = UVC_VS_IF_NUM;
			e->NumEps = 1U;
			set_ep(e, 0U, e->EpAdd[0], USBD_EP_TYPE_ISOC);
			break;

		default:
			e->Active = 0U;
			return (uint8_t)USBD_FAIL;
	}

	return (uint8_t)USBD_OK;
}

uint8_t USBD_CMPST_ClearConfDesc(USBD_HandleTypeDef *pdev) {
	(void)pdev;
	return (uint8_t)USBD_OK;
}


/* ------------------------------------------------------------------------- */

/* In the Video profile the single registered class supplies its own
 * descriptors; we are only in the path because the core routes by tclasslist. */
typedef enum { CfgHS, CfgFS, CfgOtherSpeed, CfgQualifier } CfgDescKind;

static uint8_t *video_cfg_desc(CfgDescKind kind, uint16_t *length) {
	uint8_t *(*get)(uint16_t *length) = NULL;

	if ((s_pdev != NULL) && (s_pdev->pClass[0] != NULL)) {
		switch (kind) {
			case CfgHS:
				get = s_pdev->pClass[0]->GetHSConfigDescriptor;
				break;
			case CfgFS:
				get = s_pdev->pClass[0]->GetFSConfigDescriptor;
				break;
			case CfgOtherSpeed:
				get = s_pdev->pClass[0]->GetOtherSpeedConfigDescriptor;
				break;
			case CfgQualifier:
				get = s_pdev->pClass[0]->GetDeviceQualifierDescriptor;
				break;
		}
	}

	if (get != NULL)
		return get(length);

	*length = 0U;
	return NULL;
}

static void set_bulk_mps(uint8_t ep, uint16_t mps) {
	USBD_EpDescTypeDef *desc = USBD_GetEpDesc(USBD_CMPSIT_CfgDesc, ep);
	if (desc != NULL)
		desc->wMaxPacketSize = mps;
}

static uint8_t *cmpsit_cfg_desc(uint16_t *length, uint8_t high_speed) {
	/* The MSC descriptors are physically present in the array either way; the
	   host only learns about them when the drive is on. This has to happen
	   before the endpoint fixups below: USBD_GetEpDesc walks the descriptor
	   using wTotalLength, so with the old (shorter) value in place it would
	   never reach the MSC endpoints and they would keep full-speed packet
	   sizes -- illegal for a high-speed bulk endpoint. */
	const uint16_t total = s_drive_enabled ? CMPSIT_CONFIG_DESC_SIZ_WITH_DRIVE : CMPSIT_CONFIG_DESC_SIZ;
	USBD_CMPSIT_CfgDesc[2] = LOBYTE(total);
	USBD_CMPSIT_CfgDesc[3] = HIBYTE(total);
	USBD_CMPSIT_CfgDesc[4] = s_drive_enabled ? 5U : 4U; /* bNumInterfaces */

	/* Bulk endpoints must report 512 at high speed and 64 at full speed */
	set_bulk_mps(CMPSIT_CDC_IN_EP, high_speed ? CDC_DATA_HS_MAX_PACKET_SIZE : CDC_DATA_FS_MAX_PACKET_SIZE);
	set_bulk_mps(CMPSIT_CDC_OUT_EP, high_speed ? CDC_DATA_HS_MAX_PACKET_SIZE : CDC_DATA_FS_MAX_PACKET_SIZE);
	set_bulk_mps(CMPSIT_MIDI_IN_EP, high_speed ? MIDI_DATA_HS_MAX_PACKET_SIZE : MIDI_DATA_FS_MAX_PACKET_SIZE);
	set_bulk_mps(CMPSIT_MIDI_OUT_EP, high_speed ? MIDI_DATA_HS_MAX_PACKET_SIZE : MIDI_DATA_FS_MAX_PACKET_SIZE);
	set_bulk_mps(CMPSIT_MSC_IN_EP, high_speed ? MSC_MAX_HS_PACKET : MSC_MAX_FS_PACKET);
	set_bulk_mps(CMPSIT_MSC_OUT_EP, high_speed ? MSC_MAX_HS_PACKET : MSC_MAX_FS_PACKET);

	USBD_EpDescTypeDef *cmd = USBD_GetEpDesc(USBD_CMPSIT_CfgDesc, CMPSIT_CDC_CMD_EP);
	if (cmd != NULL)
		cmd->bInterval = high_speed ? CDC_HS_BINTERVAL : CDC_FS_BINTERVAL;

	*length = total;
	return USBD_CMPSIT_CfgDesc;
}

static uint8_t *USBD_CMPSIT_GetHSCfgDesc(uint16_t *length) {
	if (s_profile == UsbCompositeProfile_Video)
		return video_cfg_desc(CfgHS, length);

	return cmpsit_cfg_desc(length, 1U);
}

static uint8_t *USBD_CMPSIT_GetFSCfgDesc(uint16_t *length) {
	if (s_profile == UsbCompositeProfile_Video)
		return video_cfg_desc(CfgFS, length);

	return cmpsit_cfg_desc(length, 0U);
}

static uint8_t *USBD_CMPSIT_GetOtherSpeedCfgDesc(uint16_t *length) {
	if (s_profile == UsbCompositeProfile_Video)
		return video_cfg_desc(CfgOtherSpeed, length);

	/* Describes how we would behave at the other speed. The caller
	 * (USBD_GetDescriptor) overwrites bDescriptorType with OTHER_SPEED. */
	return cmpsit_cfg_desc(length, 0U);
}

static uint8_t *USBD_CMPSIT_GetDeviceQualifierDesc(uint16_t *length) {
	if (s_profile == UsbCompositeProfile_Video)
		return video_cfg_desc(CfgQualifier, length);

	*length = (uint16_t)sizeof(USBD_CMPSIT_DeviceQualifierDesc);
	return USBD_CMPSIT_DeviceQualifierDesc;
}

/* Only the descriptor getters are ever used: USBD_CMPSIT is not registered as a
 * class, the core reaches it directly for GET_DESCRIPTOR. */
USBD_ClassTypeDef USBD_CMPSIT = {
	NULL, /* Init */
	NULL, /* DeInit */
	NULL, /* Setup */
	NULL, /* EP0_TxSent */
	NULL, /* EP0_RxReady */
	NULL, /* DataIn */
	NULL, /* DataOut */
	NULL, /* SOF */
	NULL, /* IsoINIncomplete */
	NULL, /* IsoOUTIncomplete */
	USBD_CMPSIT_GetHSCfgDesc,
	USBD_CMPSIT_GetFSCfgDesc,
	USBD_CMPSIT_GetOtherSpeedCfgDesc,
	USBD_CMPSIT_GetDeviceQualifierDesc,
#if (USBD_SUPPORT_USER_STRING_DESC == 1U)
	NULL,
#endif
};
