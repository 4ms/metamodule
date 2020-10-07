#include "codec_WM8731.hh"
#include "conf/codec_sai_conf.hh"
#include "conf/i2c_conf.hh"
#include "conf/qspi_flash_conf.hh"
#include "conf/sdram_conf.hh"
#include "debug.hh"
#include "qspi_flash_driver.hh"
#include "sdram.hh"
#include "shared_bus.hh"
#include "stm32xx.h"
#include "system.hh"
#include "ui.hh"

System sys;
Debug debug;

SDRAMPeriph sdram{SDRAM_AS4C_conf};
QSpiFlash qspi{qspi_flash_conf};
SharedBus shared_bus{shared_i2c_conf};
CodecWM8731 codec{shared_bus.i2c, codec_sai_conf};
__attribute__((section(".dtcm"))) PCA9685Driver led_driver{shared_bus.i2c, kNumLedDriverChips, led_driver_dma_conf};

Controls controls;
Params params{controls};
__attribute__((section(".dtcm"))) Audio audio{params, codec};
LedCtl leds{led_driver};
Ui ui{params, leds};

void main()
{
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
