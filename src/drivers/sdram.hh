#pragma once
#include "sdram_config_struct.hh"
#include "stm32xx.h"

// Todo: param for ram size, and bank#
class SDRAMPeriph {
public:
	SDRAMPeriph(const SDRAMConfig &sdram_defs,
				const uint32_t base_addr,
				const uint32_t sdram_size) noexcept;
	uint32_t test();
	bool is_busy();
	void wait_until_ready();

	const uint32_t ram_start;
	const uint32_t ram_size;
	HAL_StatusTypeDef status;

private:
	const SDRAMConfig &defs;
	HAL_StatusTypeDef init();
	void config_timing();
	void start_refresh();
	void init_gpio();
	uint32_t do_sdram_test(uint32_t (*mapfunc)(uint32_t));

	uint32_t sdram_clock_;
};

