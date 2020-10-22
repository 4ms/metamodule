#include "conf/codec_sai_conf.hh"
#include "conf/i2c_conf.hh"
#include "conf/qspi_flash_conf.hh"
#include "conf/sdram_conf.hh"
#include "debug.hh"
#include "drivers/codec_WM8731.hh"
#include "drivers/qspi_flash_driver.hh"
#include "drivers/sdram.hh"
#include "drivers/stm32xx.h"
#include "drivers/system.hh"
#include "shared_bus.hh"
#include "ui.hh"

struct DualOpenerSystem : System, Debug, SDRAMPeriph, SharedBus {
	DualOpenerSystem()
		: SDRAMPeriph{SDRAM_AS4C_conf}
		, SharedBus{i2c_conf}
	{}
} _;

void main()
{
	CodecWM8731 codec{SharedBus::i2c, codec_sai_conf};
	QSpiFlash qspi{qspi_flash_conf};
	PCA9685Driver led_driver{SharedBus::i2c, kNumLedDriverChips, led_driver_dma_conf};
	LedCtl leds{led_driver};

	Controls controls;
	Params params{controls};
	Audio audio{params, codec};

	Ui ui{params, leds};

	audio.start();
	ui.start();

	while (1) {
		ui.update();
		__NOP();
	}
}

void recover_from_task_fault(void)
{
	main();
}
