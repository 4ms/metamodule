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

using namespace MetaModule;
void main(void)
{
	target::corem4::SystemClocks start_clocks;

	Debug::Pin3::high();
	Debug::Pin2::high();
	while (HWSemaphore::is_locked<SharedBusLock>()) {
		Debug::Pin2::low();
	}
	Debug::Pin3::low();

	SharedBus::i2c.init(i2c_conf);

	// Todo: finish non-DMA PCA9685 driver and use it
	PCA9685DmaDriver::FrameBuffer led_frame_buffer;
	PCA9685DmaDriver led_driver{SharedBus::i2c, kNumLedDriverChips, {}, led_frame_buffer};
	LedCtl leds{led_driver};

	MuxedADC potadc{SharedBus::i2c, muxed_adc_conf};
	CVAdcChipT cvadc;

	Params params;
	extern char *_params_ptr; // defined by linker
	Params *params_cm7 = reinterpret_cast<Params *>(_params_ptr);

	Controls controls{potadc, cvadc, params, *params_cm7}; //, gpio_expander};

	SharedBus::i2c.enable_IT(i2c_conf.priority1, i2c_conf.priority2);

	controls.start();

	SharedBusQueue<leds.LEDUpdateRateHz> i2cqueue{leds, controls};

	while (1) {
		if (SharedBus::i2c.is_ready()) {
			Debug::Pin2::high();
			i2cqueue.update();
			Debug::Pin2::low();
		}
		controls.read();
	}
}

void recover_from_task_fault()
{
	main();
}

