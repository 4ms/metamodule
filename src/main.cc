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
	Controls controls;
	Params params{controls};
	// Todo: pass a buffer that's already created in section dctm to Audio/PCA9685
	// Or use a custom allocator to ensure the DMA member variables are created in dctm section
	static __attribute__((section(".dtcm"))) Audio audio{params, codec};
	static __attribute__((section(".dtcm")))
	PCA9685Driver led_driver{SharedBus::i2c, kNumLedDriverChips, led_driver_dma_conf};
	LedCtl leds{led_driver};

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
