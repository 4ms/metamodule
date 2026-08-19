/**
 ******************************************************************************
 * @file    USB_Device/MSC_Standalone/Src/usbd_conf.c
 * @author  MCD Application Team
 * @brief   This file implements the USB Device library callbacks and MSP
 ******************************************************************************
 * @attention
 *
 * Copyright (c) 2019 STMicroelectronics.
 * All rights reserved.
 *
 * This software is licensed under terms that can be found in the LICENSE file
 * in the root directory of this software component.
 * If no LICENSE file comes with this software, it is provided AS-IS.
 *
 ******************************************************************************
 */

/* Includes ------------------------------------------------------------------ */
#include "device_composite/usbd_composite_builder.h"
#include "device_midi/usbd_midi.h"
#include "device_msc/usb_drive_device.hh"
#include "drivers/stm32xx.h"
#include "usbd_cdc.h"
#include "usbd_core.h"
#include "usbd_msc.h"
#include "usbd_video.h"
#include <algorithm>

PCD_HandleTypeDef hpcd;

/**
 * @brief  Initializes the PCD MSP.
 * @param  hpcd: PCD handle
 * @retval None
 */
void HAL_PCD_MspInit(PCD_HandleTypeDef *hpcd) {
	//GPIO_InitTypeDef GPIO_InitStruct;

	if (hpcd->Instance == USB_OTG_HS) {
		// /* Configure VBUS Pin */
		// GPIO_InitStruct.Pin = GPIO_PIN_9;
		// GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
		// GPIO_InitStruct.Pull = GPIO_NOPULL;
		// HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

		// /* Configure ID pin */
		// GPIO_InitStruct.Pin = GPIO_PIN_10;
		// GPIO_InitStruct.Mode = GPIO_MODE_AF_OD;
		// GPIO_InitStruct.Pull = GPIO_PULLUP;
		// GPIO_InitStruct.Alternate = GPIO_AF10_OTG2_FS;
		// HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

		// Reset the OTG peripheral to allow switching between host/device mode
		__HAL_RCC_USBO_FORCE_RESET();
		__HAL_RCC_USBO_RELEASE_RESET();

		__HAL_RCC_USBO_CLK_ENABLE();
		__HAL_RCC_USBPHY_CLK_ENABLE();
		// HAL_PWREx_EnableUSBVoltageDetector();
		HAL_PWREx_DisableUSBVoltageDetector();
	}
}

/**
 * @brief  De-Initializes the PCD MSP.
 * @param  hpcd: PCD handle
 * @retval None
 */
void HAL_PCD_MspDeInit(PCD_HandleTypeDef *hpcd) {
	if (hpcd->Instance == USB_OTG_HS) {
		__HAL_RCC_USBO_CLK_DISABLE();
	}
}

/*******************************************************************************
					   LL Driver Callbacks (PCD -> USB Device Library)
*******************************************************************************/

/**
 * @brief  SetupStage callback.
 * @param  hpcd: PCD handle
 * @retval None
 */
void HAL_PCD_SetupStageCallback(PCD_HandleTypeDef *hpcd) {
	USBD_LL_SetupStage((USBD_HandleTypeDef *)hpcd->pData, (uint8_t *)hpcd->Setup);
}

/**
 * @brief  DataOut Stage callback.
 * @param  hpcd: PCD handle
 * @param  epnum: Endpoint Number
 * @retval None
 */
void HAL_PCD_DataOutStageCallback(PCD_HandleTypeDef *hpcd, uint8_t epnum) {
	USBD_LL_DataOutStage((USBD_HandleTypeDef *)hpcd->pData, epnum, hpcd->OUT_ep[epnum].xfer_buff);
}

/**
 * @brief  DataIn Stage callback.
 * @param  hpcd: PCD handle
 * @param  epnum: Endpoint Number
 * @retval None
 */
void HAL_PCD_DataInStageCallback(PCD_HandleTypeDef *hpcd, uint8_t epnum) {
	USBD_LL_DataInStage((USBD_HandleTypeDef *)hpcd->pData, epnum, hpcd->IN_ep[epnum].xfer_buff);
}

