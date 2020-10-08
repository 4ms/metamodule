#pragma once
#include "analog_in.hh"
#include "dma_config_struct.hh"
#include "pin.hh"
#include "stm32f7xx_ll_dma.h"
#include "timekeeper.hh"

// Todo: put control pin defs here
struct DualOpenerADCs {
	// using AnalogInFreq0 = AnalogIn<AdcPeriphNum::_1, AdcChanNum::_2>;
	// static inline const Pin Freq0 = {GPIO::A, 2};
	//...
};

using CVADCPeriph = AdcPeriph<AdcPeriphNum::_1>;

const DMA_LL_Config ADC_DMA_conf = {
	.DMAx = DMA2,
	.stream = LL_DMA_STREAM_0,
	.channel = LL_DMA_CHANNEL_0,
	.IRQn = DMA2_Stream0_IRQn,
	.pri = 2,
	.subpri = 0,
};

const TimekeeperConfig control_read_tim_conf = {
	.TIMx = TIM6,
	.period_ns = 100000, // 10kHz
	.priority1 = 0,
	.priority2 = 0,
};
