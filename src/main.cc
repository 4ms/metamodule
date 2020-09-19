#include "debug.hh"
#include "defs/buses.hh"
#include "drivers/codec_WM8731.hh"
#include "stm32f7xx.h"
#include "system.hh"
#include "ui.hh"

const uint32_t kSampleRate = 48000;

System sys;
Debug debug;

// Todo: some class for grouping codec, bus, led driver chips, etc
// ExternalChips exthw;
// exthw.codec
// exthw.shared_i2c
CodecBus _codec_bus;
LEDDriverBus _leddriver_bus;

CodecWM8731 codec{CodecBus::i2c};

Controls controls;
Params params{controls};
Audio audio{params, codec, kSampleRate};
LedCtl leds{LEDDriverBus::i2c};
Ui ui{params, leds};

void main()
{
	audio.start();

	// leds.start_dma_mode();

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
