#pragma once
#include "console/concurrent_buffer.hh"
#include "usbd_cdc.h"
#include "usbd_core.h"
#include "util/circular_buffer_ext.hh"
#include <vector>
#include <functional>
#include <string>

class UsbSerialDevice {

public:
	UsbSerialDevice(USBD_HandleTypeDef *pDevice, std::array<ConcurrentBuffer *, 3> console_buffers);
	void process();
	void start();
	void stop();

	void forward_to_uart();
	
	// Send a specific command to the serial port
	bool send_command(const std::vector<uint8_t>& command);
	
	// Write hex data directly to a specific buffer
	bool write_hex_to_buffer(const std::vector<uint8_t>& data, size_t buffer_index);
	
	// Set a callback to be called when data is received
	void set_receive_callback(std::function<void(const uint8_t*, uint32_t)> callback);
	
	// Get firmware version command helper with simplified callback
	bool get_firmware_version(std::function<void(bool success)> callback);
	
	// Start config update command helper
	bool start_config_update(std::function<void(bool success)> callback);
	
	// End config update command helper
	bool end_config_update(std::function<void(bool success)> callback);
	
	// Set knob control configuration
	bool set_knob_control_config(uint8_t setup_index, uint8_t control_index, uint8_t control_mode,
	                            uint8_t control_channel, uint8_t control_param, uint16_t nrpn_address,
	                            uint16_t min_value, uint16_t max_value, const std::string& control_name,
	                            uint8_t color_scheme, uint8_t haptic_mode, uint8_t indent_pos1, uint8_t indent_pos2,
	                            uint8_t haptic_steps, const std::vector<std::string>& step_names,
	                            std::function<void(bool success)> callback);

private:
	USBD_HandleTypeDef *pdev;

	std::array<ConcurrentBuffer *, 3> console_buffers;
	std::array<unsigned, 3> current_read_pos{};

	std::vector<uint8_t> rx_buffer{}; // force to be on heap
	std::function<void(const uint8_t*, uint32_t)> receive_callback = nullptr;

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
