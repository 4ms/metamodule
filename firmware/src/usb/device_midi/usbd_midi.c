/**
 ******************************************************************************
 * @file    usbd_midi.c
 * @brief   USB-MIDI 1.0 device class driver.
 *
 * Topology (USB-MIDI 1.0 spec, Appendix B reference example, 1 cable):
 *   Bulk OUT EP -> Embedded MIDI IN  Jack (ID 1) -> External MIDI OUT Jack (ID 4)
 *   Bulk IN  EP <- Embedded MIDI OUT Jack (ID 3) <- External MIDI IN  Jack (ID 2)
 *
 * Modeled on usbd_cdc.c (bulk IN/OUT + RegisterInterface). Class-specific
 * requests are not used by basic MIDI, so Setup() only handles standard ones.
 ******************************************************************************
 */

#include "usbd_midi.h"
#include "usbd_ctlreq.h"

static uint8_t USBD_MIDI_Init(USBD_HandleTypeDef *pdev, uint8_t cfgidx);
static uint8_t USBD_MIDI_DeInit(USBD_HandleTypeDef *pdev, uint8_t cfgidx);
static uint8_t USBD_MIDI_Setup(USBD_HandleTypeDef *pdev, USBD_SetupReqTypedef *req);
static uint8_t USBD_MIDI_DataIn(USBD_HandleTypeDef *pdev, uint8_t epnum);
static uint8_t USBD_MIDI_DataOut(USBD_HandleTypeDef *pdev, uint8_t epnum);
static uint8_t *USBD_MIDI_GetHSCfgDesc(uint16_t *length);
static uint8_t *USBD_MIDI_GetFSCfgDesc(uint16_t *length);
static uint8_t *USBD_MIDI_GetOtherSpeedCfgDesc(uint16_t *length);
static uint8_t *USBD_MIDI_GetDeviceQualifierDesc(uint16_t *length);

USBD_ClassTypeDef USBD_MIDI = {
	USBD_MIDI_Init,
	USBD_MIDI_DeInit,
	USBD_MIDI_Setup,
	NULL, /* EP0_TxSent  */
	NULL, /* EP0_RxReady */
	USBD_MIDI_DataIn,
	USBD_MIDI_DataOut,
	NULL, /* SOF */
	NULL, /* IsoINIncomplete  */
	NULL, /* IsoOUTIncomplete */
	USBD_MIDI_GetHSCfgDesc,
	USBD_MIDI_GetFSCfgDesc,
	USBD_MIDI_GetOtherSpeedCfgDesc,
	USBD_MIDI_GetDeviceQualifierDesc,
};

/* Class-specific descriptors shared by HS/FS/OtherSpeed (everything between the
 * standard MS interface descriptor and the endpoint descriptors). 0x24 =
 * CS_INTERFACE, 0x25 = CS_ENDPOINT. */
#define MIDI_AC_AND_JACK_DESCRIPTORS                                                                                    \
	/* Standard AudioControl (AC) Interface Descriptor */                                                              \
	0x09, USB_DESC_TYPE_INTERFACE, 0x00, 0x00, 0x00, 0x01, 0x01, 0x00, 0x00,                                           \
		/* Class-specific AC Interface Header Descriptor */                                                            \
		0x09, 0x24, 0x01, 0x00, 0x01, 0x09, 0x00, 0x01, 0x01,                                                          \
		/* Standard MIDIStreaming (MS) Interface Descriptor (iface 1, 2 endpoints) */                                  \
		0x09, USB_DESC_TYPE_INTERFACE, 0x01, 0x00, 0x02, 0x01, 0x03, 0x00, 0x00,                                       \
		/* Class-specific MS Interface Header Descriptor (wTotalLength = 37 = 0x25) */                                 \
		0x07, 0x24, 0x01, 0x00, 0x01, 0x25, 0x00,                                                                      \
		/* MIDI IN Jack Descriptor (Embedded, ID 1) */                                                                 \
		0x06, 0x24, 0x02, 0x01, 0x01, 0x00,                                                                            \
		/* MIDI IN Jack Descriptor (External, ID 2) */                                                                 \
		0x06, 0x24, 0x02, 0x02, 0x02, 0x00,                                                                            \
		/* MIDI OUT Jack Descriptor (Embedded, ID 3) <- External IN jack (ID 2) */                                     \
		0x09, 0x24, 0x03, 0x01, 0x03, 0x01, 0x02, 0x01, 0x00,                                                          \
		/* MIDI OUT Jack Descriptor (External, ID 4) <- Embedded IN jack (ID 1) */                                     \
		0x09, 0x24, 0x03, 0x02, 0x04, 0x01, 0x01, 0x01, 0x00

