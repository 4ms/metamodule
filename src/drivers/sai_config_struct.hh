#pragma once
#include "dma_config_struct.hh"
#include "pin.hh"
#include "stm32xx.h"

struct SaiConfig {
	SAI_TypeDef *sai;
	SAI_Block_TypeDef *tx_block;
	SAI_Block_TypeDef *rx_block;

	DMAConfig dma_init_tx;
	DMAConfig dma_init_rx;

	uint32_t datasize;
	uint32_t framesize;
	uint32_t samplerate;

	PinNoInit MCLK;
	PinNoInit SCLK;
	PinNoInit LRCLK;
	PinNoInit SD_DAC;
	PinNoInit SD_ADC;
};
