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
#include "sys/rcc.hh"
#include "ui.hh"

struct DualOpenerSystem : SystemClocks, Debug, SDRAMPeriph, SharedBus {
	DualOpenerSystem()
		: SDRAMPeriph{SDRAM_AS4C_conf}
		, SharedBus{i2c_conf}
	{}
} _hardware;

void main()
{
	CodecWM8731 codec{SharedBus::i2c, codec_sai_conf};
	QSpiFlash qspi{qspi_flash_conf};
	static __attribute__((section(".dtcm")))
	PCA9685Driver led_driver{SharedBus::i2c, kNumLedDriverChips, led_driver_dma_conf};
	LedCtl leds{led_driver};

	Controls controls;
	Params params{controls};
	static __attribute__((section(".dtcm"))) Audio audio{params, codec};

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
