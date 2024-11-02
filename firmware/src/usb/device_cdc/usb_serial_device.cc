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

UsbSerialDevice::UsbSerialDevice(USBD_HandleTypeDef *pDevice)
	: pdev{pDevice} {
	rx_buffer.resize(2048);
	tx_buffer.resize(2048);
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

	USBD_RegisterClass(pdev, USBD_CDC_CLASS);
	USBD_CDC_RegisterInterface(pdev, &USBD_CDC_fops);
	USBD_Start(pdev);
}

void UsbSerialDevice::stop() {
	pr_info("Stopping UsbSerialDevice\n");
	USBD_Stop(pdev);
	USBD_DeInit(pdev);
}

int8_t UsbSerialDevice::CDC_Itf_Init() {
	// TIM_Config();
	// if (HAL_TIM_Base_Start_IT(&TimHandle) != HAL_OK) {
	// 	Error_Handler();
	// }

	USBD_CDC_SetTxBuffer(_instance->pdev, _instance->tx_buffer.data(), 0); //for now, size is 0
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
	// if (HAL_UART_DeInit(&UartHandle) != HAL_OK) {
	// 	Error_Handler();
	// }
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
	// SCB_CleanDCache_by_Addr((uint32_t *)Buf, *Len);

	// HAL_UART_Transmit_DMA(&UartHandle, Buf, *Len);
	pr_dbg("Rx: ");
	uint32_t len = *Len;
	while (len--)
		pr_dbg("%c", *Buf++);
	pr_dbg("\n");

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
