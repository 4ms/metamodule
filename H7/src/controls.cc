#include "controls.hh"
#include "debug.hh"

// CM7: 10kHz, 1.6% = 1.6us
void Controls::read()
{
	// Debug::Pin2::high();
	rotary.update();
	rotary_button.update();
	button0.update();
	button1.update();

	gate_in0.update();
	gate_in1.update();
	clock_in.update();

	// Debug::Pin2::low();
}

void Controls::start()
{
	cvadc.start();
	read_controls_task.start();
	read_cvadc_task.start();
}

Controls::Controls(MuxedADC &potadc, CVAdcChipT &cvadc)
	: potadc(potadc)
	, cvadc(cvadc)
{
	potadc.start();

	// Todo: use RCC_Control or create DBGMCU_Control:
	__HAL_DBGMCU_FREEZE_TIM6();

	read_controls_task.init(control_read_tim_conf, [this]() { read(); });
	read_cvadc_task.init(cvadc_tim_conf, [&cvadc]() { cvadc.start(); });
}

