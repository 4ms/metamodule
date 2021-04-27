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

	// SAI 1
	// .MCLK = {GPIO::E, 2, LL_GPIO_AF_6},
	// .SCLK = {GPIO::E, 5, LL_GPIO_AF_6},
	// .LRCLK = {GPIO::G, 15, LL_GPIO_AF_6},
	// .SD_DAC = {GPIO::E, 6, LL_GPIO_AF_6},
	// .SD_ADC = {GPIO::E, 3, LL_GPIO_AF_6},

	// SAI 4:
	// .MCLK = {GPIO::B, 3, LL_GPIO_AF_12}, //works
	// .SCLK = {GPIO::B, 4, LL_GPIO_AF_4}, //does not work (not connected to other PCB)
	// .LRCLK = {GPIO::A, 15, LL_GPIO_AF_12}, //always high
	// .SD_DAC = {GPIO::B, 5, LL_GPIO_AF_10}, // SAI 4 SD A //does not work
	// .SD_ADC = {GPIO::H, 5, LL_GPIO_AF_12}, // SAI 4 SD B

	// SAI 3:
	.MCLK = {GPIO::D, 15, LL_GPIO_AF_6},
	.SCLK = {GPIO::D, 0, LL_GPIO_AF_6},
	.LRCLK = {GPIO::D, 4, LL_GPIO_AF_6},
	.SD_DAC = {GPIO::D, 1, LL_GPIO_AF_6}, // SD A
	.SD_ADC = {GPIO::E, 1, LL_GPIO_AF_6}, // SD B
};
