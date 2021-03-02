#include "drivers/arch.hh"
#include "drivers/hsem.hh"
#include "drivers/rcc.hh"
#include "drivers/stm32xx.h"

#include "debug.hh"

void main(void)
{
	target::RCC_Control::HSEM_::set();

	constexpr uint32_t HSEM_id_mask = 1 << 0;

	target::HSEM_::template IER<HSEM_id_mask>::set();

	// Domain D2 goes to STOP mode (Cortex-M4 in deep-sleep) waiting for Cortex-M7 to
	// perform system initialization (system clock config, external memory configuration.. )
	HAL_PWREx_ClearPendingEvent();
	HAL_PWREx_EnterSTOPMode(PWR_MAINREGULATOR_ON, PWR_STOPENTRY_WFE, PWR_D2_DOMAIN);

	// __HAL_HSEM_CLEAR_FLAG(HSEM_id_mask);
	target::HSEM_::template ICR<HSEM_id_mask>::set();

	HAL_Init();
	target::RCC_Control::SYSCFG_::set();

	while (1) {
		Debug::Pin3::high();
		Debug::Pin3::low();
	}
}

void recover_from_task_fault()
{
	main();
}
