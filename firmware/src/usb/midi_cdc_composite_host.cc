#include "midi_cdc_composite_host.hh"
#include "usb_host_helper.hh"

MidiCdcCompositeHost::MidiCdcCompositeHost(USBH_HandleTypeDef &usbhh)
	: usbhost{usbhh}
	, midi_tx_stream{make_midi_transmit_lambda()}
	, cdc_tx_stream{make_cdc_transmit_lambda()}
	, composite_class_ops{
		  "MIDI",
		  AudioClassCode,
		  composite_interface_init,
		  composite_interface_deinit,
		  composite_class_request,
		  composite_process,
		  composite_sof_process,
		  &composite_handle,
	  } {

	composite_handle.midi.tx_callback = [this]() {
		midi_tx_stream.tx_done_callback();
	};

	instance = this;
}

std::function<bool(std::span<uint8_t>)> MidiCdcCompositeHost::make_midi_transmit_lambda() {
	return [this](std::span<uint8_t> bytes) {
		auto res = USBH_MIDI_Transmit_Direct(&usbhost, &composite_handle.midi, bytes.data(), bytes.size());
		if (res == USBH_BUSY) {
			pr_err("MIDI Host: USBH is busy, cannot send\n");
		}
		return res == USBH_OK;
	};
}

std::function<bool(std::span<uint8_t>)> MidiCdcCompositeHost::make_cdc_transmit_lambda() {
	return [this](std::span<uint8_t> bytes) {
		auto *cdc = &composite_handle.cdc;
		if (!composite_handle.cdc_available)
			return false;

		if ((cdc->state == CDC_IDLE_STATE) || (cdc->state == CDC_TRANSFER_DATA)) {
			cdc->pTxData = bytes.data();
			cdc->TxDataLength = bytes.size();
			cdc->state = CDC_TRANSFER_DATA;
			cdc->data_tx_state = CDC_SEND_DATA;
			return true;
		}
		return false;
	};
}

void MidiCdcCompositeHost::init() {
	pr_info("Registering MIDI+CDC composite host\n");
	USBH_RegisterClass(&usbhost, &composite_class_ops);
	midi_tx_stream = DoubleBufferStream<uint8_t, 64>{make_midi_transmit_lambda()};
	cdc_tx_stream = DoubleBufferStream<uint8_t, 256>{make_cdc_transmit_lambda()};
}

void MidiCdcCompositeHost::connect() {
	_is_connected = true;
}

void MidiCdcCompositeHost::disconnect() {
	_is_connected = false;
	composite_handle.cdc_available = false;
}

bool MidiCdcCompositeHost::is_connected() {
	return _is_connected;
}

bool MidiCdcCompositeHost::transmit(std::span<uint8_t> bytes) {
	return midi_tx_stream.transmit(bytes);
}

void MidiCdcCompositeHost::set_rx_callback(MidiStreamRxCallbackType rx_callback) {
	composite_handle.midi.rx_callback = rx_callback;
}

USBH_StatusTypeDef MidiCdcCompositeHost::receive() {
	return USBH_MIDI_Receive_Direct(&usbhost, &composite_handle.midi, composite_handle.midi.rx_buffer, 128);
}

bool MidiCdcCompositeHost::is_cdc_available() {
	return composite_handle.cdc_available;
}

bool MidiCdcCompositeHost::cdc_transmit(std::span<uint8_t> bytes) {
	if (!composite_handle.cdc_available || !_is_connected)
		return false;
	return cdc_tx_stream.transmit(bytes);
}

void MidiCdcCompositeHost::set_cdc_rx_callback(CDCRxCallbackType cb) {
	cdc_rx_callback = cb;
}

bool MidiCdcCompositeHost::set_cdc_line_coding(uint32_t baud_rate, uint8_t data_bits, uint8_t stop_bits, uint8_t parity) {
	if (!composite_handle.cdc_available || !_is_connected)
		return false;

	auto *cdc = &composite_handle.cdc;
	cdc->LineCoding.b.dwDTERate = baud_rate;
	cdc->LineCoding.b.bDataBits = data_bits;
	cdc->LineCoding.b.bCharFormat = stop_bits;
	cdc->LineCoding.b.bParityType = parity;

	cdc->pUserLineCoding = &cdc->LineCoding;
	cdc->state = CDC_SET_LINE_CODING_STATE;
	return true;
}