/**
 * @brief  SOF callback.
 * @param  hpcd: PCD handle
 * @retval None
 */
void HAL_PCD_SOFCallback(PCD_HandleTypeDef *hpcd) {
	USBD_LL_SOF((USBD_HandleTypeDef *)hpcd->pData);
}

/**
 * @brief  Reset callback.
 * @param  hpcd: PCD handle
 * @retval None
 */
void HAL_PCD_ResetCallback(PCD_HandleTypeDef *hpcd) {
	USBD_SpeedTypeDef speed = USBD_SPEED_FULL;

	/* Set USB Current Speed */
	switch (hpcd->Init.speed) {
		case PCD_SPEED_HIGH:
			speed = USBD_SPEED_HIGH;
			break;

		case PCD_SPEED_FULL:
			speed = USBD_SPEED_FULL;
			break;

		default:
			speed = USBD_SPEED_FULL;
			break;
	}

	/* Reset Device */
	USBD_LL_Reset((USBD_HandleTypeDef *)hpcd->pData);

	USBD_LL_SetSpeed((USBD_HandleTypeDef *)hpcd->pData, speed);
}

/**
 * @brief  Suspend callback.
 * @param  hpcd: PCD handle
 * @retval None
 */
void HAL_PCD_SuspendCallback(PCD_HandleTypeDef *hpcd) {
	USBD_LL_Suspend((USBD_HandleTypeDef *)hpcd->pData);
}

/**
 * @brief  Resume callback.
 * @param  hpcd: PCD handle
 * @retval None
 */
void HAL_PCD_ResumeCallback(PCD_HandleTypeDef *hpcd) {
	USBD_LL_Resume((USBD_HandleTypeDef *)hpcd->pData);
}

/**
 * @brief  ISOOUTIncomplete callback.
 * @param  hpcd: PCD handle
 * @param  epnum: Endpoint Number
 * @retval None
 */
void HAL_PCD_ISOOUTIncompleteCallback(PCD_HandleTypeDef *hpcd, uint8_t epnum) {
	USBD_LL_IsoOUTIncomplete((USBD_HandleTypeDef *)hpcd->pData, epnum);
}

/**
 * @brief  ISOINIncomplete callback.
 * @param  hpcd: PCD handle
 * @param  epnum: Endpoint Number
 * @retval None
 */
void HAL_PCD_ISOINIncompleteCallback(PCD_HandleTypeDef *hpcd, uint8_t epnum) {
	USBD_LL_IsoINIncomplete((USBD_HandleTypeDef *)hpcd->pData, epnum);
}

/**
 * @brief  ConnectCallback callback.
 * @param  hpcd: PCD handle
 * @retval None
 */
void HAL_PCD_ConnectCallback(PCD_HandleTypeDef *hpcd) {
	USBD_LL_DevConnected((USBD_HandleTypeDef *)hpcd->pData);
	// fops->Init is called already...?
	// uint32_t num_lun = USBD_MSC_fops.GetMaxLun();
	// while (num_lun >= 0) {
	// 	USBD_MSC_fops.Init(num_lun);
	// 	num_lun--;
	// }
}

/**
 * @brief  Disconnect callback.
 * @param  hpcd: PCD handle
 * @retval None
 */
void HAL_PCD_DisconnectCallback(PCD_HandleTypeDef *hpcd) {
	USBD_LL_DevDisconnected((USBD_HandleTypeDef *)hpcd->pData);

	//TODO: Run this in the class DeInit() class callback, which is USBD_MSC_DeInit()
#ifdef USE_RAMDISK_USB
	int8_t num_lun = UsbDriveDevice::ops.GetMaxLun();
	while (num_lun >= 0) {
		UsbDriveDevice::ops.Eject(num_lun);
		num_lun--;
	}
#endif
}

/*******************************************************************************
					   LL Driver Interface (USB Device Library --> PCD)
*******************************************************************************/

// The OTG core has 4 KB (1024 words) of FIFO RAM shared by the Rx FIFO and one
// Tx FIFO per IN endpoint; with DMA enabled the core also reserves a few words
// per channel, leaving ~952 usable. A Tx FIFO must hold at least one max-size
// packet, so a high-speed bulk IN endpoint needs >= 128 words. The two device
// modes have different endpoint sets, and USBD_LL_Init runs on every mode
// change, so the split is chosen per mode rather than sized for the worst case.
static void reset_class_arena();

