#include "usb_serial_device.hh"
#include "console/pr_dbg.hh"

extern USBD_CDC_ItfTypeDef USBD_CDC_fops;
extern USBD_DescriptorsTypeDef VCP_Desc;

namespace
{
USBD_CDC_LineCodingTypeDef LineCoding = {
	115200, /* baud rate */
	0x00,	/* stop bits-1 */
	0x00,	/* parity - none */
	0x08	/* nb. of bits 8 */
};
}

UsbSerialDevice::UsbSerialDevice(USBD_HandleTypeDef *pDevice, std::array<ConcurrentBuffer *, 3> console_buffers)
	: pdev{pDevice}
	, console_buffers{console_buffers} {
	rx_buffer.resize(256);
	_instance = this;
}

void UsbSerialDevice::start() {
	_instance = this;
	auto init_ok = USBD_Init(pdev, &VCP_Desc, 0);
	if (init_ok != USBD_OK) {
		pr_err("USB Serial Device failed to initialize!\r\n");
		pr_err("Error code: %d", static_cast<int>(init_ok));
		return;
	}

	for (auto i = 0u; auto const &buff : console_buffers)
		current_read_pos[i++] = buff->current_write_pos;

	USBD_RegisterClass(pdev, USBD_CDC_CLASS);
	USBD_CDC_RegisterInterface(pdev, &USBD_CDC_fops);
	USBD_Start(pdev);
	pr_info("Started UsbSerialDevice\n");
}

void UsbSerialDevice::stop() {
	pr_info("Stopping UsbSerialDevice\n");
	USBD_Stop(pdev);
	USBD_DeInit(pdev);
}

void UsbSerialDevice::transmit_buffers(Destination dest) {
	auto transmit = [this, dest = dest](uint8_t *ptr, int len) {
		if (dest == Destination::USB) {
			USBD_CDC_SetTxBuffer(pdev, ptr, len);

			if (auto err = USBD_CDC_TransmitPacket(pdev) == USBD_OK) {
				is_transmitting = true;
				last_transmission_tm = HAL_GetTick();

			} else if (err != USBD_BUSY) {
				pr_dbg("USB CDC Transmit Error: %d\n", err);
			}
		}

		if (dest == Destination::UART) {
			while (len--)
				putchar(*ptr++);
		}
	};


	// Check for binary data in any buffer
	bool has_binary_data = false;
	for (auto *buff : console_buffers) {
		if (buff->is_binary_data) {
			has_binary_data = true;
			break;
		}
	}

	// If we have binary data, we need to force transmission even if we're currently transmitting
	if (has_binary_data) {
		is_transmitting = false;
	} else {
		// Don't transmit if we already are transmitting
		// But have a 100ms timeout in case of a USB error
		if (is_transmitting) {
			if (HAL_GetTick() - last_transmission_tm > 100) {
				is_transmitting = false;
				last_transmission_tm = HAL_GetTick();
			} else
				return;
		}
	}

	// Scan buffers for data to transmit, and exit after first transmission
	for (auto i = 0u; auto *buff : console_buffers) {
		buff->use_color = use_color;

		if (buff->writer_ref_count == 0) {
			auto start_pos = current_read_pos[i];
			unsigned end_pos = buff->current_write_pos; //.load(std::memory_order_acquire);
			end_pos = end_pos & buff->buffer.SIZEMASK;

			if (start_pos > end_pos) {
				// Data to transmit spans the "seam" of the circular buffer,
				// Send the first chunk
				transmit(&buff->buffer.data[start_pos], buff->buffer.data.size() - start_pos);
				current_read_pos[i] = 0;
				
				// Clear binary data flag after transmission
				if (buff->is_binary_data) {
					buff->is_binary_data = false;
				}
				return;

			} else if (start_pos < end_pos) {
				transmit(&buff->buffer.data[start_pos], end_pos - start_pos);
				current_read_pos[i] = end_pos;
				
				// Clear binary data flag after transmission
				if (buff->is_binary_data) {
					buff->is_binary_data = false;
				}
				return;
			}
		}
		i++;
	}
}

void UsbSerialDevice::process() {
	transmit_buffers(Destination::USB);
}

void UsbSerialDevice::forward_to_uart() {
	transmit_buffers(Destination::UART);
}

int8_t UsbSerialDevice::CDC_Itf_Init() {
	USBD_CDC_SetTxBuffer(_instance->pdev, _instance->console_buffers[0]->buffer.data.data(), 0);
	USBD_CDC_SetRxBuffer(_instance->pdev, _instance->rx_buffer.data()); // FIXME: how does the driver prevent overflow?
	return USBD_OK;
}