bool MidiCdcCompositeHost::set_cdc_control_line_state(bool dtr, bool rts) {
	if (!composite_handle.cdc_available || !_is_connected)
		return false;

	// Find the CDC Communication interface to get the correct interface number
	uint8_t comm_itf = USBH_FindInterface(&usbhost, COMMUNICATION_INTERFACE_CLASS_CODE,
										   ABSTRACT_CONTROL_MODEL, NO_CLASS_SPECIFIC_PROTOCOL_CODE);
	if (comm_itf == 0xFF)
		comm_itf = USBH_FindInterface(&usbhost, COMMUNICATION_INTERFACE_CLASS_CODE, 0xFF, 0xFF);

	uint16_t wValue = 0;
	if (dtr) wValue |= CDC_ACTIVATE_SIGNAL_DTR;
	if (rts) wValue |= CDC_ACTIVATE_CARRIER_SIGNAL_RTS;

	usbhost.Control.setup.b.bmRequestType = USB_H2D | USB_REQ_TYPE_CLASS | USB_REQ_RECIPIENT_INTERFACE;
	usbhost.Control.setup.b.bRequest = CDC_SET_CONTROL_LINE_STATE;
	usbhost.Control.setup.b.wValue.w = wValue;
	usbhost.Control.setup.b.wIndex.w = (comm_itf != 0xFF) ? comm_itf : 0;
	usbhost.Control.setup.b.wLength.w = 0;

	auto result = USBH_CtlReq(&usbhost, nullptr, 0);
	return result == USBH_OK;
}

USBH_StatusTypeDef MidiCdcCompositeHost::cdc_receive() {
	if (!composite_handle.cdc_available || !_is_connected)
		return USBH_FAIL;

	auto *cdc = &composite_handle.cdc;
	if ((cdc->state == CDC_IDLE_STATE) || (cdc->state == CDC_TRANSFER_DATA)) {
		cdc->pRxData = cdc_rx_buffer;
		cdc->RxDataLength = sizeof(cdc_rx_buffer);
		cdc->state = CDC_TRANSFER_DATA;
		cdc->data_rx_state = CDC_RECEIVE_DATA;
		return USBH_OK;
	}
	return USBH_BUSY;
}

void MidiCdcCompositeHost::on_cdc_tx_done() {
	cdc_tx_stream.tx_done_callback();
}

void MidiCdcCompositeHost::on_cdc_rx_done() {
	if (cdc_rx_callback) {
		uint32_t len = USBH_LL_GetLastXferSize(&usbhost, composite_handle.cdc.DataItf.InPipe);
		if (len > 0) {
			cdc_rx_callback(cdc_rx_buffer, len);
		}
	}
	// Re-arm receive
	cdc_receive();
}

// --- Composite class driver static callbacks ---

