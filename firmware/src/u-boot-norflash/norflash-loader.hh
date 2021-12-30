#pragma once
#include "conf/qspi_flash_conf.hh"
#include "debug.hh"
#include "qspi_flash_driver.hh"
#include "u-boot-img.h"
#include "u-boot-spl-stm32.h"
#include <array>
#include <memory>

struct NorFlashLoader {
	using QSpiFlash = mdrivlib::QSpiFlash;
	QSpiFlash flash;

	NorFlashLoader()
		: flash{qspi_flash_conf} {

		printf("QSPI is initialized.\n\r");

		Debug::blue_LED1::high();
		Debug::green_LED1::high();

		bool ok;

		//Erase 64kblocks for FSBL1 + 2: Red on. Error: flash green
		for (int i = 0; i < 8; i++) {
			Debug::red_LED1::low();
			printf("Erasing Block#%d @ 0x%x\n\r", i, i * QSPI_64KBLOCK_SIZE);
			ok = flash.Erase(QSpiFlash::BLOCK_64K, i * QSPI_64KBLOCK_SIZE, QSpiFlash::EXECUTE_FOREGROUND);
			if (!ok) {
				printf("Error erasing block #%d\n\r", i);
				while (true) {
					Debug::green_LED1::low();
					HAL_Delay(250);
					Debug::green_LED1::high();
					HAL_Delay(250);
				}
			}
			Debug::red_LED1::high();
		}

		// Write FSBL1: blue on. Error: flash red
		Debug::blue_LED1::low();
		printf("Writing %d bytes to 0x%x\n\r", u_boot_spl_stm32_len, 0x00);
		ok = flash.Write(u_boot_spl_stm32, 0x00, u_boot_spl_stm32_len); // ~100k
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

		//Verify
		{
			printf("Reading %d bytes to 0x%x\n\r", u_boot_spl_stm32_len, 0x00);
			auto data = std::make_unique<uint8_t[]>(u_boot_spl_stm32_len);
			ok = flash.Read(data.get(), 0, u_boot_spl_stm32_len, mdrivlib::QSpiFlash::EXECUTE_FOREGROUND);
			if (!ok) {
				printf("Error reading\n\r");
				while (true) {
					Debug::blue_LED1::low();
					Debug::blue_LED1::high();
				}
			}
			for (int i = 0; i < u_boot_spl_stm32_len; i++) {
				if (data[i] != u_boot_spl_stm32[i]) {
					printf("Data read back does not match: [%d] read: 0x%x, wrote: 0x%x\n\r",
						   i,
						   data[i],
						   u_boot_spl_stm32[i]);
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

		//Write FSBL2 @ 256k, blue + red on. Error: flash green
		Debug::red_LED1::low();
		Debug::blue_LED1::low();
		printf("Writing %d bytes to 0x%x\n\r", u_boot_spl_stm32_len, 256 * 1024);
		ok = flash.Write(u_boot_spl_stm32, 256 * 1024, u_boot_spl_stm32_len);
		if (!ok) {
			printf("Error writing\n\r");
			while (true) {
				Debug::green_LED1::low();
				HAL_Delay(250);
				Debug::green_LED1::high();
				HAL_Delay(250);
			}
		}
		Debug::red_LED1::high();
		Debug::blue_LED1::high();

		//Erase 64kblocks for SSBL: Red on. Error: flash green
		const int num_blocks = (u_boot_img_len / QSPI_64KBLOCK_SIZE) + 1;
		for (int i = 8; i < (8 + num_blocks); i++) {
			Debug::red_LED1::low();
			printf("Erasing Block#%d @ 0x%x\n\r", i, i * QSPI_64KBLOCK_SIZE);
			ok = flash.Erase(QSpiFlash::BLOCK_64K, i * QSPI_64KBLOCK_SIZE, QSpiFlash::EXECUTE_FOREGROUND);
			if (!ok) {
				printf("Error erasing block #%d\n\r", i);
				while (true) {
					Debug::green_LED1::low();
					HAL_Delay(250);
					Debug::green_LED1::high();
					HAL_Delay(250);
				}
			}
			Debug::red_LED1::high();
		}

		//Write SSBL @ 512k (2M length), green on
		Debug::green_LED1::low();
		printf("Writing %d bytes to 0x%x\n\r", u_boot_img_len, 512 * 1024);
		ok = flash.Write(u_boot_img, 512 * 1024, u_boot_img_len);
		if (!ok) {
			printf("Error writing\n\r");
			while (true) {
				Debug::red_LED1::low();
				HAL_Delay(250);
				Debug::red_LED1::high();
				HAL_Delay(250);
			}
		}
		Debug::green_LED1::high();

		//Verify
		{
			printf("Reading %d bytes from 0x%x\n\r", u_boot_img_len, 512 * 1024);
			auto data = std::make_unique<uint8_t[]>(u_boot_spl_stm32_len);
			ok = flash.Read(data.get(), 512 * 1024, u_boot_img_len, mdrivlib::QSpiFlash::EXECUTE_FOREGROUND);
			if (!ok) {
				printf("Error reading\n\r");
				while (true) {
					Debug::blue_LED1::low();
					HAL_Delay(250);
					Debug::blue_LED1::high();
					HAL_Delay(250);
				}
			}
			for (int i = 0; i < u_boot_img_len; i++) {
				if (data[i] != u_boot_img[i]) {
					printf(
						"Data read back does not match: [%d] read: 0x%x, wrote: 0x%x\n\r", i, data[i], u_boot_img[i]);
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
		printf("Successfully wrote SPL and u-boot to QSPI Flash\r\n");
	}
};
