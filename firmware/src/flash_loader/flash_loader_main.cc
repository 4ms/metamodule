#include "conf/rcc_conf.hh"
#include "console/uart_log.hh"
#include "debug.hh"
#include "drivers/system_clocks.hh"
#include "flash_loader.hh"
#include "fsbl.h"
#include "pr_dbg.hh"
#include "usbdfu.h"
#include <span>

namespace MetaModule::BootloaderUpdater
{

struct BootloaderUpdaterClocks {
	BootloaderUpdaterClocks() {
		using namespace mdrivlib;
		SystemClocks::init_clocks(rcc_osc_conf, rcc_clk_conf, rcc_periph_clk_conf);
	}
};

struct SystemInit : BootloaderUpdaterClocks, Debug, UartLog {
} _sysinit;

static void panic();

void main() {

	pr_info("Flash chip loader started\n");

	FlashLoader flash;

	if (!flash.check_flash_chip()) {
		pr_err("ERROR: NOR Flash returned wrong id\n");
		panic();
	}

	Debug::blue_LED1::low();
	Debug::green_LED1::low();
	Debug::red_LED1::low();

	// Erase and write flash starting with the higher addresses and working down
	// That way, if something goes wrong, we are more likely to have a working fsbl.

	constexpr uint32_t usbdfu_base_addr = 0x50000;
	if (!flash.write_sectors(usbdfu_base_addr, {usbdfu_uimg, usbdfu_uimg_len}))
		panic();

	constexpr uint32_t fsbl_base_addr2 = 0x40000;
	if (!flash.write_sectors(fsbl_base_addr2, {fsbl_stm32, fsbl_stm32_len}))
		panic();

	constexpr uint32_t fsbl_base_addr1 = 0x00000;
	if (!flash.write_sectors(fsbl_base_addr1, {fsbl_stm32, fsbl_stm32_len}))
		panic();

	pr_info("Done.\n");

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

} // namespace MetaModule::BootloaderUpdater

extern "C" void aux_core_main() {
	while (true) {
		__WFI();
	}
}

void main() {
	MetaModule::BootloaderUpdater::main();
}
