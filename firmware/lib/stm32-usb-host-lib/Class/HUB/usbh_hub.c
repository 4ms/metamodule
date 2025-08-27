/**
  ******************************************************************************
  * @file    usbh_hub.c
  * @author  Mori, modified by ua1arn, modified by danngreen
  * @version
  * @date
  * @brief   Definitions used in the USB Hub support
  ******************************************************************************
  * Copyright (c) 2016 Mori
  *
  * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and
  * associated documentation files (the "Software"), to deal in the Software without restriction,
  * including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense,
  * and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so,
  * subject to the following conditions:
  *
  * The above copyright notice and this permission notice shall be included in all copies or substantial
  * portions of the Software.
  *
  * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT
  * LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
  * IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
  * WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
  * SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
  *
  ******************************************************************************
*/

#include "usbh_hub.h"
// #include "usbh_msc.h"
#include <stdlib.h>

static USBH_StatusTypeDef set_hub_port_power(USBH_HandleTypeDef *phost, uint8_t hub_port);
static USBH_StatusTypeDef hub_request(USBH_HandleTypeDef *phost,
									  uint8_t request,
									  uint8_t feature,
									  uint8_t dataDirection,
									  uint8_t porta,
									  uint8_t *buffer,
									  uint16_t size);
static USBH_StatusTypeDef set_hub_request(USBH_HandleTypeDef *phost, uint8_t request, uint8_t feature, uint8_t port);
static USBH_StatusTypeDef get_hub_request(
	USBH_HandleTypeDef *phost, uint8_t request, uint8_t feature, uint8_t porta, uint8_t *buffer, uint16_t size);
static USBH_StatusTypeDef clear_port_feature(USBH_HandleTypeDef *phost, uint8_t feature, uint8_t port);
static USBH_StatusTypeDef set_port_feature(USBH_HandleTypeDef *phost, uint8_t feature, uint8_t port);

static void clear_port_changed(HUB_HandleTypeDef *HUB_Handle, uint8_t port);
static uint8_t get_port_changed(HUB_HandleTypeDef *HUB_Handle);
static uint8_t port_changed(HUB_HandleTypeDef *HUB_Handle, const uint8_t *b);

static void detach(USBH_HandleTypeDef *phost, uint16_t idx);
static void attach(USBH_HandleTypeDef *phost, uint16_t idx, uint8_t speed);
static void debug_port(uint8_t curport, uint8_t *buff, __IO USB_HUB_PORT_STATUS *info);

static USBH_StatusTypeDef hub_request(USBH_HandleTypeDef *phost,
									  uint8_t request,
									  uint8_t feature,
									  uint8_t dataDirection,
									  uint8_t porta,
									  uint8_t *buffer,
									  uint16_t size) {
	uint8_t bmRequestType = (dataDirection == USB_DEVICE_REQUEST_GET) ? USB_D2H : USB_H2D; // 0x23

	phost->Control.setup.b.bmRequestType = bmRequestType | USB_REQ_RECIPIENT_OTHER | USB_REQ_TYPE_CLASS;
	phost->Control.setup.b.bRequest = request;
	phost->Control.setup.b.wValue.bw.msb = feature;
	phost->Control.setup.b.wValue.bw.lsb = 0;
	phost->Control.setup.b.wIndex.bw.msb = porta;
	phost->Control.setup.b.wIndex.bw.lsb = 0;
	phost->Control.setup.b.wLength.w = size;

	return USBH_CtlReq(phost, buffer, size);

	//	USBH_StatusTypeDef res = USBH_FAIL;
	//	do { res = USBH_CtlReq(phost, buffer, size); } while(res != USBH_OK && res != USBH_FAIL);
	//	return res;
}

// porta: 1..n
static USBH_StatusTypeDef set_hub_port_power(USBH_HandleTypeDef *phost, uint8_t porta) {
	return hub_request(phost, USB_REQ_SET_FEATURE, HUB_FEATURE_SEL_PORT_POWER, USB_DEVICE_REQUEST_SET, porta, 0, 0);
}

// porta: 1..n
static USBH_StatusTypeDef get_hub_request(
	USBH_HandleTypeDef *phost, uint8_t request, uint8_t feature, uint8_t porta, uint8_t *buffer, uint16_t size) {
	return hub_request(phost, request, feature, USB_DEVICE_REQUEST_GET, porta, buffer, size);
}

// porta: 1..n
static USBH_StatusTypeDef set_hub_request(USBH_HandleTypeDef *phost, uint8_t request, uint8_t feature, uint8_t porta) {
	return hub_request(phost, request, feature, USB_DEVICE_REQUEST_SET, porta, 0, 0);
}

// porta: 1..n
static USBH_StatusTypeDef clear_port_feature(USBH_HandleTypeDef *phost, uint8_t feature, uint8_t porta) {
	return set_hub_request(phost, USB_REQUEST_CLEAR_FEATURE, feature, porta);
}

