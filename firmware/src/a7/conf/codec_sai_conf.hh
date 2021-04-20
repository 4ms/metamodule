#pragma once
#include "drivers/dma_config_struct.hh"
#include "drivers/pin.hh"
#include "drivers/sai_config_struct.hh"
#include "drivers/stm32xx.h"

const SaiConfig codec_sai_conf = {
	.sai = SAI4,
	.tx_block = SAI4_Block_B,
	.rx_block = SAI4_Block_A,

	.mode = SaiConfig::RXMaster,

	.dma_init_tx =
		{
			.DMAx = DMA2,
			.stream = DMA2_Stream1,		   // BDMA_Channel0,
			.channel = DMA_REQUEST_SAI4_B, // BDMA_REQUEST_SAI4_B,
			.IRQn = DMA2_Stream1_IRQn,	   // BDMA_Channel0_IRQn,
			.pri = 1,
			.subpri = 0,
		},
	.dma_init_rx =
		{
			.DMAx = DMA2,
			.stream = DMA2_Stream0,		   // BDMA_Channel1,
			.channel = DMA_REQUEST_SAI4_A, // BDMA_REQUEST_SAI4_A,
			.IRQn = DMA2_Stream0_IRQn,	   // BDMA_Channel1_IRQn,
			.pri = 1,
			.subpri = 0,
		},

	.datasize = SAI_DATASIZE_24,
	.framesize = 32,
	.samplerate = 48000,

	.MCLK = {GPIO::B, 3, LL_GPIO_AF_12},
	.SCLK = {GPIO::B, 4, LL_GPIO_AF_4},
	.LRCLK = {GPIO::A, 15, LL_GPIO_AF_12},
	.SD_DAC = {GPIO::B, 5, LL_GPIO_AF_10}, // SAI 4 A = RX
	.SD_ADC = {GPIO::H, 5, LL_GPIO_AF_12}, // SAI 4 B = TX
};