static void set_fifo_sizes() {
	if (USBD_CMPSIT_GetProfile() == UsbCompositeProfile_Video) {
		// EP1 IN isochronous, 1024 B/packet. Total: 512 + 64 + 256 = 832 words.
		HAL_PCDEx_SetRxFiFo(&hpcd, 0x200);
		HAL_PCDEx_SetTxFiFo(&hpcd, 0, 0x40);  // EP0
		HAL_PCDEx_SetTxFiFo(&hpcd, 1, 0x100); // UVC iso IN
	} else {
		// CDC bulk (EP1), CDC notifications (EP2), MIDI bulk (EP3). The Rx FIFO
		// is shared by both bulk OUT endpoints; 384 words is comfortably above
		// the ~160-word minimum for a 512 B packet with two OUT endpoints.
		// Total: 384 + 64 + 128 + 16 + 128 + 128 = 848 words of the ~952
		// usable. The MSC FIFO is allocated whether or not the developer drive
		// is being served -- an unused Tx FIFO costs nothing but its space, and
		// keeping the layout fixed means enabling the drive cannot disturb the
		// endpoints that were already working.
		HAL_PCDEx_SetRxFiFo(&hpcd, 0x180);
		HAL_PCDEx_SetTxFiFo(&hpcd, 0, 0x40); // EP0
		HAL_PCDEx_SetTxFiFo(&hpcd, 1, 0x80); // CDC data IN
		HAL_PCDEx_SetTxFiFo(&hpcd, 2, 0x10); // CDC notifications
		HAL_PCDEx_SetTxFiFo(&hpcd, 3, 0x80); // MIDI IN
		HAL_PCDEx_SetTxFiFo(&hpcd, 4, 0x80); // MSC IN (developer drive)
	}
}

/**
 * @brief  Initializes the Low Level portion of the Device driver.
 * @param  pdev: Device handle
 * @retval USBD Status
 */

USBD_StatusTypeDef USBD_LL_Init(USBD_HandleTypeDef *pdev) {
	/* Set LL Driver parameters */
	hpcd.Instance = USB_OTG_HS;
	hpcd.Init.dev_endpoints = 9;
	hpcd.Init.use_dedicated_ep1 = 0;

	/* Be aware that enabling DMA mode will result in data being sent only by
	 * multiple of 4 packet sizes. This is due to the fact that USB DMA does not
	 * allow sending data from non word-aligned addresses. For this specific
	 * application, it is advised to not enable this option unless required. */
	hpcd.Init.dma_enable = 1;
	hpcd.Init.low_power_enable = 0;
	hpcd.Init.lpm_enable = 0;
	hpcd.Init.phy_itface = USB_OTG_HS_EMBEDDED_PHY;
	hpcd.Init.Sof_enable = 1;
	hpcd.Init.speed = PCD_SPEED_HIGH;
	hpcd.Init.vbus_sensing_enable = 1;

	/* Link The driver to the stack */
	hpcd.pData = pdev;
	pdev->pData = &hpcd;

	// Note: Library was altered here:
	// Force this to null, so ST USB library doesn't try to de-init it
	((USBD_HandleTypeDef *)hpcd.pData)->pClassData = nullptr;

	if (HAL_PCD_Init(&hpcd) != HAL_OK)
		return USBD_FAIL;

	reset_class_arena();

	set_fifo_sizes();

	return USBD_OK;
}

/**
 * @brief  De-Initializes the Low Level portion of the Device driver.
 * @param  pdev: Device handle
 * @retval USBD Status
 */
USBD_StatusTypeDef USBD_LL_DeInit(USBD_HandleTypeDef *pdev) {
	HAL_PCD_DeInit((PCD_HandleTypeDef *)pdev->pData);
	return USBD_OK;
}

/**
 * @brief  Starts the Low Level portion of the Device driver.
 * @param  pdev: Device handle
 * @retval USBD Status
 */
