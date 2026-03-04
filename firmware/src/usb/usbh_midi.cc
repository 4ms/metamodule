/**
 ******************************************************************************
 * @file    usbh_midi.cc
 * @author  Dan Green. Based on CDC Class in STM32 USB Host Library v3.5.0
 * @brief   USB Host Audio Class MIDI Streaming Subclass driver
 *
 *   See "Universal Serial Bus Device Class Definition for MIDI Devices"
 *   Revision 1.0 November 1, 1999
 *
 ******************************************************************************
 * @attention
 * Copyright (c) 2022 Dan Green.
 * Licensed by the MIT License, see LICENSE file
 *
 * Portions of this file may be also:
 * <h2><center>&copy; Copyright (c) 2015 STMicroelectronics.
 * All rights reserved.</center></h2>
 * This software component is licensed by ST under Ultimate Liberty license
 * SLA0044, the "License"; You may not use this file except in compliance with
 * the License. You may obtain a copy of the License at:
 *                      www.st.com/SLA0044
 *
 ******************************************************************************
 */

#include "usbh_midi.hh"
#include "usbh_midi_jacks.hh"

static void MIDI_ProcessTransmission(USBH_HandleTypeDef *phost);
static void MIDI_ProcessReception(USBH_HandleTypeDef *phost);

/**
 * @brief  USBH_MIDI_InterfaceInit_Direct
 *         Init the MIDI class using a directly-provided handle.
 * @param  phost: Host handle
 * @param  handle: MidiStreamingHandle to initialize
 * @retval USBH Status
 */
USBH_StatusTypeDef USBH_MIDI_InterfaceInit_Direct(USBH_HandleTypeDef *phost, MidiStreamingHandle *handle)
{
	USBH_StatusTypeDef status;
	uint8_t interface;

	if (handle == nullptr) {
		USBH_DbgLog("Cannot allocate memory for MIDI Handle");
		return USBH_FAIL;
	}

	USBHostHelper host{phost};

	// Look for an optional Audio Control interface
	interface = USBH_FindInterface(phost, AudioClassCode, AudioControlSubclassCode, AnyProtocol);
	if ((interface == NoValidInterfaceFound) || (interface >= USBH_MAX_NUM_INTERFACES)) {
		USBH_DbgLog("Did not find an audio control interface, continuing\n");
	} else {
		USBH_DbgLog("Found Audio Control subclass\n");
		host.link_endpoint_pipe(handle->ControlItf.ControlEP, interface, 0);
		host.open_pipe(handle->ControlItf.ControlEP, EndPointType::Intr);
		host.set_toggle(handle->ControlItf.ControlEP, 0);
	}

	// Look for MidiStreamingSubClass
	interface = USBH_FindInterface(phost, AudioClassCode, MidiStreamingSubClass, AnyProtocol);
	if ((interface == NoValidInterfaceFound) || (interface >= USBH_MAX_NUM_INTERFACES)) {
		USBH_DbgLog("Cannot find the interface for MIDI subclass.");
		return USBH_FAIL;
	}

	status = USBH_SelectInterface(phost, interface);
	if (status != USBH_OK)
		return USBH_FAIL;

	if (host.is_in_ep(interface, 0))
		host.link_endpoint_pipe(handle->DataItf.InEP, interface, 0);
	else
		host.link_endpoint_pipe(handle->DataItf.OutEP, interface, 0);

	if (host.is_in_ep(interface, 1))
		host.link_endpoint_pipe(handle->DataItf.InEP, interface, 1);
	else
		host.link_endpoint_pipe(handle->DataItf.OutEP, interface, 1);

	host.open_pipe(handle->DataItf.OutEP, EndPointType::Bulk);
	host.open_pipe(handle->DataItf.InEP, EndPointType::Bulk);

	handle->state = MidiStreamingState::Idle;

	host.set_toggle(handle->DataItf.OutEP, 0);
	host.set_toggle(handle->DataItf.InEP, 0);

	return USBH_OK;
}

/**
 * @brief  USBH_MIDI_InterfaceInit
 *         The function init the MIDI class (wrapper).
 */
