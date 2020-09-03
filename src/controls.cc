#include "controls.hh"
#include "debug.hh"
#include "stm32f7xx_ll_dma.h"

//"Thread" Controls::read()
//Read CV jacks ---> update oversampler
//Check ALERT pin --> queue an I2C message
//Read rotary pins ---> update controls.rotary[].turned = +/-1
//Read rotary buttons ---> update Debouncer
//??Check new value from DMA/IT TC IRQ -->> update controls.pad[].touching

void Controls::read()
{
	Debug::set_0(true);

	freq1_cv.read();
	freq2_cv.read();
	res1_cv.read();
	res2_cv.read();
	pads.check_alert_received();

	rotary_button[0].update();
	rotary_button[1].update();

	Debug::set_0(false);

	//read_rotary
	// rotary[0].read();
}

void Controls::begin()
{
	pads.begin();
}

Controls::Controls()
{
	//Todo: Think of a more elegant solution than to either
	//   1) call the start_dma() method of just one ADC channel per ADC periph,
	//or 2) call every ADC channels' start_dma() method but make AdcPeriph::start_dma() static so it can check if it's already been started
	//or 3) start the dma with the AdcPeriph<ADC_1>::start_dma(...) format

	freq1_cv.start_dma(DMA2, LL_DMA_STREAM_4, LL_DMA_CHANNEL_0, DMA2_Stream4_IRQn);
	// AdcPeriph<ADC_1>::start_dma(DMA2, LL_DMA_STREAM_4, LL_DMA_CHANNEL_0, DMA2_Stream4_IRQn);
}

//every 11.6us (86.2kHz), ~400ns
extern "C" void DMA2_Stream4_IRQHandler(void)
{
	if (LL_DMA_IsActiveFlag_TC4(DMA2)) {
		LL_DMA_ClearFlag_TC4(DMA2);
		Controls::read();
	}
	if (LL_DMA_IsActiveFlag_TE4(DMA2)) {
		LL_DMA_ClearFlag_TE4(DMA2);
		//Todo: Handle ADC DMA error
	}
}
