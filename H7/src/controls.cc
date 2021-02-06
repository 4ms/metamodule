#include "controls.hh"
#include "debug.hh"
#include "drivers/interrupt.hh"

void Controls::read()
{
	// Debug::set_3(true);
	// todo: oversampling collection needs to happen when ADC ISR is hit
	// then here we do nothing
	// and in params.update we copy oversampler result to params.cvjacks
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
	cvadc.start();
	read_controls_task.start();
}

Controls::Controls(MuxedADC &potadc)
	: potadc(potadc)
{
	potadc.start();

	// Todo: use RCC_Control or create DBGMCU_Control:
	__HAL_DBGMCU_FREEZE_TIM6();

	read_controls_task.init(control_read_tim_conf, [this]() { read(); });
}