// porta: 1..n
static USBH_StatusTypeDef set_port_feature(USBH_HandleTypeDef *phost, uint8_t feature, uint8_t porta) {
	return set_hub_request(phost, USB_REQUEST_SET_FEATURE, feature, porta);
}
//
//// porta: 1..n
static void clear_port_changed(HUB_HandleTypeDef *HUB_Handle, uint8_t porta) {
	switch (porta) {
		case 1:
			HUB_Handle->HUB_Change.bPorts.PORT_1 = 0;
			break;
		case 2:
			HUB_Handle->HUB_Change.bPorts.PORT_2 = 0;
			break;
		case 3:
			HUB_Handle->HUB_Change.bPorts.PORT_3 = 0;
			break;
		case 4:
			HUB_Handle->HUB_Change.bPorts.PORT_4 = 0;
			break;
		case 5:
			HUB_Handle->HUB_Change.bPorts.PORT_5 = 0;
			break;
		case 6:
			HUB_Handle->HUB_Change.bPorts.PORT_6 = 0;
			break;
		case 7:
			HUB_Handle->HUB_Change.bPorts.PORT_7 = 0;
			break;
		case 8:
			HUB_Handle->HUB_Change.bPorts.PORT_8 = 0;
			break;
	}
}

static uint8_t get_port_changed(HUB_HandleTypeDef *HUB_Handle) {
	if (HUB_Handle->HUB_Change.bPorts.PORT_1)
		return 1;
	if (HUB_Handle->HUB_Change.bPorts.PORT_2)
		return 2;
	if (HUB_Handle->HUB_Change.bPorts.PORT_3)
		return 3;
	if (HUB_Handle->HUB_Change.bPorts.PORT_4)
		return 4;
	if (HUB_Handle->HUB_Change.bPorts.PORT_5)
		return 5;
	if (HUB_Handle->HUB_Change.bPorts.PORT_6)
		return 6;
	if (HUB_Handle->HUB_Change.bPorts.PORT_7)
		return 7;
	if (HUB_Handle->HUB_Change.bPorts.PORT_8)
		return 8;

	return 0;
}

static uint8_t port_changed(HUB_HandleTypeDef *HUB_Handle, const uint8_t *b) {
	HUB_Handle->HUB_Change.val = 0x00;
	if (b[0] != 0x00) {

		if (b[0] & (0x01 << 1)) {
			HUB_Handle->HUB_Change.bPorts.PORT_1 = 1;
		}
		if (b[0] & (0x01 << 2)) {
			HUB_Handle->HUB_Change.bPorts.PORT_2 = 1;
		}
		if (b[0] & (0x01 << 3)) {
			HUB_Handle->HUB_Change.bPorts.PORT_3 = 1;
		}
		if (b[0] & (0x01 << 4)) {
			HUB_Handle->HUB_Change.bPorts.PORT_4 = 1;
		}
		if (b[0] & (0x01 << 5)) {
			HUB_Handle->HUB_Change.bPorts.PORT_5 = 1;
		}
		if (b[0] & (0x01 << 6)) {
			HUB_Handle->HUB_Change.bPorts.PORT_6 = 1;
		}
		if (b[0] & (0x01 << 7)) {
			HUB_Handle->HUB_Change.bPorts.PORT_7 = 1;
		}
		USBH_UsrLog("PORT STATUS CHANGE [0x%02X] [%d %d %d %d]",
					b[0],
					HUB_Handle->HUB_Change.bPorts.PORT_1,
					HUB_Handle->HUB_Change.bPorts.PORT_2,
					HUB_Handle->HUB_Change.bPorts.PORT_3,
					HUB_Handle->HUB_Change.bPorts.PORT_4);
	}
	return HUB_Handle->HUB_Change.val > 0;
}

// _phost is the port's host handle
void detach(USBH_HandleTypeDef *_phost, uint16_t idx) {
	USBH_UsrLog("detach hub port %d", idx);

	USBH_HandleTypeDef *pphost = &_phost->handles[idx];

	if (!pphost->valid) {
		USBH_UsrLog("DETACH ERROR, ALREADY DETACHED");
		return;
	}

	if (pphost->pUser != NULL) {
		pphost->pUser(pphost, HOST_USER_DISCONNECTION);
	}

	if (pphost->pActiveClass != NULL) {
		pphost->pActiveClass->DeInit(pphost);
		pphost->pActiveClass = NULL;
	}

	pphost->hubPortAddress = 0;
	pphost->busy = 0;
	// pphost->ClassNumber = 0;
	pphost->valid = 0;

	for (unsigned i = 0; i < USBH_MAX_DATA_BUFFER; i++) {
		pphost->device.Data[i] = 0;
	}

	USBH_DbgLog("hub detach: not freeing any allocated classData. OK?");
	// Do not free hubdata[0], it's static
	// for (unsigned i = 1; i < pphost->hubInstances; ++i) {
	// 	if (pphost->classData[i]) {
	// 		free(pphost->classData[i]);
	// 		pphost->classData[i] = NULL;
	// 	}
	// }

	pphost->hubInstances = 0;
	pphost->device.is_connected = 0;

	if (pphost->Control.pipe_out > 0) {
		USBH_ClosePipe(pphost, pphost->Control.pipe_out);
		USBH_FreePipe(pphost, pphost->Control.pipe_out);
	} else {
		USBH_ErrLog("Not freeing device Control.pipe_out since it's 0");
	}
	if (pphost->Control.pipe_in > 0) {
		USBH_ClosePipe(pphost, pphost->Control.pipe_in);
		USBH_FreePipe(pphost, pphost->Control.pipe_in);
	} else {
		USBH_ErrLog("Not freeing device Control.pipe_in since it's 0");
	}
}