/**
  * @brief  CDC_Itf_DeInit
  *         DeInitializes the CDC media low layer
  * @param  None
  * @retval Result of the operation: USBD_OK if all operations are OK else USBD_FAIL
  */
int8_t UsbSerialDevice::CDC_Itf_DeInit() {
	return USBD_OK;
}

/**
  * @brief  CDC_Itf_DataRx
  *         Data received over USB OUT endpoint are sent over CDC interface
  *         through this function.
  * @param  Buf: Buffer of data to be transmitted
  * @param  Len: Number of data received (in bytes)
  * @retval Result of the operation: USBD_OK if all operations are OK else USBD_FAIL
  */
int8_t UsbSerialDevice::CDC_Itf_Receive(uint8_t *Buf, uint32_t *Len) {
	if (*Buf == 'c')
		_instance->use_color = true;
	if (*Buf == 'm')
		_instance->use_color = false;

	pr_dbg("Rx: ");
	uint32_t len = *Len;
	while (len--)
		pr_dbg("%c", *Buf++);
	pr_dbg("\n");

	// Indicate that we're ready to receive more
	USBD_CDC_ReceivePacket(_instance->pdev);
	return USBD_OK;
}

/**
  * @brief  CDC_TransmitCplt
  *         Data transmitted callback
  *
  *         @note
  *         This function is IN transfer complete callback used to inform user that
  *         the submitted Data is successfully sent over USB.
  *
  * @param  Buf: Buffer of data to be received
  * @param  Len: Number of data received (in bytes)
  * @retval Result of the operation: USBD_OK if all operations are OK else USBD_FAIL
  */
int8_t UsbSerialDevice::CDC_TransmitCplt(uint8_t *Buf, uint32_t *Len, uint8_t epnum) {
	UNUSED(Buf);
	UNUSED(Len);
	UNUSED(epnum);
	_instance->is_transmitting = false;
	return 0;
}

/**
  * @brief  CDC_Itf_Control
  *         Manage the CDC class requests
  * @param  Cmd: Command code
  * @param  Buf: Buffer containing command data (request parameters)
  * @param  Len: Number of data to be sent (in bytes)
  * @retval Result of the operation: USBD_OK if all operations are OK else USBD_FAIL
  */
int8_t UsbSerialDevice::CDC_Itf_Control(uint8_t cmd, uint8_t *pbuf, uint16_t length) {
	switch (cmd) {
		case CDC_SEND_ENCAPSULATED_COMMAND:
			/* Add your code here */
			break;

		case CDC_GET_ENCAPSULATED_RESPONSE:
			/* Add your code here */
			break;

		case CDC_SET_COMM_FEATURE:
			/* Add your code here */
			break;

		case CDC_GET_COMM_FEATURE:
			/* Add your code here */
			break;

		case CDC_CLEAR_COMM_FEATURE:
			/* Add your code here */
			break;

		case CDC_SET_LINE_CODING:
			LineCoding.bitrate = (uint32_t)(pbuf[0] | (pbuf[1] << 8) | (pbuf[2] << 16) | (pbuf[3] << 24));
			LineCoding.format = pbuf[4];
			LineCoding.paritytype = pbuf[5];
			LineCoding.datatype = pbuf[6];

			/* Set the new configuration */
			// ComPort_Config();
			break;

		case CDC_GET_LINE_CODING:
			pbuf[0] = (uint8_t)(LineCoding.bitrate);
			pbuf[1] = (uint8_t)(LineCoding.bitrate >> 8);
			pbuf[2] = (uint8_t)(LineCoding.bitrate >> 16);
			pbuf[3] = (uint8_t)(LineCoding.bitrate >> 24);
			pbuf[4] = LineCoding.format;
			pbuf[5] = LineCoding.paritytype;
			pbuf[6] = LineCoding.datatype;
			break;

		case CDC_SET_CONTROL_LINE_STATE:
			/* Add your code here */
			break;

		case CDC_SEND_BREAK:
			/* Add your code here */
			break;

		default:
			break;
	}

	return (USBD_OK);
}

USBD_CDC_ItfTypeDef UsbSerialDevice::USBD_CDC_fops = {
	CDC_Itf_Init,
	CDC_Itf_DeInit,
	CDC_Itf_Control,
	CDC_Itf_Receive,
	CDC_TransmitCplt,
};
