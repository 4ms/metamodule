/**
 ******************************************************************************
 * @file           : Target/usbh_conf.c
 * @version        : v1.0_Cube
 * @brief          : This file implements the board support package for the USB host library
 ******************************************************************************
 * @attention
 *
 * <h2><center>&copy; Copyright (c) 2021 STMicroelectronics.
 * All rights reserved.</center></h2>
 *
 * This software component is licensed by ST under Ultimate Liberty license
 * SLA0044, the "License"; You may not use this file except in compliance with
 * the License. You may obtain a copy of the License at:
 *                             www.st.com/SLA0044
 *
 ******************************************************************************
 */

#include "usbh_MIDI.h"
#include "usbh_core.h"

/* Private function prototypes -----------------------------------------------*/
static USBH_StatusTypeDef USBH_Get_USB_Status(HAL_StatusTypeDef hal_status);

HCD_HandleTypeDef hhcd;

/*******************************************************************************
					   LL Driver Callbacks (HCD -> USB Host Library)
*******************************************************************************/
/* MSP Init */

void HAL_HCD_MspInit(HCD_HandleTypeDef *hpcd) {
	if (hpcd->Instance == USB_OTG_HS) {
		__HAL_RCC_USBO_CLK_ENABLE();
		__HAL_RCC_USBPHY_CLK_ENABLE();

		//	SWITHOST 0: Select OTG controller for 2nd PHY port
		//	SWITHOST 1: Select Host controller for 2nd PHY port
		//	EHCI controller hard wired to 1st PHY port
		USBPHYC->MISC = (USBPHYC->MISC & ~(USBPHYC_MISC_SWITHOST_Msk | USBPHYC_MISC_PPCKDIS_Msk)) |
						(0 << USBPHYC_MISC_SWITHOST_Pos) | (0 << USBPHYC_MISC_PPCKDIS_Pos);

		HAL_PWREx_EnableUSBVoltageDetector();
	}
}

void HAL_HCD_MspDeInit(HCD_HandleTypeDef *hpcd) {
	if (hpcd->Instance == USB_OTG_HS) {
		// InterruptManager::disable_irq(OTG_IRQn);
	}
}

void *USBH_malloc(size_t sz) {
	static MIDI_HandleTypeDef MIDIHandle;
	if (sz == sizeof(MIDI_HandleTypeDef)) {
		return &MIDIHandle;
	}
	return NULL;
}

void USBH_free(void *x){
	// nothing, we're using static allocation
};

/**
 * @brief  SOF callback.
 * @param  hhcd: HCD handle
 * @retval None
 */
void HAL_HCD_SOF_Callback(HCD_HandleTypeDef *hhcd) {
	USBH_LL_IncTimer(hhcd->pData);
}

/**
 * @brief  Connect callback.
 * @param  hhcd: HCD handle
 * @retval None
 */
void HAL_HCD_Connect_Callback(HCD_HandleTypeDef *hhcd) {
	USBH_LL_Connect(hhcd->pData);
}

/**
 * @brief  Disconnect callback.
 * @param  hhcd: HCD handle
 * @retval None
 */
void HAL_HCD_Disconnect_Callback(HCD_HandleTypeDef *hhcd) {
	USBH_LL_Disconnect(hhcd->pData);
}

/**
 * @brief  Notify URB state change callback.
 * @param  hhcd: HCD handle
 * @param  chnum: channel number
 * @param  urb_state: state
 * @retval None
 */
// Defined in usbh_midi.cc
// void HAL_HCD_HC_NotifyURBChange_Callback(HCD_HandleTypeDef *hhcd, uint8_t chnum, HCD_URBStateTypeDef urb_state)
// {
// 	/* To be used with OS to sync URB state with the global state machine */
// #if (USBH_USE_OS == 1)
// 	USBH_LL_NotifyURBChange(hhcd->pData);
// #endif
// }

/**
 * @brief  Port Port Enabled callback.
 * @param  hhcd: HCD handle
 * @retval None
 */
void HAL_HCD_PortEnabled_Callback(HCD_HandleTypeDef *hhcd) {
	USBH_LL_PortEnabled(hhcd->pData);
}

/**
 * @brief  Port Port Disabled callback.
 * @param  hhcd: HCD handle
 * @retval None
 */
void HAL_HCD_PortDisabled_Callback(HCD_HandleTypeDef *hhcd) {
	USBH_LL_PortDisabled(hhcd->pData);
}

/*******************************************************************************
					   LL Driver Interface (USB Host Library --> HCD)
*******************************************************************************/

