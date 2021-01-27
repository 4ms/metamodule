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
#include "sys/system_clocks.hh"
#include "ui.hh"

struct DualOpenerSystem : SystemClocks, Debug /*, SDRAMPeriph*/, SharedBus {
	DualOpenerSystem()
		// : SDRAMPeriph{SDRAM_48LC16M16_6A_conf}
		: SharedBus{i2c_conf}
	{}

	// Todo: this is not ideal to have DMA buffers in D1 domain. See:
	// https://community.st.com/s/article/FAQ-DMA-is-not-working-on-STM32H7-devices
	static inline __attribute__((section(".dtcm"))) PCA9685Driver::FrameBuffer led_frame_buffer;
	static inline __attribute__((section(".dtcm"))) Audio::AudioStreamBlock audio_dma_block[4];

} _hardware;

void main()
{

	CodecWM8731 codec{SharedBus::i2c, codec_sai_conf};
	QSpiFlash qspi{qspi_flash_conf};
	PCA9685Driver led_driver{SharedBus::i2c, kNumLedDriverChips, _hardware.led_frame_buffer};
	LedCtl leds{led_driver};

	__HAL_DBGMCU_FREEZE_TIM6();

	Controls controls;
	Params params{controls};

	Audio audio{params, codec, _hardware.audio_dma_block};

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
