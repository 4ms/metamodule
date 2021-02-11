#include "controls.hh"
#include "debug.hh"
#include "drivers/interrupt.hh"

// CM7: 10kHz, 3.3%
void Controls::read()
{
	Debug::Pin2::high();
	rotary.update();
	// rotary_button.update();
	button1.update();
	button2.update();

	// gate_ins[0].update();
	// gate_ins[1].update();
	// gate_ins[2].update();

	Debug::Pin2::low();
}

void Controls::start()
{
	cvadc.start();
	read_controls_task.start();
}

Controls::Controls(MuxedADC &potadc, CVAdcChipT &cvadc)
	: potadc(potadc)
	, cvadc(cvadc)
{
	potadc.start();

	// Todo: use RCC_Control or create DBGMCU_Control:
	__HAL_DBGMCU_FREEZE_TIM6();

	read_controls_task.init(control_read_tim_conf, [this]() { read(); });
}

