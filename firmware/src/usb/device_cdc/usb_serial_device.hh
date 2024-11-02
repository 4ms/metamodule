#pragma once
#include "usbd_cdc.h"
#include "usbd_core.h"
#include "util/circular_buffer_ext.hh"
#include <vector>

class UsbSerialDevice {

public:
	UsbSerialDevice(USBD_HandleTypeDef *pDevice);
	void start();
	void stop();

private:
	USBD_HandleTypeDef *pdev;

	// std::array<uint8_t, 4096> rx_buffer{};
	// std::array<uint8_t, 4096> tx_buffer{};
	std::vector<uint8_t> rx_buffer{};
	std::vector<uint8_t> tx_buffer{};
	// CircularBufferAccess<std::array<uint8_t, 4096>> rx_fifo{rx_buffer};
	// CircularBufferAccess<std::array<uint8_t, 4096>> tx_fifo{tx_buffer};

	static int8_t CDC_Itf_Init();
	static int8_t CDC_Itf_DeInit();
	static int8_t CDC_Itf_Control(uint8_t cmd, uint8_t *pbuf, uint16_t length);
	static int8_t CDC_Itf_Receive(uint8_t *pbuf, uint32_t *Len);
	static int8_t CDC_TransmitCplt(uint8_t *pbuf, uint32_t *Len, uint8_t epnum);
	static void Error_Handler();
	static void ComPort_Config();
	static void TIM_Config();

	static USBD_CDC_ItfTypeDef USBD_CDC_fops;
	static inline UsbSerialDevice *_instance;
};
