#include "conf/control_conf.hh"
#include "conf/hsem_conf.hh"
#include "conf/i2c_conf.hh"
#include "controls.hh"
#include "debug.hh"
#include "drivers/arch.hh"
#include "drivers/hsem.hh"
#include "drivers/rcc.hh"
#include "drivers/stm32xx.h"
#include "m4/system_clocks.hh"
#include "params.hh"
#include "shared_bus.hh"
#include "shared_memory.hh"

using namespace MetaModule;
void main(void)
{
	constexpr uint32_t LEDUpdateHz = 100;

	target::corem4::SystemClocks start_clocks;

	Debug::Pin3::high();
	Debug::Pin2::high();
	while (HWSemaphore::is_locked<SharedBusLock>()) {
		Debug::Pin2::low();
	}
	Debug::Pin3::low();
	Debug::Pin1::low();

	SharedBus::i2c.init(i2c_conf);

	uint32_t led_frame_buffer[PCA9685Driver::kNumLedsPerChip];
	PCA9685Driver led_driver{SharedBus::i2c, kNumLedDriverChips, led_frame_buffer};

	MuxedADC potadc{SharedBus::i2c, muxed_adc_conf};
	CVAdcChipT cvadc;

	Params params;
	Params *params_cm7 = SharedMemory::read_address_of<Params *>(SharedMemory::ParamsPtrLocation);

	Controls controls{potadc, cvadc, params, *params_cm7}; //, gpio_expander};

	SharedBus::i2c.enable_IT(i2c_conf.priority1, i2c_conf.priority2);

	led_driver.start_it_mode();
	controls.start();

	SharedBusQueue<LEDUpdateHz> i2cqueue{led_driver, controls};

	for (int i = 0; i < 16; i++) {
		led_frame_buffer[i] = 0x00000000;
	}
	led_frame_buffer[0] = 0x30 << 20;
	led_frame_buffer[1] = 0xF0 << 20;
	led_frame_buffer[2] = 0x30 << 20;

	led_frame_buffer[3] = 0x1F << 20;
	led_frame_buffer[4] = 0xF0 << 20;
	led_frame_buffer[5] = 0xF0 << 20;

	led_frame_buffer[6] = 0x1f << 20;
	led_frame_buffer[7] = 0xf0 << 20;
	led_frame_buffer[8] = 0xf0 << 20;

	led_frame_buffer[10] = 0x3f << 20;
	led_frame_buffer[10] = 0x30 << 20;
	led_frame_buffer[11] = 0x30 << 20;

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

