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
#include "drivers/qspi_flash_driver.hh"
#include "drivers/sdram.hh"
#include "drivers/stm32xx.h"
#include "drivers/system.hh"
#include "m7/static_buffers.hh"
#include "m7/system_clocks.hh"
#include "muxed_adc.hh"
#include "shared_bus.hh"
#include "shared_memory.hh"
#include "ui.hh"

namespace MetaModule
{

// Define our hardware elements
// This initializes the SystemClocks (RCC) and other system resources
// and then initializes the external chips that this core uses, all before main() runs
struct Hardware : SystemClocks, SDRAMPeriph, Debug, SharedBus {
	Hardware()
		: SDRAMPeriph{SDRAM_48LC16M16_6A_conf}
		, SharedBus{i2c_conf_m7}
	{}

	CodecWM8731 codec{SharedBus::i2c, codec_sai_conf};
	QSpiFlash qspi{qspi_flash_conf}; // not used yet, but will hold patches, and maybe graphics/fonts
	AnalogOutT dac;
} _hw;

} // namespace MetaModule

void main()
{
	using namespace MetaModule;

	Params last_params;
	PatchList patch_list;
	PatchPlayer patch_player;

	AudioStream audio{patch_list,
					  patch_player,
					  _hw.codec,
					  _hw.dac,
					  StaticBuffers::param_blocks,
					  last_params,
					  StaticBuffers::audio_dma_block};
	LedFrame<LEDUpdateHz> leds{StaticBuffers::led_frame_buffer};
	Ui<LEDUpdateHz> ui{patch_list, patch_player, leds, last_params, StaticBuffers::screen_framebuf};

	SharedBus::i2c.deinit();

	SharedMemory::write_address_of(&StaticBuffers::param_blocks, SharedMemory::ParamsPtrLocation);
	SharedMemory::write_address_of(&StaticBuffers::led_frame_buffer, SharedMemory::LEDFrameBufLocation);
	SharedMemory::write_address_of(&StaticBuffers::screen_framebuf, SharedMemory::ScreenBufLocation);
	SCB_CleanDCache();

	HWSemaphoreCoreHandler::enable_global_ISR(2, 1);
	HWSemaphore<SharedBusLock>::disable_channel_ISR();
	HWSemaphore<SharedBusLock>::unlock();

	// wait for M4 to be ready
	while (HWSemaphore<M4_ready>::is_locked()) {
	}

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
