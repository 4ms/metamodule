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

bool UsbSerialDevice::send_command(const std::vector<uint8_t>& command) {
    // Check current time first to avoid potential race condition
    uint32_t current_time = HAL_GetTick();
    
    // Check if we're still in transmission state
    if (is_transmitting) {
        // If timeout has occurred, reset the transmission state
        if (current_time - last_transmission_tm > 200) { // Increased timeout for more reliability
            pr_dbg("USB transmission timeout - resetting state\n");
            is_transmitting = false;
        } else {
            pr_dbg("USB busy - command rejected\n");
            return false; // Still transmitting previous data
        }
    }
    
    // Safety check for empty commands
    if (command.empty()) {
        pr_dbg("Attempted to send empty command\n");
        return false;
    }
    
    // Set buffer with proper error handling
    if (command.size() > 512) { // Add reasonable size limit
        pr_dbg("Command too large: %d bytes\n", command.size());
        return false;
    }
    
    // Use a local copy of the data to avoid const_cast issues
    static std::vector<uint8_t> tx_buffer;
    tx_buffer = command;
    
    // Set the transmit buffer
    USBD_CDC_SetTxBuffer(pdev, tx_buffer.data(), tx_buffer.size());
    
    // Send the data with proper error handling
    auto err = USBD_CDC_TransmitPacket(pdev);
    if (err == USBD_OK) {
        is_transmitting = true;
        last_transmission_tm = current_time;
        return true;
    } else if (err == USBD_BUSY) {
        pr_dbg("USB CDC Busy\n");
        return false;
    } else {
        pr_dbg("USB CDC Transmit Error: %d\n", err);
        // Reset transmission state on error
        is_transmitting = false;
        return false;
    }
}

// New method to write hex data directly to a buffer
bool UsbSerialDevice::write_hex_to_buffer(const std::vector<uint8_t>& data, size_t buffer_index) {
    // Validate buffer index
    if (buffer_index >= console_buffers.size()) {
        pr_dbg("Invalid buffer index: %zu\n", buffer_index);
        return false;
    }
    
    // Get the buffer
    auto* buffer = console_buffers[buffer_index];
    
    // Check if buffer is available for writing
    if (buffer->writer_ref_count > 0) {
        pr_dbg("Buffer %zu is currently in use\n", buffer_index);
        return false;
    }
    
    // Write data to the buffer using span for efficient batch writing
    buffer->write(std::span<const uint8_t>(data.data(), data.size()));
    
    return true;
}

void UsbSerialDevice::set_receive_callback(std::function<void(const uint8_t*, uint32_t)> callback) {
    receive_callback = callback;
}

bool UsbSerialDevice::get_firmware_version(std::function<void(bool success)> callback) {
    // Format: 5A 01 01 00 00
    std::vector<uint8_t> cmd = {0x5A, 0x01, 0x01, 0x00, 0x00};
    
    // Use write_hex_to_buffer instead of send_command
    if (write_hex_to_buffer(cmd, 0)) {
        // Set up a callback to parse the response
        return true;
    } else {
        return false;
    }
}

bool UsbSerialDevice::start_config_update(std::function<void(bool success)> callback) {
    // Format: 5A 01 04 00 00
    std::vector<uint8_t> cmd = {0x5A, 0x01, 0x04, 0x00, 0x00};
    
    // Set up a callback to parse the response
    set_receive_callback([callback](const uint8_t* data, uint32_t len) {
        // Response format: A5 <RC>
        if (len >= 2 && data[0] == 0xA5) {
            // Success if response code is 0
            bool success = (data[1] == 0);
            callback(success);
        } else {
            // Invalid response format
            callback(false);
        }
    });
    
    return send_command(cmd);
}

bool UsbSerialDevice::end_config_update(std::function<void(bool success)> callback) {
    // Format: 5A 01 05 00 00
    std::vector<uint8_t> cmd = {0x5A, 0x01, 0x05, 0x00, 0x00};
    
    // Set up a callback to parse the response
    set_receive_callback([callback](const uint8_t* data, uint32_t len) {
        // Response format: A5 <RC>
        if (len >= 2 && data[0] == 0xA5) {
            // Success if response code is 0
            bool success = (data[1] == 0);
            callback(success);
        } else {
            // Invalid response format
            callback(false);
        }
    });
    
    return send_command(cmd);
}