USBH_StatusTypeDef USBH_MIDI_InterfaceInit(USBH_HandleTypeDef *phost)
{
	USBHostHelper host{phost};
	auto MSHandle = host.get_class_handle<MidiStreamingHandle>();
	return USBH_MIDI_InterfaceInit_Direct(phost, MSHandle);
}

/**
 * @brief  USBH_MIDI_InterfaceDeInit_Direct
 *         DeInit the Pipes using a directly-provided handle.
 */
USBH_StatusTypeDef USBH_MIDI_InterfaceDeInit_Direct(USBH_HandleTypeDef *phost, MidiStreamingHandle *handle)
{
	if (!handle)
		return USBH_FAIL;

	USBHostHelper host{phost};
	host.close_and_free_pipe(handle->ControlItf.ControlEP);
	host.close_and_free_pipe(handle->DataItf.InEP);
	host.close_and_free_pipe(handle->DataItf.OutEP);

	return USBH_OK;
}

/**
 * @brief  USBH_MIDI_InterfaceDeInit (wrapper)
 */
USBH_StatusTypeDef USBH_MIDI_InterfaceDeInit(USBH_HandleTypeDef *phost)
{
	USBHostHelper host{phost};
	auto MSHandle = host.get_class_handle<MidiStreamingHandle>();
	return USBH_MIDI_InterfaceDeInit_Direct(phost, MSHandle);
}

/**
 * @brief  USBH_MIDI_ClassRequest
 *         The function is responsible for handling Standard requests
 *         for MIDI class.
 * @param  phost: Host handle
 * @retval USBH Status
 */
USBH_StatusTypeDef USBH_MIDI_ClassRequest(USBH_HandleTypeDef *phost)
{
	if (phost->pUser)
		phost->pUser(phost, HOST_USER_CLASS_ACTIVE);

	return USBH_OK;
}

/**
 * @brief  USBH_MIDI_Process
 *         The function is for managing state machine for MIDI data transfers
 * @param  phost: Host handle
 * @retval USBH Status
 */
USBH_StatusTypeDef USBH_MIDI_Process(USBH_HandleTypeDef *phost)
{
	USBH_StatusTypeDef status = USBH_BUSY;

	USBHostHelper host{phost};
	auto MSHandle = host.get_class_handle<MidiStreamingHandle>();
	if (!MSHandle) {
		USBH_DbgLog("no mshandle");
		return USBH_FAIL;
	}

	switch (MSHandle->state) {
		case MidiStreamingState::Idle:
			status = USBH_OK;
			break;

		case MidiStreamingState::TransferData:
			MIDI_ProcessTransmission(phost);
			MIDI_ProcessReception(phost);
			break;

		case MidiStreamingState::Error: {
			USBH_StatusTypeDef req_status = USBH_ClrFeature(phost, 0x00U);

			if (req_status == USBH_OK) {
				MSHandle->state = MidiStreamingState::Idle;
			}
		} break;
	}

	return status;
}

/**
 * @brief  USBH_MIDI_SOFProcess
 *         The function is for managing SOF callback
 * @param  phost: Host handle
 * @retval USBH Status
 */
USBH_StatusTypeDef USBH_MIDI_SOFProcess(USBH_HandleTypeDef *phost)
{
	UNUSED(phost);
	return USBH_OK;
}

/**
 * @brief  USBH_MIDI_Stop
 *         Stop current MIDI Transmission
 * @param  phost: Host handle
 * @retval USBH Status
 */
USBH_StatusTypeDef USBH_MIDI_Stop(USBH_HandleTypeDef *phost)
{
	USBHostHelper host{phost};
	auto MSHandle = host.get_class_handle<MidiStreamingHandle>();
	if (!MSHandle)
		return USBH_FAIL;

	if (phost->gState == HOST_CLASS) {
		MSHandle->state = MidiStreamingState::Idle;

		USBH_ClosePipe(phost, MSHandle->ControlItf.ControlEP.pipe);
		USBH_ClosePipe(phost, MSHandle->DataItf.InEP.pipe);
		USBH_ClosePipe(phost, MSHandle->DataItf.OutEP.pipe);
	}
	return USBH_OK;
}

/**
 * @brief  This function return last received data size
 * @param  None
 * @retval None
 */
