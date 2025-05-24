#pragma once
#include "console/concurrent_buffer.hh"
#include "drivers/smp.hh"
#include <functional>
#include <initializer_list>
#include <span>

namespace MetaModule
{

enum class ControlMode : uint8_t {
	CC_7BIT = 0x00,
	CC_14BIT = 0x01,
	NRPN_7BIT = 0x02,
	NRPN_14BIT = 0x03
};

enum class HapticMode : uint8_t {
	KNOB_300 = 0x00,
	KNOB_N_STEP = 0x01
};

class RotoControl {
public:
	static void set_knob_control_config(
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
		uint8_t indent_pos1 = 0xFF,
		uint8_t indent_pos2 = 0xFF,
		uint8_t haptic_steps = 2,
		const char* const* step_names = nullptr);

	static void start_config_update(ConcurrentBuffer &console_cdc_buff);

	static void end_config_update(ConcurrentBuffer &console_cdc_buff);

	static void queue_config_commands(
		ConcurrentBuffer &console_cdc_buff,
		std::initializer_list<std::function<void()>> commands);
};

} // namespace MetaModule 