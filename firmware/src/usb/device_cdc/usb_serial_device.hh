#pragma once
#include "console/concurrent_buffer.hh"
#include "usbd_cdc.h"
#include "usbd_core.h"
#include "util/circular_buffer_ext.hh"
#include <vector>

class UsbSerialDevice {

public:
	UsbSerialDevice(USBD_HandleTypeDef *pDevice, std::array<ConcurrentBuffer *, 3> console_buffers);
	void process();
	void start();
	void stop();

	void forward_to_uart();

private:
	USBD_HandleTypeDef *pdev;

	std::array<ConcurrentBuffer *, 3> console_buffers;
	std::array<unsigned, 3> current_read_pos{};

	std::vector<uint8_t> rx_buffer{}; // force to be on heap

	bool is_transmitting = false;
	uint32_t last_transmission_tm = 0;

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

	enum class Destination { UART, USB };
	void transmit_buffers(Destination dest);

	bool use_color = false;
};
