#include "controls.hh"
#include "debug.hh"

void Controls::read()
{
	Debug::set_0(true);

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
	Debug::set_0(false);
}

void Controls::begin()
{
	read_controls_task.start();
}

Controls::Controls()
{
	CVADCPeriph::init_dma(ADC_DMA_conf);
	CVADCPeriph::start_adc();

	read_controls_task.init(control_read_tim_conf, [this]() { read(); });
}

