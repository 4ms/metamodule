#include "controls.hh"
#include "debug.hh"
#include "dma_config_struct.hh"
#include "stm32f7xx_ll_dma.h"

void Controls::read()
{
	Debug::set_0(true);

	for (uint32_t i = 0; i < 2; i++) {
		freq_cv[i].read();
		res_cv[i].read();
		rotary[i].update();
		rotary_button[i].update();
	}
	Debug::set_0(false);
}

void Controls::begin()
{
	//?? Todo: is this needed?
}

Controls::Controls()
{
	const DMA_LL_Config kADCDMAConfig = {
		.DMAx = DMA2,
		.stream = LL_DMA_STREAM_4,
		.channel = LL_DMA_CHANNEL_0,
		.IRQn = DMA2_Stream4_IRQn,
		.pri = 1,
		.subpri = 0,
	};
	AdcPeriph<ADC_1>::init_dma(kADCDMAConfig);
	AdcPeriph<ADC_1>::start_adc();

	const TimekeeperConfig kControlReadTaskConfig = {
		.TIMx = TIM6,
		.period_ns = 11000,
		.priority1 = 2,
		.priority2 = 3,
	};

	read_controls_task.init(
		kControlReadTaskConfig,
		[this]() { read(); });
}