/**
 * @brief  Initialize the low level portion of the host driver.
 * @param  phost: Host handle
 * @retval USBH status
 */
USBH_StatusTypeDef USBH_LL_Init(USBH_HandleTypeDef *phost) {

	hhcd.Instance = USB_OTG_HS;
	hhcd.Init.Host_channels = 16;
	hhcd.Init.speed = HCD_SPEED_HIGH;
	hhcd.Init.dma_enable = DISABLE;
	hhcd.Init.phy_itface = USB_OTG_HS_EMBEDDED_PHY;
	hhcd.Init.phy_itface = USB_OTG_HS_EMBEDDED_PHY;
	hhcd.Init.Sof_enable = DISABLE;

	// Link The driver to the stack
	hhcd.pData = phost;
	phost->pData = &hhcd;

	// Note: Library was altered here in usbd_conf.c:
	// Force this to null, so ST USB library doesn't try to de-init it
	// ((USBH_HandleTypeDef *)hhcd.pData)->pClassData = NULL;

	if (HAL_HCD_Init(&hhcd) != HAL_OK) {
		return USBH_FAIL;
	}

	USBH_LL_SetTimer(phost, HAL_HCD_GetCurrentFrame(&hhcd));

	return USBH_OK;
}

/**
 * @brief  De-Initialize the low level portion of the host driver.
 * @param  phost: Host handle
 * @retval USBH status
 */
USBH_StatusTypeDef USBH_LL_DeInit(USBH_HandleTypeDef *phost) {
	HAL_StatusTypeDef hal_status = HAL_OK;
	USBH_StatusTypeDef usb_status = USBH_OK;

	hal_status = HAL_HCD_DeInit(phost->pData);

	usb_status = USBH_Get_USB_Status(hal_status);

	phost->pData = NULL;

	return usb_status;
}

/**
 * @brief  Start the low level portion of the host driver.
 * @param  phost: Host handle
 * @retval USBH status
 */
USBH_StatusTypeDef USBH_LL_Start(USBH_HandleTypeDef *phost) {
	HAL_StatusTypeDef hal_status = HAL_OK;
	USBH_StatusTypeDef usb_status = USBH_OK;

	hal_status = HAL_HCD_Start(phost->pData);

	usb_status = USBH_Get_USB_Status(hal_status);

	return usb_status;
}

/**
 * @brief  Stop the low level portion of the host driver.
 * @param  phost: Host handle
 * @retval USBH status
 */
USBH_StatusTypeDef USBH_LL_Stop(USBH_HandleTypeDef *phost) {
	HAL_StatusTypeDef hal_status = HAL_OK;
	USBH_StatusTypeDef usb_status = USBH_OK;

	hal_status = HAL_HCD_Stop(phost->pData);

	usb_status = USBH_Get_USB_Status(hal_status);

	return usb_status;
}

/**
 * @brief  Return the USB host speed from the low level driver.
 * @param  phost: Host handle
 * @retval USBH speeds
 */
USBH_SpeedTypeDef USBH_LL_GetSpeed(USBH_HandleTypeDef *phost) {
	USBH_SpeedTypeDef speed = USBH_SPEED_FULL;

	switch (HAL_HCD_GetCurrentSpeed(phost->pData)) {
		case 0:
			speed = USBH_SPEED_HIGH;
			break;

		case 1:
			speed = USBH_SPEED_FULL;
			break;

		case 2:
			speed = USBH_SPEED_LOW;
			break;

		default:
			speed = USBH_SPEED_FULL;
			break;
	}
	return speed;
}

/**
 * @brief  Reset the Host port of the low level driver.
 * @param  phost: Host handle
 * @retval USBH status
 */
USBH_StatusTypeDef USBH_LL_ResetPort(USBH_HandleTypeDef *phost) {
	HAL_StatusTypeDef hal_status = HAL_OK;
	USBH_StatusTypeDef usb_status = USBH_OK;

	hal_status = HAL_HCD_ResetPort(phost->pData);

	usb_status = USBH_Get_USB_Status(hal_status);

	return usb_status;
}
/**
 * @brief  USBH_LL_ResetPort2
 *         Reset the Host Port of the Low Level Driver.
 * @param  phost: Host handle
 * @retval USBH Status
 */
USBH_StatusTypeDef USBH_LL_ResetPort2(USBH_HandleTypeDef *phost, unsigned resetIsActive) /* Without delays */
{
	HAL_StatusTypeDef hal_status = HAL_OK;
	USBH_StatusTypeDef usb_status = USBH_OK;

	hal_status = HAL_HCD_ResetPort2(phost->pData, resetIsActive);

	usb_status = USBH_Get_USB_Status(hal_status);

	return usb_status;
}

