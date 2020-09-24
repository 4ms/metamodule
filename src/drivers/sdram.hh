#pragma once
#include "stm32xx.h"

//Todo: template param for ram size, and bank#(?)
class SDRAMPeriph {
public:
	SDRAMPeriph() noexcept;
	HAL_StatusTypeDef status;
	bool test();
	bool is_busy();

	//SDRAM Bank 2 is 4 x 64MB, from 0xD000 0000 to 0xDFFF FFFF
	//Thus, we can access 0x10000000 addresses, or 256M addresses
	//256Mbit = 32MByte = 0x02000000
	const uint32_t SDRAM_BASE = 0xC0000000;
	const uint32_t SDRAM_SIZE = 0x02000000;
	
	
private:
	HAL_StatusTypeDef init();
	void init_gpio();

	static inline SDRAM_HandleTypeDef hsdram1;

};
