#include "buses.hh"
#include "debug.hh"
#include "stm32f7xx.h"
#include "system.hh"
#include "ui.hh"

const uint32_t kSampleRate = 48000;

System sys;
Debug debug;
SharedBus shared_i2c;

Controls controls;
Params params{controls};
Audio audio{params, SharedBus::i2c, kSampleRate};
LedCtl leds{SharedBus::i2c};
Ui ui{params, leds};

void main()
{
	audio.start();

	leds.start_dma_mode();

	controls.begin();

	while (1) {
		ui.update();
		leds.update();
		__NOP();
	}
}

extern "C" {
void SysTick_Handler(void)
{
	HAL_IncTick();
	// HAL_SYSTICK_IRQHandler();
}

void HardFault_Handler()
{
	volatile uint32_t hfsr, dfsr, afsr, bfar, mmfar, cfsr;
	mmfar = SCB->MMFAR;
	bfar = SCB->BFAR;

	hfsr = SCB->HFSR;
	afsr = SCB->AFSR;
	dfsr = SCB->DFSR;
	cfsr = SCB->CFSR;

	UNUSED(hfsr);
	UNUSED(afsr);
	UNUSED(dfsr);
	UNUSED(cfsr);
	UNUSED(mmfar);
	UNUSED(bfar);

	while (1)
		;
}
// void assert_failed(const char* file, uint32_t line) { while (1); }
void NMI_Handler()
{
	while (1)
		;
}
void MemManage_Handler()
{
	while (1)
		;
}
void BusFault_Handler()
{
	while (1)
		;
}
void UsageFault_Handler()
{
	while (1)
		;
}
void SVC_Handler()
{
	while (1)
		;
}
void DebugMon_Handler()
{
	while (1)
		;
}
void PendSV_Handler()
{
	while (1)
		;
}
void __cxa_pure_virtual()
{
	while (1)
		;
}
// __weak void _init() {}
// __weak void main() {}
}
