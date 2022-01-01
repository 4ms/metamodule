#include "drivers/stm32xx.h"
#include "drivers/system_startup.hh"
#include "medium/conf/qspi_flash_conf.hh"
#include "medium/conf/rcc_conf.hh"
#include "medium/debug.hh"
#include "norflash-loader.hh"

namespace MetaModule
{

struct SystemInit : Debug {
} _sysinit;

} // namespace MetaModule

void main() {
	using namespace MetaModule;

	mdrivlib::SystemStartup::init_clocks(rcc_osc_conf, rcc_clk_conf, rcc_periph_clk_conf);

	NorFlashLoader load{qspi_flash_conf};

	while (true) {
	}
}

extern "C" void aux_core_main() {
}

void recover_from_task_fault() {
	main();
}
