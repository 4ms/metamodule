#include "conf/qspi_flash_conf.hh"
#include "conf/rcc_conf.hh"
#include "console/uart_log.hh"
#include "debug.hh"
#include "drivers/qspi_flash_driver.hh"
#include "drivers/system_clocks.hh"
#include "pr_dbg.hh"
#include "usbdfu.h"

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

void main() {
	constexpr uint32_t base_addr = 0x50000;

	printf_("Flash chip loader started\n");

	mdrivlib::QSpiFlash flash{qspi_patchflash_conf};

	if (!flash.check_chip_id(0x180001, 0x00180001)) { //182001 or 186001 or 1840EF
		printf_("ERROR: NOR Flash returned wrong id\n");
		panic();
	}

	Debug::blue_LED1::low();
	Debug::green_LED1::low();
	Debug::red_LED1::low();

	//round up to smallest 4kB blocks that contains image
	unsigned bytes_to_erase = (usbdfu_uimg_len + 4095) & ~4095;
	printf_("Image size: 0x%x, erasing: 0x%x bytes\n", usbdfu_uimg_len, bytes_to_erase);
	uint32_t addr = base_addr;
	while (bytes_to_erase) {
		printf_("Erasing 0x%x\n", addr);
		flash.erase(mdrivlib::QSpiFlash::SECTOR, addr);
		addr += 4096;
		bytes_to_erase -= 4096;
	}

	printf_("Writing to 0x%x\n", base_addr);
	if (!flash.write(usbdfu_uimg, base_addr, usbdfu_uimg_len)) {
		Debug::blue_LED1::high();
		printf_("ERROR: Flash failed to write\n");
		panic();
	}

	printf_("OK\n");
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