bool UsbSerialDevice::set_knob_control_config(uint8_t setup_index, uint8_t control_index, uint8_t control_mode,
                                           uint8_t control_channel, uint8_t control_param, uint16_t nrpn_address,
                                           uint16_t min_value, uint16_t max_value, const std::string& control_name,
                                           uint8_t color_scheme, uint8_t haptic_mode, uint8_t indent_pos1, uint8_t indent_pos2,
                                           uint8_t haptic_steps, const std::vector<std::string>& step_names,
                                           std::function<void(bool success)> callback) {
    // Calculate command length: 0x1D + (haptic_steps * 0x0D)
    uint16_t cmd_data_len = 0x1D + (haptic_steps * 0x0D);
    
    // Create command vector with initial size
    std::vector<uint8_t> cmd = {
        0x5A, 0x02, 0x07,         // Command header
        static_cast<uint8_t>(cmd_data_len >> 8),  // Command length MSB
        static_cast<uint8_t>(cmd_data_len & 0xFF) // Command length LSB
    };
    
    // Add command parameters
    cmd.push_back(setup_index);         // SI = Setup index
    cmd.push_back(control_index);       // CI = Control index
    cmd.push_back(control_mode);        // CM = Control mode
    cmd.push_back(control_channel);     // CC = Control channel
    cmd.push_back(control_param);       // CP = Control param
    
    // NRPN address (2 bytes)
    cmd.push_back(static_cast<uint8_t>(nrpn_address >> 8));
    cmd.push_back(static_cast<uint8_t>(nrpn_address & 0xFF));
    
    // Min value (2 bytes)
    cmd.push_back(static_cast<uint8_t>(min_value >> 8));
    cmd.push_back(static_cast<uint8_t>(min_value & 0xFF));
    
    // Max value (2 bytes)
    cmd.push_back(static_cast<uint8_t>(max_value >> 8));
    cmd.push_back(static_cast<uint8_t>(max_value & 0xFF));
    
    // Control name (13 bytes, null-terminated, padded with zeros)
    size_t name_len = std::min(control_name.length(), static_cast<size_t>(12)); // Max 12 chars + null
    for (size_t i = 0; i < name_len; i++) {
        cmd.push_back(control_name[i]);
    }
    // Pad with zeros to 13 bytes total (including null terminator)
    for (size_t i = name_len; i < 13; i++) {
        cmd.push_back(0);
    }
    
    // Color scheme
    cmd.push_back(color_scheme);
    
    // Haptic mode
    cmd.push_back(haptic_mode);
    
    // Indent positions (only used for KNOB_300 mode)
    cmd.push_back(indent_pos1);
    cmd.push_back(indent_pos2);
    
    // Haptic steps
    cmd.push_back(haptic_steps);
    
    // Step names (each 13 bytes, null-terminated, padded with zeros)
    for (size_t i = 0; i < step_names.size() && i < haptic_steps; i++) {
        const std::string& step_name = step_names[i];
        size_t step_name_len = std::min(step_name.length(), static_cast<size_t>(12)); // Max 12 chars + null
        
        for (size_t j = 0; j < step_name_len; j++) {
            cmd.push_back(step_name[j]);
        }
        // Pad with zeros to 13 bytes total (including null terminator)
        for (size_t j = step_name_len; j < 13; j++) {
            cmd.push_back(0);
        }
    }
    
    // If fewer step names were provided than haptic_steps, add empty strings
    for (size_t i = step_names.size(); i < haptic_steps; i++) {
        for (size_t j = 0; j < 13; j++) {
            cmd.push_back(0);
        }
    }
    
    // Set up a callback to parse the response
    set_receive_callback([callback](const uint8_t* data, uint32_t len) {
        // Response format: A5 <RC>
        if (len >= 2 && data[0] == 0xA5) {
            // Success if response code is 0
            bool success = (data[1] == 0);
            callback(success);
        } else {
            // Invalid response format
            callback(false);
        }
    });
    
    return send_command(cmd);
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


	// Don't transmit if we already are transmitting
	// But have a 100ms timeout in case of a USB error
	if (is_transmitting) {
		if (HAL_GetTick() - last_transmission_tm > 100) {
			is_transmitting = false;
			last_transmission_tm = HAL_GetTick();
		} else
			return;
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
				return;

			} else if (start_pos < end_pos) {
				transmit(&buff->buffer.data[start_pos], end_pos - start_pos);
				current_read_pos[i] = end_pos;
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
    
    // Call the user-provided callback if set
    if (_instance->receive_callback) {
        _instance->receive_callback(Buf - *Len, *Len);
    }

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