/**
 * @brief  Return the last transferred packet size.
 * @param  phost: Host handle
 * @param  pipe: Pipe index
 * @retval Packet size
 */
uint32_t USBH_LL_GetLastXferSize(USBH_HandleTypeDef *phost, uint8_t pipe) {
	uint32_t size2 = HAL_HCD_HC_GetXferCount(phost->pData, pipe);
	uint32_t size;
	do {
		size = size2;
		size2 = HAL_HCD_HC_GetXferCount(phost->pData, pipe);
	} while (size != size2);
	return size2;
}

/**
 * @brief  Return the maximum possible transferred packet size.
 * @param  phost: Host handle
 * @param  pipe: Pipe index
 * @param  size: expectes transfer packet size
 * @retval Packet size
 */
uint32_t USBH_LL_GetAdjXferSize(USBH_HandleTypeDef *phost, uint8_t pipe, uint32_t size) {
	uint32_t maxpack = HAL_HCD_HC_GetMaxPacket(phost->pData, pipe); // Default implementation
	return (maxpack < size) ? maxpack : size;
}

/**
 * @brief  Open a pipe of the low level driver.
 * @param  phost: Host handle
 * @param  pipe_num: Pipe index
 * @param  epnum: Endpoint number
 * @param  dev_address: Device USB address
 * @param  speed: Device Speed
 * @param  ep_type: Endpoint type
 * @param  mps: Endpoint max packet size
 * @retval USBH status
 */
USBH_StatusTypeDef USBH_LL_OpenPipe(USBH_HandleTypeDef *phost,
									uint8_t pipe_num,
									uint8_t epnum,
									const USBH_TargetTypeDef *dev_target,
									uint8_t ep_type,
									uint16_t mps) {
	HAL_StatusTypeDef hal_status = HAL_OK;
	USBH_StatusTypeDef usb_status = USBH_OK;

	hal_status = HAL_HCD_HC_Init(phost->pData,
								 pipe_num,
								 epnum,
								 dev_target->dev_address,
								 dev_target->speed,
								 ep_type,
								 mps,
								 dev_target->tt_hubaddr,
								 dev_target->tt_prtaddr);

	usb_status = USBH_Get_USB_Status(hal_status);

	return usb_status;
}

/**
 * @brief  Close a pipe of the low level driver.
 * @param  phost: Host handle
 * @param  pipe: Pipe index
 * @retval USBH status
 */
USBH_StatusTypeDef USBH_LL_ClosePipe(USBH_HandleTypeDef *phost, uint8_t pipe) {
	HAL_StatusTypeDef hal_status = HAL_OK;
	USBH_StatusTypeDef usb_status = USBH_OK;

	hal_status = HAL_HCD_HC_Halt(phost->pData, pipe);

	usb_status = USBH_Get_USB_Status(hal_status);

	return usb_status;
}

/**
 * @brief  Submit a new URB to the low level driver.
 * @param  phost: Host handle
 * @param  pipe: Pipe index
 *         This parameter can be a value from 1 to 15
 * @param  direction : Channel number
 *          This parameter can be one of the these values:
 *           0 : Output
 *           1 : Input
 * @param  ep_type : Endpoint Type
 *          This parameter can be one of the these values:
 *            @arg EP_TYPE_CTRL: Control type
 *            @arg EP_TYPE_ISOC: Isochrounous type
 *            @arg EP_TYPE_BULK: Bulk type
 *            @arg EP_TYPE_INTR: Interrupt type
 * @param  token : Endpoint Type
 *          This parameter can be one of the these values:
 *            @arg 0: PID_SETUP
 *            @arg 1: PID_DATA
 * @param  pbuff : pointer to URB data
 * @param  length : Length of URB data
 * @param  do_ping : activate do ping protocol (for high speed only)
 *          This parameter can be one of the these values:
 *           0 : do ping inactive
 *           1 : do ping active
 * @retval Status
 */
USBH_StatusTypeDef USBH_LL_SubmitURB(USBH_HandleTypeDef *phost,
									 uint8_t pipe,
									 uint8_t direction,
									 uint8_t ep_type,
									 uint8_t token,
									 uint8_t *pbuff,
									 uint32_t length,
									 uint8_t do_ping) {
	HAL_StatusTypeDef hal_status = HAL_OK;
	USBH_StatusTypeDef usb_status = USBH_OK;

	hal_status = HAL_HCD_HC_SubmitRequest(phost->pData, pipe, direction, ep_type, token, pbuff, length, do_ping);
	usb_status = USBH_Get_USB_Status(hal_status);

	return usb_status;
}