USBH_StatusTypeDef MidiCdcCompositeHost::composite_interface_init(USBH_HandleTypeDef *phost) {
	auto *handle = static_cast<MidiCdcCompositeHandle *>(phost->pActiveClass->pData);
	if (!handle)
		return USBH_FAIL;

	// 1. Initialize MIDI (required)
	auto status = USBH_MIDI_InterfaceInit_Direct(phost, &handle->midi);
	if (status != USBH_OK) {
		pr_err("Composite: MIDI init failed\n");
		return USBH_FAIL;
	}
	pr_trace("Composite: MIDI interface initialized\n");

	// 2. Opportunistically look for CDC interfaces
	USBHostHelper host{phost};
	handle->cdc_available = false;

	uint8_t comm_itf = USBH_FindInterface(phost, COMMUNICATION_INTERFACE_CLASS_CODE,
										   ABSTRACT_CONTROL_MODEL, NO_CLASS_SPECIFIC_PROTOCOL_CODE);
	if (comm_itf == 0xFF || comm_itf >= USBH_MAX_NUM_INTERFACES) {
		// Try with any subclass/protocol
		comm_itf = USBH_FindInterface(phost, COMMUNICATION_INTERFACE_CLASS_CODE, 0xFF, 0xFF);
	}

	uint8_t data_itf = USBH_FindInterface(phost, DATA_INTERFACE_CLASS_CODE,
										   RESERVED, NO_CLASS_SPECIFIC_PROTOCOL_CODE);
	if (data_itf == 0xFF || data_itf >= USBH_MAX_NUM_INTERFACES) {
		data_itf = USBH_FindInterface(phost, DATA_INTERFACE_CLASS_CODE, 0xFF, 0xFF);
	}

	if (comm_itf == 0xFF || data_itf == 0xFF || comm_itf >= USBH_MAX_NUM_INTERFACES || data_itf >= USBH_MAX_NUM_INTERFACES) {
		pr_trace("Composite: No CDC interfaces found, MIDI-only mode\n");
		return USBH_OK;
	}

	pr_trace("Composite: Found CDC comm itf=%d, data itf=%d\n", comm_itf, data_itf);

	auto *cdc = &handle->cdc;
	USBH_memset(cdc, 0, sizeof(CDC_HandleTypeDef));

	// Setup notification endpoint from communication interface
	if ((phost->device.CfgDesc.Itf_Desc[comm_itf].Ep_Desc[0].bEndpointAddress & 0x80U) != 0U) {
		cdc->CommItf.NotifEp = phost->device.CfgDesc.Itf_Desc[comm_itf].Ep_Desc[0].bEndpointAddress;
		cdc->CommItf.NotifEpSize = phost->device.CfgDesc.Itf_Desc[comm_itf].Ep_Desc[0].wMaxPacketSize;
	}

	cdc->CommItf.NotifPipe = USBH_AllocPipe(phost, cdc->CommItf.NotifEp);
	USBH_OpenPipe(phost, cdc->CommItf.NotifPipe, cdc->CommItf.NotifEp,
				   phost->device.address, phost->device.speed, USB_EP_TYPE_INTR,
				   cdc->CommItf.NotifEpSize);

	// Setup data endpoints from data interface
	if ((phost->device.CfgDesc.Itf_Desc[data_itf].Ep_Desc[0].bEndpointAddress & 0x80U) != 0U) {
		cdc->DataItf.InEp = phost->device.CfgDesc.Itf_Desc[data_itf].Ep_Desc[0].bEndpointAddress;
		cdc->DataItf.InEpSize = phost->device.CfgDesc.Itf_Desc[data_itf].Ep_Desc[0].wMaxPacketSize;
	} else {
		cdc->DataItf.OutEp = phost->device.CfgDesc.Itf_Desc[data_itf].Ep_Desc[0].bEndpointAddress;
		cdc->DataItf.OutEpSize = phost->device.CfgDesc.Itf_Desc[data_itf].Ep_Desc[0].wMaxPacketSize;
	}

	if ((phost->device.CfgDesc.Itf_Desc[data_itf].Ep_Desc[1].bEndpointAddress & 0x80U) != 0U) {
		cdc->DataItf.InEp = phost->device.CfgDesc.Itf_Desc[data_itf].Ep_Desc[1].bEndpointAddress;
		cdc->DataItf.InEpSize = phost->device.CfgDesc.Itf_Desc[data_itf].Ep_Desc[1].wMaxPacketSize;
	} else {
		cdc->DataItf.OutEp = phost->device.CfgDesc.Itf_Desc[data_itf].Ep_Desc[1].bEndpointAddress;
		cdc->DataItf.OutEpSize = phost->device.CfgDesc.Itf_Desc[data_itf].Ep_Desc[1].wMaxPacketSize;
	}

	cdc->DataItf.OutPipe = USBH_AllocPipe(phost, cdc->DataItf.OutEp);
	cdc->DataItf.InPipe = USBH_AllocPipe(phost, cdc->DataItf.InEp);

	USBH_OpenPipe(phost, cdc->DataItf.OutPipe, cdc->DataItf.OutEp,
				   phost->device.address, phost->device.speed, USB_EP_TYPE_BULK,
				   cdc->DataItf.OutEpSize);

	USBH_OpenPipe(phost, cdc->DataItf.InPipe, cdc->DataItf.InEp,
				   phost->device.address, phost->device.speed, USB_EP_TYPE_BULK,
				   cdc->DataItf.InEpSize);

	cdc->state = CDC_IDLE_STATE;

	USBH_LL_SetToggle(phost, cdc->DataItf.OutPipe, 0U);
	USBH_LL_SetToggle(phost, cdc->DataItf.InPipe, 0U);

	handle->cdc_available = true;
	pr_trace("Composite: CDC interface initialized\n");

	return USBH_OK;
}

