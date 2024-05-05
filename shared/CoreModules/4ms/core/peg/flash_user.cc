#include "flash_user.hh"
#include "calibration.hh"
#include "flash.hh"
#include "flash_layout.hh"
#include "stm32xx.h"

struct SystemSettings settings;

int write_settings(void) {
	HAL_StatusTypeDef status;

	flash_begin_open_program();

	status = flash_open_erase_page(SettingsFlashAddr);
	if (status != HAL_OK) {
		flash_end_open_program();
		return status;
	}

	uint32_t sz = sizeof(struct SystemSettings);
	settings.is_valid = VALID_SETTINGS;
	status = flash_open_program_word_array((uint32_t *)(&settings), SettingsFlashAddr, sz);

	flash_end_open_program();
	return status;
}

uint8_t read_settings(void) {
	uint32_t sz = sizeof(struct SystemSettings);
	flash_read_word_array((uint32_t *)(&settings), SettingsFlashAddr, sz);

	if (!check_settings_valid()) {
		default_settings();
		return 0;
	}

	return 1;
}

uint8_t check_settings_valid(void) {
	return settings.is_valid == VALID_SETTINGS;
}

void default_settings(void) {
	default_calibration();
	settings.limit_skew = 1;
	settings.free_running_ping = 1;
	settings.trigout_is_trig = 0;
	settings.trigin_function = TRIGIN_IS_ASYNC;
	settings.trigout_function = TRIGOUT_IS_ENDOFFALL;

	settings.cycle_jack_behavior = CYCLE_JACK_BOTH_EDGES_TOGGLES;

	settings.start_clk_time = 25000;
	settings.start_cycle_on = 1;
	settings.start_sync_on = 0;
}
