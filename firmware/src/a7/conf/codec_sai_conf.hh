#pragma once
#include "drivers/dma_config_struct.hh"
#include "drivers/pin.hh"
#include "drivers/sai_config_struct.hh"
#include "drivers/stm32xx.h"

const SaiConfig codec_sai_conf = {
	.sai = SAI3,
	.tx_block = SAI3_Block_A,
	.rx_block = SAI3_Block_B,

	.mode = SaiConfig::TXMaster,

	.dma_init_tx =
		{
			.DMAx = DMA2,
			.stream = DMA2_Stream1,		   // BDMA_Channel1,
			.channel = DMA_REQUEST_SAI3_A, // BDMA_REQUEST_SAI4_A,
			.IRQn = DMA2_Stream1_IRQn,	   // BDMA_Channel1_IRQn,
			.pri = 0,
			.subpri = 0,
		},
	.dma_init_rx =
		{
			.DMAx = DMA2,
			.stream = DMA2_Stream2,		   // BDMA_Channel0,
			.channel = DMA_REQUEST_SAI3_B, // BDMA_REQUEST_SAI4_B,
			.IRQn = DMA2_Stream2_IRQn,	   // BDMA_Channel0_IRQn,
			.pri = 0,
			.subpri = 0,
		},

	.datasize = SAI_DATASIZE_24,
	.framesize = 32,
	.samplerate = 48000,

	.MCLK = {GPIO::D, 15, LL_GPIO_AF_6},
	.SCLK = {GPIO::D, 0, LL_GPIO_AF_6},
	.LRCLK = {GPIO::D, 4, LL_GPIO_AF_6},
	.SD_DAC = {GPIO::D, 1, LL_GPIO_AF_6}, // SD A
	.SD_ADC = {GPIO::E, 1, LL_GPIO_AF_6}, // SD B
};