USBD_StatusTypeDef USBD_LL_Start(USBD_HandleTypeDef *pdev) {
	HAL_PCD_Start((PCD_HandleTypeDef *)pdev->pData);
	return USBD_OK;
}

/**
 * @brief  Stops the Low Level portion of the Device driver.
 * @param  pdev: Device handle
 * @retval USBD Status
 */
USBD_StatusTypeDef USBD_LL_Stop(USBD_HandleTypeDef *pdev) {
	HAL_PCD_Stop((PCD_HandleTypeDef *)pdev->pData);
	return USBD_OK;
}

/**
 * @brief  Opens an endpoint of the Low Level Driver.
 * @param  pdev: Device handle
 * @param  ep_addr: Endpoint Number
 * @param  ep_type: Endpoint Type
 * @param  ep_mps: Endpoint Max Packet Size
 * @retval USBD Status
 */
USBD_StatusTypeDef USBD_LL_OpenEP(USBD_HandleTypeDef *pdev, uint8_t ep_addr, uint8_t ep_type, uint16_t ep_mps) {
	HAL_PCD_EP_Open((PCD_HandleTypeDef *)pdev->pData, ep_addr, ep_mps, ep_type);
	return USBD_OK;
}

/**
 * @brief  Closes an endpoint of the Low Level Driver.
 * @param  pdev: Device handle
 * @param  ep_addr: Endpoint Number
 * @retval USBD Status
 */
USBD_StatusTypeDef USBD_LL_CloseEP(USBD_HandleTypeDef *pdev, uint8_t ep_addr) {
	HAL_PCD_EP_Close((PCD_HandleTypeDef *)pdev->pData, ep_addr);
	return USBD_OK;
}

/**
 * @brief  Flushes an endpoint of the Low Level Driver.
 * @param  pdev: Device handle
 * @param  ep_addr: Endpoint Number
 * @retval USBD Status
 */
USBD_StatusTypeDef USBD_LL_FlushEP(USBD_HandleTypeDef *pdev, uint8_t ep_addr) {
	HAL_PCD_EP_Flush((PCD_HandleTypeDef *)pdev->pData, ep_addr);
	return USBD_OK;
}

/**
 * @brief  Sets a Stall condition on an endpoint of the Low Level Driver.
 * @param  pdev: Device handle
 * @param  ep_addr: Endpoint Number
 * @retval USBD Status
 */
USBD_StatusTypeDef USBD_LL_StallEP(USBD_HandleTypeDef *pdev, uint8_t ep_addr) {
	HAL_PCD_EP_SetStall((PCD_HandleTypeDef *)pdev->pData, ep_addr);
	return USBD_OK;
}

/**
 * @brief  Clears a Stall condition on an endpoint of the Low Level Driver.
 * @param  pdev: Device handle
 * @param  ep_addr: Endpoint Number
 * @retval USBD Status
 */
USBD_StatusTypeDef USBD_LL_ClearStallEP(USBD_HandleTypeDef *pdev, uint8_t ep_addr) {
	HAL_PCD_EP_ClrStall((PCD_HandleTypeDef *)pdev->pData, ep_addr);
	return USBD_OK;
}

/**
 * @brief  Returns Stall condition.
 * @param  pdev: Device handle
 * @param  ep_addr: Endpoint Number
 * @retval Stall (1: Yes, 0: No)
 */
uint8_t USBD_LL_IsStallEP(USBD_HandleTypeDef *pdev, uint8_t ep_addr) {
	auto *hpcd = (PCD_HandleTypeDef *)pdev->pData;

	if ((ep_addr & 0x80) == 0x80) {
		return hpcd->IN_ep[ep_addr & 0x7F].is_stall;
	} else {
		return hpcd->OUT_ep[ep_addr & 0x7F].is_stall;
	}
}

/**
 * @brief  Assigns a USB address to the device.
 * @param  pdev: Device handle
 * @param  ep_addr: Endpoint Number
 * @retval USBD Status
 */
USBD_StatusTypeDef USBD_LL_SetUSBAddress(USBD_HandleTypeDef *pdev, uint8_t dev_addr) {
	HAL_PCD_SetAddress((PCD_HandleTypeDef *)pdev->pData, dev_addr);
	return USBD_OK;
}

