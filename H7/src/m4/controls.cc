#include "controls.hh"
#include "debug.hh"
#include <cstring>

// CM7: 10kHz, 1.6% = 1.6us
void Controls::read()
{
	rotary.update();
	rotary_button.update();
	button0.update();
	button1.update();

	gate_in0.update();
	gate_in1.update();
	clock_in.update();

	Debug::Pin3::high();

	for (int i = 0; i < 4; i++) {
		params.cvjacks[i] = (2047.5f - static_cast<float>(cvadc.get_val(i))) / 2047.5f;
	}

	int tmp_rotary_motion = rotary.read();

	if (rotary_button.is_just_pressed()) {
		_rotary_moved_while_pressed = false;
		params.rotary_button.register_rising_edge();
	}
	if (rotary_button.is_just_released() && !_rotary_moved_while_pressed) {
		params.rotary_button.register_falling_edge();
	}
	if (rotary_button.is_pressed()) {
		if (params.rotary_motion != 0) {
			_rotary_moved_while_pressed = true;
			params.rotary_pushed_motion += tmp_rotary_motion;
		}
	} else {
		params.rotary_motion += tmp_rotary_motion;
	}

	params.buttons[0].copy_state(button0);
	params.buttons[1].copy_state(button1);
	params.rotary_button.copy_state(rotary_button);
	params.gate_ins[0].copy_state(gate_in0);
	params.gate_ins[1].copy_state(gate_in1);
	params.clock_in.copy_state(clock_in);

	for (int i = 0; i < 8; i++)
		params.knobs[i] = get_pot_reading(i) / 4095.0f;

	params.patchcv = get_patchcv_reading() / 4095.0f;
	Debug::Pin3::low();

	Debug::Pin1::high();
	params.lock_for_write();
	mem_xfer.start_transfer();
}

void Controls::start()
{
	params.unlock_for_write();
	potadc.start();
	cvadc.start();

	// mem_xfer.registerCallback([&]() {
	// 	params.unlock_for_write();
	// 	Debug::Pin1::low();
	// });
	InterruptManager::registerISR(MDMA_IRQn, 1, 1, [&]() {
		if ((MDMA_Channel0->CISR & MDMA_CISR_BRTIF) && (MDMA_Channel0->CCR & MDMA_CCR_BRTIE)) {
			MDMA_Channel0->CIFCR = MDMA_CIFCR_CBRTIF;
		}

		if ((MDMA_Channel0->CISR & MDMA_CISR_BTIF) && (MDMA_Channel0->CCR & MDMA_CCR_BTIE)) {
			MDMA_Channel0->CIFCR = MDMA_CIFCR_CBTIF;
		}

		if ((MDMA_Channel0->CISR & MDMA_CISR_CTCIF) && (MDMA_Channel0->CCR & MDMA_CCR_CTCIE)) {
			MDMA_Channel0->CIFCR = MDMA_CIFCR_CCTCIF;
			// params.unlock_for_write();
			// Debug::Pin1::low();
		}

		if ((MDMA_Channel0->CISR & MDMA_CISR_TCIF) && (MDMA_Channel0->CCR & MDMA_CCR_TCIE)) {
			MDMA_Channel0->CIFCR = MDMA_CIFCR_CLTCIF;
			params.unlock_for_write();
			Debug::Pin1::low();
			// callback();
		}
	});

	Debug::Pin2::high();
	params.lock_for_write();
	Debug::Pin1::high();
	Debug::Pin2::low();
	mem_xfer.config_transfer(&dest, &params, sizeof(Params));
	mem_xfer.start_transfer();
	while (params._is_locked()) {
		Debug::Pin3::high();
		Debug::Pin3::low();
	}

	read_controls_task.start();
	read_cvadc_task.start();
	clock_out.low();
}

Controls::Controls(MuxedADC &potadc, CVAdcChipT &cvadc, Params &params, Params &dest)
	: potadc(potadc)
	, cvadc(cvadc)
	, params(params)
	, dest(dest)
{
	// Todo: use RCC_Control or create DBGMCU_Control:
	__HAL_DBGMCU_FREEZE_TIM6();

	read_controls_task.init(control_read_tim_conf, [this]() { read(); });
	read_cvadc_task.init(cvadc_tim_conf, [&cvadc]() { cvadc.read_and_switch_channels(); });
}

