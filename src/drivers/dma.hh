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

struct DMA_LL_Config {
	DMA_TypeDef *DMAx;
	uint32_t stream;
	uint32_t channel;
	IRQn_Type IRQn;
	uint32_t pri;
	uint32_t subpri;
};

class DMAMem2Periph : public InterruptManager::ISRBase {
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
		InterruptManager::registerISR(conf_.IRQn, this);
		HAL_NVIC_SetPriority(conf_.IRQn, pri1, pri2);
		HAL_NVIC_EnableIRQ(conf_.IRQn);
	}
	virtual void isr() = 0;

protected:
	DMA_HandleTypeDef dmah_;
	DMAConfig conf_;
};
