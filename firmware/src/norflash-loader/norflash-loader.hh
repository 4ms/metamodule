#pragma once
#include "medium/debug.hh"
#include "printf.h"
#include "qspi_flash_driver.hh"
#include "uart_log.hh"
#include <memory>

// Images:
#include "build/mp1corea7/medium/main-uimg.h"
#include "u-boot-spl-stm32.h"

struct NorFlashLoader {
	using QSpiFlash = mdrivlib::QSpiFlash;
	QSpiFlash flash;

	void erase_write_and_verify(uint8_t *data, uint32_t start_block_num, uint32_t len_bytes) {
		if (!len_bytes)
			return;

		uint32_t num_blocks = (len_bytes / QSPI_64KBLOCK_SIZE) + 1;
		if ((len_bytes % QSPI_64KBLOCK_SIZE) == 0)
			num_blocks--;
		erase_blocks(start_block_num, start_block_num + num_blocks);

		uint32_t start_addr = start_block_num * QSPI_64KBLOCK_SIZE;
		write(data, start_addr, len_bytes);

		verify(data, start_addr, len_bytes);
	}

	void erase_blocks(int range_start, int range_end) {
		for (int i = range_start; i < range_end; i++) {
			Debug::red_LED1::low();
			printf_("Erasing Block#%d @ 0x%x\n\r", i, i * QSPI_64KBLOCK_SIZE);
			bool ok = flash.Erase(QSpiFlash::BLOCK_64K, i * QSPI_64KBLOCK_SIZE, QSpiFlash::EXECUTE_FOREGROUND);
			if (!ok) {
				printf_("Error erasing block #%d\n\r", i);
				while (true) {
					Debug::green_LED1::low();
					HAL_Delay(250);
					Debug::green_LED1::high();
					HAL_Delay(250);
				}
			}
			Debug::red_LED1::high();
		}
	}

	void write(uint8_t *data, uint32_t addr, uint32_t len) {
		Debug::blue_LED1::low();
		printf("Writing %d bytes to 0x%x\n\r", len, addr);
		bool ok = flash.Write(data, addr, len);
		if (!ok) {
			printf("Error writing\n\r");
			while (true) {
				Debug::red_LED1::low();
				HAL_Delay(250);
				Debug::red_LED1::high();
				HAL_Delay(250);
			}
		}
		Debug::blue_LED1::high();
	}

	void verify(uint8_t *data, uint32_t addr, uint32_t len) {
		printf("Reading %d bytes to 0x%x\n\r", len, addr);
		auto read_data = std::make_unique<uint8_t[]>(len);
		bool ok = flash.Read(read_data.get(), addr, len, mdrivlib::QSpiFlash::EXECUTE_FOREGROUND);
		if (!ok) {
			printf("Error reading\n\r");
			while (true) {
				Debug::blue_LED1::low();
				Debug::blue_LED1::high();
			}
		}
		for (int i = 0; i < len; i++) {
			if (read_data[i] != data[i]) {
				printf("Data read back does not match: [%d] read: 0x%x, wrote: 0x%x\n\r", i, read_data[i], data[i]);
				while (true) {
					Debug::blue_LED1::low();
					Debug::red_LED1::low();
					Debug::green_LED1::low();
					HAL_Delay(250);
					Debug::blue_LED1::high();
					Debug::red_LED1::high();
					Debug::green_LED1::high();
					HAL_Delay(250);
				}
			}
		}
	}

	NorFlashLoader(const mdrivlib::QSPIFlashConfig &conf)
		: flash{conf} {

		printf("QSPI is initialized.\n\r");

		Debug::red_LED1::high();
		Debug::blue_LED1::high();
		Debug::green_LED1::high();

		// Write FSBL1 @ first block: Success = red turns on
		erase_write_and_verify(u_boot_spl_stm32, 0, u_boot_spl_stm32_len);
		Debug::red_LED1::low();

		// Write FSBL2 @ block 4 = 0x40000: Success =  blue turns on (magenta)
		erase_write_and_verify(u_boot_spl_stm32, 4, u_boot_spl_stm32_len);
		Debug::blue_LED1::low();

		// Write app data @ block 8 = 0x80000: Sucess = green turns on (white)
		erase_write_and_verify(main_uimg, 8, main_uimg_len);
		Debug::green_LED1::low();

		printf("Successfully wrote SPL and application to QSPI Flash\r\n");
	}
};
