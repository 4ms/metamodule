#include "messages.hh"

namespace MetaModule
{

void RotoControlMessage::push_byte(uint8_t byte) {
	command_buffer_.push_back(byte);
}

void RotoControlMessage::set_control_config(RotoControlMessage::ControlConfig &&cfg) {
	// Calculate command data length: 0x001D base + (HS * 0x0D) for step names
	uint16_t data_length = 0x001D;
	data_length += cfg.haptic_steps * 0x0D;

	// Command header: 5A 02 [07 for knob, 08 for switch]
	push_byte(0x5A);
	push_byte(0x02);
	push_byte(static_cast<uint8_t>(cfg.control_type));

	// Command data length (MSB, LSB)
	push_byte((data_length >> 8) & 0xFF);
	push_byte(data_length & 0xFF);

	// Parameters
	push_byte(cfg.setup_index);
	push_byte(cfg.control_index);
	push_byte(static_cast<uint8_t>(cfg.control_mode));
	push_byte(cfg.control_channel);
	push_byte(cfg.control_param);

	// NRPN address (2 bytes)
	push_byte((cfg.nrpn_address >> 8) & 0xFF);
	push_byte(cfg.nrpn_address & 0xFF);

	// Min value (2 bytes)
	push_byte((cfg.min_value >> 8) & 0xFF);
	push_byte(cfg.min_value & 0xFF);

	// Max value (2 bytes)
	push_byte((cfg.max_value >> 8) & 0xFF);
	push_byte(cfg.max_value & 0xFF);

	// Control name (13 bytes, NULL terminated, padded with 00s)
	for (unsigned i = 0; i < 13; ++i) {
		if (i < cfg.control_name.length()) {
			push_byte(cfg.control_name[i]);
		} else {
			push_byte(0x00);
		}
	}

	// Color scheme
	push_byte(cfg.color_scheme);

	if (cfg.control_type == ControlType::SWITCH) {
		// param1 and param2 (different meaning for knob vs switch)
		push_byte(cfg.param1); // indent_pos1 for knob, led_on_color for switch
		push_byte(cfg.param2); // indent_pos2 for knob, led_off_color for switch

		// Haptic mode
		push_byte(static_cast<uint8_t>(cfg.haptic_mode));
	} else {
		push_byte(static_cast<uint8_t>(cfg.haptic_mode));

		push_byte(cfg.param1);
		push_byte(cfg.param2);
	}

	// Haptic steps
	push_byte(cfg.haptic_steps);

	// Step names (for KNOB_N_STEP or switch with haptic strings)
	for (size_t step = 0; step < cfg.haptic_steps; ++step) {
		for (size_t i = 0; i < 13; ++i) {
			if (step < cfg.step_names.size() && i < cfg.step_names[step].length()) {
				push_byte(cfg.step_names[step][i]);
			} else {
				push_byte(0x00);
			}
		}
	}

	push_byte(0xF0);
	push_byte(0xF1);
}

void RotoControlMessage::start_config_update() { // Removed param
	const uint8_t command[] = {0x5A, 0x01, 0x04, 0x00, 0x00, 0xF0, 0xF1};
	command_buffer_.insert(command_buffer_.end(), std::begin(command), std::end(command));
}

void RotoControlMessage::end_config_update() { // Removed param
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
