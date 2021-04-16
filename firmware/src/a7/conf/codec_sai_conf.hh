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

	.MCLK = {GPIO::B, 3, 4},   // GPIO_AF4_SAI4},
	.SCLK = {GPIO::B, 4, 4},   // GPIO_AF4_SAI4},
	.LRCLK = {GPIO::A, 15, 2}, // GPIO_AF2_SAI4},
	.SD_DAC = {GPIO::B, 5, 3}, // GPIO_AF3_SAI4}, // SAI 4 A = RX
	.SD_ADC = {GPIO::H, 5, 6}, // GPIO_AF6_SAI4}, //<< fixme: not listed in datasheet! try 2 or 3 or 6 // SAI 4 B = TX
};
