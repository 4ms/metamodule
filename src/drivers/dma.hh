#pragma once
#include "interrupt.hh"
#include "stm32f7xx.h"
#include "system.hh"

struct DMAConfig {
	DMA_TypeDef *DMAx;
	DMA_Stream_TypeDef *stream;
	uint32_t channel;
	IRQn_Type IRQn;
	uint32_t pri;
	uint32_t subpri;
};

class DMAMem2Periph {
public:
	DMAMem2Periph(const DMAConfig dmaconf)
		: conf_(dmaconf)
	{
		System::enable_dma_rcc(conf_.DMAx);
	}
	DMAMem2Periph() {}
	void set_conf(const DMAConfig dmaconf)
	{
		conf_ = dmaconf;
	}
	void start_ISR(uint32_t pri1, uint32_t pri2)
	{
		if (conf_.stream == DMA1_Stream0) Interrupts::DMA::DMA1_S0_handle = &dmah_;
		if (conf_.stream == DMA1_Stream1) Interrupts::DMA::DMA1_S1_handle = &dmah_;
		if (conf_.stream == DMA1_Stream2) Interrupts::DMA::DMA1_S2_handle = &dmah_;
		if (conf_.stream == DMA1_Stream3) Interrupts::DMA::DMA1_S3_handle = &dmah_;
		if (conf_.stream == DMA1_Stream4) Interrupts::DMA::DMA1_S4_handle = &dmah_;
		if (conf_.stream == DMA1_Stream5) Interrupts::DMA::DMA1_S5_handle = &dmah_;
		if (conf_.stream == DMA1_Stream6) Interrupts::DMA::DMA1_S6_handle = &dmah_;
		if (conf_.stream == DMA1_Stream7) Interrupts::DMA::DMA1_S7_handle = &dmah_;
		if (conf_.stream == DMA2_Stream0) Interrupts::DMA::DMA2_S0_handle = &dmah_;
		if (conf_.stream == DMA2_Stream1) Interrupts::DMA::DMA2_S1_handle = &dmah_;
		if (conf_.stream == DMA2_Stream2) Interrupts::DMA::DMA2_S2_handle = &dmah_;
		if (conf_.stream == DMA2_Stream3) Interrupts::DMA::DMA2_S3_handle = &dmah_;
		if (conf_.stream == DMA2_Stream4) Interrupts::DMA::DMA2_S4_handle = &dmah_;
		if (conf_.stream == DMA2_Stream5) Interrupts::DMA::DMA2_S5_handle = &dmah_;
		if (conf_.stream == DMA2_Stream6) Interrupts::DMA::DMA2_S6_handle = &dmah_;
		if (conf_.stream == DMA2_Stream7) Interrupts::DMA::DMA2_S7_handle = &dmah_;

		HAL_NVIC_SetPriority(conf_.IRQn, pri1, pri2);
		HAL_NVIC_EnableIRQ(conf_.IRQn);
	}

protected:
	DMA_HandleTypeDef dmah_;
	DMAConfig conf_;
};
