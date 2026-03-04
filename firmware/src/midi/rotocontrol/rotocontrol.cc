#include "rotocontrol.hh"
#include "pr_dbg.hh"

namespace MetaModule
{

// TODO:
//  - use an array for a command buffer
//  - send_all_commands takes the ConcurrentBuffer as an argument

void RotoControlMessage::set_control_config(ControlType control_type,
											uint8_t setup_index,
											uint8_t control_index,
											ControlMode control_mode,
											uint8_t control_channel,
											uint8_t control_param,
											uint16_t nrpn_address,
											uint16_t min_value,
											uint16_t max_value,
											const char *control_name,
											uint8_t color_scheme,
											HapticMode haptic_mode,
											uint8_t param1,
											uint8_t param2,
											uint8_t haptic_steps,
											const char *const *step_names) {

	// Calculate command data length: 0x001D base + (HS * 0x0D) for step names
	uint16_t data_length = 0x001D;
	if (haptic_steps > 0) {
		data_length += haptic_steps * 0x0D;
	}

	// Build command - max possible size for this single command
	uint8_t command_segment[1700]; // Adjusted for potential max size
	uint16_t pos = 0;

	// Command header: 5A 02 [07 for knob, 08 for switch]
	command_segment[pos++] = 0x5A;
	command_segment[pos++] = 0x02;
	command_segment[pos++] = static_cast<uint8_t>(control_type);

	// Command data length (MSB, LSB)
	command_segment[pos++] = (data_length >> 8) & 0xFF;
	command_segment[pos++] = data_length & 0xFF;

	// Parameters
	command_segment[pos++] = setup_index;
	command_segment[pos++] = control_index;
	command_segment[pos++] = static_cast<uint8_t>(control_mode);
	command_segment[pos++] = control_channel;
	command_segment[pos++] = control_param;

	// NRPN address (2 bytes)
	command_segment[pos++] = (nrpn_address >> 8) & 0xFF;
	command_segment[pos++] = nrpn_address & 0xFF;

	// Min value (2 bytes)
	command_segment[pos++] = (min_value >> 8) & 0xFF;
	command_segment[pos++] = min_value & 0xFF;

	// Max value (2 bytes)
	command_segment[pos++] = (max_value >> 8) & 0xFF;
	command_segment[pos++] = max_value & 0xFF;

	// Control name (13 bytes, NULL terminated, padded with 00s)
	for (int i = 0; i < 13; ++i) {
		if (control_name != nullptr && control_name[i] != '\0') {
			command_segment[pos++] = control_name[i];
		} else {
			command_segment[pos++] = 0x00;
		}
	}

	// Color scheme
	command_segment[pos++] = color_scheme;

	if (control_type == ControlType::SWITCH) {
		// param1 and param2 (different meaning for knob vs switch)
		command_segment[pos++] = param1; // indent_pos1 for knob, led_on_color for switch
		command_segment[pos++] = param2; // indent_pos2 for knob, led_off_color for switch

		// Haptic mode
		command_segment[pos++] = static_cast<uint8_t>(haptic_mode);
	} else {
		command_segment[pos++] = static_cast<uint8_t>(haptic_mode);

		command_segment[pos++] = param1;
		command_segment[pos++] = param2;
	}

	// Haptic steps
	command_segment[pos++] = haptic_steps;

	// Step names (for KNOB_N_STEP or switch with haptic strings)
	if (haptic_steps > 0) {
		for (int step = 0; step < haptic_steps; ++step) {
			for (int i = 0; i < 13; ++i) {
				if (step_names != nullptr) {
					if (step_names[step] != nullptr && step_names[step][i] != '\0') {
						command_segment[pos++] = step_names[step][i];
					} else {
						command_segment[pos++] = 0x00;
					}
				} else {
					command_segment[pos++] = 0x00;
				}
			}
		}
	}

	command_segment[pos++] = 0xF0;
	command_segment[pos++] = 0xF1;

	// Append to main command buffer
	command_buffer_.insert(command_buffer_.end(), command_segment, command_segment + pos);
}

void RotoControlMessage::start_config_update(/* ConcurrentBuffer &console_cdc_buff */) { // Removed param
	// Command: 5A 01 04 00 00 F0 F1
	const uint8_t command[] = {0x5A, 0x01, 0x04, 0x00, 0x00, 0xF0, 0xF1};
	command_buffer_.insert(command_buffer_.end(), std::begin(command), std::end(command));
}

void RotoControlMessage::end_config_update(/* ConcurrentBuffer &console_cdc_buff */) { // Removed param
	// Command: 5A 01 05 00 00 F0 F1
	const uint8_t command[] = {0x5A, 0x01, 0x05, 0x00, 0x00, 0xF0, 0xF1};
	command_buffer_.insert(command_buffer_.end(), std::begin(command), std::end(command));
}

void RotoControlMessage::set_setup(uint8_t setup_index) {
	// Command: 5A 02 03 00 01 SI F0 F1
	// CL = Command data length = 0001 (MSB, LSB)
	// SI = Setup index (00-3F)
	const uint8_t command[] = {0x5A, 0x02, 0x03, 0x00, 0x01, setup_index, 0xF0, 0xF1};
	command_buffer_.insert(command_buffer_.end(), std::begin(command), std::end(command));
}

void RotoControlMessage::clear_midi_setup(uint8_t setup_index) {
	// Command: 5A 02 0A 00 01 SI F0 F1
	// CL = Command data length = 0001 (MSB, LSB)
	// SI = Setup index
	const uint8_t command[] = {0x5A, 0x02, 0x0A, 0x00, 0x01, setup_index, 0xF0, 0xF1};
	command_buffer_.insert(command_buffer_.end(), std::begin(command), std::end(command));
}

void RotoControlMessage::send_all_commands(ConcurrentBuffer *shared_buffer) {
	if (shared_buffer && !command_buffer_.empty()) {
		shared_buffer->write(command_buffer_);
		command_buffer_.clear();
	}
}

} // namespace MetaModule
