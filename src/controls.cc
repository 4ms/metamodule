#include "controls.hh"
#include "debug.hh"
#include "drivers/interrupt.hh"

void Controls::read()
{
	// Debug::set_1(true);
	freq_cv0.read();
	res_cv0.read();
	freq_cv1.read();
	res_cv1.read();
	for (uint32_t i = 0; i < 2; i++) {
		rotary[i].update();
		rotary_button[i].update();
		mode_button[i].update();
		freq_sense[i].update();
		res_sense[i].update();
		in_sense[i].update();
		out_sense[i].update();
	}
	// Debug::set_1(false);
}

void Controls::start()
{
	read_controls_task.start();
}

Controls::Controls()
{
	CVADCPeriph::init_dma(ADC_DMA_conf, adc_buffer);
	// debug_control_read_timing();
	CVADCPeriph::start_adc();

	read_controls_task.init(control_read_tim_conf, [this]() { read(); });
}

static void debug_control_read_timing()
{
	// Debug: use this to read the DMA timing with an external pin:
	InterruptManager::registerISR(ADC_DMA_conf.IRQn, []() {
		if (LL_DMA_IsActiveFlag_TC0(DMA2)) {
			if (LL_DMA_IsEnabledIT_TC(DMA2, LL_DMA_STREAM_0)) {
				Debug::toggle_2();
			}
			LL_DMA_ClearFlag_TC0(DMA2);
		}
	});
	CVADCPeriph::enable_DMA_IT();
}
