#include "conf/control_conf.hh"
#include "conf/hsem_conf.hh"
#include "conf/i2c_conf.hh"
#include "conf/screen_conf.hh"
#include "controls.hh"
#include "debug.hh"
#include "drivers/arch.hh"
#include "drivers/hsem.hh"
#include "drivers/rcc.hh"
#include "drivers/stm32xx.h"
#include "m4/hsem_handler.hh"
#include "m4/system_clocks.hh"
#include "params.hh"
#include "screen_writer.hh"
#include "shared_bus.hh"
#include "shared_memory.hh"

using namespace MetaModule;

struct StaticBuffers {
	static inline __attribute__((section(".d3buffer"))) uint32_t screen_writebuf_base;
} _sb;

void main(void)
{
	target::corem4::SystemClocks start_clocks;

	while (HWSemaphore<SharedBusLock>::is_locked()) {
		Debug::Pin2::high();
		Debug::Pin2::low();
	}

	Debug::Pin1::high();
	SharedBus::i2c.init(i2c_conf);
	Debug::Pin1::low();

	auto led_frame_buffer = SharedMemory::read_address_of<uint32_t *>(SharedMemory::LEDFrameBufferLocation);
	PCA9685Driver led_driver{SharedBus::i2c, kNumLedDriverChips, led_frame_buffer};

	MuxedADC potadc{SharedBus::i2c, muxed_adc_conf};
	CVAdcChipT cvadc;
	auto param_block_base = SharedMemory::read_address_of<ParamBlock *>(SharedMemory::ParamsPtrLocation);
	Controls controls{potadc, cvadc, param_block_base}; //, gpio_expander};

	SharedBus::i2c.enable_IT(i2c_conf.priority1, i2c_conf.priority2);

	led_driver.start_it_mode();
	controls.start();
	HWSemaphoreCoreHandler::enable_global_ISR(0, 0);

	uint32_t *screen_writebuf = &StaticBuffers::screen_writebuf_base;
	auto screen_readbuf =
		SharedMemory::read_address_of<MMScreenConf::FrameBufferT *>(SharedMemory::ScreenFrameBufferLocation);
	ScreenFrameWriter screen_writer{screen_readbuf, screen_writebuf, sizeof(MMScreenConf::FrameBufferT) / 2};
	screen_writer.init();
	HWSemaphore<ScreenFrameBuf1Lock>::enable_channel_ISR();
	HWSemaphoreCoreHandler::register_channel_ISR<ScreenFrameBuf1Lock>([]() {
		Debug::Pin3::high();
		Debug::Pin3::low();
		// screen_writer.transfer_buffer_to_screen();
	});

	SharedBusQueue<LEDUpdateHz> i2cqueue{led_driver, controls};

	while (1) {
		if (SharedBus::i2c.is_ready()) {
			i2cqueue.update();
		}
	}
}

void recover_from_task_fault()
{
	main();
}
