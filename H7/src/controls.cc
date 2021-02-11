#include "controls.hh"
#include "debug.hh"
#include "drivers/interrupt.hh"

void Controls::read()
{
	// Debug::set_3(true);

	rotary.update();
	rotary_button.update();
	button[0].update();
	button[1].update();

	// Debug::set_3(false);
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

