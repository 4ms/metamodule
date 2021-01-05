#pragma once
#include "stm32xx.h"
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

// Todo: this should be in some dma manager class, and not a macro
// and also replace the HAL macros we use
#define __HAL_DMA_GET_ISR(__STREAM__)                                                                                  \
	(((uint32_t)(__STREAM__) > (uint32_t)DMA2_Stream3)                                                                 \
		 ? &(DMA2->HISR)                                                                                               \
		 : ((uint32_t)(__STREAM__) > (uint32_t)DMA1_Stream7)                                                           \
			   ? &(DMA2->LISR)                                                                                         \
			   : ((uint32_t)(__STREAM__) > (uint32_t)DMA1_Stream3) ? &(DMA1->HISR) : &(DMA1->LISR))

#define __HAL_DMA_GET_IFCR(__STREAM__)                                                                                 \
	(((uint32_t)(__STREAM__) > (uint32_t)DMA2_Stream3)                                                                 \
		 ? &(DMA2->HIFCR)                                                                                              \
		 : ((uint32_t)(__STREAM__) > (uint32_t)DMA1_Stream7)                                                           \
			   ? &(DMA2->LIFCR)                                                                                        \
			   : ((uint32_t)(__STREAM__) > (uint32_t)DMA1_Stream3) ? &(DMA1->HIFCR) : &(DMA1->LIFCR))
