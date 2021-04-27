#include "a7/hsem_handler.hh"
#include "drivers/hsem.hh"
// #include "drivers/qspi_flash_driver.hh"
// #include "drivers/system.hh"
#include "a7/static_buffers.hh"
// #include "ui.hh"
#include "a7/conf/codec_sai_conf.hh"
#include "a7/conf/i2c_conf.hh"
#include "a7/system_clocks.hh"
#include "audio.hh"
#include "codec_WM8731.hh"
#include "conf/dac_conf.hh"
#include "debug.hh"
#include "drivers/stm32xx.h"
// #include "params.hh"
// #include "patch_player.hh"
// #include "patchlist.hh"
#include "shared_bus.hh"
// #include "shared_memory.hh"

#include "drivers/pin.hh"

namespace MetaModule
{

// Define the hardware elements used by Core A7
// This initializes the SystemClocks (RCC) and other system resources
// and then initializes the external chips that this core uses, before main() runs
struct Hardware : AppStartup, Debug, SharedBus {
	Hardware()
		: SharedBus{i2c_conf_codec}
	{}

	CodecWM8731 codec{SharedBus::i2c, codec_sai_conf};
	// 	QSpiFlash qspi{qspi_flash_conf}; // not used yet, but will hold patches, and maybe graphics/fonts
	AnalogOutT dac;
} _hw;

} // namespace MetaModule

void timing_test(uint32_t addr);

void main()
{
	using namespace MetaModule;
	Debug::Pin2::low();

	__disable_irq();
	auto x = GIC_AcknowledgePending();
	unsigned num_irq = 32U * ((GIC_DistributorInfo() & 0x1FU) + 1U);
	for (unsigned i = 32; i < num_irq; i++) {
		GIC_EndInterrupt((IRQn_Type)i);
		GIC_ClearPendingIRQ((IRQn_Type)i);
	}
	__enable_irq();
	GIC_Enable();

	// with MMU: 4.8s for 4006 instructions: 834MIPS
	Debug::Pin2::low();
	Debug::Pin1::high();
	for (uint32_t i = 0; i < 1000; i++) {
		asm volatile("MOVW R0, #0x5556\n"
					 "MOVW R0, #0xAAAA\n");
	}
	Debug::Pin2::high();
	Debug::Pin1::low();

	// // 14.2us for 4001 instructions: 281MIPS
	// Debug::Pin2::low();
	// asm volatile("MOVW R3, #0\n"
	// 			 "cloop: \n"
	// 			 "MOVW R0, #0x5556\n"
	// 			 "ADD R3, R3, #1\n"
	// 			 "CMP R3, #0x03E8\n"
	// 			 "BNE cloop\n");
	Debug::Pin2::high();
	Debug::Pin1::high();
	// w/o MMU: 14us for 4006 instructions: 286MIPS
	// with MMU: 4.99us --> 802MIPS
	timing_test(0xD8000000);
	Debug::Pin1::low();

	// w/o MMU: 48us for 4007 instructions: 83MIPS (each test)
	// with MMU: 4.9us--> 830MIPS
	timing_test(0x10000000);
	Debug::Pin1::high();
	timing_test(0x10020000);
	Debug::Pin1::low();
	timing_test(0x10040000);
	Debug::Pin1::high();
	timing_test(0x10050000);
	Debug::Pin1::low();

	Debug::Pin2::low();
	// HWSemaphoreGlobalBase::register_channel_ISR<1>([]() {
	// 	Debug::red_LED1::high();
	// 	Debug::Pin0::high();
	// });
	// HWSemaphoreCoreHandler::enable_global_ISR(0, 0);

	// HWSemaphore<1>::disable_channel_ISR();
	// HWSemaphore<1>::clear_ISR();
	// target::System::enable_irq(HSEM_IT1_IRQn);
	// HWSemaphore<1>::enable_channel_ISR();
	// HWSemaphore<1>::lock();
	// HWSemaphore<1>::unlock();

	StaticBuffers::init();

	PatchList patch_list;
	PatchPlayer patch_player;
	ParamCache param_cache;
	UiAudioMailbox mbox;

	LedFrame<LEDUpdateHz> leds{StaticBuffers::led_frame_buffer};
	// Ui<LEDUpdateHz> ui{patch_list, patch_player, param_cache, mbox, leds, StaticBuffers::screen_framebuf};

	AudioStream audio{patch_list,
					  patch_player,
					  _hw.codec,
					  _hw.dac,
					  param_cache,
					  mbox,
					  StaticBuffers::param_blocks,
					  StaticBuffers::audio_dma_block};

	SharedBus::i2c.deinit();

	// SharedMemory::write_address_of(&StaticBuffers::param_blocks, SharedMemory::ParamsPtrLocation);
	// SharedMemory::write_address_of(&StaticBuffers::led_frame_buffer, SharedMemory::LEDFrameBufLocation);
	// SharedMemory::write_address_of(&StaticBuffers::screen_framebuf, SharedMemory::ScreenBufLocation);
	// SCB_CleanDCache();

	// HWSemaphoreCoreHandler::enable_global_ISR(2, 1);

	// // Tell M4 we're done with init
	// HWSemaphore<M7_ready>::unlock();

	// // wait for M4 to be ready
	// while (HWSemaphore<M4_ready>::is_locked())
	// 	;

	param_cache.clear();
	// ui.start();
	patch_player.load_patch(patch_list.cur_patch());
	audio.start();

	while (1) {
		Debug::red_LED1::low();
		HAL_Delay(500);
		Debug::red_LED1::high();

		Debug::red_LED2::low();
		HAL_Delay(500);
		Debug::red_LED2::high();

		Debug::green_LED1::low();
		HAL_Delay(500);
		Debug::green_LED1::high();

		Debug::green_LED2::low();
		HAL_Delay(500);
		Debug::green_LED2::high();

		__NOP();
	}
}

void timing_test(uint32_t addr)
{
	auto baseaddr = reinterpret_cast<uint32_t *>(addr);
	for (uint32_t i = 0; i < 1000; i++) {
		// Debug::Pin0::high();
		*baseaddr++ = i;
		// Debug::Pin0::low();
	}

	// STR STR ADD STR CMP BNE
	// ~5.95MHz ---> 6 instructions means 24MHz
}

void recover_from_task_fault(void)
{
	main();
}