USBH_StatusTypeDef MidiCdcCompositeHost::composite_interface_deinit(USBH_HandleTypeDef *phost) {
	auto *handle = static_cast<MidiCdcCompositeHandle *>(phost->pActiveClass->pData);
	if (!handle)
		return USBH_FAIL;

	USBH_MIDI_InterfaceDeInit_Direct(phost, &handle->midi);

	if (handle->cdc_available) {
		auto *cdc = &handle->cdc;

		if (cdc->CommItf.NotifPipe != 0U) {
			USBH_ClosePipe(phost, cdc->CommItf.NotifPipe);
			USBH_FreePipe(phost, cdc->CommItf.NotifPipe);
			cdc->CommItf.NotifPipe = 0U;
		}
		if (cdc->DataItf.InPipe != 0U) {
			USBH_ClosePipe(phost, cdc->DataItf.InPipe);
			USBH_FreePipe(phost, cdc->DataItf.InPipe);
			cdc->DataItf.InPipe = 0U;
		}
		if (cdc->DataItf.OutPipe != 0U) {
			USBH_ClosePipe(phost, cdc->DataItf.OutPipe);
			USBH_FreePipe(phost, cdc->DataItf.OutPipe);
			cdc->DataItf.OutPipe = 0U;
		}
		handle->cdc_available = false;
	}

	return USBH_OK;
}

USBH_StatusTypeDef MidiCdcCompositeHost::composite_class_request(USBH_HandleTypeDef *phost) {
	// Skip GetLineCoding which can fail on some devices — go straight to CLASS_ACTIVE
	if (phost->pUser)
		phost->pUser(phost, HOST_USER_CLASS_ACTIVE);

	return USBH_OK;
}

USBH_StatusTypeDef MidiCdcCompositeHost::composite_process(USBH_HandleTypeDef *phost) {
	auto *handle = static_cast<MidiCdcCompositeHandle *>(phost->pActiveClass->pData);
	if (!handle)
		return USBH_FAIL;

	// Run MIDI state machine
	auto *midi = &handle->midi;
	switch (midi->state) {
		case MidiStreamingState::Idle:
			break;
		case MidiStreamingState::TransferData:
			MIDI_ProcessTransmission_Direct(phost, midi);
			MIDI_ProcessReception_Direct(phost, midi);
			break;
		case MidiStreamingState::Error: {
			USBH_StatusTypeDef req_status = USBH_ClrFeature(phost, 0x00U);
			if (req_status == USBH_OK) {
				midi->state = MidiStreamingState::Idle;
			}
		} break;
	}

	// Run CDC state machine if available
	if (handle->cdc_available) {
		auto *cdc = &handle->cdc;
		USBH_StatusTypeDef req_status;

		switch (cdc->state) {
			case CDC_IDLE_STATE:
				break;

			case CDC_SET_LINE_CODING_STATE:
				// Inline SetLineCoding control request
				phost->Control.setup.b.bmRequestType = USB_H2D | USB_REQ_TYPE_CLASS | USB_REQ_RECIPIENT_INTERFACE;
				phost->Control.setup.b.bRequest = CDC_SET_LINE_CODING;
				phost->Control.setup.b.wValue.w = 0U;
				phost->Control.setup.b.wIndex.w = 0U;
				phost->Control.setup.b.wLength.w = LINE_CODING_STRUCTURE_SIZE;

				req_status = USBH_CtlReq(phost, cdc->pUserLineCoding->Array, LINE_CODING_STRUCTURE_SIZE);
				if (req_status == USBH_OK) {
					cdc->state = CDC_IDLE_STATE;
				} else if (req_status != USBH_BUSY) {
					cdc->state = CDC_ERROR_STATE;
				}
				break;

			case CDC_GET_LAST_LINE_CODING_STATE:
				// Skip this state — go straight to idle
				cdc->state = CDC_IDLE_STATE;
				break;

			case CDC_TRANSFER_DATA:
				cdc_process_transmission(phost, cdc);
				cdc_process_reception(phost, cdc);
				break;

			case CDC_ERROR_STATE:
				req_status = USBH_ClrFeature(phost, 0x00U);
				if (req_status == USBH_OK) {
					cdc->state = CDC_IDLE_STATE;
				}
				break;

			default:
				break;
		}
	}

	return USBH_BUSY;
}

