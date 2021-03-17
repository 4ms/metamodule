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
#include "shared_bus.hh"
#include "shared_memory.hh"
#include "ui.hh"

namespace MetaModule
{
struct Hardware : SystemClocks, SDRAMPeriph, Debug, SharedBus {
	Hardware()
		: SDRAMPeriph{SDRAM_48LC16M16_6A_conf}
		, SharedBus{i2c_conf}
	{}

	// Todo: understand why setting the members to static inline causes SystemClocks ctor to hang on waiting for
	// D2CLKREADY

	CodecWM8731 codec{SharedBus::i2c, codec_sai_conf};
	QSpiFlash qspi{qspi_flash_conf};
	AnalogOutT dac;
} _hw;

struct StaticBuffers {
	static inline __attribute__((section(".dma_buffer"))) AudioStream::AudioStreamBlock audio_dma_block[4];
	static inline __attribute__((section(".dma_buffer"))) uint32_t led_frame_buffer[PCA9685Driver::kNumLedsPerChip];
	static inline __attribute__((section(".dma_buffer"))) ParamBlock param_blocks[2];
	static inline __attribute__((section(".axisram"))) MMScreenConf::FrameBufferT screen_framebuf;
	static inline __attribute__((section(".d3buffer"))) uint32_t screen_writebuf_base;

	StaticBuffers()
	{
		target::MPU_::disable_cache_for_dma_buffer(audio_dma_block, sizeof(audio_dma_block));
	}
} _sb;

} // namespace MetaModule

// Todo: use PatchList memory better: right now all patches get copied with CopyInitData with mostly zeros (some
// values?) Then libc_init calls PatchList ctor. So make it static? Have a load() function? Keep in mind we'll want to
// dynamically load patches at some point

void main()
{
	using namespace MetaModule;

	Params last_params;
	PatchList patch_list;

	AudioStream audio{
		patch_list, _hw.codec, _hw.dac, StaticBuffers::param_blocks, last_params, StaticBuffers::audio_dma_block};
	LedFrame<LEDUpdateHz> leds{StaticBuffers::led_frame_buffer};
	Ui<LEDUpdateHz> ui{last_params, patch_list, leds, StaticBuffers::screen_framebuf};

	SharedBus::i2c.deinit();

	HWSemaphoreCoreHandler::enable_global_ISR(2, 1);

	SharedMemory::write_address_of(&StaticBuffers::param_blocks, SharedMemory::ParamsPtrLocation);
	SharedMemory::write_address_of(&StaticBuffers::led_frame_buffer, SharedMemory::LEDFrameBufferLocation);
	SharedMemory::write_address_of(&StaticBuffers::screen_framebuf, SharedMemory::ScreenFrameBufferLocation);
	SCB_CleanDCache();

	HWSemaphore<SharedBusLock>::disable_channel_ISR();
	HWSemaphore<SharedBusLock>::unlock();

	// wait for M4 to be ready

	Debug::Pin1::high();
	while (HWSemaphore<M4_ready>::is_locked())
		;
	Debug::Pin1::low();

	ui.start();
	audio.start();

	while (1) {
		__NOP();
	}
}

void recover_from_task_fault(void)
{
	main();
}