// phost is the hub host handle
// idx is the hub port index that was attached
static void attach(USBH_HandleTypeDef *phost, uint16_t idx, uint8_t speed) {
	USBH_UsrLog("attach hub port %d", idx);

	USBH_HandleTypeDef *pphost = &phost->handles[idx];

	if (pphost->valid) {
		USBH_UsrLog("ATTACH ERROR, ALREADY ATTACHED");
		detach(phost, idx); // mori: was pphost
	}

	//pphost->id 					= 0;//hUSBHost[0].id; // seems to be selecting the USB peripheral
	pphost->hubPortAddress = idx;

	pphost->pActiveClass = NULL;

	// #warning Then use HUB class. investigane Pipes usage.
	// Taken from https://github.com/mori-br/STM32F4HUB
	// memcpy(pphost->Pipes, phost->Pipes, sizeof pphost->Pipes);
	pphost->Pipes = phost->Pipes;

	pphost->pUser = phost->pUser;
	pphost->EnumState = ENUM_IDLE;
	pphost->RequestState = CMD_SEND;
	pphost->Timer = 0;
	pphost->Control.errorcount = 0;
	pphost->Control.state = CTRL_SETUP;
	pphost->Control.pipe_size = speed == USBH_SPEED_LOW ? USBH_MPS_LOWSPEED : USBH_MPS_DEFAULT;

	pphost->rootTarget.dev_address = USBH_ADDRESS_DEFAULT;
	pphost->rootTarget.speed = speed;
	pphost->rootTarget.tt_hubaddr = phost->currentTarget->dev_address; // hub address is always 1?
	pphost->rootTarget.tt_prtaddr = idx;							   // hub port address

	// Do we do this here?
	pphost->currentTarget = &pphost->rootTarget;
	pphost->device.is_connected = 1;

	pphost->allocaddress = phost->allocaddress;

	HCD_HandleTypeDef *phHCD = (HCD_HandleTypeDef *)(pphost->pData);
	USBH_LL_SetTimer(pphost, HAL_HCD_GetCurrentFrame(phHCD));

	// pphost->gState = HOST_ENUMERATION; //mori
	pphost->gState = HOST_DEV_ATTACHED;

	pphost->Control.pipe_out = phost->Control.pipe_out;
	pphost->Control.pipe_in = phost->Control.pipe_in;

	// Why do we null all the classData? mori does this too
	for (unsigned i = 0; i < USBH_MAX_NUM_INTERFACES; ++i) {
		pphost->classData[i] = NULL;
	}

	pphost->hubInstances = 0; // not a hub
	pphost->busy = 0;
	pphost->valid = 3; // needs to be init
}

static void debug_port(uint8_t curport, uint8_t *buff, __IO USB_HUB_PORT_STATUS *info) {
#if 1
	// clang-format off
    printf("PORT %d STATUS [%02X %02X %02X %02X] ", curport, buff[0], buff[1], buff[2], buff[3]);

    if(info->wPortStatus.PORT_CONNECTION)       printf("PORT_CONNECTION ");
    if(info->wPortStatus.PORT_ENABLE)           printf("PORT_ENABLE ");
    if(info->wPortStatus.PORT_SUSPEND)          printf("PORT_SUSPEND ");
    if(info->wPortStatus.PORT_OVER_CURRENT)     printf("PORT_OVER_CURRENT ");
    if(info->wPortStatus.PORT_RESET)            printf("PORT_RESET ");
    if(info->wPortStatus.PORT_POWER)            printf("PORT_POWER ");
    if(info->wPortStatus.PORT_LOW_SPEED)        printf("PORT_LOW_SPEED ");
    if(info->wPortStatus.PORT_HIGH_SPEED)       printf("PORT_HIGH_SPEED ");
    if(info->wPortStatus.PORT_TEST)             printf("PORT_TEST ");
    if(info->wPortStatus.PORT_INDICATOR)        printf("PORT_INDICATOR ");

    if(info->wPortChange.C_PORT_CONNECTION)     printf("C_PORT_CONNECTION ");
    if(info->wPortChange.C_PORT_ENABLE)         printf("C_PORT_ENABLE ");
    if(info->wPortChange.C_PORT_SUSPEND)        printf("C_PORT_SUSPEND ");
    if(info->wPortChange.C_PORT_OVER_CURRENT)   printf("C_PORT_OVER_CURRENT ");
    if(info->wPortChange.C_PORT_RESET)          printf("C_PORT_RESET ");
    printf("\n");
	// clang-format on
#endif
}