/**
 * @brief  Get a URB state from the low level driver.
 * @param  phost: Host handle
 * @param  pipe: Pipe index
 *         This parameter can be a value from 1 to 15
 * @retval URB state
 *          This parameter can be one of the these values:
 *            @arg URB_IDLE
 *            @arg URB_DONE
 *            @arg URB_NOTREADY
 *            @arg URB_NYET
 *            @arg URB_ERROR
 *            @arg URB_STALL
 */
USBH_URBStateTypeDef USBH_LL_GetURBState(USBH_HandleTypeDef *phost, uint8_t pipe) {

	HCD_URBStateTypeDef state2 = HAL_HCD_HC_GetURBState(phost->pData, pipe);
	HCD_URBStateTypeDef state;
	do {
		state = state2;
		state2 = HAL_HCD_HC_GetURBState(phost->pData, pipe);
	} while (state != state2);
	return (USBH_URBStateTypeDef)state2;
}

USBH_SpeedTypeDef USBH_LL_GetPipeSpeed(USBH_HandleTypeDef *phost, uint8_t pipe_num) {
	HCD_HandleTypeDef *hhcd = phost->pData;

	return hhcd->hc[pipe_num].speed;
}

uint_fast8_t USBH_LL_GetSpeedReady(USBH_HandleTypeDef *phost) {
	return HAL_HCD_GetCurrentSpeedReady(phost->pData);
}

/**
 * @brief  USBH_LL_DriverVBUS
 *         Drive VBUS.
 * @param  phost: Host handle
 * @param  state : VBUS state
 *          This parameter can be one of the these values:
 *           1 : VBUS Active
 *           0 : VBUS Inactive
 * @retval Status
 */
USBH_StatusTypeDef USBH_LL_DriverVBUS(USBH_HandleTypeDef *phost, uint8_t state) {
	if (state != FALSE) {
		// board_set_usbhostvbuson(1);
	} else {
		// board_set_usbhostvbuson(0);
	}
	HAL_Delay(200);
	return USBH_OK;
}

/**
 * @brief  Set toggle for a pipe.
 * @param  phost: Host handle
 * @param  pipe: Pipe index
 * @param  toggle: toggle (0/1)
 * @retval Status
 */
USBH_StatusTypeDef USBH_LL_SetToggle(USBH_HandleTypeDef *phost, uint8_t pipe, uint8_t toggle) {
	HCD_HandleTypeDef *pHandle;
	pHandle = phost->pData;

	if (pHandle->hc[pipe].ep_is_in) {
		pHandle->hc[pipe].toggle_in = toggle;
	} else {
		pHandle->hc[pipe].toggle_out = toggle;
	}

	return USBH_OK;
}

/**
 * @brief  Return the current toggle of a pipe.
 * @param  phost: Host handle
 * @param  pipe: Pipe index
 * @retval toggle (0/1)
 */
uint8_t USBH_LL_GetToggle(USBH_HandleTypeDef *phost, uint8_t pipe) {
	uint8_t toggle = 0;
	HCD_HandleTypeDef *pHandle;
	pHandle = phost->pData;

	if (pHandle->hc[pipe].ep_is_in) {
		toggle = pHandle->hc[pipe].toggle_in;
	} else {
		toggle = pHandle->hc[pipe].toggle_out;
	}
	return toggle;
}

/**
 * @brief  Delay routine for the USB Host Library
 * @param  Delay: Delay in ms
 * @retval None
 */
void USBH_Delay(uint32_t Delay) {
	HAL_Delay(Delay);
}

/**
 * @brief  Returns the USB status depending on the HAL status:
 * @param  hal_status: HAL status
 * @retval USB status
 */
static USBH_StatusTypeDef USBH_Get_USB_Status(HAL_StatusTypeDef hal_status) {
	USBH_StatusTypeDef usb_status = USBH_OK;

	switch (hal_status) {
		case HAL_OK:
			usb_status = USBH_OK;
			break;
		case HAL_ERROR:
			usb_status = USBH_FAIL;
			break;
		case HAL_BUSY:
			usb_status = USBH_BUSY;
			break;
		case HAL_TIMEOUT:
			usb_status = USBH_FAIL;
			break;
		default:
			usb_status = USBH_FAIL;
			break;
	}
	return usb_status;
}
