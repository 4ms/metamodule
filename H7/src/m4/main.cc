#include "conf/control_conf.hh"
#include "conf/gpio_expander_conf.hh"
#include "conf/hsem_conf.hh"
#include "conf/i2c_conf.hh"
#include "conf/screen_conf.hh"
#include "controls.hh"
#include "debug.hh"
#include "drivers/arch.hh"
#include "drivers/gpio_expander_TCA9535.hh"
#include "drivers/hsem.hh"
#include "drivers/rcc.hh"
#include "drivers/stm32xx.h"
#include "m4/hsem_handler.hh"
#include "m4/system_clocks.hh"
#include "params.hh"
#include "screen_writer.hh"
#include "shared_bus.hh"
#include "shared_bus_queue.hh"
#include "shared_memory.hh"

using namespace MetaModule;

struct StaticBuffers {
	static inline __attribute__((section(".d3buffer"))) MMScreenConf::HalfFrameBufferT screen_writebuf;
} _sb;

void main(void)
{
	target::corem4::SystemClocks start_clocks;

	while (HWSemaphore<SharedBusLock>::is_locked()) {
	}
	HWSemaphore<M4_ready>::lock();

	SharedBus::i2c.init(i2c_conf);

	auto led_frame_buffer = SharedMemory::read_address_of<uint32_t *>(SharedMemory::LEDFrameBufLocation);
	auto param_block_base = SharedMemory::read_address_of<ParamBlock *>(SharedMemory::ParamsPtrLocation);
	auto screen_readbuf = SharedMemory::read_address_of<MMScreenConf::FrameBufferT *>(SharedMemory::ScreenBufLocation);

	// Led Driver
	PCA9685Driver led_driver{SharedBus::i2c, kNumLedDriverChips, led_frame_buffer};

	// Controls
	MuxedADC potadc{SharedBus::i2c, muxed_adc_conf};
	CVAdcChipT cvadc;
	GPIOExpander gpio_expander{SharedBus::i2c, gpio_expander_conf};
	Controls controls{potadc, cvadc, param_block_base, gpio_expander};

	// SharedBus
	SharedBusQueue<LEDUpdateHz> i2cqueue{led_driver, controls};
	SharedBus::i2c.enable_IT(i2c_conf.priority1, i2c_conf.priority2);
	led_driver.start_it_mode();
	controls.start();

	// Screen
	ScreenFrameWriter screen_writer{screen_readbuf, &StaticBuffers::screen_writebuf, MMScreenConf::HalfFrameBytes};
	screen_writer.init();

	// SemaphoreAction screenupdate {ScreenFrameBuf1Lock, [&](){ screen_writer.transfer_buffer_to_screen(); });
	HWSemaphore<ScreenFrameBufLock>::clear_ISR();
	HWSemaphore<ScreenFrameBufLock>::disable_channel_ISR();
	HWSemaphoreCoreHandler::register_channel_ISR<ScreenFrameBufLock>(
		[&]() { 
		HWSemaphore<ScreenFrameWriteLock>::lock();
		screen_writer.transfer_buffer_to_screen();
		HWSemaphore<ScreenFrameWriteLock>::unlock();
	});
	HWSemaphore<ScreenFrameBufLock>::enable_channel_ISR();

	HWSemaphore<ScreenFrameWriteLock>::disable_channel_ISR();
	HWSemaphore<ScreenFrameWriteLock>::unlock();

	HWSemaphoreCoreHandler::enable_global_ISR(2, 2);

	while (1) {
		if (SharedBus::i2c.is_ready()) {
			i2cqueue.update();
		}
		__NOP();
	}
}

void recover_from_task_fault()
{
	main();
}
