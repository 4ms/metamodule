#pragma once
#include "drivers/dma_config_struct.hh"
#include "drivers/pin.hh"
#include "drivers/sai_config_struct.hh"
#include "drivers/stm32xx.h"

const SaiConfig codec_sai_conf = {
	.sai = SAI1,
	.tx_block = SAI1_Block_B,
	.rx_block = SAI1_Block_A,

	.mode = SaiConfig::RXMaster,

	.dma_init_tx =
		{
			.DMAx = DMA1,
			.stream = DMA1_Stream1,		   // BDMA_Channel0,
			.channel = DMA_REQUEST_SAI1_B, // BDMA_REQUEST_SAI4_B,
			.IRQn = DMA1_Stream1_IRQn,	   // BDMA_Channel0_IRQn,
			.pri = 1,
			.subpri = 0,
		},
	.dma_init_rx =
		{
			.DMAx = DMA1,
			.stream = DMA1_Stream0,		   // BDMA_Channel1,
			.channel = DMA_REQUEST_SAI1_A, // BDMA_REQUEST_SAI4_A,
			.IRQn = DMA1_Stream0_IRQn,	   // BDMA_Channel1_IRQn,
			.pri = 1,
			.subpri = 0,
		},

	.datasize = SAI_DATASIZE_24,
	.framesize = 32,
	.samplerate = 48000,

	.MCLK = {GPIO::E, 2, GPIO_AF6_SAI1},
	.SCLK = {GPIO::E, 5, GPIO_AF6_SAI1},
	.LRCLK = {GPIO::E, 4, GPIO_AF6_SAI1},
	.SD_DAC = {GPIO::E, 3, GPIO_AF6_SAI1},
	.SD_ADC = {GPIO::E, 6, GPIO_AF6_SAI1},
};
