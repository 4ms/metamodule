#include "buses.hh"
#include "debug.hh"
#include "defs/sdram_defs.hh"
#include "drivers/codec_WM8731.hh"
#include "sdram.hh"
#include "stm32xx.h"
#include "system.hh"
#include "ui.hh"
#include "qspi_flash_driver.hh"
#include "qspi_flash_defs.hh"

const uint32_t kSampleRate = 48000;

System sys;
Debug debug;

// Note:
// SDRAM is 4 x 64MB, from 0xC000 0000 to 0xC200 0000
// PCB p2 has only 12 address pins connected, so we can only
// access up to 0xC080 0000, or 64MBit = 8MByte
SDRAMPeriph sdram{SDRAMTiming_AS4C16M16SA_7CN, 0xC0000000, 0x00800000};

QSpiFlash qspi{kQSPIDefs};

// Todo: some class for grouping codec, bus, led driver chips, etc
// ExternalChips exthw;
// exthw.codec
// exthw.shared_i2c
SharedBus shared_i2c;
CodecWM8731 codec{SharedBus::i2c};

Controls controls;
Params params{controls};
Audio audio{params, codec, kSampleRate};
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

