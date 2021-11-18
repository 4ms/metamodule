#pragma once
#include "conf/qspi_flash_conf.hh"
#include "debug.hh"
#include "qspi_flash_driver.hh"
#include "u-boot-spl-stm32.h"

struct NorFlashLoader {
	mdrivlib::QSpiFlash flash;

	NorFlashLoader()
		: flash{qspi_flash_conf} {

		Debug::blue_LED1::high();
		Debug::green_LED1::high();
		Debug::red_LED1::low();
		bool ok = flash.Erase(mdrivlib::QSpiFlash::ENTIRE_CHIP, 0x00, mdrivlib::QSpiFlash::EXECUTE_FOREGROUND);
		if (!ok) {
			Debug::red_LED1::high();
			while (true) {
				Debug::green_LED1::low();
				HAL_Delay(250);
				Debug::green_LED1::high();
				HAL_Delay(250);
			}
		}

		ok = flash.Write(u_boot_spl_stm32, 0x00, u_boot_spl_stm32_len); //101961 bytes
		Debug::red_LED1::high();
		Debug::blue_LED1::low();

		if (!ok) {
			while (true) {
				Debug::red_LED1::low();
				HAL_Delay(250);
				Debug::red_LED1::high();
				HAL_Delay(250);
			}
		}
	}
};
