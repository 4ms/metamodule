#include "controls.hh"
#include "debug.hh"
#include "dma_config_struct.hh"
#include "stm32f7xx_ll_dma.h"

void Controls::read()
{
	Debug::set_0(true);

	freq_cv0.read();
	res_cv0.read();
	freq_cv1.read();
	res_cv1.read();
	for (uint32_t i = 0; i < 2; i++) {
		rotary[i].update();
		rotary_button[i].update();
		mode_button[i].update();
		freq_sense[i].update();
		res_sense[i].update();
		in_sense[i].update();
		out_sense[i].update();
	}
	Debug::set_0(false);
}

void Controls::begin()
{
	read_controls_task.start();
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

	read_controls_task.init(kControlReadTaskConfig, [this]() { read(); });
}

