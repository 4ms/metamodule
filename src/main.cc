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

SDRAMPeriph sdram{SDRAM_AS4C_conf, 0xC0000000, 0x00800000};
QSpiFlash qspi{qspi_flash_conf};

SharedBus shared_i2c{shared_i2c_conf};
CodecWM8731 codec{SharedBus::i2c, codec_sai_conf};

Controls controls;
Params params{controls};
Audio audio{params, codec};
LedCtl leds{SharedBus::i2c};
Ui ui{params, leds};

void main()
{
	audio.start();

	leds.start_dma_mode();

	controls.begin();

	while (1) {
		ui.update();
		leds.update();
		__NOP();
	}
}

