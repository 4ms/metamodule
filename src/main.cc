#include <stm32f7xx.h>
#include "system.hh"
#include "ui.hh"
#include "debug.hh"
System sys;
Audio audio;
Ui ui;
Debug debug;

//Todo: create LED update timer to run ui.update() (which just updates LEDs if there's a glow or flash)
//

//every 682us (1.4kHz)
void audio_loop(AudioStreamBlock& in, AudioStreamBlock& out) {
	// debug.set(0,1);
	ui.params.update(); //This should be ui.read()
	audio.process(ui.params, in, out);
	// debug.set(0,0);
}

void main() {
	audio.register_callback(audio_loop);
	audio.start();

	ui.controls.begin();

	while (1) {
        ui.handle_sensor_queue();
		ui.update(); //leds
		__NOP();
	}
}


extern "C" {
void SysTick_Handler(void)
{
	HAL_IncTick();
	// HAL_SYSTICK_IRQHandler();
}

void HardFault_Handler() {
	volatile uint32_t hfsr,dfsr,afsr,bfar,mmfar,cfsr;
	mmfar=SCB->MMFAR;
	bfar=SCB->BFAR;

	hfsr=SCB->HFSR;
	afsr=SCB->AFSR;
	dfsr=SCB->DFSR;
	cfsr=SCB->CFSR;

	UNUSED(hfsr);
	UNUSED(afsr);
	UNUSED(dfsr);
	UNUSED(cfsr);
	UNUSED(mmfar);
	UNUSED(bfar);

	while(1);
}
  // void assert_failed(const char* file, uint32_t line) { while (1); }
  void NMI_Handler() { while(1); }
  void MemManage_Handler() { while (1); }
  void BusFault_Handler() { while (1); }
  void UsageFault_Handler() { while (1); }
  void SVC_Handler() { while(1); }
  void DebugMon_Handler() { while(1); }
  void PendSV_Handler() { while(1); }
  void __cxa_pure_virtual() { while(1); }
  // __weak void _init() {}
  // __weak void main() {}
}