static USBH_StatusTypeDef USBH_HUB_InterfaceInit(USBH_HandleTypeDef *phost, const USBH_TargetTypeDef *target) {
	USBH_DbgLog("USBH_HUB_InterfaceInit (host handle %p)", phost);
	uint8_t interface;

	USBH_StatusTypeDef status = USBH_FAIL;

	interface = USBH_FindInterface(phost, phost->pActiveClass->ClassCode, 0x00, 0xFF);
	USBH_DbgLog("USBH_HUB_InterfaceInit: found interface %u", interface);

	if (interface == 0xFF) /* No Valid Interface */ {
		USBH_DbgLog("Cannot Find the interface for %s class.", phost->pActiveClass->Name);
		return USBH_FAIL;
	}

	static HUB_HandleTypeDef staticHUB_Handle;
	HUB_HandleTypeDef *HUB_Handle = &staticHUB_Handle;

	USBH_DbgLog("USBH_HUB_InterfaceInit: assigned host handle->classData[0] to static hub handle %p", HUB_Handle);
	phost->classData[0] = HUB_Handle;
	memset((void *)HUB_Handle, 0, sizeof(HUB_HandleTypeDef));

	phost->hubInstances = 1;
	HUB_Handle->parent = NULL; //DG: cascaded hubs not supported

	// hftrx:
	HUB_Handle->target.speed = target->speed;
	HUB_Handle->target.dev_address = target->dev_address;
	HUB_Handle->target.tt_hubaddr = target->tt_hubaddr;
	HUB_Handle->target.tt_prtaddr = target->tt_prtaddr;

	HUB_Handle->NumPorts = 0;
	HUB_Handle->pwrGoodDelay = 0;

	HUB_Handle->pChangeInfo = NULL;
	HUB_Handle->HUB_CurPort = 0;
	HUB_Handle->HUB_Change.val = 0;

	HUB_Handle->detectedPorts = 0;
	///////// end hftrx

	USBH_SelectInterface(phost, interface);

	HUB_Handle->state = HUB_IDLE;
	HUB_Handle->ctl_state = HUB_REQ_IDLE;
	HUB_Handle->ep_addr = phost->device.CfgDesc.Itf_Desc[phost->device.current_interface].Ep_Desc[0].bEndpointAddress;
	HUB_Handle->length = phost->device.CfgDesc.Itf_Desc[phost->device.current_interface].Ep_Desc[0].wMaxPacketSize;
	HUB_Handle->poll = phost->device.CfgDesc.Itf_Desc[phost->device.current_interface].Ep_Desc[0].bInterval;

	USBH_UsrLog("USBH_HUB_InterfaceInit: device poll=%d, length=%d", HUB_Handle->poll, HUB_Handle->length);

	if (HUB_Handle->poll < HUB_MIN_POLL)
		HUB_Handle->poll = HUB_MIN_POLL;

	if (phost->device.CfgDesc.Itf_Desc[phost->device.current_interface].Ep_Desc[0].bEndpointAddress & 0x80) {
		HUB_Handle->InEp =
			(phost->device.CfgDesc.Itf_Desc[phost->device.current_interface].Ep_Desc[0].bEndpointAddress);
		HUB_Handle->InPipe = USBH_AllocPipe(phost, HUB_Handle->InEp);

		// Open pipe for IN endpoint
		USBH_OpenPipe(
			phost, HUB_Handle->InPipe, HUB_Handle->InEp, &HUB_Handle->target, USB_EP_TYPE_INTR, HUB_Handle->length);
		USBH_LL_SetToggle(phost, HUB_Handle->InPipe, 0);
	}

	status = USBH_OK;

	return status;
}

static USBH_StatusTypeDef USBH_HUB_InterfaceDeInit(USBH_HandleTypeDef *phost) {
	USBH_DbgLog("USBH_HUB_InterfaceDeInit (host handle %p)", phost);
	HUB_HandleTypeDef *const HUB_Handle = (HUB_HandleTypeDef *)phost->classData[0];

	if (phost->classData[0]) {
		USBH_UsrLog("USBH_HUB_InterfaceDeInit");

		if (HUB_Handle->InPipe != 0x00) {
			USBH_DbgLog("Closing and Freeing InPipe");
			USBH_ClosePipe(phost, HUB_Handle->InPipe);
			USBH_FreePipe(phost, HUB_Handle->InPipe);
			HUB_Handle->InPipe = 0; // Reset the pipe as Free
		}

		// USBH_free(phost->hubDatas[0]);
	} else {
		USBH_UsrLog("USBH_HUB_InterfaceDeInit failed: hubDatas[0] not allocated");
	}

	return USBH_OK;
}

static void USBH_HUB_ProcessDelay(HUB_HandleTypeDef *HUB_Handle, HUB_CtlStateTypeDef state, unsigned delayMS) {
	HUB_Handle->tickstart = HAL_GetTick();
	HUB_Handle->wait = delayMS < 1000 ? delayMS : 1000;
	HUB_Handle->ctl_state = HUB_DELAY;
	HUB_Handle->ctl_state_push = state;
}

