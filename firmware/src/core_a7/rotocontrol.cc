#include "rotocontrol.hh"
#include "pr_dbg.hh"
#include <vector> // Ensure vector is included for the definition

namespace MetaModule
{

// Initialize static command buffer
std::vector<uint8_t> RotoControl::command_buffer_;

// const uint8_t terminator[] = {0xF0, 0xF1}; // Keep for reference or local use if needed

void RotoControl::set_knob_control_config(
	// ConcurrentBuffer &console_cdc_buff, // Removed
	uint8_t setup_index,
	uint8_t control_index,
	ControlMode control_mode,
	uint8_t control_channel,
	uint8_t control_param,
	uint16_t nrpn_address,
	uint16_t min_value,
	uint16_t max_value,
	const char* control_name,
	uint8_t color_scheme,
	HapticMode haptic_mode,
	uint8_t indent_pos1,
	uint8_t indent_pos2,
	uint8_t haptic_steps,
	const char* const* step_names) {
	
	// Calculate command data length: 0x001D base + (HS * 0x0D) for step names
	uint16_t data_length = 0x001D;
	if (haptic_mode == HapticMode::KNOB_N_STEP && step_names != nullptr) {
		data_length += haptic_steps * 0x0D;
	}
	
	// Build command - max possible size for this single command
    // Max theoretical size for this specific command.
    // Command header (3) + length (2) + params (29) + step_names (haptic_steps * 13) + terminator (2)
    // Let's assume haptic_steps max is around 128 for safety, though typical is less.
    // 3 + 2 + 29 + (128 * 13) + 2 = 36 + 1664 = 1700.
    // A local buffer is fine here, then append to the main command_buffer_.
	uint8_t command_segment[1700]; // Adjusted for potential max size
	uint16_t pos = 0;
	
	// Command header: 5A 02 07
	command_segment[pos++] = 0x5A;
	command_segment[pos++] = 0x02;
	command_segment[pos++] = 0x07;
	
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
		if (control_name != nullptr && control_name[i] != '\\0') {
			command_segment[pos++] = control_name[i];
		} else {
			command_segment[pos++] = 0x00;
		}
	}
	
	// Color scheme
	command_segment[pos++] = color_scheme;
	
	// Haptic mode
	command_segment[pos++] = static_cast<uint8_t>(haptic_mode);
	
	// Indent positions
	command_segment[pos++] = indent_pos1;
	command_segment[pos++] = indent_pos2;
	
	// Haptic steps
	command_segment[pos++] = haptic_steps;
	
	// Step names (only for KNOB_N_STEP)
	if (haptic_mode == HapticMode::KNOB_N_STEP && step_names != nullptr) {
		for (int step = 0; step < haptic_steps; ++step) {
			const char* step_name = step_names[step];
			for (int i = 0; i < 13; ++i) {
				if (step_name != nullptr && step_name[i] != '\\0') {
					command_segment[pos++] = step_name[i];
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
    // pr_dbg("RotoControl: Set knob control config, appended command to internal buffer"); // Optional debug
}

void RotoControl::start_config_update(/* ConcurrentBuffer &console_cdc_buff */) { // Removed param
	// Command: 5A 01 04 00 00 F0 F1
	const uint8_t command[] = {0x5A, 0x01, 0x04, 0x00, 0x00, 0xF0, 0xF1};
	command_buffer_.insert(command_buffer_.end(), std::begin(command), std::end(command));
    // pr_dbg("RotoControl: Start config update, appended command to internal buffer"); // Optional debug
}

void RotoControl::end_config_update(/* ConcurrentBuffer &console_cdc_buff */) { // Removed param
	// Command: 5A 01 05 00 00 F0 F1
	const uint8_t command[] = {0x5A, 0x01, 0x05, 0x00, 0x00, 0xF0, 0xF1};
	command_buffer_.insert(command_buffer_.end(), std::begin(command), std::end(command));
    // pr_dbg("RotoControl: End config update, appended command to internal buffer"); // Optional debug
}

void RotoControl::send_all_commands(ConcurrentBuffer &console_cdc_buff) {
	if (!command_buffer_.empty()) {
		console_cdc_buff.write(std::span<const uint8_t>(command_buffer_.data(), command_buffer_.size()));
		command_buffer_.clear();
		// pr_dbg("RotoControl: Sent all commands and cleared buffer"); // Optional debug
	}
}

// Removed queue_config_commands method as it's no longer needed.
// void RotoControl::queue_config_commands(
// ConcurrentBuffer &console_cdc_buff,
// std::initializer_list<std::function<void()>> commands) {
// 
// for (auto& command_func : commands) {
// // Execute the command
// command_func();
// // Add terminator after each command
// console_cdc_buff.write(std::span<const uint8_t>(terminator, sizeof(terminator)));
// }
// }

} // namespace MetaModule 