uint16_t USBH_MIDI_GetLastReceivedDataSize(USBH_HandleTypeDef *phost)
{
	USBHostHelper host{phost};
	auto MSHandle = host.get_class_handle<MidiStreamingHandle>();
	if (!MSHandle)
		return USBH_FAIL;

	uint32_t dataSize;

	if (phost->gState == HOST_CLASS) {
		dataSize = USBH_LL_GetLastXferSize(phost, MSHandle->DataItf.InEP.pipe);
	} else {
		dataSize = 0U;
	}

	return (uint16_t)dataSize;
}

/**
 * @brief  USBH_MIDI_Transmit_Direct — using a directly-provided handle.
 */
USBH_StatusTypeDef USBH_MIDI_Transmit_Direct(USBH_HandleTypeDef *phost, MidiStreamingHandle *handle, uint8_t *pbuff, uint32_t length)
{
	if (!handle)
		return USBH_FAIL;

	USBH_StatusTypeDef status = USBH_BUSY;

	if ((handle->state == MidiStreamingState::Idle) || (handle->state == MidiStreamingState::TransferData)) {
		handle->pTxData = pbuff;
		handle->TxDataLength = length;
		handle->state = MidiStreamingState::TransferData;
		handle->data_tx_state = MidiStreamingDataState::SendData;
		status = USBH_OK;

#if (USBH_USE_OS == 1U)
		phost->os_msg = (uint32_t)USBH_CLASS_EVENT;
		(void)osMessageQueuePut(phost->os_event, &phost->os_msg, 0U, NULL);
#endif
	}
	return status;
}

USBH_StatusTypeDef USBH_MIDI_Transmit(USBH_HandleTypeDef *phost, uint8_t *pbuff, uint32_t length)
{
	USBHostHelper host{phost};
	return USBH_MIDI_Transmit_Direct(phost, host.get_class_handle<MidiStreamingHandle>(), pbuff, length);
}

/**
 * @brief  USBH_MIDI_Receive_Direct — using a directly-provided handle.
 */
USBH_StatusTypeDef USBH_MIDI_Receive_Direct(USBH_HandleTypeDef *phost, MidiStreamingHandle *handle, uint8_t *pbuff, uint32_t length)
{
	if (!handle)
		return USBH_FAIL;

	USBH_StatusTypeDef status = USBH_BUSY;

	if ((handle->state == MidiStreamingState::Idle) || (handle->state == MidiStreamingState::TransferData)) {
		handle->pRxData = pbuff;
		handle->RxDataLength = length;
		handle->state = MidiStreamingState::TransferData;
		handle->data_rx_state = MidiStreamingDataState::ReceiveData;
		status = USBH_OK;

#if (USBH_USE_OS == 1U)
		phost->os_msg = (uint32_t)USBH_CLASS_EVENT;
		(void)osMessageQueuePut(phost->os_event, &phost->os_msg, 0U, NULL);
#endif
	}
	return status;
}

USBH_StatusTypeDef USBH_MIDI_Receive(USBH_HandleTypeDef *phost, uint8_t *pbuff, uint32_t length)
{
	USBHostHelper host{phost};
	return USBH_MIDI_Receive_Direct(phost, host.get_class_handle<MidiStreamingHandle>(), pbuff, length);
}

/**
 * @brief  MIDI_ProcessTransmission_Direct — using a directly-provided handle.
 */