// state machine - for each hub port...
static USBH_StatusTypeDef USBH_HUB_ClassRequest(USBH_HandleTypeDef *phost) {
	// USBH_DbgLog("USBH_HUB_ClassRequest (host handle %p)", phost);
	USBH_StatusTypeDef status = USBH_BUSY;
	HUB_HandleTypeDef *const HUB_Handle = (HUB_HandleTypeDef *)phost->classData[0];

	switch (HUB_Handle->ctl_state) {
		case HUB_REQ_IDLE:
			phost->Control.setup.b.bmRequestType = USB_D2H | USB_REQ_RECIPIENT_DEVICE | USB_REQ_TYPE_CLASS;
			phost->Control.setup.b.bRequest = USB_REQ_GET_DESCRIPTOR;
			phost->Control.setup.b.wValue.bw.msb = 0;
			phost->Control.setup.b.wValue.bw.lsb = USB_DESCRIPTOR_HUB;
			phost->Control.setup.b.wIndex.w = 0;
			phost->Control.setup.b.wLength.w = sizeof(USB_HUB_DESCRIPTOR);

			status = USBH_CtlReq(phost, HUB_Handle->buffer, sizeof(USB_HUB_DESCRIPTOR));
			if (status == USBH_OK) {
				USB_HUB_DESCRIPTOR *HUB_Desc = (USB_HUB_DESCRIPTOR *)HUB_Handle->buffer;
				HUB_Handle->NumPorts = (HUB_Desc->bNbrPorts > MAX_HUB_PORTS) ? MAX_HUB_PORTS : HUB_Desc->bNbrPorts;
				HUB_Handle->pwrGoodDelay = (HUB_Desc->bPwrOn2PwrGood * 2);
				//USBH_UsrLog("USBH_HUB_ClassRequest: NumPorts=%d, pwrGoodDelay=%d", HUB_Handle->NumPorts, HUB_Handle->pwrGoodDelay);

				HUB_Handle->hubClassRequestPort = 1;
				HUB_Handle->ctl_state = HUB_REQ_SET_POWER;
				status = USBH_BUSY;
			}
			break;

		case HUB_REQ_SET_POWER:
			// Turn on power for each hub port...
			status = set_hub_port_power(phost, HUB_Handle->hubClassRequestPort);
			if (status == USBH_OK) {
				// Reach last port
				if (HUB_Handle->NumPorts <= HUB_Handle->hubClassRequestPort)
					HUB_Handle->ctl_state = HUB_WAIT_PWRGOOD;
				else
					HUB_Handle->hubClassRequestPort++;
				status = USBH_BUSY;
			}
			break;

		case HUB_WAIT_PWRGOOD:
			//HAL_Delay(HUB_Handle->pwrGoodDelay);
			//HUB_Handle->ctl_state = HUB_WAIT_PWRGOOD_DONE;
			USBH_HUB_ProcessDelay(HUB_Handle, HUB_WAIT_PWRGOOD_DONE, HUB_Handle->pwrGoodDelay);
			status = USBH_BUSY;
			break;

		case HUB_WAIT_PWRGOOD_DONE:
			phost->busy = 0;
			USBH_UsrLog("USBH_HUB_ClassRequest done: NumPorts=%d, pwrGoodDelay=%d",
						HUB_Handle->NumPorts,
						HUB_Handle->pwrGoodDelay);
			USBH_UsrLog("=============================================");
			// HUB_Handle->hubClassRequestPort = 1;
			// HUB_Handle->ctl_state = HUB_REQ_RESETS;
			HUB_Handle->ctl_state = HUB_REQ_DONE;
			break;

			//////////////////////////////////////////////
		case HUB_REQ_RESETS:
			// Выполняем сброс всех портов (We reset all ports)
			status = set_port_feature(phost, HUB_FEAT_SEL_PORT_RESET, HUB_Handle->hubClassRequestPort);
			if (status == USBH_OK) {
				// Reach last port
				if (HUB_Handle->NumPorts <= HUB_Handle->hubClassRequestPort) {
					HUB_Handle->ctl_state = HUB_REQ_RESETS_DONE;
					//  HS устройства не сразу становятся подключенными (HS devices do not immediately become connected)
					//USBH_HUB_ProcessDelay(HUB_Handle, HUB_REQ_RESETS_DONE, 25);
				} else {
					HUB_Handle->hubClassRequestPort++;
					HUB_Handle->ctl_state = HUB_REQ_RESETS;
					// HS устройства не сразу становятся подключенными
					//USBH_HUB_ProcessDelay(HUB_Handle, HUB_REQ_RESETS, 25);
				}
				status = USBH_BUSY;
			} else {
				// HS устройства не сразу становятся подключенными
				USBH_HUB_ProcessDelay(HUB_Handle, HUB_REQ_RESETS, 25);
			}
			break;

		case HUB_REQ_RESETS_DONE:
			// Строим карту подключенных портов (We build a map of connected ports)
			HUB_Handle->hubClassRequestPort = 1;
			HUB_Handle->ctl_state = HUB_REQ_SCAN_STATUSES;
			status = USBH_BUSY;
			break;

		case HUB_REQ_SCAN_STATUSES:
			// if (HUB_Handle->hubClassRequestPort < 1)
			// 	USBH_ErrLog("ASSERT FAILED: hubClassRequestPort == %u", HUB_Handle->hubClassRequestPort);
			status = get_hub_request(phost,
									 USB_REQUEST_GET_STATUS,
									 HUB_FEAT_SEL_PORT_CONN,
									 HUB_Handle->hubClassRequestPort,
									 HUB_Handle->buffer,
									 sizeof(USB_HUB_PORT_STATUS));
			if (status == USBH_OK) {
				/* Enumeration target */
				// We will store
				USBH_TargetTypeDef *const tg = &HUB_Handle->Targets[HUB_Handle->hubClassRequestPort - 1];
				// if (HUB_Handle->hubClassRequestPort < 1)
				// 	USBH_ErrLog("ASSERT FAILED: hubClassRequestPort == %u", HUB_Handle->hubClassRequestPort);

				//printhex(HUB_Handle->buffer, HUB_Handle->buffer, sizeof (USB_HUB_PORT_STATUS));
				USB_HUB_PORT_STATUS *const st = (USB_HUB_PORT_STATUS *)HUB_Handle->buffer;
				// ИНтерпретируем результаты (Interpreting the results)
				// debug_port(HUB_Handle->buffer, st);
				// TODO: если выбрана енумерация LOW SPEED устройста, при установленной HIGH SPEED flash не проходит енумерация.
				// (TODO: if LOW SPEED device enumeration is selected, enumeration does not pass when HIGH SPEED flash is installed)
				if (st->wPortStatus.PORT_ENABLE /* && HUB_Handle->hubClassRequestPort > 1 */) {
					if (st->wPortStatus.PORT_LOW_SPEED) {
						// LOW SPEED, мышка - нашлась. (mouse found)
						HUB_Handle->detectedPorts += 1;

						tg->tt_hubaddr = phost->currentTarget->dev_address;
						tg->dev_address = USBH_ADDRESS_DEFAULT;
						tg->speed = USBH_SPEED_LOW;
						tg->tt_prtaddr = HUB_Handle->hubClassRequestPort;

						USBH_UsrLog("port %d status val=%04X: conn=%d, ena=%d, pwr=%d, hs=%d, ls=%d - LS device",
									HUB_Handle->hubClassRequestPort,
									st->wPortStatus.val,
									st->wPortStatus.PORT_CONNECTION,
									st->wPortStatus.PORT_ENABLE,
									st->wPortStatus.PORT_POWER,
									st->wPortStatus.PORT_HIGH_SPEED,
									st->wPortStatus.PORT_LOW_SPEED);

						phost->currentTarget = tg;
					} else if (st->wPortStatus.PORT_HIGH_SPEED) {
						// HIGH SPEED, флешка - нашлась.
						HUB_Handle->detectedPorts += 1;

						tg->tt_hubaddr = phost->currentTarget->dev_address;
						tg->dev_address = USBH_ADDRESS_DEFAULT;
						tg->speed = USBH_SPEED_HIGH;
						tg->tt_prtaddr = HUB_Handle->hubClassRequestPort;

						USBH_UsrLog("port %d status val=%04X: conn=%d, ena=%d, pwr=%d, hs=%d, ls=%d - HS device",
									HUB_Handle->hubClassRequestPort,
									st->wPortStatus.val,
									st->wPortStatus.PORT_CONNECTION,
									st->wPortStatus.PORT_ENABLE,
									st->wPortStatus.PORT_POWER,
									st->wPortStatus.PORT_HIGH_SPEED,
									st->wPortStatus.PORT_LOW_SPEED);

						phost->currentTarget = tg;
					} else {
						// FULL SPEED
						HUB_Handle->detectedPorts += 1;

						tg->tt_hubaddr = phost->currentTarget->dev_address;
						tg->dev_address = USBH_ADDRESS_DEFAULT;
						tg->speed = USBH_SPEED_FULL;
						tg->tt_prtaddr = HUB_Handle->hubClassRequestPort;

						USBH_UsrLog("port %d status val=%04X: conn=%d, ena=%d, pwr=%d, hs=%d, ls=%d - FS device",
									HUB_Handle->hubClassRequestPort,
									st->wPortStatus.val,
									st->wPortStatus.PORT_CONNECTION,
									st->wPortStatus.PORT_ENABLE,
									st->wPortStatus.PORT_POWER,
									st->wPortStatus.PORT_HIGH_SPEED,
									st->wPortStatus.PORT_LOW_SPEED);

						phost->currentTarget = tg;
					}
				} else {
					USBH_memset(tg, 0, sizeof *tg);

					USBH_UsrLog("port %d status val=%04X: conn=%d, ena=%d, pwr=%d, hs=%d, ls=%d",
								HUB_Handle->hubClassRequestPort,
								st->wPortStatus.val,
								st->wPortStatus.PORT_CONNECTION,
								st->wPortStatus.PORT_ENABLE,
								st->wPortStatus.PORT_POWER,
								st->wPortStatus.PORT_HIGH_SPEED,
								st->wPortStatus.PORT_LOW_SPEED);
				}

				// Reach last port
				if (HUB_Handle->NumPorts <= HUB_Handle->hubClassRequestPort) {
					// выходим из цикла (exit the loop)
					HUB_Handle->ctl_state = HUB_REQ_SCAN_STATUSES_DONE;
					status = USBH_BUSY;

				} else {
					HUB_Handle->hubClassRequestPort++;
					status = USBH_BUSY;
				}

			} else if (status == USBH_BUSY) {

			} else {
				// выходим по ошибке (we leave by mistake)
				HUB_Handle->ctl_state = HUB_REQ_IDLE;
				status = USBH_OK;
			}
			break;

		case HUB_REQ_SCAN_STATUSES_DONE:
			USBH_UsrLog("=============================================");

			USBH_UsrLog("Detected %d USB devices on HUB.", (int)HUB_Handle->detectedPorts);
			if (HUB_Handle->detectedPorts == 0) {
				return USBH_OK;
			}

			/* free Interrupt pipe */
			if (HUB_Handle->InPipe != 0x00) {
				USBH_ClosePipe(phost, HUB_Handle->InPipe);
				USBH_FreePipe(phost, HUB_Handle->InPipe);
				HUB_Handle->InPipe = 0; // Reset the pipe as Free
			}

			/* free control pipes */
			USBH_ClosePipe(phost, phost->Control.pipe_out);
			(void)USBH_FreePipe(phost, phost->Control.pipe_out);
			USBH_ClosePipe(phost, phost->Control.pipe_in);
			(void)USBH_FreePipe(phost, phost->Control.pipe_in);

			HUB_Handle->ctl_state = HUB_ALREADY_INITED;
			status = USBH_HUB_REQ_REENUMERATE;
			break;

		case HUB_DELAY:
			if ((HAL_GetTick() - HUB_Handle->tickstart) >= HUB_Handle->wait)
				HUB_Handle->ctl_state = HUB_Handle->ctl_state_push;
			status = USBH_BUSY;
			break;

		case HUB_ALREADY_INITED:
			USBH_DbgLog("Hub already init");
			phost->busy = 0;
			status = USBH_OK;
			break;
			//////////////////////////////////////

		case HUB_REQ_DONE:
			USBH_DbgLog("Hub done init");
			phost->busy = 0;
			status = USBH_OK;
			break;

		default:
			status = USBH_OK;
			break;
	}

	return status;
}