/**
 * @brief  Transmits data over an endpoint.
 * @param  pdev: Device handle
 * @param  ep_addr: Endpoint Number
 * @param  pbuf: Pointer to data to be sent
 * @param  size: Data size
 * @retval USBD Status
 */
USBD_StatusTypeDef USBD_LL_Transmit(USBD_HandleTypeDef *pdev, uint8_t ep_addr, uint8_t *pbuf, uint32_t size) {
	HAL_PCD_EP_Transmit((PCD_HandleTypeDef *)pdev->pData, ep_addr, pbuf, size);
	return USBD_OK;
}

/**
 * @brief  Prepares an endpoint for reception.
 * @param  pdev: Device handle
 * @param  ep_addr: Endpoint Number
 * @param  pbuf: Pointer to data to be received
 * @param  size: Data size
 * @retval USBD Status
 */
USBD_StatusTypeDef USBD_LL_PrepareReceive(USBD_HandleTypeDef *pdev, uint8_t ep_addr, uint8_t *pbuf, uint32_t size) {
	HAL_PCD_EP_Receive((PCD_HandleTypeDef *)pdev->pData, ep_addr, pbuf, size);
	return USBD_OK;
}

/**
 * @brief  Returns the last transferred packet size.
 * @param  pdev: Device handle
 * @param  ep_addr: Endpoint Number
 * @retval Received Data Size
 */
uint32_t USBD_LL_GetRxDataSize(USBD_HandleTypeDef *pdev, uint8_t ep_addr) {
	return HAL_PCD_EP_GetRxCount((PCD_HandleTypeDef *)pdev->pData, ep_addr);
}

/**
 * @brief  Static single allocation.
 * @param  size: Size of allocated memory
 * @retval None
 */
// Each registered class allocates its handle here during SetConfiguration and
// releases it on ClrClassConfig. A composite configuration has several classes
// live at once, so this cannot hand out one shared block the way ST's template
// does -- it bump-allocates from an arena instead, and rewinds once every
// allocation has been released. USBD_LL_Init() resets it outright: a fresh
// USBD_Init means every previously handed-out handle is dead.
//
// Sized for the largest device mode: MIDI + Console (plus the MSC handle, which
// is the biggest of the four and is what the developer-mode drive will add).
static constexpr uint32_t round4(uint32_t n) {
	return (n + 3u) & ~3u;
}

static constexpr uint32_t ArenaSize = std::max(round4(sizeof(USBD_CDC_HandleTypeDef)) +
												   round4(sizeof(USBD_MIDI_HandleTypeDef)) +
												   round4(sizeof(USBD_MSC_BOT_HandleTypeDef)),
											   round4(sizeof(USBD_VIDEO_HandleTypeDef)));

static uint32_t class_arena[ArenaSize / 4];
static uint32_t arena_used;   // bytes handed out
static uint32_t arena_allocs; // outstanding allocations

static void reset_class_arena() {
	arena_used = 0;
	arena_allocs = 0;
}

void *USBD_static_malloc(uint32_t size) {
	size = round4(size);

	if (arena_used + size > sizeof(class_arena)) {
		// The caller (a class Init) reports this to the core as USBD_EMEM
		return nullptr;
	}

	void *p = reinterpret_cast<uint8_t *>(class_arena) + arena_used;
	arena_used += size;
	arena_allocs++;
	return p;
}

/**
 * @brief  Dummy memory free
 * @param  p: Pointer to allocated  memory address
 * @retval None
 */
void USBD_static_free(void *p) {
	if (p != nullptr && arena_allocs > 0) {
		// Classes are torn down as a group (USBD_ClrClassConfig / USBD_DeInit),
		// so rewinding when the last one goes is enough to keep this stable
		// across re-enumeration; individual frees are otherwise no-ops.
		if (--arena_allocs == 0)
			arena_used = 0;
	}
}

/**
 * @brief  Delays routine for the USB Device Library.
 * @param  Delay: Delay in ms
 * @retval None
 */
void USBD_LL_Delay(uint32_t Delay) {
	HAL_Delay(Delay);
}