void MIDI_ProcessTransmission_Direct(USBH_HandleTypeDef *phost, MidiStreamingHandle *handle)
{
	if (!handle)
		return;

	USBH_URBStateTypeDef URB_Status = USBH_URB_IDLE;

	switch (handle->data_tx_state) {
		case MidiStreamingDataState::SendData:
			if (handle->TxDataLength > handle->DataItf.OutEP.size) {
				USBH_BulkSendData(
					phost, handle->pTxData, handle->DataItf.OutEP.size, handle->DataItf.OutEP.pipe, 1U);
			} else {
				USBH_BulkSendData(
					phost, handle->pTxData, (uint16_t)handle->TxDataLength, handle->DataItf.OutEP.pipe, 1U);
			}

			handle->data_tx_state = MidiStreamingDataState::SendDataWait;
			break;

		case MidiStreamingDataState::SendDataWait:

			URB_Status = USBH_LL_GetURBState(phost, handle->DataItf.OutEP.pipe);

			if (URB_Status == USBH_URB_DONE) {
				if (handle->TxDataLength > handle->DataItf.OutEP.size) {
					handle->TxDataLength -= handle->DataItf.OutEP.size;
					handle->pTxData += handle->DataItf.OutEP.size;
				} else {
					handle->TxDataLength = 0U;
				}

				if (handle->TxDataLength > 0U) {
					handle->data_tx_state = MidiStreamingDataState::SendData;
				} else {
					handle->data_tx_state = MidiStreamingDataState::Idle;
					handle->tx_callback();
				}

#if (USBH_USE_OS == 1U)
				phost->os_msg = (uint32_t)USBH_CLASS_EVENT;
				(void)osMessageQueuePut(phost->os_event, &phost->os_msg, 0U, NULL);
#endif
			} else {
				if (URB_Status == USBH_URB_NOTREADY) {
					handle->data_tx_state = MidiStreamingDataState::SendData;

#if (USBH_USE_OS == 1U)
					phost->os_msg = (uint32_t)USBH_CLASS_EVENT;
					(void)osMessageQueuePut(phost->os_event, &phost->os_msg, 0U, NULL);
#endif
				}
			}
			break;

		default:
			break;
	}
}

/**
 * @brief  MIDI_ProcessReception_Direct — using a directly-provided handle.
 */
void MIDI_ProcessReception_Direct(USBH_HandleTypeDef *phost, MidiStreamingHandle *handle)
{
	if (!handle)
		return;

	USBH_URBStateTypeDef URB_Status = USBH_URB_IDLE;
	uint32_t length;

	switch (handle->data_rx_state) {

		case MidiStreamingDataState::ReceiveData:
			USBH_BulkReceiveData(phost, handle->pRxData, handle->DataItf.InEP.size, handle->DataItf.InEP.pipe);
			handle->data_rx_state = MidiStreamingDataState::ReceiveDataWait;
			break;

		case MidiStreamingDataState::ReceiveDataWait:
			URB_Status = USBH_LL_GetURBState(phost, handle->DataItf.InEP.pipe);

			if (URB_Status == USBH_URB_DONE) {
				length = USBH_LL_GetLastXferSize(phost, handle->DataItf.InEP.pipe);

				if (((handle->RxDataLength - length) > 0U) && (length > handle->DataItf.InEP.size)) {
					handle->RxDataLength -= length;
					handle->pRxData += length;
					handle->data_rx_state = MidiStreamingDataState::ReceiveData;
				} else {
					handle->data_rx_state = MidiStreamingDataState::Idle;
					handle->rx_callback(std::span<uint8_t>(handle->pRxData, length));
				}

#if (USBH_USE_OS == 1U)
				phost->os_msg = (uint32_t)USBH_CLASS_EVENT;
				(void)osMessageQueuePut(phost->os_event, &phost->os_msg, 0U, NULL);
#endif
			}
			break;

		default:
			break;
	}
}

static void MIDI_ProcessTransmission(USBH_HandleTypeDef *phost)
{
	USBHostHelper host{phost};
	MIDI_ProcessTransmission_Direct(phost, host.get_class_handle<MidiStreamingHandle>());
}

static void MIDI_ProcessReception(USBH_HandleTypeDef *phost)
{
	USBHostHelper host{phost};
	MIDI_ProcessReception_Direct(phost, host.get_class_handle<MidiStreamingHandle>());
}

// Note: To use this class like other STM32 Host Classes,
// Do something like this (in your application code):

// static MidiStreamingHandle MSHandle;
//
// USBH_ClassTypeDef MIDI_Class_Ops = {
// 	"MIDI",
// 	AudioClassCode,
// 	USBH_MIDI_InterfaceInit,
// 	USBH_MIDI_InterfaceDeInit,
// 	USBH_MIDI_ClassRequest,
// 	USBH_MIDI_Process,
// 	USBH_MIDI_SOFProcess,
// 	&MSHandle,
// };
