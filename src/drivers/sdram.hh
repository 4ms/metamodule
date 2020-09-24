#pragma once
#include "sdram_config_struct.hh"
#include "stm32xx.h"

// Todo: param for ram size, and bank#
class SDRAMPeriph {
public:
	SDRAMPeriph(const SDRAMTimingConfig &timing,
				const uint32_t base_addr,
				const uint32_t sdram_size) noexcept;
	uint32_t test();
	bool is_busy();
	void wait_until_ready();

	const uint32_t ram_start;
	const uint32_t ram_size;
	HAL_StatusTypeDef status;

private:
	HAL_StatusTypeDef init(const SDRAMTimingConfig &timing);
	void init_gpio();
	uint32_t do_sdram_test(uint32_t (*mapfunc)(uint32_t));
};

