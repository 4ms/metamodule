#pragma once
#include "stm32f7xx.h"
#include "pin.hh"

//I2C_bus_defs:
struct LedDriverDefs {
	// const static inline auto I2C_EV_IRQn = I2C1_EV_IRQn;
	// const static inline auto I2C_ER_IRQn = I2C1_ER_IRQn;

	static inline DMA_TypeDef *DMAx = DMA1;
	static inline auto DMAx_stream = DMA1_Stream6;
	const static inline auto DMAx_channel = DMA_CHANNEL_1;
	const static inline auto DMA_TX_IRQn = DMA1_Stream6_IRQn;

};

#define LEDDRIVER_I2C_DMA_TX_IRQHandler DMA1_Stream6_IRQHandler 