/* Standard + class-specific bulk endpoint descriptors. The OUT endpoint feeds
 * Embedded IN jack (ID 1); the IN endpoint is fed by Embedded OUT jack (ID 3).
 * Note: USB-Audio v1.0 standard endpoint descriptors are 9 bytes (the extra
 * bRefresh + bSynchAddress fields), not the usual 7. */
#define MIDI_ENDPOINT_DESCRIPTORS(MPS_LO, MPS_HI)                                                                      \
	/* Standard Bulk OUT Endpoint Descriptor */                                                                        \
	0x09, USB_DESC_TYPE_ENDPOINT, MIDI_OUT_EP, 0x02, (MPS_LO), (MPS_HI), 0x00, 0x00, 0x00,                             \
		/* Class-specific MS Bulk OUT Endpoint Descriptor (assoc Embedded IN jack 1) */                                \
		0x05, 0x25, 0x01, 0x01, 0x01,                                                                                  \
		/* Standard Bulk IN Endpoint Descriptor */                                                                     \
		0x09, USB_DESC_TYPE_ENDPOINT, MIDI_IN_EP, 0x02, (MPS_LO), (MPS_HI), 0x00, 0x00, 0x00,                          \
		/* Class-specific MS Bulk IN Endpoint Descriptor (assoc Embedded OUT jack 3) */                                \
		0x05, 0x25, 0x01, 0x01, 0x03

#if (USBD_SELF_POWERED == 1U)
#define MIDI_BMATTRIBUTES 0xC0U
#else
#define MIDI_BMATTRIBUTES 0x80U
#endif

/* High-speed configuration descriptor (bulk MPS = 512) */
__ALIGN_BEGIN static uint8_t USBD_MIDI_CfgHSDesc[USB_MIDI_CONFIG_DESC_SIZ] __ALIGN_END = {
	0x09,
	USB_DESC_TYPE_CONFIGURATION,
	USB_MIDI_CONFIG_DESC_SIZ,
	0x00,
	0x02, /* bNumInterfaces */
	0x01,
	0x00,
	MIDI_BMATTRIBUTES,
	USBD_MAX_POWER,
	MIDI_AC_AND_JACK_DESCRIPTORS,
	MIDI_ENDPOINT_DESCRIPTORS(LOBYTE(MIDI_DATA_HS_MAX_PACKET_SIZE), HIBYTE(MIDI_DATA_HS_MAX_PACKET_SIZE)),
};

/* Full-speed configuration descriptor (bulk MPS = 64) */
__ALIGN_BEGIN static uint8_t USBD_MIDI_CfgFSDesc[USB_MIDI_CONFIG_DESC_SIZ] __ALIGN_END = {
	0x09,
	USB_DESC_TYPE_CONFIGURATION,
	USB_MIDI_CONFIG_DESC_SIZ,
	0x00,
	0x02,
	0x01,
	0x00,
	MIDI_BMATTRIBUTES,
	USBD_MAX_POWER,
	MIDI_AC_AND_JACK_DESCRIPTORS,
	MIDI_ENDPOINT_DESCRIPTORS(LOBYTE(MIDI_DATA_FS_MAX_PACKET_SIZE), HIBYTE(MIDI_DATA_FS_MAX_PACKET_SIZE)),
};

/* Other-speed configuration descriptor (describes FS behavior to a HS host) */
__ALIGN_BEGIN static uint8_t USBD_MIDI_OtherSpeedCfgDesc[USB_MIDI_CONFIG_DESC_SIZ] __ALIGN_END = {
	0x09,
	USB_DESC_TYPE_OTHER_SPEED_CONFIGURATION,
	USB_MIDI_CONFIG_DESC_SIZ,
	0x00,
	0x02,
	0x01,
	0x00,
	MIDI_BMATTRIBUTES,
	USBD_MAX_POWER,
	MIDI_AC_AND_JACK_DESCRIPTORS,
	MIDI_ENDPOINT_DESCRIPTORS(LOBYTE(MIDI_DATA_FS_MAX_PACKET_SIZE), HIBYTE(MIDI_DATA_FS_MAX_PACKET_SIZE)),
};

