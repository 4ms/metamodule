#include "controls.hh"
#include "debug.hh"
#include "drivers/interrupt.hh"

void Controls::read()
{
	// Debug::set_3(true);
	cvadc.read();

	rotary.update();
	rotary_button.update();
	for (uint32_t i = 0; i < 2; i++) {
		button[i].update();
		// cv_sense[i].update();
		// cv_sense[i + 2].update();
		// in_sense[i].update();
		// out_sense[i].update();
		// dac_sense[i].update();
		// trig_in_sense[i].update();
	}
	// Debug::set_3(false);
}

void Controls::start()
{
	read_controls_task.start();
}

Controls::Controls()
{
	cvadc.start();
	// debug_control_read_timing();

	read_controls_task.init(control_read_tim_conf, [this]() { read(); });
}

static void debug_control_read_timing()
{
	// Debug: use this to read the DMA timing with an external pin:
	// InterruptManager::registerISR(ADC_DMA_conf.IRQn, []() {
	// 	if (LL_DMA_IsActiveFlag_TC0(DMA2)) {
	// 		if (LL_DMA_IsEnabledIT_TC(DMA2, LL_DMA_STREAM_0)) {
	// 			Debug::toggle_2();
	// 		}
	// 		LL_DMA_ClearFlag_TC0(DMA2);
	// 	}
	// });
	// CVADCPeriph::enable_DMA_IT();
}
