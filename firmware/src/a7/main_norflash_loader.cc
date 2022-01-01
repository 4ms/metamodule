#include "app_startup.hh"
#include "conf/rcc_conf.hh"
#include "debug.hh"
#include "drivers/stm32xx.h"
#include "drivers/system_startup.hh"
#include "u-boot-norflash/norflash-loader.hh"

namespace MetaModule
{

struct SystemInit : Debug {
} _sysinit;

} // namespace MetaModule

void main() {
	using namespace MetaModule;

	mdrivlib::SystemStartup::init_clocks(rcc_osc_conf, rcc_clk_conf, rcc_periph_clk_conf);

	NorFlashLoader load{};

	while (true) {
	}
}

void recover_from_task_fault() {
	main();
}