USBH_StatusTypeDef MidiCdcCompositeHost::composite_sof_process(USBH_HandleTypeDef *phost) {
	(void)phost;
	return USBH_OK;
}

void MidiCdcCompositeHost::cdc_process_transmission(USBH_HandleTypeDef *phost, CDC_HandleTypeDef *cdc) {
	USBH_URBStateTypeDef URB_Status = USBH_URB_IDLE;

	switch (cdc->data_tx_state) {
		case CDC_SEND_DATA:
			if (cdc->TxDataLength > cdc->DataItf.OutEpSize) {
				USBH_BulkSendData(phost, cdc->pTxData, cdc->DataItf.OutEpSize, cdc->DataItf.OutPipe, 1U);
			} else {
				USBH_BulkSendData(phost, cdc->pTxData, (uint16_t)cdc->TxDataLength, cdc->DataItf.OutPipe, 1U);
			}
			cdc->data_tx_state = CDC_SEND_DATA_WAIT;
			break;

		case CDC_SEND_DATA_WAIT:
			URB_Status = USBH_LL_GetURBState(phost, cdc->DataItf.OutPipe);

			if (URB_Status == USBH_URB_DONE) {
				if (cdc->TxDataLength > cdc->DataItf.OutEpSize) {
					cdc->TxDataLength -= cdc->DataItf.OutEpSize;
					cdc->pTxData += cdc->DataItf.OutEpSize;
				} else {
					cdc->TxDataLength = 0U;
				}

				if (cdc->TxDataLength > 0U) {
					cdc->data_tx_state = CDC_SEND_DATA;
				} else {
					cdc->data_tx_state = CDC_IDLE;
					if (instance)
						instance->on_cdc_tx_done();
				}
			} else if (URB_Status == USBH_URB_NOTREADY) {
				cdc->data_tx_state = CDC_SEND_DATA;
			}
			break;

		default:
			break;
	}
}

void MidiCdcCompositeHost::cdc_process_reception(USBH_HandleTypeDef *phost, CDC_HandleTypeDef *cdc) {
	USBH_URBStateTypeDef URB_Status = USBH_URB_IDLE;
	uint32_t length;

	switch (cdc->data_rx_state) {
		case CDC_RECEIVE_DATA:
			USBH_BulkReceiveData(phost, cdc->pRxData, cdc->DataItf.InEpSize, cdc->DataItf.InPipe);
			cdc->data_rx_state = CDC_RECEIVE_DATA_WAIT;
			break;

		case CDC_RECEIVE_DATA_WAIT:
			URB_Status = USBH_LL_GetURBState(phost, cdc->DataItf.InPipe);

			if (URB_Status == USBH_URB_DONE) {
				length = USBH_LL_GetLastXferSize(phost, cdc->DataItf.InPipe);

				if (((cdc->RxDataLength - length) > 0U) && (length == cdc->DataItf.InEpSize)) {
					cdc->RxDataLength -= length;
					cdc->pRxData += length;
					cdc->data_rx_state = CDC_RECEIVE_DATA;
				} else {
					cdc->data_rx_state = CDC_IDLE;
					if (instance)
						instance->on_cdc_rx_done();
				}
			}
			break;

		default:
			break;
	}
}
