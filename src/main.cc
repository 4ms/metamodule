#include "buses.hh"
#include "debug.hh"
#include "drivers/codec_WM8731.hh"
#include "sdram.hh"
#include "stm32xx.h"
#include "system.hh"
#include "ui.hh"

const uint32_t kSampleRate = 48000;

System sys;
Debug debug;
SDRAMPeriph sdram;

//Todo: some class for grouping codec, bus, led driver chips, etc
//ExternalChips exthw;
//exthw.codec
//exthw.shared_i2c
SharedBus shared_i2c;
CodecWM8731 codec{SharedBus::i2c};

Controls controls;
Params params{controls};
Audio audio{params, codec, kSampleRate};
LedCtl leds{SharedBus::i2c};
Ui ui{params, leds};

void main()
{
	sdram.test();

	audio.start();

	leds.start_dma_mode();

	controls.begin();

	while (1) {
		ui.update();
		leds.update();
		__NOP();
	}
}

