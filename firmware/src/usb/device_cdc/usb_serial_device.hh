#pragma once
#include "console/console_buffer_reader.hh"
#include "usbd_cdc.h"
#include "usbd_core.h"
#include <array>
#include <vector>

// USB CDC console device. While a host has enumerated us, this becomes the
// active drain of the per-core console buffers (the UART drain idles, see
// console_routing.hh), forwarding all cores' printf() output to the host.
class UsbSerialDevice {

public:
	UsbSerialDevice(USBD_HandleTypeDef *pDevice,
					std::array<ConcurrentBuffer *, MetaModule::ConsoleBufferReader::NumBuffers> console_buffers);
	void process();
	void start();
	void stop();
	void soft_stop();

private:
	USBD_HandleTypeDef *pdev;

	MetaModule::ConsoleBufferReader reader;

	std::vector<uint8_t> rx_buffer{}; // force to be on heap

	// Holds the chunk currently being sent; must stay stable until CDC_TransmitCplt
	std::array<uint8_t, 512> tx_bounce{};
	size_t tx_pending = 0;

	bool is_transmitting = false;
	uint32_t last_transmission_tm = 0;

	void transmit_pending();
	void set_console_routing(bool active);

	static int8_t CDC_Itf_Init();
	static int8_t CDC_Itf_DeInit();
	static int8_t CDC_Itf_Control(uint8_t cmd, uint8_t *pbuf, uint16_t length);
	static int8_t CDC_Itf_Receive(uint8_t *pbuf, uint32_t *Len);
	static int8_t CDC_TransmitCplt(uint8_t *pbuf, uint32_t *Len, uint8_t epnum);

	static USBD_CDC_ItfTypeDef USBD_CDC_fops;
	static inline UsbSerialDevice *_instance;
};
