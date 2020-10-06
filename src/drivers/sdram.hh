#pragma once
#include "sdram_config_struct.hh"
#include "stm32xx.h"

class SDRAMPeriph {
public:
	SDRAMPeriph(const SDRAMConfig &sdram_defs) noexcept;
	static uint32_t test(const uint32_t ram_start, const uint32_t ram_size);
	static bool is_busy();
	static void wait_until_ready();

	HAL_StatusTypeDef status;

private:
	const SDRAMConfig &defs;
	HAL_StatusTypeDef init();
	void config_timing();
	void start_refresh();
	void init_gpio();
	static uint32_t do_sdram_test(uint32_t (*mapfunc)(uint32_t), const uint32_t ram_start, const uint32_t ram_size);

	uint32_t sdram_clock_;
};

