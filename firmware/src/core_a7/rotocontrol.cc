#include "rotocontrol.hh"
#include "pr_dbg.hh"

namespace MetaModule
{

const uint8_t terminator[] = {0xF0, 0xF1};

void RotoControl::set_knob_control_config(
	ConcurrentBuffer &console_cdc_buff,
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
	
	// Build command buffer - max possible size
	uint8_t command[256];
	uint16_t pos = 0;
	
	// Command header: 5A 02 07
	command[pos++] = 0x5A;
	command[pos++] = 0x02;
	command[pos++] = 0x07;
	
	// Command data length (MSB, LSB)
	command[pos++] = (data_length >> 8) & 0xFF;
	command[pos++] = data_length & 0xFF;
	
	// Parameters
	command[pos++] = setup_index;
	command[pos++] = control_index;
	command[pos++] = static_cast<uint8_t>(control_mode);
	command[pos++] = control_channel;
	command[pos++] = control_param;
	
	// NRPN address (2 bytes)
	command[pos++] = (nrpn_address >> 8) & 0xFF;
	command[pos++] = nrpn_address & 0xFF;
	
	// Min value (2 bytes)
	command[pos++] = (min_value >> 8) & 0xFF;
	command[pos++] = min_value & 0xFF;
	
	// Max value (2 bytes)
	command[pos++] = (max_value >> 8) & 0xFF;
	command[pos++] = max_value & 0xFF;
	
	// Control name (13 bytes, NULL terminated, padded with 00s)
	for (int i = 0; i < 13; ++i) {
		if (control_name != nullptr && control_name[i] != '\0') {
			command[pos++] = control_name[i];
		} else {
			command[pos++] = 0x00;
		}
	}
	
	// Color scheme
	command[pos++] = color_scheme;
	
	// Haptic mode
	command[pos++] = static_cast<uint8_t>(haptic_mode);
	
	// Indent positions
	command[pos++] = indent_pos1;
	command[pos++] = indent_pos2;
	
	// Haptic steps
	command[pos++] = haptic_steps;
	
	// Step names (only for KNOB_N_STEP)
	if (haptic_mode == HapticMode::KNOB_N_STEP && step_names != nullptr) {
		for (int step = 0; step < haptic_steps; ++step) {
			const char* step_name = step_names[step];
			for (int i = 0; i < 13; ++i) {
				if (step_name != nullptr && step_name[i] != '\0') {
					command[pos++] = step_name[i];
				} else {
					command[pos++] = 0x00;
				}
			}
		}
	}

    command[pos++] = 0xF0;
    command[pos++] = 0xF1;
	
	// Write to console buffer
	console_cdc_buff.write(std::span<const uint8_t>(command, pos));
    pr_dbg("RotoControl: Set knob control config, wrote command to console buffer: %s", command);
}

void RotoControl::start_config_update(ConcurrentBuffer &console_cdc_buff) {
	// Command: 5A 01 04 00 00
	const uint8_t command[] = {0x5A, 0x01, 0x04, 0x00, 0x00, 0xF0, 0xF1};
	console_cdc_buff.write(std::span<const uint8_t>(command, sizeof(command)));
    pr_dbg("RotoControl: Start config update, wrote command to console buffer: %s", command);
}

void RotoControl::end_config_update(ConcurrentBuffer &console_cdc_buff) {
	// Command: 5A 01 05 00 00
	const uint8_t command[] = {0x5A, 0x01, 0x05, 0x00, 0x00, 0xF0, 0xF1};
	console_cdc_buff.write(std::span<const uint8_t>(command, sizeof(command)));
    pr_dbg("RotoControl: End config update, wrote command to console buffer: %s", command);
}

void RotoControl::queue_config_commands(
	ConcurrentBuffer &console_cdc_buff,
	std::initializer_list<std::function<void()>> commands) {
	
	for (auto& command_func : commands) {
		// Execute the command
		command_func();
		// Add terminator after each command
		console_cdc_buff.write(std::span<const uint8_t>(terminator, sizeof(terminator)));
	}
}

} // namespace MetaModule 