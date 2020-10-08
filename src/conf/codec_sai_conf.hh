#pragma once
#include "dma_config_struct.hh"
#include "pin.hh"
#include "sai_config_struct.hh"
#include "stm32xx.h"

const SaiConfig codec_sai_conf = {
	.sai = SAI1,
	.tx_block = SAI1_Block_A,
	.rx_block = SAI1_Block_B,

	.dma_init_tx =
		{
			.DMAx = DMA2,
			.stream = DMA2_Stream1,
			.channel = DMA_CHANNEL_0,
			.IRQn = DMA2_Stream1_IRQn,
			.pri = 1,
			.subpri = 0,
		},
	.dma_init_rx =
		{
			.DMAx = DMA2,
			.stream = DMA2_Stream4,
			.channel = DMA_CHANNEL_1,
			.IRQn = DMA2_Stream4_IRQn,
			.pri = 1,
			.subpri = 0,
		},

	.datasize = SAI_DATASIZE_24,
	.framesize = 32,
	.samplerate = 48000,

	.MCLK = {GPIO::E, 2, GPIO_AF6_SAI1},
	.SCLK = {GPIO::E, 5, GPIO_AF6_SAI1},
	.LRCLK = {GPIO::E, 4, GPIO_AF6_SAI1},
	.SD_DAC = {GPIO::E, 6, GPIO_AF6_SAI1},
	.SD_ADC = {GPIO::E, 3, GPIO_AF6_SAI1},
};
