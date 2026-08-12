#include "usb_serial_device.hh"
#include "device_composite/add_class.hh"
#include "console/console_routing.hh"
#include "console/pr_dbg.hh"

extern USBD_CDC_ItfTypeDef USBD_CDC_fops;

namespace
{
USBD_CDC_LineCodingTypeDef LineCoding = {
	115200, /* baud rate */
	0x00,	/* stop bits-1 */
	0x00,	/* parity - none */
	0x08	/* nb. of bits 8 */
};
}

UsbSerialDevice::UsbSerialDevice(USBD_HandleTypeDef *pDevice,
								 std::array<ConcurrentBuffer *, MetaModule::ConsoleBufferReader::NumBuffers> buffers)
	: pdev{pDevice}
	, reader{buffers} {
	rx_buffer.resize(256);
	_instance = this;
}

void UsbSerialDevice::register_class() {
	_instance = this;

	auto ok = MetaModule::UsbComposite::add_class(
		pdev, USBD_CDC_CLASS, CLASS_TYPE_CDC, CMPSIT_CDC_EpAdd, [this] {
			USBD_CDC_RegisterInterface(pdev, &USBD_CDC_fops);
		});

	if (ok)
		pr_info("Registered USB CDC console\n");
}

void UsbSerialDevice::on_stopped() {
	set_console_routing(false);
}

void UsbSerialDevice::set_console_routing(bool active) {
	if (active == MetaModule::ConsoleRouting::usb_console_active)
		return;
	MetaModule::ConsoleRouting::usb_console_active = active;
	if (active) {
		// The UART drain already printed everything up to this point
		reader.resync();
		is_transmitting = false;
		tx_pending = 0;
	}
}

void UsbSerialDevice::process() {
	// Only drain the console buffers while a host is enumerated and awake;
	// otherwise the UART drain does it
	set_console_routing(pdev->dev_state == USBD_STATE_CONFIGURED);

	if (MetaModule::ConsoleRouting::usb_console_active)
		transmit_pending();
}

void UsbSerialDevice::transmit_pending() {
	// Don't start a transmission if one is in flight,
	// but time out after 100ms in case of a USB error
	if (is_transmitting) {
		if (HAL_GetTick() - last_transmission_tm > 100)
			is_transmitting = false;
		else
			return;
	}

	if (tx_pending == 0)
		tx_pending = reader.next_chunk(tx_bounce);
	if (tx_pending == 0)
		return;

	USBD_CDC_SetTxBuffer(pdev, tx_bounce.data(), tx_pending, cdc_class_id());

	auto err = USBD_CDC_TransmitPacket(pdev, cdc_class_id());
	if (err == USBD_OK) {
		is_transmitting = true;
		last_transmission_tm = HAL_GetTick();
		tx_pending = 0; // tx_bounce stays untouched until CDC_TransmitCplt

	} else if (err != USBD_BUSY) {
		pr_dbg("USB CDC Transmit Error: %d\n", static_cast<int>(err));
		tx_pending = 0; // unrecoverable: drop the chunk
	}
	// USBD_BUSY: keep tx_pending, retry next process()
}

// Which composite slot the CDC class landed in. pdev->classId only identifies
// the class inside a class callback -- from the main loop it holds whichever
// class the OTG ISR last dispatched to -- so the app-facing CDC calls must pass
// the id explicitly.
uint8_t UsbSerialDevice::cdc_class_id() const {
	return _cdc_class_id;
}

int8_t UsbSerialDevice::CDC_Itf_Init() {
	// Inside a class callback: classId is ours
	_instance->_cdc_class_id = (uint8_t)_instance->pdev->classId;
	USBD_CDC_SetTxBuffer(_instance->pdev, _instance->tx_bounce.data(), 0, _instance->_cdc_class_id);
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
		_instance->reader.set_color(true);
	if (*Buf == 'm')
		_instance->reader.set_color(false);

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