static USBH_StatusTypeDef USBH_HUB_Process(USBH_HandleTypeDef *phost) {
	/* не требуется, но по стилю = чтобы продолжались вызовы */
	// (not required, but in style = to keep the calls going)
	// USBH_DbgLog("USBH_HUB_Process (host handle %p)", phost);
	USBH_StatusTypeDef status = USBH_OK; //hftrx USBH_BUSY

	HUB_HandleTypeDef *const HUB_Handle = (HUB_HandleTypeDef *)phost->classData[0];

	switch (HUB_Handle->state) {
		case HUB_IDLE:
			HUB_Handle->HUB_CurPort = 0;
			HUB_Handle->state = HUB_SYNC;
			break;

		case HUB_SYNC:
			/* Sync with start of Even Frame */
			if ((phost->Timer & 0x01) != 0) {
				HUB_Handle->state = HUB_GET_DATA;
			}
			break;

		case HUB_GET_DATA:
			//			if(hUSBHost[1].busy)
			//				break;

			USBH_InterruptReceiveData(phost, HUB_Handle->buffer, HUB_Handle->length, HUB_Handle->InPipe);
			HUB_Handle->state = HUB_POLL;
			//HUB_Handle->state = HUB_PORT_CHANGED;
			HUB_Handle->timer = phost->Timer;
			HUB_Handle->DataReady = 0;
			break;

		case HUB_POLL: {
			const USBH_URBStateTypeDef urbState = USBH_LL_GetURBState(phost, HUB_Handle->InPipe);

			if (urbState == USBH_URB_DONE) {
				USBH_UsrLog("USBH_HUB_Process: HUB_POLL, HUB_CurPort=%d, answer=%02X,%02X (len=%d)",
							(int)HUB_Handle->HUB_CurPort,
							HUB_Handle->buffer[0],
							HUB_Handle->buffer[1],
							HUB_Handle->length);

				if (HUB_Handle->DataReady == 0) {
					HUB_Handle->DataReady = 1;
					if (port_changed(HUB_Handle, HUB_Handle->buffer))
						HUB_Handle->state = HUB_LOOP_PORT_CHANGED;
					else
						HUB_Handle->state = HUB_GET_DATA;
				}
			} else if (urbState == USBH_URB_STALL) /* IN Endpoint Stalled */ {
				// Issue Clear Feature on interrupt IN endpoint
				if ((USBH_ClrFeature(phost, HUB_Handle->ep_addr)) == USBH_OK) {
					// Change state to issue next IN token
					HUB_Handle->state = HUB_GET_DATA;
				}
			} else if (urbState == USBH_URB_ERROR) {
				USBH_ErrLog("=urb error=");
			} else {
				// URB_IDLE
			}

		} break;

		case HUB_LOOP_PORT_CHANGED:
			HUB_Handle->HUB_CurPort = get_port_changed(HUB_Handle);
			if (HUB_Handle->HUB_CurPort > 0) {
				USBH_UsrLog("LOOP PORT CHANGED: HUB_CurPort %d", HUB_Handle->HUB_CurPort);

				phost->busy = 1; //commented out hftrx
				clear_port_changed(HUB_Handle, HUB_Handle->HUB_CurPort);
				HUB_Handle->state = HUB_PORT_CHANGED;
			} else
				HUB_Handle->state = HUB_IDLE;

			break;
			//
		case HUB_PORT_CHANGED:
			// uses EP0
			if (get_hub_request(phost,
								USB_REQUEST_GET_STATUS,
								HUB_FEAT_SEL_PORT_CONN,
								HUB_Handle->HUB_CurPort,
								HUB_Handle->buffer,
								sizeof(USB_HUB_PORT_STATUS)) == USBH_OK)
			{
				HUB_Handle->pChangeInfo = (USB_HUB_PORT_STATUS *)HUB_Handle->buffer;

				debug_port(HUB_Handle->HUB_CurPort, HUB_Handle->buffer, HUB_Handle->pChangeInfo);

				if (HUB_Handle->pChangeInfo->wPortStatus.PORT_POWER) {
					if (HUB_Handle->pChangeInfo->wPortChange.C_PORT_OVER_CURRENT) {
						HUB_Handle->state = HUB_C_PORT_OVER_CURRENT;
						break;
					}

					if (HUB_Handle->pChangeInfo->wPortChange.C_PORT_SUSPEND) {
						HUB_Handle->state = HUB_C_PORT_SUSPEND;
						break;
					}

					if (HUB_Handle->pChangeInfo->wPortChange.C_PORT_CONNECTION) {
						HUB_Handle->state = HUB_C_PORT_CONNECTION;
					} else {
						if (HUB_Handle->pChangeInfo->wPortStatus.PORT_CONNECTION) {
							if (HUB_Handle->pChangeInfo->wPortStatus.PORT_RESET) {
								HUB_Handle->state = HUB_PORT_CHANGED;
							} else if (HUB_Handle->pChangeInfo->wPortChange.C_PORT_RESET) {
								HUB_Handle->state = HUB_C_PORT_RESET;
							} else if (HUB_Handle->pChangeInfo->wPortStatus.PORT_ENABLE) {
								// Device Attached
								/*								if(pChangeInfo->wPortStatus.PORT_LOW_SPEED)
											{
												//phost->hubBusy = 0;
												HUB_Handle->state = HUB_LOOP_PORT_CHANGED;
											}
											else*/
								HUB_Handle->state = HUB_DEV_ATTACHED;
							} else {
								HUB_Handle->state = HUB_RESET_DEVICE;
							}
						} else {
							// Device Detached
							HUB_Handle->state = HUB_DEV_DETACHED;
						}
					}
				}
			}
			break;

		case HUB_C_PORT_SUSPEND:
			if (clear_port_feature(phost, HUB_FEAT_SEL_C_PORT_SUSPEND, HUB_Handle->HUB_CurPort) == USBH_OK) {
				HUB_Handle->state = HUB_PORT_CHANGED;
			}
			break;

		case HUB_C_PORT_OVER_CURRENT:
			if (clear_port_feature(phost, HUB_FEAT_SEL_C_PORT_OVER_CURRENT, HUB_Handle->HUB_CurPort) == USBH_OK) {
				HUB_Handle->state = HUB_PORT_CHANGED;
			}
			break;

		case HUB_C_PORT_CONNECTION:
			if (clear_port_feature(phost, HUB_FEAT_SEL_C_PORT_CONNECTION, HUB_Handle->HUB_CurPort) == USBH_OK) {
				HUB_Handle->state = HUB_PORT_CHANGED;
			}
			break;

		case HUB_C_PORT_RESET:
			if (clear_port_feature(phost, HUB_FEAT_SEL_C_PORT_RESET, HUB_Handle->HUB_CurPort) == USBH_OK) {
				HUB_Handle->state = HUB_PORT_CHANGED;
			}
			break;

		case HUB_RESET_DEVICE:
			if (set_port_feature(phost, HUB_FEAT_SEL_PORT_RESET, HUB_Handle->HUB_CurPort) == USBH_OK) {
				USBH_Delay(150);
				HUB_Handle->state = HUB_PORT_CHANGED;
			}
			break;

		case HUB_DEV_ATTACHED:
			USBH_UsrLog("HUB_DEV_ATTACHED %d, lowspeed? %d highspeed? %d",
						HUB_Handle->HUB_CurPort,
						HUB_Handle->pChangeInfo->wPortStatus.PORT_LOW_SPEED,
						HUB_Handle->pChangeInfo->wPortStatus.PORT_HIGH_SPEED);

			HUB_Handle->state = HUB_LOOP_PORT_WAIT;
			{
				uint8_t speed = HUB_Handle->pChangeInfo->wPortStatus.PORT_LOW_SPEED	 ? USBH_SPEED_LOW :
								HUB_Handle->pChangeInfo->wPortStatus.PORT_HIGH_SPEED ? USBH_SPEED_HIGH :
																					   USBH_SPEED_FULL;
				attach(phost, HUB_Handle->HUB_CurPort, speed);
			}
			phost->busy = 0;
			break;

		case HUB_DEV_DETACHED:
			USBH_UsrLog("HUB_DEV_DETACHED %d", HUB_Handle->HUB_CurPort);

			HUB_Handle->state = HUB_LOOP_PORT_WAIT;
			detach(phost, HUB_Handle->HUB_CurPort);
			phost->busy = 0;
			break;

		case HUB_LOOP_PORT_WAIT:
			USBH_Delay(10);
			HUB_Handle->state = HUB_LOOP_PORT_CHANGED;
			break;

		case HUB_ERROR:
		default:
			break;
	}

	return status;
}

static USBH_StatusTypeDef USBH_HUB_SOFProcess(USBH_HandleTypeDef *phost) {
	HUB_HandleTypeDef *const HUB_Handle = (HUB_HandleTypeDef *)phost->classData[0];
	if (!phost->hubInstances) {
		USBH_ErrLog("HUB_SOFProcess: Not a hub!");
		return USBH_OK;
	}

	if (HUB_Handle->poll < HUB_POLL)
		USBH_UsrLog("ERR %d %d", HUB_Handle->poll, HUB_Handle->length);

	if (HUB_Handle->state == HUB_POLL) {
		if ((phost->Timer - HUB_Handle->timer) >= HUB_Handle->poll) {
			HUB_Handle->state = HUB_GET_DATA;
		}
	}

	return USBH_OK;
}

USBH_ClassTypeDef HUB_Class = {
	"HUB",
	USB_HUB_CLASS,
	USBH_HUB_InterfaceInit,
	USBH_HUB_InterfaceDeInit,
	USBH_HUB_ClassRequest,
	USBH_HUB_Process,
	USBH_HUB_SOFProcess,
	// NULL,
};