/* USB Standard Device Qualifier Descriptor */
__ALIGN_BEGIN static uint8_t USBD_MIDI_DeviceQualifierDesc[USB_LEN_DEV_QUALIFIER_DESC] __ALIGN_END = {
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

static uint8_t USBD_MIDI_Init(USBD_HandleTypeDef *pdev, uint8_t cfgidx) {
	UNUSED(cfgidx);

	USBD_MIDI_HandleTypeDef *hmidi = USBD_malloc(sizeof(USBD_MIDI_HandleTypeDef));
	if (hmidi == NULL) {
		pdev->pClassData = NULL;
		return (uint8_t)USBD_EMEM;
	}
	pdev->pClassData = (void *)hmidi;

	uint16_t mps =
		(pdev->dev_speed == USBD_SPEED_HIGH) ? MIDI_DATA_HS_MAX_PACKET_SIZE : MIDI_DATA_FS_MAX_PACKET_SIZE;

	(void)USBD_LL_OpenEP(pdev, MIDI_IN_EP, USBD_EP_TYPE_BULK, mps);
	pdev->ep_in[MIDI_IN_EP & 0xFU].is_used = 1U;

	(void)USBD_LL_OpenEP(pdev, MIDI_OUT_EP, USBD_EP_TYPE_BULK, mps);
	pdev->ep_out[MIDI_OUT_EP & 0xFU].is_used = 1U;

	/* Init physical interface (sets Rx/Tx buffers via SetRxBuffer/SetTxBuffer) */
	if (pdev->pUserData != NULL)
		((USBD_MIDI_ItfTypeDef *)pdev->pUserData)->Init();

	hmidi->TxState = 0U;

	/* Prepare OUT endpoint to receive the first packet */
	(void)USBD_LL_PrepareReceive(pdev, MIDI_OUT_EP, hmidi->RxBuffer, mps);

	return (uint8_t)USBD_OK;
}

static uint8_t USBD_MIDI_DeInit(USBD_HandleTypeDef *pdev, uint8_t cfgidx) {
	UNUSED(cfgidx);

	(void)USBD_LL_CloseEP(pdev, MIDI_IN_EP);
	pdev->ep_in[MIDI_IN_EP & 0xFU].is_used = 0U;

	(void)USBD_LL_CloseEP(pdev, MIDI_OUT_EP);
	pdev->ep_out[MIDI_OUT_EP & 0xFU].is_used = 0U;

	if (pdev->pClassData != NULL) {
		if (pdev->pUserData != NULL)
			((USBD_MIDI_ItfTypeDef *)pdev->pUserData)->DeInit();
		(void)USBD_free(pdev->pClassData);
		pdev->pClassData = NULL;
	}

	return (uint8_t)USBD_OK;
}

static uint8_t USBD_MIDI_Setup(USBD_HandleTypeDef *pdev, USBD_SetupReqTypedef *req) {
	uint16_t status_info = 0U;
	uint8_t ifalt = 0U;
	USBD_StatusTypeDef ret = USBD_OK;

	switch (req->bmRequest & USB_REQ_TYPE_MASK) {
		case USB_REQ_TYPE_STANDARD:
			switch (req->bRequest) {
				case USB_REQ_GET_STATUS:
					if (pdev->dev_state == USBD_STATE_CONFIGURED)
						(void)USBD_CtlSendData(pdev, (uint8_t *)&status_info, 2U);
					else {
						USBD_CtlError(pdev, req);
						ret = USBD_FAIL;
					}
					break;

				case USB_REQ_GET_INTERFACE:
					if (pdev->dev_state == USBD_STATE_CONFIGURED)
						(void)USBD_CtlSendData(pdev, &ifalt, 1U);
					else {
						USBD_CtlError(pdev, req);
						ret = USBD_FAIL;
					}
					break;

				case USB_REQ_SET_INTERFACE:
				case USB_REQ_CLEAR_FEATURE:
					break;

				default:
					USBD_CtlError(pdev, req);
					ret = USBD_FAIL;
					break;
			}
			break;

		/* Basic MIDI streaming has no class-specific requests */
		case USB_REQ_TYPE_CLASS:
		default:
			USBD_CtlError(pdev, req);
			ret = USBD_FAIL;
			break;
	}

	return (uint8_t)ret;
}

static uint8_t USBD_MIDI_DataIn(USBD_HandleTypeDef *pdev, uint8_t epnum) {
	USBD_MIDI_HandleTypeDef *hmidi = (USBD_MIDI_HandleTypeDef *)pdev->pClassData;
	PCD_HandleTypeDef *hpcd = pdev->pData;

	if (hmidi == NULL)
		return (uint8_t)USBD_FAIL;

	if ((pdev->ep_in[epnum].total_length > 0U) &&
		((pdev->ep_in[epnum].total_length % hpcd->IN_ep[epnum].maxpacket) == 0U)) {
		/* Send a ZLP to terminate a transfer that is a multiple of maxpacket */
		pdev->ep_in[epnum].total_length = 0U;
		(void)USBD_LL_Transmit(pdev, epnum, NULL, 0U);
	} else {
		hmidi->TxState = 0U;
	}

	return (uint8_t)USBD_OK;
}

static uint8_t USBD_MIDI_DataOut(USBD_HandleTypeDef *pdev, uint8_t epnum) {
	USBD_MIDI_HandleTypeDef *hmidi = (USBD_MIDI_HandleTypeDef *)pdev->pClassData;

	if (hmidi == NULL)
		return (uint8_t)USBD_FAIL;

	hmidi->RxLength = USBD_LL_GetRxDataSize(pdev, epnum);

	if (pdev->pUserData != NULL)
		((USBD_MIDI_ItfTypeDef *)pdev->pUserData)->Receive(hmidi->RxBuffer, &hmidi->RxLength);

	return (uint8_t)USBD_OK;
}

static uint8_t *USBD_MIDI_GetHSCfgDesc(uint16_t *length) {
	*length = (uint16_t)sizeof(USBD_MIDI_CfgHSDesc);
	return USBD_MIDI_CfgHSDesc;
}

static uint8_t *USBD_MIDI_GetFSCfgDesc(uint16_t *length) {
	*length = (uint16_t)sizeof(USBD_MIDI_CfgFSDesc);
	return USBD_MIDI_CfgFSDesc;
}

static uint8_t *USBD_MIDI_GetOtherSpeedCfgDesc(uint16_t *length) {
	*length = (uint16_t)sizeof(USBD_MIDI_OtherSpeedCfgDesc);
	return USBD_MIDI_OtherSpeedCfgDesc;
}

static uint8_t *USBD_MIDI_GetDeviceQualifierDesc(uint16_t *length) {
	*length = (uint16_t)sizeof(USBD_MIDI_DeviceQualifierDesc);
	return USBD_MIDI_DeviceQualifierDesc;
}

uint8_t USBD_MIDI_RegisterInterface(USBD_HandleTypeDef *pdev, USBD_MIDI_ItfTypeDef *fops) {
	if (fops == NULL)
		return (uint8_t)USBD_FAIL;

	pdev->pUserData = fops;
	return (uint8_t)USBD_OK;
}

uint8_t USBD_MIDI_SetTxBuffer(USBD_HandleTypeDef *pdev, uint8_t *pbuff, uint32_t length) {
	USBD_MIDI_HandleTypeDef *hmidi = (USBD_MIDI_HandleTypeDef *)pdev->pClassData;
	if (hmidi == NULL)
		return (uint8_t)USBD_FAIL;

	hmidi->TxBuffer = pbuff;
	hmidi->TxLength = length;
	return (uint8_t)USBD_OK;
}

uint8_t USBD_MIDI_SetRxBuffer(USBD_HandleTypeDef *pdev, uint8_t *pbuff) {
	USBD_MIDI_HandleTypeDef *hmidi = (USBD_MIDI_HandleTypeDef *)pdev->pClassData;
	if (hmidi == NULL)
		return (uint8_t)USBD_FAIL;

	hmidi->RxBuffer = pbuff;
	return (uint8_t)USBD_OK;
}

uint8_t USBD_MIDI_TransmitPacket(USBD_HandleTypeDef *pdev) {
	USBD_MIDI_HandleTypeDef *hmidi = (USBD_MIDI_HandleTypeDef *)pdev->pClassData;
	USBD_StatusTypeDef ret = USBD_BUSY;

	if (hmidi == NULL)
		return (uint8_t)USBD_FAIL;

	if (hmidi->TxState == 0U) {
		hmidi->TxState = 1U;
		pdev->ep_in[MIDI_IN_EP & 0xFU].total_length = hmidi->TxLength;
		(void)USBD_LL_Transmit(pdev, MIDI_IN_EP, hmidi->TxBuffer, hmidi->TxLength);
		ret = USBD_OK;
	}

	return (uint8_t)ret;
}

uint8_t USBD_MIDI_ReceivePacket(USBD_HandleTypeDef *pdev) {
	USBD_MIDI_HandleTypeDef *hmidi = (USBD_MIDI_HandleTypeDef *)pdev->pClassData;

	if (hmidi == NULL)
		return (uint8_t)USBD_FAIL;

	uint16_t mps =
		(pdev->dev_speed == USBD_SPEED_HIGH) ? MIDI_DATA_HS_MAX_PACKET_SIZE : MIDI_DATA_FS_MAX_PACKET_SIZE;

	(void)USBD_LL_PrepareReceive(pdev, MIDI_OUT_EP, hmidi->RxBuffer, mps);
	return (uint8_t)USBD_OK;
}
