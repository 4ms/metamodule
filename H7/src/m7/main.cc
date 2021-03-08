#include "conf/codec_sai_conf.hh"
#include "conf/control_conf.hh"
#include "conf/dac_conf.hh"
#include "conf/hsem_conf.hh"
#include "conf/i2c_conf.hh"
#include "conf/qspi_flash_conf.hh"
#include "conf/sdram_conf.hh"
#include "debug.hh"
#include "drivers/arch.hh"
#include "drivers/codec_WM8731.hh"
#include "drivers/dac_MCP48FVBxx.hh"
#include "drivers/gpio_expander.hh"
#include "drivers/hsem.hh"
#include "drivers/mpu.hh"
#include "drivers/qspi_flash_driver.hh"
#include "drivers/sdram.hh"
#include "drivers/stm32xx.h"
#include "drivers/system.hh"
#include "m7/system_clocks.hh"
#include "muxed_adc.hh"
#include "screen.hh"
#include "shared_bus.hh"
#include "shared_memory.hh"
#include "ui.hh"

namespace MetaModule
{
struct Hardware : SystemClocks, SDRAMPeriph, Debug /*, SharedBus*/ {
	Hardware()
		: SDRAMPeriph{SDRAM_48LC16M16_6A_conf}
	// , SharedBus{i2c_conf}
	{}

	// Todo: understand why setting the members to static inline causes SystemClocks ctor to hang on waiting for
	// D2CLKREADY

	// Todo: figure out how to use i2c on both cores -- OR -- separate Codec::I2C from Codec::SAI
	CodecWM8731 codec{SharedBus::i2c, codec_sai_conf};
	QSpiFlash qspi{qspi_flash_conf};
	AnalogOutT dac;
	Screen screen;
} _hw;

struct StaticBuffers {
	static inline __attribute__((section(".dma_buffer"))) AudioStream::AudioStreamBlock audio_dma_block[4];

	StaticBuffers()
	{
		target::MPU_::disable_cache_for_dma_buffer(audio_dma_block, sizeof(audio_dma_block));
	}
} _sb;

} // namespace MetaModule

void main()
{
	constexpr uint32_t LEDUpdateHz = 100;
	using namespace MetaModule;

	// Todo: use memory better: right now all patches get copied with CopyInitData with mostly zeros (some values?)
	// Then libc_init calls PatchList ctor. So make it static? Have a load() function? Keep in mind we'll want to
	// dynamically load patches at some point
	PatchList patch_list;

	Params params;

	params.init();

	AudioStream audio{params, patch_list, _hw.codec, _hw.dac, StaticBuffers::audio_dma_block};

	uint32_t led_frame_buf[PCA9685Driver::kNumLedsPerChip];
	LedFrame<LEDUpdateHz> leds{led_frame_buf};
	Ui<LEDUpdateHz> ui{params, patch_list, leds, _hw.screen};

	// SharedBus::i2c.enable_IT(i2c_conf.priority1, i2c_conf.priority2);

	ui.start();

	SharedMemory::write_address_of(&params, SharedMemory::ParamsPtrLocation);
	SCB_CleanDCache();

	HWSemaphore::unlock<SharedBusLock>();
	Debug::Pin1::high();

	// audio.start();

	while (1) {
		ui.update();
		__NOP();
	}
}

void recover_from_task_fault(void)
{
	main();
}
