#include "conf/qspi_flash_conf.hh"
#include "conf/rcc_conf.hh"
#include "console/uart_log.hh"
#include "debug.hh"
#include "drivers/qspi_flash_driver.hh"
#include "drivers/system_clocks.hh"
#include "fsbl.h"
#include "pr_dbg.hh"
#include "usbdfu.h"
#include <span>

namespace MetaModule::FlashLoader
{

struct FlashLoaderClocks {
	FlashLoaderClocks() {
		using namespace mdrivlib;
		SystemClocks::init_clocks(rcc_osc_conf, rcc_clk_conf, rcc_periph_clk_conf);
	}
};

struct SystemInit : FlashLoaderClocks, Debug, UartLog {
} _sysinit;

static void panic();
static void flash_sectors(mdrivlib::QSpiFlash &flash, uint32_t base_addr, std::span<uint8_t> buffer);

void main() {

	pr_info("Flash chip loader started\n");

	mdrivlib::QSpiFlash flash{qspi_patchflash_conf};

	if (!flash.check_chip_id(0x180001, 0x00180001)) { //182001 or 186001 or 1840EF
		pr_err("ERROR: NOR Flash returned wrong id\n");
		panic();
	}

	Debug::blue_LED1::low();
	Debug::green_LED1::low();
	Debug::red_LED1::low();

	// Erase and write flash starting with the higher addresses and working down
	// That way, if something goes wrong, we are more likely to have a working fsbl.

	constexpr uint32_t usbdfu_base_addr = 0x50000;
	flash_sectors(flash, usbdfu_base_addr, {usbdfu_uimg, usbdfu_uimg_len});

	constexpr uint32_t fsbl_base_addr2 = 0x40000;
	flash_sectors(flash, fsbl_base_addr2, {fsbl_stm32, fsbl_stm32_len});

	constexpr uint32_t fsbl_base_addr1 = 0x00000;
	flash_sectors(flash, fsbl_base_addr1, {fsbl_stm32, fsbl_stm32_len});

	pr_info("OK\n");
	while (true) {
		Debug::blue_LED1::high();
		HAL_Delay(300);
		Debug::blue_LED1::low();
		HAL_Delay(300);
		Debug::green_LED1::high();
		HAL_Delay(300);
		Debug::green_LED1::low();
		HAL_Delay(300);
	}
}

void flash_sectors(mdrivlib::QSpiFlash &flash, uint32_t base_addr, std::span<uint8_t> buffer) {
	//round up to smallest 4kB blocks that contains image
	unsigned bytes_to_erase = (buffer.size() + 4095) & ~4095;
	pr_info("Image size: 0x%x, erasing: 0x%x bytes\n", buffer.size(), bytes_to_erase);
	uint32_t addr = base_addr;
	while (bytes_to_erase) {
		pr_info("Erasing 0x%x\n", (unsigned)addr);
		flash.erase(mdrivlib::QSpiFlash::SECTOR, addr);
		addr += 4096;
		bytes_to_erase -= 4096;
	}

	printf("Writing to 0x%x\n", (unsigned)base_addr);
	if (!flash.write(buffer.data(), base_addr, buffer.size())) {
		Debug::blue_LED1::high();
		pr_err("ERROR: Flash failed to write\n");
		panic();
	}
}

void panic() {
	while (true) {
		Debug::red_LED1::high();
		HAL_Delay(100);
		Debug::red_LED1::low();
		HAL_Delay(100);
	}
}

} // namespace MetaModule::FlashLoader

extern "C" void aux_core_main() {
	while (true) {
		__WFI();
	}
}

void main() {
	MetaModule::FlashLoader::main();
}
